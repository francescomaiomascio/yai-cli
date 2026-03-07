#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
CLI="$ROOT/dist/bin/yai"
TMP="$(mktemp -d /tmp/yai-cli-help-v1-XXXXXX)"
trap 'rm -rf "$TMP"' EXIT

"$CLI" help --groups >"$TMP/groups.txt" 2>&1
rg -n "^YAI Command Surface$" "$TMP/groups.txt" >/dev/null
rg -n "^Main Surface Commands:$" "$TMP/groups.txt" >/dev/null
rg -n "ws|run|gov|verify|inspect|bundle|config|doctor|watch|help|version" "$TMP/groups.txt" >/dev/null

"$CLI" help run >"$TMP/help_run.txt" 2>&1
rg -n "^run$" "$TMP/help_run.txt" >/dev/null
rg -n "^Topics:$" "$TMP/help_run.txt" >/dev/null
rg -n "root|engine|lifecycle" "$TMP/help_run.txt" >/dev/null

set +e
"$CLI" run >"$TMP/run_missing_subcommand.txt" 2>&1
RC_RUN=$?
set -e
if [[ "$RC_RUN" -ne 20 ]]; then
  echo "expected rc=20 for missing run subcommand, got $RC_RUN"
  cat "$TMP/run_missing_subcommand.txt"
  exit 1
fi
rg -n "^BAD ARGS$" "$TMP/run_missing_subcommand.txt" >/dev/null

set +e
"$CLI" foo ping >"$TMP/unknown_group.txt" 2>&1
RC_GROUP=$?
set -e
if [[ "$RC_GROUP" -ne 20 ]]; then
  echo "expected rc=20 for unknown group, got $RC_GROUP"
  cat "$TMP/unknown_group.txt"
  exit 1
fi
rg -n "^BAD ARGS$" "$TMP/unknown_group.txt" >/dev/null
rg -n "^Unknown command group: foo$" "$TMP/unknown_group.txt" >/dev/null
rg -n "^Hint: Run: yai help --groups$" "$TMP/unknown_group.txt" >/dev/null

"$CLI" help gov decision >"$TMP/help_gov_decision.txt" 2>&1
rg -n "^gov decision$" "$TMP/help_gov_decision.txt" >/dev/null
rg -n "^Operations:$" "$TMP/help_gov_decision.txt" >/dev/null
rg -n "make|status|trace" "$TMP/help_gov_decision.txt" >/dev/null

echo "help_guardrail: ok"
