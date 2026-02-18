from __future__ import annotations

import os
import shutil
import subprocess
from pathlib import Path


def repo_root() -> Path:
    return Path(__file__).resolve().parents[3]


def run(cmd: list[str], cwd: Path | None = None) -> int:
    return subprocess.run(cmd, cwd=str(cwd or repo_root()), check=False).returncode


def has_cmd(name: str) -> bool:
    return shutil.which(name) is not None


def print_phase(name: str) -> None:
    print(f"== {name}")


def fail(msg: str) -> int:
    print(f"FAIL: {msg}")
    return 1


def ok(msg: str) -> None:
    print(f"OK: {msg}")
