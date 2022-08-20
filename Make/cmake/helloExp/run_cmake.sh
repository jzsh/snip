#!/bin/sh

rm -rf build
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/tmp/cmake ..
make
make install
