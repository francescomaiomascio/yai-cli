from __future__ import annotations

from yai_cli_tools.util import run, fail, ok


def run_phase() -> int:
    rc = run(["make", "test"])
    if rc != 0:
        return fail("make test failed")
    ok("tests passed")
    return 0
