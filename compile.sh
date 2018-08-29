#!/bin/sh

docker start wasm
docker exec --user root -t wasm rm -rf ./*
docker cp . wasm:/src
docker exec --user root -t wasm make
docker cp wasm:/src/index.wasm .
docker cp wasm:/src/index.js .
