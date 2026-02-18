from __future__ import annotations

from yai_cli_tools.util import has_cmd


def run() -> int:
    missing = []
    for cmd in ("make", "python3"):
        if not has_cmd(cmd):
            missing.append(cmd)

    cc_ok = has_cmd("cc") or has_cmd("clang") or has_cmd("gcc")
    if not cc_ok:
        missing.append("cc|clang|gcc")

    if missing:
        print(f"FAIL: missing required tools: {', '.join(missing)}")
        return 1

    if not has_cmd("doxygen"):
        print("WARN: doxygen not found (docs target may fail)")

    print("OK: environment checks passed")
    return 0
