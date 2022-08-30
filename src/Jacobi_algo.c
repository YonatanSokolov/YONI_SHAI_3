#include "datastructures.h"
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#define sign(x)   ((x >= 0) - (x < 0))



//step1 - compute P, c, s, theta, t.
// ask shai's Jacobi rotation matrix object_name. 
// ask shai's eigenvalues_and_eigenvectors object_name. - mat and vec
//
//create an identical typedef of an object called eigenvalues_and_eigenvectors to shai's mat_and_vec.(ask dad)
//
eigenvalues_and_eigenvectors Jacobi_algo(MATRIX *A)
{
    MATRIX copy;
    memcpy(copy.data,A->data,//size?????????);
    actual_Jacobi_algo()
    // maybe for step e we should make the "actual_Jacobi_algo" get and return the A' and also P,
    // so we can always compute on the fly, the multiplication P1*P2*P3....
}
//todo: ffigure out how to copy the matrix to a copy and work on it
eigenvalues_and_eigenvectors actual_Jacobi_algo(MATRIX *A,double epsilon)
{
    MATRIX ATAG = calculate_ATAG(A);
    if (!is_diagonal(A, ATAG, epsilon)){return (actual_Jacobi_algo(ATAG,epsilon))}


}

Jacobi_rotation_matrix compute_P(MATRIX *A){
    unsigned int i,j;
    double maximal_element = 0; //this assumes that the matrix isn't empty
    unsigned int maximal_row;
    unsigned int maximal_col;
    for (i=0; i < A->num_rows; i++){
        for (j=0; j < A->num_cols; j++){
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
    //return some object (i,j,c,s)
} 

MATRIX tag(MATRIX *A)
{
    //transpose(P)*A*P
}

Jacobi_rotation_matrix transpose(Jacobi_rotation_matrix P)
{
    //make this function.
}

//this is also called "convergence step"
bool is_diagonal(MATRIX *A, MATRIX *B,double epsilon)
{
    //B is A'
    unsigned int i,j;
    double off_A = 0;
    double off_B = 0;
    for (i=0; i < A->num_rows; i++){
        for (j=0; j < A->num_cols; j++){
            if (i != j)
            {
                off_A += m_at(A,i,j)*m_at(A,i,j);
                off_B += m_at(B,i,j)*m_at(B,i,j);
            }
        }
    }
    if (off_A-off_B <= epsilon){return true;}
    return false;
}
MATRIX calculate_ATAG(MATRIX *A)
{
    MATRIX *ATAG = alloc_matrix(A->num_rows,A->num_cols);
    Jacobi_rotation_matrix P;
    P = compute_P(A);
    double c = P->c;
    double s = P->s; 
    unsigned int i,j;
    for (i=0; i < A->num_rows; i++){
        for (j=0; j < A->num_cols; j++){
            if ((i == P->i)&&(j != P->i)&&(j != P->j))
            {
                m_at(ATAG,i,j) = c*m_at(A,i,P->i) -s*m_at(A,i,P->j)
            }
            if ((i == P->j)&&(j != P->i)&&(j != P->j))
            {
                m_at(ATAG,i,j) = c*m_at(A,i,P->j) +s*m_at(A,i,P->i)
            }
            if ((j == P->i)&&(i != P->i)&&(i != P->j))
            {
                //c*c*m_at(A,i,i) + s*s*m_at(A,j,j)-2*s*c*m_at(A,i,j);
                //s*s*m_at(A,i,i) + c*c*m_at(A,j,j)+2*s*c*m_at(A,i,j);
            }
            else 
            {

            }
        }
    }
    m_at(ATAG,P->i,P->i) = c*c*m_at(A,P->i,P->i) + s*s*m_at(A,P->j,P->j)-2*s*c*m_at(A,P->i,P->j);
    m_at(ATAG,P->j,P->j) = s*s*m_at(A,P->i,P->i) + c*c*m_at(A,P->j,P->j)+2*s*c*m_at(A,P->i,P->j);
    m_at(ATAG,P->i,P->j) = 0;
    m_at(ATAG,P->j,P->i) = 0;
    return ATAG;
}

//create a function that can smartly multiply Rotation matrices.







//define multiplication fun
//