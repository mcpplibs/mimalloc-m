# Usage and API

`mcpplibs.mwrap.mimalloc` 3.6.1 exports mimalloc's public API, upstream's names
unchanged. This page lists what each module holds and the places where a module
and a header differ.

## Modules

| Module | Holds |
|---|---|
| `mcpplibs.mwrap.mimalloc` | the functions of `<mimalloc.h>` (allocation, aligned allocation, heaps, arenas, sub-processes, options, process and thread control, the POSIX and C++ `new` forms); `mi_heap_t`, `mi_heap_area_t`, `mi_theap_t`, `mi_arena_id_t`, `mi_subproc_id_t`, the callback types, `mi_option_t` and its enumerators; `mi_stl_allocator`, `mi_heap_stl_allocator` and `mi_heap_destroy_stl_allocator` with their comparisons; re-exports the three below |
| `mcpplibs.mwrap.mimalloc.stats` | `<mimalloc-stats.h>`: `mi_stats_get`, `mi_heap_stats_get`, `mi_subproc_stats_get` and their JSON and text forms; `mi_stats_t` and its counters; `mi_chunkbin_t` |
| `mcpplibs.mwrap.mimalloc.profile` | `<mimalloc-profile.h>`: `mi_profiler_t` and its callbacks, `mi_heap_profile`, `mi_profile`, `mi_profiler_start` / `stop` / `snapshot`, `mi_pprof_profiler_new` / `delete` |
| `mcpplibs.mwrap.mimalloc.macros` | the value macros as constants in `mcpplibs::mwrap::mimalloc::macros` |

## What a module cannot export, and what stands in for it

- **`static inline` functions.** `<mimalloc.h>` defines nine (`mi_wsize_from_size`,
  `mi_malloc_csize`, `mi_zalloc_csize`, `mi_theap_malloc_csize`,
  `mi_theap_zalloc_csize`, `mi_free_csize` and its three variants), and
  `<mimalloc-stats.h>` two (`mi_stats_header_init`, `mi_stats_init`). A function
  with internal linkage belongs to one translation unit, so each is adapted under
  its name in `mcpplibs::mwrap::mimalloc` and calls upstream's body.
- **Macros that take a type.** `mi_malloc_tp(T)`, `mi_zalloc_tp(T)`,
  `mi_calloc_tp(T, n)`, `mi_mallocn_tp`, `mi_reallocn_tp`, `mi_recalloc_tp`,
  `mi_free_tp` and the six `mi_heap_*_tp`, and `mi_stats_t_decl(name)`, stay macros
  in `<mwrap/mimalloc/macros.hpp>`. Include it before the imports; the macros
  that call an adapted helper name it with its namespace.
- **Value macros.** `MI_MALLOC_VERSION`, `MI_SMALL_WSIZE_MAX`, `MI_SMALL_SIZE_MAX`,
  `MI_STAT_VERSION`, `MI_BIN_HUGE`, `MI_PROFILE_SAMPLE_DATA_MAX_SIZE` and
  `MI_HAS_HEAP_STL_ALLOCATOR` are `inline constexpr` constants of the same names.

## A header beside the module

`#include <mimalloc.h>` and `import mcpplibs.mwrap.mimalloc;` may appear in one
unit: they declare the same entities. A macro expands even inside a qualified
name, so `mcpplibs::mwrap::mimalloc::macros::MI_MALLOC_VERSION` written after the
header is `...::macros::30601`. Read the header's value under another name and
`#undef` the macro before naming the constant (tests/macros.cpp does this).

## Configuration

The library is `compat.mimalloc` 3.6.1, built by mcpp from the release tarball
without `MI_MALLOC_OVERRIDE`: `malloc` remains the C library's. Options are set at
run time with `mi_option_set` or the `MIMALLOC_*` environment variables
(`MIMALLOC_SHOW_STATS=1`, `MIMALLOC_VERBOSE=1` …), as upstream documents.

## Testing

```sh
mcpp test                               # the module: API, constants, header mixing
python3 tools/check_exports.py          # every entity and macro accounted for
python3 tools/run_conformance.py        # upstream's test-api and test-stress
python3 tools/test_template.py          # the default template, as installed
```
