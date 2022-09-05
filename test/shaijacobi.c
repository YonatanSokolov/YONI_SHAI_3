#include "../src/myIO.h"
#include "../src/shaijacobi.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

#define espsilon 0.0001

void test_eigenvalues_eigenvectors() {
    MATRIX A = read_vectors_from_file("test/shaijaconi_samp1.txt");
    // printf("S = \n");
    // print_matrix(A);
    MAT_AND_VEC res = eigenvalues_eigenvectors(A);
    MAT_AND_VEC prob_res = {
        .vector = {3, (double []) {1.6099,0.2357,1.1545}},
        .matrix = {3, 3, 
            (double []) {0.7283,0.6565,-0.1964,-0.6712,0.6256,-0.3976,-0.1381,0.4214,0.8963}
        }
    };
    // printf("res = \n");
    // print_matrix_and_vector(res);
    
    assert(!is_null(res.matrix));
    assert(!is_null(res.vector));
    assert(res.matrix.num_cols == 3);
    assert(res.matrix.num_rows == 3);
    assert(res.vector.length == 3);
    for (int i = 0; i < 3; i++)
        assert(fabs(v_at(res.vector, i) - v_at(prob_res.vector, i)) < espsilon);
    for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++)
        assert(fabs(m_at(res.matrix, i, j) - m_at(prob_res.matrix, i, j)) < espsilon);

    free_matrix(A);
    free_matrix(res.matrix);
    free_vector(res.vector);

    // A = read_vectors_from_file("test/shaijaconi_samp2.txt");
    // // printf("%u %u\n", A.num_rows, A.num_cols);
    // printf("S = \n");
    // print_matrix(A);
    // res = eigenvalues_eigenvectors(A);
    // printf("res = \n");
    // print_matrix_and_vector(res);
    // free_matrix(A);
    // free_matrix(res.matrix);
    // free_vector(res.vector);

    // A = read_vectors_from_file("test/shaijaconi_samp3.txt");
    // printf("S = \n");
    // print_matrix(A);
    // res = eigenvalues_eigenvectors(A);
    // printf("res = \n");
    // print_matrix_and_vector(res);
    // free_matrix(A);
    // free_matrix(res.matrix);
    // free_vector(res.vector);

    // A = read_vectors_from_file("test/shaijaconi_samp4.txt");
    // printf("S = \n");
    // print_matrix(A);
    // res = eigenvalues_eigenvectors(A);
    // printf("res = \n");
    // print_matrix_and_vector(res);
    // free_matrix(A);
    // free_matrix(res.matrix);
    // free_vector(res.vector);

    printf("~test~ eigenvalues_eigenvectors DONE\n");

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