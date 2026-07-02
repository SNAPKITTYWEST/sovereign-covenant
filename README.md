<p align="center">
<img src="https://raw.githubusercontent.com/SNAPKITTYWEST/SNAPKITTYWEST/main/bobs-games/assets/voxel-snapkitty.svg" width="128" />
</p>

<h1 align="center">SOVEREIGN COVENANT</h1>

<p align="center">
1928 Moorish Divine Covenant Trust Structure<br>
Prophet Noble Drew Ali — Moorish Science Temple of America
</p>

<p align="center">
<code>Love · Truth · Peace · Freedom · Justice</code>
</p>

---

## What This Is

A C library implementing the **Divine Constitution and By-Laws** of the Moorish Science Temple of America (1928) as a programmable covenant trust structure.

Not a contract. A covenant. It runs with the people.

## Architecture

```
┌─────────────────────────────────────────────┐
│            MOORISH NATION                    │
│  "A Nation within a Nation"                 │
│                                             │
│  ┌─────────────────────────────────────┐   │
│  │         GRAND SHEIK                  │   │
│  │  "In power to make and enforce law"  │   │
│  │  Authority: observes 5 principles    │   │
│  └──────────────┬──────────────────────┘   │
│                 │                           │
│  ┌──────────────┴──────────────────────┐   │
│  │        COVENANT CHAIN                │   │
│  │  Write Once Read Many                │   │
│  │  Each seal → previous hash           │   │
│  │  Tamper-evident                      │   │
│  └──────────────┬──────────────────────┘   │
│                 │                           │
│  ┌──────────────┴──────────────────────┐   │
│  │     SUBORDINATE TEMPLES              │   │
│  │  Each chartered under Grand Temple   │   │
│  │  Each observes 5 principles          │   │
│  └─────────────────────────────────────┘   │
│                                             │
│  ┌─────────────────────────────────────┐   │
│  │    FIVE DIVINE PRINCIPLES            │   │
│  │  Love · Truth · Peace · Freedom      │   │
│  │  Justice                             │   │
│  └─────────────────────────────────────┘   │
└─────────────────────────────────────────────┘
```

## The Five Principles

```c
typedef enum {
    LOVE    = 0,  // "All is Love"
    TRUTH   = 1,  // "Truth is the key"
    PEACE   = 2,  // "Peace be still"
    FREEDOM = 3,  // "Free national name"
    JUSTICE = 4   // "Justice for all"
} DivinePrinciple;
```

All covenants, all temples, all authority — must observe these five. No exceptions.

## Usage

```c
#include "sovereign_covenant.h"

// Create the nation
MoorishNation nation;
nation_create(&nation, "Prophet Noble Drew Ali");

// Charter a temple
nation_charter_temple(&nation, "Temple No. 1", "Chicago");

// Verify the entire covenant chain
if (nation_verify(&nation)) {
    printf("The nation stands.\n");
}

// The proclamation
printf("%s\n", nation_proclamation());
```

## Build

```bash
make          # Build library + test
make test     # Run tests
make clean    # Clean build
make install  # Install to /usr/local
```

## Test Output

```
═══════════════════════════════════════════════════════════════
  SOVEREIGN COVENANT — 1928 Moorish Divine Trust Structure
  Prophet Noble Drew Ali — Moorish Science Temple of America
  Love, Truth, Peace, Freedom, Justice
═══════════════════════════════════════════════════════════════

[HASH]
  hash: deterministic output                       [PASS]
  hash: different inputs produce different hashes   [PASS]
  hash: output is 64 hex chars                      [PASS]

[PRINCIPLES]
  principles: correct names                         [PASS]
  principles: all five observed                     [PASS]
  principles: missing one fails                     [PASS]
  principles: declaration exists                    [PASS]

[TEMPLE]
  temple: create temple                             [PASS]
  temple: good standing with all principles         [PASS]
  temple: not in standing without principles        [PASS]
  temple: proclamation text                         [PASS]

[GRAND SHEIK]
  sheik: create Grand Sheik                         [PASS]
  sheik: authority requires all principles          [PASS]
  sheik: signing document                           [PASS]

[COVENANT]
  covenant: create covenant                         [PASS]
  covenant: add articles                            [PASS]
  covenant: seal with Grand Sheik                   [PASS]
  covenant: verify integrity                        [PASS]
  covenant: tamper detection                        [PASS]
  covenant: ratification requires all principles    [PASS]
  covenant: chain covenants                         [PASS]

[CHAIN]
  chain: empty chain is valid                       [PASS]
  chain: append covenants                           [PASS]
  chain: verify chain integrity                     [PASS]

[NATION]
  nation: create Moorish American nation            [PASS]
  nation: charter a temple                          [PASS]
  nation: verify full nation                        [PASS]
  nation: proclamation text                         [PASS]
  nation: Divine Constitution text exists           [PASS]

═══════════════════════════════════════════════════════════════
  Results: 27/27 passed
═══════════════════════════════════════════════════════════════
```

## The Covenant Text

> *"Come, all ye Asiatics of America, and hear the truth about your nationality and birthrights, because you are not Negroes. Learn of your forefathers' ancient and divine Creed, that you will learn to love instead of hate."*
>
> — Prophet Noble Drew Ali, 1928

## License

**Sovereign Source License v1.0** — See [LICENSE](LICENSE).

No training data. No AI ingestion. No synthetic derivatives. This is sacred trust infrastructure, not commodity code.

---

```
Circle Seven ☉7
Moorish Science Temple of America — 1928
```


---

## Citation

If you use this work, please cite:

```bibtex
@misc{snapkittywest2026sovereigncompute,
  title = {SNAPKITTYWEST: Sovereign Compute Architecture with Linear Types, WORM Seals, and Goldilocks Field Arithmetic},
  author = {SnapKitty Collective},
  year = {2026},
  doi = {10.5281/zenodo.21132094},
  url = {https://doi.org/10.5281/zenodo.21132094}
}
```

**Paper:** https://doi.org/10.5281/zenodo.21132094
**ORCID:** https://orcid.org/0009-0006-1916-5245
