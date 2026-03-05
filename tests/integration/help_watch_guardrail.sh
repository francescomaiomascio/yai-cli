#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
CLI="$ROOT/dist/bin/yai"
TMP="$(mktemp -d /tmp/yai-cli-help-watch-XXXXXX)"
trap 'rm -rf "$TMP"' EXIT

"$CLI" help >"$TMP/help.txt" 2>&1
rg -n "^YAI Operator CLI$" "$TMP/help.txt" >/dev/null
rg -n "^Usage:$" "$TMP/help.txt" >/dev/null
rg -n "^Command Groups:$" "$TMP/help.txt" >/dev/null

"$CLI" help root >"$TMP/help_root.txt" 2>&1
rg -n "^root$" "$TMP/help_root.txt" >/dev/null
rg -n "^Commands:$" "$TMP/help_root.txt" >/dev/null

"$CLI" help root ping >"$TMP/help_root_ping.txt" 2>&1
rg -n "^Command:$" "$TMP/help_root_ping.txt" >/dev/null
rg -n "^  root ping$" "$TMP/help_root_ping.txt" >/dev/null
rg -n "^Usage:$" "$TMP/help_root_ping.txt" >/dev/null

YAI_PAGER=1 "$CLI" --no-pager help root >"$TMP/help_no_pager.txt" 2>&1
rg -n "^root$" "$TMP/help_no_pager.txt" >/dev/null

set +e
timeout 3 "$CLI" watch root ping >"$TMP/watch.txt" 2>&1
RC_WATCH=$?
set -e
if [[ "$RC_WATCH" -ne 0 && "$RC_WATCH" -ne 124 ]]; then
  echo "unexpected watch rc=$RC_WATCH"
  cat "$TMP/watch.txt"
  exit 1
fi
rg -n "YAI Watch Mode" "$TMP/watch.txt" >/dev/null
rg -n "Command: root ping" "$TMP/watch.txt" >/dev/null

echo "help_watch_guardrail: ok"
