/*
Write a function void swap(int *a, int *b) to swap two numbers using pointer manipulation.

Input:
a = 3, b = 9

Output:
a = 9, b = 3
*/
#include <stdio.h>

void swap(int *a, int *b) { /* pointer manipulation, pass by reference */
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    /* pass by reference */
    int a = 3, b = 9;
    printf("Before swap: a = %d, b = %d\n", a, b);
    swap(&a, &b);
    printf("After swap: a = %d, b = %d\n", a, b);
    return 0;
}