# CLI Dependency Matrix

| area/file | current role | target role | action | verify impact | compatibility impact | follow-up needed |
|---|---|---|---|---|---|---|
| `docs/development/specs-pinning.md` | pinning-centric doc | compatibility model doc (legacy title) | rewrite | clarifies verify intent | high | optional rename file later |
| `tools/python/yai_cli_tools/verify/specs.py` | pin cleanliness check | compatibility check phase (verify-only) | realign | medium | high | keep deprecated alias support |
| `tools/python/yai_cli_tools/verify/law.py` | unclear/empty module | deprecated alias wrapper | keep-as-verify-only | low | low | remove once callers gone |
| `tools/python/yai_cli_tools/verify/layout.py` | layout guard | unchanged layout guard | keep | none | low | none |
| `tools/python/yai_cli_tools/verify/smoke.py` | runtime smoke | unchanged | keep | none | low | none |
| `tools/python/yai_cli_tools/verify/tests.py` | tests phase | unchanged | keep | none | low | none |
| `tools/manifests/ci.v1.json` | includes `specs` phase | includes `compatibility` phase | realign | medium | medium | keep alias fallback in runner |
| `tools/manifests/verify.v1.json` | includes `specs` phase | includes `compatibility` phase | realign | medium | medium | keep alias fallback in runner |
| `tests/integration/output_contract_v1_guardrail.sh` | contract/output guardrail | contract/output guardrail | keep | none | medium | migrate legacy command aliases later |
