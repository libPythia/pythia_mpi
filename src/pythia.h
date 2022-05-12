#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void pythia_init(int world_rank);
void pythia_deinit(void);

#define AUX(x, y) Pythia##x,
enum Pythia_MPI_fn {
#include "pythia_fn.inl"
    COUNT
};
#undef AUX

void pythia_event(enum Pythia_MPI_fn fn, int arg1, int arg2, int arg3);

#ifdef __cplusplus
}
#endif
