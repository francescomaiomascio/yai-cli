# Contributing

## Scope

Repo orientato a superficie pubblica CLI e allineamento contrattuale.
Cambiare codice C/H/tests solo quando esplicitamente richiesto dal task.

## Commit Convention

- Commit piccoli e descrittivi
- Un obiettivo per commit
- Niente cambi misti non correlati

## Pull Request Rules

- Spiega cosa cambia e perche'
- Indica impatto su compatibilita' (`COMPATIBILITY.md`)
- Evita PR giganti: preferire PR incrementali

## Minimum Checks

Prima di aprire PR:
- build locale (`make`)
- verifica che working tree non includa artefatti non desiderati
- verifica allineamento con `deps/yai-specs`
