
/*
 * This program demonstrates the use of ternary operators.
 */
#include <stdio.h>
int main() {
    int x = 5;
    int y = 10;
    int z = x > y ? x : y;  /* Ternary operator */
    
    /*
    if (x > y) {
        z = x;
    } else {
        z = y;
    }
    */

    printf("The value of z is %d\n", z);
    return 0;
}