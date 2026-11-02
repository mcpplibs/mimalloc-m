// mcpplibs.mwrap.mimalloc.stats --- <mimalloc-stats.h>: a heap's, a
// subprocess's and the process's statistics as a structure, as JSON and as
// text. The upstream names, unchanged; the two `static inline' initialisers
// adapted in mcpplibs::mwrap::mimalloc, and `mi_stats_t_decl(name)' kept in
// <mwrap/mimalloc/macros.hpp>.
module;
#include <mimalloc.h>
#include <mimalloc-stats.h>

export module mcpplibs.mwrap.mimalloc.stats;

export {
using ::mi_heap_stats_get; using ::mi_heap_stats_get_json; using ::mi_heap_stats_print_out; using ::mi_subproc_stats_get;
using ::mi_subproc_stats_get_json; using ::mi_subproc_stats_print_out; using ::mi_subproc_heap_stats_print_out; using ::mi_stats_get;
using ::mi_stats_get_json; using ::mi_heap_stats_merge_to_subproc; using ::mi_subproc_stats_get_exclusive; using ::mi_stats_as_json;
using ::mi_stats_get_bin_size; using ::mi_theap_stats_get; using ::mi_theap_stats_merge_to_heap;
using ::mi_stats_t; using ::mi_stats_s; using ::mi_stat_count_t; using ::mi_stat_count_s;
using ::mi_stat_counter_t; using ::mi_stat_counter_s; using ::mi_chunkbin_t; using ::mi_chunkbin_e;
using ::MI_CBIN_SMALL; using ::MI_CBIN_OTHER; using ::MI_CBIN_MEDIUM; using ::MI_CBIN_LARGE;
using ::MI_CBIN_HUGE; using ::MI_CBIN_NONE; using ::MI_CBIN_COUNT;
}

// Upstream's `static inline' helpers of <mimalloc-stats.h>, adapted under
// their names (a function local to a translation unit cannot be exported).
export namespace mcpplibs::mwrap::mimalloc {
void mi_stats_header_init(mi_stats_t* stats) noexcept;
void mi_stats_init(mi_stats_t* stats) noexcept;
}

namespace mcpplibs::mwrap::mimalloc {
void mi_stats_header_init(mi_stats_t* stats) noexcept { ::mi_stats_header_init(stats); }
void mi_stats_init(mi_stats_t* stats) noexcept { ::mi_stats_init(stats); }
}

