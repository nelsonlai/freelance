/*
  * Use pointer to access the members of the struct
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Person {
    char *name;
    int age;
    float height;
    float weight;
};

typedef struct Person Person;
    
int main() {
    Person *ptr;
    ptr = (Person *) malloc (sizeof(Person));
    ptr->name = (char *) malloc(sizeof(char) * 20);
    snprintf(ptr->name, sizeof(ptr->name), "Louis");
    ptr->age = 20;
    ptr->height = 1.75;
    ptr->weight = 70.5;
    printf("Name: %s\n", ptr->name);
    printf("Age: %d\n", ptr->age);
    printf("Height: %f\n", ptr->height);
    printf("Weight: %f\n", ptr->weight);
    free(ptr->name);
    free(ptr);
    return 0;
}