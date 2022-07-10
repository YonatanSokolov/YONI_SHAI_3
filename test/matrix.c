#include "../src/universal.h"

void testNewMatrixAndFreeMatrix() {
    MATRIX *A = newMatrix(3, 4);
    assert(A != NULL);
    mCell(A, 2, 3) = 3.14;
    assert(A->rowCnt == 3 && A->colCnt == 4);
    assert(mCell(A, 2, 3) == 3.14);
    freeMatrix(A);
    println("newMatrix and freeMatrix test complete");
}

void testNewMatrixFromArray() {
    double data[] = {0, 1, 2, 3, 4, 5};
    MATRIX *A = newMatrixFromArray(2, 3, data);
    assert(A != NULL);
    assert(A->rowCnt == 2 && A->colCnt == 3);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            assert(mCell(A, i, j) == 3*i + j);
    free(A);
    println("newMatrixFromArray test complete");
}

void testDivByRow() {
    double data[] = {0, 1, 2, 3, 4, 5};
    MATRIX *A = newMatrixFromArray(2, 3, data);
    double v[] = {1, 0.5};
    divByRow(A, v);

    forRange(3, assert(mCell(A, 0, i) == i));
    forRange(3, assert(mCell(A, 1, i) == 6 + 2*i));
    assert(v[0] == 1 && v[1] == 0.5);

    println("divByRow test complete");
}

void testDivByCol() {
    double data[] = {0, 1, 2, 3, 4, 5};
    MATRIX *A = newMatrixFromArray(2, 3, data);
    double v[] = {1, 0.5, -1};
    divByCol(A, v);

    forRange(2, assert(mCell(A, i, 0) == 3*i));
    forRange(2, assert(mCell(A, i, 1) == 6*i + 2));
    forRange(2, assert(mCell(A, i, 2) == -3*i -2));
    assert(v[0] == 1 && v[1] == 0.5 && v[2] == -1);

    println("divByCol test complete");
}

void testSubMatrix() {
    double data1[] = {0, 1, 2, 3, 4, 5};
    double data2[] = {0, 1, 2, 3, 3, 3};
    MATRIX *A = newMatrixFromArray(2, 3, data1);
    MATRIX *B = newMatrixFromArray(2, 3, data2);

    subMatrix(A, B);
    forRange(3, assert(mCell(A, 0, i) == 0));
    forRange(3, assert(mCell(A, 1, i) == i));
    forRange(3, assert(mCell(B, 0, i) == i));
    forRange(3, assert(mCell(B, 1, i) == 3));

    println("subMatrix test complete");
}

void testIdentityMatrix() {
    MATRIX *I = identityMatrix(4);
    forEachCell(I, assert(mCell(I, i, j) == (i == j)));
    println("identityMatrix test complete");
}

int main(int argc, char *argv[]) {
    testNewMatrixAndFreeMatrix();
    testNewMatrixFromArray();
    testDivByRow();
    testDivByCol();
    testSubMatrix();
    testIdentityMatrix();
}
