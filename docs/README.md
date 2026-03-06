# yai-cli Documentation

This directory is the documentation entrypoint for the YAI command surface, contract references, and repository governance for `yai-cli`.

## Documentation map

- `docs/guide/` - install, quickstart, command usage, troubleshooting
- `docs/reference/` - contract-facing references and governance notes
- `docs/development/` - build, tests, release flow, pinning, repo tooling
- `docs/api/` - generated/API landing content

## Start sequence

1. `docs/guide/quickstart.md`
2. `docs/reference/` materials relevant to your command family
3. `docs/development/repo-tooling.md` for verification and release operations

## Alignment rule

CLI docs are informative for CLI operation.
Normative contract authority remains in pinned `deps/yai-law/` artifacts.
SDK API authority remains in pinned `deps/yai-sdk/` artifacts.

## Docs architecture note

For cross-repo truth boundaries and surface exposure policy, see:
- `deps/yai-law/docs/pointers/DOCS_ARCHITECTURE.pointer.md`
- `deps/yai-law/docs/pointers/SURFACE_POLICY.pointer.md`
