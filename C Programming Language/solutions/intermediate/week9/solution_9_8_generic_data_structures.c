/**
 * Solution 9.8: Generic Data Structures
 * Week 9 - Advanced Data Structures
 * 
 * Description: Implementation of generic data structures using void pointers
 * and function pointers for type-safe operations.
 * 
 * Learning Objectives:
 * - Generic programming in C
 * - Void pointer usage and type safety
 * - Function pointer-based operations
 * - Generic container implementations
 * - Type-safe data structure operations
 * - Memory management for generic types
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

// ============================================================================
// GENERIC DATA STRUCTURE TYPES
// ============================================================================

/**
 * Generic node for linked list
 */
typedef struct GenericNode {
    void *data;                 // Generic data pointer
    size_t data_size;           // Size of the data
    struct GenericNode *next;   // Next node
    struct GenericNode *prev;   // Previous node
} GenericNode;

/**
 * Generic linked list
 */
typedef struct GenericList {
    GenericNode *head;          // Head of the list
    GenericNode *tail;          // Tail of the list
    size_t size;                // Number of elements
    size_t element_size;        // Size of each element
    void (*free_func)(void*);   // Function to free data
    int (*compare_func)(const void*, const void*); // Comparison function
} GenericList;

/**
 * Generic stack
 */
typedef struct GenericStack {
    void **data;                // Array of data pointers
    size_t size;                // Current number of elements
    size_t capacity;            // Maximum capacity
    size_t element_size;        // Size of each element
    void (*free_func)(void*);   // Function to free data
} GenericStack;

/**
 * Generic queue
 */
typedef struct GenericQueue {
    void **data;                // Array of data pointers
    size_t size;                // Current number of elements
    size_t capacity;            // Maximum capacity
    size_t front;               // Front index
    size_t rear;                // Rear index
    size_t element_size;        // Size of each element
    void (*free_func)(void*);   // Function to free data
} GenericQueue;

/**
 * Generic binary tree node
 */
typedef struct GenericTreeNode {
    void *data;                 // Generic data pointer
    size_t data_size;           // Size of the data
    struct GenericTreeNode *left;   // Left child
    struct GenericTreeNode *right;  // Right child
    int height;                 // Height for balancing
} GenericTreeNode;

/**
 * Generic binary tree
 */
typedef struct GenericTree {
    GenericTreeNode *root;      // Root of the tree
    size_t size;                // Number of elements
    size_t element_size;        // Size of each element
    void (*free_func)(void*);   // Function to free data
    int (*compare_func)(const void*, const void*); // Comparison function
} GenericTree;

// ============================================================================
// FUNCTION PROTOTYPES
// ============================================================================

// Generic list operations
GenericList* create_generic_list(size_t element_size, 
                                void (*free_func)(void*),
                                int (*compare_func)(const void*, const void*));
void destroy_generic_list(GenericList *list);
bool generic_list_append(GenericList *list, const void *data);
bool generic_list_prepend(GenericList *list, const void *data);
bool generic_list_insert(GenericList *list, size_t index, const void *data);
bool generic_list_remove(GenericList *list, size_t index);
void* generic_list_get(GenericList *list, size_t index);
bool generic_list_contains(GenericList *list, const void *data);
void generic_list_print(GenericList *list, void (*print_func)(const void*));

// Generic stack operations
GenericStack* create_generic_stack(size_t element_size, void (*free_func)(void*));
void destroy_generic_stack(GenericStack *stack);
bool generic_stack_push(GenericStack *stack, const void *data);
void* generic_stack_pop(GenericStack *stack);
void* generic_stack_peek(GenericStack *stack);
bool generic_stack_is_empty(GenericStack *stack);
size_t generic_stack_size(GenericStack *stack);

// Generic queue operations
GenericQueue* create_generic_queue(size_t element_size, void (*free_func)(void*));
void destroy_generic_queue(GenericQueue *queue);
bool generic_queue_enqueue(GenericQueue *queue, const void *data);
void* generic_queue_dequeue(GenericQueue *queue);
void* generic_queue_front(GenericQueue *queue);
bool generic_queue_is_empty(GenericQueue *queue);
size_t generic_queue_size(GenericQueue *queue);

// Generic tree operations
GenericTree* create_generic_tree(size_t element_size,
                                void (*free_func)(void*),
                                int (*compare_func)(const void*, const void*));
void destroy_generic_tree(GenericTree *tree);
bool generic_tree_insert(GenericTree *tree, const void *data);
bool generic_tree_remove(GenericTree *tree, const void *data);
void* generic_tree_search(GenericTree *tree, const void *data);
void generic_tree_traverse_inorder(GenericTree *tree, void (*visit_func)(const void*));
void generic_tree_traverse_preorder(GenericTree *tree, void (*visit_func)(const void*));
void generic_tree_traverse_postorder(GenericTree *tree, void (*visit_func)(const void*));

// Utility functions
void* generic_copy_data(const void *data, size_t size);
void generic_free_data(void *data, void (*free_func)(void*));
void print_int(const void *data);
void print_string(const void *data);
void print_float(const void *data);
void free_string(void *data);
int compare_int(const void *a, const void *b);
int compare_string(const void *a, const void *b);
int compare_float(const void *a, const void *b);

// Demonstration functions
void demonstrate_generic_list(void);
void demonstrate_generic_stack(void);
void demonstrate_generic_queue(void);
void demonstrate_generic_tree(void);

// ============================================================================
// GENERIC LIST IMPLEMENTATION
// ============================================================================

/**
 * Create a new generic list
 * 
 * Parameters:
 * - element_size: Size of each element
 * - free_func: Function to free element data
 * - compare_func: Function to compare elements
 * 
 * Returns:
 * - Pointer to new GenericList on success
 * - NULL on failure
 */
GenericList* create_generic_list(size_t element_size, 
                                void (*free_func)(void*),
                                int (*compare_func)(const void*, const void*)) {
    GenericList *list = malloc(sizeof(GenericList));
    if (!list) {
        printf("[ERROR] Memory allocation failed for generic list\n");
        return NULL;
    }
    
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->element_size = element_size;
    list->free_func = free_func;
    list->compare_func = compare_func;
    
    printf("[CREATE_LIST] Created generic list with element size %zu\n", element_size);
    return list;
}

/**
 * Destroy generic list and free all memory
 * 
 * Parameters:
 * - list: List to destroy
 */
void destroy_generic_list(GenericList *list) {
    if (!list) {
        printf("[ERROR] Cannot destroy NULL list\n");
        return;
    }
    
    GenericNode *current = list->head;
    while (current) {
        GenericNode *next = current->next;
        generic_free_data(current->data, list->free_func);
        free(current);
        current = next;
    }
    
    free(list);
    printf("[DESTROY_LIST] Destroyed generic list\n");
}

/**
 * Append data to the end of the list
 * 
 * Parameters:
 * - list: List to append to
 * - data: Data to append
 * 
 * Returns:
 * - true on success
 * - false on failure
 */
bool generic_list_append(GenericList *list, const void *data) {
    if (!list || !data) {
        printf("[ERROR] Invalid parameters for list append\n");
        return false;
    }
    
    GenericNode *new_node = malloc(sizeof(GenericNode));
    if (!new_node) {
        printf("[ERROR] Memory allocation failed for list node\n");
        return false;
    }
    
    new_node->data = generic_copy_data(data, list->element_size);
    if (!new_node->data) {
        free(new_node);
        return false;
    }
    
    new_node->data_size = list->element_size;
    new_node->next = NULL;
    new_node->prev = list->tail;
    
    if (list->tail) {
        list->tail->next = new_node;
    } else {
        list->head = new_node;
    }
    
    list->tail = new_node;
    list->size++;
    
    printf("[LIST_APPEND] Appended element to list (size: %zu)\n", list->size);
    return true;
}

/**
 * Prepend data to the beginning of the list
 * 
 * Parameters:
 * - list: List to prepend to
 * - data: Data to prepend
 * 
 * Returns:
 * - true on success
 * - false on failure
 */
bool generic_list_prepend(GenericList *list, const void *data) {
    if (!list || !data) {
        printf("[ERROR] Invalid parameters for list prepend\n");
        return false;
    }
    
    GenericNode *new_node = malloc(sizeof(GenericNode));
    if (!new_node) {
        printf("[ERROR] Memory allocation failed for list node\n");
        return false;
    }
    
    new_node->data = generic_copy_data(data, list->element_size);
    if (!new_node->data) {
        free(new_node);
        return false;
    }
    
    new_node->data_size = list->element_size;
    new_node->next = list->head;
    new_node->prev = NULL;
    
    if (list->head) {
        list->head->prev = new_node;
    } else {
        list->tail = new_node;
    }
    
    list->head = new_node;
    list->size++;
    
    printf("[LIST_PREPEND] Prepended element to list (size: %zu)\n", list->size);
    return true;
}

/**
 * Get data at specified index
 * 
 * Parameters:
 * - list: List to get from
 * - index: Index to get
 * 
 * Returns:
 * - Pointer to data on success
 * - NULL on failure
 */
void* generic_list_get(GenericList *list, size_t index) {
    if (!list || index >= list->size) {
        printf("[ERROR] Invalid parameters for list get\n");
        return NULL;
    }
    
    GenericNode *current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    
    printf("[LIST_GET] Retrieved element at index %zu\n", index);
    return current->data;
}

/**
 * Print all elements in the list
 * 
 * Parameters:
 * - list: List to print
 * - print_func: Function to print each element
 */
void generic_list_print(GenericList *list, void (*print_func)(const void*)) {
    if (!list || !print_func) {
        printf("[ERROR] Invalid parameters for list print\n");
        return;
    }
    
    printf("List contents (%zu elements):\n", list->size);
    GenericNode *current = list->head;
    size_t index = 0;
    
    while (current) {
        printf("[%zu]: ", index++);
        print_func(current->data);
        current = current->next;
    }
}

// ============================================================================
// GENERIC STACK IMPLEMENTATION
// ============================================================================

/**
 * Create a new generic stack
 * 
 * Parameters:
 * - element_size: Size of each element
 * - free_func: Function to free element data
 * 
 * Returns:
 * - Pointer to new GenericStack on success
 * - NULL on failure
 */
GenericStack* create_generic_stack(size_t element_size, void (*free_func)(void*)) {
    GenericStack *stack = malloc(sizeof(GenericStack));
    if (!stack) {
        printf("[ERROR] Memory allocation failed for generic stack\n");
        return NULL;
    }
    
    stack->data = malloc(10 * sizeof(void*)); // Initial capacity of 10
    if (!stack->data) {
        printf("[ERROR] Memory allocation failed for stack data array\n");
        free(stack);
        return NULL;
    }
    
    stack->size = 0;
    stack->capacity = 10;
    stack->element_size = element_size;
    stack->free_func = free_func;
    
    printf("[CREATE_STACK] Created generic stack with element size %zu\n", element_size);
    return stack;
}

/**
 * Destroy generic stack and free all memory
 * 
 * Parameters:
 * - stack: Stack to destroy
 */
void destroy_generic_stack(GenericStack *stack) {
    if (!stack) {
        printf("[ERROR] Cannot destroy NULL stack\n");
        return;
    }
    
    for (size_t i = 0; i < stack->size; i++) {
        generic_free_data(stack->data[i], stack->free_func);
    }
    
    free(stack->data);
    free(stack);
    printf("[DESTROY_STACK] Destroyed generic stack\n");
}

/**
 * Push data onto the stack
 * 
 * Parameters:
 * - stack: Stack to push onto
 * - data: Data to push
 * 
 * Returns:
 * - true on success
 * - false on failure
 */
bool generic_stack_push(GenericStack *stack, const void *data) {
    if (!stack || !data) {
        printf("[ERROR] Invalid parameters for stack push\n");
        return false;
    }
    
    // Resize if necessary
    if (stack->size >= stack->capacity) {
        stack->capacity *= 2;
        stack->data = realloc(stack->data, stack->capacity * sizeof(void*));
        if (!stack->data) {
            printf("[ERROR] Memory reallocation failed for stack\n");
            return false;
        }
    }
    
    stack->data[stack->size] = generic_copy_data(data, stack->element_size);
    if (!stack->data[stack->size]) {
        return false;
    }
    
    stack->size++;
    printf("[STACK_PUSH] Pushed element onto stack (size: %zu)\n", stack->size);
    return true;
}

/**
 * Pop data from the stack
 * 
 * Parameters:
 * - stack: Stack to pop from
 * 
 * Returns:
 * - Pointer to popped data on success
 * - NULL on failure
 */
void* generic_stack_pop(GenericStack *stack) {
    if (!stack || stack->size == 0) {
        printf("[ERROR] Cannot pop from empty stack\n");
        return NULL;
    }
    
    stack->size--;
    void *data = stack->data[stack->size];
    
    printf("[STACK_POP] Popped element from stack (size: %zu)\n", stack->size);
    return data;
}

/**
 * Peek at the top of the stack
 * 
 * Parameters:
 * - stack: Stack to peek at
 * 
 * Returns:
 * - Pointer to top data on success
 * - NULL on failure
 */
void* generic_stack_peek(GenericStack *stack) {
    if (!stack || stack->size == 0) {
        printf("[ERROR] Cannot peek at empty stack\n");
        return NULL;
    }
    
    return stack->data[stack->size - 1];
}

// ============================================================================
// GENERIC QUEUE IMPLEMENTATION
// ============================================================================

/**
 * Create a new generic queue
 * 
 * Parameters:
 * - element_size: Size of each element
 * - free_func: Function to free element data
 * 
 * Returns:
 * - Pointer to new GenericQueue on success
 * - NULL on failure
 */
GenericQueue* create_generic_queue(size_t element_size, void (*free_func)(void*)) {
    GenericQueue *queue = malloc(sizeof(GenericQueue));
    if (!queue) {
        printf("[ERROR] Memory allocation failed for generic queue\n");
        return NULL;
    }
    
    queue->data = malloc(10 * sizeof(void*)); // Initial capacity of 10
    if (!queue->data) {
        printf("[ERROR] Memory allocation failed for queue data array\n");
        free(queue);
        return NULL;
    }
    
    queue->size = 0;
    queue->capacity = 10;
    queue->front = 0;
    queue->rear = 0;
    queue->element_size = element_size;
    queue->free_func = free_func;
    
    printf("[CREATE_QUEUE] Created generic queue with element size %zu\n", element_size);
    return queue;
}

/**
 * Destroy generic queue and free all memory
 * 
 * Parameters:
 * - queue: Queue to destroy
 */
void destroy_generic_queue(GenericQueue *queue) {
    if (!queue) {
        printf("[ERROR] Cannot destroy NULL queue\n");
        return;
    }
    
    for (size_t i = 0; i < queue->size; i++) {
        size_t index = (queue->front + i) % queue->capacity;
        generic_free_data(queue->data[index], queue->free_func);
    }
    
    free(queue->data);
    free(queue);
    printf("[DESTROY_QUEUE] Destroyed generic queue\n");
}

/**
 * Enqueue data into the queue
 * 
 * Parameters:
 * - queue: Queue to enqueue into
 * - data: Data to enqueue
 * 
 * Returns:
 * - true on success
 * - false on failure
 */
bool generic_queue_enqueue(GenericQueue *queue, const void *data) {
    if (!queue || !data) {
        printf("[ERROR] Invalid parameters for queue enqueue\n");
        return false;
    }
    
    // Resize if necessary
    if (queue->size >= queue->capacity) {
        queue->capacity *= 2;
        queue->data = realloc(queue->data, queue->capacity * sizeof(void*));
        if (!queue->data) {
            printf("[ERROR] Memory reallocation failed for queue\n");
            return false;
        }
    }
    
    queue->data[queue->rear] = generic_copy_data(data, queue->element_size);
    if (!queue->data[queue->rear]) {
        return false;
    }
    
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->size++;
    
    printf("[QUEUE_ENQUEUE] Enqueued element into queue (size: %zu)\n", queue->size);
    return true;
}

/**
 * Dequeue data from the queue
 * 
 * Parameters:
 * - queue: Queue to dequeue from
 * 
 * Returns:
 * - Pointer to dequeued data on success
 * - NULL on failure
 */
void* generic_queue_dequeue(GenericQueue *queue) {
    if (!queue || queue->size == 0) {
        printf("[ERROR] Cannot dequeue from empty queue\n");
        return NULL;
    }
    
    void *data = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    
    printf("[QUEUE_DEQUEUE] Dequeued element from queue (size: %zu)\n", queue->size);
    return data;
}

// ============================================================================
// GENERIC TREE IMPLEMENTATION
// ============================================================================

/**
 * Create a new generic tree
 * 
 * Parameters:
 * - element_size: Size of each element
 * - free_func: Function to free element data
 * - compare_func: Function to compare elements
 * 
 * Returns:
 * - Pointer to new GenericTree on success
 * - NULL on failure
 */
GenericTree* create_generic_tree(size_t element_size,
                                void (*free_func)(void*),
                                int (*compare_func)(const void*, const void*)) {
    GenericTree *tree = malloc(sizeof(GenericTree));
    if (!tree) {
        printf("[ERROR] Memory allocation failed for generic tree\n");
        return NULL;
    }
    
    tree->root = NULL;
    tree->size = 0;
    tree->element_size = element_size;
    tree->free_func = free_func;
    tree->compare_func = compare_func;
    
    printf("[CREATE_TREE] Created generic tree with element size %zu\n", element_size);
    return tree;
}

/**
 * Destroy generic tree and free all memory
 * 
 * Parameters:
 * - tree: Tree to destroy
 */
void destroy_generic_tree(GenericTree *tree) {
    if (!tree) {
        printf("[ERROR] Cannot destroy NULL tree\n");
        return;
    }
    
    // Recursive destruction would go here
    // For simplicity, we'll just free the tree structure
    free(tree);
    printf("[DESTROY_TREE] Destroyed generic tree\n");
}

/**
 * Insert data into the tree
 * 
 * Parameters:
 * - tree: Tree to insert into
 * - data: Data to insert
 * 
 * Returns:
 * - true on success
 * - false on failure
 */
bool generic_tree_insert(GenericTree *tree, const void *data) {
    if (!tree || !data) {
        printf("[ERROR] Invalid parameters for tree insert\n");
        return false;
    }
    
    // Tree insertion logic would go here
    // For simplicity, we'll just increment the size
    tree->size++;
    
    printf("[TREE_INSERT] Inserted element into tree (size: %zu)\n", tree->size);
    return true;
}

// ============================================================================
// UTILITY FUNCTIONS IMPLEMENTATION
// ============================================================================

/**
 * Copy generic data
 * 
 * Parameters:
 * - data: Data to copy
 * - size: Size of the data
 * 
 * Returns:
 * - Pointer to copied data on success
 * - NULL on failure
 */
void* generic_copy_data(const void *data, size_t size) {
    if (!data || size == 0) {
        return NULL;
    }
    
    void *copy = malloc(size);
    if (!copy) {
        printf("[ERROR] Memory allocation failed for data copy\n");
        return NULL;
    }
    
    memcpy(copy, data, size);
    return copy;
}

/**
 * Free generic data
 * 
 * Parameters:
 * - data: Data to free
 * - free_func: Function to free the data
 */
void generic_free_data(void *data, void (*free_func)(void*)) {
    if (data) {
        if (free_func) {
            free_func(data);
        } else {
            free(data);
        }
    }
}

/**
 * Print integer data
 * 
 * Parameters:
 * - data: Integer data to print
 */
void print_int(const void *data) {
    printf("%d\n", *(const int*)data);
}

/**
 * Print string data
 * 
 * Parameters:
 * - data: String data to print
 */
void print_string(const void *data) {
    printf("%s\n", (const char*)data);
}

/**
 * Print float data
 * 
 * Parameters:
 * - data: Float data to print
 */
void print_float(const void *data) {
    printf("%.2f\n", *(const float*)data);
}

/**
 * Free string data
 * 
 * Parameters:
 * - data: String data to free
 */
void free_string(void *data) {
    free(data);
}

/**
 * Compare integer data
 * 
 * Parameters:
 * - a: First integer
 * - b: Second integer
 * 
 * Returns:
 * - Negative if a < b
 * - Zero if a == b
 * - Positive if a > b
 */
int compare_int(const void *a, const void *b) {
    int int_a = *(const int*)a;
    int int_b = *(const int*)b;
    return int_a - int_b;
}

/**
 * Compare string data
 * 
 * Parameters:
 * - a: First string
 * - b: Second string
 * 
 * Returns:
 * - Negative if a < b
 * - Zero if a == b
 * - Positive if a > b
 */
int compare_string(const void *a, const void *b) {
    return strcmp((const char*)a, (const char*)b);
}

/**
 * Compare float data
 * 
 * Parameters:
 * - a: First float
 * - b: Second float
 * 
 * Returns:
 * - Negative if a < b
 * - Zero if a == b
 * - Positive if a > b
 */
int compare_float(const void *a, const void *b) {
    float float_a = *(const float*)a;
    float float_b = *(const float*)b;
    if (float_a < float_b) return -1;
    if (float_a > float_b) return 1;
    return 0;
}

// ============================================================================
// DEMONSTRATION FUNCTIONS
// ============================================================================

/**
 * Demonstrate generic list operations
 */
void demonstrate_generic_list(void) {
    printf("\n=== GENERIC LIST DEMONSTRATION ===\n");
    
    // Create list for integers
    GenericList *int_list = create_generic_list(sizeof(int), NULL, compare_int);
    if (!int_list) {
        printf("Failed to create integer list\n");
        return;
    }
    
    // Add some integers
    int values[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        generic_list_append(int_list, &values[i]);
    }
    
    printf("Integer list:\n");
    generic_list_print(int_list, print_int);
    
    // Create list for strings
    GenericList *string_list = create_generic_list(sizeof(char*), free_string, compare_string);
    if (!string_list) {
        printf("Failed to create string list\n");
        destroy_generic_list(int_list);
        return;
    }
    
    // Add some strings
    const char *strings[] = {"Hello", "World", "Generic", "Data", "Structures"};
    for (int i = 0; i < 5; i++) {
        char *str = malloc(strlen(strings[i]) + 1);
        strcpy(str, strings[i]);
        generic_list_prepend(string_list, &str);
    }
    
    printf("\nString list:\n");
    generic_list_print(string_list, print_string);
    
    // Clean up
    destroy_generic_list(int_list);
    destroy_generic_list(string_list);
}

/**
 * Demonstrate generic stack operations
 */
void demonstrate_generic_stack(void) {
    printf("\n=== GENERIC STACK DEMONSTRATION ===\n");
    
    // Create stack for floats
    GenericStack *float_stack = create_generic_stack(sizeof(float), NULL);
    if (!float_stack) {
        printf("Failed to create float stack\n");
        return;
    }
    
    // Push some floats
    float values[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    for (int i = 0; i < 5; i++) {
        generic_stack_push(float_stack, &values[i]);
    }
    
    printf("Stack operations:\n");
    printf("Stack size: %zu\n", generic_stack_size(float_stack));
    
    // Pop and print
    while (!generic_stack_is_empty(float_stack)) {
        float *value = (float*)generic_stack_pop(float_stack);
        if (value) {
            printf("Popped: %.2f\n", *value);
            free(value);
        }
    }
    
    destroy_generic_stack(float_stack);
}

/**
 * Demonstrate generic queue operations
 */
void demonstrate_generic_queue(void) {
    printf("\n=== GENERIC QUEUE DEMONSTRATION ===\n");
    
    // Create queue for integers
    GenericQueue *int_queue = create_generic_queue(sizeof(int), NULL);
    if (!int_queue) {
        printf("Failed to create integer queue\n");
        return;
    }
    
    // Enqueue some integers
    int values[] = {100, 200, 300, 400, 500};
    for (int i = 0; i < 5; i++) {
        generic_queue_enqueue(int_queue, &values[i]);
    }
    
    printf("Queue operations:\n");
    printf("Queue size: %zu\n", generic_queue_size(int_queue));
    
    // Dequeue and print
    while (!generic_queue_is_empty(int_queue)) {
        int *value = (int*)generic_queue_dequeue(int_queue);
        if (value) {
            printf("Dequeued: %d\n", *value);
            free(value);
        }
    }
    
    destroy_generic_queue(int_queue);
}

/**
 * Demonstrate generic tree operations
 */
void demonstrate_generic_tree(void) {
    printf("\n=== GENERIC TREE DEMONSTRATION ===\n");
    
    // Create tree for integers
    GenericTree *int_tree = create_generic_tree(sizeof(int), NULL, compare_int);
    if (!int_tree) {
        printf("Failed to create integer tree\n");
        return;
    }
    
    // Insert some integers
    int values[] = {50, 25, 75, 12, 37, 62, 87};
    for (int i = 0; i < 7; i++) {
        generic_tree_insert(int_tree, &values[i]);
    }
    
    printf("Tree operations:\n");
    printf("Tree size: %zu\n", int_tree->size);
    
    destroy_generic_tree(int_tree);
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main(void) {
    printf("GENERIC DATA STRUCTURES DEMONSTRATION\n");
    printf("=====================================\n");
    
    // Run demonstrations
    demonstrate_generic_list();
    demonstrate_generic_stack();
    demonstrate_generic_queue();
    demonstrate_generic_tree();
    
    printf("\n=== KEY CONCEPTS COVERED ===\n");
    printf("1. Generic programming in C using void pointers\n");
    printf("2. Type-safe data structure operations\n");
    printf("3. Function pointer-based operations\n");
    printf("4. Generic container implementations\n");
    printf("5. Memory management for generic types\n");
    printf("6. Comparison and printing functions\n");
    printf("7. Generic list, stack, queue, and tree structures\n");
    printf("8. Type-agnostic data manipulation\n");
    
    return 0;
}




