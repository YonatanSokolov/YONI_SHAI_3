#include "datastructures.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#define sign(x)   ((x >= 0) - (x < 0))
#define epsilon 0.00001

eigenvalues_and_eigenvectors Jacobi_algo(MATRIX A);
eigenvalues_and_eigenvectors actual_Jacobi_algo(MATRIX A,MATRIX P);
JACOBI_ROTATION_MATRIX compute_P(MATRIX A);
bool converged(MATRIX A, MATRIX B);
MATRIX calculate_ATAG(MATRIX A);
void multiply_M_and_P(MATRIX M,JACOBI_ROTATION_MATRIX P);



void main()
{
    MATRIX A = alloc_matrix(2,2);
    m_at(A,0,0) = 2;
    m_at(A,0,1) = 3;
    m_at(A,1,0) = 5;
    m_at(A,1,1) = 7;
    eigenvalues_and_eigenvectors rslt = Jacobi_algo(A);
    printf("%f%f%f%f",m_at(rslt.matrix,0,0),m_at(rslt.matrix,0,1),m_at(rslt.matrix,1,0),m_at(rslt.matrix,1,1));
}

eigenvalues_and_eigenvectors Jacobi_algo(MATRIX A)
{
    unsigned int i,j;
    MATRIX id = alloc_matrix(A.num_rows,A.num_cols);
    for (j=0; j<A.num_cols; j++)
    {
        for (i=0; i<A.num_rows; i++)
        {
            if (i==j){m_at(id,i,j) = 0;}
            else {m_at(id,i,j) =1;}
        }
    }
    eigenvalues_and_eigenvectors rslt = actual_Jacobi_algo(A, id);
    free_matrix(id);
    return rslt;
}




eigenvalues_and_eigenvectors actual_Jacobi_algo(MATRIX A,MATRIX P)
{
    unsigned int i;
    MATRIX ATAG = calculate_ATAG(A);
    JACOBI_ROTATION_MATRIX new_P = compute_P(A);
    if (!converged(A, ATAG))
    {
        free_matrix(A);
        multiply_M_and_P(P,new_P);
        return (actual_Jacobi_algo(ATAG ,P));
    }
    //if this works - change to a "While" loop
    else
    {
        free_matrix(A);
        
        VECTOR eigenvalues = alloc_vector(ATAG.num_cols);
        for (i=0;i<ATAG.num_rows;i++){
            v_at(eigenvalues,i) = m_at(ATAG,i,i);
        }
        multiply_M_and_P(P,new_P);
        eigenvalues_and_eigenvectors rslt;
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
            if (abs(m_at(A,i,j)) > abs(maximal_element)){
                maximal_element = m_at(A,i,j);
                maximal_row = i;
                maximal_col = j;
            }
        }
    }
    double theta = (m_at(A,maximal_col,maximal_col)-m_at(A,maximal_row,maximal_row))/(2*maximal_element);
    double t = sign(theta)/(abs(theta)+sqrt(theta*theta +1));
    double c = 1/(sqrt(t*t + 1));
    double s = t*c;
    JACOBI_ROTATION_MATRIX rslt;
    //malloc and check thereis memory
    rslt.c = c;
    rslt.s = s;
    rslt.i = i;
    rslt.j = j;
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
    if (2*(off_A-off_B) <= epsilon){return true;}
    return false;
}




MATRIX calculate_ATAG(MATRIX A)
{
    MATRIX ATAG = alloc_matrix(A.num_rows,A.num_cols);
    //if (!ATAG) {return NULL;}
    JACOBI_ROTATION_MATRIX P;
    P = compute_P(A);
    double c = P.c;
    double s = P.s; 
    unsigned int i,j;
    for (j=0; j < A.num_cols; j++){
        for (i=j; i < A.num_rows; i++){
            if ((i == P.i)&&(j != P.i)&&(j != P.j))
            {
                m_at(ATAG,i,j) = c*m_at(A,i,P.i) -s*m_at(A,i,P.j);
                m_at(ATAG,j,i) = c*m_at(A,i,P.i) -s*m_at(A,i,P.j);
            }
            if ((i == P.j)&&(j != P.i)&&(j != P.j))
            {
                m_at(ATAG,i,j) = c*m_at(A,i,P.j) +s*m_at(A,i,P.i);
                m_at(ATAG,j,i) = c*m_at(A,i,P.j) +s*m_at(A,i,P.i);
            }
            else 
            {
                m_at(ATAG,i,j) = m_at(A,i,j);
                m_at(ATAG,j,i) = m_at(A,i,j);
            }
        }
    }
    m_at(ATAG,P.i,P.i) = c*c*m_at(A,P.i,P.i) + s*s*m_at(A,P.j,P.j)-2*s*c*m_at(A,P.i,P.j);
    m_at(ATAG,P.j,P.j) = s*s*m_at(A,P.i,P.i) + c*c*m_at(A,P.j,P.j)+2*s*c*m_at(A,P.i,P.j);
    m_at(ATAG,P.i,P.j) = 0;
    m_at(ATAG,P.j,P.i) = 0;
    return ATAG;
}





void multiply_M_and_P(MATRIX M,JACOBI_ROTATION_MATRIX P)
{
    //multiplys in-place in M
    unsigned int i,j;
    MATRIX copy = alloc_matrix(M.num_rows,M.num_cols);
    for (j=0; j <= copy.num_cols ;j++)
    {
        for (i=0; i <= copy.num_rows; i++)
        {
            m_at(copy,i,j) = m_at(M,i,j);
        }
    }
    for (i=0; i<= M.num_cols;i++){
        m_at(copy,i,P.i) = (P.c)*m_at(M,i,P.i) - (P.s)*m_at(M,i,P.j);
        m_at(copy,i,P.j) = (P.s)*m_at(M,i,P.i) + (P.c)*m_at(M,i,P.j);
    }
    M = copy;
    //how to deal with memory here?
    //first free the original matrix data and then make m point to copy?
}

//create a function that can smartly multiply Rotation matrices.

//define multiplication fun
//