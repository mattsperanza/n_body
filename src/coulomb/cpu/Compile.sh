#!/usr/bin/env bash

mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ../
make $1 coulomb_cpu
cd ../
