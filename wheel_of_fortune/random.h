#ifndef ECE_209_P2_RANDOM_H_
#define ECE_209_P2_RANDOM_H_

// return a pseudorandom integer between 0 and limit-1
unsigned int getRandom(unsigned int limit);

// initialize pseudorandom number generator
void seedRandom(unsigned int seed);

#endif