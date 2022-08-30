#include "eigengap.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <stdio.h>

typedef struct {
    double val;
    unsigned pos;
} VAL_W_POS;

/**
 * Quick-sort a VAL_W_POS array.
 */
static void sort_VAL_W_POS_rec(VAL_W_POS *arr, unsigned length) {
    #define swap(i, j)  do {       \
        VAL_W_POS temp = arr[i];   \
        arr[i] = arr[j];           \
        arr[j] = temp;             \
        } while (0)   

    #define larger(i, j)    ((arr[i].val > arr[j].val) ? true : (arr[i].pos < arr[j].pos))

    unsigned start = 0, end = --length;
    if (end - start == 1) {
        if (larger(end, start)) swap(end, start);
    }
    else while (start < end) {
        if (larger(length, start)) {
            end--;
            swap(start, end);
        }
        else start++;
    }
    swap(end, length);
    if (end) sort_VAL_W_POS_rec(arr, end);
    if (length - end) sort_VAL_W_POS_rec(arr + end + 1, length - end);
}

/**
 * Sorts matrix and vector by vector's elements inplace.
 */
static int sort_by_vector(MAT_AND_VEC *U) {
    #define at(t, i)   v_at(U->t, i)

    unsigned length = len(U->vector), i;
    VAL_W_POS *vps = (VAL_W_POS *) malloc(length * sizeof(VAL_W_POS));
    double **new_data = (double **) malloc(length * sizeof(double *));
    if (!vps || !new_data) return 1;

    for (i = 0; i < length; i++) {
        VAL_W_POS temp;
        temp.val = at(vector, i);
        temp.pos = i;
        vps[i] = temp;
    }
    sort_VAL_W_POS_rec(vps, length);
    for (i = 0; i < length; i++)
        new_data[i] = at(matrix, vps[i].pos);
    U->matrix->data = new_data;
    for (i = 0; i < length; i++) {
        at(vector, i) = vps[i].val;
        printf("%f\n", vps[i].val);
    }
    return 0;
}

MATRIX *reduced_vectors(MAT_AND_VEC U) {
    unsigned length = U.vector->length, k, i;
    double max = -1;

    for (i = 0; i < length; i++) printf("%f, ", v_at(U.vector, i));
    printf("\n");

    if (sort_by_vector(&U)) return NULL;

    for (i = 0; i < length; i++) printf("%f, ", v_at(U.vector, i));
    printf("\n");

    for (i = 0; i < length / 2; i++) {
        double delta = v_at(U.vector, i) - v_at(U.vector, i + 1);
        if (delta > max) {
            max = delta;
            k = i;
        }
    }

    {
        MATRIX *res = alloc_matrix(U.matrix->num_rows, k);
        if (!res) return NULL;
        memcpy(res->data, U.matrix->data, k * sizeof(double *));
        return res;
    }
}