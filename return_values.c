#include <stdio.h>
//take 3 arguments, 1 integer and 2 pointers to integers, and assign the tens digit of the integer to the first pointer and the ones digit to the second pointer
void digits(int num, int* onesDig, int* tensDig) {  
    
}
int main() {
   int num;
   int tensDig = 0, onesDig = 0;
   printf("Enter a two-digit decimal integer: ");
   scanf("%d", &num);
   digits(num, &onesDig, &tensDig);
   printf("The digits of %d are %d and %d\n", num, tensDig, onesDig);
   return 0;
}
