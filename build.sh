#!/bin/bash

rm -rf build/*

emcc -o build/singlethread.wasm -O3 -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s EXPORTED_FUNCTIONS='["_free", "_step", _setWH, _go]' -s ALLOW_MEMORY_GROWTH=1 src/*.cpp

wasm2wat build/singlethread.wasm |
sed 's/(memory (;0;) 256 32768)/(memory (;0;) 256 32768 shared)/' > build/multithreaded.wat

wat2wasm -o build/multithreaded.wasm --enable-threads build/multithreaded.wat
rm build/multithreaded.wat


cp src/*.html build/
cp src/*.js build/
