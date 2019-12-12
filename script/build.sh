#!/bin/bash

cd ..

[ -d out ] || mkdir out
cd out

cmake ..
if [ $? -ne 0 ]; then
  echo Build failed!
  exit 1
fi

cmake --build .
if [ $? -ne 0 ]; then
  echo Build failed!
  exit 2
fi
