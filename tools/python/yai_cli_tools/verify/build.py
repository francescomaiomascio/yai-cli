from __future__ import annotations

from yai_cli_tools.util import run, fail, ok


def run_phase() -> int:
    if run(["make", "clean"]) != 0:
        return fail("make clean failed")
    if run(["make"]) != 0:
        return fail("make failed")
    ok("build passed")
    return 0
