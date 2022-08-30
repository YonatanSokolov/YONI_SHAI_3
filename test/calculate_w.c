#include "../src/datastructures.h"
#include "../src/calculate_w.h"
#include <stdio.h>
#include <math.h>

void main()
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
    // printf("BAD\n");
    {printf("test3 failed and returned %lf instead of 7.68984848745\n", rslt);}
    //test_w_1
    MATRIX *V = alloc_matrix(2, 2);
    m_at(V,0,0) = 1.1;
    m_at(V,0,1) = 4.3553;
    m_at(V,1,0) = 2.2;
    m_at(V,1,1) = 1.9;
    V->num_cols =2;
    V->num_rows =2;
    MATRIX *W = create_W(V);
    printf("%lf\n", m_at(W, 0, 0));
    printf("%lf\n", m_at(W, 0, 1));
    printf("%lf\n", m_at(W, 1, 0));
    printf("%lf\n", m_at(W, 1, 1));

    printf("%u\n", W->num_cols);
    printf("%u\n", W->num_rows);

    printf("exp(-20) = %lf\n", exp(-20));
}

