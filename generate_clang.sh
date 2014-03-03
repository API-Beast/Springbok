#!/bin/bash

export CC=/home/sirjson/projects/emscripten-fastcomp/build/Release/bin/clang
export CXX=/home/sirjson/projects/emscripten-fastcomp/build/Release/bin/clang++

if [ -d "build" ]; then
	rm -rf build
fi

mkdir build

cd build
cmake -DCMAKE_BUILD_TYPE=Debug -G Ninja ../
