#!/bin/sh

set -e

# The two calls to apt-get install might seem pointless, it may seem they could be done as one call.
# That is false. This is a work around with the currently broken java package in debian

apt-get update && apt-get install -y openjdk-11-jre
apt-get install -y python2.7-minimal curl git p7zip-full make libglm-dev pkg-config \
autoconf automake libtool g++

curl -sL https://deb.nodesource.com/setup_11.x | bash -
apt-get install -y nodejs
npm install -g google-closure-compiler
ln -s /usr/bin/google-closure-compiler /usr/bin/closure-compiler
git clone https://github.com/emscripten-core/emsdk.git

cd emsdk
./emsdk update-tags
./emsdk install latest
./emsdk activate latest
cd ..

mkdir /root/include
ln -s /usr/include/glm /root/include/glm

git clone https://github.com/protocolbuffers/protobuf.git
cd protobuf
./autogen.sh
./configure --disable-shared
make install

# rm -rf rm -rf  /usr/local/lib/
# source /root/emsdk/emsdk_env.sh
# emconfigure ./configure --prefix /root/protobuf_emscripten --with-protoc=protoc --disable-shared
# emmake make

cd ..
rm -rf protobuf

# Trick emscripten into caching everything
cd /root/emsdk/
. ./emsdk_env.sh
cd /root/
tee test.cpp <<EOF
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <iostream>

int main(){
EmscriptenWebGLContextAttributes a;
emscripten_webgl_init_context_attributes(&a);
std::cout << "a" << std::endl;
emscripten_webgl_create_context("a", &a);
}
EOF

em++ -std=c++17 -s WASM=1 -s USE_WEBGL2=1 test.cpp
rm -f a.out.js a.out.wasm test.cpp

apt-get remove -y autoconf automake libtool g++
apt-get autoremove -y
