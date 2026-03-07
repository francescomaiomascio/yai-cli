#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
CLI="$ROOT/dist/bin/yai"

TMP="$(mktemp -d /tmp/yai-cli-ghost-XXXXXX)"
trap 'rm -rf "$TMP"' EXIT

assert_no_ghost() {
  local f="$1"
  if rg -n "unknown command group|invalid_arguments_or_contract_violation" "$f" >/dev/null; then
    echo "ghost output detected in $f"
    cat "$f"
    exit 1
  fi
}

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
assert_no_ghost "$TMP/up.txt"

set +e
"$CLI" root ping >"$TMP/root_ping.txt" 2>&1
RC_PING=$?
set -e
if [[ "$RC_PING" -ne 0 && "$RC_PING" -ne 40 ]]; then
  echo "expected root ping rc 0 or 40, got $RC_PING"
  cat "$TMP/root_ping.txt"
  exit 1
fi
assert_no_ghost "$TMP/root_ping.txt"

set +e
"$CLI" --verbose-contract root ping >"$TMP/verbose_ping.txt" 2>&1
RC_CONTRACT=$?
set -e
if [[ "$RC_CONTRACT" -ne 0 && "$RC_CONTRACT" -ne 40 ]]; then
  echo "expected verbose-contract root ping rc 0 or 40, got $RC_CONTRACT"
  cat "$TMP/verbose_ping.txt"
  exit 1
fi
if [[ "$(wc -l < "$TMP/verbose_ping.txt")" -ne 2 ]]; then
  echo "verbose-contract must print exactly 2 lines"
  cat "$TMP/verbose_ping.txt"
  exit 1
fi
rg -n "^control_call: " "$TMP/verbose_ping.txt" >/dev/null
rg -n "^exec_reply: " "$TMP/verbose_ping.txt" >/dev/null
assert_no_ghost "$TMP/verbose_ping.txt"

set +e
"$CLI" boot artifact_audit >"$TMP/nyi.txt" 2>&1
RC_NYI=$?
set -e
if [[ "$RC_NYI" -eq 10 ]]; then
  assert_no_ghost "$TMP/nyi.txt"
  rg -n "^NOT IMPLEMENTED$" "$TMP/nyi.txt" >/dev/null
elif [[ "$RC_NYI" -eq 40 ]]; then
  assert_no_ghost "$TMP/nyi.txt"
  rg -n "^SERVER UNAVAILABLE$" "$TMP/nyi.txt" >/dev/null
else
  echo "expected rc=10 (nyi) or rc=40 (runtime unavailable), got $RC_NYI"
  cat "$TMP/nyi.txt"
  exit 1
fi

"$CLI" lifecycle down >"$TMP/down.txt" 2>&1 || true
set +e
"$CLI" root ping >"$TMP/offline_ping.txt" 2>&1
RC_OFF=$?
set -e
if [[ "$RC_OFF" -ne 40 ]]; then
  echo "expected rc=40 for server unavailable, got $RC_OFF"
  cat "$TMP/offline_ping.txt"
  exit 1
fi
assert_no_ghost "$TMP/offline_ping.txt"
rg -n "^SERVER UNAVAILABLE$" "$TMP/offline_ping.txt" >/dev/null

set +e
"$CLI" wat ping >"$TMP/invalid.txt" 2>&1
RC_INV=$?
set -e
if [[ "$RC_INV" -ne 20 ]]; then
  echo "expected rc=20 for invalid command, got $RC_INV"
  cat "$TMP/invalid.txt"
  exit 1
fi
rg -n "Unknown command group" "$TMP/invalid.txt" >/dev/null
rg -n "yai help --groups|yai help" "$TMP/invalid.txt" >/dev/null

echo "ghost_guardrail: ok"
