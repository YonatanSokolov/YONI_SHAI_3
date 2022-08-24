#ifndef __universial
#define __universial

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>

#define string          char *

#include "vector.h"
#include "matrix.h"
#include "rotation.h"
#include "myIO.h"
#include "algorithms.h"

#define ERROR_MSG       "An Error Has Occurred"
#define INVALID_MSG     "Invalid Input!"

#define forRange(range, op) do {                                \
                                int i;                          \
                                for (i = 0; i < range; i++) op; \
                            } while (0)
#define square(x)           ((x)*(x))


/**
 * Terminates program if given condition is met.
 * @param   cond condition for termination
 * @param   msg messege to print before termination
 * @return  void
 */
void exitIf(bool cond, string msg);

/**
 * Prints given string and goes to next line.
 * @param   line string to be printed.
 * @return  void
 */
void println(string line);

#endif //__universial