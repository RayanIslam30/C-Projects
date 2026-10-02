#include <stdio.h>
// find the nth occurrence of a given value in an array
int findNthOccurrence(int arr[], int size, int value, int n) {
   int count = 0;
   for (int i = 0; i < size; i++) {
        if (arr[i] == value) {
            count++;
            if (count == n) {
                return i;
            }
        }
    }
    return -1; // Return -1 if the nth occurrence is not found
}

int main() {
   return 0;
}
