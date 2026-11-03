#include <stdlib.h>
#include <stdio.h>

int __wrap_rand()
{
    printf("Not allowed to call rand()\n");
    exit(0);
    return 0;
}

void __wrap_qsort(void *base, size_t nitems, size_t size,
                  int (*compar)(const void *, const void *))
{
    printf("Not allowed to call qsort(...)\n");
    exit(0);
}
