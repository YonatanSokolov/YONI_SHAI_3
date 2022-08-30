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
void sort_VAL_W_POS_rec(VAL_W_POS *arr, unsigned length) {
    #define swap(i, j)  do {       \
        VAL_W_POS temp = arr[i];   \
        arr[i] = arr[j];           \
        arr[j] = temp;             \
        } while (0)   

    #define larger(i, j)    ((arr[i].val == arr[j].val) ? (arr[i].pos < arr[j].pos) : (arr[i].val > arr[j].val))

    printf("length = %u\n", length);
    unsigned start = 0, end = --length;
    for (int i = 0; i <= length; i++) printf("%lf, ", arr[i].val);
    printf("\n");

    // printf("start = %u, end = %u\n", start, end);
    if (end - start == 1) {
        if (larger(end, start)) swap(end, start);
        printf("5) %u %u %u\n", start, end, length);

    }
    else while (start < end) {
        printf("10) %u %u %u\n", start, end, length);
        printf("15) %d %d\n", (arr[length].val > arr[start].val), (arr[length].pos < arr[start].pos));
        if (larger(length, start)) {
            printf("20) %u %u %u\n", start, end, length);
            end--;
            swap(start, end);
        }
        else start++;
    }
    printf("* start = %u, end = %u\n", start, end);
    swap(end, length);
    for (int i = 0; i <= length; i++) printf("%lf, ", arr[i].val);
    printf("\n");
    printf("l start = %lf, length = %u\n", arr->val, end);
    if (end) sort_VAL_W_POS_rec(arr, end);
    printf("r start = %lf, length = %u\n", (arr + end + 1)->val, length - end);
    if (length - end) sort_VAL_W_POS_rec(arr + end + 1, length - end);
    }

int main(int argc, char **argv) {
    #define L   7

    VAL_W_POS arr[L] = {{9, 0}, {1, 1}, {4, 2}, {6, 3}, {1, 4}, {1, 5}, {8, 6}};

    // #define L   5

    // VAL_W_POS arr[L] = {{6, 1}, {1, 2}, {1, 3}, {1, 4}, {4, 5}};
    
    sort_VAL_W_POS_rec(arr, L);
    printf("----------\n");
    for (int i = 0; i < L; i++) printf("%lf, %u\n", arr[i].val, arr[i].pos);
    return 0;
}