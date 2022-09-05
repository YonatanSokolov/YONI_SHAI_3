#include "../src/myIO.h"
#include "../src/shaijacobi.h"
#include <assert.h>
#include <stdio.h>

void test_eigenvalues_eigenvectors() {
    MATRIX A = read_vectors_from_file("test/shaijaconi_samp1.txt");

    printf("S = \n");
    print_matrix(A);

    MAT_AND_VEC res = eigenvalues_eigenvectors(A);
    printf("res = \n");
    print_matrix_and_vector(res);

    free_matrix(A);
    free_matrix(res.matrix);
    free_vector(res.vector);
    printf("test eigenvalues_eigenvectors DONE\n");

    /* should print:
            S = 
            1.0000,-0.6000,-0.3000
            -0.6000,1.0000,-0.2000
            -0.3000,-0.2000,1.0000
            res = 
            1.6099,0.2357,1.1545
            0.7283,0.6565,-0.1964
            -0.6712,0.6256,-0.3976
            -0.1381,0.4214,0.8963
    */
}

int main(int argc, char **argv) {
    test_eigenvalues_eigenvectors();
    return 0;
}