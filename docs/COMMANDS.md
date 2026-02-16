# Commands

## Source of Truth

La source-of-truth dei comandi e':
- `deps/yai-specs/cli/commands.v1.json`

Lo schema associato e':
- `deps/yai-specs/cli/commands.schema.json`

## Come leggere

1. `commands.v1.json` definisce il set comandi e la semantica contrattuale.
2. `commands.schema.json` definisce la validazione formale del documento.

## Regola Operativa

Nessun comando "inventato" fuori dalle specs.
Se c'e' drift tra CLI e specs: aprire issue e allineare prima del rilascio.
