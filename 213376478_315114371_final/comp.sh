#!/bin/bash
gcc -ansi -Wall -Wextra -Werror -pedantic-errors \
myIO.c \
datastructures.c \
lnorm.c \
eigengap.c \
jacobi.c \
spkmeans.c \
calculate_w.c \
-lm -o spkmeans