# Architecture

Boundaries we protect as the project grows. Prefer boring folders and sharp edges over clever frameworks.

## Current status (Phase 0 done)

In place: `src/main.cpp`, `src/app/`, `src/game/`, `src/render/`, `src/net/` (placeholder README only).  
Not yet: `world/`, `data/`, `assets/`, real netcode.

## Intended layout (evolve toward this)

```text
Game/
  docs/                 # Vision, roadmap, design (you are here)
  cmake/                # Toolchain / find modules if needed
  third_party/          # Vendored deps only if we must
  src/
    main.cpp            # Entry; wires modules; thin
    app/                # SDL lifecycle, window, loop orchestration
    render/             # Draw only; reads sim state; no game rules
    game/               # Simulation: entities, combat, rooms, storm
    world/              # Dungeon generation, collision grid (can live under game/ early)
    data/               # Character/weapon defs (later)
    net/                # Transport + session + sync — NO SDL includes
  assets/               # Art, audio (later)
```

Early phases may collapse `world/` into `game/`. Do **not** collapse `net/` into `render/` or SDL code.

## Core rules

1. **Fixed timestep** — simulation advances in constant `dt` ticks; rendering interpolates or draws latest state.
2. **Sim ≠ view** — `game` never calls SDL_Render*; `render` never applies damage or moves entities for real.
3. **`net` is portable** — sockets, packets, reliability, session. Callbacks or interfaces into `game`, not the reverse dependency on SDL.
4. **Host authority (later)** — host sim is truth; clients predict locally and reconcile.
5. **Seeded world** — generation inputs are seed + params; no hidden `rand()` in gameplay paths we care to sync.

## Multiplayer shape (future)

```text
[Client input] → net → [Host game tick] → snapshots → net → [Client interpolate / predict]
```

Listen-server: one process is host (runs `game` + serves); others are clients (predict + render). Same binary, different role.

## Reuse story for `net`

Target consumers: small C++ games that want lobby-scale listen-server sync.

Library-ish API direction (names TBD when we implement):

- start host / connect client
- queue input for tick `n`
- pump packets
- produce/consume snapshots
- hooks: serialize input, apply remote input, read state for snapshot

Game-specific structs stay outside `net` or behind traits the game implements.

## What we deliberately postpone

- ECS frameworks (start with simple structs/arrays; introduce SoA/ECS only if pain is real)
- SDL_GPU (start with `SDL_Renderer`; GPU path is a later upgrade)
- Full reliability protocol before a dumb “send state every tick” prototype works
- Host migration / TURN until friends-on-different-NATs is an actual need
