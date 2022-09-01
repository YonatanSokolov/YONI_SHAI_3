#ifndef __spkmeans__
#define __spkmeans__

typedef enum {WAM, DDG, LNORM, JACOBI} GOAL;

int run(GOAL goal, const char *file_name);

#endif /*__spkmeans__*/