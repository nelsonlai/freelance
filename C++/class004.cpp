
/*
* This program demonstrates the use of pre-increment and post-increment in C.
*/
#include <stdio.h>
#include <math.h>

int main() {
    /* pre-increment and post-increment */
    int a = 5;
    int b = 10;
    int c;

    /* a++ <-> a = a + 1 */
    /* ++a <-> a = a + 1 */

    c = a++ * 5;
    printf("After post-increment, a: %d, c: %d\n", a, c);
    printf("After post-increment, a: %d\n", a);

    c = ++b * 5;
    printf("After pre-increment, b: %d, c: %d\n", b, c);
    printf("After pre-increment, b: %d\n", b);

    return 0;
}
