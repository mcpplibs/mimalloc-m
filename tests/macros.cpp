// The value macros of mimalloc's headers, as the module's constants: equal to
// the macros of the headers. A macro expands even in a qualified name, so the
// headers' values are taken under other names and the macros undefined before
// the constants are named (docs/usage.md).
#include <mimalloc.h>
#include <mimalloc-stats.h>
#include <mimalloc-profile.h>

namespace header {
constexpr long long MALLOC_VERSION = MI_MALLOC_VERSION;
constexpr long long SMALL_WSIZE_MAX = MI_SMALL_WSIZE_MAX;
constexpr long long SMALL_SIZE_MAX = MI_SMALL_SIZE_MAX;
constexpr long long STAT_VERSION = MI_STAT_VERSION;
constexpr long long BIN_HUGE = MI_BIN_HUGE;
constexpr long long PROFILE_SAMPLE_DATA_MAX_SIZE = MI_PROFILE_SAMPLE_DATA_MAX_SIZE;
constexpr bool HAS_HEAP_STL_ALLOCATOR = (MI_HAS_HEAP_STL_ALLOCATOR) != 0;
}
#undef MI_MALLOC_VERSION
#undef MI_SMALL_WSIZE_MAX
#undef MI_SMALL_SIZE_MAX
#undef MI_STAT_VERSION
#undef MI_BIN_HUGE
#undef MI_PROFILE_SAMPLE_DATA_MAX_SIZE
#undef MI_HAS_HEAP_STL_ALLOCATOR

import std;
import mcpplibs.mwrap.mimalloc.macros;

namespace m = mcpplibs::mwrap::mimalloc::macros;

int main()
{
    int failures = 0;
    auto check = [&](bool ok, std::string_view what) {
        std::println("{} {}", ok ? "ok  " : "FAIL", what);
        if (!ok) ++failures;
    };
    check(m::MI_MALLOC_VERSION == header::MALLOC_VERSION && m::MI_MALLOC_VERSION == 30601, "MI_MALLOC_VERSION");
    check(static_cast<long long>(m::MI_SMALL_WSIZE_MAX) == header::SMALL_WSIZE_MAX, "MI_SMALL_WSIZE_MAX");
    check(static_cast<long long>(m::MI_SMALL_SIZE_MAX) == header::SMALL_SIZE_MAX, "MI_SMALL_SIZE_MAX");
    check(m::MI_STAT_VERSION == header::STAT_VERSION, "MI_STAT_VERSION");
    check(static_cast<long long>(m::MI_BIN_HUGE) == header::BIN_HUGE, "MI_BIN_HUGE");
    check(static_cast<long long>(m::MI_PROFILE_SAMPLE_DATA_MAX_SIZE) == header::PROFILE_SAMPLE_DATA_MAX_SIZE,
          "MI_PROFILE_SAMPLE_DATA_MAX_SIZE");
    check(m::MI_HAS_HEAP_STL_ALLOCATOR == header::HAS_HEAP_STL_ALLOCATOR, "MI_HAS_HEAP_STL_ALLOCATOR");
    std::println("-- failures: {} --", failures);
    return failures != 0;
}
