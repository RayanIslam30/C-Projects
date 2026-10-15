#include <stdio.h>
//working with recursion in C
//takes a number and counts the number of digits in that number
int DigitCount(int n) {
    /* NOTE: This printf statement will be used to demonstrate that the
       function is called recursively.  Don't solve the problem iteratively. */
    printf("DigitCount(%d) is called\n", n);
    /* TODO: finish the function definition below . */
    
    return 0;  /* change this to return the correct value */
}
   

int main(void) {
   int num;
   int digits;

   scanf("%d", &num); 
   digits = DigitCount(num);
   printf("%d", digits);
   return 0;
}
