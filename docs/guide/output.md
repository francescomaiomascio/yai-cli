# YAI Output Language v1

YAI CLI execution output has 4 canonical modes.

- `default` (human): concise command-surface output.
- `--verbose` (human): default output plus `Details:` block.
- `--verbose-contract` (audit): exactly two lines:
  - `control_call: {...}`
  - `exec_reply: {...}`
- `--json` (machine): exactly one JSON object, no prefixes.

Shape:

1. subject line: invoked command in short human form (for example `root ping`)
2. status line: `OK` or one canonical error class
3. optional curated detail line(s)
4. optional `Hint: ...` line
5. optional `Trace: ...` line for non-OK outcomes when trace is available

Rules:

- no raw JSON
- no `command_id=...` metadata
- no internal reason tokens as primary message
- colors are enabled only on TTY (`NO_COLOR`, `YAI_NO_COLOR`, `TERM=dumb` disable colors)

## `--verbose` (human + diagnostics)

Verbose keeps the same first lines as `default`, then adds:

- `Details:` section
- normalized metadata (`status`, `code`, `reason`, `command_id`, `target_plane`)
- `Trace: ...` when present
- `Hint: ...` when applicable

## `--verbose-contract` (audit)

Always prints:

- `control_call: <json>`
- `exec_reply: <json>`

No other prefixes are added in this mode.
JSON blocks are never colorized.

## `--json` (machine)

Prints only one JSON object (`exec_reply`) with no extra text.
Output must be parseable directly via `jq`.

## Canonical Exit Codes

- `0` -> `OK`
- `10` -> `NOT_IMPLEMENTED`
- `20` -> `BAD_ARGS` / invalid invocation class
- `30` -> `UNAUTHORIZED`
- `40` -> `SERVER_UNAVAILABLE` / `RUNTIME_NOT_READY`
- `50` -> `PROTOCOL_ERROR` / `INTERNAL_ERROR` fallback
