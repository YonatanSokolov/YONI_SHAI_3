#ifndef __datastructures__
#define __datastructures__

#define is_null(DS) !DS.data

typedef struct {
    unsigned num_rows, num_cols;
    double *data;
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

#define m_at(matrix, i, j) matrix.data[i*matrix.num_cols + j]

typedef struct {
    unsigned length;
    double *data;
} VECTOR;

VECTOR NULL_VECTOR;

typedef VECTOR DIAGONAL_MATRIX;

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
    VECTOR vector;
} MAT_AND_VEC;

MAT_AND_VEC NULL_MAT_AND_VEC;

typedef MAT_AND_VEC eigenvalues_and_eigenvectors;

typedef struct{
    unsigned int i;
    unsigned int j;
    double c;
    double s;
} JACOBI_ROTATION_MATRIX;

#endif /*__datastructures__*/

/*

*/