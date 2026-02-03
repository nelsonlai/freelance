/**
 * Solution 7.6: Function Pointers Comprehensive
 * Week 7 - Pointers Fundamentals
 * 
 * Description: Complete demonstration of function pointers in C
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

// Function prototypes for basic operations
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int divide_op(int a, int b);

// Function prototypes for string operations
int string_length(const char *str);
void string_uppercase(char *str);
void string_lowercase(char *str);
void string_reverse(char *str);

// Function prototypes for array operations
void bubble_sort(int arr[], int n);
void selection_sort(int arr[], int n);
int linear_search(int arr[], int n, int target);
int binary_search(int arr[], int n, int target);

// Function prototypes for callback demonstrations
void process_array(int arr[], int n, void (*callback)(int*, int));
int filter_array(int arr[], int n, int result[], bool (*predicate)(int));
void for_each(int arr[], int n, void (*action)(int));
int reduce_array(int arr[], int n, int initial, int (*reducer)(int, int));

// Predicate functions
bool is_even(int n);
bool is_positive(int n);
bool is_prime(int n);

// Action functions
void print_number(int n);
void print_square(int n);
void print_double(int n);

// Comparison functions
int compare_ascending(const void *a, const void *b);
int compare_descending(const void *a, const void *b);

// State machine functions
void idle_enter(void);
void idle_exit(void);
void running_enter(void);
void running_exit(void);
void stopped_enter(void);
void stopped_exit(void);

// Menu action functions
void show_help(void);
void show_about(void);
void show_credits(void);
void exit_program(void);

// Command handler functions
void cmd_help(const char *args);
void cmd_echo(const char *args);
void cmd_calc(const char *args);
void cmd_quit(const char *args);

// Helper function, function pointer returning a function pointer
int (*get_operation(char op))(int, int);

void demonstrate_basic_function_pointers() {
    printf("=== Basic Function Pointers ===\n");
    
    // Declare function pointer
    int (*operation)(int, int);
    
    int a = 15, b = 5;
    printf("Operating on %d and %d:\n", a, b);
    
    // Point to different functions
    operation = add;
    printf("Addition: %d\n", operation(a, b));
    
    operation = subtract;
    printf("Subtraction: %d\n", operation(a, b));
    
    operation = multiply;
    printf("Multiplication: %d\n", operation(a, b));
    
    operation = divide_op;
    printf("Division: %d\n", operation(a, b));
    
    // Direct function pointer call
    printf("Direct call: %d\n", (*operation)(a, b));
    
    // Show function addresses
    printf("\nFunction addresses:\n");
    printf("add: %p\n", (void*)add);
    printf("subtract: %p\n", (void*)subtract);
    printf("multiply: %p\n", (void*)multiply);
    printf("divide_op: %p\n", (void*)divide_op);
}

void demonstrate_function_pointer_arrays() {
    printf("\n=== Arrays of Function Pointers ===\n");
    
    // Array of function pointers (array of function pointers)
    int (*math_operations[])(int, int) = {add, subtract, multiply, divide_op};
    char *operation_names[] = {"Addition", "Subtraction", "Multiplication", "Division"};
    char operation_symbols[] = {'+', '-', '*', '/'};
    int num_operations = sizeof(math_operations) / sizeof(math_operations[0]);
    
    int x = 20, y = 4;
    printf("Performing operations on %d and %d:\n", x, y);
    
    for (int i = 0; i < num_operations; i++) {
        int result = math_operations[i](x, y);
        printf("%s (%c): %d\n", operation_names[i], operation_symbols[i], result);
    }
    
    // String operations array
    void (*string_ops[])(char*) = {string_uppercase, string_lowercase, string_reverse};
    char *string_op_names[] = {"Uppercase", "Lowercase", "Reverse"};
    int num_string_ops = sizeof(string_ops) / sizeof(string_ops[0]);
    
    char test_string[] = "Hello World";
    printf("\nString operations on \"%s\":\n", test_string);
    
    for (int i = 0; i < num_string_ops; i++) {
        char temp_string[50];
        strcpy(temp_string, test_string);
        string_ops[i](temp_string);
        printf("%s: \"%s\"\n", string_op_names[i], temp_string);
    }
}

void demonstrate_callback_functions() {
    printf("\n=== Callback Functions ===\n");
    
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(numbers) / sizeof(numbers[0]);
    
    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    // Filter operations
    int even_numbers[10];
    int even_count = filter_array(numbers, n, even_numbers, is_even);
    printf("\nEven numbers: ");
    for (int i = 0; i < even_count; i++) {
        printf("%d ", even_numbers[i]);
    }
    printf("(count: %d)\n", even_count);
    
    int positive_numbers[10];
    int positive_count = filter_array(numbers, n, positive_numbers, is_positive);
    printf("Positive numbers: ");
    for (int i = 0; i < positive_count; i++) {
        printf("%d ", positive_numbers[i]);
    }
    printf("(count: %d)\n", positive_count);
    
    int prime_numbers[10];
    int prime_count = filter_array(numbers, n, prime_numbers, is_prime);
    printf("Prime numbers: ");
    for (int i = 0; i < prime_count; i++) {
        printf("%d ", prime_numbers[i]);
    }
    printf("(count: %d)\n", prime_count);
    
    // Apply different actions using for_each
    printf("\nApplying different actions:\n");
    printf("Original numbers: ");
    for_each(numbers, 5, print_number);
    printf("\n");
    
    printf("Squared numbers: ");
    for_each(numbers, 5, print_square);
    printf("\n");
    
    printf("Doubled numbers: ");
    for_each(numbers, 5, print_double);
    printf("\n");
    
    // Reduce operations
    int sum = reduce_array(numbers, n, 0, add);
    printf("\nSum using reduce: %d\n", sum);
    
    int product = reduce_array(numbers, 5, 1, multiply);
    printf("Product of first 5 numbers: %d\n", product);
}

void demonstrate_function_pointer_structures() {
    printf("\n=== Function Pointers in Structures ===\n");
    
    // Calculator structure with function pointer
    struct Calculator {
        char name[20];
        int (*operation)(int, int);
        char symbol;
    };
    
    struct Calculator calculators[] = {
        {"Addition", add, '+'},
        {"Subtraction", subtract, '-'},
        {"Multiplication", multiply, '*'},
        {"Division", divide_op, '/'}
    };
    
    int num_calcs = sizeof(calculators) / sizeof(calculators[0]);
    int operand1 = 24, operand2 = 6;
    
    printf("Calculator operations on %d and %d:\n", operand1, operand2);
    for (int i = 0; i < num_calcs; i++) {
        int result = calculators[i].operation(operand1, operand2);
        printf("%s (%c): %d\n", calculators[i].name, calculators[i].symbol, result);
    }
    
    // State machine using function pointers
    struct State {
        char name[20];
        void (*enter_state)(void);
        void (*exit_state)(void);
        struct State *next_state;
    };
    
    struct State idle = {"IDLE", idle_enter, idle_exit, NULL};
    struct State running = {"RUNNING", running_enter, running_exit, NULL};
    struct State stopped = {"STOPPED", stopped_enter, stopped_exit, NULL};
    
    // Set up state transitions
    idle.next_state = &running;
    running.next_state = &stopped;
    stopped.next_state = &idle;
    
    printf("\nState machine demonstration:\n");
    struct State *current_state = &idle;
    
    for (int i = 0; i < 6; i++) {
        current_state->enter_state();
        printf("Current state: %s\n", current_state->name);
        current_state->exit_state();
        current_state = current_state->next_state;
        printf("---\n");
    }
}

void demonstrate_menu_system() {
    printf("\n=== Menu System Using Function Pointers ===\n");
    
    // Menu item structure
    struct MenuItem {
        char description[50];
        void (*action)(void);
    };
    
    // Create menu
    struct MenuItem menu[] = {
        {"Show Help", show_help},
        {"Show About", show_about},
        {"Show Credits", show_credits},
        {"Exit", exit_program}
    };
    
    int menu_size = sizeof(menu) / sizeof(menu[0]);
    
    printf("Menu System Demo:\n");
    for (int i = 0; i < menu_size; i++) {
        printf("%d. %s\n", i + 1, menu[i].description);
    }
    
    printf("\nExecuting all menu items:\n");
    for (int i = 0; i < menu_size; i++) {
        printf("Executing: %s\n", menu[i].description);
        menu[i].action();
        printf("---\n");
    }
}

void demonstrate_dynamic_function_selection() {
    printf("\n=== Dynamic Function Selection ===\n");
    
    char operators[] = {'+', '-', '*', '/'};
    int a = 20, b = 4;
    
    printf("Dynamic operation selection for %d and %d:\n", a, b);
    for (int i = 0; i < 4; i++) {
        int (*op)(int, int) = get_operation(operators[i]);
        if (op) {
            printf("%c: %d\n", operators[i], op(a, b));
        }
    }
    
    // Search algorithm selection
    int sorted_array[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int array_size = sizeof(sorted_array) / sizeof(sorted_array[0]);
    int target = 7;
    
    int (*search_functions[])(int[], int, int) = {
        linear_search,
        binary_search
    };
    
    char *search_names[] = {"Linear Search", "Binary Search"};
    int num_searches = sizeof(search_functions) / sizeof(search_functions[0]);
    
    printf("\nSearching for %d in sorted array:\n", target);
    for (int i = 0; i < num_searches; i++) {
        int result = search_functions[i](sorted_array, array_size, target);
        printf("%s: %s at index %d\n", 
               search_names[i], 
               result != -1 ? "Found" : "Not found", 
               result);
    }
}

void demonstrate_sorting_with_function_pointers() {
    printf("\n=== Sorting with Function Pointers ===\n");
    
    int original[] = {64, 34, 25, 12, 22, 11, 90, 5};
    int n = sizeof(original) / sizeof(original[0]);
    
    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", original[i]);
    }
    printf("\n");
    
    // Using qsort with different comparison functions
    int ascending[8], descending[8];
    memcpy(ascending, original, sizeof(original));
    memcpy(descending, original, sizeof(original));
    
    qsort(ascending, n, sizeof(int), compare_ascending);
    qsort(descending, n, sizeof(int), compare_descending);
    
    printf("Ascending sort: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", ascending[i]);
    }
    printf("\n");
    
    printf("Descending sort: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", descending[i]);
    }
    printf("\n");
    
    // Custom sorting algorithms with function pointers
    void (*sort_algorithms[])(int[], int) = {bubble_sort, selection_sort};
    char *sort_names[] = {"Bubble Sort", "Selection Sort"};
    int num_sorts = sizeof(sort_algorithms) / sizeof(sort_algorithms[0]);
    
    for (int i = 0; i < num_sorts; i++) {
        int temp_array[8];
        memcpy(temp_array, original, sizeof(original));
        
        printf("\n%s result: ", sort_names[i]);
        sort_algorithms[i](temp_array, n);
        for (int j = 0; j < n; j++) {
            printf("%d ", temp_array[j]);
        }
        printf("\n");
    }
}

void demonstrate_advanced_function_pointers() {
    printf("\n=== Advanced Function Pointer Techniques ===\n");
    
    // Function that returns a function pointer
    printf("Function returning function pointer:\n");
    int x = 12, y = 3;
    
    char ops[] = {'+', '-', '*', '/'};
    for (int i = 0; i < 4; i++) {
        int (*operation)(int, int) = get_operation(ops[i]);
        if (operation) {
            printf("%d %c %d = %d\n", x, ops[i], y, operation(x, y));
        }
    }
    
    // 2D array of function pointers
    printf("\n2D Function Pointer Array:\n");
    int (*matrix_ops[2][2])(int, int) = {
        {add, subtract},
        {multiply, divide_op}
    };
    
    char *op_names[2][2] = {
        {"Add", "Subtract"},
        {"Multiply", "Divide"}
    };
    
    printf("Operations matrix for %d and %d:\n", x, y);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            int result = matrix_ops[i][j](x, y);
            printf("%-8s: %2d  ", op_names[i][j], result);
        }
        printf("\n");
    }
}

// Function implementations

// Basic arithmetic operations
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide_op(int a, int b) { return b != 0 ? a / b : 0; }

// String operations
int string_length(const char *str) {
    int len = 0;
    while (str[len]) len++;
    return len;
}

void string_uppercase(char *str) {
    while (*str) {
        if (*str >= 'a' && *str <= 'z') {
            *str = *str - 'a' + 'A';
        }
        str++;
    }
}

void string_lowercase(char *str) {
    while (*str) {
        if (*str >= 'A' && *str <= 'Z') {
            *str = *str - 'A' + 'a';
        }
        str++;
    }
}

void string_reverse(char *str) {
    int len = string_length(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

// Array operations
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selection_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

int linear_search(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int binary_search(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

// Callback and higher-order functions
void process_array(int arr[], int n, void (*callback)(int*, int)) {
    callback(arr, n);
}

int filter_array(int arr[], int n, int result[], bool (*predicate)(int)) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (predicate(arr[i])) {
            result[count++] = arr[i];
        }
    }
    return count;
}

void for_each(int arr[], int n, void (*action)(int)) {
    for (int i = 0; i < n; i++) {
        action(arr[i]);
    }
}

int reduce_array(int arr[], int n, int initial, int (*reducer)(int, int)) {
    int result = initial;
    for (int i = 0; i < n; i++) {
        result = reducer(result, arr[i]);
    }
    return result;
}

// Predicate functions
bool is_even(int n) { return n % 2 == 0; }
bool is_positive(int n) { return n > 0; }
bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

// Action functions
void print_number(int n) { printf("%d ", n); }
void print_square(int n) { printf("%d ", n * n); }
void print_double(int n) { printf("%d ", n * 2); }

// Comparison functions
int compare_ascending(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int compare_descending(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

// State machine functions
void idle_enter(void) { printf("Entering IDLE state\n"); }
void idle_exit(void) { printf("Exiting IDLE state\n"); }
void running_enter(void) { printf("Entering RUNNING state\n"); }
void running_exit(void) { printf("Exiting RUNNING state\n"); }
void stopped_enter(void) { printf("Entering STOPPED state\n"); }
void stopped_exit(void) { printf("Exiting STOPPED state\n"); }

// Menu action functions
void show_help(void) {
    printf("Help: This is a demonstration menu system\n");
}

void show_about(void) {
    printf("About: Function Pointers Demo v1.0\n");
}

void show_credits(void) {
    printf("Credits: Created for C Programming Education\n");
}

void exit_program(void) {
    printf("Goodbye!\n");
}

// Command handler functions
void cmd_help(const char *args) {
    printf("Available commands: help, echo, calc, quit\n");
}

void cmd_echo(const char *args) {
    printf("Echo: %s\n", args ? args : "");
}

void cmd_calc(const char *args) {
    if (args) {
        int a, b;
        char op;
        if (sscanf(args, "%d %c %d", &a, &op, &b) == 3) {
            int (*operation)(int, int) = get_operation(op);
            if (operation) {
                printf("Result: %d %c %d = %d\n", a, op, b, operation(a, b));
            } else {
                printf("Invalid operator: %c\n", op);
            }
        } else {
            printf("Usage: calc <num1> <op> <num2>\n");
        }
    }
}

void cmd_quit(const char *args) {
    printf("Quitting command processor\n");
}

// Helper function for dynamic selection
int (*get_operation(char op))(int, int) {
    switch (op) {
        case '+': return add;
        case '-': return subtract;
        case '*': return multiply;
        case '/': return divide_op;
        default: return NULL;
    }
}

int main() {
    printf("COMPREHENSIVE FUNCTION POINTERS DEMONSTRATION\n");
    printf("=============================================\n\n");
    
    demonstrate_basic_function_pointers();
    demonstrate_function_pointer_arrays();
    demonstrate_callback_functions();
    demonstrate_function_pointer_structures();
    demonstrate_menu_system();
    demonstrate_dynamic_function_selection();
    demonstrate_sorting_with_function_pointers();
    demonstrate_advanced_function_pointers();
    
    printf("\nKey Concepts Covered:\n");
    printf("- Basic function pointer declaration and usage\n");
    printf("- Arrays of function pointers for dispatch tables\n");
    printf("- Function pointers as parameters (callbacks)\n");
    printf("- Higher-order functions (filter, map, reduce)\n");
    printf("- Function pointers in structures\n");
    printf("- State machines using function pointers\n");
    printf("- Menu systems and command processors\n");
    printf("- Dynamic function selection\n");
    printf("- Sorting with different comparison functions\n");
    printf("- 2D arrays of function pointers\n");
    
    printf("\nFunction Pointer Syntax Reference:\n");
    printf("- Declaration: return_type (*pointer_name)(parameter_types)\n");
    printf("- Assignment: pointer_name = function_name\n");
    printf("- Call: pointer_name(arguments) or (*pointer_name)(arguments)\n");
    printf("- Array: return_type (*array_name[])(parameter_types)\n");
    printf("- Parameter: void func(return_type (*fp)(parameter_types))\n");
    printf("- Return type: return_type (*func())(parameter_types)\n");
    
    printf("\nPractical Applications:\n");
    printf("- Event handling systems\n");
    printf("- Plugin architectures\n");
    printf("- State machines\n");
    printf("- Command processors\n");
    printf("- Algorithm selection\n");
    printf("- Callback-based APIs\n");
    
    return 0;
}