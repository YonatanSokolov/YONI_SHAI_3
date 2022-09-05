#include "shaijacobi.h"
#include <math.h>

#define MAX_ITER    100
#define EPSILON     0.000005
#define square(a)   ((a)*(a))

static MATRIX identity_matrix(unsigned n) {
    unsigned i, j;
    MATRIX I = alloc_matrix(n, n);
    
    for (i = 0; i < n; i++) for (j = 0; j < n; j++)
        m_at(I, i, j) = (i == j);
    return I;
}

static void find_largest_offdiagonal_and_sum_upper(
            MATRIX S, 
            unsigned *res_i, 
            unsigned *res_j, 
            double *res_sum
        ) {
    unsigned i, j;
    double curr, max_square = -1;
    *res_sum = 0;

    for (i = 0; i < S.num_rows; i++)
        for (j = i + 1; j < S.num_cols; j++) {
            curr = m_at(S, i, j);
            curr = square(curr);
            *res_sum += curr;
            if (curr > max_square) {
                max_square = curr;
                *res_i = i;
                *res_j = j;
            }
        }
}

void left_rotate_inplace(MATRIX M, ROTATION P) {
    unsigned k;
    double a_i, a_j;

    for (k = 0; k < M.num_rows; k++) {
        a_i = m_at(M, k, P.i), a_j = m_at(M, k, P.j);
        m_at(M, k, P.i) = P.c*a_i - P.s*a_j;
        m_at(M, k, P.j) = P.c*a_j + P.s*a_i;
    }
}

void pivot_inplace(MATRIX M, ROTATION P) {
    unsigned k;
    double a_i, a_j, a_ij;

    for (k = 0; k < M.num_rows; k++) {
        if (k == P.i || k == P.j) continue;
        a_i = m_at(M, k, P.i), a_j = m_at(M, k, P.j);
        m_at(M, k, P.i) = m_at(M, P.i, k) = P.c*a_i - P.s*a_j;
        m_at(M, k, P.j) = m_at(M, P.j, k) = P.c*a_j + P.s*a_i;
    }
    a_i = m_at(M, P.i, P.i), a_j = m_at(M, P.j, P.j), a_ij = m_at(M, P.i, P.j);
    m_at(M, P.i, P.i) = square(P.c)*a_i + square(P.s)*a_j - 2*P.s*P.c*a_ij;
    m_at(M, P.j, P.j) = square(P.s)*a_i + square(P.c)*a_j + 2*P.s*P.c*a_ij;
    m_at(M, P.i, P.j) = m_at(M, P.j, P.i) = 0;
}

EIGENVS eigenvalues_eigenvectors(MATRIX S) {
    unsigned iter = 0;
    double prev_largest_off, curr_largest_off;
    ROTATION P;
    EIGENVS res;
    res.matrix = identity_matrix(S.num_rows);
    if (is_null(res.matrix)) return NULL_EIGENVS;

    find_largest_offdiagonal_and_sum_upper(S, &P.i, &P.j, &curr_largest_off);
    do {
        if (curr_largest_off == 0) break;
        prev_largest_off = curr_largest_off;
        /* calculate and update c and s */
        {
            double theta = (m_at(S, P.j, P.j) - m_at(S, P.i, P.i)) / (2 * m_at(S, P.i, P.j));
            short sign = (theta >= 0) - (theta < 0);
            double t = sign / (sign*theta + sqrt(square(theta) + 1));
            P.c = 1 / sqrt(square(t) + 1);
            P.s = t * P.c;
        }
        pivot_inplace(S, P);
        left_rotate_inplace(res.matrix, P);
        find_largest_offdiagonal_and_sum_upper(S, &P.i, &P.j, &curr_largest_off);
    } while (++iter < MAX_ITER && prev_largest_off - curr_largest_off > EPSILON);

    /* extract eigenvalues */
    {
        unsigned i;
        res.vector = alloc_vector(S.num_rows);
        if (is_null(res.vector)) return NULL_EIGENVS;
        for (i = 0; i < S.num_rows; i++) 
            v_at(res.vector, i) = m_at(S, i, i);
    }
    return res;
}