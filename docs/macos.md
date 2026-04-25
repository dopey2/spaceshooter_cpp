# macOS Guide

> This project requires: **git**, a **C++ compiler**, **CMake**, **make**, and **vcpkg** to manage project dependencies.

---

## 1. Install Xcode Command Line Tools

```bash
xcode-select --install
```

This provides git, clang (C++ compiler), and make.

---

## 2. Install CMake

CMake is not included with Xcode Command Line Tools. Install it via [Homebrew](https://brew.sh):

```bash
# Install Homebrew if you don't have it
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install CMake
brew install cmake
```

---

## 3. Install vcpkg


```bash
git clone https://github.com/microsoft/vcpkg.git ~/vcpkg
cd ~/vcpkg
./bootstrap-vcpkg.sh
```

Add `VCPKG_ROOT` to your shell config (`~/.zshrc`):

```bash
export VCPKG_ROOT=~/vcpkg
export PATH="$VCPKG_ROOT:$PATH"
```

Reload your shell:

```bash
source ~/.zshrc
```

Verify vcpkg is working:

```bash
vcpkg --version
```

---

## 4. Build

```bash
make build
```

This will:
1. Configure the project with CMake
2. Download and build SDL3, SDL3_ttf, and Catch2 via vcpkg *(first run only — takes a few minutes)*
3. Compile the game

---

## 5. Run

```bash
make run
```

---

## 6. Test

Run the test suite to confirm everything is working:

```bash
make test
```

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
