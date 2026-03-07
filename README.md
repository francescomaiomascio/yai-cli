# YAI CLI (C)

YAI CLI is the operator surface consumer of the YAI ecosystem.

## Platform role

- `yai-law`: normative authority source
- `yai-sdk`: programmatic surface
- `yai-cli`: operator command surface
- `yai`: integrated runtime

## Dependency posture

- `yai-cli` does not structurally pin `yai-law`.
- `yai-cli` does not structurally pin `yai-sdk`.
- `yai-cli` declares compatibility and runs verify-only checks.

Verify hooks are compatibility checks, not repository dependency edges.

## Build

```bash
make
```

## Outputs

- `dist/bin/yai`
- `dist/bin/yai-cli`

## Docs

- `docs/README.md`
- `docs/development/cli-compatibility-model.md`
- `docs/development/cli-dependency-matrix.md`
