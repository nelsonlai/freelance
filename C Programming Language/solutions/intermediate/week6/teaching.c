#include <stdio.h>

void increment_for_loop_demo() {
    printf("\n=== Increment for Loop Demo ===\n");
    
    for (int i = 0; i < 5;) {
        printf("%d ", i);
        i++;
    }

    for (int i = 0; i < 5;) {
        printf("%d ", i);
        ++i;
    }
}

int main() {
    increment_for_loop_demo();
    return 0;
}