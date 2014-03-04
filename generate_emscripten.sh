#!/bin/bash

EMSCRIPTEN=/home/sirjson/projects/emscripten

if [ -d "build" ]; then
	rm -rf build
fi

mkdir build

cd build

cmake -DHTML5BUILD=ON -DCMAKE_TOOLCHAIN_FILE=$EMSCRIPTEN/cmake/Platform/Emscripten.cmake -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" ../
