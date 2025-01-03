#!/bin/bash

rm -rf cmake-build
mkdir cmake-build
cd cmake-build

cmake -G Ninja ..
cmake --build . -- -j4
