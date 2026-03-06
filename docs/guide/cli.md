# CLI Workspace Context

`yai-cli` treats workspace as a runtime-owned entity with a session binding layer.

## Context commands

- `yai ws use <ws-id>`: validate against runtime and persist current binding
- `yai ws current`: show bound workspace and runtime state
- `yai ws clear`: remove current binding

## Effective workspace precedence

1. explicit `--ws-id`
2. current binding (`ws use`)
3. unresolved context -> deterministic `BAD ARGS` for workspace-scoped commands

## Workspace-scoped command behavior

For workspace-scoped commands, when `--ws-id` is omitted and a current binding exists, CLI injects `--ws-id <current>` before execution.

If no binding exists, CLI fails with an actionable hint.
