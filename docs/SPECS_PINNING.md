# Specs Pinning

## Principle

`yai-cli` is a consumer of `yai-specs` and must use explicit pinning.

## Guidance

- Pin to a known commit/release of `deps/yai-specs`.
- Avoid floating references for production rollouts.
- Validate compatibility before updating the pin.
