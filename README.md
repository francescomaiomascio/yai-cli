# YAI CLI (C)

YAI CLI is the command surface of the YAI platform.

It exposes governed command behavior for invoking, inspecting, and operating YAI under explicit law and aligned interfaces.

This repository contains the canonical CLI implementation of the platform.

## Platform position

`yai-law` → `yai-sdk` → `yai-cli` → `yai` → `yai-ops`

Law defines the rules. The SDK carries the interface. The CLI exposes the surface.

## Design posture

- **Commands follow law**
- **Behavior is explicit**
- **Side effects are controlled**
- **Outputs are reviewable**
- **Compatibility is tracked**

## Scope

This repository owns the canonical command implementation for YAI.

It does not own normative contract semantics (`yai-law`), platform implementation (`yai`), or shared governance tooling (`yai-infra`).

## Contract discipline

Pinned dependencies include:

- `deps/yai-law/registry/commands.v1.json`
- `deps/yai-law/registry/schema/commands.v1.schema.json`
- `deps/yai-law/contracts/protocol/include/*`
- `deps/yai-sdk/include/yai_sdk/public.h`

Divergence from pinned law or aligned SDK interfaces is an implementation defect.

## Build

```bash
make
```

## Outputs

- `dist/bin/yai`
- `dist/bin/yai-cli`

## Usage

```bash
./dist/bin/yai --help
./dist/bin/yai ws workspace create --ws-id demo
./dist/bin/yai ws use demo
./dist/bin/yai gov decision status
./dist/bin/yai inspect bundle status
```

## Documentation

- `docs/README.md`

## License

Apache-2.0. See `LICENSE`, `NOTICE`, and `THIRD_PARTY_NOTICES.md`.