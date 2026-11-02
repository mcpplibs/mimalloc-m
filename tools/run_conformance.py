#!/usr/bin/env python3
"""Run mimalloc's own test/test-api.c and test/test-stress.c (of the release)
against compat.mimalloc 3.6.1, the library this wrapper exports.

The release tarball is downloaded once into target/upstream and checked
against upstream/documents.json. The two tests and their helper header are
copied unchanged into target/conformance/test, and a project there builds them
as C over compat.mimalloc (the tests include <mimalloc.h> and one internal
header, mimalloc/types.h, which a C program cannot import as a module; the
module's own tests are tests/*.cpp). Both run, and both must end with status 0:
test-api reports every case, and test-stress runs `--threads` threads over
`--scale` and `--iterations` (upstream's defaults are 32, 50 and 50; the run
is bounded for a shared runner).
"""
import argparse
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import sys
import tarfile
import urllib.request

MANIFEST = '''[package]
name        = "mimalloc-conformance"
version     = "3.6.1"
description = "mimalloc 3.6.1's test/test-api.c and test/test-stress.c over compat.mimalloc (tools/run_conformance.py)"

[targets.test-api]
kind = "bin"
main = "test/test-api.c"

[targets.test-stress]
kind = "bin"
main = "test/test-stress.c"

[build]
c_standard = "c11"
sources    = []

[dependencies]
compat.mimalloc = "3.6.1"
'''


def fetch(root: Path) -> Path:
    pins = json.loads((root / 'upstream/documents.json').read_text(encoding='utf-8'))
    cache = root / 'target/upstream'
    cache.mkdir(parents=True, exist_ok=True)
    archive = cache / 'mimalloc-release.tar.gz'
    if not archive.exists() or hashlib.sha256(archive.read_bytes()).hexdigest() != pins['upstream_sha256']:
        print('+ fetch', pins['upstream'], flush=True)
        with urllib.request.urlopen(pins['upstream'], timeout=120) as response:
            archive.write_bytes(response.read())
    digest = hashlib.sha256(archive.read_bytes()).hexdigest()
    if digest != pins['upstream_sha256']:
        sys.exit(f'upstream archive checksum {digest} != {pins["upstream_sha256"]}')
    with tarfile.open(archive) as tar:
        top = tar.getmembers()[0].name.split('/')[0]
        if not (cache / top).exists():
            tar.extractall(cache, filter='data')
    return cache / top


def run(command, cwd):
    print('+', ' '.join(map(str, command)), flush=True)
    return subprocess.run(command, cwd=cwd, check=True)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--mcpp', default='mcpp')
    parser.add_argument('--toolchain')
    parser.add_argument('--threads', type=int, default=8)
    parser.add_argument('--scale', type=int, default=25)
    parser.add_argument('--iterations', type=int, default=5)
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    upstream = fetch(root)
    work = root / 'target/conformance'
    shutil.rmtree(work, ignore_errors=True)
    (work / 'test').mkdir(parents=True)
    for name in ('test-api.c', 'test-stress.c', 'testhelper.h'):
        shutil.copyfile(upstream / 'test' / name, work / 'test' / name)
    (work / 'mcpp.toml').write_text(MANIFEST, encoding='utf-8')
    build = [args.mcpp, 'build', '--release']
    if args.toolchain:
        build += ['--toolchain', args.toolchain]
    run(build, work)
    binaries = {p.stem: p for p in (work / 'target').rglob('*') if p.is_file() and p.stem in ('test-api', 'test-stress')
                and p.suffix in ('', '.exe')}
    for name in ('test-api', 'test-stress'):
        if name not in binaries:
            sys.exit(f'{name} did not build')
    run([binaries['test-api']], work)
    run([binaries['test-stress'], str(args.threads), str(args.scale), str(args.iterations)], work)
    print('mimalloc 3.6.1: test-api and test-stress passed over compat.mimalloc', flush=True)


if __name__ == '__main__':
    main()
