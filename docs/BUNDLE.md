# Bundle

## Concept

Il bundle ufficiale e' versione-pinned e firmabile (oggi il processo puo' essere manuale).
Obiettivo: distribuire un insieme coerente di binari + specs senza drift.

## Layout (attuale)

- CLI bin: `dist/bin/yai-cli`
- Specs pinned: `deps/yai-specs/`

## Runtime Bundle (futuro, menzione)

In un bundle runtime completo verranno inclusi anche i core bins (`yai/dist/bin/*`).
Questa repository non implementa quella parte: la documenta soltanto.
