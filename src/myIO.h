#ifndef __myIO__
#define __myIO__

#include "datastructures.h"

/**
 * Reads vectors form file with given file name.
 * Each row is treated as a vector.
 * Returns a matrix, with a column for each vector.
 * Assumes correct formatting of file.
 */
const MATRIX read_vectors_from_file(const char *file_name);

#endif //__myIO__