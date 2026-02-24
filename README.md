# yai-cli - The Operator Interface

YAI = "YAI Ain't Intelligence"  
The CLI is where humans meet sovereignty.

`yai-cli` is the official command-line interface for the YAI runtime. It is intentionally thin: a contract-driven operator surface over the control plane of YAI.

It is built to be predictable, auditable, and compatible with the pinned canonical YAI Law. No hidden behaviors. No surprise side effects.

---

## 1) What it is

- The primary interface for operating YAI planes: Root, Kernel, Engine, Mind, and Law
- A strict consumer of the canonical command set defined in YAI Law
- A production-oriented tool for operators, developers, and CI gates

---

## 2) What it is not

- Not an "interactive shell" that invents workflows
- Not a wrapper around prompts
- Not a place where contracts are negotiated

The CLI follows the contracts. If the contract changes, the CLI updates with it.

---

## 3) Contract discipline (non-negotiable)

The CLI is governed by pinned law:

- Canonical command set: `deps/yai-law/specs/cli/schema/commands.v1.json`
- Canonical schema: `deps/yai-law/specs/cli/schema/commands.schema.json`
- Protocol envelope + IDs: `deps/yai-law/specs/protocol/include/*`

If behavior drifts from the pinned law, it's a bug. Fix the implementation - do not "work around" it.

---

## Install

Two common paths:

1) From a YAI Bundle (recommended)  
The public bundle ships an entrypoint `yai` that includes the CLI.

2) From source

```bash
make
```

Outputs:
- `dist/bin/yai-cli`

## Quick usage

```bash
# Root plane (global authority)
./dist/bin/yai-cli root status
./dist/bin/yai-cli root ping

# Kernel plane (workspace lifecycle / control)
./dist/bin/yai-cli kernel ws list

# Engine/Mind are workspace-scoped
./dist/bin/yai-cli engine --ws dev status
./dist/bin/yai-cli mind   --ws dev chat "ciao"
```

## Governance and lifecycle

This repo is run like infrastructure:

- Releases are reproducible
- Law is pinned explicitly (never floating)
- Compatibility is tracked and enforced

See: `VERSIONING.md`, `COMPATIBILITY.md`, `CHANGELOG.md`, `SECURITY.md`, `CONTRIBUTING.md`.

## License

Apache-2.0. See `LICENSE`, `NOTICE`, and `THIRD_PARTY_NOTICES.md`.
