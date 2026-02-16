# Versioning

`yai-cli` usa Semantic Versioning.

## SemVer

- `MAJOR`: cambiamenti incompatibili lato CLI pubblico
- `MINOR`: aggiunte backward-compatible
- `PATCH`: fix e miglioramenti non-breaking

## Coordinamento con Specs

Ogni rilascio CLI deve essere valutato rispetto al pin `deps/yai-specs`.
Breaking lato contratto richiede bump MAJOR o allineamento esplicito del range compatibile.
