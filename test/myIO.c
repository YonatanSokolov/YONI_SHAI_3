#include "../src/universal.h"

void testReadMatrixFromFile() {
    MATRIX *A = readMatrixFromFile("test/12matrix.txt");
    assert(A->rowCnt == 2 && A->colCnt == 3);
    forEachCell(A, assert(mCell(A, i, j) == i+1));
    freeMatrix(A);
    println("readMatrixFromFile test complete");
}

int main(int argc, char *argv[]) {
    testReadMatrixFromFile();
}
