#include "lnorm.h"
#include <stddef.h>

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
    return NULL;
}
