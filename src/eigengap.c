#include "eigengap.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include <stdio.h>

typedef struct {
    double val;
    unsigned pos;
} KEY;

/**
 * Quick-sort a key array.
 */
static void sort_inplace_rec(KEY *arr, unsigned length) {
    #define cmp(i, j, f, c)   (arr[i].f c arr[j].f)
    #define less_than(i, j)       \
        (cmp(i, j, val, ==) * cmp(i, j, pos, <) + cmp(i, j, val, <))
    #define swap(i, j)  do {    \
        KEY temp = arr[i];      \
        arr[i] = arr[j];        \
        arr[j] = temp;          \
        } while (0)   

    unsigned start = 0, end = --length;
    if (end - start == 1 && less_than(end, start)) {
        swap(end, start);
        return;
    }
    else while (start < end) {
        if (less_than(length, start)) {
            end--;
            swap(start, end);
        }
        else start++;
    }
    swap(end, length);
    if (end) sort_inplace_rec(arr, end);
    if (length - end) sort_inplace_rec(arr + end + 1, length - end);

    #undef cmp
    #undef less_than
    #undef swap
}

/**
 * Sorts matrix and vector by vector's elements inplace.
 * Messes up memory layout!!!
 */
static int sort_inplace(MAT_AND_VEC *U) {
    #define at(t, i)   v_at(U->t, i)

    unsigned length = len(U->vector), i;
    KEY *vps = (KEY *) malloc(length * sizeof(KEY));
    double **new_data = (double **) malloc(length * sizeof(double *));
    if (!vps || !new_data) return 1;

    for (i = 0; i < length; i++) {
        KEY temp;
        temp.val = at(vector, i);
        temp.pos = i;
        vps[i] = temp;
    }
    sort_inplace_rec(vps, length);
    for (i = 0; i < length; i++)
        new_data[i] = at(matrix, vps[i].pos);
    free(U->matrix->data);
    U->matrix->data = new_data;
    for (i = 0; i < length; i++)
        at(vector, i) = vps[i].val;
    free(vps);
    return 0;

    #undef at
}

MATRIX *reduced_vectors(MAT_AND_VEC U) {
    unsigned length = U.vector->length, k = 0, i, j;
    double max = -1;
    MATRIX *res;

    if (sort_inplace(&U)) return NULL;

    for (i = 0; i < length / 2; i++) {
        double delta = v_at(U.vector, length - 1 - i) - v_at(U.vector, length - 2 - i);
        if (delta > max) {
            max = delta;
            k = i;
        }
    }

    res = alloc_matrix(U.matrix->num_rows, ++k);
    if (!res) return NULL;
    for (j = 0; j < k; j ++) for (i = 0; i < U.matrix->num_rows; i++)
        m_at(res, i, j) = m_at(U.matrix, i, j);
    return res;
}

void renormalize_inplace(MATRIX *U) {
    unsigned i, j;
    for (i = 0; i < U->num_rows; i++) {
        double norma = 0;
        for (j = 0; j < U->num_cols; j++)
            norma += m_at(U, i, j) * m_at(U, i, j);
        norma = sqrt(norma);
        for (j = 0; j < U->num_cols; j++)
            m_at(U, i, j) /= norma;
    }
}