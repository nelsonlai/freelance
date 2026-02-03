/**
 * Solution 6.5: Pre/Post Increment Operators Mastery
 * Week 6 - Arrays and String Basics
 * 
 * Description: Comprehensive demonstration of increment/decrement operators in various contexts
 */

#include <stdio.h>
#include <string.h>

/*
  int x = 10;
  int y = 11;
  // int z = x + y++;  // z = 21, y = 12   // post-increment
  int a = x + ++y;  // a = 22, y = 12    // pre-increment
*/
void basic_increment_demo() {
    printf("=== Basic Increment/Decrement Operations ===\n");
    
    int a = 5, b = 5, c = 5, d = 5;
    
    printf("Initial values: a=%d, b=%d, c=%d, d=%d\n", a, b, c, d);
    
    // Pre-increment: increment first, then use value
    printf("++a = %d, a is now %d\n", ++a, a);
    
    // Post-increment: use current value, then increment
    printf("b++ = %d, b is now %d\n", b++, b);
    
    // Pre-decrement: decrement first, then use value
    printf("--c = %d, c is now %d\n", --c, c);
    
    // Post-decrement: use current value, then decrement
    printf("d-- = %d, d is now %d\n", d--, d);
    
    printf("Final values: a=%d, b=%d, c=%d, d=%d\n", a, b, c, d);
}

void array_increment_operations() {
    printf("\n=== Increment Operations with Arrays ===\n");
    
    int arr[] = {10, 20, 30, 40, 50};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
        // i++; ++i;
    }
    printf("\n");
    
    // Pre-increment all elements
    printf("After pre-increment (++arr[++i]):\n");
    for (int i = 0; i < n; i++) {
        printf("arr[%d]: %d -> %d\n", i, arr[i], ++arr[i]);
    }
    
    // Reset array
    int arr2[] = {10, 20, 30, 40, 50};
    
    // Post-increment all elements
    printf("\nAfter post-increment (arr[i]++):\n");
    for (int i = 0; i < n; i++) {
        printf("arr[%d]: %d -> ", i, arr2[i]);
        int old_value = arr2[i]++;
        printf("%d (returned %d)\n", arr2[i], old_value);
    }
}

void loop_increment_patterns() {
    printf("\n=== Increment in Loop Patterns ===\n");
    
    // Traditional for loop
    printf("Traditional for loop (i++):\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", i);
    }
    printf("\n");
    
    // Pre-increment in for loop
    printf("Pre-increment for loop (++i):\n");
    for (int i = 0; i < 5; ++i) {
        printf("%d ", i);
    }
    printf("\n");
    
    // While loop with post-increment
    printf("While loop with post-increment:\n");
    int j = 0;
    while (j < 5) {
        printf("%d ", j++);
    }
    printf("\n");
    
    // While loop with pre-increment
    printf("While loop with pre-increment:\n");
    j = 0;
    while (++j <= 5) {
        printf("%d ", j);
    }
    printf("\n");
}

void string_increment_operations() {
    printf("\n=== String Operations with Increment ===\n");
    
    char str[] = "Hello";
    char *p = str;
    
    printf("Original string: %s\n", str);
    
    // Traverse string with post-increment
    printf("Characters using post-increment:\n");
    p = str;
    while (*p) {
        printf("'%c' ", *p++);
    }
    printf("\n");
    
    // Traverse string with pre-increment
    printf("Characters using pre-increment (skip first):\n");
    p = str;
    while (*++p) {  // Skip first character
        printf("'%c' ", *p);
    }
    printf("\n");
    
    // Count vowels with increment
    p = str;
    int vowel_count = 0;
    while (*p) {
        char c = *p++;
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            vowel_count++;
        }
    }
    printf("Vowel count: %d\n", vowel_count);
}

void complex_increment_expressions() {
    printf("\n=== Complex Increment Expressions ===\n");
    
    int x = 10, y = 5, z = 3;
    int result;
    
    printf("Initial: x=%d, y=%d, z=%d\n", x, y, z);
    
    // Complex expressions with increment
    result = x++ + ++y - z--;
    printf("x++ + ++y - z-- = %d\n", result);
    printf("After: x=%d, y=%d, z=%d\n", x, y, z);
    
    // Reset values
    x = 10; y = 5; z = 3;
    
    // Multiple increments in one expression
    result = ++x * y++ + --z;
    printf("++x * y++ + --z = %d\n", result);
    printf("After: x=%d, y=%d, z=%d\n", x, y, z);
    
    // Array index with increment
    int arr[] = {1, 2, 3, 4, 5};
    int i = 0;
    
    printf("\nArray access with increment:\n");
    printf("arr[i++] = %d, i is now %d\n", arr[i++], i);
    printf("arr[++i] = %d, i is now %d\n", arr[++i], i);
}

void increment_with_pointers_advanced() {
    printf("\n=== Advanced Pointer Increment ===\n");
    
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    int *p = (int*)matrix;
    
    printf("Matrix traversal with pointer increment:\n");
    for (int i = 0; i < 9; i++) {
        printf("%d ", *p++);
        if ((i + 1) % 3 == 0) printf("\n");
    }
    
    // Two-dimensional pointer increment
    printf("\nRow-wise traversal:\n");
    for (int i = 0; i < 3; i++) {
        int *row = matrix[i];
        for (int j = 0; j < 3; j++) {
            printf("%d ", *row++);
        }
        printf("\n");
    }
}

void increment_for_loop_demo() {
    printf("\n=== Increment for Loop Demo ===\n");
    
    for (int i = 0; i < 5; i++) {
        printf("%d ", i);
    }

    for (int i = 0; i < 5; ++i) {
        printf("%d ", i);
    }
}

void increment_side_effects() {
    printf("\n=== Increment Side Effects and Gotchas ===\n");
    
    int x = 5;
    
    // Undefined behavior example (don't do this!)
    printf("x = %d\n", x);
    printf("WARNING: The following may have undefined behavior:\n");
    // int result = x++ + ++x;  // Undefined behavior!
    // printf("x++ + ++x = %d, x = %d\n", result, x);
    
    // Safe way to do complex operations
    x = 5;
    int temp1 = x++;
    int temp2 = ++x;
    int safe_result = temp1 + temp2;
    printf("Safe calculation: %d + %d = %d\n", temp1, temp2, safe_result);
    
    // Sequence points demonstration
    x = 5;
    printf("x = %d\n", x);
    x = x++;  // Undefined behavior!
    printf("After x = x++: x = %d (undefined!)\n", x);
    
    // Correct ways
    x = 5;
    printf("Correct: x++ results in x = %d\n", x++, x);  // This is wrong too!
    
    x = 5;
    int old_x = x;
    x++;
    printf("Safe way: old x = %d, new x = %d\n", old_x, x);
}

void practical_increment_examples() {
    printf("\n=== Practical Increment Examples ===\n");
    
    // Example 1: Copy array with increment
    int source[] = {10, 20, 30, 40, 50};
    int dest[5];
    int *src = source, *dst = dest;
    
    printf("Copying array using pointers:\n");
    for (int i = 0; i < 5; i++) {
        *dst++ = *src++;
    }
    
    printf("Copied array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", dest[i]);
    }
    printf("\n");
    
    // Example 2: String length with increment
    char text[] = "Programming";
    char *p = text;
    int length = 0;
    
    while (*p++) {
        length++;
    }
    printf("String '%s' has length %d\n", text, length);
    
    // Example 3: Find character with increment
    p = text;
    int position = 0;
    char target = 'g';
    
    while (*p && *p != target) {
        p++;
        position++;
    }
    
    if (*p) {
        printf("Found '%c' at position %d\n", target, position);
    } else {
        printf("Character '%c' not found\n", target);
    }
}

int main() {
    printf("COMPREHENSIVE INCREMENT/DECREMENT OPERATORS DEMONSTRATION\n");
    printf("========================================================\n\n");
    
    basic_increment_demo();
    array_increment_operations();
    loop_increment_patterns();
    string_increment_operations();
    complex_increment_expressions();
    increment_with_pointers_advanced();
    increment_side_effects();
    practical_increment_examples();
    
    printf("\nKey Concepts Covered:\n");
    printf("- Pre-increment (++var) vs Post-increment (var++)\n");
    printf("- Pre-decrement (--var) vs Post-decrement (var--)\n");
    printf("- Increment with arrays and pointers\n");
    printf("- Increment in loops and expressions\n");
    printf("- Complex expressions and side effects\n");
    printf("- Practical applications\n");
    printf("- Common pitfalls and undefined behavior\n");
    
    return 0;
}
