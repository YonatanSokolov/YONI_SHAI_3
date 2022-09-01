#include "myIO.h"
#include <stddef.h>
#include <stdio.h>

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

    res = alloc_matrix(vec_dim, num_vecs);
    if (is_null(res)) return NULL_MATRIX;

    /* read data from file into memory */
    {
        unsigned i, j;
        for (j = 0; j < num_vecs; j++)
            for (i = 0; i < vec_dim; i++) {
                fscanf(file, "%lf", &m_at(res, i, j));
                getc(file);
            }
    }
    
    fclose(file);
    return res;
}