# Linux Guide

> This project requires: **git**, a **C++ compiler**, **CMake**, **make**, and **vcpkg** to manage project dependency.

---

## 1. Install system packages

**Ubuntu / Debian**

```bash
sudo apt update
sudo apt install git cmake make gcc g++
```

**OpenSUSE Tumbleweed**

```bash
sudo zypper install git cmake make gcc gcc-c++
```

---

## 2. Install vcpkg


```bash
git clone https://github.com/microsoft/vcpkg.git ~/vcpkg
cd ~/vcpkg
./bootstrap-vcpkg.sh
```

Add `VCPKG_ROOT` to your shell config (`~/.zshrc` or `~/.bashrc`):

```bash
export VCPKG_ROOT=~/vcpkg
```

Reload your shell:

```bash
source ~/.zshrc   # or ~/.bashrc
```

---

## 3. Build

```bash
make build
```
This will:
1. Configure the project with CMake
2. Download and build SDL3, SDL3_ttf, and Catch2 via vcpkg *(first run only — takes a few minutes)*
3. Compile the game
---

## 4. Run

```bash
make run
```

---

## 5. Test

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
