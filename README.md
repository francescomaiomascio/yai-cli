# yai-cli — Governed Operator Interface for the YAI Platform

`yai-cli` is the enterprise command-line control surface for governed YAI runtime operations.

It is intentionally thin, deterministic, and auditable: a contract-driven operator interface over `yai-sdk` and pinned `yai-law` artifacts.

## Platform role

Dependency and authority chain:

`yai-law` -> `yai-sdk` -> `yai-cli` -> `yai` -> `yai-ops`

The CLI does not invent contract semantics.
It executes and exposes them.

## What this repository is

- Primary operator interface for Root, Kernel, Engine, and Mind-facing runtime operations
- Deterministic command surface aligned to pinned law registries and schemas
- Production tooling for operators, CI gates, and integration workflows

## What this repository is not

- Not a policy authority repository
- Not a speculative workflow shell
- Not a place to negotiate contract semantics outside `yai-law`

## Contract discipline (non-negotiable)

The CLI is governed by pinned law and SDK surfaces:

- Canonical command registry: `deps/yai-law/registry/commands.v1.json`
- Canonical command schema: `deps/yai-law/registry/schema/commands.v1.schema.json`
- Canonical protocol surface: `deps/yai-law/contracts/protocol/include/*`
- Canonical SDK public include: `deps/yai-sdk/include/yai_sdk/public.h`

If behavior drifts from pinned law, the implementation is defective.

## Determinism and governance posture

- No hidden side effects
- Explicit return-code semantics
- Reproducible releases and compatibility tracking
- Law pinning is explicit and reviewable

## Build and outputs

```bash
make
```

Outputs:
- `dist/bin/yai` (canonical entrypoint)
- `dist/bin/yai-cli` (compat alias)

## Quick usage

```bash
./dist/bin/yai root status
./dist/bin/yai kernel ws list
./dist/bin/yai engine --ws dev status
./dist/bin/yai mind --ws dev chat "status"
```

## Documentation entrypoint

- `docs/README.md`

## Governance references

- `VERSIONING.md`
- `COMPATIBILITY.md`
- `CHANGELOG.md`
- `SECURITY.md`
- `CONTRIBUTING.md`

## License

Apache-2.0. See `LICENSE`, `NOTICE`, and `THIRD_PARTY_NOTICES.md`.
