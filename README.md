# IO Game client

C++ / WASM / webgl2 client for IO Game
Makes use of protobuffers for server-client communication.

## Build Dependencies
* emscripten >= 1.38.29
* closure-compiler
* make
* protoc
* proto-gen-cpp

## Setup for MacOS
Install things that can be installed from brew:  
`brew install closure-compiler protobuf`  
**Do not install emscripten from brew.**  
Install it by following the instructions on this [page](https://emscripten.org/docs/getting_started/downloads.html)  
If you are install on a machine that uses **NFS** you need to set `EM_CACHE`  
to a location outside of the **NFS**.  
Example:  
```sh
mkdir -p /tmp/wasm_cache
export EM_CACHE=/tmp/wasm_cache
```
You probably want to add that you your shell profile.  
To switch into an emscripten build enviroment run:
```sh
source /path/to/emscritpen/emsdk_env.sh
```
At this point `make run` will build the client and host it at `localhost:8080`
