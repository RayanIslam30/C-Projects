#include <stdio.h>

// Working with recursion in C
// Takes a number and counts the number of digits
int DigitCount(int n) {
    /* NOTE: This printf statement demonstrates recursion. */
    printf("DigitCount(%d) is called\n", n);

    if (n < 10) {
        return 1;
    }

    return 1 + DigitCount(n / 10);
}

int main(void) {
    int num;
    int digits;

    scanf("%d", &num);
    digits = DigitCount(num);
    printf("%d", digits);

    return 0;
}