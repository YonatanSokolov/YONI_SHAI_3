typedef struct double_matrix_t {
    int rowCnt, colCnt;
    double *data;
} MATRIX;

typedef struct double_matrix_with_vector_t {
    MATRIX *matrix;
    VECTOR vector;
} MATRIX_WITH_VECTOR;

#define mCell(M, i, j)      (M->data[(M->colCnt)*(i) + (j)])
#define mRow(M, i)          (M->data + ((M->colCnt)*(i)))
#define forEachCell(A, op)  do {                                        \
                                int i, j;                               \
                                for (i = 0; i < A->rowCnt; i++)         \
                                    for (j = 0; j < A->colCnt; j++)     \
                                    op;                                 \
                            } while (0)


/**
 * Creates new uninitialized matrix.
 * @param   rowCnt number of rows in new matrix
 * @param   colCnt number of cols in new matrix
 * @return  pointer to new matrix, or NULL on failure
 */
MATRIX *newMatrix(int rowCnt, int colCnt);

/**
 * Creates new matrix with given data.
 * @param   rowCnt number of rows in new matrix
 * @param   colCnt number of cols in new matrix
 * @param   data data array (row after row, total size: colCnt * colCnt)
 * @return  pointer to new matrix, or NULL on failure
 */
MATRIX *newMatrixFromArray(int rowCnt, int colCnt, double data[]);

#ifndef __matrix
#define __matrix

/**
 * Frees memory of given matrix.
 * @param   M matrix to be cleared
 * @return  void
 */
void freeMatrix(MATRIX *M);

/**
 * Divides row i of given matrix by i-th vector coordinate.
 * @param   M pointer to matrix to be divided
 * @param   v vector to divided by
 * @return  void
 */
void divByRow(MATRIX *M, VECTOR v);

/**
 * Divides column j of given matrix by j-th vector coordinate.
 * @param   M pointer to matrix to be divided
 * @param   v vector to divided by
 * @return  void
 */
void divByCol(MATRIX *M, VECTOR v);

/**
 * Subtracts matrix B from matrix A.
 * @param   A pointer to matrix A
 * @param   B pointer to matrix B
 * @return  void
 */
void subMatrix(MATRIX *A, MATRIX *B);

/**
 * Creates the identity matrix of given order.
 * @param   n order of identity matrix
 * @return  pointer to identity matrix
 */
MATRIX *identityMatrix(int n);

#endif //__matrix