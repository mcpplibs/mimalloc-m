// The header and the module in one translation unit: the same entities, so a
// block from one spelling is released through the other.
#include <mimalloc.h>
import std;
import mcpplibs.mwrap.mimalloc;

int main()
{
    void* p = ::mi_malloc(64);              // the header's declaration
    const bool same = ::mi_usable_size(p) >= 64;
    mi_free(p);                             // the module's
    mi_heap_t* h = mi_heap_new();
    const bool heap = h != nullptr;
    if (h) mi_heap_delete(h);
    std::println("{}", same && heap ? "header and module agree" : "FAIL");
    return same && heap ? 0 : 1;
}
