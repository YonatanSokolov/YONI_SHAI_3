#!/bin/bash

bash make.sh

gcc -lm -c test/$1.c -o build/$1_test.o
gcc build/vector.o build/matrix.o build/rotation.o build/littles.o build/myIO.o build/algorithms.o \
build/$1_test.o -o build/$1_test -lm
./build/$1_test

echo DONE