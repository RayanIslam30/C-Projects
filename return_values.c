#include <stdio.h>
//take 3 arguments, 1 integer and 2 pointers to integers, and assign the tens digit of the integer to the first pointer and the ones digit to the second pointer
void digits(int num, int* onesDig, int* tensDig) {  
    for (int i = 0; i < 2; i++) {
        if (i == 0) {
            *onesDig = num % 10;
        } else {
            *tensDig = (num / 10) % 10;
        }
    }
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
