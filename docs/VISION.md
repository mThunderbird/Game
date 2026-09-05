# Vision

## Product

A top-down, twin-stick style multiplayer dungeon run:

- Character select with distinct kits (abilities, stats, starting weapons)
- Seeded procedural dungeon each round
- Camps, special rooms, bosses → loot / equipment
- Shrinking storm that forces fights toward the center
- Solo or teams; last team standing wins

Feel targets: readable combat, snappy movement, short rounds, “one more run.”

## Technical north star

Learn and own the hard parts — not hide them behind a full engine.

| Choice | Decision |
|--------|----------|
| Language | C++ (modern: C++20 where practical) |
| Platform layer | SDL3 (window, input, 2D render, audio later) |
| First vertical | **Local play** — no networking until the loop feels good |
| Multiplayer model | **Listen-server P2P** (one peer hosts, authoritative sim) |
| Netcode home | Separate **`net` module** — no SDL dependency; reusable later |
| Simulation | Fixed tick rate; game logic independent of render FPS |
| World gen | Seeded RNG so the same seed ⇒ same dungeon (sync-friendly later) |

We are **not** building a dedicated-server MMO or true lockstep P2P first. Host authority keeps combat and loot sane while still teaching real netcode.

## Reusable multiplayer module

Long-term: extract `net` into a small toolkit other C++ games can use.

**In scope for the library:** UDP I/O, reliability (acks/resend), session/hosting, tick alignment, snapshot/input framing, hooks for prediction & interpolation.

**Out of scope for the library:** abilities, loot, dungeon rules, rendering, SDL.

Until extraction: keep `net/` clean inside this repo. Prove it with *this* game first; a second tiny demo only after move/shoot/predict works.

## Build with the future in mind

- Prefer small modules with clear ownership (`game`, `render`, `net`, later `world` / `combat`)
- Simulation code must not include SDL headers
- Data-driven character/weapon defs when kits arrive (no hardcoded forks of net or tick logic)
- Document decisions here when we change course

## Non-goals (for a long while)

- AAA art pipeline or custom engine editor
- Perfect anti-cheat
- Cross-play with consoles
- Full MMO scale / interest management of hundreds of players
