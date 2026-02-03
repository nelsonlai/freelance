/*
 * 1. Declare an integer pointer
 * 2. allocate memory to the pointer
 * 3. assign a value to the pointer
 * 4. print the value of the pointer
 * 5. free the memory
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr, *ptemp;
    ptr = (int *) malloc(sizeof(int) * 10);
    ptemp = ptr;

    printf("Value of ptr: %p\n", ptr);
    for (int i = 0; i < 10; i++) {
        /* ptr[i] = i; */
        *ptemp = i;  ptemp++;
    }

    ptemp = ptr;
    for (int i = 0; i < 10; i++) {
        /* printf("Value of ptr[%d]: %d\n", i, ptr[i]); */
        printf("Value of ptemp[%d]: %d\n", i, *ptemp);
        ptemp++;
    }

    free(ptr);
}