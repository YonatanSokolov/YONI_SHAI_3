#include "universal.h"


/**
 * Counts number of lines in given file.
 * @param   file file whose lines are to be counted
 * @return  number of lines
 */
static int countLines(FILE *file);

/**
 * Counts number of columns of first line in given file.
 * @param   file file whose columns of first line are to be counted
 * @return  number of columns
 */
static int countCols(FILE *file);


void printMatrix(MATRIX *M) {
    if (M == NULL) println("NULL");
    else forEachCell(M, printf("%.4f%c", mCell(M, i, j), j+1 == M->colCnt ? '\n' : ','));
}

void printVector(VECTOR v, int length) {
    if (v == NULL) println("NULL");
    else forRange(length, printf("%.4f%c", v[i], i+1 == length ? '\n' : ','));
}

static int countLines(FILE *file) {
    int cnt = 0, c;

    for(c = getc(file); c != EOF; c = getc(file))
        if (c == '\n') cnt++;
    fseek(file, 0, SEEK_SET);
    return cnt;
}

static int countCols(FILE *file) {
    int cnt = 1, c;

    for(c = getc(file); c != '\n'; c = getc(file))
        if (c == ',') cnt++;
    fseek(file, 0, SEEK_SET);
    return cnt;
}

MATRIX *readMatrixFromFile(string fileName) {
    int rowCnt, colCnt;
    double *data;
    FILE *inputFile = fopen(fileName, "r");

    exitIf(inputFile == NULL, ERROR_MSG);

    rowCnt = countLines(inputFile);
    colCnt = countCols(inputFile);
    data = (double *) malloc(rowCnt * colCnt * sizeof(double));
    if (data == NULL) return NULL;
    {
        int i;
        for (i = 0; i < rowCnt * colCnt; i++) {
            fscanf(inputFile, "%lf", &data[i]);
            getc(inputFile);
        }
    }
    fclose(inputFile);

    return newMatrixFromArray(rowCnt, colCnt, data);
}

