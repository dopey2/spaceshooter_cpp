# Build Workflow
> This document describe the build workflow for educational purposes using ascii art schema.

## Build tool chain

```
         Project
            │
      CMakeLists.txt
            │
            │
            ▼
    ┌──────────────────────────────────────────┐
    │    cmake                                 │ ◄── generates platform-specific build files (Makefiles)
    │                                          │
    │    loads vcpkg toolchain                 │
    │         │                                │
    │         ├── SDL3       ─┐                │
    │         ├── SDL3_ttf   ─┤ (first run)    │
    │         └── Catch2     ─┘                │
    │                                          │
    │                                          │
    └──────────────────────────────────────────┘
            │
            │  Generated Makefiles:   
            │           - build/linux-debug/Makefiles               
            │           - build/macos-debug/Makefiles    
            │
            │
            ▼
    ┌──────────────┐
    │     make     │  ◄── reads the generated Makefiles and calls the compiler
    └──────────────┘
            │
            ▼
    ┌──────────────┐
    │  clang / g++ │  ◄── compiles .cpp files into object files, then links them
    └──────────────┘
            │   
            │ 
            ▼
       App Binary ──►
                       - build/linux-debug/Spaceship     
                       - build/macos-debug/Spaceship     
```

---

### Cross-platform Build Commands

```
       Command                                Binary
  ┌───────────────┐        Produce        ┌─────────────┐
  │ $: make build │  ──────────────────►  │  Spaceship  │
  └───────────────┘                       └─────────────┘
```

The command  `make build` work on both linux and macOS by resolving the CMake preset based on the OS in the `Makefile`.

```
  uname -s
      │
      ├── Darwin  ─►  PRESET_DEBUG = macos-debug  /  PRESET_RELEASE = macos-release
      └── Linux   ─►  PRESET_DEBUG = linux-debug  /  PRESET_RELEASE = linux-release
                              │
                              ▼
                   cmake --preset $(PRESET_DEBUG)
```