
/*
 * This program demonstrates how to use conditional statements in C.
 *  If-else statements
 */
#include <stdio.h>
int main() {
    int n;

    printf("Enter a positive integer: ");
    scanf("%d", &n);

    printf("You entered: %d\n", n);

    if (n % 2 == 0) {       /* even number */
        printf("%d is even.\n", n);
    } else {                /* odd number */
        printf("%d is odd.\n", n);
    }

    return 0;
}
