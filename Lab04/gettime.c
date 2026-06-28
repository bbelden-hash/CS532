/* includes the header so this file knows about the function declaration and required libraries */
#include "gettime.h"

double gettime(void) {

    struct timeval tval;
    gettimeofday(&tval, NULL);
    return ((double) tval.tv_sec + (double) tval.tv_usec / 1000000.0);
}