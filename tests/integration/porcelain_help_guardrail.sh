#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
CLI="$ROOT/dist/bin/yai"
TMP="$(mktemp -d /tmp/yai-cli-help-guard-XXXXXX)"
trap 'rm -rf "$TMP"' EXIT

"$CLI" help --groups >"$TMP/groups.txt" 2>&1
[[ -s "$TMP/groups.txt" ]]
rg -n "root|kernel|boot" "$TMP/groups.txt" >/dev/null

"$CLI" help root >"$TMP/root.txt" 2>&1
rg -n "^root$" "$TMP/root.txt" >/dev/null
rg -n "ping" "$TMP/root.txt" >/dev/null

"$CLI" lifecycle up >/dev/null 2>&1 || true
"$CLI" root ping >"$TMP/root_ping.txt" 2>&1 || true
if rg -n "unknown command group|try: yai help --groups|invalid_arguments_or_contract_violation" "$TMP/root_ping.txt" >/dev/null; then
  echo "help garbage detected on normal command path"
  cat "$TMP/root_ping.txt"
  exit 1
fi

echo "porcelain_help_guardrail: ok"
