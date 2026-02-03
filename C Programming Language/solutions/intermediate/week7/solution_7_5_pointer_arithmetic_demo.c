/**
 * Solution 7.5: Advanced Pointer Arithmetic Demonstration
 * Week 7 - Pointers Fundamentals
 * 
 * Description: Comprehensive pointer arithmetic with pre/post increment operators
 */

#include <stdio.h>
#include <string.h>

void demonstrate_pointer_arithmetic() {
    printf("=== Pointer Arithmetic with Arrays ===\n");
    
    int numbers[] = {10, 20, 30, 40, 50};
    int *ptr = numbers;  // Point to first element
    
    printf("Array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n\n");
    
    // Pre-increment vs Post-increment with pointers
    printf("Original pointer value: %p (points to %d)\n", (void*)ptr, *ptr);
    
    // Post-increment: use current value, then increment
    printf("*ptr++ = %d (post-increment)\n", *ptr++);
    printf("Now ptr points to: %p (value: %d)\n", (void*)ptr, *ptr);
    
    // Pre-increment: increment first, then use value
    printf("*++ptr = %d (pre-increment)\n", *++ptr);
    printf("Now ptr points to: %p (value: %d)\n", (void*)ptr, *ptr);
    
    // Reset pointer
    ptr = numbers;
    
    printf("\n=== Pointer Arithmetic Operations ===\n");
    printf("ptr + 0: %p -> %d\n", (void*)(ptr + 0), *(ptr + 0));
    printf("ptr + 1: %p -> %d\n", (void*)(ptr + 1), *(ptr + 1));
    printf("ptr + 2: %p -> %d\n", (void*)(ptr + 2), *(ptr + 2));
    
    // Pointer subtraction
    int *end_ptr = &numbers[4];
    printf("\nPointer difference: %ld elements\n", end_ptr - ptr);
}

void increment_operators_demo() {
    printf("\n=== Pre/Post Increment Operators ===\n");
    
    int x = 5, y = 5;
    int *px = &x, *py = &y;
    
    printf("Initial: x = %d, y = %d\n", x, y);
    
    // Pre-post-increment on values
    printf("++x = %d, x is now %d\n", ++x, x);
    printf("y++ = %d, y is now %d\n", y++, y);
    
    // Pre/Post increment on pointer dereference
    x = 10; y = 10;
    printf("\nWith pointers (x=10, y=10):\n");
    printf("++(*px) = %d, x is now %d\n", ++(*px), x);
    printf("(*py)++ = %d, y is now %d\n", (*py)++, y);
    
    // Complex expressions
    int arr[] = {1, 2, 3, 4, 5};
    int *p = arr;
    
    printf("\nComplex pointer expressions:\n");
    printf("*p++ = %d, p now points to %d\n", *p++, *p);
    printf("*++p = %d\n", *++p);
    printf("++*p = %d, value at p is now %d\n", ++*p, *p);
}

void pointer_to_pointer_demo() {
    printf("\n=== Pointer to Pointer ===\n");
    
    int value = 42;
    int *ptr = &value;
    int **ptr_to_ptr = &ptr;
    
    printf("value = %d\n", value);
    printf("*ptr = %d\n", *ptr);
    printf("**ptr_to_ptr = %d\n", **ptr_to_ptr);
    
    printf("\nAddresses:\n");
    printf("&value = %p\n", (void*)&value);
    printf("ptr = %p\n", (void*)ptr);
    printf("&ptr = %p\n", (void*)&ptr);
    printf("ptr_to_ptr = %p\n", (void*)ptr_to_ptr);
    
    // Modify through double pointer
    **ptr_to_ptr = 100;
    printf("\nAfter **ptr_to_ptr = 100:\n");
    printf("value = %d\n", value);
}

void array_pointer_equivalence() {
    printf("\n=== Array and Pointer Equivalence ===\n");
    
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    // Different ways to access matrix elements
    printf("matrix[1][2] = %d\n", matrix[1][2]);    // 7
    printf("*(*(matrix + 1) + 2) = %d\n", *(*(matrix + 1) + 2));    // 7
    printf("*((int*)matrix + 1*4 + 2) = %d\n", *((int*)matrix + 1*4 + 2)); //  7
    
    // Pointer arithmetic with 2D arrays
    int (*row_ptr)[4] = matrix;  // Pointer to array of 4 ints
    printf("\nUsing row pointer:\n");
    printf("row_ptr[1][2] = %d\n", row_ptr[1][2]);  // 7
    printf("(*(row_ptr + 1))[2] = %d\n", (*(row_ptr + 1))[2]);  // 7
}

void string_pointer_manipulation() {
    printf("\n=== String Pointer Manipulation ===\n");
    
    char str[] = "Hello World";
    char *p = str;
    
    printf("Original string: %s\n", str);
    
    // Move through string with pointer arithmetic
    printf("Character by character:\n");
    while (*p != '\0') {
        printf("'%c' at address %p\n", *p, (void*)p);
        p++;
    }
    
    // Reset pointer and use pre/post increment
    p = str;
    printf("\nUsing increment operators:\n");
    printf("*p++ = '%c', p now points to '%c'\n", *p++, *p); // W
    printf("*++p = '%c'\n", *++p);  // W
    
    // Find and replace using pointers
    p = str;
    while (*p) {
        if (*p == 'o') {
            *p = '0';  // Replace 'o' with '0'
        }
        p++;
    }
    printf("After replacement: %s\n", str);
}

void pointer_comparison_demo() {
    printf("\n=== Pointer Comparison ===\n");
    
    int arr[] = {10, 20, 30, 40, 50};
    int *start = arr;
    int *end = arr + 5;
    int *current = start;
    
    printf("Traversing array with pointer comparison:\n");
    while (current < end) {
        printf("%d ", *current);
        current++;
    }
    printf("\n");
    
    // Pointer arithmetic and comparison
    int *p1 = &arr[1];
    int *p2 = &arr[3];
    
    printf("\np1 points to arr[1] = %d\n", *p1);
    printf("p2 points to arr[3] = %d\n", *p2);
    printf("p2 - p1 = %ld (elements apart)\n", p2 - p1);
    printf("p1 < p2: %s\n", (p1 < p2) ? "true" : "false");
}

int main() {
    printf("ADVANCED POINTER ARITHMETIC DEMONSTRATION\n");
    printf("=========================================\n\n");
    
    demonstrate_pointer_arithmetic();
    increment_operators_demo();
    pointer_to_pointer_demo();
    array_pointer_equivalence();
    string_pointer_manipulation();
    pointer_comparison_demo();
    
    printf("\nKey Concepts Demonstrated:\n");
    printf("- Pre/Post increment with pointers\n");
    printf("- Pointer arithmetic operations\n");
    printf("- Pointer to pointer usage\n");
    printf("- Array-pointer equivalence\n");
    printf("- String manipulation with pointers\n");
    printf("- Pointer comparison operations\n");
    
    return 0;
}
