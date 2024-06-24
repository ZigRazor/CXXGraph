#!/bin/bash

#if [ -d "build" ]; then
#  echo "empty directory build"
#  rm -rf build
#  mkdir -p build
#fi

cd build
cmake ../ -DTEST=ON -Dgtest_disable_pthreads=OFF
make
