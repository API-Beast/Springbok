#!/bin/bash

./generate_emscripten.sh

cd build
make
cd ../bin
mv Springbok Springbok.bc
echo "Generate JavaScript..."
EMCC_FAST_COMPILER=1 emcc Springbok.bc -o Springbok.html
