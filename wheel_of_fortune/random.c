
#include "random.h"
#include <stdint.h>

static uint64_t randomState = 0;
static uint64_t randomIncrement = 1442695040888963407ULL;
static int initialized = 0;

// Generate a 32-bit pseudorandom number
static uint32_t nextRandom(void) {
    uint64_t oldState = randomState;

    randomState = oldState * 6364136223846793005ULL
                + randomIncrement;

    uint32_t xorshifted =
        (uint32_t)(((oldState >> 18u) ^ oldState) >> 27u);

    uint32_t rotation = (uint32_t)(oldState >> 59u);

    return (xorshifted >> rotation)
         | (xorshifted << ((-rotation) & 31));
}

unsigned int getRandom(unsigned int limit) {
    if (limit == 0) {
        return 0;
    }

    if (!initialized) {
        seedRandom(1);
    }

    // Rejection sampling avoids modulo bias
    uint32_t threshold = (uint32_t)(-limit) % limit;

    while (1) {
        uint32_t value = nextRandom();

        if (value >= threshold) {
            return value % limit;
        }
    }
}

void seedRandom(unsigned int seed) {
    randomState = 0;
    initialized = 1;

    nextRandom();

    randomState += seed;

    nextRandom();
}
