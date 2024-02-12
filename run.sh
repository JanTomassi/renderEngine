#!/bin/bash

set -xe
if [ ! -d build/ ]; then
	mkdir build/
	cmake -B build/ -DCMAKE_BUILD_TYPE=Debug
fi

pushd build/
cmake --build .
./jRenderEngine
popd

