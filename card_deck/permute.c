#include <stdio.h>
#include <stdlib.h>
//code to permute an array of unsigned integers 
// declaration -- needed by permute and/or main: do not change!
void printArray(unsigned int * data, unsigned int size);

// permute -- rearrange the elements of an array of size n
// must call rand() and must follow exactly the algorithm in the spec
void permute(unsigned int a[], unsigned int n) {
    if (n < 2) return;

    for (unsigned int i = n - 1; i > 0; i--) {
        unsigned int j = rand() % (i + 1);

        unsigned int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
}
int main()
{
    srand(0xbaadd00d);   // "bad dude"  :-)

    unsigned int data[5] = {0, 1, 2, 3, 4};
    printf("Starting array:\n");
    printArray(data, 5);
    permute(data, 5);
    printf("Ending array:\n");
    printArray(data, 5);  // you should see a mixed up version of starting array
    return 0;

}

void printArray(unsigned int * data, unsigned int size) {
    for (unsigned int i = 0; i < size; i++) printf("%d ", data[i]);
    printf("\n");
}

