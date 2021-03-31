#ifndef _UTILS_INCLUDE
#define _UTILS_INCLUDE

#include <time.h>

static int randomInt()
{
    srand(time(NULL));
    return rand();
}

#endif