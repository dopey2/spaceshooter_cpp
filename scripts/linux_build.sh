#!/usr/bin/env bash
set -e

cmake --preset linux-debug
cmake --build --preset linux-debug
