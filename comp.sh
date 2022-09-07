#!/bin/bash

mkdir -p bin
mkdir -p testexe

# gcc -ansi -Wall -Wextra -Werror -pedantic-errors -lm -c src/_.c -o bin/_.o

gcc -ansi -Wall -Wextra -Werror -pedantic-errors -lm -c src/myIO.c -o bin/myIO.o
gcc -ansi -Wall -Wextra -Werror -pedantic-errors -lm -c src/datastructures.c -o bin/datastructures.o
gcc -ansi -Wextra -Werror -pedantic-errors -lm -c src/lnorm.c -o bin/lnorm.o
gcc -ansi -Wextra -Werror -pedantic-errors -lm -c src/eigengap.c -o bin/eigengap.o
gcc -ansi -Wextra -Werror -pedantic-errors -lm -c src/shaijacobi.c -o bin/shaijacobi.o
gcc -ansi -Wextra -Werror -pedantic-errors -lm -c src/spkmeans.c -o bin/spkmeans.o
gcc -ansi -Wextra -Werror -pedantic-errors -lm -c src/calculate_w.c -o bin/calculate_w.o



gcc bin/myIO.o bin/datastructures.o bin/lnorm.o bin/eigengap.o bin/shaijacobi.o bin/spkmeans.o bin/calculate_w.o \
-o spkmeans -lm

echo DONE