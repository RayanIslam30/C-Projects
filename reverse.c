#include <stdio.h>
// This program reads a maximum of 20 integers from the user and then prints them in reverse order.
int main(void) {
   const int NUM_ELEMENTS = 20;         // Number of input integers
   int userVals[NUM_ELEMENTS];          // Array to hold the user's input integers


    // Prompt the user for input
    printf("Enter up to %d integers (press Enter after each integer):\n", NUM_ELEMENTS); // Read the integers from the user
    
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        scanf("%d", &userVals[i]);
        if (getchar() == '\n') { // Check if the user pressed Enter
            break; // Exit the loop if Enter is pressed
        }
    }

    // Print the integers in reverse order
    printf("The integers in reverse order are:\n");
    for (int i = NUM_ELEMENTS - 1; i >= 0; i--) {
        printf("%d ", userVals[i]);
    }
    printf("\n");

   return 0;
}