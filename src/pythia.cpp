#include "pythia.h"

#include <stdlib.h>

#include <array>
#include <atomic>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <eta/factorization/bin_file.hpp>
#include <eta/factorization/reduction.hpp>
#include <fstream>
#include <iostream>
#include <tuple>
#include <unordered_map>


#define AUX(x) case Pythia##x: return "MPI_" #x
inline auto pythia_MPI_fn_name(Pythia_MPI_fn fn) {
    switch (fn) {
	    AUX(Allgather);
	    AUX(Allgatherv);
	    AUX(Allreduce);
	    AUX(Alltoall);
	    AUX(Alltoallv);
	    AUX(Barrier);
	    AUX(Bcast);
	    AUX(Bsend);
	    AUX(Gather);
	    AUX(Gatherv);
	    AUX(Get);
	    AUX(Iallgather );
	    AUX(Iallgatherv);
	    AUX(Iallreduce);
	    AUX(Ialltoall);
	    AUX(Ialltoallv);
	    AUX(Ibarrier);
	    AUX(Ibcast);
	    AUX(Ibsend);
	    AUX(Igather);
	    AUX(Igatherv);
	    AUX(Irecv);
	    AUX(Ireduce);
	    AUX(Ireduce_scatter);
	    AUX(Irsend);
	    AUX(Iscan);
	    AUX(Iscatter);
	    AUX(Iscatterv);
	    AUX(Isend);
	    AUX(Issend);
	    AUX(Probe);
	    AUX(Put);
	    AUX(Recv);
	    AUX(Reduce);
	    AUX(Reduce_scatter);
	    AUX(Rsend);
	    AUX(Scan);
	    AUX(Scatter);
	    AUX(Scatterv);
	    AUX(Send);
	    AUX(Sendrecv);
	    AUX(Sendrecv_replace);
	    AUX(Ssend);
	    AUX(Startall);
	    AUX(Start);
	    AUX(Testall);
	    AUX(Testany);
	    AUX(Test);
	    AUX(Testsome);
	    AUX(Waitall);
	    AUX(Waitany);
	    AUX(Wait);
	    AUX(Waitsome);
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

struct Data {
    struct Event {
        std::unordered_map<std::tuple<int, int, int>, Terminal *, tuple_hash> terminals;
    };
    std::array<Event, (int)Pythia_MPI_fn::COUNT - 1> events;

    std::atomic_int recursion_count = 1;
    bool is_recording = true;
    bool log = false;

    Grammar grammar;
    NonTerminal * root = nullptr;

    char file_name[1024];
};

static auto get_data() -> Data * {
	static auto d = new Data;
	return d;
}

// -------------------------------------------------------------

extern "C" {

auto pythia_event(Pythia_MPI_fn fn, int arg1, int arg2, int arg3) -> void {
    if (++get_data()->recursion_count == 1) {
        if (get_data()->log)
            fprintf(stdout, "Pythia raised event %s with args %d, %d, %d\n", pythia_MPI_fn_name(fn), arg1, arg2, arg3);

        auto const terminal = [&]() -> Terminal * {
            auto const [it, inserted] =
                    get_data()->events[(int)fn].terminals.try_emplace({ arg1, arg2, arg3 }, nullptr);
            if (inserted && get_data()->is_recording) {
                it->second = new_terminal(get_data()->grammar, new Payload { fn, arg1, arg2, arg3 });
            }
            return it->second;
        }();

        if (get_data()->is_recording) {
            get_data()->root = insertSymbol(get_data()->grammar, get_data()->root, terminal);
        } else {
            assert(false);
        }
    }
    --get_data()->recursion_count;
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
    sprintf(get_data()->file_name, "pythia_MPI_%d.btr", world_rank);

    auto const log_env = getenv("PYTHIA_MPI_LOG");
    get_data()->log = (log_env != nullptr && strcmp(log_env, "YES") == 0);

    auto const mode_env = getenv("PYTHIA_MPI");
    get_data()->is_recording = mode_env == nullptr || strcmp(mode_env, "Predict") != 0;
    if (get_data()->log)
        fprintf(stdout, get_data()->is_recording ? "Pythia MPI recording\n" : "Pythia MPI predicting\n");

    if (get_data()->is_recording == false) {
        auto file = std::ifstream { get_data()->file_name };
        if (get_data()->log)
            fprintf(stdout, "Load trace from file %s\n", get_data()->file_name);
        load_bin_file(get_data()->grammar, file, deserialize);

        for (auto & terminal : get_data()->grammar.terminals) {
            auto const p = (Payload const *)terminal->payload;
            get_data()->events[(int)p->fn].terminals[{ p->arg1, p->arg2, p->arg3}] = terminal.get();
        }
    }
    get_data()->recursion_count = 0;
}

auto pythia_deinit() -> void {
    if (get_data()->is_recording) {
	if (get_data()->root != nullptr) {
		if (get_data()->log)
		    fprintf(stdout, "Export trace in file %s\n", get_data()->file_name);
		auto file = std::ofstream { get_data()->file_name };
		print_bin_file(get_data()->grammar, file, serialize);
	}
	else if (get_data()->log)
		    fprintf(stdout, "No trace to export\n");
    }
    if (get_data()->log)
	    fprintf(stdout, "Close Pythia\n");
}

} // extern "C"
