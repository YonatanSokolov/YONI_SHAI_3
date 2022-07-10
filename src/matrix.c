#include "universal.h"

MATRIX *newMatrix(int rowCnt, int colCnt) {
    return newMatrixFromArray(rowCnt, colCnt, malloc(rowCnt * colCnt * sizeof(double)));
}

MATRIX *newMatrixFromArray(int rowCnt, int colCnt, double data[]) {
    MATRIX *res = (MATRIX *) malloc(sizeof(MATRIX));

    exitIf(res == NULL || data == NULL, ERROR_MSG);

    res->rowCnt = rowCnt;
    res->colCnt = colCnt;
    res->data = data;

    return res;
}

void freeMatrix(MATRIX *M) {
    if (M == NULL) return;
    free(M->data);
    free(M);
}

void divByRow(MATRIX *M, VECTOR v) {
    forEachCell(M, mCell(M, i, j) /= v[i]); 
}

void divByCol(MATRIX *M, VECTOR v) {
    forEachCell(M, mCell(M, i, j) /= v[j]); 
}

void subMatrix(MATRIX *A, MATRIX *B) {
    forEachCell(A, mCell(A, i, j) -= mCell(B, i, j));
}

MATRIX *identityMatrix(int n) {
    MATRIX *I = newMatrix(n, n);
    
    forEachCell(I, mCell(I, i, j) = (i == j));
    return I;
}