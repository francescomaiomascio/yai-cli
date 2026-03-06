#!/usr/bin/env bash
set -euo pipefail

BIN="${1:-./dist/bin/yai}"

echo "[guardrail] workspace attached context"

"$BIN" ws clear >/dev/null 2>&1 || true

if "$BIN" ws current >/tmp/yai_ws_current.out 2>&1; then
  echo "expected ws current to fail when no workspace selected"
  exit 1
fi

if ! grep -q "No workspace selected" /tmp/yai_ws_current.out; then
  echo "expected deterministic no-workspace message"
  cat /tmp/yai_ws_current.out
  exit 1
fi

echo "[ok] workspace attached context guardrail"
