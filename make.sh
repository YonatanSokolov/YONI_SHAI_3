#!/bin/bash

mkdir -p build

gcc -ansi -Wall -Wextra -Werror -pedantic-errors -lm -c src/vector.c     -o build/vector.o
gcc -ansi -Wall -Wextra -Werror -pedantic-errors -lm -c src/matrix.c     -o build/matrix.o
gcc -ansi -Wall -Wextra -Werror -pedantic-errors -lm -c src/rotation.c   -o build/rotation.o
gcc -ansi -Wall -Wextra -Werror -pedantic-errors -lm -c src/littles.c    -o build/littles.o
gcc -ansi -Wall -Wextra -Werror -pedantic-errors -lm -c src/myIO.c       -o build/myIO.o
gcc -ansi -Wall -Wextra -Werror -pedantic-errors -lm -c src/algorithms.c -o build/algorithms.o


