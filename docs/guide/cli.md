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

Live refresh mode:

`yai watch <group> <command> [args...]`

Flags:

- `--interval <sec>` (float seconds)
- `--interval-ms <ms>`
- `--count <n>`
- `--once`
- `--no-clear`

TTY behavior:

- alternate screen UI
- keys: `q`/`Esc` quit, `space` pause, `r` refresh, `?` help overlay, `/` filter, `c` clear history

Non-TTY behavior:

- line-by-line polling output with timestamps (no ANSI)

## Pager

Pager support is available for long text outputs (primarily help).

Enable:

- `--pager`
- `YAI_PAGER=1`

Disable:

- `--no-pager`
- `YAI_NO_PAGER=1`
- `YAI_PAGER=off`

Pager is only used on TTY outputs.

## Exit Codes

- `0`: success
- `10`: not implemented (`NYI`)
- `20`: bad arguments / invalid input
- `30`: unauthorized
- `40`: unavailable / not ready
- `50`: protocol/internal fallback
