#include "universal.h"

double normOfDifference(int length, VECTOR u, VECTOR v) {
    double res = 0;
    int i;

    for (i = 0; i < length; i++)
        res += square(u[i] - v[i]);  

    return sqrt(res);
}
