# Commands

## Source of Truth

The command source of truth is:
- `deps/yai-law/registry/commands.v1.json`

The associated schema is:
- `deps/yai-law/registry/schema/commands.v1.schema.json`

Exposure policy source of truth:
- `deps/yai-law/docs/pointers/SURFACE_POLICY.pointer.md`

## How to read it

1. `commands.v1.json` defines command set and contract semantics.
2. `commands.schema.json` defines formal validation rules for that document.

## Workspace-first Surface

The command surface is workspace-first for runtime operations:

- select or switch context with `yai ws use <ws-id>`
- inspect current binding with `yai ws current`
- clear binding with `yai ws clear`

Workspace resolution for workspace-scoped commands is deterministic:

1. explicit `--ws-id`
2. attached current workspace
3. clear error when no workspace is selected

## Operational Rule

No "invented" commands outside specs.
If CLI/specs drift appears: open an issue and align before release.
