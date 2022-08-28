#ifndef __datastructures__
#define __datastructures__

typedef struct {
    unsigned num_rows, num_cols;
    double **data;
} MATRIX;

/**
 * allocates memory for matrix of specified size.
 */
MATRIX *alloc_matrix(unsigned num_rows, unsigned num_cols);

/**
 * frees given matrix
 */
void free_matrix(MATRIX *matrix);

#define get_m(matrix, i, j) matrix->data[j][i]

#endif /*__datastructures__*/