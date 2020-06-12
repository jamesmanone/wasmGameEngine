#!/bin/bash

emcc -o build/tst.wasm -O2 -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s EXPORTED_FUNCTIONS='["_free", "_step", _setWH]' -s ALLOW_MEMORY_GROWTH=1 src/*.cpp

cp src/*.js build/
