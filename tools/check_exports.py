#!/usr/bin/env python3
"""Audit the modules against mimalloc's public headers.

Every function, type and enumerator that <mimalloc.h>, <mimalloc-stats.h> and
<mimalloc-profile.h> declare must be exported by src/*.cppm (`using ::name`),
adapted in mcpplibs::mwrap::mimalloc (an upstream `static inline` function,
which a module cannot export), or listed below with the reason it is not.
Every macro must be a constant of src/macros.cppm, a macro of
include/mwrap/mimalloc/macros.hpp, or listed with its reason. The headers are
read from the release tarball tools/run_conformance.py fetches.
"""
from pathlib import Path
import re
import sys

sys.path.insert(0, str(Path(__file__).resolve().parent))
from run_conformance import fetch  # noqa: E402

HEADERS = ('mimalloc.h', 'mimalloc-stats.h', 'mimalloc-profile.h')

# Macros that are part of how the headers are written, not of what they offer.
SYNTAX_MACROS = {
    'MIMALLOC_H', 'MIMALLOC_STATS_H', 'MIMALLOC_PROFILE_H',
    'mi_attr_noexcept', 'mi_attr_noreturn', 'mi_decl_nodiscard', 'mi_decl_export', 'mi_decl_restrict',
    'mi_cdecl', 'mi_attr_malloc', 'mi_attr_alloc_size', 'mi_attr_alloc_size2', 'mi_attr_alloc_align',
    'mi_decl_align', 'mi_decl_thread', 'mi_decl_externc',
    'MI_STAT_FIELDS', 'MI_STAT_COUNT', 'MI_STAT_COUNTER',
}


def strip(text: str) -> str:
    text = re.sub(r'/\*.*?\*/', ' ', text, flags=re.S)
    return re.sub(r'//[^\n]*', '', text)


def header_entities(include: Path):
    functions, inline, types, enumerators, macros = set(), set(), set(), set(), set()
    for name in HEADERS:
        text = strip((include / name).read_text(encoding='utf-8'))
        for m in re.finditer(r'^\s*#\s*define\s+([A-Za-z_][A-Za-z_0-9]*)', text, flags=re.M):
            macros.add(m.group(1))
        body = re.sub(r'^\s*#.*$', '', text, flags=re.M)
        for m in re.finditer(r'static\s+inline\b[^;{(]*?\b(mi_[a-z0-9_]+)\s*\(', body):
            inline.add(m.group(1))
        for m in re.finditer(r'\b(mi_[a-z0-9_]+)\s*\([^;{)]*\)[^;{]*;', body):
            if not m.group(1).startswith(('mi_attr', 'mi_decl')):
                functions.add(m.group(1))
        for m in re.finditer(r'typedef\b[^;{]*?\b(mi_[a-z0-9_]+(?:_t|_fun))\b[^;{]*;', body, flags=re.S):
            types.add(m.group(1))
        for m in re.finditer(r'\}\s*(mi_[a-z0-9_]+_t)\s*;', body):
            types.add(m.group(1))
        for m in re.finditer(r'\b(?:struct|enum)\s+(mi_[a-z0-9_]+_[se])\b', body):
            types.add(m.group(1))
        for m in re.finditer(r'template\s*<[^>]*>\s*struct\s+(mi_[a-z_]+allocator)\b', body):
            types.add(m.group(1))
        for block in re.findall(r'enum\s+mi_[a-z_]+_e\s*\{(.*?)\}', body, flags=re.S):
            for item in block.split(','):
                item = item.split('=')[0].strip()
                if item:
                    enumerators.add(item)
    functions -= inline
    return functions, inline, types, enumerators, macros


def module_names(root: Path):
    exported, adapted = set(), set()
    for source in (root / 'src').glob('*.cppm'):
        text = strip(source.read_text(encoding='utf-8'))
        exported |= set(re.findall(r'using\s+::([A-Za-z_][A-Za-z_0-9]*)\s*;', text))
        for block in re.findall(r'export\s+namespace\s+mcpplibs::mwrap::mimalloc\s*\{(.*?)\}', text, flags=re.S):
            adapted |= set(re.findall(r'\b(mi_[a-z0-9_]+)\s*\(', block))
    constants = set(re.findall(r'inline\s+constexpr\s+\w+\s+(MI_[A-Z_]+)\s*=',
                               (root / 'src/macros.cppm').read_text(encoding='utf-8')))
    kept = set(re.findall(r'#\s*define\s+([A-Za-z_][A-Za-z_0-9]*)',
                          (root / 'include/mwrap/mimalloc/macros.hpp').read_text(encoding='utf-8')))
    return exported, adapted, constants, kept


def main():
    root = Path(__file__).resolve().parents[1]
    include = fetch(root) / 'include'
    functions, inline, types, enumerators, macros = header_entities(include)
    exported, adapted, constants, kept = module_names(root)
    problems = []
    for name in sorted(functions | types | enumerators):
        if name not in exported:
            problems.append(f'not exported: {name}')
    for name in sorted(inline):
        if name not in adapted:
            problems.append(f'not adapted: static inline {name}')
    for name in sorted(macros - SYNTAX_MACROS):
        if name not in constants and name not in kept and name not in ('MWRAP_MIMALLOC_MACROS_HPP',):
            problems.append(f'macro neither mapped nor kept: {name}')
    for name in sorted(exported - functions - types - enumerators - {'operator==', 'operator!='}):
        problems.append(f'exported but not in the headers: {name}')
    for p in problems:
        print(p)
    print(f'{len(functions)} functions, {len(types)} types, {len(enumerators)} enumerators exported; '
          f'{len(inline)} inline functions adapted; {len(constants)} macros mapped, {len(kept)} kept; '
          f'{len(problems)} problems')
    return 1 if problems else 0


if __name__ == '__main__':
    sys.exit(main())
