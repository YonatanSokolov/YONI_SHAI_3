#ifndef __datastructures__
#define __datastructures__

#define is_null(DS) !DS.data

typedef struct {
    unsigned num_rows, num_cols;
    double **data;
} MATRIX;

MATRIX NULL_MATRIX;

/**
 * Allocates memory for matrix of specified size.
 */
MATRIX alloc_matrix(unsigned num_rows, unsigned num_cols);

/**
 * Frees given matrix.
 */
void free_matrix(MATRIX matrix);

#define m_at(matrix, i, j) matrix.data[j][i]

typedef struct {
    double *data;
    unsigned length;
} VECTOR;

typedef VECTOR DIAGONAL_MATRIX;

VECTOR NULL_VECTOR;

/**
 * Allocates memory for vector of specified size.
 */
VECTOR alloc_vector(unsigned length);

/**
 * Frees given vector.
 */
void free_vector(VECTOR vec);

#define v_at(vec, i)   vec.data[i]

typedef struct {
    MATRIX matrix;
    double *vector;
} MAT_AND_VEC;

#endif /*__datastructures__*/