# Dungeon Run

Soul Knight–like multiplayer dungeon crawler (C++ / SDL3). Local play first; listen-server netcode later.

Design docs: [`docs/`](docs/README.md)

## Prerequisites (Windows)

- **CMake** 3.24+
- A C++20 compiler (**MinGW-w64** via WinLibs, or **MSVC** Build Tools)
- **Git** (CMake FetchContent downloads SDL3 on first configure)
- **Ninja** (recommended) or a Visual Studio generator

## Build

Prefer the **Ninja** generator (this repo’s default). If CMake Tools switches you to “MinGW Makefiles” and build fails looking for `Makefile`, reconfigure:

```powershell
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
cmake --build build
```

Or select the **default** preset from `CMakePresets.json` in CMake Tools.

```powershell
cmake --build build
.\build\dungeon_run.exe
```

## Run

```powershell
.\build\dungeon_run.exe
```

(With the Visual Studio generator the binary is under `.\build\Debug\dungeon_run.exe`.)

Close the window or press **Esc** to quit. Phase 0 shows a pulsing clear color driven by the fixed 60 Hz simulation tick.

## Layout

```text
src/app/      SDL lifecycle + fixed-timestep loop
src/game/     Simulation (no SDL)
src/render/   Drawing only
src/net/      Future reusable netcode (empty for now)
docs/         Vision, roadmap, architecture
```
