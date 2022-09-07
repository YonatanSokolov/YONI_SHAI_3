#ifndef __spkmeans__
#define __spkmeans__

#include "datastructures.h"

typedef enum {WAM, DDG, LNORM, JACOBI} GOAL;

/**
 * Runs algorithms for goals wam, ddg, lnorm, & jacobi.
 * Assumes correct file name format.
 * Return 0 on success.
 */
int run(GOAL goal, const char *file_name);

/**
 * Performs spectralization.
 * Assume correct file name format, but not legal k value.
 * Return vectors to cluster on success, NULL_MATRIX on failure.
 */
MATRIX spectralization(const char *file_name, unsigned k);

/**
 * Runs kmeans with given intial centroids.
 * Prints output to standerd output.
 * Return 0 on success.
 */
int kmeans(MATRIX vectors, MATRIX intial_centroids);

#endif /*__spkmeans__*/