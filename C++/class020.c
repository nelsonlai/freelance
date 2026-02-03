/*
 * This program demonstrates the use of union in C.
*/
#include <stdio.h>

union MyUnion {
    int x;  /* 4 bytes */
    float y;  /* 4 bytes */
    char z;  /* 1 byte */
};

typedef union MyUnion MyUnion;

int main() {
    MyUnion u;
    printf("Size of MyUnion: %lu\n", sizeof(MyUnion));
    u.x = 10;
    printf("x: %d\n", u.x);
    u.y = 3.14;
    printf("y: %f\n", u.y);
    printf("x: %f\n", (int) u.x);
    u.z = 'A';
    printf("z: %c\n", u.z);
    return 0;
}