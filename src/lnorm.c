#include "lnorm.h"
#include <math.h>

DIAGONAL_MATRIX diagonal_degree_matrix(MATRIX W) {
    unsigned i, j;

    DIAGONAL_MATRIX D = alloc_vector(W.num_cols);
    if (is_null(D)) return NULL_VECTOR;

    for (i = 0; i < D.length; i++) 
        v_at(D, i) = 0;
    for (i = 0; i < D.length; i++)
        for (j = 0; j < D.length; j++) 
            v_at(D, i) += m_at(W, i, j);
    
    return D;
}

MATRIX normalized_graph_laplacian(MATRIX W, DIAGONAL_MATRIX D) {
    unsigned dim = D.length, i, j;

    DIAGONAL_MATRIX D_sqrt = alloc_vector(dim);
    MATRIX L = alloc_matrix(dim, dim);
    if (is_null(D_sqrt) || is_null(L)) return NULL_MATRIX;

    for (i = 0; i < dim; i++)
        v_at(D_sqrt, i) = sqrt(v_at(D, i));
    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            m_at(L, i, j) = 
                (i == j) - m_at(W, i, j) / v_at(D_sqrt, i) / v_at(D_sqrt, j);  
    
    return L;
}
