# Contract Boundary

`yai-cli` consumes contract semantics as a compatibility consumer.
It does not own normative law and does not structurally pin source repositories.

## Canonical references

- command and protocol semantics are defined by `yai-law`
- SDK API semantics are defined by `yai-sdk`

## CLI rule

No local command/protocol semantics may diverge from declared compatibility targets.
Verify hooks check conformance but do not create structural dependency edges.
