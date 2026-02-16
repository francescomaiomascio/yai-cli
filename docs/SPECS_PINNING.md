# Specs Pinning

## Rule 1: Explicit pin

`deps/yai-specs` is a pin (commit or tag), not a floating reference.

## Rule 2: Declared compatibility

`yai-cli` must declare which specs versions it supports.
Reference: `COMPATIBILITY.md`.

## Rule 3: No drift

If `yai-specs` changes, `yai-cli` must adapt.
Out-of-contract behavior is not acceptable.
