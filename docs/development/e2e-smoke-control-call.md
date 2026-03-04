# E2E Smoke — Control Call Spine v1

This runbook validates the CLI -> SDK -> control.call execution spine.

## Offline checks

```bash
make
./dist/bin/yai help --all
./dist/bin/yai help yai.kernel.ws
```

Expected:
- help list renders command ids from law registry
- command help resolves canonical id

## Runtime checks

```bash
./dist/bin/yai root ping
./dist/bin/yai kernel ping
./dist/bin/yai kernel ws list
```

Expected:
- `root ping` / `kernel ping` succeed when runtime is available
- a registered-but-not-implemented command returns deterministic non-success (`nyi` path), never "unknown command"

## Deterministic failure checks

With runtime down:

```bash
YAI_ROOT_SOCK=/tmp/yai-root-sock-does-not-exist.sock ./dist/bin/yai kernel ping
```

Expected:
- deterministic failure with `server unavailable`
