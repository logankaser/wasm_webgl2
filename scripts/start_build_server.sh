#!/bin/sh

echo "Creating build server instance.."

docker create -t --name wasm_build_server -v /home/docker/build:/root/build fyrn/wasm_build_server
