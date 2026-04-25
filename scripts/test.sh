#!/bin/bash
cmake --build build/linux-debug && ctest --test-dir build/linux-debug --output-on-failure
