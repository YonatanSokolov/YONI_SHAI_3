#include "datastructures.h"
#include "math.h"
//step1 - create fun called "distanceL2"
//step2 - use math.h to calculate exp(-...)
//step3 - use shais matrix class and create the new W matrix

double distance_L2(double *v1, double *v2, unsigned int len){
    double result = 0;
    for (int a = 0; a < len ; a++ ){
        result += (v1[a] - v2[a])*(v1[a] - v2[a]);
    }
    result = sqrt(result);
    return result;
}

MATRIX *create_W(MATRIX *V)
{
    MATRIX *w;
    int n = V->num_cols;
    w->num_cols = n;
    w->num_rows = n;
    for(int i=0; i<n; i++){
        for(int j=0;j<n;j++){
            if (i==j){
                get_m(w,i,j) = 0;
            }
            else{
                    get_m(w,i,j) = exp(-distance_L2(V->data[i],V->data[j],V->num_rows)/2);
            }
        }
    }
    return w;
}