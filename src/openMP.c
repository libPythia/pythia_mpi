#define _GNU_SOURCE
#include <assert.h>
#include <dlfcn.h>
#include <stddef.h>

#include "pythia.h"

// Includes

// Extra definitions

// Pointers on intercepted fonctions
void GOMP_atomic_enter() {
    pythia_event(PythiaGOMP_atomic_enter, 0, 0, 0);

    static void (*orig_GOMP_atomic_enter)(void) = 0;
    if (orig_GOMP_atomic_enter == 0)
        orig_GOMP_atomic_enter = (void(*)(void)) dlsym(RTLD_NEXT, "GOMP_atomic_enter");

    orig_GOMP_atomic_enter();
}
void GOMP_atomic_exit() {
    pythia_event(PythiaGOMP_atomic_exit, 0, 0, 0);

    static void (*orig_GOMP_atomic_exit)(void) = 0;
    if (orig_GOMP_atomic_exit == 0)
        orig_GOMP_atomic_exit = (void(*)(void)) dlsym(RTLD_NEXT, "GOMP_atomic_exit");

    orig_GOMP_atomic_exit();
}
void GOMP_barrier() {
    pythia_event(PythiaGOMP_barrier, 0, 0, 0);

    static void (*orig_GOMP_barrier)(void) = 0;
    if (orig_GOMP_barrier == 0)
        orig_GOMP_barrier = (void(*)(void)) dlsym(RTLD_NEXT, "GOMP_barrier");

    orig_GOMP_barrier();
}
void GOMP_parallel_start(void (*fn)(void *), void * data, unsigned num_threads) {
    pythia_event(PythiaGOMP_parallel_start, 0, 0, 0);

    static void (*orig_GOMP_parallel_start)(void (*)(void *), void *, unsigned) = 0;
    if (orig_GOMP_parallel_start == 0)
        orig_GOMP_parallel_start = (void(*)(void (*)(void *), void *, unsigned)) dlsym(RTLD_NEXT, "GOMP_parallel_start");

    orig_GOMP_parallel_start(fn, data, num_threads);
}
void GOMP_parallel_end() {
    pythia_event(PythiaGOMP_parallel_end, 0, 0, 0);

    static void (*orig_GOMP_parallel_end)(void) = 0;
    if (orig_GOMP_parallel_end == 0)
        orig_GOMP_parallel_end = (void(*)(void)) dlsym(RTLD_NEXT, "GOMP_parallel_end");

    orig_GOMP_parallel_end();
}
void GOMP_critical_start() {
    pythia_event(PythiaGOMP_critical_start, 0, 0, 0);

    static void (*orig_GOMP_critical_start)(void) = 0;
    if (orig_GOMP_critical_start == 0)
        orig_GOMP_critical_start = (void(*)(void)) dlsym(RTLD_NEXT, "GOMP_critical_start");

    orig_GOMP_critical_start();
}
void GOMP_critical_end() {
    pythia_event(PythiaGOMP_critical_end, 0, 0, 0);

    static void (*orig_GOMP_critical_end)(void) = 0;
    if (orig_GOMP_critical_end == 0)
        orig_GOMP_critical_end = (void(*)(void)) dlsym(RTLD_NEXT, "GOMP_critical_end");

    orig_GOMP_critical_end();
}
void GOMP_parallel_loop_static(void (*arg0)(void *), void * arg1, unsigned arg2, long arg3, long arg4, long arg5, long arg6, unsigned arg7) {
    pythia_event(PythiaGOMP_parallel_loop_static, 0, 0, 0);

    static void (*orig_GOMP_parallel_loop_static)(void (*)(void *), void *, unsigned, long, long, long, long, unsigned) = 0;
    if (orig_GOMP_parallel_loop_static == 0)
        orig_GOMP_parallel_loop_static = (void(*)(void (*)(void *), void *, unsigned, long, long, long, long, unsigned)) dlsym(RTLD_NEXT, "GOMP_parallel_loop_static");

    orig_GOMP_parallel_loop_static(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}
void GOMP_parallel_loop_dynamic(void (*arg0)(void *), void * arg1, unsigned arg2, long arg3, long arg4, long arg5, long arg6, unsigned arg7) {
    pythia_event(PythiaGOMP_parallel_loop_dynamic, 0, 0, 0);

    static void (*orig_GOMP_parallel_loop_dynamic)(void (*)(void *), void *, unsigned, long, long, long, long, unsigned) = 0;
    if (orig_GOMP_parallel_loop_dynamic == 0)
        orig_GOMP_parallel_loop_dynamic = (void(*)(void (*)(void *), void *, unsigned, long, long, long, long, unsigned)) dlsym(RTLD_NEXT, "GOMP_parallel_loop_dynamic");

    orig_GOMP_parallel_loop_dynamic(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}
void GOMP_parallel_loop_guided(void (*arg0)(void *), void * arg1, unsigned arg2, long arg3, long arg4, long arg5, long arg6, unsigned arg7) {
    pythia_event(PythiaGOMP_parallel_loop_guided, 0, 0, 0);

    static void (*orig_GOMP_parallel_loop_guided)(void (*)(void *), void *, unsigned, long, long, long, long, unsigned) = 0;
    if (orig_GOMP_parallel_loop_guided == 0)
        orig_GOMP_parallel_loop_guided = (void(*)(void (*)(void *), void *, unsigned, long, long, long, long, unsigned)) dlsym(RTLD_NEXT, "GOMP_parallel_loop_guided");

    orig_GOMP_parallel_loop_guided(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}
void GOMP_parallel_loop_runtime(void (*arg0)(void *), void * arg1, unsigned arg2, long arg3, long arg4, long arg5, unsigned arg6) {
    pythia_event(PythiaGOMP_parallel_loop_runtime, 0, 0, 0);

    static void (*orig_GOMP_parallel_loop_runtime)(void (*)(void *), void *, unsigned, long, long, long, unsigned) = 0;
    if (orig_GOMP_parallel_loop_runtime == 0)
        orig_GOMP_parallel_loop_runtime = (void(*)(void (*)(void *), void *, unsigned, long, long, long, unsigned)) dlsym(RTLD_NEXT, "GOMP_parallel_loop_runtime");

    orig_GOMP_parallel_loop_runtime(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
}
long GOMP_loop_runtime_start(long arg0, long arg1, long arg2, long * arg3, long * arg4) {
    pythia_event(PythiaGOMP_loop_runtime_start, 0, 0, 0);

    static long (*orig_GOMP_loop_runtime_start)(long, long, long, long *, long *) = 0;
    if (orig_GOMP_loop_runtime_start == 0)
        orig_GOMP_loop_runtime_start = (long(*)(long, long, long, long *, long *)) dlsym(RTLD_NEXT, "GOMP_loop_runtime_start");

    long ret = orig_GOMP_loop_runtime_start(arg0, arg1, arg2, arg3, arg4);
    return ret;
}
long GOMP_loop_runtime_next(long * arg0, long * arg1) {
    pythia_event(PythiaGOMP_loop_runtime_next, 0, 0, 0);

    static long (*orig_GOMP_loop_runtime_next)(long *, long *) = 0;
    if (orig_GOMP_loop_runtime_next == 0)
        orig_GOMP_loop_runtime_next = (long(*)(long *, long *)) dlsym(RTLD_NEXT, "GOMP_loop_runtime_next");

    long ret = orig_GOMP_loop_runtime_next(arg0, arg1);
    return ret;
}
void GOMP_loop_end() {
    pythia_event(PythiaGOMP_loop_end, 0, 0, 0);

    static void (*orig_GOMP_loop_end)(void) = 0;
    if (orig_GOMP_loop_end == 0)
        orig_GOMP_loop_end = (void(*)(void)) dlsym(RTLD_NEXT, "GOMP_loop_end");

    orig_GOMP_loop_end();
}
void GOMP_ordered_start() {
    pythia_event(PythiaGOMP_ordered_start, 0, 0, 0);

    static void (*orig_GOMP_ordered_start)(void) = 0;
    if (orig_GOMP_ordered_start == 0)
        orig_GOMP_ordered_start = (void(*)(void)) dlsym(RTLD_NEXT, "GOMP_ordered_start");

    orig_GOMP_ordered_start();
}
void GOMP_ordered_end() {
    pythia_event(PythiaGOMP_ordered_end, 0, 0, 0);

    static void (*orig_GOMP_ordered_end)(void) = 0;
    if (orig_GOMP_ordered_end == 0)
        orig_GOMP_ordered_end = (void(*)(void)) dlsym(RTLD_NEXT, "GOMP_ordered_end");

    orig_GOMP_ordered_end();
}
long GOMP_sections_start(long arg0) {
    pythia_event(PythiaGOMP_sections_start, 0, 0, 0);

    static long (*orig_GOMP_sections_start)(long) = 0;
    if (orig_GOMP_sections_start == 0)
        orig_GOMP_sections_start = (long(*)(long)) dlsym(RTLD_NEXT, "GOMP_sections_start");

    long ret = orig_GOMP_sections_start(arg0);
    return ret;
}
long GOMP_sections_next() {
    pythia_event(PythiaGOMP_sections_next, 0, 0, 0);

    static long (*orig_GOMP_sections_next)(void) = 0;
    if (orig_GOMP_sections_next == 0)
        orig_GOMP_sections_next = (long(*)(void)) dlsym(RTLD_NEXT, "GOMP_sections_next");

    long ret = orig_GOMP_sections_next();
    return ret;
}
long GOMP_single_start() {
    pythia_event(PythiaGOMP_single_start, 0, 0, 0);

    static long (*orig_GOMP_single_start)(void) = 0;
    if (orig_GOMP_single_start == 0)
        orig_GOMP_single_start = (long(*)(void)) dlsym(RTLD_NEXT, "GOMP_single_start");

    long ret = orig_GOMP_single_start();
    return ret;
}
void* GOMP_single_copy_start() {
    pythia_event(PythiaGOMP_single_copy_start, 0, 0, 0);

    static void* (*orig_GOMP_single_copy_start)(void) = 0;
    if (orig_GOMP_single_copy_start == 0)
        orig_GOMP_single_copy_start = (void*(*)(void)) dlsym(RTLD_NEXT, "GOMP_single_copy_start");

    void* ret = orig_GOMP_single_copy_start();
    return ret;
}
void GOMP_single_copy_end(void* arg0) {
    pythia_event(PythiaGOMP_single_copy_end, 0, 0, 0);

    static void (*orig_GOMP_single_copy_end)(void*) = 0;
    if (orig_GOMP_single_copy_end == 0)
        orig_GOMP_single_copy_end = (void(*)(void*)) dlsym(RTLD_NEXT, "GOMP_single_copy_end");

    orig_GOMP_single_copy_end(arg0);
}
void GOMP_parallel() {
    pythia_event(PythiaGOMP_parallel, 0, 0, 0);

    static void (*orig_GOMP_parallel)(void) = 0;
    if (orig_GOMP_parallel == 0)
        orig_GOMP_parallel = (void(*)(void)) dlsym(RTLD_NEXT, "GOMP_parallel");

    orig_GOMP_parallel();
}
