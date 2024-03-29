#include "../src/lnorm.h"
#include "../src/myIO.h"
#include <assert.h>
#include <stdio.h>
#include <math.h>

#define EPSILON 0.0000000000000001


void test_diagonal_degree_matrix() {
    MATRIX W = read_vectors_from_file("test/lnorm_samp1.txt");
    DIAGONAL_MATRIX D = diagonal_degree_matrix(W);
    assert(!is_null(D));
    assert(D.length == 3);
    assert(v_at(D, 0) == 3);
    assert(v_at(D, 0) == 3);
    assert(v_at(D, 0) == 3);

    free_matrix(W);
    free_vector(D);
    printf("test diagonal_degree_matric DONE\n");
}

void test_normalized_graph_laplacian() {
    MATRIX W = read_vectors_from_file("test/lnorm_samp1.txt");
    DIAGONAL_MATRIX D = diagonal_degree_matrix(W);
    MATRIX L = normalized_graph_laplacian(W, D);

    assert(!is_null(L));
    assert(L.num_cols == L.num_rows && L.num_cols == 3);
    for (unsigned i = 0; i < 3; i++)
        for (unsigned j = i + 1; j < 3; j++)
            assert(m_at(L, i, j) == m_at(L, j, i));
    for (unsigned i = 0; i < 3; i++)
        assert(m_at(L, i, i) == 1);
    
    assert(m_at(L, 0, 1) + sqrt(3.0)/6 < EPSILON);
    assert(m_at(L, 0, 2) + 2/sqrt(15.0) < EPSILON);
    assert(m_at(L, 1, 2) + 3*sqrt(5.0)/10 < EPSILON);
    // printf("assert %lf = %lf\n", m_at(L, 0, 1), -sqrt(3.0)/6);
    // printf("assert %lf = %lf\n", m_at(L, 0, 2), -2/sqrt(15.0));
    // printf("assert %lf = %lf\n", m_at(L, 1, 2), -3*sqrt(5.0)/10);

    free_matrix(W);
    free_vector(D);
    free_matrix(L);
    printf("test normalized_graph_laplacian DONE\n");
}

int main(int argc, char **argv) {
    test_diagonal_degree_matrix();
    test_normalized_graph_laplacian();
}