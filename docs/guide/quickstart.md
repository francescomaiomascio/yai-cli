# Quickstart

## 1. Discover surface

```bash
yai --help
yai help
```

## 2. Explore domains

```bash
yai help run
yai help gov
yai help verify
```

## 3. Drill down to operations

```bash
yai help run kernel ping
yai help gov decision
yai help gov decision status
```

## 4. Advanced visibility

```bash
yai help --all
yai help --plumbing
```

## 5. Attach a workspace context

```bash
yai ws workspace create --ws-id demo
yai ws use demo
yai ws current
```

## 6. Work without repeating --ws-id

```bash
yai gov decision status
yai inspect bundle status
```

Explicit override always wins:

```bash
yai gov decision status --ws-id other_demo
```

## 7. Use watch mode for live checks

```bash
yai watch run kernel ping --interval-ms 1000
NO_COLOR=1 yai watch run kernel ping --count 3 --interval-ms 200
```

## 8. Run Operator Capability Pack

```bash
yai doctor env
yai doctor runtime
yai doctor workspace
yai doctor all

yai inspect workspace
yai inspect runtime
yai inspect catalog

yai verify law
yai verify registry
yai verify workspace
yai verify alignment
```

Machine mode:

```bash
yai doctor all --json
yai inspect workspace --json
yai verify alignment --json
```
