import json
import re
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[4]  # .../tools/python/yai_cli_tools/verify -> repo root

LAW_REGISTRY = ROOT / "deps" / "yai-sdk" / "deps" / "yai-law" / "registry" / "commands.v1.json"
OPS_DISPATCH_C = ROOT / "deps" / "yai-sdk" / "src" / "ops" / "ops_dispatch.c"

def load_commands(path: Path):
    obj = json.loads(path.read_text(encoding="utf-8"))
    if isinstance(obj, list):
        return obj
    for k in ("items", "commands", "entries"):
        v = obj.get(k)
        if isinstance(v, list):
            return v
    # fallback: empty
    return []

def command_id(item):
    if isinstance(item, dict):
        return item.get("id") or item.get("command_id") or item.get("key")
    return None

def parse_mapped_ids_from_ops_dispatch(path: Path):
    txt = path.read_text(encoding="utf-8", errors="replace")
    # extract {"yai.xxx.yyy", ...}
    ids = set(re.findall(r'"\s*(yai\.[a-z0-9_.-]+)\s*"', txt))
    # filter out obvious non-command strings if ever present
    return {s for s in ids if s.startswith("yai.")}

def main():
    if not LAW_REGISTRY.exists():
        print(f"verify.coverage: FAIL: missing law registry at {LAW_REGISTRY}", file=sys.stderr)
        return 3
    if not OPS_DISPATCH_C.exists():
        print(f"verify.coverage: FAIL: missing ops dispatch at {OPS_DISPATCH_C}", file=sys.stderr)
        return 3

    cmds = load_commands(LAW_REGISTRY)
    reg_ids = {cid for cid in (command_id(x) for x in cmds) if cid}

    mapped_ids = parse_mapped_ids_from_ops_dispatch(OPS_DISPATCH_C)

    implemented = sorted(reg_ids & mapped_ids)
    missing = sorted(reg_ids - mapped_ids)
    extra = sorted(mapped_ids - reg_ids)

    print(f"verify.coverage: registry={len(reg_ids)} mapped={len(mapped_ids)} implemented={len(implemented)} missing={len(missing)} extra={len(extra)}")

    # Print a small, useful sample
    if implemented:
        print("implemented (sample):")
        for x in implemented[:20]:
            print(f"  - {x}")

    if extra:
        print("extra (mapped but not in registry):")
        for x in extra[:20]:
            print(f"  - {x}")

    # In early bootstrap, missing will be huge; treat as WARN unless strict requested.
    strict = "--strict" in sys.argv
    if missing:
        print("missing (sample):")
        for x in missing[:40]:
            print(f"  - {x}")
        if strict:
            print("verify.coverage: FAIL: missing mapped handlers for some registry commands", file=sys.stderr)
            return 2
        else:
            print("verify.coverage: WARN: registry contains commands not yet mapped (expected in bootstrap phase)")
            return 0

    return 0

if __name__ == "__main__":
    raise SystemExit(main())
