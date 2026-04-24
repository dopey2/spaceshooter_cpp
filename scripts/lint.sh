#!/bin/bash
clang-tidy --quiet -p build/linux-debug src/main.cpp src/engine/*.cpp
