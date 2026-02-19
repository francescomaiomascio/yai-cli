# yai-cli — The Operator Interface

_YAI = "YAI Ain't Intelligence"_  
The CLI is where humans meet sovereignty.

`yai-cli` is the **official command-line interface** for the YAI runtime. It is intentionally thin: a contract-driven operator surface over the control plane of YAI.

It is built to be **predictable**, **auditable**, and **compatible** with the pinned canonical specs. No hidden behaviors. No surprise side effects.

---

## 1) What it is

- The primary interface for operating YAI planes: **Root**, **Kernel**, **Engine**, **Mind**, and **Law**
- A strict consumer of the canonical command set defined in **YAI Specs**
- A production-oriented tool for operators, developers, and CI gates

---

## 2) What it is not

- Not an "interactive shell" that invents workflows
- Not a wrapper around prompts
- Not a place where contracts are negotiated

The CLI follows the contracts. If the contract changes, the CLI updates *with it*.

---

## 3) Contract discipline (non-negotiable)

The CLI is governed by pinned specs:

- Canonical command set: `deps/yai-specs/specs/cli/schema/commands.v1.json`
- Canonical schema: `deps/yai-specs/specs/cli/schema/commands.schema.json`
- Protocol envelope + IDs: `deps/yai-specs/specs/protocol/include/*`

If behavior drifts from the pinned specs, it's a bug. Fix the implementation — do not "work around" it.

---

## Install

Two common paths:

**1) From a YAI Bundle (recommended)**  
The public bundle ships an entrypoint `yai` that includes the CLI.


- Canonical command set: `deps/yai-specs/specs/cli/schema/commands.v1.json`
- Canonical command schema: `deps/yai-specs/specs/cli/schema/commands.schema.json`
- Protocol envelope/IDs: `deps/yai-specs/specs/protocol/include/transport.h` and `deps/yai-specs/specs/protocol/include/yai_protocol_ids.h`

---

## Build

```bash
make
```

Outputs:

- `dist/bin/yai-cli`

---

## Quick usage

Typical workflows are plane-based:

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

---

## Governance & lifecycle

This repo is run like infrastructure:

- Releases are reproducible
- Specs are pinned explicitly (never floating)
- Compatibility is tracked and enforced

See:

- `VERSIONING.md`
- `COMPATIBILITY.md`
- `CHANGELOG.md`
- `SECURITY.md`
- `CONTRIBUTING.md`

---

## License

Apache-2.0. See `LICENSE`, `NOTICE`, and `THIRD_PARTY_NOTICES.md`.
