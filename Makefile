.PHONY: help build build-release test lint run run-release clean

OS := $(shell uname -s)

ifeq ($(OS), Darwin)
  PRESET_DEBUG   := macos-debug
  PRESET_RELEASE := macos-release
else
  PRESET_DEBUG   := linux-debug
  PRESET_RELEASE := linux-release
endif

BUILD_DEBUG   := build/$(PRESET_DEBUG)
BUILD_RELEASE := build/$(PRESET_RELEASE)
BIN           := Spaceship

help:
	@echo "build         - configure and build (debug)"
	@echo "build-release - configure and build (release)"
	@echo "test          - build and run tests"
	@echo "lint          - run clang-tidy"
	@echo "run           - build and launch game (debug)"
	@echo "run-release   - build and launch game (release)"
	@echo "clean         - remove build directories"

build:
	cmake --preset $(PRESET_DEBUG)
	cmake --build --preset $(PRESET_DEBUG)

build-release:
	cmake --preset $(PRESET_RELEASE)
	cmake --build --preset $(PRESET_RELEASE)

test: build
	ctest --test-dir $(BUILD_DEBUG) --output-on-failure

lint:
	clang-tidy --quiet -p $(BUILD_DEBUG) src/main.cpp src/engine/*.cpp

run: build
	./$(BUILD_DEBUG)/$(BIN)

run-release: build-release
	./$(BUILD_RELEASE)/$(BIN)

clean:
	rm -rf build/
