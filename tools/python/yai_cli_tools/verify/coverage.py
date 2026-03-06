import json
from pathlib import Path
import sys

ROOT = Path(__file__).resolve().parents[4]  # .../tools/python/yai_cli_tools/verify -> repo root

LAW_REGISTRY_CANDIDATES = [
    ROOT / "deps" / "yai-sdk" / "deps" / "yai-law" / "registry" / "commands.v1.json",
    ROOT / "deps" / "yai-law" / "registry" / "commands.v1.json",
]

def resolve_law_registry() -> Path | None:
    for p in LAW_REGISTRY_CANDIDATES:
        if p.exists():
            return p
    return None

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

def is_canonical_id(cid: str) -> bool:
    if not cid or not cid.startswith("yai."):
        return False
    parts = cid.split(".")
    return len(parts) == 3 and all(parts)

def main():
    law_registry = resolve_law_registry()
    if law_registry is None:
        print("verify.coverage: FAIL: missing law registry in known locations", file=sys.stderr)
        return 3

    cmds = load_commands(law_registry)
    reg_ids = {cid for cid in (command_id(x) for x in cmds) if cid}
    bad_ids = sorted(cid for cid in reg_ids if not is_canonical_id(cid))
    print(f"verify.coverage: mode=protocol_first registry={len(reg_ids)} bad_ids={len(bad_ids)}")

    if bad_ids:
        print("invalid command ids (sample):")
        for x in bad_ids[:40]:
            print(f"  - {x}")
        print("verify.coverage: FAIL: registry has non-canonical command ids", file=sys.stderr)
        return 2

    return 0

if __name__ == "__main__":
    raise SystemExit(main())
