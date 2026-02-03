/**
 * Solution 9.6: Advanced Pointer Techniques
 * Week 9 - Advanced Pointer Programming
 * 
 * Description: Comprehensive demonstration of advanced pointer techniques
 * including function pointers, pointer arithmetic, and complex data structures.
 * 
 * Learning Objectives:
 * - Advanced pointer arithmetic and manipulation
 * - Function pointers and callback mechanisms
 * - Pointer to pointer operations
 * - Complex data structure navigation
 * - Memory layout understanding
 * - Pointer safety and validation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ============================================================================
// ADVANCED POINTER STRUCTURES AND TYPES
// ============================================================================

/**
 * Structure for demonstrating complex pointer operations
 */
typedef struct ComplexData {
    int id;
    char name[50];
    float value;
    struct ComplexData *next;
    struct ComplexData *prev;
} ComplexData;

/**
 * Function pointer type for comparison functions
 */
typedef int (*CompareFunc)(const void *a, const void *b);

/**
 * Function pointer type for operation functions
 */
typedef void (*OperationFunc)(int *data);

/**
 * Structure for function pointer arrays
 */
typedef struct FunctionTable {
    char name[20];
    OperationFunc func;
} FunctionTable;

// ============================================================================
// FUNCTION PROTOTYPES
// ============================================================================

// Basic pointer operations
void demonstrate_pointer_arithmetic(void);
void demonstrate_pointer_to_pointer(void);
void demonstrate_array_of_pointers(void);
void demonstrate_pointer_arrays(void);

// Function pointer operations
void demonstrate_function_pointers(void);
void demonstrate_callback_mechanisms(void);
void demonstrate_function_pointer_arrays(void);

// Complex data structure operations
void demonstrate_linked_list_pointers(void);
void demonstrate_tree_navigation(void);
void demonstrate_matrix_operations(void);

// Memory layout and safety
void demonstrate_memory_layout(void);
void demonstrate_pointer_validation(void);
void demonstrate_alignment_operations(void);

// Advanced techniques
void demonstrate_pointer_casting(void);
void demonstrate_offset_calculations(void);
void demonstrate_pointer_comparison(void);

// Utility functions
ComplexData* create_complex_data(int id, const char *name, float value);
void print_complex_data(const ComplexData *data);
void free_complex_data(ComplexData *data);
void print_memory_address(const void *ptr, const char *description);

// Function pointer implementations
void increment_operation(int *data);
void decrement_operation(int *data);
void square_operation(int *data);
void double_operation(int *data);
int compare_int(const void *a, const void *b);
int compare_string(const void *a, const void *b);

// ============================================================================
// BASIC POINTER OPERATIONS IMPLEMENTATION
// ============================================================================

/**
 * Demonstrate pointer arithmetic operations
 */
void demonstrate_pointer_arithmetic(void) {
    printf("\n=== POINTER ARITHMETIC DEMONSTRATION ===\n");
    
    int array[] = {10, 20, 30, 40, 50};
    int *ptr = array;
    
    printf("Array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    
    printf("Pointer arithmetic:\n");
    printf("ptr = %p (points to %d)\n", (void*)ptr, *ptr);
    
    ptr++; // Increment pointer
    printf("ptr++ = %p (points to %d)\n", (void*)ptr, *ptr);
    
    ptr += 2; // Add 2 to pointer
    printf("ptr += 2 = %p (points to %d)\n", (void*)ptr, *ptr);
    
    ptr--; // Decrement pointer
    printf("ptr-- = %p (points to %d)\n", (void*)ptr, *ptr);
    
    // Calculate difference between pointers
    int *start = array;
    int *end = array + 4;
    printf("Difference between pointers: %ld elements\n", end - start);
    
    // Access array elements using pointer arithmetic
    printf("Array elements via pointer arithmetic:\n");
    for (int i = 0; i < 5; i++) {
        printf("array[%d] = %d (address: %p)\n", i, *(array + i), (void*)(array + i));
    }
}

/**
 * Demonstrate pointer to pointer operations
 */
void demonstrate_pointer_to_pointer(void) {
    printf("\n=== POINTER TO POINTER DEMONSTRATION ===\n");
    
    int value = 42;
    int *ptr1 = &value;
    int **ptr2 = &ptr1;
    int ***ptr3 = &ptr2;
    
    printf("value = %d (address: %p)\n", value, (void*)&value);
    printf("ptr1 = %p (points to %d)\n", (void*)ptr1, *ptr1);
    printf("ptr2 = %p (points to ptr1)\n", (void*)ptr2);
    printf("ptr3 = %p (points to ptr2)\n", (void*)ptr3);
    
    printf("\nDereferencing:\n");
    printf("*ptr1 = %d\n", *ptr1);
    printf("**ptr2 = %d\n", **ptr2);
    printf("***ptr3 = %d\n", ***ptr3);
    
    // Modify value through multiple levels of indirection
    ***ptr3 = 100;
    printf("\nAfter ***ptr3 = 100:\n");
    printf("value = %d\n", value);
    printf("*ptr1 = %d\n", *ptr1);
    printf("**ptr2 = %d\n", **ptr2);
    printf("***ptr3 = %d\n", ***ptr3);
}

/**
 * Demonstrate array of pointers
 */
void demonstrate_array_of_pointers(void) {
    printf("\n=== ARRAY OF POINTERS DEMONSTRATION ===\n");
    
    int a = 10, b = 20, c = 30, d = 40;
    int *pointers[] = {&a, &b, &c, &d};
    
    printf("Values: a=%d, b=%d, c=%d, d=%d\n", a, b, c, d);
    printf("Array of pointers:\n");
    
    for (int i = 0; i < 4; i++) {
        printf("pointers[%d] = %p (points to %d)\n", 
               i, (void*)pointers[i], *pointers[i]);
    }
    
    // Modify values through array of pointers
    printf("\nModifying values through array of pointers:\n");
    for (int i = 0; i < 4; i++) {
        *pointers[i] *= 2;
        printf("pointers[%d] now points to %d\n", i, *pointers[i]);
    }
    
    printf("Original values after modification: a=%d, b=%d, c=%d, d=%d\n", a, b, c, d);
}

/**
 * Demonstrate pointer arrays (2D array simulation)
 */
void demonstrate_pointer_arrays(void) {
    printf("\n=== POINTER ARRAYS DEMONSTRATION ===\n");
    
    // Create a 2D array using pointer to pointer
    int rows = 3, cols = 4;
    int **matrix = malloc(rows * sizeof(int*));
    
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j + 1;
        }
    }
    
    printf("2D Matrix (%dx%d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    // Access using pointer arithmetic
    printf("\nAccessing via pointer arithmetic:\n");
    for (int i = 0; i < rows; i++) {
        printf("Row %d: ", i);
        for (int j = 0; j < cols; j++) {
            printf("%3d ", *(*(matrix + i) + j));
        }
        printf("\n");
    }
    
    // Free memory
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// ============================================================================
// FUNCTION POINTER OPERATIONS IMPLEMENTATION
// ============================================================================

/**
 * Demonstrate function pointers
 */
void demonstrate_function_pointers(void) {
    printf("\n=== FUNCTION POINTERS DEMONSTRATION ===\n");
    
    // Function pointer declaration
    void (*func_ptr)(int*) = NULL;
    int data = 5;
    
    printf("Initial data: %d\n", data);
    
    // Assign different functions to the pointer
    func_ptr = increment_operation;
    func_ptr(&data);
    printf("After increment: %d\n", data);
    
    func_ptr = square_operation;
    func_ptr(&data);
    printf("After square: %d\n", data);
    
    func_ptr = double_operation;
    func_ptr(&data);
    printf("After double: %d\n", data);
    
    // Function pointer array
    OperationFunc operations[] = {
        increment_operation,
        decrement_operation,
        square_operation,
        double_operation
    };
    
    const char *operation_names[] = {
        "increment", "decrement", "square", "double"
    };
    
    data = 10;
    printf("\nApplying operations to data = %d:\n", data);
    
    for (int i = 0; i < 4; i++) {
        int original = data;
        operations[i](&data);
        printf("%s: %d -> %d\n", operation_names[i], original, data);
    }
}

/**
 * Demonstrate callback mechanisms
 */
void demonstrate_callback_mechanisms(void) {
    printf("\n=== CALLBACK MECHANISMS DEMONSTRATION ===\n");
    
    // Function that applies operation to array elements
    void apply_operation(int *array, int size, OperationFunc operation) {
        for (int i = 0; i < size; i++) {
            operation(&array[i]);
        }
    }
    
    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    // Apply different operations
    printf("After increment operation: ");
    apply_operation(numbers, size, increment_operation);
    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    printf("After square operation: ");
    apply_operation(numbers, size, square_operation);
    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
}

/**
 * Demonstrate function pointer arrays
 */
void demonstrate_function_pointer_arrays(void) {
    printf("\n=== FUNCTION POINTER ARRAYS DEMONSTRATION ===\n");
    
    FunctionTable function_table[] = {
        {"increment", increment_operation},
        {"decrement", decrement_operation},
        {"square", square_operation},
        {"double", double_operation}
    };
    
    int table_size = sizeof(function_table) / sizeof(function_table[0]);
    int data = 8;
    
    printf("Initial data: %d\n", data);
    printf("Available operations:\n");
    
    for (int i = 0; i < table_size; i++) {
        printf("%d. %s\n", i + 1, function_table[i].name);
    }
    
    // Apply each operation
    for (int i = 0; i < table_size; i++) {
        int original = data;
        function_table[i].func(&data);
        printf("Operation '%s': %d -> %d\n", 
               function_table[i].name, original, data);
    }
}

// ============================================================================
// COMPLEX DATA STRUCTURE OPERATIONS IMPLEMENTATION
// ============================================================================

/**
 * Demonstrate linked list pointer operations
 */
void demonstrate_linked_list_pointers(void) {
    printf("\n=== LINKED LIST POINTERS DEMONSTRATION ===\n");
    
    // Create a linked list
    ComplexData *head = create_complex_data(1, "First", 10.5);
    ComplexData *second = create_complex_data(2, "Second", 20.5);
    ComplexData *third = create_complex_data(3, "Third", 30.5);
    
    // Link the nodes
    head->next = second;
    second->next = third;
    second->prev = head;
    third->prev = second;
    
    // Navigate using pointers
    printf("Forward traversal:\n");
    ComplexData *current = head;
    while (current) {
        print_complex_data(current);
        current = current->next;
    }
    
    printf("\nBackward traversal:\n");
    current = third;
    while (current) {
        print_complex_data(current);
        current = current->prev;
    }
    
    // Insert new node in the middle
    printf("\nInserting new node in the middle:\n");
    ComplexData *new_node = create_complex_data(4, "Middle", 25.0);
    
    // Insert after second node
    new_node->next = second->next;
    new_node->prev = second;
    second->next->prev = new_node;
    second->next = new_node;
    
    // Print updated list
    current = head;
    while (current) {
        print_complex_data(current);
        current = current->next;
    }
    
    // Clean up
    free_complex_data(head);
    free_complex_data(second);
    free_complex_data(third);
    free_complex_data(new_node);
}

/**
 * Demonstrate tree navigation with pointers
 */
void demonstrate_tree_navigation(void) {
    printf("\n=== TREE NAVIGATION DEMONSTRATION ===\n");
    
    // Create a simple binary tree structure
    typedef struct TreeNode {
        int data;
        struct TreeNode *left;
        struct TreeNode *right;
    } TreeNode;
    
    TreeNode* create_tree_node(int data) {
        TreeNode *node = malloc(sizeof(TreeNode));
        node->data = data;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    
    // Create tree:      1
    //                 / \
    //                2   3
    //               / \
    //              4   5
    TreeNode *root = create_tree_node(1);
    root->left = create_tree_node(2);
    root->right = create_tree_node(3);
    root->left->left = create_tree_node(4);
    root->left->right = create_tree_node(5);
    
    // Function to traverse tree using pointers
    void traverse_tree(TreeNode *node, const char *traversal_type) {
        if (!node) return;
        
        if (strcmp(traversal_type, "preorder") == 0) {
            printf("%d ", node->data);
            traverse_tree(node->left, traversal_type);
            traverse_tree(node->right, traversal_type);
        } else if (strcmp(traversal_type, "inorder") == 0) {
            traverse_tree(node->left, traversal_type);
            printf("%d ", node->data);
            traverse_tree(node->right, traversal_type);
        } else if (strcmp(traversal_type, "postorder") == 0) {
            traverse_tree(node->left, traversal_type);
            traverse_tree(node->right, traversal_type);
            printf("%d ", node->data);
        }
    }
    
    printf("Tree traversals:\n");
    printf("Preorder: ");
    traverse_tree(root, "preorder");
    printf("\n");
    
    printf("Inorder: ");
    traverse_tree(root, "inorder");
    printf("\n");
    
    printf("Postorder: ");
    traverse_tree(root, "postorder");
    printf("\n");
    
    // Clean up tree
    void free_tree(TreeNode *node) {
        if (node) {
            free_tree(node->left);
            free_tree(node->right);
            free(node);
        }
    }
    free_tree(root);
}

// ============================================================================
// MEMORY LAYOUT AND SAFETY IMPLEMENTATION
// ============================================================================

/**
 * Demonstrate memory layout understanding
 */
void demonstrate_memory_layout(void) {
    printf("\n=== MEMORY LAYOUT DEMONSTRATION ===\n");
    
    // Local variables
    int local_var = 42;
    char local_array[10] = "Hello";
    
    // Dynamic allocation
    int *dynamic_var = malloc(sizeof(int));
    *dynamic_var = 100;
    
    // Array allocation
    int *dynamic_array = malloc(5 * sizeof(int));
    for (int i = 0; i < 5; i++) {
        dynamic_array[i] = i * 10;
    }
    
    printf("Memory addresses:\n");
    printf("Local variable: %p (value: %d)\n", (void*)&local_var, local_var);
    printf("Local array: %p (value: %s)\n", (void*)local_array, local_array);
    printf("Dynamic variable: %p (value: %d)\n", (void*)dynamic_var, *dynamic_var);
    printf("Dynamic array: %p\n", (void*)dynamic_array);
    
    // Show array element addresses
    printf("Dynamic array elements:\n");
    for (int i = 0; i < 5; i++) {
        printf("  [%d]: %p (value: %d)\n", i, (void*)(dynamic_array + i), dynamic_array[i]);
    }
    
    // Calculate memory differences
    printf("\nMemory layout analysis:\n");
    printf("Size of int: %zu bytes\n", sizeof(int));
    printf("Size of char: %zu bytes\n", sizeof(char));
    printf("Size of pointer: %zu bytes\n", sizeof(void*));
    
    // Clean up
    free(dynamic_var);
    free(dynamic_array);
}

/**
 * Demonstrate pointer validation
 */
void demonstrate_pointer_validation(void) {
    printf("\n=== POINTER VALIDATION DEMONSTRATION ===\n");
    
    // Safe pointer operations
    int *ptr = NULL;
    int value = 42;
    
    printf("Testing pointer validation:\n");
    
    // Check for NULL pointer
    if (ptr == NULL) {
        printf("Pointer is NULL - safe to initialize\n");
        ptr = &value;
    }
    
    // Validate pointer before use
    if (ptr != NULL) {
        printf("Pointer is valid - value: %d\n", *ptr);
    }
    
    // Demonstrate safe array access
    int array[5] = {1, 2, 3, 4, 5};
    int index = 3;
    
    if (index >= 0 && index < 5) {
        printf("Safe array access: array[%d] = %d\n", index, array[index]);
    } else {
        printf("Index %d is out of bounds\n", index);
    }
    
    // Demonstrate bounds checking with pointers
    int *array_ptr = array;
    int offset = 2;
    
    if (offset >= 0 && offset < 5) {
        printf("Safe pointer arithmetic: *(array_ptr + %d) = %d\n", 
               offset, *(array_ptr + offset));
    } else {
        printf("Offset %d is out of bounds\n", offset);
    }
}

// ============================================================================
// ADVANCED TECHNIQUES IMPLEMENTATION
// ============================================================================

/**
 * Demonstrate pointer casting
 */
void demonstrate_pointer_casting(void) {
    printf("\n=== POINTER CASTING DEMONSTRATION ===\n");
    
    int value = 0x12345678;
    int *int_ptr = &value;
    
    printf("Original value: 0x%08X (%d)\n", value, value);
    printf("Int pointer: %p\n", (void*)int_ptr);
    
    // Cast to different types
    char *char_ptr = (char*)int_ptr;
    short *short_ptr = (short*)int_ptr;
    float *float_ptr = (float*)int_ptr;
    
    printf("As char: ");
    for (int i = 0; i < sizeof(int); i++) {
        printf("0x%02X ", (unsigned char)char_ptr[i]);
    }
    printf("\n");
    
    printf("As short: 0x%04X\n", *short_ptr);
    printf("As float: %f\n", *float_ptr);
    
    // Demonstrate void pointer usage
    void *void_ptr = &value;
    printf("Void pointer: %p\n", void_ptr);
    
    // Cast back to int
    int *back_to_int = (int*)void_ptr;
    printf("Cast back to int: %d\n", *back_to_int);
}

/**
 * Demonstrate offset calculations
 */
void demonstrate_offset_calculations(void) {
    printf("\n=== OFFSET CALCULATIONS DEMONSTRATION ===\n");
    
    typedef struct {
        int id;
        char name[20];
        float salary;
        char department[15];
    } Employee;
    
    Employee emp = {101, "John Doe", 75000.0, "Engineering"};
    
    printf("Employee structure:\n");
    printf("ID: %d\n", emp.id);
    printf("Name: %s\n", emp.name);
    printf("Salary: %.2f\n", emp.salary);
    printf("Department: %s\n", emp.department);
    
    printf("\nMemory layout and offsets:\n");
    printf("Structure size: %zu bytes\n", sizeof(Employee));
    printf("ID offset: %zu bytes\n", (char*)&emp.id - (char*)&emp);
    printf("Name offset: %zu bytes\n", (char*)&emp.name - (char*)&emp);
    printf("Salary offset: %zu bytes\n", (char*)&emp.salary - (char*)&emp);
    printf("Department offset: %zu bytes\n", (char*)&emp.department - (char*)&emp);
    
    // Access fields using offset calculations
    char *base_ptr = (char*)&emp;
    int *id_ptr = (int*)(base_ptr + 0);
    char *name_ptr = base_ptr + sizeof(int);
    float *salary_ptr = (float*)(base_ptr + sizeof(int) + 20);
    
    printf("\nAccess via calculated offsets:\n");
    printf("ID: %d\n", *id_ptr);
    printf("Name: %s\n", name_ptr);
    printf("Salary: %.2f\n", *salary_ptr);
}

// ============================================================================
// UTILITY FUNCTIONS IMPLEMENTATION
// ============================================================================

/**
 * Create complex data structure
 */
ComplexData* create_complex_data(int id, const char *name, float value) {
    ComplexData *data = malloc(sizeof(ComplexData));
    if (data) {
        data->id = id;
        strncpy(data->name, name, sizeof(data->name) - 1);
        data->name[sizeof(data->name) - 1] = '\0';
        data->value = value;
        data->next = NULL;
        data->prev = NULL;
    }
    return data;
}

/**
 * Print complex data structure
 */
void print_complex_data(const ComplexData *data) {
    if (data) {
        printf("ID: %d, Name: %s, Value: %.2f\n", 
               data->id, data->name, data->value);
    }
}

/**
 * Free complex data structure
 */
void free_complex_data(ComplexData *data) {
    if (data) {
        free(data);
    }
}

/**
 * Print memory address with description
 */
void print_memory_address(const void *ptr, const char *description) {
    printf("%s: %p\n", description, ptr);
}

// ============================================================================
// FUNCTION POINTER IMPLEMENTATIONS
// ============================================================================

void increment_operation(int *data) {
    (*data)++;
}

void decrement_operation(int *data) {
    (*data)--;
}

void square_operation(int *data) {
    *data = (*data) * (*data);
}

void double_operation(int *data) {
    *data = (*data) * 2;
}

int compare_int(const void *a, const void *b) {
    int int_a = *(const int*)a;
    int int_b = *(const int*)b;
    return int_a - int_b;
}

int compare_string(const void *a, const void *b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main(void) {
    printf("ADVANCED POINTER TECHNIQUES DEMONSTRATION\n");
    printf("=========================================\n");
    
    // Run demonstrations
    demonstrate_pointer_arithmetic();
    demonstrate_pointer_to_pointer();
    demonstrate_array_of_pointers();
    demonstrate_pointer_arrays();
    
    demonstrate_function_pointers();
    demonstrate_callback_mechanisms();
    demonstrate_function_pointer_arrays();
    
    demonstrate_linked_list_pointers();
    demonstrate_tree_navigation();
    
    demonstrate_memory_layout();
    demonstrate_pointer_validation();
    
    demonstrate_pointer_casting();
    demonstrate_offset_calculations();
    
    printf("\n=== KEY CONCEPTS COVERED ===\n");
    printf("1. Advanced pointer arithmetic and manipulation\n");
    printf("2. Function pointers and callback mechanisms\n");
    printf("3. Pointer to pointer operations\n");
    printf("4. Complex data structure navigation\n");
    printf("5. Memory layout understanding\n");
    printf("6. Pointer safety and validation\n");
    printf("7. Advanced casting techniques\n");
    printf("8. Offset calculations and memory management\n");
    
    return 0;
}



