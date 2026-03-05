#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
CLI="$ROOT/dist/bin/yai"

TMP="$(mktemp -d /tmp/yai-cli-porcelain-XXXXXX)"
trap 'rm -rf "$TMP"' EXIT

assert_one_line() {
  local f="$1"
  local n
  n="$(wc -l < "$f")"
  if [[ "$n" -ne 1 ]]; then
    echo "expected exactly 1 line in $f, got $n"
    cat "$f"
    exit 1
  fi
}

"$CLI" lifecycle down >/dev/null 2>&1 || true
"$CLI" lifecycle up >"$TMP/up.txt" 2>&1
assert_one_line "$TMP/up.txt"
rg -n "^lifecycle: up ok$" "$TMP/up.txt" >/dev/null

"$CLI" root ping >"$TMP/root_ping.txt" 2>&1
assert_one_line "$TMP/root_ping.txt"
rg -n "^root: ping ok$" "$TMP/root_ping.txt" >/dev/null

"$CLI" --verbose root ping >"$TMP/verbose.txt" 2>&1
rg -n "^root: ping ok$" "$TMP/verbose.txt" >/dev/null
rg -n "^status=" "$TMP/verbose.txt" >/dev/null
rg -n "^code=" "$TMP/verbose.txt" >/dev/null
rg -n "^reason=" "$TMP/verbose.txt" >/dev/null
rg -n "^command_id=" "$TMP/verbose.txt" >/dev/null
rg -n "^target_plane=" "$TMP/verbose.txt" >/dev/null
rg -n "^trace_id=" "$TMP/verbose.txt" >/dev/null

"$CLI" --json root ping >"$TMP/json.txt" 2>&1
jq -e . "$TMP/json.txt" >/dev/null

"$CLI" --verbose-contract root ping >"$TMP/contract.txt" 2>&1
if [[ "$(wc -l < "$TMP/contract.txt")" -ne 2 ]]; then
  echo "verbose-contract must print exactly 2 lines"
  cat "$TMP/contract.txt"
  exit 1
fi
rg -n "^control_call: " "$TMP/contract.txt" >/dev/null
rg -n "^exec_reply: " "$TMP/contract.txt" >/dev/null

"$CLI" kernel ws create --ws-id ws_sem_02 >"$TMP/ws_create.txt" 2>&1
assert_one_line "$TMP/ws_create.txt"
rg -n "^kernel: ws created \\(ws_id=ws_sem_02\\)$" "$TMP/ws_create.txt" >/dev/null

"$CLI" kernel ws destroy --ws-id ws_sem_02 >"$TMP/ws_destroy.txt" 2>&1 || true

set +e
"$CLI" boot artifact_audit >"$TMP/nyi.txt" 2>&1
RC_NYI=$?
set -e
assert_one_line "$TMP/nyi.txt"
if [[ "$RC_NYI" -eq 10 ]]; then
  rg -n "NOT_IMPLEMENTED: boot: artifact(_| )audit" "$TMP/nyi.txt" >/dev/null
elif [[ "$RC_NYI" -eq 40 ]]; then
  rg -n "^SERVER_UNAVAILABLE: root socket unreachable$" "$TMP/nyi.txt" >/dev/null
else
  echo "expected rc=10 (nyi) or rc=40 (runtime unavailable), got $RC_NYI"
  cat "$TMP/nyi.txt"
  exit 1
fi

"$CLI" lifecycle down >/dev/null 2>&1 || true
set +e
"$CLI" root ping >"$TMP/offline.txt" 2>&1
RC_OFF=$?
set -e
if [[ "$RC_OFF" -ne 40 ]]; then
  echo "expected rc=40 for server unavailable, got $RC_OFF"
  cat "$TMP/offline.txt"
  exit 1
fi
assert_one_line "$TMP/offline.txt"
rg -n "^SERVER_UNAVAILABLE: root socket unreachable$" "$TMP/offline.txt" >/dev/null

echo "porcelain_v1_guardrail: ok"
