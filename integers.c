#include <stdio.h>
//Code that takes in a number and a digit from user and outputs how many times that digit appears in the number.
int main()
{
    int num, digit, count = 0;
    printf("Enter a number: ");
    fflush(stdout);
    scanf("%d", &num);
    printf("Enter a digit to count: ");
    fflush(stdout);
    scanf("%d", &digit);
         //loop through each digit of number, see if it matches the digit we are looking for, and increment count if it does
    while (num != 0) {
        if (num % 10 == digit) {
            count++;
        }
        num /= 10; //remove last digit from number, iterate
    }
    printf("The digit %d appears %d times in the number.\n", digit, count); //print out how many times the digit appears in the number
    return 0;
}s