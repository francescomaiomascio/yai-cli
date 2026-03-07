# CLI Compatibility Model

## Role

`yai-cli` is an autonomous operator surface consumer.

## Dependency rules

- no structural pin to `yai-law`
- no structural pin to `yai-sdk`
- compatibility declarations are mandatory
- verify-only checks are allowed and encouraged

## Verify-only distinction

A verify check may inspect compatibility targets (schemas/contracts/baselines) but must not require live repo dependency as execution prerequisite.

## Inputs allowed

- exported compatibility artifacts
- local compatibility manifests
- optional local deps copies (best-effort)

## Inputs forbidden as hard requirement

- mandatory live `yai-law` repository checkout
- mandatory satellite-to-satellite pinning
