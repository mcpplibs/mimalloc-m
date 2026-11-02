// mcpplibs.mwrap.mimalloc.profile --- <mimalloc-profile.h>: sampling
// profilers of a heap, a subprocess or the process, and upstream's pprof
// writer. The upstream names, unchanged.
module;
#include <mimalloc.h>
#include <mimalloc-profile.h>

export module mcpplibs.mwrap.mimalloc.profile;

export {
using ::mi_heap_profile; using ::mi_heap_profile_disable; using ::mi_subproc_profile; using ::mi_profile;
using ::mi_profiler_start; using ::mi_profiler_stop; using ::mi_profiler_snapshot; using ::mi_pprof_profiler_new;
using ::mi_pprof_profiler_delete;
using ::mi_profiler_t; using ::mi_profiler_s; using ::mi_profiler_sample_data_t; using ::mi_profiler_sample_data_s;
using ::mi_profiler_on_alloc_fun; using ::mi_profiler_on_realloc_inplace_fun;
using ::mi_profiler_on_free_fun; using ::mi_profiler_on_snapshot_fun;
}
