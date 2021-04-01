#ifndef _UTILS_INCLUDE
#define _UTILS_INCLUDE

#include <time.h>

class RandGen
{
    public:
    
    static RandGen& instance()
    {
        static RandGen gen;
        return gen;
    }

    RandGen()
    {
        srand(time(NULL));
    }

    int randomInt()
    {
        return rand();
    }
};

#endif