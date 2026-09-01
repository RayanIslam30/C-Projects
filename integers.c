#include <stdio.h>

int main()
{
    int num, digit, count;
    count=0;
    printf("Enter a number: ");
    fflush(stdout);
    scanf("%d", &num);
    printf("Enter a digit to count: ");
    fflush(stdout);
    scanf("%d", &digit);
    //loop through each digit of number, see if it matches the digit we are looking for, and increment count if it does
    int tempNum = num;
    if ((tempNum == 0) && (tempNum==digit)); //if the number is 0 and the digit is 0, increment count, catch this edge case
        count++;
    while (tempNum != 0) {
        if (tempNum % 10 == digit) {
            count++;
        }
        tempNum /= 10; //remove last digit from number, iterate
    }
    printf("The digit %d appears %d times in %d.\n", digit, count, num); //print out how many times the digit appears in the number
    return 0;
}