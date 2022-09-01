#ifndef __lnorm__
#define __lnorm__

#include "datastructures.h"

/**
 * Calculate the diagnal degree matrix from a weighted adjacency matrix.
 * Assumes W in symetric.
 */
DIAGONAL_MATRIX diagonal_degree_matrix(const MATRIX W);

/**
 * Calculates the normalized graph Laplacian from a weighted 
 * adjacency matrix and its diagonal degree matrix.
 * Assumes W is symetric, and of dimention equal to D's.
 */
MATRIX normalized_graph_laplacian(const MATRIX W, const DIAGONAL_MATRIX D);

#endif /*__lnorm__*/