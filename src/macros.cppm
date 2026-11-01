// mcpplibs.mwrap.mimalloc.macros --- the macros of mimalloc's headers that are
// values (a named module cannot export a macro), under their original names in
// mcpplibs::mwrap::mimalloc::macros, each `inline constexpr' and equal to the
// macro where the module is built:
//
//   MI_MALLOC_VERSION                major, two digits of minor, two of patch
//   MI_SMALL_WSIZE_MAX, MI_SMALL_SIZE_MAX   the largest "small" allocation,
//                                    in words and in bytes
//   MI_STAT_VERSION, MI_BIN_HUGE     the statistics structure's version and
//                                    its last size bin (<mimalloc-stats.h>)
//   MI_PROFILE_SAMPLE_DATA_MAX_SIZE  the largest profiler sample data
//                                    (<mimalloc-profile.h>)
//   MI_HAS_HEAP_STL_ALLOCATOR        the heap STL allocators are declared
//
// The function-like macros that take a type (mi_malloc_tp, mi_heap_calloc_tp
// …) cannot be functions with the same call syntax: they stay macros, in
// <mwrap/mimalloc/macros.hpp>. tools/check_exports.py accounts for every macro.
module;
#include <stddef.h>
#include <mimalloc.h>
#include <mimalloc-stats.h>
#include <mimalloc-profile.h>

// The values, taken under other names while the macros are defined; then the
// macros are undefined, so that the names below are declared rather than
// expanded.
namespace mwrap_mimalloc_capture {
inline constexpr int value_MI_MALLOC_VERSION = MI_MALLOC_VERSION;
inline constexpr size_t value_MI_SMALL_WSIZE_MAX = MI_SMALL_WSIZE_MAX;
inline constexpr size_t value_MI_SMALL_SIZE_MAX = MI_SMALL_SIZE_MAX;
inline constexpr int value_MI_STAT_VERSION = MI_STAT_VERSION;
inline constexpr unsigned value_MI_BIN_HUGE = MI_BIN_HUGE;
inline constexpr size_t value_MI_PROFILE_SAMPLE_DATA_MAX_SIZE = MI_PROFILE_SAMPLE_DATA_MAX_SIZE;
inline constexpr bool value_MI_HAS_HEAP_STL_ALLOCATOR = (MI_HAS_HEAP_STL_ALLOCATOR) != 0;
}
#undef MI_MALLOC_VERSION
#undef MI_SMALL_WSIZE_MAX
#undef MI_SMALL_SIZE_MAX
#undef MI_STAT_VERSION
#undef MI_BIN_HUGE
#undef MI_PROFILE_SAMPLE_DATA_MAX_SIZE
#undef MI_HAS_HEAP_STL_ALLOCATOR

export module mcpplibs.mwrap.mimalloc.macros;

export namespace mcpplibs::mwrap::mimalloc::macros {
inline constexpr int MI_MALLOC_VERSION = mwrap_mimalloc_capture::value_MI_MALLOC_VERSION;
inline constexpr size_t MI_SMALL_WSIZE_MAX = mwrap_mimalloc_capture::value_MI_SMALL_WSIZE_MAX;
inline constexpr size_t MI_SMALL_SIZE_MAX = mwrap_mimalloc_capture::value_MI_SMALL_SIZE_MAX;
inline constexpr int MI_STAT_VERSION = mwrap_mimalloc_capture::value_MI_STAT_VERSION;
inline constexpr unsigned MI_BIN_HUGE = mwrap_mimalloc_capture::value_MI_BIN_HUGE;
inline constexpr size_t MI_PROFILE_SAMPLE_DATA_MAX_SIZE = mwrap_mimalloc_capture::value_MI_PROFILE_SAMPLE_DATA_MAX_SIZE;
inline constexpr bool MI_HAS_HEAP_STL_ALLOCATOR = mwrap_mimalloc_capture::value_MI_HAS_HEAP_STL_ALLOCATOR;
}
