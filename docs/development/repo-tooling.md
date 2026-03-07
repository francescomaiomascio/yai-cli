# Repo Tooling

`tools/` hosts CLI automation.

## Verify model

`yai-cli-tools verify` runs compatibility-oriented phases:
- `layout`
- `compatibility`
- `build`
- `tests`
- `smoke` (full profile)

`compatibility` is verify-only and must not be interpreted as structural pinning.
