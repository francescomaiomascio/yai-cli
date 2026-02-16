# Versioning

`yai-cli` follows Semantic Versioning.

## SemVer

- `MAJOR`: incompatible public CLI changes
- `MINOR`: backward-compatible additions
- `PATCH`: non-breaking fixes and documentation updates

## Specs Coordination

Each CLI release must be evaluated against the pinned `deps/yai-specs` revision.
Contract-breaking changes require a MAJOR bump or an explicit compatibility range update.
