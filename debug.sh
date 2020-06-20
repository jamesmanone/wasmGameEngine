#!/bin/bash

emcc -o build/tst.wasm -O2 -g4 --source-map-base http://localhost:8000/ -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s EXPORTED_FUNCTIONS='["_free", "_step", _setWH]' -s ALLOW_MEMORY_GROWTH=1 src/*.cpp

cp src/*.js build/
cp -r src build
