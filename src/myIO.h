#ifndef __myIO__
#define __myIO__

#include "datastructures.h"

/**
 * Reads vectors form file with given file name.
 * Each row is treated as a vector.
 * Returns a matrix, with a column for each vector, or NULL on failure.
 * Assumes correct formatting of file and of file_name.
 */
MATRIX read_vectors_from_file(const char *file_name);

void print_matrix(MATRIX M);

void print_matrix_and_vector(MAT_AND_VEC mav);

void print_diagonal_matrix(DIAGONAL_MATRIX D);

int has_input_file_name_format(char *string);



#endif /*__myIO__*/