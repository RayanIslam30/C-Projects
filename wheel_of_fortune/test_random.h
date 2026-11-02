#ifndef ECE_209_PRNG_TEST_H_
#define ECE_209_PRNG_TEST_H_

#include <stdlib.h>

// defined in test_random.c
int test_prng_unseeded();
int test_prng_basic();
int test_prng_correlations();
int test_prng_distribution();

// defined in chisq.c
double chisq_uniform_test(const unsigned int *x, size_t n, int m);

// defined in correlation.c
int turning_point_test(const unsigned int *x, size_t n);
void acf(const unsigned int *x, size_t n, double *acfArray, size_t maxLag);
#endif
