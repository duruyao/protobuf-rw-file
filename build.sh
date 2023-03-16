#!/usr/bin/env bash

PS4='\033[0;34m+ [${BASH_SOURCE}:${LINENO}]\033[0m '

set -xeuo pipefail

cmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="${PWD}"
cmake --build build --target all -- --jobs=4
cmake --build build --target install
