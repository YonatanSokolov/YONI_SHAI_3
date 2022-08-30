#include "../src/eigengap.h"
#include "../src/myIO.h"
#include <stdio.h>
#include <assert.h>

void test_reduced_vectors() {
    MATRIX *M = read_vectors_from_file("test/eigengap_samp1.txt");
    VECTOR *V = & (VECTOR) {.data = v_at(M, 0), .length = 7};
    for (int i = 0; i < 7; i++) printf("%lf, ", v_at(V, i));
    printf("\n");
    MAT_AND_VEC input = {M, V};
    MATRIX *result = reduced_vectors(input);

    assert(result);
    printf("num_cols = %u\n", result->num_cols);
    assert(result->num_cols == 2);
    assert(m_at(result, 0, 0) == 9);
    assert(m_at(result, 0, 1) == 9);

    free_matrix(M);
    free_vector(V);
    free_matrix(result);

    printf("test reduced_vectors DONE\n");
}

int main(int argc, char **argv) {
    test_reduced_vectors();
    return 0;
}
