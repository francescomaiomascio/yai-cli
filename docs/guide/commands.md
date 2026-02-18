# Commands

## Source of Truth

The command source of truth is:
- `deps/yai-specs/specs/cli/schema/commands.v1.json`

The associated schema is:
- `deps/yai-specs/specs/cli/schema/commands.schema.json`

## How to read it

1. `commands.v1.json` defines command set and contract semantics.
2. `commands.schema.json` defines formal validation rules for that document.

## Operational Rule

No "invented" commands outside specs.
If CLI/specs drift appears: open an issue and align before release.
