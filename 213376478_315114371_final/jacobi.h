#ifndef __jacobi__
#define __jacobi__

#include "datastructures.h"

/**
 * Runs the Jacobi algorithm for given input.
 * Assumes given matrix is symetric.
 * Corrupts given matrix!
 */ 
MAT_AND_VEC eigenvalues_eigenvectors(MATRIX S);


#endif /*__jacobi__*/