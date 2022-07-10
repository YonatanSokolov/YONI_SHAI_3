#define VECTOR      double *

/**
 * Calculates the l2 norm of the difference of the given vectors.
 * @param   length length of given vectors
 * @param   u first given vector
 * @param   v second given vector
 * @return  calculated l2 norm of (u-v)
 */
double normOfDifference(int length, VECTOR u, VECTOR v);