# CLI Guide

## Command Grammar

YAI command surface help/navigation follows:

`yai <entrypoint> <topic> [op] [options]`

## Help Navigation

- `yai --help` / `yai help`: surface entrypoints
- `yai help --all`: surface + ancillary
- `yai help --plumbing`: includes plumbing/internal
- `yai help <entrypoint>`
- `yai help <entrypoint> <topic>`
- `yai help <entrypoint> <topic> <op>`

Exposure policy for these views is defined in:
- `deps/yai-law/docs/pointers/SURFACE_POLICY.pointer.md`

## Legacy Compatibility

Legacy names can be resolved as aliases where possible.
When legacy input is not canonical, help suggests the canonical entrypoint/topic/op path.

## Workspace Context Mode

- `yai ws use <ws-id>`: attach current workspace context
- `yai ws current`: show attached workspace
- `yai ws clear`: clear attached workspace
- `yai ws use <other-ws-id>`: explicit workspace switch

Workspace resolution precedence:

1. explicit `--ws-id`
2. attached current workspace
3. error: no workspace selected (for workspace-scoped commands)

## Output Modes

- default human: concise subject + outcome (+ optional summary/hint)
- `--verbose`: adds `Details:` and optional `Trace: ...`
- `--verbose-contract`: strict audit channel (`control_call`, `exec_reply`)
- `--json`: raw machine JSON only
- color policy: `--color=auto|always|never` and `--no-color`

## Watch Mode

- `yai watch <entrypoint> <topic> [op] [args...]`
- `--interval-ms <ms>` controls refresh rate
- `--count <n>` runs a bounded number of iterations

Interactive controls:

- `q` or `ESC`: quit
- `r`: refresh now
- `t`: toggle trace
- `c`: toggle color
- `h`: toggle controls overlay

See [output.md](./output.md) for the full output contract.

## Operator Capabilities

Operator capability surfaces are intentionally separated:

- `doctor`: readiness and diagnostics checks
- `inspect`: read-only state introspection
- `verify`: contract and alignment validation

Capability topics:

- `doctor env|runtime|workspace|pins|config|all`
- `inspect workspace|runtime|catalog|context`
- `verify law|registry|runtime|workspace|reply|alignment`

All capability commands support the standard output modes, including `--json`.

## Runtime Resolution

CLI runtime/bootstrap paths are resolved through the SDK canonical resolver layer.
The CLI does not maintain machine-specific absolute path fallbacks.

Resolver precedence:

1. explicit command/config override
2. environment override (`YAI_*`)
3. SDK canonical install/runtime discovery
4. deterministic error

Relevant overrides:

- `YAI_RUNTIME_HOME`
- `YAI_INSTALL_ROOT`
- `YAI_ROOT_SOCK`
- `YAI_BOOT_BIN`
- `YAI_ROOT_BIN`
- `YAI_KERNEL_BIN`
- `YAI_ENGINE_BIN`

Normative pointer:
- `deps/yai-law/docs/pointers/RUNTIME_RESOLUTION.pointer.md`
