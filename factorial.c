#include <stdio.h>
// This program reads a decimal integer from the user, stores its digits in an array,
// and then prints the digits, their factorials, and checks if the number is a strong number.
int main()
{
    int userNum;
    //const int maxDigits = 9;      // will allow up to 9 digits in the input value
    int digits[9] = {0};  // array of digits, initialized to zero

    printf("Enter a decimal integer: ");
    fflush(stdout);
    scanf("%d", &userNum);  // input assumed to meet the spec

    // TASK 1 code:
    // store the digits into an array
    int tempNum = userNum;
    int digitIndex = 0; // index for the digits array
    while (tempNum > 0) // loop to store each digit into array
    {
        digits[digitIndex] = tempNum % 10; // get the last digit
        digitIndex++; // increment index for next digit
        tempNum /= 10; // remove the last digit from tempNum
    }

    // TASK 1 code:
    // print the digits, in order, ones place first, separated by commas, no comma after last digit
    printf("Digits: %d", digits[digitIndex - 1]); // print the first digit
    for (int i = digitIndex - 2; i >= 0; i--){ // loop to print remaining digits)
        printf(",%d", digits[i]); // print each digit with a comma, last digit won't have comma
    }
    printf("\n"); // print a newline after the digits

    // TASK 2 code:
    // print the factorial of each digit

    // TASK 3 code:
    // print the sum, and whether number is strong


    return 0;
}