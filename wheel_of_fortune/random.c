#include "random.h"

#include <stdlib.h>


//give us a random number between 0 and limit-1
unsigned int getRandom(unsigned int limit) {
    return rand() % limit;
}

void seedRandom(unsigned int seed) {
    srand(seed);
    
}

    return;
}
