// mcpplibs.mwrap.mimalloc --- mimalloc 3.6.1, Microsoft's general-purpose
// allocator, as a C++ module. Every exported name is the upstream entity of
// <mimalloc.h>, unchanged, in the global namespace where upstream declares it:
// the `mi_*' functions, the heap and arena types, the callback types, the
// option enumeration and its enumerators, and the STL allocators of C++. The
// root also re-exports the statistics (<mimalloc-stats.h>), the profiler
// (<mimalloc-profile.h>) and the macro mappings. The implementation is
// compat.mimalloc 3.6.1; tools/check_exports.py audits these lists against the
// headers.
module;
#include <mimalloc.h>

export module mcpplibs.mwrap.mimalloc;

export import mcpplibs.mwrap.mimalloc.stats;
export import mcpplibs.mwrap.mimalloc.profile;
export import mcpplibs.mwrap.mimalloc.macros;

// The functions of <mimalloc.h>.
export {
using ::mi_malloc; using ::mi_calloc; using ::mi_realloc; using ::mi_expand;
using ::mi_free; using ::mi_strdup; using ::mi_strndup; using ::mi_realpath;
using ::mi_malloc_small; using ::mi_zalloc_small; using ::mi_zalloc; using ::mi_mallocn;
using ::mi_reallocn; using ::mi_reallocf; using ::mi_usable_size; using ::mi_good_size;
using ::mi_free_size; using ::mi_free_small; using ::mi_free_small_nonnull; using ::mi_free_size_aligned;
using ::mi_free_aligned; using ::mi_cfree; using ::mi_malloc_aligned; using ::mi_malloc_aligned_at;
using ::mi_zalloc_aligned; using ::mi_zalloc_aligned_at; using ::mi_calloc_aligned; using ::mi_calloc_aligned_at;
using ::mi_realloc_aligned; using ::mi_realloc_aligned_at; using ::mi_register_deferred_free; using ::mi_register_output;
using ::mi_register_error; using ::mi_collect; using ::mi_version; using ::mi_options_print;
using ::mi_process_info_print; using ::mi_options_print_out; using ::mi_process_info_print_out; using ::mi_process_info;
using ::mi_process_init; using ::mi_process_done; using ::mi_thread_init; using ::mi_thread_done;
using ::mi_thread_set_in_threadpool; using ::mi_umalloc; using ::mi_ucalloc; using ::mi_urealloc;
using ::mi_ufree; using ::mi_umalloc_aligned; using ::mi_uzalloc_aligned; using ::mi_umalloc_small;
using ::mi_uzalloc_small; using ::mi_heap_new; using ::mi_heap_delete; using ::mi_heap_destroy;
using ::mi_heap_set_numa_affinity; using ::mi_heap_set_debug_fill_preserve; using ::mi_heap_collect; using ::mi_heap_main;
using ::mi_heap_of; using ::mi_heap_contains; using ::mi_any_heap_contains; using ::mi_heap_malloc;
using ::mi_heap_zalloc; using ::mi_heap_calloc; using ::mi_heap_mallocn; using ::mi_heap_malloc_small;
using ::mi_heap_zalloc_small; using ::mi_heap_realloc; using ::mi_heap_reallocn; using ::mi_heap_reallocf;
using ::mi_heap_strdup; using ::mi_heap_strndup; using ::mi_heap_realpath; using ::mi_heap_malloc_aligned;
using ::mi_heap_malloc_aligned_at; using ::mi_heap_zalloc_aligned; using ::mi_heap_zalloc_aligned_at; using ::mi_heap_calloc_aligned;
using ::mi_heap_calloc_aligned_at; using ::mi_heap_realloc_aligned; using ::mi_heap_realloc_aligned_at; using ::mi_rezalloc;
using ::mi_recalloc; using ::mi_rezalloc_aligned; using ::mi_rezalloc_aligned_at; using ::mi_recalloc_aligned;
using ::mi_recalloc_aligned_at; using ::mi_heap_rezalloc; using ::mi_heap_recalloc; using ::mi_heap_rezalloc_aligned;
using ::mi_heap_rezalloc_aligned_at; using ::mi_heap_recalloc_aligned; using ::mi_heap_recalloc_aligned_at; using ::mi_heap_visit_blocks;
using ::mi_heap_visit_abandoned_blocks; using ::mi_is_redirected; using ::mi_reserve_huge_os_pages_interleave; using ::mi_reserve_huge_os_pages_at;
using ::mi_reserve_os_memory; using ::mi_manage_os_memory; using ::mi_debug_show_arenas; using ::mi_arenas_print;
using ::mi_arenas_purge; using ::mi_arena_min_alignment; using ::mi_arena_min_size; using ::mi_arena_max_object_size;
using ::mi_arena_area; using ::mi_reserve_huge_os_pages_at_ex; using ::mi_reserve_os_memory_ex; using ::mi_manage_os_memory_ex;
using ::mi_arena_contains; using ::mi_heap_new_in_arena; using ::mi_subproc_main; using ::mi_subproc_current;
using ::mi_subproc_new; using ::mi_subproc_destroy; using ::mi_subproc_add_current_thread; using ::mi_subproc_visit_heaps;
using ::mi_heap_theap; using ::mi_theap_set_default; using ::mi_theap_get_default; using ::mi_theap_collect;
using ::mi_theap_malloc; using ::mi_theap_zalloc; using ::mi_theap_calloc; using ::mi_theap_malloc_small;
using ::mi_theap_zalloc_small; using ::mi_theap_malloc_aligned; using ::mi_theap_zalloc_aligned; using ::mi_theap_realloc;
using ::mi_theap_rezalloc; using ::mi_theap_guarded_set_sample_rate; using ::mi_theap_guarded_set_size_bound; using ::mi_manage_memory;
using ::mi_unsafe_heap_page_is_under_utilized; using ::mi_theap_delete; using ::mi_theap_quiescent_abandon; using ::mi_thread_id_of;
using ::mi_check_owned; using ::mi_thread_stats_print_out; using ::mi_is_in_heap_region; using ::mi_theap_visit_blocks;
using ::mi_reserve_huge_os_pages; using ::mi_collect_reduce; using ::mi_stats_reset; using ::mi_stats_merge;
using ::mi_stats_print; using ::mi_stats_print_out; using ::mi_option_is_enabled; using ::mi_option_enable;
using ::mi_option_disable; using ::mi_option_set_enabled; using ::mi_option_set_enabled_default; using ::mi_option_get;
using ::mi_option_get_clamp; using ::mi_option_get_size; using ::mi_option_set; using ::mi_option_set_default;
using ::mi_malloc_size; using ::mi_malloc_good_size; using ::mi_malloc_usable_size; using ::mi_posix_memalign;
using ::mi_memalign; using ::mi_valloc; using ::mi_pvalloc; using ::mi_reallocarray;
using ::mi_reallocarr; using ::mi_aligned_recalloc; using ::mi_aligned_offset_recalloc; using ::mi_aligned_alloc;
using ::mi_free_aligned_sized; using ::mi_free_sized; using ::mi__expand; using ::mi_dupenv_s;
using ::mi_wdupenv_s; using ::mi_wcsdup; using ::mi_mbsdup; using ::mi_new;
using ::mi_new_aligned; using ::mi_new_nothrow; using ::mi_new_aligned_nothrow; using ::mi_new_n;
using ::mi_new_realloc; using ::mi_new_reallocn; using ::mi_heap_alloc_new; using ::mi_heap_alloc_new_n;
using ::mi_theap_alloc_new; using ::mi_theap_alloc_new_n; using ::mi_theap_alloc_new_nothrow; using ::mi_free_small_local;
using ::mi_free_small_local_nonnull;
}

// Declared without upstream's export attribute, and extern all the same.
export {
using ::mi_wzalloc_small; using ::mi_wmalloc_small; using ::mi_theap_wmalloc_small; using ::mi_theap_wzalloc_small;
}

// UPSTREAM'S `static inline' FUNCTIONS, adapted. A function with internal
// linkage is local to a translation unit and cannot be exported, so each is
// declared here under its own name in mcpplibs::mwrap::mimalloc and calls
// upstream's body (below). <mwrap/mimalloc/macros.hpp> spells the typed
// macros with these names.
export namespace mcpplibs::mwrap::mimalloc {
size_t mi_wsize_from_size(size_t size) noexcept;
void* mi_malloc_csize(size_t size) noexcept;
void* mi_zalloc_csize(size_t size) noexcept;
void* mi_theap_malloc_csize(mi_theap_t* theap, size_t size) noexcept;
void* mi_theap_zalloc_csize(mi_theap_t* theap, size_t size) noexcept;
void mi_free_csize(void* p, size_t size) noexcept;
void mi_free_csize_nonnull(void* p, size_t size) noexcept;
void mi_free_csize_aligned(void* p, size_t size, size_t aligned) noexcept;
void mi_free_csize_aligned_nonnull(void* p, size_t size, size_t aligned) noexcept;
}

// Its types.
export {
using ::mi_heap_t; using ::mi_heap_s; using ::mi_heap_area_t; using ::mi_heap_area_s;
using ::mi_theap_t; using ::mi_theap_s; using ::mi_arena_id_t;
using ::mi_subproc_id_t; using ::mi_option_t; using ::mi_option_e;
using ::mi_deferred_free_fun; using ::mi_output_fun; using ::mi_error_fun;
using ::mi_block_visit_fun; using ::mi_heap_visit_fun; using ::mi_commit_fun_t;
}

// The options, mi_option_t's enumerators (deprecated spellings included, as
// upstream keeps them).
export {
using ::mi_option_show_errors; using ::mi_option_show_stats; using ::mi_option_verbose;
using ::mi_option_deprecated_eager_commit; using ::mi_option_arena_eager_commit; using ::mi_option_purge_decommits;
using ::mi_option_allow_large_os_pages; using ::mi_option_reserve_huge_os_pages; using ::mi_option_reserve_huge_os_pages_at;
using ::mi_option_reserve_os_memory; using ::mi_option_deprecated_segment_cache; using ::mi_option_deprecated_page_reset;
using ::mi_option_deprecated_abandoned_page_purge; using ::mi_option_deprecated_segment_reset; using ::mi_option_deprecated_eager_commit_delay;
using ::mi_option_purge_delay; using ::mi_option_use_numa_nodes; using ::mi_option_disallow_os_alloc;
using ::mi_option_os_tag; using ::mi_option_max_errors; using ::mi_option_max_warnings;
using ::mi_option_deprecated_max_segment_reclaim; using ::mi_option_destroy_on_exit; using ::mi_option_arena_reserve;
using ::mi_option_arena_purge_mult; using ::mi_option_deprecated_purge_extend_delay; using ::mi_option_disallow_arena_alloc;
using ::mi_option_retry_on_oom; using ::mi_option_deprecated_visit_abandoned; using ::mi_option_guarded_min;
using ::mi_option_guarded_max; using ::mi_option_unsafe_guarded_precise; using ::mi_option_guarded_sample_rate;
using ::mi_option_guarded_sample_seed; using ::mi_option_generic_collect; using ::mi_option_page_reclaim_on_free;
using ::mi_option_page_full_retain; using ::mi_option_page_max_candidates; using ::mi_option_max_vabits;
using ::mi_option_pagemap_commit; using ::mi_option_page_commit_on_demand; using ::mi_option_page_max_reclaim;
using ::mi_option_page_cross_thread_max_reclaim; using ::mi_option_allow_thp; using ::mi_option_arena_purge_min_size;
using ::mi_option_arena_max_object_size; using ::mi_option_arena_is_numa_local; using ::mi_option_stats_merge_on_collect;
using ::mi_option_profile_alloc_interval; using ::mi_option_profile_inuse_interval; using ::mi_option_profile_time_interval;
using ::mi_option_profile_sample_rate; using ::mi_option_stats_merge_threshold; using ::mi_option_arena_purge_immediate_size;
using ::_mi_option_last; using ::mi_option_large_os_pages; using ::mi_option_eager_region_commit;
using ::mi_option_reset_decommits; using ::mi_option_reset_delay; using ::mi_option_limit_os_alloc;
using ::mi_option_minimal_purge_size;
}

// The allocators of C++ (upstream's MI_HAS_HEAP_STL_ALLOCATOR), with their
// comparisons.
export {
using ::mi_stl_allocator;
using ::mi_heap_stl_allocator;
using ::mi_heap_destroy_stl_allocator;
using ::operator==;
using ::operator!=;
}

namespace mcpplibs::mwrap::mimalloc {
size_t mi_wsize_from_size(size_t size) noexcept { return ::mi_wsize_from_size(size); }
void* mi_malloc_csize(size_t size) noexcept { return ::mi_malloc_csize(size); }
void* mi_zalloc_csize(size_t size) noexcept { return ::mi_zalloc_csize(size); }
void* mi_theap_malloc_csize(mi_theap_t* theap, size_t size) noexcept { return ::mi_theap_malloc_csize(theap, size); }
void* mi_theap_zalloc_csize(mi_theap_t* theap, size_t size) noexcept { return ::mi_theap_zalloc_csize(theap, size); }
void mi_free_csize(void* p, size_t size) noexcept { ::mi_free_csize(p, size); }
void mi_free_csize_nonnull(void* p, size_t size) noexcept { ::mi_free_csize_nonnull(p, size); }
void mi_free_csize_aligned(void* p, size_t size, size_t aligned) noexcept { ::mi_free_csize_aligned(p, size, aligned); }
void mi_free_csize_aligned_nonnull(void* p, size_t size, size_t aligned) noexcept { ::mi_free_csize_aligned_nonnull(p, size, aligned); }
}

