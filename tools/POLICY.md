# Tools Policy

- No `scripts` directory is allowed.
- No logic in `tools/bin/*` wrappers.
- Tool implementation lives in `tools/python/yai_cli_tools/*`.
- CI must call `tools/bin/yai-cli-verify`.
- `deps/yai-specs` is pinned and must remain untouched.
