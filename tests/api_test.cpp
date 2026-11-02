// The allocator through import mcpplibs.mwrap.mimalloc: each check can fail,
// and each names what the allocator promises rather than that a call returned.
#include <mwrap/mimalloc/macros.hpp>
import std;
import mcpplibs.mwrap.mimalloc;

namespace {
int failures = 0;
void check(bool ok, std::string_view what)
{
    std::println("{} {}", ok ? "ok  " : "FAIL", what);
    if (!ok) ++failures;
}
struct point { double x, y, z; };
}

int main()
{
    void* p = mi_malloc(1000);
    check(p != nullptr && mi_usable_size(p) >= 1000, "mi_malloc hands out at least what was asked, and knows its size");
    std::memset(p, 0x5a, 1000);
    p = mi_realloc(p, 100000);
    check(p != nullptr && static_cast<unsigned char*>(p)[999] == 0x5a, "mi_realloc keeps the bytes it moves");
    mi_free(p);

    auto* z = static_cast<unsigned char*>(mi_zalloc(4096));
    check(z && std::all_of(z, z + 4096, [](unsigned char c) { return c == 0; }), "mi_zalloc returns zeroed memory");
    mi_free(z);

    for (std::size_t align : {16u, 64u, 4096u, 65536u}) {
        void* a = mi_malloc_aligned(100, align);
        check(a && reinterpret_cast<std::uintptr_t>(a) % align == 0, std::format("mi_malloc_aligned honours {}", align));
        mi_free(a);
    }

    char* s = mi_strdup("mimalloc");
    check(s && std::string_view(s) == "mimalloc", "mi_strdup copies a string");
    mi_free(s);

    mi_heap_t* heap = mi_heap_new();
    check(heap != nullptr, "a private heap is made");
    std::vector<void*> blocks;
    for (int i = 0; i < 1000; ++i) blocks.push_back(mi_heap_malloc(heap, 64 + i));
    check(std::all_of(blocks.begin(), blocks.end(), [&](void* b) { return mi_heap_contains(heap, b); }),
          "the heap holds every block it handed out");
    std::size_t visited = 0;
    mi_heap_visit_blocks(heap, true, [](const mi_heap_t*, const mi_heap_area_t*, void* block, std::size_t, void* arg) {
        if (block) ++*static_cast<std::size_t*>(arg);
        return true;
    }, &visited);
    check(visited == blocks.size(), "visiting the heap finds every block");
    mi_heap_destroy(heap);

    point* pt = mi_malloc_tp(point);
    check(pt != nullptr, "mi_malloc_tp, a macro of <mwrap/mimalloc/macros.hpp>, allocates its type");
    pt->x = 1;
    mi_free_tp(point, pt);

    check(mi_version() == mcpplibs::mwrap::mimalloc::macros::MI_MALLOC_VERSION, "mi_version is the version the module was built from");

    const long before = mi_option_get(mi_option_purge_delay);
    mi_option_set(mi_option_purge_delay, before + 1);
    check(mi_option_get(mi_option_purge_delay) == before + 1, "an option is set and read back");
    mi_option_set(mi_option_purge_delay, before);

    std::vector<int, mi_stl_allocator<int>> v(1000, 7);
    check(std::accumulate(v.begin(), v.end(), 0) == 7000, "a vector allocates through mi_stl_allocator");
    check(mi_stl_allocator<int>() == mi_stl_allocator<long>(), "two STL allocators compare equal");

    mi_stats_t_decl(stats);
    check(stats.size == sizeof stats && static_cast<int>(stats.version) == mcpplibs::mwrap::mimalloc::macros::MI_STAT_VERSION,
          "mi_stats_t_decl declares a statistics structure with its size and version");
    check(mi_stats_get(&stats), "the process's statistics are read (mcpplibs.mwrap.mimalloc.stats)");

    std::atomic<int> done{0};
    std::vector<std::jthread> threads;
    for (int t = 0; t < 4; ++t)
        threads.emplace_back([&] {
            std::vector<void*> mine;
            for (int i = 0; i < 10000; ++i) mine.push_back(mi_malloc(16 + i % 512));
            for (void* m : mine) mi_free(m);
            done.fetch_add(1);
        });
    threads.clear();
    check(done.load() == 4, "four threads allocate and free at once");

    std::println("-- failures: {} --", failures);
    return failures != 0;
}
