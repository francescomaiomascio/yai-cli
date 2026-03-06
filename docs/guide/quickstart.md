# Quickstart

## 1) Start runtime

```bash
./dist/bin/yai lifecycle up
```

## 2) Create and bind a workspace

```bash
./dist/bin/yai kernel ws create --ws-id demo_ws
./dist/bin/yai ws use demo_ws
./dist/bin/yai ws current
```

`ws current` reports the current binding plus runtime state (`state`, `root_path`) when available.

## 3) Run workspace-scoped commands without repeating `--ws-id`

```bash
./dist/bin/yai gov decision status
./dist/bin/yai inspect bundle status
```

The CLI resolves workspace using this precedence:

1. explicit `--ws-id <id>`
2. current binding (`yai ws use <id>`)
3. error when unresolved for workspace-scoped commands

## 4) Override binding explicitly

```bash
./dist/bin/yai gov decision status --ws-id other_ws
```

Explicit `--ws-id` always overrides current binding.

## 5) Clear binding

```bash
./dist/bin/yai ws clear
```
