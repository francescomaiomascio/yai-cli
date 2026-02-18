# Repo Tooling

`tools/` is the canonical location for repository automation.

Rules:
- `tools/bin/*` wrappers are intentionally thin and contain no business logic.
- Python implementation lives in `tools/python/yai_cli_tools`.
- CI executes the same verify command used locally.

Usage:
- `tools/bin/yai-cli-verify --profile ci`
- `tools/bin/yai-cli-verify --profile full`
- `tools/bin/yai-cli-doctor`
- `tools/bin/yai-cli-release bump`
