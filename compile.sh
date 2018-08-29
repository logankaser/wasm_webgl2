#!/bin/sh

docker run \
  --rm \
  -v $(pwd):/src \
  -u emscripten \
  trzeci/emscripten \
  make
