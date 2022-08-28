#include "lnorm.h"
#include <stddef.h>
#include <math.h>

DIAGONAL_MATRIX *diagonal_degree_matrix(const MATRIX *W) {
    unsigned i, j;

    DIAGONAL_MATRIX *D = alloc_vector(W->num_cols);
    if (!D) return NULL;

    for (i = 0; i < len(D); i++) 
        get_v(D, i) = 0;
    for (i = 0; i < len(D); i++) 
        for (j = 0; j < len(D); j++)
            get_v(D, i) += get_m(W, i, j);
    
    return D;
}

MATRIX *normalized_graph_laplacian(const MATRIX *W, const DIAGONAL_MATRIX *D) {
    unsigned dim = len(D), i, j;

    DIAGONAL_MATRIX *D_sqrt = alloc_vector(dim);
    MATRIX *L = alloc_matrix(dim, dim);
    if (!D_sqrt || !L) return NULL;

    for (i = 0; i < dim; i++)
        get_v(D_sqrt, i) = sqrt(get_v(D, i));
    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            get_m(L, i, j) = -get_m(W, i, j) / get_v(D_sqrt, i) / get_v(D_sqrt, j);
    for (i = 0; i < dim; i++)
        get_m(L, i, i) = 1;        
    
    return L;
}
