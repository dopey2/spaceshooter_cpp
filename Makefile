.PHONY: help build build-release test lint run run-release clean

BUILD_DEBUG   := build/linux-debug
BUILD_RELEASE := build/linux-release
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
	cmake --preset linux-debug
	cmake --build --preset linux-debug

build-release:
	cmake --preset linux-release
	cmake --build --preset linux-release

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
