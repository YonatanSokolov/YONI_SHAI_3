#include "kmeans.h"
#include "myIO.h"

#include <stdio.h>

int kmeans(MATRIX vectors, MATRIX initial_centrods) {
    printf("vectors = \n");
    print_matrix(vectors);
    printf("initial centroids = \n");
    print_matrix(initial_centrods);
    return 0;
}
