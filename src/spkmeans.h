#ifndef __spkmeans__
#define __spkmeans__

#include "datastructures.h"
#include "kmeans.h"

/**
 * Runs algorithms for goals wam, ddg, lnorm, & jacobi.
 * Assumes correct file name format, and that goal is valid.
 * Return 0 on success.
 */
int run(GOAL goal, const char *file_name);

/**
 * Performs spectralization.
 * Assume correct file name format, but not legal k value.
 * Return vectors to cluster on success, NULL_MATRIX on failure.
 */
MATRIX spectralization(const char *file_name, unsigned k);

#endif /*__spkmeans__*/