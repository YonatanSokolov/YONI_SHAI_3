#include "../src/universal.h"

void testNewRotationAndFreeRotation() {
    ROTATION *P = newRotation(0.54030230586, 0.8414709848, 0, 2);
    freeRotation(P);
    println("newRotation and freeRotation test complete");
}

void testLeftRotate() {
    double c = 0.54030230586, s = 0.8414709848;
    ROTATION *P = newRotation(c, s, 0, 2);
    MATRIX *I = identityMatrix(4);

    leftRotate(I, P);
    assert(mCell(I, 0, 0) == c && mCell(I, 2, 2) == c);
    assert(mCell(I, 1, 1) == 1 && mCell(I, 3, 3) == 1);
    assert(mCell(I, 0, 2) == s && mCell(I, 2, 0) == -s);
    assert( !mCell(I, 0, 1) && !mCell(I, 0, 3) && !mCell(I, 1, 0) && 
            !mCell(I, 1, 2) && !mCell(I, 1, 3) && !mCell(I, 2, 1) && 
            !mCell(I, 2, 3) && !mCell(I, 3, 0) && !mCell(I, 3, 1) && 
            !mCell(I, 3, 2) );

    freeRotation(P);
    freeMatrix(I);
    println("leftRotate test complete");
}

void testPivot() {
    double c = sqrt(3)/2, s = 0.5;
    ROTATION *P = newRotation(c, s, 0, 2);
    MATRIX *A = readMatrixFromFile("test/232matrix.txt");

    pivot(A, P);
    for (int i = 0; i < 3; i++)
        for (int j = i+1; j < 3; j++)
            assert(mCell(A, i, j) == mCell(A, j, i));
    assert(abs(mCell(A, 0, 0) - sqrt(3) - 2) < 0.001);
    assert(abs(mCell(A, 0, 1) - 4 * sqrt(3)) < 0.001);
    assert(mCell(A, 0, 2) == 0);
    assert(mCell(A, 1, 1) == 3);
    assert(mCell(A, 1, 2) == 4);
    assert(abs(mCell(A, 2, 2) + sqrt(3) - 2) < 0.001);

    println("pivot test complete");
}

int main(int argc, char *argv[]) {
    testNewRotationAndFreeRotation();
    testLeftRotate();
    testPivot();
}
