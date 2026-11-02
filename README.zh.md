# mimalloc

> mimalloc——微软的通用内存分配器，以 C++23 模块提供。

[English](README.md) · **简体中文** · [上游](https://github.com/microsoft/mimalloc) · [发布](https://github.com/mcpplibs/mimalloc-m/releases) · [mcpp](https://github.com/mcpp-community/mcpp) · [索引](https://github.com/mcpplibs/mcpp-index)

[![C++23](https://img.shields.io/badge/C%2B%2B-23-blue.svg)](https://en.cppreference.com/w/cpp/23)
[![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg)](LICENSE)
[![mcpp-community](https://img.shields.io/badge/mcpp--community-mwrap-blue)](https://github.com/mcpp-community)
[![CI](https://github.com/mcpplibs/mimalloc-m/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/mcpplibs/mimalloc-m/actions/workflows/ci.yml)

上游 API 不变：`mi_*` 函数、`mi_heap_t`、选项枚举、回调类型与 STL 分配器都是 `<mimalloc.h>` 中的上游实体，位于上游声明它们的
全局命名空间。库本身是 `compat.mimalloc` 3.6.1；值宏映射为常量。每次 CI 都在同一份库上运行上游自己的 `test-api` 与
`test-stress`。

## 模块

- `import mcpplibs.mwrap.mimalloc;`：`<mimalloc.h>` 的函数、堆、arena、子进程、选项与 STL 分配器，并重新导出下面三个模块
- `import mcpplibs.mwrap.mimalloc.stats;`：`mi_stats_get`、`mi_heap_stats_get` 等与 `mi_stats_t`（`<mimalloc-stats.h>`）
- `import mcpplibs.mwrap.mimalloc.profile;`：采样剖析器与 pprof 写出（`<mimalloc-profile.h>`）
- `import mcpplibs.mwrap.mimalloc.macros;`：`MI_MALLOC_VERSION`、`MI_SMALL_SIZE_MAX` 等，位于 `mcpplibs::mwrap::mimalloc::macros`

> 更多模块 API -> [用法与 API](docs/usage.md)

## 快速开始

```sh
mcpp new allocate --template mcpplibs.mwrap.mimalloc@3.6.1
cd allocate
mcpp run
```

默认模板在一个私有堆中分配并一次销毁，分配一个对齐的块，让 vector 的元素由 mimalloc 分配，并打印版本。

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
    mi_heap_destroy(heap);                       // 释放这个堆中的全部块
    std::vector<int, mi_stl_allocator<int>> v{1, 2, 3};
}
```

## 配置与宏

mimalloc 在构建 `compat.mimalloc` 时配置；运行时的选项经 `mi_option_set` 或 `MIMALLOC_*` 环境变量设置。带类型参数的分配宏
（`mi_malloc_tp(T)`、`mi_heap_calloc_tp(T, heap, n)` 等）没有调用形式相同的函数可以替代，保留为
`<mwrap/mimalloc/macros.hpp>` 中的宏，在 import 之前包含；其中三个调用上游的 `static inline` 辅助函数，模块无法导出它们，模块以
`mcpplibs::mwrap::mimalloc::mi_malloc_csize` 等同名函数适配。宏在限定名中同样会展开，因此与 `<mimalloc.h>` 同时使用时要换名
读取常量（[docs/usage.md](docs/usage.md)）。

本包不替换 `malloc`：与 `compat.mimalloc` 相同，构建时不定义 `MI_MALLOC_OVERRIDE`。

## 构建与测试

Linux、macOS 与 Windows 的 CI 构建模块并运行测试：分配、重新分配、清零、对齐、私有堆及其遍历、类型宏、选项、STL 分配器、
统计、四个线程同时分配、常量与头文件混用。CI 还运行导出审计（[tools/check_exports.py](tools/check_exports.py)：三个头文件的
每个函数与类型都已导出、适配或列出理由），以及在同一份库上构建的上游 `test/test-api.c` 与 `test/test-stress.c`
（[tools/run_conformance.py](tools/run_conformance.py)）。另有一个作业以已安装包的方式生成默认模板并运行。

## 许可

封装部分为 [Apache-2.0](LICENSE)，作者 mcpp-community（[NOTICE](NOTICE)）。mimalloc 仍为 MIT 许可
（[upstream/mimalloc/LICENSE](upstream/mimalloc/LICENSE)、[README](upstream/mimalloc/README.md)）。
