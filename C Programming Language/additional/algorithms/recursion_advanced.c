/**
 * Advanced Recursion in C
 * Comprehensive demonstration of recursive algorithms and techniques
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Function prototypes
long factorial_recursive(int n);
long factorial_tail_recursive(int n, long accumulator);
int fibonacci_recursive(int n);
int fibonacci_memoized(int n, int *memo);
void tower_of_hanoi(int n, char from, char to, char aux);
bool is_palindrome_recursive(char *str, int start, int end);
int gcd_recursive(int a, int b);
int binary_search_recursive(int arr[], int left, int right, int target);
void merge_sort_recursive(int arr[], int left, int right);
void quick_sort_recursive(int arr[], int low, int high);
void print_permutations(char *str, int left, int right);
int count_paths(int m, int n, int **memo);
bool solve_n_queens(int **board, int col, int n);
void print_board(int **board, int n);

void demonstrate_basic_recursion() {
    printf("=== Basic Recursion Examples ===\n");
    
    // Factorial
    int n = 6;
    printf("Factorial of %d:\n", n);
    printf("Regular recursion: %ld\n", factorial_recursive(n));
    printf("Tail recursion: %ld\n", factorial_tail_recursive(n, 1));
    
    // Fibonacci
    n = 10;
    printf("\nFibonacci sequence up to F(%d):\n", n);
    printf("Using regular recursion: ");
    for (int i = 0; i <= n; i++) {
        printf("%d ", fibonacci_recursive(i));
    }
    printf("\n");
    
    // Fibonacci with memoization
    int *memo = calloc(n + 1, sizeof(int));
    printf("Using memoized recursion: ");
    for (int i = 0; i <= n; i++) {
        printf("%d ", fibonacci_memoized(i, memo));
    }
    printf("\n");
    free(memo);
}

void demonstrate_tower_of_hanoi() {
    printf("\n=== Tower of Hanoi ===\n");
    
    int n = 3;
    printf("Solution for %d disks:\n", n);
    tower_of_hanoi(n, 'A', 'C', 'B');
}

void demonstrate_string_recursion() {
    printf("\n=== String Recursion ===\n");
    
    char test_strings[][20] = {"racecar", "hello", "madam", "programming", "level"};
    int num_strings = sizeof(test_strings) / sizeof(test_strings[0]);
    
    printf("Palindrome checking:\n");
    for (int i = 0; i < num_strings; i++) {
        int len = strlen(test_strings[i]);
        bool is_pal = is_palindrome_recursive(test_strings[i], 0, len - 1);
        printf("'%s': %s\n", test_strings[i], is_pal ? "Palindrome" : "Not palindrome");
    }
}

void demonstrate_mathematical_recursion() {
    printf("\n=== Mathematical Recursion ===\n");
    
    // Greatest Common Divisor
    int pairs[][2] = {{48, 18}, {100, 25}, {17, 13}, {56, 42}};
    int num_pairs = sizeof(pairs) / sizeof(pairs[0]);
    
    printf("Greatest Common Divisor:\n");
    for (int i = 0; i < num_pairs; i++) {
        int gcd = gcd_recursive(pairs[i][0], pairs[i][1]);
        printf("GCD(%d, %d) = %d\n", pairs[i][0], pairs[i][1], gcd);
    }
}

void demonstrate_array_recursion() {
    printf("\n=== Array Recursion ===\n");
    
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 45, 67, 78};
    int size = sizeof(arr) / sizeof(arr[0]);
    int targets[] = {23, 15, 78, 1};
    int num_targets = sizeof(targets) / sizeof(targets[0]);
    
    printf("Array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\nBinary search results:\n");
    
    for (int i = 0; i < num_targets; i++) {
        int result = binary_search_recursive(arr, 0, size - 1, targets[i]);
        if (result != -1) {
            printf("Found %d at index %d\n", targets[i], result);
        } else {
            printf("%d not found\n", targets[i]);
        }
    }
}

void demonstrate_sorting_recursion() {
    printf("\n=== Recursive Sorting Algorithms ===\n");
    
    // Merge Sort
    int arr1[] = {64, 34, 25, 12, 22, 11, 90, 5};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    
    printf("Original array: ");
    for (int i = 0; i < size1; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");
    
    merge_sort_recursive(arr1, 0, size1 - 1);
    
    printf("After merge sort: ");
    for (int i = 0; i < size1; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");
    
    // Quick Sort
    int arr2[] = {64, 34, 25, 12, 22, 11, 90, 5};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    
    printf("\nOriginal array: ");
    for (int i = 0; i < size2; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n");
    
    quick_sort_recursive(arr2, 0, size2 - 1);
    
    printf("After quick sort: ");
    for (int i = 0; i < size2; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n");
}

void demonstrate_permutations() {
    printf("\n=== String Permutations ===\n");
    
    char str[] = "ABC";
    printf("All permutations of '%s':\n", str);
    print_permutations(str, 0, strlen(str) - 1);
}

void demonstrate_dynamic_programming_recursion() {
    printf("\n=== Dynamic Programming with Recursion ===\n");
    
    // Count paths in a grid
    int m = 3, n = 3;
    
    // Create memoization table
    int **memo = malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        memo[i] = calloc(n, sizeof(int));
    }
    
    int paths = count_paths(m - 1, n - 1, memo);
    printf("Number of paths in a %dx%d grid: %d\n", m, n, paths);
    
    // Clean up
    for (int i = 0; i < m; i++) {
        free(memo[i]);
    }
    free(memo);
}

void demonstrate_backtracking() {
    printf("\n=== Backtracking: N-Queens Problem ===\n");
    
    int n = 4;
    
    // Create chessboard
    int **board = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        board[i] = calloc(n, sizeof(int));
    }
    
    printf("Solving %d-Queens problem:\n", n);
    if (solve_n_queens(board, 0, n)) {
        printf("Solution found:\n");
        print_board(board, n);
    } else {
        printf("No solution exists for %d-Queens\n", n);
    }
    
    // Clean up
    for (int i = 0; i < n; i++) {
        free(board[i]);
    }
    free(board);
}

// Function implementations

long factorial_recursive(int n) {
    if (n <= 1) return 1;
    return n * factorial_recursive(n - 1);
}

long factorial_tail_recursive(int n, long accumulator) {
    if (n <= 1) return accumulator;
    return factorial_tail_recursive(n - 1, n * accumulator);
}

int fibonacci_recursive(int n) {
    if (n <= 1) return n;
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

int fibonacci_memoized(int n, int *memo) {
    if (n <= 1) return n;
    if (memo[n] != 0) return memo[n];
    
    memo[n] = fibonacci_memoized(n - 1, memo) + fibonacci_memoized(n - 2, memo);
    return memo[n];
}

void tower_of_hanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        printf("Move disk 1 from %c to %c\n", from, to);
        return;
    }
    
    tower_of_hanoi(n - 1, from, aux, to);
    printf("Move disk %d from %c to %c\n", n, from, to);
    tower_of_hanoi(n - 1, aux, to, from);
}

bool is_palindrome_recursive(char *str, int start, int end) {
    if (start >= end) return true;
    if (str[start] != str[end]) return false;
    return is_palindrome_recursive(str, start + 1, end - 1);
}

int gcd_recursive(int a, int b) {
    if (b == 0) return a;
    return gcd_recursive(b, a % b);
}

int binary_search_recursive(int arr[], int left, int right, int target) {
    if (left > right) return -1;
    
    int mid = left + (right - left) / 2;
    
    if (arr[mid] == target) return mid;
    if (arr[mid] > target) return binary_search_recursive(arr, left, mid - 1, target);
    return binary_search_recursive(arr, mid + 1, right, target);
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));
    
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    free(L);
    free(R);
}

void merge_sort_recursive(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        merge_sort_recursive(arr, left, mid);
        merge_sort_recursive(arr, mid + 1, right);
        
        merge(arr, left, mid, right);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    return i + 1;
}

void quick_sort_recursive(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        quick_sort_recursive(arr, low, pi - 1);
        quick_sort_recursive(arr, pi + 1, high);
    }
}

void swap_chars(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void print_permutations(char *str, int left, int right) {
    if (left == right) {
        printf("%s\n", str);
    } else {
        for (int i = left; i <= right; i++) {
            swap_chars(&str[left], &str[i]);
            print_permutations(str, left + 1, right);
            swap_chars(&str[left], &str[i]);  // backtrack
        }
    }
}

int count_paths(int m, int n, int **memo) {
    if (m == 0 || n == 0) return 1;
    if (memo[m][n] != 0) return memo[m][n];
    
    memo[m][n] = count_paths(m - 1, n, memo) + count_paths(m, n - 1, memo);
    return memo[m][n];
}

bool is_safe(int **board, int row, int col, int n) {
    // Check this column on upper rows
    for (int i = 0; i < row; i++) {
        if (board[i][col]) return false;
    }
    
    // Check upper diagonal on left side
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) return false;
    }
    
    // Check upper diagonal on right side
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        if (board[i][j]) return false;
    }
    
    return true;
}

bool solve_n_queens(int **board, int col, int n) {
    if (col >= n) return true;
    
    for (int row = 0; row < n; row++) {
        if (is_safe(board, row, col, n)) {
            board[row][col] = 1;
            
            if (solve_n_queens(board, col + 1, n)) {
                return true;
            }
            
            board[row][col] = 0;  // backtrack
        }
    }
    
    return false;
}

void print_board(int **board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%c ", board[i][j] ? 'Q' : '.');
        }
        printf("\n");
    }
}

int main() {
    printf("ADVANCED RECURSION IN C\n");
    printf("=======================\n\n");
    
    demonstrate_basic_recursion();
    demonstrate_tower_of_hanoi();
    demonstrate_string_recursion();
    demonstrate_mathematical_recursion();
    demonstrate_array_recursion();
    demonstrate_sorting_recursion();
    demonstrate_permutations();
    demonstrate_dynamic_programming_recursion();
    demonstrate_backtracking();
    
    printf("\nKey Concepts Covered:\n");
    printf("- Basic recursion (factorial, fibonacci)\n");
    printf("- Tail recursion optimization\n");
    printf("- Memoization for optimization\n");
    printf("- Classic problems (Tower of Hanoi)\n");
    printf("- String recursion (palindromes)\n");
    printf("- Mathematical recursion (GCD)\n");
    printf("- Array recursion (binary search)\n");
    printf("- Recursive sorting (merge sort, quick sort)\n");
    printf("- Permutation generation\n");
    printf("- Dynamic programming with recursion\n");
    printf("- Backtracking (N-Queens problem)\n");
    
    return 0;
}
