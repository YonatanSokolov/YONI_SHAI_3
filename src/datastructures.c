#include "datastructures.h"
#include <stdlib.h>

MATRIX NULL_MATRIX = {0, 0, NULL};
VECTOR NULL_VECTOR = {0, NULL};

MATRIX alloc_matrix(unsigned num_rows, unsigned num_cols) {
    unsigned j;

    MATRIX matrix;
    double *data = (double *) malloc(num_rows * num_cols * sizeof(double));
    if (!data) return NULL_MATRIX;
    
    matrix.data = data;
    matrix.num_rows = num_rows;
    matrix.num_cols = num_cols;

    return matrix;
}

void free_matrix(MATRIX matrix) {
    free(matrix.data);
}

VECTOR alloc_vector(unsigned length) {
    VECTOR vec;
    double *data = (double *) malloc(length * sizeof(double));
    if (!data) return NULL_VECTOR;

    vec.data = data;
    vec.length = length;

    return vec;
}

void free_vector(VECTOR vec) {
    free(vec.data);
}