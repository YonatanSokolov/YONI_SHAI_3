#include "universal.h"

/**
 * Finds off-diagonal element of given symetric matrix with largest absolute value, 
 * and sumes the squares of the elemntes in the upper triangle (not including main diagonal).
 * @param   S pointer to a symetric matrix
 * @param   resI pointer to variable where the row of the largest off-diagonal element will be stored
 * @param   resJ pointer to variable where the column of the largest off-diagonal element will be stored (resI < resJ)
 * @return  void
 */
static void findLargestOffdiagonalAndSumUpperTriangle 
                    (MATRIX *S, int *resI, int *resJ, double *sum);

MATRIX *weightedAdjacencyMatrix(MATRIX *data) {
    MATRIX *W = newMatrix(data->rowCnt, data->rowCnt);

    forEachCell(W, mCell(W, i, j) = 
        i == j ? 0              : 
        i > j  ? mCell(W, j, i) : 
        exp(-0.5 * normOfDifference(data->colCnt, mRow(data, i), mRow(data, j)))
    );
    return W;
}

VECTOR diagonalDegreeMatrix(MATRIX *W) {
    VECTOR D = calloc(W->rowCnt, sizeof(double));

    exitIf(D == NULL, ERROR_MSG);
    
    forEachCell(W, D[i] += mCell(W, i, j));
    return D;
}

void normalizedGraphLaplacian(MATRIX *W, VECTOR D) {
    forRange(W->rowCnt, D[i] = sqrt(D[i]));
    divByRow(W, D);
    divByCol(W, D);
    forEachCell(W, mCell(W, i, j) = (i==j) - mCell(W, i, j));
}

static void findLargestOffdiagonalAndSumUpperTriangle
                    (MATRIX *S, int *resI, int *resJ, double *sum) {
    int i, j;
    double curr, maxSquare = -DBL_MAX;
    *sum = 0;

    for (i = 0; i < S->rowCnt; i++)
        for (j = i+1; j < S->colCnt; j++) {
            curr = mCell(S, i, j);
            curr = square(curr);
            *sum += curr;
            if (curr > maxSquare) {
                maxSquare = curr;
                *resI = i;
                *resJ = j;
            }
        }
}

#define maxIter     100
#define epsilon     0.000005
MATRIX_WITH_VECTOR *eigenvaluesAndEigenvectors(MATRIX *S) {
    const int n = S->rowCnt;
    int iter = 0, i, j;
    double prevOff, currOff;
    ROTATION *P = malloc(sizeof(ROTATION));
    MATRIX_WITH_VECTOR *res = malloc(sizeof(MATRIX_WITH_VECTOR));
    res->matrix = identityMatrix(n);

    exitIf(P == NULL || res == NULL, ERROR_MSG);

    findLargestOffdiagonalAndSumUpperTriangle(S, &i, &j, &currOff);
    do {
        prevOff = currOff;
        /* calculate P */
        {
            double theta = (mCell(S, j, j)-mCell(S, i, i)) / (2*mCell(S, i, j));
            short sign = theta >= 0 ? 1 : -1;
            double t = sign / (sign*theta + sqrt(square(theta) + 1));
            double c = 1 / sqrt(square(t) + 1);
            double s = t*c;
            P->c = c; P->s = s; P->i = i; P->j = j;
        }
        pivot(S, P);
        leftRotate(res->matrix, P);
        findLargestOffdiagonalAndSumUpperTriangle(S, &i, &j, &currOff);
    } while (++iter < maxIter && prevOff - currOff > epsilon);
    free(P);

    /* extract eigenvalues */
    {
        res->vector = malloc(n * sizeof(double));
        exitIf(res->vector == NULL, ERROR_MSG);
        forRange(n, res->vector[i] = mCell(S, i, i));
    }
    return res;
}

