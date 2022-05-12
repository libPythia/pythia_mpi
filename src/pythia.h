#pragma once

#ifdef __cplusplus
extern "C" {
#endif

void pythia_init(int world_rank);
void pythia_deinit(void);

#define AUX(x) Pythia##x
enum Pythia_MPI_fn {
    AUX(Allgather),
    AUX(Allgatherv),
    AUX(Allreduce),
    AUX(Alltoall),
    AUX(Alltoallv),
    AUX(Barrier),
    AUX(Bcast),
    AUX(Bsend),
    AUX(Gather),
    AUX(Gatherv),
    AUX(Get),
    AUX(Iallgather ),
    AUX(Iallgatherv),
    AUX(Iallreduce),
    AUX(Ialltoall),
    AUX(Ialltoallv),
    AUX(Ibarrier),
    AUX(Ibcast),
    AUX(Ibsend),
    AUX(Igather),
    AUX(Igatherv),
    AUX(Irecv),
    AUX(Ireduce),
    AUX(Ireduce_scatter),
    AUX(Irsend),
    AUX(Iscan),
    AUX(Iscatter),
    AUX(Iscatterv),
    AUX(Isend),
    AUX(Issend),
    AUX(Probe),
    AUX(Put),
    AUX(Recv),
    AUX(Reduce),
    AUX(Reduce_scatter),
    AUX(Rsend),
    AUX(Scan),
    AUX(Scatter),
    AUX(Scatterv),
    AUX(Send),
    AUX(Sendrecv),
    AUX(Sendrecv_replace),
    AUX(Ssend),
    AUX(Startall),
    AUX(Start),
    AUX(Testall),
    AUX(Testany),
    AUX(Test),
    AUX(Testsome),
    AUX(Waitall),
    AUX(Waitany),
    AUX(Wait),
    AUX(Waitsome),
    COUNT,
};
#undef AUX

void pythia_event(enum Pythia_MPI_fn fn, int arg1, int arg2, int arg3);

#ifdef __cplusplus
}
#endif
