#include "../src/eigengap.h"
#include "../src/myIO.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void test_reduced_vectors() {
    MATRIX M = read_vectors_from_file("test/eigengap_samp1.txt");
    // print_matrix(M);
    // double evals[];
    VECTOR V = {.data = (double []) {9.,2.,4.,6.,1.,1.,8.}, .length = 7};
    MAT_AND_VEC input = {M, V};
    unsigned k = k_and_sort_inplace(&input);
    // print_matrix(input.matrix);
    MATRIX result = reduced_vectors(input.matrix, k);

    assert(!is_null(result));
    // printf("num_cols = %u\n", result->num_cols);
    // printf("%u\n", result->num_cols);
    assert(result.num_cols == 2);
    // print_matrix(result);
    assert(m_at(result, 0, 0) == 9);
    assert(m_at(result, 0, 1) == 8);

    // printf("%p\n", M->data[0]);
    free_matrix(input.matrix);
    // free_vector(V);
    free_matrix(result);

    printf("test reduced_vectors DONE\n");
}

void test_renormalize_inplace() {
    MATRIX M = read_vectors_from_file("test/eigengap_samp2.txt");
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
