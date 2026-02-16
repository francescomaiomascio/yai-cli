# YAI CLI

YAI CLI is the official client for the Control Plane (Root/Kernel/Engine/Mind).

## Quickstart

```bash
yai root ping
yai ws list
yai kernel status
```

These commands exist today and run through the runtime control plane.

## Specs Pinned

The contract source of truth is `deps/yai-specs`.
This CLI consumes that pin; no command/protocol behavior may drift from it.

## Documentation

- `docs/INSTALL.md`
- `docs/BUNDLE.md`
- `docs/SPECS_PINNING.md`
- `docs/COMMANDS.md`
- `docs/GOVERNANCE.md`

## Policies

- `SECURITY.md`
- `CONTRIBUTING.md`
- `CODE_OF_CONDUCT.md`
