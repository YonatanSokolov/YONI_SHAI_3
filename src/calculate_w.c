//step1 - create fun called "distanceL2"
//step2 - use math.h to calculate exp(-...)
//step3 - use shais matrix class and create the new W matrix

typedef MATRIX{ 
    data
    num cols
    num rows
}

double distance_L2(double *v1, double *v2, unsigned int len){
    double result = 0;
    for (int a = 0; a < len ; a += 1 ){
        result += (v1[a] - v2[a])*(v1[a] - v2[a]);
    }
    result = sqrt(result);
    return result;
}

MATRIX create_W(MATRIX V)
{
    
}