# Spaceshooter C++

> A C++ made Spaceshooter & its own tiny game engine built on top of SDL3.

---

## Setup

- [Linux & macOS](docs/setup_unix.md)
- [Windows](docs/setup_windows.md) *(work in progress)*

---

## Available commands

| Command              | Description                                  |
|----------------------|----------------------------------------------|
| `make build`         | Configure and build (debug)                  |
| `make run`           | Build and launch the game (debug)            |
| `make test`          | Build and run tests                          |
| `make lint`          | Run clang-tidy static analysis               |
| `make build-release` | Configure and build (release, no sanitizers) |
| `make run-release`   | Build and launch the game (release)          |
| `make clean`         | Remove all build artifacts                   |

## File structure

```ASCII
spaceshooter-cpp/
├─ assets/              <-- Game assets
├─ docs/                <-- Documentation
├─ scripts/             <-- Various scripts
├─ tests/               <-- Unit tests
├─ src/
│  ├─ engine/           <-- Game engine
│  ├─ game/             <-- Game logic
│  ├─ main.cpp          <-- App entry point
├─ .clang-tidy          <-- Clang-tidy config (static analysis)
├─ .clangd              <-- IDE server lang config (untracked & auto-generated)
├─ CMakeLists.txt       <-- CMake config
├─ CMakePresets.json    <-- CMake presets (linux + macos)    
├─ Makefile             <-- Global commands
├─ vcpkg.json           <-- Vcpkg manifest (dependencies)
```
