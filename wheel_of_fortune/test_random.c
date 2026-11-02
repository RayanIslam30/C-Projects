#include <stdio.h>
#include "random.h"
#include "test_random.h"
#include <math.h>

// chisq function defined in chisq.c

static void getSamples(unsigned int limit, unsigned int vals[], int n)
{
   for (int i = 0; i < n; i++)
   {
      vals[i] = getRandom(limit);
   }
}

static int arrayEq(unsigned int a[], unsigned int b[], int n)
{
   for (int i = 0; i < n; i++)
   {
      if (a[i] != b[i])
         return 0;
   }
   return 1;
}

// make sure to call this test function first, before any call to seedRandom
int test_prng_unseeded()
{
   int errors = 0;
   unsigned int testVals[500] = {0};
   unsigned int limit = 0;

   printf("If not seeded, does it behave as seed=1?\n");
   limit = 100;
   getSamples(limit, testVals, 10);
   if (arrayEq(testVals, testVals + 10, 10))
   {
      printf("FAILS: not implemented (returns zero)\n");
      return 0;
   }
   seedRandom(1);
   getSamples(limit, testVals + 10, 10); // should be the same values
   if (arrayEq(testVals, testVals + 10, 10))
   {
      printf("PASS\n");
   }
   else
   {
      printf("FAIL: Unseeded is not the same as seed=1.\n");
      errors++;
   }

   return (errors == 0);
}

int test_prng_basic()
{
   int errors = 0;
   unsigned int testVals[500] = {0};
   unsigned int r; // test value
   int i, j;       // loop index
   unsigned int limit = 0;
   unsigned int seed = 0;

   // test 1: single value only
   printf("Part 1: Does it produce the same value every time?\n");
   limit = 256;
   seed = 0xbaadf00d;
   printf("parameters: seed = %0#10X, limit = %u\n", seed, limit);
   int count = 1;
   seedRandom(seed);
   ;
   getSamples(limit, testVals, 5);
   int firstVal = testVals[0];
   for (i = 1; i < 5; i++)
   {
      if (testVals[i] == firstVal)
         count += 1;
   }
   if (count == 5)
   {
      printf("FAIL: The same value is returned on every call.\n");
      printf("value = %d (%#X)\n", firstVal, firstVal);
      errors += 1;
   }
   else
   {
      printf("PASS: Different values are produced on each call.\n");
   }

   // test 2: different values for different seeds
   printf("-----\nPart 2: Does it produce different values for different seeds?\n");
   printf("parameters: limit = %d\n", limit);
   unsigned int seeds[5] = {0xbaadf00d, 0xbaad, 0x3, 0xdeadbeef, 0xbaad0000};
   unsigned int seedVals[5][5];
   for (i = 0; i < 5; i++)
   {
      seedRandom(seeds[i]);
      printf("...seed = %0#10X\n", seeds[i]);
      getSamples(limit, seedVals[i], 5);
   }
   count = 0;
   for (i = 0; i < 4; i++)
   {
      for (j = i + 1; j < 5; j++)
      {
         if (arrayEq(seedVals[i], seedVals[j], 5))
         {
            printf("FAIL: seeds %0#10X and %0#10X generate the same values\n", seeds[i], seeds[j]);
            count += 1;
         }
      }
   }
   if (count == 0)
      printf("PASS: different values for different seeds.\n");
   else
      errors++;

   // Test 3: limit tests
   printf("-----\nPart 3: Does it produce values within the specified range?\n");
   printf("parameters: seed = 0xAAAA, reseeded for each limit\n");
   int over = 0;
   unsigned int limits[4] = {6, 10, 500, 10000};
   for (i = 0; i < 4; i++)
   {
      printf("...limit = %d  ", limits[i]);
      seedRandom(0xAAAA);
      for (j = 0; j < 500; j++)
      {
         unsigned int val = getRandom(limits[i]);
         if (val >= limits[i])
         {
            printf("FAIL: value = %d", val);
            ++over;
            break;
         }
      }
      printf("\n");
   }
   if (over)
      ++errors;
   else
      printf("PASS: All values are between 0 and (limit-1).\n");

   return (errors == 0);
}

int test_prng_distribution()
{
   // use chi-squared test for uniform distribution
   // 1,000,000 samples, number range [0,10000),
   // degrees of freedom = 10,000 (one number per bin)

   printf("CHI-SQUARE Test with Different Seeds\n");
   unsigned int seeds[3] = {0xA05505AA, 0xFF, 0xABCD1234};
   unsigned int limits[3] = {100, 50, 750};
   unsigned int samples[3] = {1000, 350, 3000};
   int pass = 1;
   for (int i = 0; i < 3; i++)
   {
      printf("\nparameters: seed = %0#10X, limit = %u, samples = %u\n", seeds[i], limits[i], samples[i]);
      unsigned int data[samples[i]];
      seedRandom(seeds[i]);
      getSamples(limits[i], data, samples[i]);
      double p = chisq_uniform_test(data, samples[i], limits[i]);
      if (p < 0.05)
      {
         printf("FAIL: p = %.3f indicates that values are too clustered to be uniform\n", p);
         pass = 0;
      }
      else if (p > 0.95)
      {
         printf("FAIL: p = %.3f indicates that sequence is 'too perfect' and likely not random\n", p);
         pass = 0;
      }
      else
      {
         printf("PASS with p = %.3f\n", p);
      }
   }
   return pass;
}

int test_prng_correlations()
{
   printf("Turning point and autocorrelation tests (lag = 1 to 25) for different seeds\n");
   unsigned int seeds[3] = {0xb0a, 0xbeeffeed, 0x876012};
   unsigned int limits[3] = {1000, 64, 256};
   unsigned int samples = 500;
   unsigned int data[samples];
   int pass = 1;
   int tp;
   double autoFactors[26];
   int i, j;

   for (i = 0; i < 3; i++)
   {
      seedRandom(seeds[i]);
      getSamples(limits[i], data, samples);
      printf("\nparameters: seed = %0#10x, limit = %d\n", seeds[i], limits[i]);
      tp = turning_point_test(data, samples);
      if (tp)
      {
         printf("PASS turning point test\n");
      }
      else
      {
         printf("FAIL turning point test\n");
         pass = 0;
      }
      printf("...Autocorrelation tests with lag = 1, 2, 3, ... 25\n");
      acf(data, samples, autoFactors, 25);
      for (j = 1; j <= 25; j++)
      {
         // probably should be 0.1, but giving some slack
         if (fabs(autoFactors[j]) > 0.15)
         {
            printf("FAIL: autocorrelation factor = %.3f for lag = %d\n", autoFactors[j], j);
            pass = 0;
            break;
         }
      }
      if (j > 25)
      {
         printf("PASS: All factors close to zero.\n");
      }
   }
   return pass;
}
