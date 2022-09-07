#include "spkmeans.h"
#include "myIO.h"
#include "calculate_w.h"
#include "lnorm.h"
#include "eigengap.h"
#include "Jacobi_algo.h"
#include <stdio.h>
#include <stdlib.h>

#define ERROR_MSG "An Error Has Occurred"
#define INVALID_INPUT_MSG "Invalid Input!"
#define terminate(msg)      do { printf("%s\n", msg); exit(1); } while(0)

int run(GOAL goal, const char *file_name) {
    MATRIX X = read_vectors_from_file(file_name);
    if (is_null(X)) return 1;
    if (goal == JACOBI) {
        MAT_AND_VEC U = Jacobi_algo(X);
        free_matrix(X);
        if (is_null(U.matrix)) return 1;
        print_matrix_and_vector(U);
        return 0;
    }
    else /* goal in {WAM, DDG, LNORM} */ {
        MATRIX W = NULL_MATRIX, L = NULL_MATRIX; 
        DIAGONAL_MATRIX D = NULL_VECTOR;

        #define exit_func(status) do {  \
            free_matrix(X);             \
            free_matrix(W);             \
            free_matrix(L);             \
            free_vector(D);             \
            return status;              \
            } while (0)

        W = create_W(X);
        if (is_null(W)) exit_func(1);
        if (goal == WAM) {
            print_matrix(W);
            exit_func(0);
        }
        D = diagonal_degree_matrix(W);
        if (is_null(D)) exit_func(1);
        if (goal == DDG) {
            print_diagonal_matrix(D);
            exit_func(0);
        }
        L = normalized_graph_laplacian(W, D);
        if (is_null(L)) exit_func(1);
        if (goal == LNORM) {
            print_matrix(L);
            exit_func(0);
        }
        exit_func(2);

        #undef exit_func
    }
    return 3;

}

MATRIX spectralization(const char *file_name, unsigned k) {
    MATRIX X, W, L, T; DIAGONAL_MATRIX D; MAT_AND_VEC U; 

    X = read_vectors_from_file(file_name);
    if (is_null(X)) return NULL_MATRIX;
    if (k >= X.num_rows) return NULL_MATRIX;
    W = create_W(X);
    free_matrix(X);
    if (is_null(W)) return NULL_MATRIX;
    D = diagonal_degree_matrix(W);
    if (is_null(D)) return NULL_MATRIX;
    L = normalized_graph_laplacian(W, D);
    free_matrix(W); free_vector(D);
    if (is_null(L)) return NULL_MATRIX;
    /* TODO jacobi */
    free_matrix(L);
    if (k > 0) sort_inplace(&U);
    else k = k_and_sort_inplace(&U);
    T = reduced_vectors(U.matrix, k);
    free_matrix(U.matrix); free_vector(U.vector);
    if (is_null(T)) return NULL_MATRIX;
    return T;
}

int main (int argc, char **argv) {
    GOAL goal;

    if (argc != 3) 
        terminate(INVALID_INPUT_MSG);
    goal = goal_from_string(argv[1]);
    if (goal == INVALID)
        terminate(INVALID_INPUT_MSG);
    if (!has_input_file_name_format(argv[2])) 
        terminate(INVALID_INPUT_MSG);
     if (run(goal, argv[2]))
        terminate(ERROR_MSG);
    return 0;
}