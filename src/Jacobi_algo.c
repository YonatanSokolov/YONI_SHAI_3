#include "datastructures.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define sign(x)   ((x >= 0) - (x < 0))
#define epsilon 0.00001
#define NUM_ITER 100

eigenvalues_and_eigenvectors Jacobi_algo(MATRIX A);
eigenvalues_and_eigenvectors actual_Jacobi_algo(MATRIX A,MATRIX P);
JACOBI_ROTATION_MATRIX compute_P(MATRIX A);
bool converged(MATRIX A, MATRIX B);
bool is_diagonal(MATRIX A);
MATRIX calculate_ATAG(MATRIX A);
MATRIX multiply_M_and_P(MATRIX M,JACOBI_ROTATION_MATRIX P);
void print_JRM(JACOBI_ROTATION_MATRIX P);

void main()
{
    //test1 - compute P
    MATRIX A = alloc_matrix(2,2),B = alloc_matrix(2,2),C = alloc_matrix(3,3),D = alloc_matrix(2,2),E = alloc_matrix(2,2),F = alloc_matrix(2,2);
    m_at(A,0,0) = 2;
    m_at(A,0,1) = 3;
    m_at(A,1,0) = 3;
    m_at(A,1,1) = 7;
    //A is |2 3|
    //     |3 7|

    m_at(B,0,0) = 0;
    m_at(B,0,1) = 2;
    m_at(B,1,0) = 2;
    m_at(B,1,1) = 9;

    //B is |0 2|
    //     |2 9|

    m_at(C,0,0) = 1;
    m_at(C,0,1) = 2;
    m_at(C,0,2) = 4;
    m_at(C,1,0) = 2;
    m_at(C,1,1) = 3;
    m_at(C,1,2) = 5;
    m_at(C,2,0) = 4;
    m_at(C,2,1) = 5;
    m_at(C,2,2) = 6;

    //JACOBI_ROTATION_MATRIX P1 = compute_P(A);
    //JACOBI_ROTATION_MATRIX P2 = compute_P(B);
    //print_JRM(P1);
    //print_JRM(P2);
    //test matrix multiplication
    //MATRIX ATAG = calculate_ATAG(A);
    //printf("this is %f %f %f %f\n",m_at(ATAG,0,0),m_at(ATAG,0,1),m_at(ATAG,1,0),m_at(ATAG,1,1));
    

    eigenvalues_and_eigenvectors rslt = Jacobi_algo(A);
    printf("%f  %f  %f  %f\n",m_at(rslt.matrix,0,0),m_at(rslt.matrix,0,1),m_at(rslt.matrix,1,0),m_at(rslt.matrix,1,1));
    printf("%f  %f \n",v_at(rslt.vector,0),v_at(rslt.vector,1));

    eigenvalues_and_eigenvectors rslt_c = Jacobi_algo(C);
    printf("results for matrix C:\n");
    printf("---------------------------------------------------------------------------------------\n");
    printf("matrix:\n");
    printf("[%f  %f  %f] \n",m_at(rslt_c.matrix,0,0),m_at(rslt_c.matrix,0,1),m_at(rslt_c.matrix,0,2));
    printf("[%f  %f  %f] \n",m_at(rslt_c.matrix,1,0),m_at(rslt_c.matrix,1,1),m_at(rslt_c.matrix,1,2));
    printf("[%f  %f  %f] \n",m_at(rslt_c.matrix,2,0),m_at(rslt_c.matrix,2,1),m_at(rslt_c.matrix,2,2));
    printf("vector:\n");
    printf("%f  %f %f\n",v_at(rslt_c.vector,0),v_at(rslt_c.vector,1),v_at(rslt_c.vector,2));



}

void print_JRM(JACOBI_ROTATION_MATRIX P)
{
     printf("i= %i j= %i c= %f s= %f\n",P.i,P.j,P.c,P.s); 
}

eigenvalues_and_eigenvectors Jacobi_algo(MATRIX A)
{
    unsigned int i,j;
    MATRIX id = alloc_matrix(A.num_rows,A.num_cols);
    // printf("succssfully allocated identity matrix\n");
    for (j=0; j<A.num_cols; j++)
    {
        for (i=0; i<A.num_rows; i++)
        {
            if (i==j){m_at(id,i,j) = 1;}
            else {m_at(id,i,j) =0;}
        }
    }
    eigenvalues_and_eigenvectors rslt = actual_Jacobi_algo(A, id);
    free_matrix(id);
    return rslt;
}

eigenvalues_and_eigenvectors actual_Jacobi_algo(MATRIX A,MATRIX P)
{
    unsigned int i;
    unsigned int num_iter = 0;
    // printf("before created A'\n");
    printf("before ATAG make sure that  %i   %i   are the size.\n" ,A.num_cols,A.num_rows);
    MATRIX ATAG = calculate_ATAG(A);
    printf("succssfully created A'\n");
    JACOBI_ROTATION_MATRIX new_P = compute_P(A);
    // printf("succssfully created P\n");
    if (is_diagonal(ATAG) == true){printf("ATAG is diagonal! these are zeros: %f %f %f\n",m_at(ATAG,0,1),m_at(ATAG,0,2),m_at(ATAG,1,2));}
    if (is_diagonal(ATAG) == false){printf("ATAG is NOT diagonal! these are NOT zeros: %f %f %f\n",m_at(ATAG,0,1),m_at(ATAG,0,2),m_at(ATAG,1,2));}
    if (converged(A,ATAG))
    if (!converged(A, ATAG) && !is_diagonal(ATAG) && num_iter < NUM_ITER)
    {
        num_iter +=1;
        printf("before free_mat\n");
        free_matrix(A);
        printf("freeing success!, multipy tho?\n");
        multiply_M_and_P(P,new_P);
        printf("multiply success!\n");
        return (actual_Jacobi_algo(ATAG ,P));
    }
    //if this works - change to a "While" loop
    else
    {
        free_matrix(A);
        printf("got here (10)\n");
        // malloc(1);
        printf("before created eigenvalus %u\n", ATAG.num_cols);
        VECTOR eigenvalues = alloc_vector(ATAG.num_cols);
        printf("hi!\n");
        for (i=0;i<ATAG.num_rows;i++){
            v_at(eigenvalues,i) = m_at(ATAG,i,i);
        }
        printf("success created eigenvalus\n");
        // printf("before created M*P\n");
        printf("the matrix is : [%f, %f, %f, %f]\n ",m_at(P,0,0),m_at(P,0,1),m_at(P,1,0),m_at(P,1,1));
        printf("the P is : [c = %f, s = %f]\n ",new_P.c,new_P.s);
        P = multiply_M_and_P(P,new_P);
        // printf("after created M*P\n");
        printf("the multiplication result is : [%f, %f, %f, %f]\n ",m_at(P,0,0),m_at(P,0,1),m_at(P,1,0),m_at(P,1,1));
        eigenvalues_and_eigenvectors rslt;
        // printf("before created rslt\n");
        rslt.vector = eigenvalues;
        rslt.matrix = P;
        return (rslt);
    }
}

JACOBI_ROTATION_MATRIX compute_P(MATRIX A){

    unsigned int i,j;
    double maximal_element = 0; //this assumes that the matrix isn't empty
    unsigned int maximal_row;
    unsigned int maximal_col;
    for (i=0; i < A.num_rows -1; i++){
        for (j=i+1; j < A.num_cols; j++){
            if (fabs(m_at(A,i,j)) > fabs(maximal_element)){
                maximal_element = m_at(A,i,j);
                maximal_row = i;
                maximal_col = j;
            }
        }
    }
    double theta = (m_at(A,maximal_col,maximal_col)-m_at(A,maximal_row,maximal_row))/(2*maximal_element);
    double t = sign(theta)/(fabs(theta)+sqrt(theta*theta +1));
    double c = 1/(sqrt(t*t + 1));
    double s = t*c;
    JACOBI_ROTATION_MATRIX rslt;
    rslt.c = c;
    rslt.s = s;
    rslt.i = maximal_row;
    rslt.j = maximal_col;
    printf("the matrix A=[%f %f %f %f] created such P that: P.c = %f ,P.s = %f , theta = %f , t = %f\n",m_at(A,0,0),m_at(A,0,1),m_at(A,1,0),m_at(A,1,1),rslt.c,rslt.s,theta,t);
    return rslt;
} 

//this is also called "convergence step"
bool converged(MATRIX A, MATRIX B)
{
    //B is A'
    unsigned int i,j;
    double off_A = 0;
    double off_B = 0;
    for (i=0; i < A.num_rows-1; i++){
        for (j=i+1; j < A.num_cols; j++){
                off_A += m_at(A,i,j)*m_at(A,i,j);
                off_B += m_at(B,i,j)*m_at(B,i,j);
        }
    }
    printf(" the distance between A and A' is %f\n",2*(off_A-off_B));
    if (2*(off_A-off_B) <= epsilon){return true;}
    return false;
}

bool is_diagonal(MATRIX A)
{
    unsigned int i,j;
    bool rslt = true;
    for (i=0; i < A.num_rows-1; i++){
        for (j=i+1; j < A.num_cols; j++){
                if (m_at(A,i,j) != 0.0){rslt = false;}
        }
    }
    return rslt;
}

MATRIX calculate_ATAG(MATRIX A)
{
    printf("before created ATAG :)\n");
    MATRIX ATAG = alloc_matrix(A.num_rows, A.num_cols);
    if(is_null(ATAG)){printf("NULL_MATRIX!!!!!!!!!!\n");}
    printf("after created ATAG :))\n");
    // int a = 9; a++; // why TF this works!!!!
    JACOBI_ROTATION_MATRIX P;
    P = compute_P(A);
    printf("the relevant P is : i = %i, j = %i, c = %f, s = %f \n",P.i,P.j,P.c,P.s);
    double c = P.c;
    double s = P.s; 
    unsigned int i,j;
    for (j=0; j < A.num_cols; j++){
        for (i=j; i < A.num_rows; i++){
            if ((i == P.i)&&(j != P.i)&&(j != P.j))
            {
                printf("first_if %i  %i\n",i,j);
                m_at(ATAG,P.i,j) = c*m_at(A,P.i,j) -s*m_at(A,P.j,j);
                m_at(ATAG,j,P.i) = c*m_at(A,P.i,j) -s*m_at(A,P.j,j);
            }
            if ((i == P.j)&&(j != P.i)&&(j != P.j))
            {
                printf("sec_if %i  %i\n",i,j);
                m_at(ATAG,j,P.j) = c*m_at(A,j,P.j) +s*m_at(A,j,P.j);
                m_at(ATAG,P.j,j) = c*m_at(A,j,P.j) +s*m_at(A,j,P.j);
            }
            else 
            {
                printf("else %i  %i\n",i,j);
                m_at(ATAG,i,j) = m_at(A,i,j);
                m_at(ATAG,j,i) = m_at(A,i,j);
            }
        }
    }
    m_at(ATAG,P.i,P.i) = c*c*m_at(A,P.i,P.i) + s*s*m_at(A,P.j,P.j)-2*s*c*m_at(A,P.i,P.j);
    m_at(ATAG,P.j,P.j) = s*s*m_at(A,P.i,P.i) + c*c*m_at(A,P.j,P.j)+2*s*c*m_at(A,P.i,P.j);
    m_at(ATAG,P.i,P.j) = 0;
    m_at(ATAG,P.j,P.i) = 0;
    printf("calculation_finished\n");
    return ATAG;
}

MATRIX multiply_M_and_P(MATRIX M,JACOBI_ROTATION_MATRIX P)
{
    //multiplys in-place in M
    unsigned int i,j;
    // printf("before created copyyyyy\n");
    MATRIX copy = alloc_matrix(M.num_rows,M.num_cols);
    for (j=0; j < copy.num_cols ;j++)
    {
        for (i=0; i < copy.num_rows; i++)
        {
            m_at(copy,i,j) = m_at(M,i,j);
        }
    }
    // printf("after created copyyyy\n");
    for (i=0; i < M.num_cols;i++){
        m_at(copy,i,P.i) = (P.c)*m_at(M,i,P.i) - (P.s)*m_at(M,i,P.j);
        m_at(copy,i,P.j) = (P.s)*m_at(M,i,P.i) + (P.c)*m_at(M,i,P.j);
    }
    //M = copy;
    return copy;
    //how to deal with memory here?
    //first free the original matrix data and then make m point to copy?
}

//create a function that can smartly multiply Rotation matrices.

//define multiplication fun
//