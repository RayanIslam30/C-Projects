#include <stdio.h>
// Working with recursion in C
// Takes a number and returns the nth Fibonacci number
int Fibonacci(int n) {
   
   if (n<0) {
      return -1; // Error case for negative input
   }
   else if (n==0) {
      return 0; // Base case: Fibonacci(0) = 0
   }
   else if (n==1) {
      return 1; // Base case: Fibonacci(1) = 1
   }
   else {
      return Fibonacci(n-1) + Fibonacci(n-2); // Recursive case
   }
      
}

int main() {
   int startNum;
      
   scanf("%d", &startNum);
   printf("Fibonacci(%d) is %d\n", startNum, Fibonacci(startNum));

   return 0;
}