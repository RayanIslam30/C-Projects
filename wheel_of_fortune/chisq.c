// The following code was adapted from Claude (10/02/26)
// No, this is not hypocritical. We instructors are not learning how
// to program, so using an AI tool to generate code with supervision
// is reasonable. The code was manually reviewed, adapted, and tested. 

#include <math.h>
#include <stdlib.h>
#include <assert.h>

/* Regularized upper incomplete gamma Q(a, x) = Gamma(a, x) / Gamma(a). */
static double gamma_q(double a, double x)
{
    const int    MAXIT = 1000;
    const double EPS   = 1e-14, FPMIN = 1e-300;

    assert(x >= 0.0 && a > 0.0);
    if (x == 0.0) return 1.0;

    double gln = lgamma(a);

    if (x < a + 1.0) {                     /* series for P(a,x), return 1-P */
        double ap = a, sum = 1.0 / a, del = sum;
        for (int n = 0; n < MAXIT; n++) {
            ap += 1.0;
            del *= x / ap;
            sum += del;
            if (fabs(del) < fabs(sum) * EPS) break;
        }
        return 1.0 - sum * exp(-x + a * log(x) - gln);
    }

    /* continued fraction (modified Lentz) for Q(a,x) */
    double b = x + 1.0 - a, c = 1.0 / FPMIN, d = 1.0 / b, h = d;
    for (int i = 1; i <= MAXIT; i++) {
        double an = -i * (i - a);
        b += 2.0;
        d = an * d + b; if (fabs(d) < FPMIN) d = FPMIN;
        c = b + an / c; if (fabs(c) < FPMIN) c = FPMIN;
        d = 1.0 / d;
        double del = d * c;
        h *= del;
        if (fabs(del - 1.0) < EPS) break;
    }
    return exp(-x + a * log(x) - gln) * h;
}

/* p-value for a chi-squared statistic with k degrees of freedom. */
static double chisq_pvalue(double chi2, int k)
{
    return gamma_q(k / 2.0, chi2 / 2.0);
}

/* Chi-squared statistic from observed counts and expected counts. 
   For this program, expected value is a single value, because it is
   the same for every observed value.
*/
static double chisq_stat(const double *observed, double expected, int bins)
{
    double chi2 = 0.0;
    for (int i = 0; i < bins; i++) {
        double diff = observed[i] - expected;
        chi2 += diff * diff / expected;
    }
    return chi2;
}

/* Test whether n samples of integers in [0,m-1] are uniform. Uses m bins so
 * the test has m degrees of freedom. Returns the p-value.
 * Rule of thumb: expected count per bin n/m should be >= 5. */
double chisq_uniform_test(const unsigned int *x, size_t n, int m)
{
    assert(m > 1 && n > 0);
    // using doubles for observations and for expectation
    // value, because we want to do floating-point math
    double obs[m];
    double expected_value = (double) n / m;
    size_t i;  // loop index

    // initialize all observation counts to 0.0
    for (i=0; i < m; i++) {
        obs[i] = 0.0;
    }

    for (i = 0; i < n; i++) {
        assert(x[i] < m);
        obs[x[i]] += 1.0;
    }

    double p = chisq_pvalue(chisq_stat(obs, expected_value, m), m);
    return p;
}
