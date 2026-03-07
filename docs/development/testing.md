# Testing

Core checks:
- `make test`
- integration guardrails under `tests/integration/`

## Guardrail intent

Guardrails validate behavioral surface and output/contract stability.
They should not encode structural repository dependency assumptions.
