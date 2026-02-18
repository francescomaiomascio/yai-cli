from __future__ import annotations

from pathlib import Path

from yai_cli_tools.util import ok, fail, repo_root


REQUIRED = [
    "tools/VERSION",
    "tools/manifests/verify.v1.json",
    "tools/manifests/ci.v1.json",
    "include/yai_cli",
    "src",
    "tests",
]


def run() -> int:
    root = repo_root()
    if (root / "scripts").exists():
        return fail("scripts directory must not exist")

    missing = [p for p in REQUIRED if not (root / p).exists()]
    if missing:
        return fail(f"missing required paths: {', '.join(missing)}")

    ok("layout checks passed")
    return 0
