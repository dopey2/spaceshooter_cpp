# Setup — Linux & macOS

> This project requires: **git**, a **C++ compiler**, **CMake**, **make**, and **vcpkg** to manage project dependencies.

---

## 1. Install system tools

**Ubuntu / Debian**
```bash
sudo apt update
sudo apt install git cmake make gcc g++
```

**OpenSUSE Tumbleweed**
```bash
sudo zypper install git cmake make gcc gcc-c++
```

**macOS**
```bash
xcode-select --install
# This provides git, clang, and make. 
```

```bash
brew install cmake
```

---

## 2. Install vcpkg

```bash
git clone https://github.com/microsoft/vcpkg.git ~/vcpkg
cd ~/vcpkg
./bootstrap-vcpkg.sh
```

Add to your shell config (`~/.zshrc` or `~/.bashrc`):

```bash
export VCPKG_ROOT=~/vcpkg
export PATH="$VCPKG_ROOT:$PATH"
```

Reload your shell:

```bash
source ~/.zshrc   # or ~/.bashrc
```

Verify:

```bash
vcpkg --version
```

---

## 3. Install clang-tidy (optional)

clang-tidy is a static analyzer tool, that may be useful for catching common errors, bad patterns.

**Ubuntu / Debian**
```bash
sudo apt install clang-tidy
```

**OpenSUSE Tumbleweed**
```bash
sudo zypper install clang-tools
```

**macOS**
```bash
brew install llvm
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

```bash
make test
```
