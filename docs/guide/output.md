# Output Modes

YAI CLI has 4 execution output modes.

## Default

Human one-line summary:

- `root: ping ok`
- `kernel: ws created (ws_id=ws_sem_02)`
- `NOT_IMPLEMENTED: boot: artifact_audit`
- `SERVER_UNAVAILABLE: root socket unreachable`

Default mode never prints JSON metadata (`command_id`, `trace_id`, `target_plane`).

## `--verbose`

Operator/debug mode:

1. first line is the same as default
2. then metadata key/value lines:
   - `status=...`
   - `code=...`
   - `reason=...`
   - `command_id=...`
   - `target_plane=...`
   - `trace_id=...`

## `--json`

Machine mode:

- prints only raw `exec_reply` JSON
- no extra prefixes
- parseable via `jq`

## `--verbose-contract`

Audit/proof mode:

- exactly 2 lines:
  - `control_call: {...}`
  - `exec_reply: {...}`
- no extra logs, hints, or decorations

## Colors

Color policy applies only to default/verbose human rendering:

- `ok` green
- `nyi` yellow
- `error` red
- verbose keys (`status`, `code`, etc.) cyan

Colors are enabled only when `stdout/stderr` is a TTY.

Colors are disabled when either:

- `--no-color` is set
- `NO_COLOR` environment variable is set

No colors are used in `--json` or `--verbose-contract`.

## Exit Codes

- `0`: success (`ok/OK`)
- `10`: not implemented (`nyi/NOT_IMPLEMENTED`)
- `20`: invalid input (`BAD_ARGS`/invalid target)
- `30`: unauthorized
- `40`: unavailable/not ready
- `50`: protocol/internal fallback
