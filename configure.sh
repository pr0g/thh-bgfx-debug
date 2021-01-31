#!/bin/bash

cmake -S . -B build/debug -G Ninja -DCMAKE_BUILD_TYPE=Debug \
-DCMAKE_PREFIX_PATH="$(pwd)/third-party/build" \
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
-DAS_PRECISION_FLOAT=ON -DAS_COL_MAJOR=ON \
-DCMAKE_INSTALL_PREFIX=./install

cmake -S . -B build/release -G Ninja -DCMAKE_BUILD_TYPE=Release \
-DCMAKE_PREFIX_PATH="$(pwd)/third-party/build" \
-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
-DAS_PRECISION_FLOAT=ON -DAS_COL_MAJOR=ON \
-DCMAKE_INSTALL_PREFIX=./install
