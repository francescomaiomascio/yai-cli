# Specs Pinning

## Regola 1: Pin esplicito

`deps/yai-specs` e' un pin (commit o tag), non una reference flottante.

## Regola 2: Compatibilita' dichiarata

`yai-cli` deve dichiarare quali versioni specs supporta.
Riferimento: `COMPATIBILITY.md`.

## Regola 3: No drift

Se `yai-specs` cambia, `yai-cli` deve adeguarsi.
Comandi o comportamenti fuori contratto non sono accettati.
