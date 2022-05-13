#define _GNU_SOURCE
#include <assert.h>
#include <dlfcn.h>
#include <stddef.h>

#include "pythia.h"

// Includes

// Extra definitions

// Pointers on intercepted fonctions
void omp_destroy_lock(long svar) {
    pythia_event(PythiaOMP_destroy_lock_event, 0, 0, 0);

    static void (*orig_omp_destroy_lock)(long) = 0;
    if (orig_omp_destroy_lock == 0)
        orig_omp_destroy_lock = (void(*)(long)) dlsym(RTLD_NEXT, "omp_destroy_lock");

    orig_omp_destroy_lock(svar);
}
void omp_destroy_nest_lock(long svar) {
    pythia_event(PythiaOMP_destroy_nest_lock_event, 0, 0, 0);

    static void (*orig_omp_destroy_nest_lock)(long) = 0;
    if (orig_omp_destroy_nest_lock == 0)
        orig_omp_destroy_nest_lock = (void(*)(long)) dlsym(RTLD_NEXT, "omp_destroy_nest_lock");

    orig_omp_destroy_nest_lock(svar);
}
long omp_get_active_level() {
    pythia_event(PythiaOMP_get_active_level_event, 0, 0, 0);

    static long (*orig_omp_get_active_level)(void) = 0;
    if (orig_omp_get_active_level == 0)
        orig_omp_get_active_level = (long(*)(void)) dlsym(RTLD_NEXT, "omp_get_active_level");

    long ret = orig_omp_get_active_level();
    return ret;
}
long omp_get_ancestor_thread_num(long level) {
    pythia_event(PythiaOMP_get_ancestor_thread_num_event, 0, 0, 0);

    static long (*orig_omp_get_ancestor_thread_num)(long) = 0;
    if (orig_omp_get_ancestor_thread_num == 0)
        orig_omp_get_ancestor_thread_num = (long(*)(long)) dlsym(RTLD_NEXT, "omp_get_ancestor_thread_num");

    long ret = orig_omp_get_ancestor_thread_num(level);
    return ret;
}
long omp_get_dynamic() {
    pythia_event(PythiaOMP_get_dynamic_event, 0, 0, 0);

    static long (*orig_omp_get_dynamic)(void) = 0;
    if (orig_omp_get_dynamic == 0)
        orig_omp_get_dynamic = (long(*)(void)) dlsym(RTLD_NEXT, "omp_get_dynamic");

    long ret = orig_omp_get_dynamic();
    return ret;
}
long omp_get_level() {
    pythia_event(PythiaOMP_get_level_event, 0, 0, 0);

    static long (*orig_omp_get_level)(void) = 0;
    if (orig_omp_get_level == 0)
        orig_omp_get_level = (long(*)(void)) dlsym(RTLD_NEXT, "omp_get_level");

    long ret = orig_omp_get_level();
    return ret;
}
long omp_get_max_active_levels() {
    pythia_event(PythiaOMP_get_max_active_levels_event, 0, 0, 0);

    static long (*orig_omp_get_max_active_levels)(void) = 0;
    if (orig_omp_get_max_active_levels == 0)
        orig_omp_get_max_active_levels = (long(*)(void)) dlsym(RTLD_NEXT, "omp_get_max_active_levels");

    long ret = orig_omp_get_max_active_levels();
    return ret;
}
long omp_get_max_threads() {
    pythia_event(PythiaOMP_get_max_threads_event, 0, 0, 0);

    static long (*orig_omp_get_max_threads)(void) = 0;
    if (orig_omp_get_max_threads == 0)
        orig_omp_get_max_threads = (long(*)(void)) dlsym(RTLD_NEXT, "omp_get_max_threads");

    long ret = orig_omp_get_max_threads();
    return ret;
}
long omp_get_nested() {
    pythia_event(PythiaOMP_get_nested_event, 0, 0, 0);

    static long (*orig_omp_get_nested)(void) = 0;
    if (orig_omp_get_nested == 0)
        orig_omp_get_nested = (long(*)(void)) dlsym(RTLD_NEXT, "omp_get_nested");

    long ret = orig_omp_get_nested();
    return ret;
}
long omp_get_num_procs() {
    pythia_event(PythiaOMP_get_num_procs_event, 0, 0, 0);

    static long (*orig_omp_get_num_procs)(void) = 0;
    if (orig_omp_get_num_procs == 0)
        orig_omp_get_num_procs = (long(*)(void)) dlsym(RTLD_NEXT, "omp_get_num_procs");

    long ret = orig_omp_get_num_procs();
    return ret;
}
long omp_get_num_threads() {
    pythia_event(PythiaOMP_get_num_threads_event, 0, 0, 0);

    static long (*orig_omp_get_num_threads)(void) = 0;
    if (orig_omp_get_num_threads == 0)
        orig_omp_get_num_threads = (long(*)(void)) dlsym(RTLD_NEXT, "omp_get_num_threads");

    long ret = orig_omp_get_num_threads();
    return ret;
}
long omp_get_schedule(long kind, long modifier) {
    pythia_event(PythiaOMP_get_schedule_event, 0, 0, 0);

    static long (*orig_omp_get_schedule)(long, long) = 0;
    if (orig_omp_get_schedule == 0)
        orig_omp_get_schedule = (long(*)(long, long)) dlsym(RTLD_NEXT, "omp_get_schedule");

    long ret = orig_omp_get_schedule(kind, modifier);
    return ret;
}
long omp_get_team_size(long level) {
    pythia_event(PythiaOMP_get_team_size_event, 0, 0, 0);

    static long (*orig_omp_get_team_size)(long) = 0;
    if (orig_omp_get_team_size == 0)
        orig_omp_get_team_size = (long(*)(long)) dlsym(RTLD_NEXT, "omp_get_team_size");

    long ret = orig_omp_get_team_size(level);
    return ret;
}
long omp_get_thread_limit() {
    pythia_event(PythiaOMP_get_thread_limit_event, 0, 0, 0);

    static long (*orig_omp_get_thread_limit)(void) = 0;
    if (orig_omp_get_thread_limit == 0)
        orig_omp_get_thread_limit = (long(*)(void)) dlsym(RTLD_NEXT, "omp_get_thread_limit");

    long ret = orig_omp_get_thread_limit();
    return ret;
}
long omp_get_thread_num() {
    pythia_event(PythiaOMP_get_thread_num_event, 0, 0, 0);

    static long (*orig_omp_get_thread_num)(void) = 0;
    if (orig_omp_get_thread_num == 0)
        orig_omp_get_thread_num = (long(*)(void)) dlsym(RTLD_NEXT, "omp_get_thread_num");

    long ret = orig_omp_get_thread_num();
    return ret;
}
double omp_get_wtick() {
    pythia_event(PythiaOMP_get_wtick_event, 0, 0, 0);

    static double (*orig_omp_get_wtick)(void) = 0;
    if (orig_omp_get_wtick == 0)
        orig_omp_get_wtick = (double(*)(void)) dlsym(RTLD_NEXT, "omp_get_wtick");

    double ret = orig_omp_get_wtick();
    return ret;
}
double omp_get_wtime() {
    pythia_event(PythiaOMP_get_wtime_event, 0, 0, 0);

    static double (*orig_omp_get_wtime)(void) = 0;
    if (orig_omp_get_wtime == 0)
        orig_omp_get_wtime = (double(*)(void)) dlsym(RTLD_NEXT, "omp_get_wtime");

    double ret = orig_omp_get_wtime();
    return ret;
}
long omp_in_final() {
    pythia_event(PythiaOMP_in_final_event, 0, 0, 0);

    static long (*orig_omp_in_final)(void) = 0;
    if (orig_omp_in_final == 0)
        orig_omp_in_final = (long(*)(void)) dlsym(RTLD_NEXT, "omp_in_final");

    long ret = orig_omp_in_final();
    return ret;
}
long omp_in_parallel() {
    pythia_event(PythiaOMP_in_parallel_event, 0, 0, 0);

    static long (*orig_omp_in_parallel)(void) = 0;
    if (orig_omp_in_parallel == 0)
        orig_omp_in_parallel = (long(*)(void)) dlsym(RTLD_NEXT, "omp_in_parallel");

    long ret = orig_omp_in_parallel();
    return ret;
}
void omp_init_lock(long svar) {
    pythia_event(PythiaOMP_init_lock_event, 0, 0, 0);

    static void (*orig_omp_init_lock)(long) = 0;
    if (orig_omp_init_lock == 0)
        orig_omp_init_lock = (void(*)(long)) dlsym(RTLD_NEXT, "omp_init_lock");

    orig_omp_init_lock(svar);
}
void omp_init_nest_lock(long nvar) {
    pythia_event(PythiaOMP_init_nest_lock_event, 0, 0, 0);

    static void (*orig_omp_init_nest_lock)(long) = 0;
    if (orig_omp_init_nest_lock == 0)
        orig_omp_init_nest_lock = (void(*)(long)) dlsym(RTLD_NEXT, "omp_init_nest_lock");

    orig_omp_init_nest_lock(nvar);
}
void omp_set_dynamic(long enable_expr) {
    pythia_event(PythiaOMP_set_dynamic_event, 0, 0, 0);

    static void (*orig_omp_set_dynamic)(long) = 0;
    if (orig_omp_set_dynamic == 0)
        orig_omp_set_dynamic = (void(*)(long)) dlsym(RTLD_NEXT, "omp_set_dynamic");

    orig_omp_set_dynamic(enable_expr);
}
void omp_set_lock(long svar) {
    pythia_event(PythiaOMP_set_lock_event, 0, 0, 0);

    static void (*orig_omp_set_lock)(long) = 0;
    if (orig_omp_set_lock == 0)
        orig_omp_set_lock = (void(*)(long)) dlsym(RTLD_NEXT, "omp_set_lock");

    orig_omp_set_lock(svar);
}
void omp_set_max_active_levels(long max_levels) {
    pythia_event(PythiaOMP_set_max_active_levels_event, 0, 0, 0);

    static void (*orig_omp_set_max_active_levels)(long) = 0;
    if (orig_omp_set_max_active_levels == 0)
        orig_omp_set_max_active_levels = (void(*)(long)) dlsym(RTLD_NEXT, "omp_set_max_active_levels");

    orig_omp_set_max_active_levels(max_levels);
}
long omp_set_nested(long enable_expr) {
    pythia_event(PythiaOMP_set_nested_event, 0, 0, 0);

    static long (*orig_omp_set_nested)(long) = 0;
    if (orig_omp_set_nested == 0)
        orig_omp_set_nested = (long(*)(long)) dlsym(RTLD_NEXT, "omp_set_nested");

    long ret = orig_omp_set_nested(enable_expr);
    return ret;
}
void omp_set_nest_lock(long nvar) {
    pythia_event(PythiaOMP_set_nest_lock_event, 0, 0, 0);

    static void (*orig_omp_set_nest_lock)(long) = 0;
    if (orig_omp_set_nest_lock == 0)
        orig_omp_set_nest_lock = (void(*)(long)) dlsym(RTLD_NEXT, "omp_set_nest_lock");

    orig_omp_set_nest_lock(nvar);
}
void omp_set_num_threads(long number_of_threads_expr) {
    pythia_event(PythiaOMP_set_num_threads_event, 0, 0, 0);

    static void (*orig_omp_set_num_threads)(long) = 0;
    if (orig_omp_set_num_threads == 0)
        orig_omp_set_num_threads = (void(*)(long)) dlsym(RTLD_NEXT, "omp_set_num_threads");

    orig_omp_set_num_threads(number_of_threads_expr);
}
void omp_set_schedule(long kind, long modifier) {
    pythia_event(PythiaOMP_set_schedule_event, 0, 0, 0);

    static void (*orig_omp_set_schedule)(long, long) = 0;
    if (orig_omp_set_schedule == 0)
        orig_omp_set_schedule = (void(*)(long, long)) dlsym(RTLD_NEXT, "omp_set_schedule");

    orig_omp_set_schedule(kind, modifier);
}
long omp_test_lock(long svar) {
    pythia_event(PythiaOMP_test_lock_event, 0, 0, 0);

    static long (*orig_omp_test_lock)(long) = 0;
    if (orig_omp_test_lock == 0)
        orig_omp_test_lock = (long(*)(long)) dlsym(RTLD_NEXT, "omp_test_lock");

    long ret = orig_omp_test_lock(svar);
    return ret;
}
long omp_test_nest_lock(long nvar) {
    pythia_event(PythiaOMP_test_nest_lock_event, 0, 0, 0);

    static long (*orig_omp_test_nest_lock)(long) = 0;
    if (orig_omp_test_nest_lock == 0)
        orig_omp_test_nest_lock = (long(*)(long)) dlsym(RTLD_NEXT, "omp_test_nest_lock");

    long ret = orig_omp_test_nest_lock(nvar);
    return ret;
}
void omp_unset_lock(long svar) {
    pythia_event(PythiaOMP_unset_lock_event, 0, 0, 0);

    static void (*orig_omp_unset_lock)(long) = 0;
    if (orig_omp_unset_lock == 0)
        orig_omp_unset_lock = (void(*)(long)) dlsym(RTLD_NEXT, "omp_unset_lock");

    orig_omp_unset_lock(svar);
}
void omp_unset_nest_lock(long nvar) {
    pythia_event(PythiaOMP_unset_nest_lock_event, 0, 0, 0);

    static void (*orig_omp_unset_nest_lock)(long) = 0;
    if (orig_omp_unset_nest_lock == 0)
        orig_omp_unset_nest_lock = (void(*)(long)) dlsym(RTLD_NEXT, "omp_unset_nest_lock");

    orig_omp_unset_nest_lock(nvar);
}
void GOMP_atomic_enter() {
    pythia_event(PythiaGOMP_atomic_enter_event, 0, 0, 0);

    static void (*orig_GOMP_atomic_enter)(void) = 0;
    if (orig_GOMP_atomic_enter == 0)
        orig_GOMP_atomic_enter = (void(*)(void)) dlsym(RTLD_NEXT, "GOMP_atomic_enter");

    orig_GOMP_atomic_enter();
}
void GOMP_atomic_exit() {
    pythia_event(PythiaGOMP_atomic_exit_event, 0, 0, 0);

    static void (*orig_GOMP_atomic_exit)(void) = 0;
    if (orig_GOMP_atomic_exit == 0)
        orig_GOMP_atomic_exit = (void(*)(void)) dlsym(RTLD_NEXT, "GOMP_atomic_exit");

    orig_GOMP_atomic_exit();
}
void GOMP_barrier() {
    pythia_event(PythiaGOMP_barrier_event, 0, 0, 0);

    static void (*orig_GOMP_barrier)(void) = 0;
    if (orig_GOMP_barrier == 0)
        orig_GOMP_barrier = (void(*)(void)) dlsym(RTLD_NEXT, "GOMP_barrier");

    orig_GOMP_barrier();
}
long GOMP_loop_static_next(long * _s0, long * _e0) {
    pythia_event(PythiaGOMP_loop_static_next_event, 0, 0, 0);

    static long (*orig_GOMP_loop_static_next)(long *, long *) = 0;
    if (orig_GOMP_loop_static_next == 0)
        orig_GOMP_loop_static_next = (long(*)(long *, long *)) dlsym(RTLD_NEXT, "GOMP_loop_static_next");

    long ret = orig_GOMP_loop_static_next(_s0, _e0);
    return ret;
}
void GOMP_loop_end_nowait() {
    pythia_event(PythiaGOMP_loop_end_nowait_event, 0, 0, 0);

    static void (*orig_GOMP_loop_end_nowait)(void) = 0;
    if (orig_GOMP_loop_end_nowait == 0)
        orig_GOMP_loop_end_nowait = (void(*)(void)) dlsym(RTLD_NEXT, "GOMP_loop_end_nowait");

    orig_GOMP_loop_end_nowait();
}
void GOMP_parallel_loop_static_start(void (*arg0)(void *), void * arg1, unsigned arg2, long arg3, long arg4, long arg5, long arg6) {
    pythia_event(PythiaGOMP_parallel_loop_static_start_event, 0, 0, 0);

    static void (*orig_GOMP_parallel_loop_static_start)(void (*)(void *), void *, unsigned, long, long, long, long) = 0;
    if (orig_GOMP_parallel_loop_static_start == 0)
        orig_GOMP_parallel_loop_static_start = (void(*)(void (*)(void *), void *, unsigned, long, long, long, long)) dlsym(RTLD_NEXT, "GOMP_parallel_loop_static_start");

    orig_GOMP_parallel_loop_static_start(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
}
void GOMP_parallel_loop_runtime_start(void (*arg0)(void *), void * arg1, unsigned arg2, long arg3, long arg4, long arg5, long arg6) {
    pythia_event(PythiaGOMP_parallel_loop_runtime_start_event, 0, 0, 0);

    static void (*orig_GOMP_parallel_loop_runtime_start)(void (*)(void *), void *, unsigned, long, long, long, long) = 0;
    if (orig_GOMP_parallel_loop_runtime_start == 0)
        orig_GOMP_parallel_loop_runtime_start = (void(*)(void (*)(void *), void *, unsigned, long, long, long, long)) dlsym(RTLD_NEXT, "GOMP_parallel_loop_runtime_start");

    orig_GOMP_parallel_loop_runtime_start(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
}
void GOMP_parallel_loop_dynamic_start(void (*arg0)(void *), void * arg1, unsigned arg2, long arg3, long arg4, long arg5, long arg6) {
    pythia_event(PythiaGOMP_parallel_loop_dynamic_start_event, 0, 0, 0);

    static void (*orig_GOMP_parallel_loop_dynamic_start)(void (*)(void *), void *, unsigned, long, long, long, long) = 0;
    if (orig_GOMP_parallel_loop_dynamic_start == 0)
        orig_GOMP_parallel_loop_dynamic_start = (void(*)(void (*)(void *), void *, unsigned, long, long, long, long)) dlsym(RTLD_NEXT, "GOMP_parallel_loop_dynamic_start");

    orig_GOMP_parallel_loop_dynamic_start(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
}
void GOMP_parallel_loop_guided_start(void (*arg0)(void *), void * arg1, unsigned arg2, long arg3, long arg4, long arg5, long arg6) {
    pythia_event(PythiaGOMP_parallel_loop_guided_start_event, 0, 0, 0);

    static void (*orig_GOMP_parallel_loop_guided_start)(void (*)(void *), void *, unsigned, long, long, long, long) = 0;
    if (orig_GOMP_parallel_loop_guided_start == 0)
        orig_GOMP_parallel_loop_guided_start = (void(*)(void (*)(void *), void *, unsigned, long, long, long, long)) dlsym(RTLD_NEXT, "GOMP_parallel_loop_guided_start");

    orig_GOMP_parallel_loop_guided_start(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
}
void GOMP_parallel_start(void (*fn)(void *), void * data, unsigned num_threads) {
    pythia_event(PythiaGOMP_parallel_start_event, 0, 0, 0);

    static void (*orig_GOMP_parallel_start)(void (*)(void *), void *, unsigned) = 0;
    if (orig_GOMP_parallel_start == 0)
        orig_GOMP_parallel_start = (void(*)(void (*)(void *), void *, unsigned)) dlsym(RTLD_NEXT, "GOMP_parallel_start");

    orig_GOMP_parallel_start(fn, data, num_threads);
}
void GOMP_parallel_end() {
    pythia_event(PythiaGOMP_parallel_end_event, 0, 0, 0);

    static void (*orig_GOMP_parallel_end)(void) = 0;
    if (orig_GOMP_parallel_end == 0)
        orig_GOMP_parallel_end = (void(*)(void)) dlsym(RTLD_NEXT, "GOMP_parallel_end");

    orig_GOMP_parallel_end();
}
void GOMP_critical_start() {
    pythia_event(PythiaGOMP_critical_start_event, 0, 0, 0);

    static void (*orig_GOMP_critical_start)(void) = 0;
    if (orig_GOMP_critical_start == 0)
        orig_GOMP_critical_start = (void(*)(void)) dlsym(RTLD_NEXT, "GOMP_critical_start");

    orig_GOMP_critical_start();
}
void GOMP_critical_end() {
    pythia_event(PythiaGOMP_critical_end_event, 0, 0, 0);

    static void (*orig_GOMP_critical_end)(void) = 0;
    if (orig_GOMP_critical_end == 0)
        orig_GOMP_critical_end = (void(*)(void)) dlsym(RTLD_NEXT, "GOMP_critical_end");

    orig_GOMP_critical_end();
}
void GOMP_parallel_loop_static(void (*arg0)(void *), void * arg1, unsigned arg2, long arg3, long arg4, long arg5, long arg6, unsigned arg7) {
    pythia_event(PythiaGOMP_parallel_loop_static_event, 0, 0, 0);

    static void (*orig_GOMP_parallel_loop_static)(void (*)(void *), void *, unsigned, long, long, long, long, unsigned) = 0;
    if (orig_GOMP_parallel_loop_static == 0)
        orig_GOMP_parallel_loop_static = (void(*)(void (*)(void *), void *, unsigned, long, long, long, long, unsigned)) dlsym(RTLD_NEXT, "GOMP_parallel_loop_static");

    orig_GOMP_parallel_loop_static(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}
void GOMP_parallel_loop_dynamic(void (*arg0)(void *), void * arg1, unsigned arg2, long arg3, long arg4, long arg5, long arg6, unsigned arg7) {
    pythia_event(PythiaGOMP_parallel_loop_dynamic_event, 0, 0, 0);

    static void (*orig_GOMP_parallel_loop_dynamic)(void (*)(void *), void *, unsigned, long, long, long, long, unsigned) = 0;
    if (orig_GOMP_parallel_loop_dynamic == 0)
        orig_GOMP_parallel_loop_dynamic = (void(*)(void (*)(void *), void *, unsigned, long, long, long, long, unsigned)) dlsym(RTLD_NEXT, "GOMP_parallel_loop_dynamic");

    orig_GOMP_parallel_loop_dynamic(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}
void GOMP_parallel_loop_guided(void (*arg0)(void *), void * arg1, unsigned arg2, long arg3, long arg4, long arg5, long arg6, unsigned arg7) {
    pythia_event(PythiaGOMP_parallel_loop_guided_event, 0, 0, 0);

    static void (*orig_GOMP_parallel_loop_guided)(void (*)(void *), void *, unsigned, long, long, long, long, unsigned) = 0;
    if (orig_GOMP_parallel_loop_guided == 0)
        orig_GOMP_parallel_loop_guided = (void(*)(void (*)(void *), void *, unsigned, long, long, long, long, unsigned)) dlsym(RTLD_NEXT, "GOMP_parallel_loop_guided");

    orig_GOMP_parallel_loop_guided(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}
void GOMP_parallel_loop_runtime(void (*arg0)(void *), void * arg1, unsigned arg2, long arg3, long arg4, long arg5, unsigned arg6) {
    pythia_event(PythiaGOMP_parallel_loop_runtime_event, 0, 0, 0);

    static void (*orig_GOMP_parallel_loop_runtime)(void (*)(void *), void *, unsigned, long, long, long, unsigned) = 0;
    if (orig_GOMP_parallel_loop_runtime == 0)
        orig_GOMP_parallel_loop_runtime = (void(*)(void (*)(void *), void *, unsigned, long, long, long, unsigned)) dlsym(RTLD_NEXT, "GOMP_parallel_loop_runtime");

    orig_GOMP_parallel_loop_runtime(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
}
long GOMP_loop_runtime_start(long arg0, long arg1, long arg2, long * arg3, long * arg4) {
    pythia_event(PythiaGOMP_loop_runtime_start_event, 0, 0, 0);

    static long (*orig_GOMP_loop_runtime_start)(long, long, long, long *, long *) = 0;
    if (orig_GOMP_loop_runtime_start == 0)
        orig_GOMP_loop_runtime_start = (long(*)(long, long, long, long *, long *)) dlsym(RTLD_NEXT, "GOMP_loop_runtime_start");

    long ret = orig_GOMP_loop_runtime_start(arg0, arg1, arg2, arg3, arg4);
    return ret;
}
long GOMP_loop_runtime_next(long * arg0, long * arg1) {
    pythia_event(PythiaGOMP_loop_runtime_next_event, 0, 0, 0);

    static long (*orig_GOMP_loop_runtime_next)(long *, long *) = 0;
    if (orig_GOMP_loop_runtime_next == 0)
        orig_GOMP_loop_runtime_next = (long(*)(long *, long *)) dlsym(RTLD_NEXT, "GOMP_loop_runtime_next");

    long ret = orig_GOMP_loop_runtime_next(arg0, arg1);
    return ret;
}
void GOMP_loop_end() {
    pythia_event(PythiaGOMP_loop_end_event, 0, 0, 0);

    static void (*orig_GOMP_loop_end)(void) = 0;
    if (orig_GOMP_loop_end == 0)
        orig_GOMP_loop_end = (void(*)(void)) dlsym(RTLD_NEXT, "GOMP_loop_end");

    orig_GOMP_loop_end();
}
void GOMP_ordered_start() {
    pythia_event(PythiaGOMP_ordered_start_event, 0, 0, 0);

    static void (*orig_GOMP_ordered_start)(void) = 0;
    if (orig_GOMP_ordered_start == 0)
        orig_GOMP_ordered_start = (void(*)(void)) dlsym(RTLD_NEXT, "GOMP_ordered_start");

    orig_GOMP_ordered_start();
}
void GOMP_ordered_end() {
    pythia_event(PythiaGOMP_ordered_end_event, 0, 0, 0);

    static void (*orig_GOMP_ordered_end)(void) = 0;
    if (orig_GOMP_ordered_end == 0)
        orig_GOMP_ordered_end = (void(*)(void)) dlsym(RTLD_NEXT, "GOMP_ordered_end");

    orig_GOMP_ordered_end();
}
long GOMP_sections_start(long arg0) {
    pythia_event(PythiaGOMP_sections_start_event, 0, 0, 0);

    static long (*orig_GOMP_sections_start)(long) = 0;
    if (orig_GOMP_sections_start == 0)
        orig_GOMP_sections_start = (long(*)(long)) dlsym(RTLD_NEXT, "GOMP_sections_start");

    long ret = orig_GOMP_sections_start(arg0);
    return ret;
}
long GOMP_sections_next() {
    pythia_event(PythiaGOMP_sections_next_event, 0, 0, 0);

    static long (*orig_GOMP_sections_next)(void) = 0;
    if (orig_GOMP_sections_next == 0)
        orig_GOMP_sections_next = (long(*)(void)) dlsym(RTLD_NEXT, "GOMP_sections_next");

    long ret = orig_GOMP_sections_next();
    return ret;
}
long GOMP_single_start() {
    pythia_event(PythiaGOMP_single_start_event, 0, 0, 0);

    static long (*orig_GOMP_single_start)(void) = 0;
    if (orig_GOMP_single_start == 0)
        orig_GOMP_single_start = (long(*)(void)) dlsym(RTLD_NEXT, "GOMP_single_start");

    long ret = orig_GOMP_single_start();
    return ret;
}
void* GOMP_single_copy_start() {
    pythia_event(PythiaGOMP_single_copy_start_event, 0, 0, 0);

    static void* (*orig_GOMP_single_copy_start)(void) = 0;
    if (orig_GOMP_single_copy_start == 0)
        orig_GOMP_single_copy_start = (void*(*)(void)) dlsym(RTLD_NEXT, "GOMP_single_copy_start");

    void* ret = orig_GOMP_single_copy_start();
    return ret;
}
void GOMP_single_copy_end(void* arg0) {
    pythia_event(PythiaGOMP_single_copy_end_event, 0, 0, 0);

    static void (*orig_GOMP_single_copy_end)(void*) = 0;
    if (orig_GOMP_single_copy_end == 0)
        orig_GOMP_single_copy_end = (void(*)(void*)) dlsym(RTLD_NEXT, "GOMP_single_copy_end");

    orig_GOMP_single_copy_end(arg0);
}
void GOMP_parallel() {
    pythia_event(PythiaGOMP_single_copy_end_event_parallel_event);

    static void (*orig_GOMP_parallel)(void) = 0;
    if (orig_GOMP_parallel == 0)
        orig_GOMP_parallel = (void(*)(void)) dlsym(RTLD_NEXT, "GOMP_parallel");

    orig_GOMP_parallel();
}

static void init() __attribute__((constructor));
static void init() {
    printf("Init module omp\n");
}

// static void deinit() __attribute__((destructor));
// static void deinit() {
//     printf("Deinit module $(m.name)\n");
// }
