# Contract Boundary

`yai-cli` implements and consumes pinned specs in `deps/yai-law`.
Specs in that directory are the contract source of truth.

## Canonical References

- Commands contract: `deps/yai-law/registry/registry/commands.v1.json`
- Commands schema: `deps/yai-law/registry/schema/commands.v1.schema.json`
- Protocol envelope/IDs: `deps/yai-law/law/surfaces/protocol/include/transport.h`, `deps/yai-law/law/surfaces/protocol/include/yai_protocol_ids.h`
- Errors/auth/roles: `deps/yai-law/law/surfaces/protocol/include/errors.h`, `deps/yai-law/law/surfaces/protocol/include/auth.h`, `deps/yai-law/law/surfaces/protocol/include/roles.h`

## Rule

No command/protocol semantics may be invented outside pinned specs.
If drift exists: open an issue and realign CLI/specs before release.
