#include "datastructures.h"
#include <stdlib.h>

MATRIX NULL_MATRIX = {0, 0, NULL};
VECTOR NULL_VECTOR = {NULL, 0};

MATRIX alloc_matrix(unsigned num_rows, unsigned num_cols) {
    unsigned j;

    MATRIX matrix;
    double **data = (double **) malloc(num_cols * sizeof(double *));
    double *underlying_data = (double *) malloc(num_rows * num_cols * sizeof(double));
    if (!data || !underlying_data) return NULL_MATRIX;
    
    for (j = 0; j < num_cols; j++)
        data[j] = underlying_data + j*num_rows*sizeof(double);
    matrix.data = data;
    matrix.num_rows = num_rows;
    matrix.num_cols = num_cols;

    return matrix;
}

void free_matrix(MATRIX matrix) {
    if (!matrix.data) return;
    free(matrix.data[0]);
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