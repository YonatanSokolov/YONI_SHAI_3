#ifndef __eigengap__
#define __eigengap__

#include "datastructures.h"

/**
 * Sorts matrix and vector by vector's elements inplace.
 * Returns 0 on success.
 */
int sort_inplace(MAT_AND_VEC *U);

/**
 * Determine k via eigengap heuristic, and reduce input to k columns. 
 * Assumes input vector has an eigenvalue for each column of input matrix.
 */
unsigned k_and_sort_inplace(MAT_AND_VEC *U);

/**
 * Reduce input to k columns. 
 */
MATRIX reduced_vectors(MATRIX U, unsigned k);

/**
 * Renormalizes given matrix's rows
 * Returns 0 on success.
 */
void renormalize_inplace(MATRIX U);

#endif /*__eigengap__*/
