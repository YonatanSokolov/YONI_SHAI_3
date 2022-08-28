#include "../src/universal.h"

void testNormOfDifference() {
    MATRIX *A = readMatrixFromFile("test/12matrix.txt");
    assert(normOfDifference(3, mRow(A, 0), mRow(A,1)) == normOfDifference(3, mRow(A, 1), mRow(A, 0)));
    assert(normOfDifference(3, mRow(A, 0), mRow(A,1)) == sqrt(3));
    freeMatrix(A);

    MATRIX *B = readMatrixFromFile("test/105data.csv");
    assert(normOfDifference(4, mRow(B, 0), mRow(B, 1)) == 2);
    assert(normOfDifference(4, mRow(B, 0), mRow(B, 2)) == sqrt(19));
    assert(normOfDifference(4, mRow(B, 1), mRow(B, 2)) == 5);
    freeMatrix(B);

    println("normOfDifference test complete");
}

int main(int argc, char *argv[]) {
    testNormOfDifference();
}
