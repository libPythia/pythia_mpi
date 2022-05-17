#include "pythia.h"

#include <stdlib.h>
#include <time.h>

#include <array>
#include <atomic>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <eta/factorization/bin_file.hpp>
#include <eta/factorization/prediction.hpp>
#include <eta/factorization/reduction.hpp>
#include <fstream>
#include <iostream>
#include <list>
#include <tuple>
#include <unordered_map>


#define AUX(x, y) case Pythia##x: return "MPI_" #x;
inline auto pythia_MPI_fn_name(Pythia_MPI_fn fn) {
    switch (fn) {
#include "pythia_fn.inl"
        default: return "UNKNOWN";
    }
}
#undef AUX

struct tuple_hash {
    template <class T1, class T2, class T3> std::size_t operator()(const std::tuple<T1, T2, T3> & t) const {
        return std::hash<T1>()(std::get<0>(t)) ^ std::hash<T2>()(std::get<1>(t)) ^std::hash<T3>()(std::get<2>(t));
    }
};

struct Payload {
    Pythia_MPI_fn fn;
    int arg1;
    int arg2;
    int arg3;
};

struct PredictionTest {
    size_t event_id;
    Payload const * payload;
    size_t duration;
};

struct PredictionStatistics {
    size_t count = 0;
    size_t min_duration = 0;
    size_t max_duration = 0;
    size_t total_duration = 0;
};

struct Data {
    struct Event {
        std::unordered_map<std::tuple<int, int, int>, Terminal *, tuple_hash> terminals;
    };
    std::array<Event, (int)Pythia_MPI_fn::COUNT - 1> events;

    size_t event_id = 0;
    size_t world_rank;

    std::atomic_int recursion_count = 1;
    bool is_recording = true;
    bool log = false;
    bool register_size;

    int prediction_advance = 1;
    bool log_prediction = false;
    Estimation estimation;
    std::list<PredictionTest> prediction_test;
    PredictionStatistics prediction_success;
    PredictionStatistics prediction_failure;
    PredictionStatistics no_prediction;

    Grammar grammar;
    NonTerminal * root = nullptr;

    char file_name[1024];
    char stats_file_name[1024];

    bool initialized = false;
};

static auto get_data() -> Data * {
	static auto d = new Data;
	return d;
}

// -------------------------------------------------------------

enum class ActionOnEvent {
    do_nothing,
    trigger_prediction,
};

static auto trigger_prediction(Pythia_MPI_fn fn) -> bool {
#define AUX(x, y) case Pythia_MPI_fn::Pythia##x: return ActionOnEvent::y == ActionOnEvent::trigger_prediction;
    switch (fn) {
#include "pythia_fn.inl"
        default: assert(false);
    }
#undef AUX
}

static auto timespec_diff(timespec a, timespec b) -> timespec {
    timespec result;
    result.tv_sec  = a.tv_sec  - b.tv_sec;
    result.tv_nsec = a.tv_nsec - b.tv_nsec;
    if (result.tv_nsec < 0) {
        --result.tv_sec;
        result.tv_nsec += 1000000000L;
    }
    return result;
}

static auto compute_duration_ms(timespec const & start) -> size_t {
    timespec stop, result;
    timespec_get(&stop, TIME_UTC);
    auto const diff = timespec_diff(stop, start);
    assert(diff.tv_sec == 0);
    return diff.tv_nsec;
}

static auto update_prediction_statistics(PredictionStatistics * stats, size_t duration_ns) {
    if (stats->count == 0 || duration_ns < stats->min_duration)
        stats->min_duration = duration_ns;
    if (stats->count == 0 || duration_ns > stats->max_duration)
        stats->max_duration= duration_ns;
    stats->total_duration += duration_ns;
    ++stats->count;
}

static auto record_event(Pythia_MPI_fn fn, Terminal * terminal) -> void {
    auto const data = get_data();
    if (data->initialized == false)
	    return;

    ++data->event_id;

    if (data->is_recording) {
        data->root = insertSymbol(data->grammar, data->root, terminal);
    } else {
        data->estimation = next_estimation(std::move(data->estimation), terminal);

        if (trigger_prediction(fn)) {
            timespec start;
            timespec_get(&start, TIME_UTC);
            auto prediction = get_prediction_from_estimation(data->estimation);
            if (prediction.infos.size() == 0) {
                update_prediction_statistics(&data->no_prediction, compute_duration_ms(start));
            } else {
                auto i = 1;

                for (i = 1; i < data->prediction_advance; ++i) {
                    if (get_first_next(&prediction) == false) {
                        i = -1;
                        break;
                    }
                }

                if (i != data->prediction_advance) {
                    update_prediction_statistics(&data->no_prediction, compute_duration_ms(start));
                } else {
                    auto const predicted_event =
                        (Payload const *)get_terminal(prediction)->payload;
                    data->prediction_test.push_back( {
                        data->event_id + data->prediction_advance,
                        predicted_event,
                        compute_duration_ms(start)
                    });
                }
            }
        }

        if (data->prediction_test.size() > 0) {
            auto const prediction = data->prediction_test.front();
            if (prediction.event_id == data->event_id) {
                if (terminal == nullptr) {
                    update_prediction_statistics(&data->prediction_failure, prediction.duration);
                } else {
                    auto const payload = (Payload const *)terminal->payload;
                    if (prediction.payload == payload) {
                        update_prediction_statistics(&data->prediction_success, prediction.duration);
                    } else {
                        update_prediction_statistics(&data->prediction_failure, prediction.duration);
                    }
                }
                data->prediction_test.pop_front();
            }
        }
    }
}

extern "C" {

auto pythia_event(Pythia_MPI_fn fn, int arg1, int arg2, int arg3) -> void {
    auto const data = get_data();
    if (++data->recursion_count == 1) {
        if (data->log)
            fprintf(stdout, "%lu: Pythia raised event %s with args %d, %d, %d\n", data->world_rank, pythia_MPI_fn_name(fn), arg1, arg2, arg3);

        auto const terminal = [&]() -> Terminal * {
            auto const [it, inserted] =
                    data->events[(int)fn].terminals.try_emplace({ arg1, arg2, arg3 }, nullptr);
            if (inserted && data->is_recording) {
                it->second = new_terminal(data->grammar, new Payload { fn, arg1, arg2, arg3 });
            }
            return it->second;
        }();

        record_event(fn, terminal);
    }
    --data->recursion_count;
}

int pythia_record_size() {
    return get_data()->register_size;
}

// -------------------------------------------------------------

static auto serialize(Terminal const * t, std::ostream & os) -> void {
    auto const p = (Payload const *)t->payload;
    os << (int)p->fn << ':' << p->arg1 << ',' << p->arg2 << ',' << p->arg3;
}

static auto deserialize(std::istream & is, size_t size) -> void * {
    char buf[2048];
    assert(size < 2048);
    assert(size > 0);
    is.read(buf, size);
    buf[size] = 0;
    int fn, arg1, arg2, arg3;
    sscanf(buf, "%d:%d,%d,%d", &fn, &arg1, &arg2, &arg3);
    return new Payload { (Pythia_MPI_fn)fn, arg1 , arg2, arg3};
}

auto pythia_init(int world_rank) -> void {
    auto const data = get_data();
    data->world_rank = world_rank;

    sprintf(data->file_name, "pythia_MPI_%d.btr", world_rank);
    sprintf(data->stats_file_name, "preditions_%d.stats", world_rank);

    auto const log_env = getenv("PYTHIA_MPI_LOG");
    data->log = (log_env != nullptr && strcmp(log_env, "YES") == 0);

    auto const mode_env = getenv("PYTHIA_MPI");
    data->is_recording = mode_env == nullptr || strcmp(mode_env, "Predict") != 0;
    if (data->log)
        fprintf(stdout, data->is_recording ? "Pythia MPI recording\n" : "Pythia MPI predicting\n");

    auto const register_size_env = getenv("PYTHIA_MPI_REGISTER_SIZES");
    data->register_size = register_size_env != nullptr && strcmp(register_size_env, "YES") == 0;

    if (data->is_recording == false) {
        auto file = std::ifstream { data->file_name };
        if (data->log)
            fprintf(stdout, "Load trace from file %s\n", data->file_name);
        load_bin_file(data->grammar, file, deserialize);

        for (auto & terminal : data->grammar.terminals) {
            auto const p = (Payload const *)terminal->payload;
            data->events[(int)p->fn].terminals[{ p->arg1, p->arg2, p->arg3}] = terminal.get();
        }

        auto const advance_env = getenv("PYTHIA_MPI_PREDICTION_ADVANCE");
        data->prediction_advance = advance_env == nullptr ? 1 : atoi(advance_env);

        auto const log_prediction_env = getenv("PYTHIA_MPI_LOG_PREDICTION");
        data->log_prediction =  log_prediction_env != nullptr &&
                                          strcmp(log_prediction_env, "YES") == 0;
        data->estimation = init_estimation_from_start(data->grammar);

    }

    data->initialized = true;
    data->recursion_count = 0;
}

auto pythia_deinit() -> void {
    auto const data = get_data();
    if (data->is_recording) {
        if (data->root != nullptr) {
            if (data->log)
                fprintf(stdout, "Export trace in file %s\n", data->file_name);
            auto file = std::ofstream{data->file_name};
            print_bin_file(data->grammar, file, serialize);
        } else if (data->log)
            fprintf(stdout, "No trace to export\n");
    } else {
        auto const succ = data->prediction_success;;
        auto const fail = data->prediction_failure;
        auto const no = data->no_prediction;
        auto f = fopen(data->stats_file_name, "w");
        fprintf(f, "type,count,min,max,total\n");
        fprintf(f, "success,%ld,%ld,%ld,%ld\n",succ.count, succ.min_duration, succ.max_duration, succ.total_duration);
        fprintf(f, "impossible,%ld,%ld,%ld,%ld\n",no.count, no.min_duration, no.max_duration, no.total_duration);
        fprintf(f, "failure,%ld,%ld,%ld,%ld\n",fail.count, fail.min_duration, fail.max_duration, fail.total_duration);
        fclose(f);
    }
    if (data->log)
        fprintf(stdout, "Close Pythia\n");
}

} // extern "C"
