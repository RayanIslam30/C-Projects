#include "test_random.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

int turning_point_test(const unsigned int *x, size_t n)
{
    // code adapted from Gemini (10/02/2026)
    assert(n >= 3);
    int tpCount = 0; // Turning point counter

    // direction: +1 is increasing, -1 is decreasing
    int direction = (x[1] >= x[0]) ? 1 : -1;
    // Count turning points
    for (int i = 2; i < n; i++)
    {
        if (((x[i] > x[i - 1]) && (direction == -1)) || ((x[i] < x[i - 1]) && (direction == 1)))
        {
            tpCount++;
            direction *= -1;
        }
        // if points equal, no change in direction
    }

    // Calculate theoretical mean and variance
    double mu = (2.0 * n - 4.0) / 3.0;
    double variance = (16.0 * n - 29.0) / 90.0;
    double sigma = sqrt(variance);

    // Calculate Z test statistic
    double z_stat = ((double)tpCount - mu) / sigma;

#if 0
    // Display Results
    printf("--- Turning Point Test Results ---\n");
    printf("Sequence Length (n):    %u\n", n);
    printf("Observed Turning Points: %d\n", tpCount);
    printf("Expected Mean (mu):     %.4f\n", mu);
    printf("Standard Deviation:     %.4f\n", sigma);
    printf("Z-Statistic:            %.4f\n", z_stat);
#endif

    // Simple two-tailed critical value check at 95% confidence level (alpha = 0.05)
    // Critical Z value is approximately 1.96
    return (fabs(z_stat) <= 1.96);
}

void acf(const unsigned int *x, size_t n, double *acfArray, size_t maxLag)
{
    // array of outputs is size maxLag+1
    // code adapted from Claude (10/02/2026)
    assert(n >= 2);
    assert(maxLag >= 1);
    // Mean
    double mean = 0, var = 0;
    for (int i = 0; i < n - 1; i++)
    {
        mean += x[i];
    }
    mean /= n;
    // Variance
    for (int i = 0; i < n; i++)
    {
        double diff = x[i] - mean;
        var += diff * diff;
    }
    var /= (n - 1);

    // for completeness, put this in the lag-0 result
    // (autocorrelation with self is always zero)
    acfArray[0] = 0.0;

    for (int k = 1; k <= maxLag; k++)
    {
        // Lag-k autocorrelation of differences
        // Compares differences from original sequence (index 0..n-1)
        // and offset sequence (index k..n-1)
        double cov = 0;
        for (int i = 0; i < n - k; i++)
        {
            double d1 = x[i] - mean;
            double d2 = x[i + k] - mean;
            cov += d1 * d2;
        }
        acfArray[k] = cov / (n - k) / var;
    }
    return;
}

#if 0
void acf(const unsigned int *x, size_t n, double * acfArray, size_t maxLag) {
    // array of outputs is size maxLag+1
    // code adapted from Claude (10/02/2026)
    assert(n >= 2);
    assert(maxLag >= 1);
    // Mean of differences
    double mean_diff = 0, var_diff = 0;
    for (int i = 0; i < n-1; i++) {
        double d = (int) x[i+1] - (int) x[i];
        mean_diff += d;
    }
    mean_diff /= (n-1);
    // Variance of differences
    for (int i = 0; i < n-1; i++) {
        double d = (int) x[i+1] - (int) x[i];
        var_diff += (d - mean_diff) * (d - mean_diff);
    }
    var_diff /= (n-1);
    printf("%f   %f\n", mean_diff, var_diff);

    // for completeness, put this in the lag-0 result
    // (autocorrelation with self is always zero)
    acfArray[0] = 0.0;

    for (int k = 1; k <= maxLag; k++) {
        // Lag-k autocorrelation of differences
        // Compares differences from original sequence (index 0..n-1)
        // and offset sequence (index k..n-1)
        double cov = 0;
        for (int i = 0; i < n-k-1; i++) {
            double d1 = ((int) x[i+1] - (int) x[i]) - mean_diff;
            double d2 = ((int) x[i+1+k] - (int) x[i+k]) - mean_diff;
            cov += d1 * d2;
            printf("%.1f   %.1f   %f\n", d1, d2, cov);
        }
        acfArray[k] = cov / (n - 1 - k) / var_diff;
        printf("%f   %ld    %f    %.3f\n", cov, (n-1-k), var_diff, acfArray[k]);
    }
    return;
}
#endif
