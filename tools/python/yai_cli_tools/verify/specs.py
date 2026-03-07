from __future__ import annotations

from pathlib import Path

from yai_cli_tools.util import ok, fail, repo_root


def run() -> int:
    """
    Compatibility check phase (historical module name retained).
    This is verify-only and must not enforce structural pinning.
    """
    root = repo_root()

    # Required local compatibility surfaces.
    required = [
        root / "tools" / "manifests" / "verify.v1.json",
        root / "docs" / "development" / "cli-compatibility-model.md",
    ]
    missing = [str(p.relative_to(root)) for p in required if not p.exists()]
    if missing:
        return fail(f"missing compatibility assets: {', '.join(missing)}")

    # Optional local law checkout is informational only.
    law = root / "deps" / "yai-law"
    if law.exists():
        ok("compatibility target available: deps/yai-law (optional)")
    else:
        ok("compatibility target not vendored locally (allowed)")

    ok("compatibility checks passed")
    return 0
