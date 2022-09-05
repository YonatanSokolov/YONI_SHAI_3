#include "../src/datastructures.h"
#include <stdio.h>
#include <assert.h>

void test_alloc_vector() {
    MATRIX ATAG = {1, 2, NULL};

    VECTOR v1 = alloc_vector(ATAG.num_cols);
    v_at(v1, 1) = 2;
    assert(!is_null(v1));
    assert(v1.length == 2);
    assert(v_at(v1, 1) == 2);

    printf("test alloc_vector DONE\n");
}

int main(int argc, char **argv) {
    test_alloc_vector();
    return 0;
}