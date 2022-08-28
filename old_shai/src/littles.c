#include "universal.h"


void println(string line) { 
    printf("%s\n", line);
}

void exitIf(bool cond, string msg) {
    if (cond) {
        println(msg);
        exit(EXIT_FAILURE);
    }
}