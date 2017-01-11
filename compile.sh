#!/bin/sh

rm -rf ./build
mkdir ./build
cd ./build
cmake ../
make
cd ../
rm -rf ./build