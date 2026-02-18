from __future__ import annotations

import json
from pathlib import Path


def test_manifests_have_phases() -> None:
    root = Path(__file__).resolve().parents[2]
    for name in ("verify.v1.json", "ci.v1.json"):
        data = json.loads((root / "tools/manifests" / name).read_text(encoding="utf-8"))
        assert isinstance(data.get("phases"), list)
        assert data["phases"]
