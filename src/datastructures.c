#include "datastructures.h"
#include <stdlib.h>

MATRIX *alloc_matrix(unsigned num_rows, unsigned num_cols) {
    unsigned j;

    MATRIX *matrix = (MATRIX *) malloc(sizeof(MATRIX));
    double **data = (double **) malloc(num_cols * sizeof(double *));
    double *underlying_data = (double *) malloc(num_rows * num_cols * sizeof(double));
    if (!matrix || !data || !underlying_data) return NULL;
    
    for (j = 0; j < num_cols; j++)
        data[j] = underlying_data + j * num_rows * sizeof(double);
    matrix->data = data;
    matrix->num_rows = num_rows;
    matrix->num_cols = num_cols;

    return matrix;
}

void free_matrix(MATRIX *matrix) {
    if (!matrix) return;
    free(matrix->data[0]);
    free(matrix->data);
    free(matrix);
}

VECTOR *alloc_vector(unsigned length) {
    VECTOR *vec = (VECTOR *) malloc(sizeof(VECTOR));
    double *data = (double *) malloc(length * sizeof(double));
    if (!vec || !data) return NULL;

    vec->data = data;
    vec->length = length;

    return vec;
}

void free_vector(VECTOR *vec) {
    if (!vec) return;
    free(vec->data);
    free(vec);
}