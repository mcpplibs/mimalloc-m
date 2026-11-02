// <mwrap/mimalloc/macros.hpp> --- the macros of <mimalloc.h> that take a type
// (`mi_malloc_tp(T)' and its eleven companions), which a named module cannot
// export and no function can replace with the same call syntax. Include it
// before `import mcpplibs.mwrap.mimalloc;'; each expands to the upstream
// functions the module exports, and the three that upstream spells with its
// `static inline' helpers to the module's adaptations of them
// (mcpplibs::mwrap::mimalloc::mi_malloc_csize, mi_zalloc_csize,
// mi_free_csize). The definitions are otherwise upstream's (mimalloc 3.6.1,
// include/mimalloc.h, MIT license, upstream/mimalloc/LICENSE), each defined
// only where <mimalloc.h> has not defined it already.
#ifndef MWRAP_MIMALLOC_MACROS_HPP
#define MWRAP_MIMALLOC_MACROS_HPP

#ifndef mi_malloc_tp
#define mi_malloc_tp(tp)                 ((tp*)::mcpplibs::mwrap::mimalloc::mi_malloc_csize(sizeof(tp)))
#define mi_zalloc_tp(tp)                 ((tp*)::mcpplibs::mwrap::mimalloc::mi_zalloc_csize(sizeof(tp)))
#define mi_calloc_tp(tp,n)               ((tp*)mi_calloc(n,sizeof(tp)))
#define mi_mallocn_tp(tp,n)              ((tp*)mi_mallocn(n,sizeof(tp)))
#define mi_reallocn_tp(tp,p,n)           ((tp*)mi_reallocn(p,n,sizeof(tp)))
#define mi_recalloc_tp(tp,p,n)           ((tp*)mi_recalloc(p,n,sizeof(tp)))
#define mi_free_tp(tp,p)                 (::mcpplibs::mwrap::mimalloc::mi_free_csize(p,sizeof(tp)))

#define mi_heap_malloc_tp(tp,hp)         ((tp*)mi_heap_malloc(hp,sizeof(tp)))
#define mi_heap_zalloc_tp(tp,hp)         ((tp*)mi_heap_zalloc(hp,sizeof(tp)))
#define mi_heap_calloc_tp(tp,hp,n)       ((tp*)mi_heap_calloc(hp,n,sizeof(tp)))
#define mi_heap_mallocn_tp(tp,hp,n)      ((tp*)mi_heap_mallocn(hp,n,sizeof(tp)))
#define mi_heap_reallocn_tp(tp,hp,p,n)   ((tp*)mi_heap_reallocn(hp,p,n,sizeof(tp)))
#define mi_heap_recalloc_tp(tp,hp,p,n)   ((tp*)mi_heap_recalloc(hp,p,n,sizeof(tp)))
#endif

// <mimalloc-stats.h>: a statistics structure declared and initialised, through
// the module's adaptation of upstream's `static inline' mi_stats_init.
#ifndef mi_stats_t_decl
#define mi_stats_t_decl(name)  mi_stats_t name; ::mcpplibs::mwrap::mimalloc::mi_stats_init(&name);
#endif

#endif
