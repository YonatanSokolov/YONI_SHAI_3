#!/bin/bash
mkdir -p testexe

# gcc test/calculate_w.c src/calculate_w.c src/datastructures.c -lm -o testexe/calcw_test
# ./testexe/calcw_test

gcc src/Jacobi_algo.c src/datastructures.c -lm -o testexe/Jacobi_algo_test
./testexe/Jacobi_algo_test