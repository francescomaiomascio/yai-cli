#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
CLI="$ROOT/dist/bin/yai"

TMP="$(mktemp -d /tmp/yai-cli-porcelain-XXXXXX)"
trap 'rm -rf "$TMP"' EXIT

"$CLI" lifecycle down >/dev/null 2>&1 || true
set +e
"$CLI" lifecycle up >"$TMP/up.txt" 2>&1
RC_UP=$?
set -e
if [[ "$RC_UP" -ne 0 && "$RC_UP" -ne 40 ]]; then
  echo "expected lifecycle up rc 0 or 40, got $RC_UP"
  cat "$TMP/up.txt"
  exit 1
fi
rg -n "^lifecycle up$" "$TMP/up.txt" >/dev/null
rg -n "^(OK|RUNTIME NOT READY|SERVER UNAVAILABLE)$" "$TMP/up.txt" >/dev/null

set +e
"$CLI" root ping >"$TMP/root_ping.txt" 2>&1
RC_PING=$?
set -e
if [[ "$RC_PING" -ne 0 && "$RC_PING" -ne 40 ]]; then
  echo "expected root ping rc 0 or 40, got $RC_PING"
  cat "$TMP/root_ping.txt"
  exit 1
fi
rg -n "^root ping$" "$TMP/root_ping.txt" >/dev/null
rg -n "^(OK|RUNTIME NOT READY|SERVER UNAVAILABLE)$" "$TMP/root_ping.txt" >/dev/null

set +e
"$CLI" --verbose root ping >"$TMP/verbose.txt" 2>&1
RC_VERBOSE=$?
set -e
if [[ "$RC_VERBOSE" -ne 0 && "$RC_VERBOSE" -ne 40 ]]; then
  echo "expected verbose root ping rc 0 or 40, got $RC_VERBOSE"
  cat "$TMP/verbose.txt"
  exit 1
fi
rg -n "^root ping$" "$TMP/verbose.txt" >/dev/null
rg -n "^Details:$" "$TMP/verbose.txt" >/dev/null
rg -n "^  status=" "$TMP/verbose.txt" >/dev/null
rg -n "^  code=" "$TMP/verbose.txt" >/dev/null
rg -n "^  reason=" "$TMP/verbose.txt" >/dev/null
rg -n "^  command_id=" "$TMP/verbose.txt" >/dev/null
rg -n "^  target_plane=" "$TMP/verbose.txt" >/dev/null

set +e
"$CLI" --json root ping >"$TMP/json.txt" 2>&1
RC_JSON=$?
set -e
if [[ "$RC_JSON" -ne 0 && "$RC_JSON" -ne 40 ]]; then
  echo "expected json root ping rc 0 or 40, got $RC_JSON"
  cat "$TMP/json.txt"
  exit 1
fi
jq -e . "$TMP/json.txt" >/dev/null

set +e
"$CLI" --verbose-contract root ping >"$TMP/contract.txt" 2>&1
RC_CONTRACT=$?
set -e
if [[ "$RC_CONTRACT" -ne 0 && "$RC_CONTRACT" -ne 40 ]]; then
  echo "expected verbose-contract root ping rc 0 or 40, got $RC_CONTRACT"
  cat "$TMP/contract.txt"
  exit 1
fi
if [[ "$(wc -l < "$TMP/contract.txt")" -ne 2 ]]; then
  echo "verbose-contract must print exactly 2 lines"
  cat "$TMP/contract.txt"
  exit 1
fi
rg -n "^control_call: " "$TMP/contract.txt" >/dev/null
rg -n "^exec_reply: " "$TMP/contract.txt" >/dev/null

set +e
"$CLI" boot artifact_audit >"$TMP/nyi.txt" 2>&1
RC_NYI=$?
set -e
if [[ "$RC_NYI" -eq 10 ]]; then
  rg -n "^boot artifact audit$" "$TMP/nyi.txt" >/dev/null
  rg -n "^NOT IMPLEMENTED$" "$TMP/nyi.txt" >/dev/null
elif [[ "$RC_NYI" -eq 40 ]]; then
  rg -n "^boot artifact audit$" "$TMP/nyi.txt" >/dev/null
  rg -n "^SERVER UNAVAILABLE$" "$TMP/nyi.txt" >/dev/null
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
rg -n "^root ping$" "$TMP/offline.txt" >/dev/null
rg -n "^SERVER UNAVAILABLE$" "$TMP/offline.txt" >/dev/null

echo "porcelain_v1_guardrail: ok"
