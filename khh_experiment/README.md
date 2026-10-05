# kHeavyHash-as-AI-primitive experiment

Software-only test of whether the **final** kHeavyHash/cSHAKE output (or black-box
mining behavior) retains task-useful information. Full write-up and verdict:
`../docs/kHeavyHash-as-AI-primitive-experiment.md`.

| file | purpose |
|---|---|
| `kheavyhash.py` | exact Kaspa kHeavyHash (Keccak-f1600, SHAKE256, cSHAKE256, xoshiro256++ matrix gen, heavy_hash stages). Self-validates vs `hashlib` and the NIST cSHAKE256 vector. |
| `experiment.py` | representation experiment (input → v → raw M·v → norm M·v → pre-cSHAKE → final), tiny-model family, multi-job stacking → `results.json`. |
| `oracle.py` | black-box predicate `kHeavyHash<target`: hit-rate / nonce / search-time dependence on label, MI + permutation null → `oracle_results.json`. |
| `plots.py` | `fig1_accuracy_cascade.png`, `fig2_stage_cascade.png`, `fig3_oracle.png`. |

```sh
python3 kheavyhash.py && python3 experiment.py && python3 oracle.py && python3 plots.py
```

Result in one line: **the matrix op `M·v` is a useful ML feature (claim A), the
final cSHAKE output is not (claim B, refuted), so a faster ASIC cannot help on the
normal interface (claim C, impossible).** Everything useful is pre-cSHAKE — the
state the KS0 protocol does not expose.
