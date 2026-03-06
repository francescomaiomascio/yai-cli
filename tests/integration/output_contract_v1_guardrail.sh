#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
CLI="$ROOT/dist/bin/yai"
TMP="$(mktemp -d /tmp/yai-cli-output-v1-XXXXXX)"
trap 'rm -rf "$TMP"' EXIT

"$CLI" lifecycle down >/dev/null 2>&1 || true
"$CLI" lifecycle up >/dev/null 2>&1

"$CLI" root ping >"$TMP/root_ping_tty_maybe.txt" 2>&1
NO_COLOR=1 "$CLI" root ping >"$TMP/root_ping_nocolor.txt" 2>&1
if rg -n $'\x1b\\[' "$TMP/root_ping_nocolor.txt" >/dev/null; then
  echo "NO_COLOR output contains ansi sequences"
  cat "$TMP/root_ping_nocolor.txt"
  exit 1
fi

"$CLI" root ping >"$TMP/root_ping.txt" 2>&1
if rg -n "command_id=|exec_reply:|control_call:|ok: OK:" "$TMP/root_ping.txt" >/dev/null; then
  echo "default output contains forbidden tokens"
  cat "$TMP/root_ping.txt"
  exit 1
fi
LINES="$(wc -l < "$TMP/root_ping.txt")"
if [[ "$LINES" -lt 2 || "$LINES" -gt 4 ]]; then
  echo "default output should be 2-4 lines, got $LINES"
  cat "$TMP/root_ping.txt"
  exit 1
fi

if command -v jq >/dev/null 2>&1; then
  "$CLI" --json root ping >"$TMP/root_ping.json" 2>&1
  jq -e . "$TMP/root_ping.json" >/dev/null
  if rg -n $'\x1b\\[' "$TMP/root_ping.json" >/dev/null; then
    echo "--json output contains ansi sequences"
    cat "$TMP/root_ping.json"
    exit 1
  fi
fi

"$CLI" --verbose-contract root ping >"$TMP/root_ping_contract.txt" 2>&1
rg -n "^control_call: \{" "$TMP/root_ping_contract.txt" >/dev/null
rg -n "^exec_reply: \{" "$TMP/root_ping_contract.txt" >/dev/null

set +e
"$CLI" boot artifact_audit >"$TMP/nyi.txt" 2>&1
RC_NYI=$?
set -e
if [[ "$RC_NYI" -ne 10 ]]; then
  echo "expected rc=10 for nyi, got $RC_NYI"
  cat "$TMP/nyi.txt"
  exit 1
fi
rg -n "^NOT IMPLEMENTED$" "$TMP/nyi.txt" >/dev/null

"$CLI" lifecycle down >/dev/null 2>&1 || true
set +e
"$CLI" root ping >"$TMP/root_ping_down.txt" 2>&1
RC_DOWN=$?
set -e
if [[ "$RC_DOWN" -ne 40 ]]; then
  echo "expected rc=40 for runtime down, got $RC_DOWN"
  cat "$TMP/root_ping_down.txt"
  exit 1
fi
rg -n "^SERVER UNAVAILABLE$" "$TMP/root_ping_down.txt" >/dev/null
rg -n "^Hint: Start the runtime with: yai lifecycle up$" "$TMP/root_ping_down.txt" >/dev/null

set +e
"$CLI" nonsense >"$TMP/bad_args.txt" 2>&1
RC_BAD=$?
set -e
if [[ "$RC_BAD" -ne 20 ]]; then
  echo "expected rc=20 for bad args, got $RC_BAD"
  cat "$TMP/bad_args.txt"
  exit 1
fi
rg -n "^BAD ARGS$" "$TMP/bad_args.txt" >/dev/null

YAI_PAGER=off "$CLI" help --groups >"$TMP/groups_no_pager.txt" 2>&1
[[ -s "$TMP/groups_no_pager.txt" ]]

NO_COLOR=1 "$CLI" watch root ping --interval 0.1 --count 3 >"$TMP/watch_non_tty.txt" 2>&1
LINES_WATCH="$(wc -l < "$TMP/watch_non_tty.txt")"
if [[ "$LINES_WATCH" -lt 3 ]]; then
  echo "watch non-tty fallback should print at least 3 lines"
  cat "$TMP/watch_non_tty.txt"
  exit 1
fi
if rg -n $'\x1b\\[' "$TMP/watch_non_tty.txt" >/dev/null; then
  echo "watch non-tty output contains ansi sequences"
  cat "$TMP/watch_non_tty.txt"
  exit 1
fi

echo "output_contract_v1_guardrail: ok"
