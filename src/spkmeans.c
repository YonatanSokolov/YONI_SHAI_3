#include "spkmeans.h"
#include "myIO.h"
#include "calculate_w.h"
#include "lnorm.h"
#include "eigengap.h"
#include <stdio.h>
#include <stdlib.h>

#define ERROR_MSG "An Error Has Occurred"
#define INVALID_INPUT_MSG "Invalid Input!"
#define terminate(msg)      do { printf("%s\n", msg); exit(1); } while(0)

int run(GOAL goal, const char *file_name) {
    MATRIX X = read_vectors_from_file(file_name);
    if (is_null(X)) return 1;
    if (goal == JACOBI) {
        /* TODO run Jacobi algo */
    }
    else /* goal in {WAM, DDG, LNORM} */ {
        MATRIX W, L; DIAGONAL_MATRIX D;
        W = /* TODO func tha clacs W */ NULL_MATRIX;
        if (is_null(W)) return 1;
        if (goal == WAM) {
            print_matrix(W);
            return 0;
        }
        D = diagonal_degree_matrix(W);
        if (is_null(D)) return 1;
        if (goal == DDG) {
            print_diagonal_matrix(D);
            return 0;
        }
        L = normalized_graph_laplacian(W, D);
        if (is_null(L)) return 1;
        if (goal == LNORM) {
            print_matrix(L);
            return 0;
        }
    }
    return 2;
}

MATRIX spectralization(const char *file_name, unsigned k) {
    MATRIX X, W, L, T; DIAGONAL_MATRIX D; MAT_AND_VEC U; 

    X = read_vectors_from_file(file_name);
    if (is_null(X)) return NULL_MATRIX;
    /* TODO calc W */
    if (is_null(W)) return NULL_MATRIX;
    D = diagonal_degree_matrix(W);
    if (is_null(D)) return NULL_MATRIX;
    L = normalized_graph_laplacian(W, D);\
    if (is_null(L)) return NULL_MATRIX;
    /* TODO jacobi */
    if (k > 0) sort_inplace(&U);
    else k = k_and_sort_inplace(&U);
    T = reduced_vectors(U.matrix, k);
    if (is_null(T)) return NULL_MATRIX;
    return T;
}

int main (int argc, char **argv) {
    if (argc != 3) terminate(INVALID_INPUT_MSG);
    if (!has_input_file_name_format(argv[2])) terminate(INVALID_INPUT_MSG);
    /* TODO find goal */
    return 0;
}