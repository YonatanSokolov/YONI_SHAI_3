#include "../src/universal.h"

void testWeightedAdjacencyMatrix1() {
    MATRIX *data = readMatrixFromFile("test/12matrix.txt");
    MATRIX *W = weightedAdjacencyMatrix(data);

    assert(W->colCnt == 2 && W->rowCnt == 2);
    assert(mCell(W, 0, 0) == 0 && mCell(W, 1, 1) == 0);
    double w = exp(-0.5 * sqrt(3));
    assert(mCell(W, 0, 1) == w && mCell(W, 1, 0) == w);

    freeMatrix(data);
    freeMatrix(W);
    println("weightedAdjacencyMatrix I test complete");
}

void testWeightedAdjacencyMatrix2() {
    MATRIX *data = readMatrixFromFile("test/105data.csv");
    MATRIX *W = weightedAdjacencyMatrix(data);

    for (int i = 0; i < 3; i++)
        for (int j = i; j < 3; j++)
            if (i == j) assert(mCell(W, i, j) == 0);
            else assert(mCell(W, i, j) == mCell(W, j, i));
    assert(mCell(W, 0, 1) == exp(-1));
    assert(mCell(W, 0, 2) == exp(-0.5 * sqrt(19)));
    assert(mCell(W, 1, 2) == exp(-2.5));

    freeMatrix(data);
    freeMatrix(W);
    println("weightedAdjacencyMatrix II test complete");
}

void testDiagonalDegreeMatrix() {
    MATRIX *data = readMatrixFromFile("test/105data.csv");
    MATRIX *W = weightedAdjacencyMatrix(data);
    VECTOR D = diagonalDegreeMatrix(W);

    assert(D[0] == exp(-1) + exp(-0.5 * sqrt(19)));
    assert(D[1] == exp(-1) + exp(-2.5));
    assert(D[2] == exp(-2.5) + exp(-0.5 * sqrt(19)));


    println("diagonalDegreeMatrix test complete");
}

void testNormalizedGraphLaplacian() {
    MATRIX *A = readMatrixFromFile("test/345matrix.txt");
    VECTOR D = diagonalDegreeMatrix(A);
    normalizedGraphLaplacian(A, D);

    // A = [[1 0 -0.6] [0 1 -0.8] [-0.6 -0.8 1]]
    forRange(3, assert(mCell(A, i, i) == 1));
    assert(mCell(A, 0, 1) ==  0   && mCell(A, 1, 0) ==  0  );
    assert(mCell(A, 0, 2) == -0.6 && mCell(A, 2, 0) == -0.6);
    assert(mCell(A, 1, 2) == -0.8 && mCell(A, 2, 1) == -0.8);

    println("normalizedGraphLaplacian test complete");
}

void testEigenvaluesAndEigenvectors() {
    MATRIX *A = readMatrixFromFile("test/111matrix.txt");

    println("S = ");
    printMatrix(A);

    MATRIX_WITH_VECTOR *res = eigenvaluesAndEigenvectors(A);

    println("v = ");
    printVector(res->vector, 3);
    println("V = ");
    printMatrix(res->matrix);

    freeMatrix(A);
    println("eigenvaluesAndEigenvectors test complete");
}

int main(int argc, char *argv[]) {
    testWeightedAdjacencyMatrix1();
    testWeightedAdjacencyMatrix2();
    testDiagonalDegreeMatrix();
    testNormalizedGraphLaplacian();
    testEigenvaluesAndEigenvectors();
}