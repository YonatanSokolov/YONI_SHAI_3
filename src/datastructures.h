#ifndef __datastructures__
#define __datastructures__

typedef struct {
    unsigned num_rows, num_cols;
    double **data;
} MATRIX;

/**
 * Allocates memory for matrix of specified size.
 */
MATRIX *alloc_matrix(unsigned num_rows, unsigned num_cols);

/**
 * Frees given matrix.
 */
void free_matrix(MATRIX *matrix);

#define get_m(matrix, i, j) matrix->data[j][i]

typedef struct {
    double *data;
    unsigned length;
} VECTOR;

typedef VECTOR DIAGONAL_MATRIX;

/**
 * Allocates memory for vector of specified size.
 */
VECTOR *alloc_vector(unsigned length);

/**
 * Frees given vector.
 */
void free_vector(VECTOR *vec);

#define get_v(vec, i)   vec->data[i]


#endif /*__datastructures__*/