# Bundle

## Concept

The official bundle is version-pinned and signable (the current process may still be manual).
Goal: distribute a coherent set of binaries + specs with zero drift.

## Layout (current)

- CLI bin: `dist/bin/yai-cli`
- Specs pinned: `deps/yai-specs/`

## Runtime Bundle (future mention)

A complete runtime bundle will also include core bins (`yai/dist/bin/*`).
This repository does not implement that part yet; it only documents it.
