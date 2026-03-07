#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
CLI="$ROOT/dist/bin/yai"
TMP="$(mktemp -d /tmp/yai-cli-operator-pack-XXXXXX)"
trap 'rm -rf "$TMP"' EXIT

"$CLI" doctor env >"$TMP/doctor_env.txt" 2>&1 || true
rg -n "doctor" "$TMP/doctor_env.txt" >/dev/null

"$CLI" doctor runtime >"$TMP/doctor_runtime.txt" 2>&1 || true
rg -n "doctor" "$TMP/doctor_runtime.txt" >/dev/null

"$CLI" doctor workspace >"$TMP/doctor_workspace.txt" 2>&1 || true
rg -n "doctor" "$TMP/doctor_workspace.txt" >/dev/null

"$CLI" doctor all >"$TMP/doctor_all.txt" 2>&1 || true
rg -n "doctor" "$TMP/doctor_all.txt" >/dev/null

"$CLI" inspect workspace >"$TMP/inspect_workspace.txt" 2>&1 || true
rg -n "inspect" "$TMP/inspect_workspace.txt" >/dev/null

"$CLI" inspect runtime >"$TMP/inspect_runtime.txt" 2>&1 || true
rg -n "inspect" "$TMP/inspect_runtime.txt" >/dev/null

"$CLI" inspect catalog >"$TMP/inspect_catalog.txt" 2>&1 || true
rg -n "inspect" "$TMP/inspect_catalog.txt" >/dev/null

"$CLI" verify law >"$TMP/verify_law.txt" 2>&1 || true
rg -n "verify" "$TMP/verify_law.txt" >/dev/null

"$CLI" verify registry >"$TMP/verify_registry.txt" 2>&1 || true
rg -n "verify" "$TMP/verify_registry.txt" >/dev/null

"$CLI" verify workspace >"$TMP/verify_workspace.txt" 2>&1 || true
rg -n "verify" "$TMP/verify_workspace.txt" >/dev/null

"$CLI" verify alignment >"$TMP/verify_alignment.txt" 2>&1 || true
rg -n "verify" "$TMP/verify_alignment.txt" >/dev/null

if command -v jq >/dev/null 2>&1; then
  "$CLI" doctor all --json >"$TMP/doctor_all.json" 2>&1 || true
  jq -e . "$TMP/doctor_all.json" >/dev/null

  "$CLI" inspect workspace --json >"$TMP/inspect_workspace.json" 2>&1 || true
  jq -e . "$TMP/inspect_workspace.json" >/dev/null

  "$CLI" verify alignment --json >"$TMP/verify_alignment.json" 2>&1 || true
  jq -e . "$TMP/verify_alignment.json" >/dev/null
fi

echo "operator_capability_pack_guardrail: ok"
