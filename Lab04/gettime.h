
/* checks whether _GETTIME_H_ has already been defined 
    - if it hasn't, the code inside is included
    - if it has, the compiler skips it
*/
#ifndef _GETTIME_H_
#define _GETTIME_H

#include <stdio.h>
#include <sys/time.h>

/* function prototype, tells the compiler:
    There is a function named gettime that:
    1) takes no parameters
    2) returns a double 
*/
double gettime(void);

/* ends header guard */
#endif