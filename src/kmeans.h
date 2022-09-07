#ifndef __kmeans__
#define __kmeans__

#include "datastructures.h"

int kmeans(double         *vectors_array,
                   double         *centroids_array,
                   unsigned int  vectors_num,
                   unsigned int  vector_dim);
/*
this is a wrapper function - from last project.
*/

#endif /*__kmeans__*/