/*
 * This program demonstrates the use of pointer in C.
*/
#include <stdio.h>

int main() {
    int a = 10;
    int *ptr = &a;
    printf("Value of a: %d\n", a);
    printf("Value of ptr: %p\n", ptr);
    printf("Value of *ptr: %d\n", *ptr);
    *ptr = 20;
    printf("Value of a: %d\n", a);
    printf("Value of *ptr: %d\n", *ptr);
    return 0;
}

/*
    38 / 2 = 19 remainder 0
    19 / 2 = 9 remainder 1
    9 / 2 = 4 remainder 1
    4 / 2 = 2 remainder 0
    2 / 2 = 1 remainder 0
    1 / 2 = 0 remainder 1
    38 (10進制) 100110 (2進制) 46 (8進制)
    8 進制 0, 1, 2, 3, 4, 5, 6, 7
    0 -> 000
    1 -> 001
    2 -> 010
    3 -> 011
    4 -> 100
    5 -> 101
    6 -> 110
    7 -> 111
   
    16 進制 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F
    0 -> 0000
    1 -> 0001
    2 -> 0010
    3 -> 0011
    4 -> 0100
    5 -> 0101
    6 -> 0110
    7 -> 0111
    8 -> 1000
    9 -> 1001
    A -> 1010
    B -> 1011
    C -> 1100
    D -> 1101
    E -> 1110
    F -> 1111

    b100110 -> 46 (8進制) (16進制) 0x26
    b1101 0100 0101 -> 0xD45
*/