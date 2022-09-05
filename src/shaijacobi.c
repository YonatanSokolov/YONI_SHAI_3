#include "shaijacobi.h"
#include <float.h>
#include <stdlib.h>
#include <math.h>

#define square(a)   ((a)*(a))

static MATRIX identity_matrix(unsigned n) {
    unsigned i, j;
    MATRIX I = alloc_matrix(n, n);
    
    for (i = 0; i < n; i++) for (j = 0; j < n; j++)
        m_at(I, i, j) = (i == j);
    return I;
}

static void find_largest_offdiagonal_and_sum_upper
                    (MATRIX S, unsigned *resI, unsigned *resJ, double *sum) {
    unsigned i, j;
    double curr, maxSquare = -DBL_MAX;
    *sum = 0;

    for (i = 0; i < S.num_rows; i++)
        for (j = i+1; j < S.num_cols; j++) {
            curr = m_at(S, i, j);
            curr *= curr;
            *sum += curr;
            if (curr > maxSquare) {
                maxSquare = curr;
                *resI = i;
                *resJ = j;
            }
        }
}

void left_rotate_inplace(MATRIX M, ROTATION P) {
    unsigned k, i = P.i, j= P.j;
    double a_i, a_j, c = P.c, s = P.s;

    for (k = 0; k < M.num_rows; k++) {
        a_i = m_at(M, k, i), a_j = m_at(M, k, j);
        m_at(M, k, i) = c*a_i - s*a_j;
        m_at(M, k, j) = c*a_j + s*a_i;
    }
}

void pivot_inplace(MATRIX M, ROTATION P) {
    unsigned k, i = P.i, j = P.j;
    double a_i, a_j, a_ij, c = P.c, s = P.s;

    for (k = 0; k < M.num_rows; k++) {
        if (k == i || k == j) continue;
        a_i = m_at(M, k, i), a_j = m_at(M, k, j);
        m_at(M, k, i) = m_at(M, i, k) = c*a_i - s*a_j;
        m_at(M, k, j) = m_at(M, j, k) = c*a_j + s*a_i;
    }
    a_i = m_at(M, i, i), a_j = m_at(M, j, j), a_ij = m_at(M, i, j);
    m_at(M, i, i) = square(c)*a_i + square(s)*a_j - 2*s*c*a_ij;
    m_at(M, j, j) = square(s)*a_i + square(c)*a_j + 2*s*c*a_ij;
    m_at(M, i, j) = m_at(M, j, i) = 0;
}

#define maxIter     100
#define epsilon     0.000005
EIGENVS eigenvalues_eigenvectors(MATRIX S) {
    const unsigned n = S.num_rows;
    unsigned iter = 0, i, j;
    double prevOff, currOff;
    ROTATION P;
    EIGENVS res;
    res.matrix = identity_matrix(n);
    if (is_null(res.matrix)) return NULL_EIGENVS;

    find_largest_offdiagonal_and_sum_upper(S, &i, &j, &currOff);
    do {
        prevOff = currOff;
        /* calculate P */
        {
            double theta = (m_at(S, j, j)-m_at(S, i, i)) / (2*m_at(S, i, j));
            short sign = theta >= 0 ? 1 : -1;
            double t = sign / (sign*theta + sqrt(square(theta) + 1));
            double c = 1 / sqrt(square(t) + 1);
            double s = t*c;
            P.c = c; P.s = s; P.i = i; P.j = j;
        }
        pivot_inplace(S, P);
        left_rotate_inplace(res.matrix, P);
        find_largest_offdiagonal_and_sum_upper(S, &i, &j, &currOff);
    } while (++iter < maxIter && prevOff - currOff > epsilon);

    /* extract eigenvalues */
    {
        res.vector = alloc_vector(n);
        if (is_null(res.vector)) return NULL_EIGENVS;
        for (i = 0; i < n; i++) v_at(res.vector, i) = m_at(S, i, i);
    }
    return res;
}