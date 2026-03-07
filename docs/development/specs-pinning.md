# Compatibility Baseline (replaces specs-pinning)

Status: legacy title retained for continuity.

## Policy

- `yai-cli` must not structurally pin `yai-law`.
- `yai-cli` must not structurally pin `yai-sdk`.
- `yai-cli` declares supported compatibility baselines.
- verify hooks may check compatibility targets, but do not define dependency edges.

## Verify model

Compatibility checks may use:
- local exported baseline artifacts
- optional local `deps/*` copies when present

Absence of local `deps/yai-law` is not by itself a structural failure.
