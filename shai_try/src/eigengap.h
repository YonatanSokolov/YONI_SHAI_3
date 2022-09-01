#ifndef __eigengap__
#define __eigengap__

#include "datastructures.h"

/**
 * Determine k via eigengap heuristic, and reduce input to k columns. 
 * Assumes input vector has an eigenvalue for each column of input matrix.
 */
MATRIX reduced_vectors(MAT_AND_VEC U);

/**
 * Renormalizes given matrix's rows
 */
void renormalize_inplace(MATRIX U);

#endif /*__eigengap__*/
