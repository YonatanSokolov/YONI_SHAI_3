#ifndef __datastructures__
#define __datastructures__

struct matrix_t {
    unsigned num_rows, num_cols;
    double **data;
};
typedef matrix_t *MATRIX;

MATRIX alloc_matrix(unsigned num_rows, unsigned num_cols);
void free_matrix(MATRIX matrix);

#define get_m(matrix, i, j) matrix->data[j][i]

#endif //__datastructures__