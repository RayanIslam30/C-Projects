#include <stdio.h>
//find the last element in an array that is greater than a given value
int lastGreater(int arr[], int size, int value) {
   int last_index = -1;
   for (int i = 0; i < size; i++) {
      if (arr[i] > value) {
         last_index = i;
      }
   }
   return last_index;
}

// main function does nothing, only UNIT TESTS are used
int main() {
   return 0;
}
