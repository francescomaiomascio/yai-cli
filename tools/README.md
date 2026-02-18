# Tools

Canonical, versioned automation for `yai-cli`.

Entrypoints:
- `tools/bin/yai-cli-verify --profile ci|full`
- `tools/bin/yai-cli-doctor`
- `tools/bin/yai-cli-release bump`

Architecture:
- `tools/bin/*`: thin wrappers only.
- `tools/python/yai_cli_tools/*`: implementation.
- `tools/manifests/*`: ordered verify phases.
