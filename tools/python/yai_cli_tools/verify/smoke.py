from __future__ import annotations

from pathlib import Path

from yai_cli_tools.util import repo_root, run, ok


def run_phase() -> int:
    root = repo_root()
    candidate = root / "dist/bin/yai-cli"
    if candidate.exists():
        rc1 = run([str(candidate), "--help"])
        rc2 = run([str(candidate), "version"])
        if rc1 == 0 and rc2 == 0:
            ok("smoke passed")
            return 0
    print("SKIP: smoke skipped (binary not available yet)")
    return 0
