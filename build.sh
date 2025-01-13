#!/bin/bash

rm -rf cmake-build
mkdir cmake-build
cd cmake-build

cmake -DUSE_VCPKG=OFF -G Ninja ..
cmake --build . -- -j4
