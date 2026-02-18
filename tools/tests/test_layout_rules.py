from __future__ import annotations

from pathlib import Path


def test_no_scripts_dir() -> None:
    root = Path(__file__).resolve().parents[2]
    assert not (root / "scripts").exists()
