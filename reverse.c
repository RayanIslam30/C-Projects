#include <stdio.h>
// This program reads a maximum of 20 integers from the user and then prints them in reverse order.
int main(void) {
   const int NUM_ELEMENTS = 20;         // Number of input integers
   int userVals[NUM_ELEMENTS];          // Array to hold the user's input integers


    // Prompt the user for input
    printf("Enter the number of integers you want to input (up to %d): ", NUM_ELEMENTS);
    int numIntegers;
    scanf("%d", &numIntegers);

    for (int i = 0; i < numIntegers; i++) {
        scanf("%d", &userVals[i]);
    }

    // Print the integers in reverse order
    for (int i = numIntegers - 1; i >= 0; i--) {
        printf("%d,", userVals[i]);
    }
    printf("\n");

   return 0;
}