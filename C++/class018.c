/*
 * This program demonstrates the use struct in C.
*/
#include <stdio.h>
#include <string.h>

struct Person {
    char name[20];  /* 20 bytes */
    int age;        /* 4 bytes */
    float height;   /* 4 bytes */
    float weight;   /* 4 bytes */
};

typedef struct Person Person;
int main() {
    Person p;
    snprintf(p.name, sizeof(p.name), "Louis");
    p.age = 20;
    p.height = 1.75;
    p.weight = 70.5;
    printf("Name: %s\n", p.name);
    printf("Age: %d\n", p.age);
    printf("Height: %f\n", p.height);
    printf("Weight: %f\n", p.weight);
    return 0;
}