# CLI Usage

`yai` is the operator CLI for runtime control and governance surfaces.

Basic form:

`yai <group> <command> [options]`

## Output Modes

- default: human one-line output
- `--verbose`: human line + metadata (`status/code/reason/ids`)
- `--json`: raw `exec_reply` JSON
- `--verbose-contract`: two lines (`control_call`, `exec_reply`)

## Help System

Help is registry-driven and generated from `deps/yai-law/registry/commands.v1.json`.

Supported forms:

- `yai help`
- `yai help <group>`
- `yai help <group> <command>`
- `yai help yai.<group>.<command>`
- `yai help --groups`
- `yai help --all`

## Watch Mode

Prototype live refresh mode:

`yai watch <group> <command> [args...]`

Behavior:

- clears screen on each refresh
- shows status header
- executes command every 1 second
- exits on `Ctrl+C`

## Pager

Pager support is available for long text outputs (primarily help).

Enable:

- `--pager`
- `YAI_PAGER=1`

Disable:

- `--no-pager`

Pager is only used on TTY outputs.

## Exit Codes

- `0`: success
- `10`: not implemented (`NYI`)
- `20`: bad arguments / invalid input
- `30`: unauthorized
- `40`: unavailable / not ready
- `50`: protocol/internal fallback
