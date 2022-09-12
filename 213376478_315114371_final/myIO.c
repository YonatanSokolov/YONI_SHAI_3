#include "myIO.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

MATRIX read_vectors_from_file(const char *file_name) {
    FILE *file = fopen(file_name, "r");
    MATRIX res;
    unsigned vec_dim = 1, num_vecs = 1;
    if (!file) return NULL_MATRIX;

    /* find vec_dim and num_vecs */
    {
        int c;
        for (c = getc(file); c != '\n'; c = getc(file))
            if (c == ',') vec_dim++;
        for (c = getc(file); c != EOF; c = getc(file))
            if (c == '\n') num_vecs++;
        fseek(file, 0, SEEK_SET);
    }

    res = alloc_matrix(num_vecs, vec_dim);
    if (is_null(res)) return NULL_MATRIX;

    /* read data from file into memory */
    {
        unsigned i, j;
        for (i = 0; i < num_vecs; i++)
            for (j = 0; j < vec_dim; j++) {
                fscanf(file, "%lf", &m_at(res, i, j));
                getc(file);
            }
    }
    
    fclose(file);
    return res;
}

void print_matrix(MATRIX M) {
    unsigned i, j;
    for (i = 0; i < M.num_rows; i++) for(j = 0; j < M.num_cols; j++)
        printf("%.4f%c", m_at(M, i, j), j + 1 == M.num_cols ? '\n' : ',');
}

void print_matrix_and_vector(MAT_AND_VEC mav) {
    unsigned i;
    for (i = 0; i < mav.vector.length; i++)
        printf("%.4f%c", v_at(mav.vector, i), i + 1 == mav.vector.length ? '\n' : ',');
    print_matrix(mav.matrix);
}

void print_diagonal_matrix(DIAGONAL_MATRIX D) {
    unsigned i, j;
    for (i = 0; i < D.length; i++) for(j = 0; j < D.length; j++)
        printf("%.4f%c", i == j ? v_at(D, i) : 0, j + 1 == D.length ? '\n' : ',');
}

static int string_compare(char *s1, char *s2) {
    while (*s1 && *s2 && *s1++ == *s2++);
    return *s1 == *s2;
}

int has_input_file_name_format(char *string) {
    int length = strlen(string);
    if (length < 4) return 0;
    string += length - 4;
    if (*string++ != '.') return 0;
    if (*string == 'c') 
        return string_compare(string, "csv");
    else return string_compare(string, "txt");
}

GOAL goal_from_string(char *string) {
    switch (string[0]) {
        case 'w':
        return string_compare(string, "wam")    ? WAM    : INVALID;
        case 'd':
        return string_compare(string, "ddg")    ? DDG    : INVALID;
        case 'l':
        return string_compare(string, "lnorm")  ? LNORM  : INVALID;
        case 'j':
        return string_compare(string, "jacobi") ? JACOBI : INVALID;
        default:
        return INVALID;
    }
}