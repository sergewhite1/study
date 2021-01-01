#!/bin/bash

set -x

cd ..

[ -d out ] || mkdir out
cd out

cmake ..
if [ $? -ne 0 ]; then
  echo Build failed!
  exit 1
fi

cmake --build .
#cmake --build . --target tcpdump-demo-client
#cmake --build . --target tcpdump-demo-server
if [ $? -ne 0 ]; then
  echo Build failed!
  exit 2
fi
