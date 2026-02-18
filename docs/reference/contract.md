# Contract Boundary

`yai-cli` implements and consumes pinned specs in `deps/yai-specs`.
Specs in that directory are the contract source of truth.

## Canonical References

- Commands contract: `deps/yai-specs/specs/cli/schema/commands.v1.json`
- Commands schema: `deps/yai-specs/specs/cli/schema/commands.schema.json`
- Protocol envelope/IDs: `deps/yai-specs/specs/protocol/include/transport.h`, `deps/yai-specs/specs/protocol/include/yai_protocol_ids.h`
- Errors/auth/roles: `deps/yai-specs/specs/protocol/include/errors.h`, `deps/yai-specs/specs/protocol/include/auth.h`, `deps/yai-specs/specs/protocol/include/roles.h`

## Rule

No command/protocol semantics may be invented outside pinned specs.
If drift exists: open an issue and realign CLI/specs before release.
