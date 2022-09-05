#ifndef __shaijacobi__
#define __shaijacobi__

#include "datastructures.h"

/**
 * Runs the Jacobi algorithm for given input.
 * Assumes given matrix is symetric.
 * Corrupts given matrix!
 */ 
MAT_AND_VEC eigenvalues_eigenvectors(MATRIX S);


#endif /*__shaijacobi__*/