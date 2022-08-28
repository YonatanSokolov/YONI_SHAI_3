#include "../src/myIO.h"
#include <assert.h>
#include <stdio.h>

void test_read_vectors_from_file() {
    MATRIX *vecs = read_vectors_from_file("test/myIO_samp1");
    assert(vecs);
    assert(vecs->num_cols == 2);
    assert(vecs->num_rows == 3);
    assert(get_m(vecs, 2, 1) == 3.1);
    printf("test read_vectors_from_file DONE\n");
}

int main(int argc, char **argv) {
    test_read_vectors_from_file();
    return 0;
}