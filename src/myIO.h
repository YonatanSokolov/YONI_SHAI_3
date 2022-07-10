/**
 * Prints given matrix.
 * @param   M pointer to matrix to be printed
 * @return  void
 */
void printMatrix(MATRIX *M);

/**
 * Read matrix in csv format from file. Assumes input validity. 
 * @param   fileName name of file containing matrix
 * @return  pointer to read matrix
 */
MATRIX *readMatrixFromFile(string filename);

/**
 * Prints given vector.
 * @param   v vector to be printed
 * @param   length length of given vector
 * @return  void
 */
void printVector(VECTOR v, int length);