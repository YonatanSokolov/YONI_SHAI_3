#include "lnorm.h"
#include <stddef.h>
#include <math.h>

DIAGONAL_MATRIX diagonal_degree_matrix(MATRIX W) {
    unsigned i, j;

    DIAGONAL_MATRIX D = alloc_vector(W.num_cols);
    if (is_null(D)) return NULL_VECTOR;

    for (i = 0; i < D.length; i++) 
        v_at(D, i) = 0;
    for (j = 0; j < D.length; j++) 
        for (i = 0; i < D.length; i++)
            v_at(D, i) += m_at(W, i, j);
    
    return D;
}

MATRIX normalized_graph_laplacian(const MATRIX W, const DIAGONAL_MATRIX D) {
    unsigned dim = D.length, i, j;

    DIAGONAL_MATRIX D_sqrt = alloc_vector(dim);
    MATRIX L = alloc_matrix(dim, dim);
    if (is_null(D_sqrt) || is_null(L)) return NULL_MATRIX;

    for (i = 0; i < dim; i++)
        v_at(D_sqrt, i) = sqrt(v_at(D, i));
    for (j = 0; j < dim; j++)
        for (i = 0; i < dim; i++)
            m_at(L, i, j) = 
                (i == j) - m_at(W, i, j) / v_at(D_sqrt, i) / v_at(D_sqrt, j);  
    
    return L;
}
