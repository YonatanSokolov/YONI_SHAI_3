/**
 * Calculates weighted adjacency matrix (W).
 * @param   data vectors whose W is calculated
 * @return  pointer to W
 */
MATRIX *weightedAdjacencyMatrix(MATRIX *data);

/**
 * Calculates diagonal degree matrix (D).
 * @param   W weighted adjacency matrix whose D is calculated
 * @return  D (represented by its principal diagonal)
 */
VECTOR diagonalDegreeMatrix(MATRIX *W);

/**
 * Calculates normalized graph laplacian (L). Overwrites W with L.
 * D is modified.
 * @param   W weighted adjacency matrix whose L is calculated
 * @param   D diagonal degree matrix of W
 * 
 * @return  void
 */
void normalizedGraphLaplacian(MATRIX *W, VECTOR D);

/**
 * Calculates all eigenvalues (v) and eigenvectors (V).
 * S is modified.
 * @param   S symmetric full rank matrix whose v and V are calculated
 * @return  vector v, 
 *          and matrix V, where its 'i'th column is an eigenvector of v[i]
 */
MATRIX_WITH_VECTOR *eigenvaluesAndEigenvectors(MATRIX *S);