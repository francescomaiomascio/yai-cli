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
