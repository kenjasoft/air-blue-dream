# air-blue dream

A small 2D platformer written in C using SDL2. Jump, explore, avoid enemies, and try to reach the portal at the top of each stage as fast as you can.

This project is intended as a clean, readable template for anyone who wants to make a 2D game in C and SDL2. The codebase is deliberately small and straightforward — no engine, no framework, just C and a few SDL2 libraries.

---

## Table of contents

- [About the game](#about-the-game)
- [Features](#features)
- [Project structure](#project-structure)
- [Dependencies](#dependencies)
- [Building on Windows (Visual Studio)](#building-on-windows-visual-studio)
- [Controls](#controls)
- [Game modes](#game-modes)
- [Architecture overview](#architecture-overview)
- [How assets are embedded](#how-assets-are-embedded)
- [Embedding your own assets (bin2h)](#embedding-your-own-assets-bin2h)
- [Level data format](#level-data-format)
- [License](#license)

---

## About the game

air-blue dream is a vertical platformer with two modes: a relaxed **stroll** mode and a timed **sprint** mode. The player climbs upward through a series of stages, navigating platforms and avoiding pigeons and crows. Each stage records your clear time, and the game tracks your personal best.

The game window is 384×768 pixels — a tall, narrow aspect ratio that suits vertical climbing gameplay.

---

## Features

- 6 handmade stages plus a title/menu stage
- Two play modes: stroll (sequential stages, best-time tracking) and sprint (random stages, cumulative timer)
- Particle-based light effects at portals
- Animated player, pigeon, and crow entities
- Parallax background with sky, clouds, and landscape layers
- All game assets loaded into memory (no loose asset files at runtime)
- Gamepad support via SDL2's game controller API
- High score saving/loading with simple XOR encryption
- Frame rate cap targeting ~60 fps

---

## Project structure

```
air-blue-dream/
├── Untitled.sln                 # Visual Studio solution
├── Untitled/
│   ├── Untitled.vcxproj         # Visual Studio project
│   ├── src/
│   │   ├── main.c / main.h      # Entry point, game loop, frame cap
│   │   ├── common.c / common.h  # Shared types, constants, enums, structs
│   │   ├── init.c / init.h      # SDL init, asset loading, high score save/load
│   │   ├── stage.c / stage.h    # Stage lifecycle, background, end-of-stage screens
│   │   ├── entity.c / entity.h  # Entity system, physics, collision, level data
│   │   ├── player.c / player.h  # Player input and movement
│   │   ├── camera.c / camera.h  # Camera logic
│   │   ├── draw.c / draw.h      # Renderer helpers (blit, prepareScene, presentScene)
│   │   ├── input.c / input.h    # Keyboard and gamepad input
│   │   ├── crow.c / crow.h      # Crow enemy entity
│   │   ├── pigeon.c / pigeon.h  # Pigeon enemy entity
│   │   ├── platform.c / platform.h  # Platform entity
│   │   ├── portal.c / portal.h  # Portal entity (stage exit trigger)
│   │   ├── light.c / light.h    # Light particle effects
│   │   ├── particle.c / particle.h  # Particle texture generation
│   │   ├── text.c / text.h      # In-world text entity (menu labels, subtitles)
│   │   ├── textures.c / textures.h  # (binary) All image assets as C arrays
│   │   ├── sound.c / sound.h    # (binary) Sound effects and music playback
│   │   ├── stroll.h             # (binary) Stroll music
│   │   ├── sprint.h             # (binary) Sprint music
│   │   └── title.h              # (binary) Title music
│   ├── img/                     # Source PNG assets (used to generate textures.h)
│   ├── ogg/                     # Source OGG audio files (used to generate audio headers)
│   └── resource.h / Untitled.rc # Windows resource file (application icon)
```

---

## Dependencies

You will need the following SDL2 libraries. The Visual Studio project expects them installed at `C:\SDL\`:

| Library | Purpose |
|---|---|
| SDL2 | Core windowing, rendering, input, events |
| SDL2_image | PNG texture loading |
| SDL2_mixer | Audio playback (OGG music, WAV sound effects) |
| SDL2_ttf | TrueType font rendering (timer and UI text) |

### Installing SDL2 on Windows

1. Download the development libraries (Visual C++) for each package from [libsdl.org](https://libsdl.org) and the SDL2 GitHub releases.
2. Extract each into `C:\SDL\` so the layout looks like:
   ```
   C:\SDL\SDL2\include\
   C:\SDL\SDL2\lib\x86\
   C:\SDL\SDL2_image\include\
   ...
   ```
3. Copy the corresponding `.dll` files into your build output directory (next to the `.exe`), or add them to your system PATH.

If you prefer a different install location, update the include and library paths in `Untitled.vcxproj` accordingly.

---

## Building on Windows (Visual Studio)

1. Install [Visual Studio 2019 or later](https://visualstudio.microsoft.com/) with the **Desktop development with C++** workload.
2. Install the SDL2 libraries as described above.
3. Open `Untitled.sln`.
4. Select the **Debug | Win32** or **Release | Win32** configuration.
5. Build the solution (`Ctrl+Shift+B`).
6. The executable will appear in `Untitled/Debug/` or `Untitled/Release/`.
7. Make sure the SDL2 `.dll` files are in the same directory as the `.exe` before running.

> **Note:** The x64 configurations are present in the project but have no library paths configured — use Win32 builds unless you update the paths for x64 SDL2 libraries.

---

## Controls

All of the following inputs are equivalent — the game accepts keyboard or gamepad:

| Action | Keyboard | Gamepad |
|---|---|---|
| Move left | `A` / `←` | D-pad left |
| Move right | `D` / `→` | D-pad right |
| Jump / hold to rise higher | `Space`, `Z`, `X`, `C`, `Shift`, `Ctrl`, `Q`, `E` | A / B / X / Y |
| Drop through platform | `S` / `↓` + jump | D-pad down + jump |
| Enter portal | `W` / `↑` | D-pad up |

The player can jump and hold the jump button to extend height. Pressing down while standing on a platform and then jumping will drop through it.

---

## Game modes

### Stroll
Selected from the title menu. You play through all 6 stages in sequence. Each stage is individually timed; your best time per stage is saved. After completing all 6 stages the game displays your total time and tracks a best total as well.

### Sprint
Also selected from the title menu. Stages are selected randomly (never repeating back-to-back). A single cumulative timer runs across all stages. The run ends when the player falls off the bottom of a stage (the camera overtakes them). Your best sprint time is saved.

### Quit
The third menu option exits the game.

---

## Architecture overview

The game uses a simple delegate pattern for the main loop. A `Game` struct holds a `Delegate` with two function pointers — `logic` and `draw` — which are set by `initStage()` and called every frame:

```c
while (stage.runGame) {
    prepareScene();
    doInput();
    game.delegate.logic();
    game.delegate.draw();
    presentScene();
    capFrameRate(&then, &remainder);
}
```

### Entity system

All game objects (player, platforms, portals, birds, lights, text labels, decorative scenery) are `Entity` structs linked in a singly-linked list anchored at `stage.entityHead`. Each entity has optional `tick` and `touch` function pointers for per-frame update logic and collision response. The global `self` pointer is set to the current entity before calling `tick` or `touch`, giving each entity a reference to itself without passing it as a parameter.

Physics are simple: gravity accumulates `dy` each frame, entities move by their `dx`/`dy`, and `moveToEntities()` resolves AABB collisions against platforms and the ground. Weightless entities (decorations, lights, portals, crows) skip gravity entirely via the `EF_WEIGHTLESS` flag.

### Stage/level data

Level layouts are stored as plain text strings inside `entity.h` in a static array `levelData[MAX_LEVELS]`. Each line describes one entity by type name and position. This makes it straightforward to design levels in a text editor without a separate level editor.

### Camera

The camera smoothly follows the player vertically in stroll mode. In sprint mode the camera scrolls upward automatically, putting time pressure on the player.

### Rendering

All rendering goes through the `blit()` function in `draw.c`, which calls `SDL_RenderSetScale` and `SDL_RenderCopyEx`. The render scale is set per-blit call, so individual entities can be drawn at different scales without affecting others.

---

## How assets are embedded

All game assets — textures, sound effects, and music — are compiled directly into the executable as C byte arrays. There are no loose asset files required at runtime. Assets are loaded from memory using SDL's `SDL_RWops` interface:

```c
// Loading a sound effect from a C array
SDL_RWops* rw = SDL_RWFromConstMem(jump, sizeof(jump));
sounds[SND_JUMP] = Mix_LoadWAV_RW(rw, 1);

// Loading a texture from a C array
SDL_RWops* rw = SDL_RWFromConstMem(player_idle, sizeof(player_idle));
SDL_Surface* surface = IMG_Load_RW(rw, 1);
textures[TX_PLAYERIDLE1] = SDL_CreateTextureFromSurface(renderer, surface);
```

---

## Embedding your own assets (bin2h)

bin2h is a small utility that converts any binary file into a C header containing a `const unsigned char` array, ready to be `#include`d and loaded via `SDL_RWops`.

1. Download `bin2h.exe` from [http://www.deadnode.org/sw/bin2h](http://www.deadnode.org/sw/bin2h).
2. Place `bin2h.exe` in the same folder as your asset files.
3. Open a command prompt in that folder.
4. Run the conversion. For example, to convert `image.png` into a header with an array named `image`:
   ```
   bin2h image < image.png > image.h
   ```
5. Open the generated `image.h` and copy the array declaration into your codebase (or `#include` the header directly).
6. Load the asset at runtime using `SDL_RWFromConstMem`:
   ```c
   SDL_RWops* rw = SDL_RWFromConstMem(image, sizeof(image));
   SDL_Surface* surf = IMG_Load_RW(rw, 1);
   ```

Look through `sound.c` and `textures.c` in this project for complete working examples of this pattern for both images and audio.

---

## Level data format

Levels are defined as newline-delimited strings in `entity.h`. Each line follows this pattern:

```
ENTITY_TYPE x y [additional_params]
```

Supported entity types and their parameters:

| Type | Parameters | Notes |
|---|---|---|
| `PLAYER` | x y facing | facing: 1 = right, 0 = left |
| `PORTAL` | x y hitMode | hitMode: 0 = off, 1 = on, 2 = always |
| `ROCKPLATFORM` | x y flip | flip: 1 = none, 0 = horizontal |
| `GRASSPLATFORM` | x y flip | |
| `SMALLROCKPLATFORM` | x y flip | |
| `GROUND` | x y | Solid ground tile, no flip |
| `PIGEON` | x y | Direction chosen randomly at spawn |
| `CROW` | x y xSin xFreq ySin yFreq | Sinusoidal float path parameters |
| `TREE` | x y flip | Decorative, weightless |
| `BUSH` | x y flip | Decorative, weightless |
| `FLOWERS` | x y flip | Decorative, weightless |
| `MAPLE` | x y flip | Decorative, weightless |
| `TEXT` | x y type | type index selects texture from TX_SUBTITLE onward |

All y coordinates in level data are relative to the bottom of the map; `SCREEN_HEIGHT` is added at load time.

---

## License

Released under the MIT License as a reference/learning resource. Feel free to read, adapt, or build upon this code for your own projects.
