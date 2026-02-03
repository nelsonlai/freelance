/**
 * Advanced Pointers and Arrays
 * Comprehensive demonstration of pointer-array relationships and advanced techniques
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void demonstrate_pointer_array_equivalence() {
    printf("=== Pointer-Array Equivalence ===\n");
    
    int arr[] = {10, 20, 30, 40, 50};
    int *ptr = arr;  // arr decays to pointer to first element
    
    printf("Array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    // Different ways to access array elements
    printf("\nDifferent access methods:\n");
    printf("arr[2] = %d\n", arr[2]);
    printf("*(arr + 2) = %d\n", *(arr + 2));
    printf("ptr[2] = %d\n", ptr[2]);
    printf("*(ptr + 2) = %d\n", *(ptr + 2));
    
    // Pointer arithmetic
    printf("\nPointer arithmetic:\n");
    printf("ptr = %p, ptr + 1 = %p (difference: %ld bytes)\n", 
           (void*)ptr, (void*)(ptr + 1), (char*)(ptr + 1) - (char*)ptr);
}

void demonstrate_multidimensional_arrays() {
    printf("\n=== Multidimensional Arrays and Pointers ===\n");
    
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    printf("Matrix:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    // Different ways to access 2D array elements
    printf("\nAccessing matrix[1][2] (value 7):\n");
    printf("matrix[1][2] = %d\n", matrix[1][2]);
    printf("*(*(matrix + 1) + 2) = %d\n", *(*(matrix + 1) + 2));
    printf("*((int*)matrix + 1*4 + 2) = %d\n", *((int*)matrix + 1*4 + 2));
    
    // Array of pointers vs pointer to array
    int *row_ptrs[3];  // Array of pointers
    for (int i = 0; i < 3; i++) {
        row_ptrs[i] = matrix[i];
    }
    
    printf("\nUsing array of pointers:\n");
    printf("row_ptrs[1][2] = %d\n", row_ptrs[1][2]);
    
    // Pointer to array
    int (*matrix_ptr)[4] = matrix;  // Pointer to array of 4 ints
    printf("matrix_ptr[1][2] = %d\n", matrix_ptr[1][2]);
}

void demonstrate_dynamic_arrays() {
    printf("\n=== Dynamic Arrays ===\n");
    
    int size = 5;
    int *dynamic_arr = (int*)malloc(size * sizeof(int));
    
    if (!dynamic_arr) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    // Initialize dynamic array
    for (int i = 0; i < size; i++) {
        dynamic_arr[i] = (i + 1) * 10;
    }
    
    printf("Dynamic array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", dynamic_arr[i]);
    }
    printf("\n");
    
    // Resize array
    size = 8;
    dynamic_arr = (int*)realloc(dynamic_arr, size * sizeof(int));
    
    if (!dynamic_arr) {
        printf("Memory reallocation failed!\n");
        return;
    }
    
    // Initialize new elements
    for (int i = 5; i < size; i++) {
        dynamic_arr[i] = (i + 1) * 10;
    }
    
    printf("Resized array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", dynamic_arr[i]);
    }
    printf("\n");
    
    free(dynamic_arr);
}

void demonstrate_2d_dynamic_arrays() {
    printf("\n=== 2D Dynamic Arrays ===\n");
    
    int rows = 3, cols = 4;
    
    // Method 1: Array of pointers
    int **matrix1 = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix1[i] = (int*)malloc(cols * sizeof(int));
    }
    
    // Initialize matrix1
    int value = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix1[i][j] = value++;
        }
    }
    
    printf("2D Dynamic Array (Method 1):\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", matrix1[i][j]);
        }
        printf("\n");
    }
    
    // Method 2: Single malloc with pointer arithmetic
    int *matrix2 = (int*)malloc(rows * cols * sizeof(int));
    
    // Initialize matrix2
    value = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            *(matrix2 + i * cols + j) = value++;
        }
    }
    
    printf("\n2D Dynamic Array (Method 2):\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", *(matrix2 + i * cols + j));
        }
        printf("\n");
    }
    
    // Clean up
    for (int i = 0; i < rows; i++) {
        free(matrix1[i]);
    }
    free(matrix1);
    free(matrix2);
}

// Helper functions for function pointers
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return b != 0 ? a / b : 0; }

void demonstrate_function_pointers() {
    printf("\n=== Function Pointers ===\n");
    
    // Function pointer declarations
    int (*operation)(int, int);
    
    // Array of function pointers
    int (*operations[])(int, int) = {add, subtract, multiply, divide};
    char *op_names[] = {"add", "subtract", "multiply", "divide"};
    
    int a = 15, b = 3;
    
    printf("Operating on %d and %d:\n", a, b);
    for (int i = 0; i < 4; i++) {
        operation = operations[i];
        printf("%s: %d\n", op_names[i], operation(a, b));
    }
}

void demonstrate_complex_pointer_expressions() {
    printf("\n=== Complex Pointer Expressions ===\n");
    
    int arr[] = {1, 2, 3, 4, 5};
    int *ptr = arr;
    
    printf("Array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    // Complex expressions
    printf("\nComplex pointer expressions:\n");
    printf("*ptr = %d\n", *ptr);
    printf("*ptr++ = %d (ptr now points to %d)\n", *ptr++, *ptr);
    printf("*++ptr = %d\n", *++ptr);
    printf("++*ptr = %d (value at ptr is now %d)\n", ++*ptr, *ptr);
    printf("(*ptr)++ = %d (value at ptr is now %d)\n", (*ptr)++, *ptr);
    
    // Reset pointer
    ptr = arr;
    printf("\nAfter reset, array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void demonstrate_pointer_arrays_strings() {
    printf("\n=== Pointers, Arrays, and Strings ===\n");
    
    // Array of string literals
    char *fruits[] = {"apple", "banana", "cherry", "date", "elderberry"};
    int num_fruits = sizeof(fruits) / sizeof(fruits[0]);
    
    printf("Fruits array:\n");
    for (int i = 0; i < num_fruits; i++) {
        printf("%d: %s (address: %p)\n", i, fruits[i], (void*)fruits[i]);
    }
    
    // 2D character array
    char colors[][10] = {"red", "green", "blue", "yellow"};
    int num_colors = sizeof(colors) / sizeof(colors[0]);
    
    printf("\nColors 2D array:\n");
    for (int i = 0; i < num_colors; i++) {
        printf("%d: %s (address: %p)\n", i, colors[i], (void*)colors[i]);
    }
    
    // String manipulation with pointers
    char str[] = "Hello World";
    char *p = str;
    
    printf("\nString manipulation:\n");
    printf("Original: %s\n", str);
    
    // Convert to uppercase using pointer
    while (*p) {
        if (*p >= 'a' && *p <= 'z') {
            *p = *p - 'a' + 'A';
        }
        p++;
    }
    printf("Uppercase: %s\n", str);
}

int main() {
    printf("ADVANCED POINTERS AND ARRAYS DEMONSTRATION\n");
    printf("==========================================\n\n");
    
    demonstrate_pointer_array_equivalence();
    demonstrate_multidimensional_arrays();
    demonstrate_dynamic_arrays();
    demonstrate_2d_dynamic_arrays();
    demonstrate_function_pointers();
    demonstrate_complex_pointer_expressions();
    demonstrate_pointer_arrays_strings();
    
    printf("\nKey Concepts Covered:\n");
    printf("- Pointer-array equivalence and different access methods\n");
    printf("- Multidimensional arrays and various pointer techniques\n");
    printf("- Dynamic memory allocation for arrays\n");
    printf("- 2D dynamic arrays (two different methods)\n");
    printf("- Function pointers and arrays of function pointers\n");
    printf("- Complex pointer expressions and their evaluation\n");
    printf("- String manipulation using pointers\n");
    
    return 0;
}
