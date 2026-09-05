# Roadmap

Status legend: `[ ]` todo · `[~]` in progress · `[x]` done

Update this file when a phase starts or finishes. **What’s next** is always the first incomplete phase.

---

## Phase 0 — Project skeleton
**Goal:** Build runs on Windows; empty window; fixed timestep loop.

- [x] CMake project
- [x] SDL3 linked and window opens
- [x] Fixed timestep game loop (sim tick vs render)
- [x] Folder layout matching [ARCHITECTURE.md](ARCHITECTURE.md)
- [x] Minimal README at repo root (how to build)

**Exit:** `F5` / build → colored window closes cleanly. **Done.**

---

## Phase 1 — Local mover
**Goal:** One controllable entity; prove input → sim → render.

- [x] Keyboard move (and look/aim direction if easy)
- [x] Simple drawn sprite/rect for the player
- [ ] Camera follow (optional, keep simple) — skipped for now

**Exit:** Walk around a blank arena at a stable tick rate. **Done.**

---

## Phase 2 — Local combat stub
**Goal:** Something to shoot; hit detection exists.

- [ ] Projectiles or melee hitbox
- [ ] Dummy target that can be damaged / destroyed
- [ ] Basic health

**Exit:** Kill a dummy; feel the combat cadence.

---

## Phase 3 — Dungeon stub
**Goal:** Seeded rooms before full generation art.

- [ ] Seed → deterministic layout (even if just rooms + corridors)
- [ ] Collision with walls
- [ ] Spawn player in a start room

**Exit:** Same seed = same map; player can explore rooms.

---

## Phase 4 — Round loop (still local)
**Goal:** A playable single-player “match” skeleton.

- [ ] Monster camps or simple enemies
- [ ] Clear room → grant placeholder loot
- [ ] Storm / safe-zone shrink
- [ ] Win/lose condition (survive / last standing vs AI or timer)

**Exit:** One full local round from drop to end.

---

## Phase 5 — Net module (host + 1 client)
**Goal:** Separate `net` layer; listen-server; two processes.

- [ ] UDP + binary packets
- [ ] Host runs authoritative sim
- [ ] Client sends input; receives state
- [ ] Remote entity interpolation
- [ ] Still no SDL inside `net`

**Exit:** Two windows; both see each other move.

---

## Phase 6 — Feel online
**Goal:** Local control feels responsive under latency.

- [ ] Client-side prediction
- [ ] Server reconciliation
- [ ] Basic lag / packet-loss testing mindset

**Exit:** Move/shoot online without “skating on ice.”

---

## Phase 7 — Multiplayer game features
**Goal:** Bring the vision onto the net spine.

- [ ] Character select / kits (data-driven)
- [ ] Teams
- [ ] Shared seeded dungeon + storm + loot online
- [ ] NAT / connection story (STUN etc.) when friends need it

**Exit:** Friends can play a full round over the network.

---

## Phase 8 — Extract & share `net` (optional)
**Goal:** Reusable module for others.

- [ ] Stable public API / headers
- [ ] Docs + maybe a second tiny sample
- [ ] Own repo or clear library target in CMake

**Exit:** Another project can depend on `net` without pulling the dungeon game.

---

## What’s next

**Phase 2 — Local combat stub.**

Dragostin implements game logic (Ask mode coaching). Agent scaffolds/tooling when requested.

---

## Progress log

| When | Milestone | Notes |
|------|-----------|--------|
| 2026-09-05 | Phase 0 complete | CMake + SDL3 FetchContent, fixed 60 Hz loop, `app`/`game`/`render`/`net` layout. Toolchain: CMake, Ninja, WinLibs MinGW. Smoke-tested window. |
| 2026-09-05 | Phase 1 complete | WASD → `Input` → `Game` move; player rect drawn. Fixed double-Present flicker. Camera skipped. |
