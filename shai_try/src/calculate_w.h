#ifndef __calculate_w__
#define __calculate_w__
#include "datastructures.h"
/**
 * Calculates L2 distance between two vectors (given Vector->data)
 */
double distance_L2(double *v1, double *v2, unsigned int len);

/**
 * Creates the Weighted Adjacency Matrix and Calculates it, and returns it.
 */
MATRIX *create_W(MATRIX *V);

#endif /*__datastructures__*/