#include "eigengap.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef struct {
    double val;
    unsigned pos;
} KEY;

/**
 * Quick-sort a key array.
 */
static void sort_inplace_rec(KEY *arr, unsigned length) {
    #define cmp(i, j, f, c)   (arr[i].f c arr[j].f)
    #define before(i, j)        \
        (cmp(i, j, val, ==) * cmp(i, j, pos, <) + cmp(i, j, val, >))
    #define swap(i, j)  do {    \
        KEY temp = arr[i];      \
        arr[i] = arr[j];        \
        arr[j] = temp;          \
        } while (0)   

    unsigned start = 0, end = --length;
    if (end - start == 1) {
        if (before(end, start)) swap(end, start);
        return;
    }
    else while (start < end) {
        if (before(length, start)) {
            end--;
            swap(start, end);
        }
        else start++;
    }
    swap(end, length);
    if (end) sort_inplace_rec(arr, end);
    if (length - end) sort_inplace_rec(arr + end + 1, length - end);

    #undef cmp
    #undef before
    #undef swap
}

int sort_inplace(MAT_AND_VEC *U) {
    unsigned num_vecs = U->matrix.num_cols, num_coos = U->matrix.num_rows;
    unsigned i, j;
    KEY *vps = (KEY *) malloc(num_vecs * sizeof(KEY));
    double *new_data = (double *) malloc(
        U->matrix.num_rows * U->matrix.num_cols * sizeof(double)
    );
    if (!vps || !new_data) return 1;

    for (j = 0; j < num_vecs; j++) {
        KEY temp;
        temp.val = v_at(U->vector, j);
        temp.pos = j;
        vps[j] = temp;
    }
    sort_inplace_rec(vps, num_vecs);
    for (i = 0; i < num_coos; i++) for (j = 0; j < num_vecs; j++)
        new_data[i*num_coos + j] = m_at(U->matrix, i, vps[j].pos);
    free(U->matrix.data);
    U->matrix.data = new_data;
    for (j = 0; j < num_vecs; j++)
        v_at(U->vector, j) = vps[j].val;
    free(vps);
    return 0;
}

unsigned k_and_sort_inplace(MAT_AND_VEC *U) {
    unsigned length = U->vector.length, k = 0, i;
    double max = -1;

    if (sort_inplace(U)) return 0;

    for (i = 0; i < length / 2; i++) {
        double delta = v_at(U->vector, i) - v_at(U->vector, i + 1);
        if (delta > max) {
            max = delta;
            k = i;
        }
    }
    return k + 1;
}

MATRIX reduced_vectors(MATRIX U, unsigned k) {
    unsigned i, j;
    MATRIX res;

    res = alloc_matrix(U.num_rows, k);
    if (is_null(res)) return NULL_MATRIX;
    for (i = 0; i < U.num_rows; i++) for (j = 0; j < k; j ++)
        m_at(res, i, j) = m_at(U, i, j);
    return res;
}

int renormalize_inplace(MATRIX U) {
    unsigned i, j;
    for (i = 0; i < U.num_rows; i++) {
        double norma = 0;
        for (j = 0; j < U.num_cols; j++)
            norma += m_at(U, i, j) * m_at(U, i, j);
        if (norma == 0) return 1;
        norma = sqrt(norma);
        for (j = 0; j < U.num_cols; j++)
            m_at(U, i, j) /= norma;
    }
    return 0;
}