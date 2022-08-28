#include "universal.h"

ROTATION *newRotation(double c, double s, int i, int j) {
    ROTATION *P = malloc(sizeof(ROTATION));
    exitIf(P == NULL, ERROR_MSG);
    P->c = c, P->s = s, P->i = i, P->j = j;
    return P;
}

void freeRotation(ROTATION *P) {
    free(P);
}

void leftRotate(MATRIX *M, ROTATION *P) {
    int k, i = P->i, j= P->j;
    double a_i, a_j, c = P->c, s = P->s;

    for (k = 0; k < M->rowCnt; k++) {
        a_i = mCell(M, k, i), a_j = mCell(M, k, j);
        mCell(M, k, i) = c*a_i - s*a_j;
        mCell(M, k, j) = c*a_j + s*a_i;
    }
}

void pivot(MATRIX *M, ROTATION *P) {
    int k, i = P->i, j = P->j;
    double a_i, a_j, a_ij, c = P->c, s = P->s;

    for (k = 0; k < M->rowCnt; k++) {
        if (k == i || k == j) continue;
        a_i = mCell(M, k, i), a_j = mCell(M, k, j);
        mCell(M, k, i) = mCell(M, i, k) = c*a_i - s*a_j;
        mCell(M, k, j) = mCell(M, j, k) = c*a_j + s*a_i;
    }
    a_i = mCell(M, i, i), a_j = mCell(M, j, j), a_ij = mCell(M, i, j);
    mCell(M, i, i) = square(c)*a_i + square(s)*a_j - 2*s*c*a_ij;
    mCell(M, j, j) = square(s)*a_i + square(c)*a_j + 2*s*c*a_ij;
    mCell(M, i, j) = mCell(M, j, i) = 0;
}