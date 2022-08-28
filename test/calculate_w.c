#include "../src/datastructures.h"
#include "../src/calculate_w.h"
#include <stdio.h>

void test()
{
    //test1
    VECTOR *V1 = alloc_vector(4);
    V1->data[0] = 1.0;
    V1->data[1] = 1.0;
    V1->data[2] = 1.0;
    V1->data[3] = 1.0;
    V1->length=4;
    VECTOR *V2 = alloc_vector(4);
    V2->data[0] = 0.0;
    V2->data[1] = 0.0;
    V2->data[2] = 0.0;
    V2->data[3] = 0.0;
    V2->length=4;
    if (distance_L2(V1->data,V2->data,4) != (double)2)
    {printf("test1 failed");}
    //test2
    V1->data[0] = 1.0;
    V1->data[1] = 2.0;
    V1->data[2] = 3.0;
    V1->data[3] = 4.0;
    V1->length=4;
    V2->data[0] = 1.0;
    V2->data[1] = 2.0;
    V2->data[2] = 3.0;
    V2->data[3] = 4.0;
    V2->length=4;
    if (distance_L2(V1->data,V2->data,4) != (double)0)
    {printf("test2 failed");}
    //test3
    V1->data[0] = 3.5;
    V1->data[1] = 4.6;
    V1->data[2] = 5.7;
    V1->data[3] = 6.8;
    V1->length=4;
    V2->data[0] = 3.5;
    V2->data[1] = 2.5;
    V2->data[2] = 1.124;
    V2->data[3] = 0.9876;
    V2->length=4;
    double rslt = distance_L2(V1->data,V2->data,4);
    if (distance_L2(V1->data,V2->data,4) != (double)7.68984848745)
    {printf("test3 failed and returned ", rslt,"instead of 7.68984848745");}
}

