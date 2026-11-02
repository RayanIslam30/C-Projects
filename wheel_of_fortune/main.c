#include <stdio.h>
#include <stdlib.h>
#include "random.h"
#include "test_random.h"

int __wrap_rand()
{
    printf("Not allowed to call rand()\n");
    return 0;
}

int main()
{
    int pass = 0;
    printf("----------\n");
    printf("PRNG Unseeded Test\n\n");
    pass += test_prng_unseeded();
    printf("----------\n");
    printf("PRNG Basic Tests\n\n");
    pass += test_prng_basic();
    printf("----------\n");
    printf("PRNG Distribution Test\n");
    pass += test_prng_distribution();
    printf("----------\n");
    printf("PRNG Correlation Tests\n");
    pass += test_prng_correlations();
    printf("----------\n");
    printf("Passed %d tests\n\n", pass);
    return 0;
}
