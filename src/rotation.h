/**
 * ROTATION represents the Jacobi rotation matrix of the form:
 * https://wikimedia.org/api/rest_v1/media/math/render/svg/2bb748aa40e4567df12134656077867df44a02cd 
 * @invariant i < j
 * @invariant c = cos(phi), s = sin(phi) for some angle phi
 */
typedef struct rotation_t {
    double c, s;
    int i, j;
} ROTATION;

/**
 * Creates new rotation.
 * @param   c c of new rotation
 * @param   s s of new rotation
 * @param   i i of new rotation
 * @param   j j of new rotation
 * @return  pointer to new rotation
 */
ROTATION *newRotation(double c, double s, int i, int j);

/**
 * Frees memory of given rotation.
 * @param   P rotation to be cleared
 * @return  void
 */
void freeRotation(ROTATION *P);

/**
 * Left-multiplies given matrix by given rotation.
 * @param   M matrix to be multiplied
 * @param   P rotation to multiply by
 * @return  void
 */
void leftRotate(MATRIX *M, ROTATION *P);

/**
 * Transform given symetric matrix by given rotation (M -> (P^T)*M*P).
 * Assumes P nullifies of diagonals (M)ij.
 * @param   M matrix to be transformed
 * @param   P rotation to transform by
 * @return  void
 */
void pivot(MATRIX *M, ROTATION *P);