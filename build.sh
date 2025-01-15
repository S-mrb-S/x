#!/bin/bash

rm -rf cmake-build
mkdir cmake-build
cd cmake-build

cmake -DUSE_VCPKG=ON -G Ninja ..
cmake --build . -- -j4
