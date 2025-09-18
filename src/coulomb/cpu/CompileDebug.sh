#!/usr/bin/env bash

mkdir buildDebug
cd buildDebug
cmake -DCMAKE_BUILD_TYPE=Debug ../
make $1 coulomb_cpu
cd ../
