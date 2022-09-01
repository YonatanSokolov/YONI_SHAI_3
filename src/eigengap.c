#include "eigengap.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    double val;
    unsigned pos;
} KEY;

/**
 * Quick-sort a key array.
 */
static void sort_inplace_rec(KEY *arr, unsigned length) {
    #define cmp(i, j, f, c)   (arr[i].f c arr[j].f)
    #define greater(i, j)       \
        (cmp(i, j, val, ==) * cmp(i, j, pos, <) + cmp(i, j, val, >))
    #define swap(i, j)  do {    \
        KEY temp = arr[i];      \
        arr[i] = arr[j];        \
        arr[j] = temp;          \
        } while (0)   

    unsigned start = 0, end = --length;
    if (end - start == 1 && greater(end, start)) {
        swap(end, start);
        return;
    }
    else while (start < end) {
        if (greater(length, start)) {
            end--;
            swap(start, end);
        }
        else start++;
    }
    swap(end, length);
    if (end) sort_inplace_rec(arr, end);
    if (length - end) sort_inplace_rec(arr + end + 1, length - end);

    #undef cmp
    #undef greater
    #undef swap
}

/**
 * Sorts matrix and vector by vector's elements inplace.
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
    U->matrix->data = new_data;
    for (i = 0; i < length; i++)
        at(vector, i) = vps[i].val;
    return 0;

    #undef at
}

MATRIX *reduced_vectors(MAT_AND_VEC U) {
    unsigned length = U.vector->length, k, i, j;
    double max = -1;
    MATRIX *res;

    if (sort_inplace(&U)) return NULL;

    for (i = 0; i < length / 2; i++) {
        double delta = v_at(U.vector, i) - v_at(U.vector, i + 1);
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