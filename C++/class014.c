/*
 * This program demonstrates the use of union in C.
*/
#include <stdio.h>

int main() {
    union Number {
        int integer;    /* 4 bytes */
        float decimal;  /* 4 bytes */
        double precision;   /* 8 bytes */
        char character;  /* 1 byte */
        /* Total union size = 8 bytes (size of largest member) */
    };
    union Number num;
    num.integer = 42;
    printf("Integer: %d\n", num.integer);
    printf("Decimal: %f\n", num.decimal);
    printf("Precision: %f\n", num.precision);
    printf("Character: %c\n", num.character);
    printf("Total size: %ld\n\n", sizeof(num));

    num.decimal = 3.14;
    printf("Integer: %d\n", num.integer);
    printf("Decimal: %f\n", num.decimal);
    printf("Precision: %f\n", num.precision);
    printf("Character: %c\n", num.character);
    printf("Total size: %ld\n\n", sizeof(num));

    num.precision = 3.14159;
    printf("Integer: %d\n", num.integer);
    printf("Precision: %f\n", num.precision);
    printf("Decimal: %f\n", num.decimal);
    printf("Character: %c\n", num.character);
    printf("Total size: %ld\n\n", sizeof(num));

    num.character = 'A';
    printf("Character: %c\n", num.character);
    printf("Integer: %d\n", num.integer);
    printf("Decimal: %f\n", num.decimal);
    printf("Precision: %f\n", num.precision);
    printf("Total size: %ld\n\n", sizeof(num));
    return 0;
}