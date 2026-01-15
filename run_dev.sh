#!/bin/bash
rm -rf build
mkdir build
cd build
cmake -G "Unix Makefiles" ..
make
./examples/primitives/primitives_example.exe
