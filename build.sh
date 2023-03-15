#!/usr/bin/env bash

set -xeuo pipefail

cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="${PWD}"
cmake --build build --target all -- --jobs=4
cmake --build build --target install
