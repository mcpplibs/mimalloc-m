# mimalloc

> mimalloc, Microsoft's general-purpose allocator, through C++23 modules.

**English** · [简体中文](README.zh.md) · [Upstream](https://github.com/microsoft/mimalloc) · [Releases](https://github.com/mcpplibs/mimalloc-m/releases) · [mcpp](https://github.com/mcpp-community/mcpp) · [Index](https://github.com/mcpplibs/mcpp-index)

[![C++23](https://img.shields.io/badge/C%2B%2B-23-blue.svg)](https://en.cppreference.com/w/cpp/23)
[![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg)](LICENSE)
[![mcpp-community](https://img.shields.io/badge/mcpp--community-mwrap-blue)](https://github.com/mcpp-community)
[![CI](https://github.com/mcpplibs/mimalloc-m/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/mcpplibs/mimalloc-m/actions/workflows/ci.yml)

The upstream API is unchanged. The `mi_*` functions, `mi_heap_t`, the option
enumeration, the callback types and the STL allocators are the upstream
entities of `<mimalloc.h>`, in the global namespace where upstream declares
them. The library is `compat.mimalloc` 3.6.1. The value macros are constants.
Upstream's own `test-api` and `test-stress` pass on every CI run over the same
library.

## Modules

- `import mcpplibs.mwrap.mimalloc;`: the functions, heaps, arenas, sub-processes, options and STL allocators of `<mimalloc.h>`, re-exporting the three below
- `import mcpplibs.mwrap.mimalloc.stats;`: `mi_stats_get`, `mi_heap_stats_get` … and `mi_stats_t` (`<mimalloc-stats.h>`)
- `import mcpplibs.mwrap.mimalloc.profile;`: the sampling profiler and the pprof writer (`<mimalloc-profile.h>`)
- `import mcpplibs.mwrap.mimalloc.macros;`: `MI_MALLOC_VERSION`, `MI_SMALL_SIZE_MAX` … in `mcpplibs::mwrap::mimalloc::macros`

> More Modules API -> [Usage and API](docs/usage.md)

## Getting started

```sh
mcpp new allocate --template mcpplibs.mwrap.mimalloc@3.6.1
cd allocate
mcpp run
```

The default template fills a private heap and destroys it in one call. It
allocates an aligned block, keeps a vector's elements in mimalloc, and prints
the version.

```toml
[dependencies]
"mcpplibs.mwrap.mimalloc" = "3.6.1"
```

```cpp
import std;
import mcpplibs.mwrap.mimalloc;

int main() {
    mi_heap_t* heap = mi_heap_new();
    auto* p = static_cast<char*>(mi_heap_malloc(heap, 64));
    std::println("{} usable bytes", mi_usable_size(p));
    mi_heap_destroy(heap);                       // frees every block of the heap
    std::vector<int, mi_stl_allocator<int>> v{1, 2, 3};
}
```

## Configuration and macros

mimalloc is configured when `compat.mimalloc` is built, and its options at
run time through `mi_option_set` or the `MIMALLOC_*` environment variables.
The typed allocation macros (`mi_malloc_tp(T)`, `mi_heap_calloc_tp(T, heap, n)` …)
take a type, so no function can have the same call syntax. They stay macros in
`<mwrap/mimalloc/macros.hpp>`, included before the imports. Three of them call
upstream's `static inline` helpers, which a module cannot export. The module
adapts those helpers as `mcpplibs::mwrap::mimalloc::mi_malloc_csize` and its
companions. A macro expands even in a qualified name. A unit that includes
`<mimalloc.h>` beside the module therefore reads the constants through other
names ([docs/usage.md](docs/usage.md)).

mimalloc does not replace `malloc` here: the package builds without
`MI_MALLOC_OVERRIDE`, as `compat.mimalloc` does.

## Build and testing

Linux, macOS and Windows CI build the modules and run the tests. They cover
allocation, reallocation, zeroing, alignment, private heaps and their
visiting, the typed macros, options, the STL allocator, statistics, four
threads at once, the constants, and header mixing. CI also runs:

- the export audit ([tools/check_exports.py](tools/check_exports.py)): every
  function and type of the three headers is exported, adapted or listed with
  its reason;
- upstream's `test/test-api.c` and `test/test-stress.c` over the same library
  ([tools/run_conformance.py](tools/run_conformance.py)).

A separate job scaffolds the default template as an installed package and runs
it.

## License

[Apache-2.0](LICENSE) for the wrapper, by mcpp-community ([NOTICE](NOTICE)).
mimalloc remains under the MIT license
([upstream/mimalloc/LICENSE](upstream/mimalloc/LICENSE),
[README](upstream/mimalloc/README.md)).
