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

apt-get remove -y autoconf automake libtool g++
apt-get autoremove -y
