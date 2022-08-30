#include "eigengap.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

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

    #define larger(i, j)    ((arr[i].val > arr[j].val) ?: (arr[i].pos > arr[j].pos))

    unsigned start = 0, end = length;
    if (end - start == 2) {
        if (larger(end - 1, start)) swap(end - 1, start);
    }
    else if (end - start > 2) {
        while (start + 1 < end) {
            if (larger(length - 1, start)) {
                end--;
                swap(start, end);
            }
            else start++;
        }
        swap(end, length - 1);
        sort_VAL_W_POS_rec(arr, end);
        sort_VAL_W_POS_rec(arr + (end+1)*sizeof(VAL_W_POS), length - end - 1);
    }
}

/**
 * Sorts matrix and vector by vector's elements inplace.
 */
static int sort_by_vector(MAT_AND_VEC *U, unsigned start, unsigned end) {
    #define at(t, i)   v_at(U->t, i)

    unsigned length = len(U->vector), i;
    VAL_W_POS *vps = (VAL_W_POS *) malloc(length * sizeof(VAL_W_POS));
    double **new_data = (double **) malloc(length * sizeof(double *));
    if (!vps || !new_data) return 1;

    for (i = 0; i < length; i++) 
        vps[i] = (VAL_W_POS) {.val = at(vector, i), .pos = i};
    sort_VAL_W_POS_rec(vps, length);
    for (i = 0; i < length; i++)
        new_data[i] = at(matrix, vps[i].pos);
    U->matrix->data = new_data;
    for (i = 0; i < length; i++)
        at(vector, i) = vps[i].val;
    return 0;
}

MATRIX *reduced_vectors(MAT_AND_VEC U) {
    unsigned length = U.vector->length, k = 0;
    double max = -1;
    if (sort_by_vector_inplace(0, length)) return NULL;


}