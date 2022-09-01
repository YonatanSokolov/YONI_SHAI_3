#include "../src/eigengap.h"
#include "../src/myIO.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void test_reduced_vectors() {
    MATRIX *M = read_vectors_from_file("test/eigengap_samp1.txt");
    VECTOR *V = & (VECTOR) {.data = v_at(M, 0), .length = 7};
    MAT_AND_VEC input = {M, V};
    double *data = M->data[0];
    MATRIX *result = reduced_vectors(input);

    assert(result);
    // printf("num_cols = %u\n", result->num_cols);
    // printf("%u\n", result->num_cols);
    assert(result->num_cols == 2);
    assert(m_at(result, 0, 0) == 3);
    assert(m_at(result, 0, 1) == 3);

    // printf("%p\n", M->data[0]);
    free(data);
    free(M->data);
    free(M);
    // free_matrix(M);
    // free_vector(V);
    free_matrix(result);

    printf("test reduced_vectors DONE\n");
}

void test_renormalize_inplace() {
    MATRIX *M = read_vectors_from_file("test/eigengap_samp2.txt");
    double res[] = {0.6, 0.8, 0, 1, 0, 0, 1, 0, 0};

    renormalize_inplace(M);

    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) 
        assert(m_at(M, i, j) == res[3*i + j]);

    free_matrix(M);

    printf("test renormalize_inplace DONE\n");
}

int main(int argc, char **argv) {
    test_reduced_vectors();
    test_renormalize_inplace();
    return 0;
}
