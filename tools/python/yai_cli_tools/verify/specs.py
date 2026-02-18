from __future__ import annotations

import subprocess

from yai_cli_tools.util import ok, fail, repo_root


def run() -> int:
    root = repo_root()
    specs = root / "deps/yai-specs"
    if not specs.exists():
        return fail("deps/yai-specs not found")

    res = subprocess.run(
        ["git", "status", "--porcelain"],
        cwd=str(specs),
        check=False,
        capture_output=True,
        text=True,
    )
    if res.returncode != 0:
        return fail("cannot read git status in deps/yai-specs")
    if res.stdout.strip():
        return fail("deps/yai-specs is dirty")

    ok("specs pin is present and clean")
    return 0
