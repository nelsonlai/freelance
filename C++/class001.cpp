/*

 */

/*
* This program demonstrates the use of different data types in C.
*/
#include <stdio.h>

int main() {
    int a = 10;
    double pi = 3.14159;
    char grade = 'A';
    bool ok = true; /* False */
    float temperature = 36.6f;

    printf("Integer: %d\n", a);
    printf("Double: %.4f\n", pi);
    printf("Character: %c\n", grade);
    printf("Boolean: %s\n", ok ? "true" : "false"); /* %s for string */
    printf("Float: %.1f\n", temperature);

    return 0;
}
