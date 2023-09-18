#!/bin/bash

set -xe

cd build/
make
cd ../
./jRenderEngine 
