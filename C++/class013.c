/*
 * This program demonstrates the use of enum in C.
 */
#include <stdio.h>

int main() {
    enum Day {
        MONDAY = 1,
        TUESDAY,
        WEDNESDAY,
        THURSDAY,
        FRIDAY,
        SATURDAY,
        SUNDAY
    };
    enum Day today = MONDAY;

    switch (today) {
        case MONDAY:
        case TUESDAY:
        case WEDNESDAY:
        case THURSDAY:
        case FRIDAY:
            printf("Work day\n");
            break;
        case SATURDAY:
        case SUNDAY:
            printf("Weekend\n");
            break;
    }
    printf("Today is %d\n", today);

    enum Color {
        RED,    /* 0 */
        GREEN,  /* 1 */
        BLUE,   /* 2 */
        YELLOW, /* 3 */
        PURPLE  /* 4 */
    };
    enum Color myColor = RED;
    printf("My color is %d\n", myColor);

    if (myColor == RED) {
        printf("My color is red\n");
    }
    if (myColor == GREEN) {
        printf("My color is green\n");
    }
    if (myColor == BLUE) {
        printf("My color is blue\n");
    }
    if (myColor == YELLOW) {
        printf("My color is yellow\n");
    }
    if (myColor == PURPLE) {
        printf("My color is purple\n");
    }

    return 0;
}