/**
 * Solution 9.9: Advanced Function Pointers
 * Week 9 - Advanced Function Pointer Programming
 * 
 * Description: Comprehensive demonstration of advanced function pointer
 * techniques including callbacks, function tables, and event systems.
 * 
 * Learning Objectives:
 * - Advanced function pointer usage
 * - Callback mechanisms and event handling
 * - Function pointer arrays and tables
 * - Generic function pointer operations
 * - Function pointer-based polymorphism
 * - Event-driven programming patterns
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

// ============================================================================
// FUNCTION POINTER TYPES AND STRUCTURES
// ============================================================================

/**
 * Function pointer type for mathematical operations
 */
typedef double (*MathFunction)(double, double);

/**
 * Function pointer type for string operations
 */
typedef char* (*StringFunction)(const char*);

/**
 * Function pointer type for comparison operations
 */
typedef int (*CompareFunction)(const void*, const void*);

/**
 * Function pointer type for event handlers
 */
typedef void (*EventHandler)(void*);

/**
 * Function pointer type for data processors
 */
typedef void (*DataProcessor)(void*);

/**
 * Function pointer type for validation functions
 */
typedef bool (*ValidatorFunction)(const void*);

/**
 * Structure for mathematical operation
 */
typedef struct MathOperation {
    char name[20];
    MathFunction func;
    char symbol;
} MathOperation;

/**
 * Structure for event
 */
typedef struct Event {
    int id;
    char name[32];
    void *data;
    EventHandler handler;
    uint64_t timestamp;
} Event;

/**
 * Structure for event system
 */
typedef struct EventSystem {
    Event *events;
    int event_count;
    int capacity;
    bool is_running;
} EventSystem;

/**
 * Structure for function table
 */
typedef struct FunctionTable {
    char name[32];
    void (*function)(void*);
    int priority;
    bool is_active;
} FunctionTable;

/**
 * Structure for callback registry
 */
typedef struct CallbackRegistry {
    char event_name[32];
    EventHandler *callbacks;
    int callback_count;
    int capacity;
} CallbackRegistry;

// ============================================================================
// FUNCTION PROTOTYPES
// ============================================================================

// Mathematical operations
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
double power(double a, double b);
double modulo(double a, double b);

// String operations
char* string_uppercase(const char* str);
char* string_lowercase(const char* str);
char* string_reverse(const char* str);
char* string_trim(const char* str);

// Comparison functions
int compare_int(const void* a, const void* b);
int compare_string(const void* a, const void* b);
int compare_float(const void* a, const void* b);

// Event system functions
EventSystem* create_event_system(int capacity);
void destroy_event_system(EventSystem* system);
bool register_event(EventSystem* system, int id, const char* name, void* data, EventHandler handler);
bool trigger_event(EventSystem* system, int event_id);
void process_events(EventSystem* system);

// Function table operations
FunctionTable* create_function_table(const char* name, void (*function)(void*), int priority);
void execute_function_table(FunctionTable* table, void* data);
void sort_function_table_by_priority(FunctionTable* tables, int count);

// Callback registry operations
CallbackRegistry* create_callback_registry(const char* event_name);
void destroy_callback_registry(CallbackRegistry* registry);
bool register_callback(CallbackRegistry* registry, EventHandler callback);
void trigger_callbacks(CallbackRegistry* registry, void* data);

// Generic function pointer operations
void apply_function_to_array(void* array, size_t count, size_t element_size, DataProcessor processor);
void filter_array(void* array, size_t count, size_t element_size, ValidatorFunction validator, void* result_array);
void* find_element(void* array, size_t count, size_t element_size, CompareFunction compare, const void* target);

// Event handlers
void print_event_handler(void* data);
void log_event_handler(void* data);
void count_event_handler(void* data);

// Data processors
void print_data_processor(void* data);
void double_data_processor(void* data);
void square_data_processor(void* data);

// Validator functions
bool is_positive_int(const void* data);
bool is_even_int(const void* data);
bool is_valid_string(const void* data);

// Demonstration functions
void demonstrate_math_operations(void);
void demonstrate_string_operations(void);
void demonstrate_event_system(void);
void demonstrate_function_tables(void);
void demonstrate_callback_system(void);
void demonstrate_generic_operations(void);

// Utility functions
void print_separator(const char* title);
uint64_t get_timestamp(void);
void* safe_malloc(size_t size);
void safe_free(void* ptr);

// ============================================================================
// MATHEMATICAL OPERATIONS IMPLEMENTATION
// ============================================================================

/**
 * Add two numbers
 */
double add(double a, double b) {
    return a + b;
}

/**
 * Subtract two numbers
 */
double subtract(double a, double b) {
    return a - b;
}

/**
 * Multiply two numbers
 */
double multiply(double a, double b) {
    return a * b;
}

/**
 * Divide two numbers
 */
double divide(double a, double b) {
    if (b == 0) {
        printf("[ERROR] Division by zero\n");
        return 0;
    }
    return a / b;
}

/**
 * Raise a to the power of b
 */
double power(double a, double b) {
    double result = 1;
    for (int i = 0; i < (int)b; i++) {
        result *= a;
    }
    return result;
}

/**
 * Modulo operation
 */
double modulo(double a, double b) {
    if (b == 0) {
        printf("[ERROR] Modulo by zero\n");
        return 0;
    }
    return (int)a % (int)b;
}

// ============================================================================
// STRING OPERATIONS IMPLEMENTATION
// ============================================================================

/**
 * Convert string to uppercase
 */
char* string_uppercase(const char* str) {
    if (!str) return NULL;
    
    size_t len = strlen(str);
    char* result = safe_malloc(len + 1);
    if (!result) return NULL;
    
    for (size_t i = 0; i < len; i++) {
        result[i] = toupper(str[i]);
    }
    result[len] = '\0';
    
    return result;
}

/**
 * Convert string to lowercase
 */
char* string_lowercase(const char* str) {
    if (!str) return NULL;
    
    size_t len = strlen(str);
    char* result = safe_malloc(len + 1);
    if (!result) return NULL;
    
    for (size_t i = 0; i < len; i++) {
        result[i] = tolower(str[i]);
    }
    result[len] = '\0';
    
    return result;
}

/**
 * Reverse string
 */
char* string_reverse(const char* str) {
    if (!str) return NULL;
    
    size_t len = strlen(str);
    char* result = safe_malloc(len + 1);
    if (!result) return NULL;
    
    for (size_t i = 0; i < len; i++) {
        result[i] = str[len - 1 - i];
    }
    result[len] = '\0';
    
    return result;
}

/**
 * Trim whitespace from string
 */
char* string_trim(const char* str) {
    if (!str) return NULL;
    
    size_t len = strlen(str);
    char* result = safe_malloc(len + 1);
    if (!result) return NULL;
    
    // Find start and end of non-whitespace
    size_t start = 0;
    while (start < len && isspace(str[start])) start++;
    
    size_t end = len;
    while (end > start && isspace(str[end - 1])) end--;
    
    // Copy trimmed string
    size_t new_len = end - start;
    strncpy(result, str + start, new_len);
    result[new_len] = '\0';
    
    return result;
}

// ============================================================================
// COMPARISON FUNCTIONS IMPLEMENTATION
// ============================================================================

/**
 * Compare integers
 */
int compare_int(const void* a, const void* b) {
    int int_a = *(const int*)a;
    int int_b = *(const int*)b;
    return int_a - int_b;
}

/**
 * Compare strings
 */
int compare_string(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

/**
 * Compare floats
 */
int compare_float(const void* a, const void* b) {
    float float_a = *(const float*)a;
    float float_b = *(const float*)b;
    if (float_a < float_b) return -1;
    if (float_a > float_b) return 1;
    return 0;
}

// ============================================================================
// EVENT SYSTEM IMPLEMENTATION
// ============================================================================

/**
 * Create event system
 */
EventSystem* create_event_system(int capacity) {
    EventSystem* system = safe_malloc(sizeof(EventSystem));
    if (!system) return NULL;
    
    system->events = safe_malloc(capacity * sizeof(Event));
    if (!system->events) {
        safe_free(system);
        return NULL;
    }
    
    system->event_count = 0;
    system->capacity = capacity;
    system->is_running = false;
    
    printf("[CREATE_EVENT_SYSTEM] Created event system with capacity %d\n", capacity);
    return system;
}

/**
 * Destroy event system
 */
void destroy_event_system(EventSystem* system) {
    if (!system) return;
    
    safe_free(system->events);
    safe_free(system);
    printf("[DESTROY_EVENT_SYSTEM] Destroyed event system\n");
}

/**
 * Register event
 */
bool register_event(EventSystem* system, int id, const char* name, void* data, EventHandler handler) {
    if (!system || system->event_count >= system->capacity) {
        printf("[ERROR] Cannot register event - system full or invalid\n");
        return false;
    }
    
    Event* event = &system->events[system->event_count];
    event->id = id;
    strncpy(event->name, name, sizeof(event->name) - 1);
    event->name[sizeof(event->name) - 1] = '\0';
    event->data = data;
    event->handler = handler;
    event->timestamp = get_timestamp();
    
    system->event_count++;
    
    printf("[REGISTER_EVENT] Registered event '%s' with ID %d\n", name, id);
    return true;
}

/**
 * Trigger event
 */
bool trigger_event(EventSystem* system, int event_id) {
    if (!system) return false;
    
    for (int i = 0; i < system->event_count; i++) {
        if (system->events[i].id == event_id) {
            Event* event = &system->events[i];
            printf("[TRIGGER_EVENT] Triggering event '%s' (ID: %d)\n", event->name, event->id);
            
            if (event->handler) {
                event->handler(event->data);
            }
            return true;
        }
    }
    
    printf("[ERROR] Event with ID %d not found\n", event_id);
    return false;
}

// ============================================================================
// FUNCTION TABLE OPERATIONS IMPLEMENTATION
// ============================================================================

/**
 * Create function table
 */
FunctionTable* create_function_table(const char* name, void (*function)(void*), int priority) {
    FunctionTable* table = safe_malloc(sizeof(FunctionTable));
    if (!table) return NULL;
    
    strncpy(table->name, name, sizeof(table->name) - 1);
    table->name[sizeof(table->name) - 1] = '\0';
    table->function = function;
    table->priority = priority;
    table->is_active = true;
    
    printf("[CREATE_FUNCTION_TABLE] Created function table '%s' with priority %d\n", name, priority);
    return table;
}

/**
 * Execute function table
 */
void execute_function_table(FunctionTable* table, void* data) {
    if (!table || !table->is_active || !table->function) {
        printf("[ERROR] Cannot execute function table\n");
        return;
    }
    
    printf("[EXECUTE_FUNCTION_TABLE] Executing '%s'\n", table->name);
    table->function(data);
}

// ============================================================================
// CALLBACK REGISTRY IMPLEMENTATION
// ============================================================================

/**
 * Create callback registry
 */
CallbackRegistry* create_callback_registry(const char* event_name) {
    CallbackRegistry* registry = safe_malloc(sizeof(CallbackRegistry));
    if (!registry) return NULL;
    
    strncpy(registry->event_name, event_name, sizeof(registry->event_name) - 1);
    registry->event_name[sizeof(registry->event_name) - 1] = '\0';
    
    registry->callbacks = safe_malloc(10 * sizeof(EventHandler));
    if (!registry->callbacks) {
        safe_free(registry);
        return NULL;
    }
    
    registry->callback_count = 0;
    registry->capacity = 10;
    
    printf("[CREATE_CALLBACK_REGISTRY] Created callback registry for '%s'\n", event_name);
    return registry;
}

/**
 * Destroy callback registry
 */
void destroy_callback_registry(CallbackRegistry* registry) {
    if (!registry) return;
    
    safe_free(registry->callbacks);
    safe_free(registry);
    printf("[DESTROY_CALLBACK_REGISTRY] Destroyed callback registry\n");
}

/**
 * Register callback
 */
bool register_callback(CallbackRegistry* registry, EventHandler callback) {
    if (!registry || !callback) {
        printf("[ERROR] Invalid parameters for callback registration\n");
        return false;
    }
    
    if (registry->callback_count >= registry->capacity) {
        registry->capacity *= 2;
        registry->callbacks = realloc(registry->callbacks, registry->capacity * sizeof(EventHandler));
        if (!registry->callbacks) {
            printf("[ERROR] Memory reallocation failed for callbacks\n");
            return false;
        }
    }
    
    registry->callbacks[registry->callback_count] = callback;
    registry->callback_count++;
    
    printf("[REGISTER_CALLBACK] Registered callback for '%s' (total: %d)\n", 
           registry->event_name, registry->callback_count);
    return true;
}

/**
 * Trigger callbacks
 */
void trigger_callbacks(CallbackRegistry* registry, void* data) {
    if (!registry) {
        printf("[ERROR] Cannot trigger callbacks - registry is NULL\n");
        return;
    }
    
    printf("[TRIGGER_CALLBACKS] Triggering %d callbacks for '%s'\n", 
           registry->callback_count, registry->event_name);
    
    for (int i = 0; i < registry->callback_count; i++) {
        if (registry->callbacks[i]) {
            registry->callbacks[i](data);
        }
    }
}

// ============================================================================
// GENERIC FUNCTION POINTER OPERATIONS IMPLEMENTATION
// ============================================================================

/**
 * Apply function to array elements
 */
void apply_function_to_array(void* array, size_t count, size_t element_size, DataProcessor processor) {
    if (!array || !processor) {
        printf("[ERROR] Invalid parameters for apply function\n");
        return;
    }
    
    char* data = (char*)array;
    for (size_t i = 0; i < count; i++) {
        processor(data + i * element_size);
    }
    
    printf("[APPLY_FUNCTION] Applied function to %zu elements\n", count);
}

/**
 * Filter array using validator function
 */
void filter_array(void* array, size_t count, size_t element_size, ValidatorFunction validator, void* result_array) {
    if (!array || !validator || !result_array) {
        printf("[ERROR] Invalid parameters for filter function\n");
        return;
    }
    
    char* data = (char*)array;
    char* result = (char*)result_array;
    size_t result_count = 0;
    
    for (size_t i = 0; i < count; i++) {
        if (validator(data + i * element_size)) {
            memcpy(result + result_count * element_size, data + i * element_size, element_size);
            result_count++;
        }
    }
    
    printf("[FILTER_ARRAY] Filtered %zu elements, %zu passed validation\n", count, result_count);
}

// ============================================================================
// EVENT HANDLERS IMPLEMENTATION
// ============================================================================

/**
 * Print event handler
 */
void print_event_handler(void* data) {
    if (data) {
        printf("  Event Handler: Printing data: %s\n", (char*)data);
    }
}

/**
 * Log event handler
 */
void log_event_handler(void* data) {
    if (data) {
        printf("  Log Handler: Logging event at timestamp %lu\n", get_timestamp());
    }
}

/**
 * Count event handler
 */
void count_event_handler(void* data) {
    static int count = 0;
    count++;
    printf("  Count Handler: Event count is now %d\n", count);
}

// ============================================================================
// DATA PROCESSORS IMPLEMENTATION
// ============================================================================

/**
 * Print data processor
 */
void print_data_processor(void* data) {
    if (data) {
        printf("Processing: %d\n", *(int*)data);
    }
}

/**
 * Double data processor
 */
void double_data_processor(void* data) {
    if (data) {
        int* value = (int*)data;
        *value *= 2;
        printf("Doubled value: %d\n", *value);
    }
}

/**
 * Square data processor
 */
void square_data_processor(void* data) {
    if (data) {
        int* value = (int*)data;
        *value = (*value) * (*value);
        printf("Squared value: %d\n", *value);
    }
}

// ============================================================================
// VALIDATOR FUNCTIONS IMPLEMENTATION
// ============================================================================

/**
 * Check if integer is positive
 */
bool is_positive_int(const void* data) {
    if (!data) return false;
    return *(const int*)data > 0;
}

/**
 * Check if integer is even
 */
bool is_even_int(const void* data) {
    if (!data) return false;
    return *(const int*)data % 2 == 0;
}

/**
 * Check if string is valid
 */
bool is_valid_string(const void* data) {
    if (!data) return false;
    const char* str = (const char*)data;
    return strlen(str) > 0;
}

// ============================================================================
// UTILITY FUNCTIONS IMPLEMENTATION
// ============================================================================

/**
 * Print separator with title
 */
void print_separator(const char* title) {
    printf("\n%s\n", title);
    printf("==========================================\n");
}

/**
 * Get current timestamp
 */
uint64_t get_timestamp(void) {
    return (uint64_t)time(NULL);
}

/**
 * Safe memory allocation
 */
void* safe_malloc(size_t size) {
    void* ptr = malloc(size);
    if (!ptr) {
        printf("[ERROR] Memory allocation failed: %zu bytes\n", size);
    }
    return ptr;
}

/**
 * Safe memory deallocation
 */
void safe_free(void* ptr) {
    if (ptr) {
        free(ptr);
    }
}

// ============================================================================
// DEMONSTRATION FUNCTIONS
// ============================================================================

/**
 * Demonstrate mathematical operations
 */
void demonstrate_math_operations(void) {
    print_separator("MATHEMATICAL OPERATIONS DEMONSTRATION");
    
    MathOperation operations[] = {
        {"Addition", add, '+'},
        {"Subtraction", subtract, '-'},
        {"Multiplication", multiply, '*'},
        {"Division", divide, '/'},
        {"Power", power, '^'},
        {"Modulo", modulo, '%'}
    };
    
    int num_operations = sizeof(operations) / sizeof(operations[0]);
    double a = 10.0, b = 3.0;
    
    printf("Performing operations on %.2f and %.2f:\n", a, b);
    
    for (int i = 0; i < num_operations; i++) {
        MathOperation* op = &operations[i];
        double result = op->func(a, b);
        printf("%s: %.2f %c %.2f = %.2f\n", op->name, a, op->symbol, b, result);
    }
}

/**
 * Demonstrate string operations
 */
void demonstrate_string_operations(void) {
    print_separator("STRING OPERATIONS DEMONSTRATION");
    
    StringFunction functions[] = {
        string_uppercase,
        string_lowercase,
        string_reverse,
        string_trim
    };
    
    const char* function_names[] = {
        "Uppercase",
        "Lowercase",
        "Reverse",
        "Trim"
    };
    
    const char* test_string = "  Hello World  ";
    int num_functions = sizeof(functions) / sizeof(functions[0]);
    
    printf("Original string: '%s'\n", test_string);
    
    for (int i = 0; i < num_functions; i++) {
        char* result = functions[i](test_string);
        if (result) {
            printf("%s: '%s'\n", function_names[i], result);
            free(result);
        }
    }
}

/**
 * Demonstrate event system
 */
void demonstrate_event_system(void) {
    print_separator("EVENT SYSTEM DEMONSTRATION");
    
    EventSystem* system = create_event_system(10);
    if (!system) {
        printf("Failed to create event system\n");
        return;
    }
    
    // Register events
    register_event(system, 1, "User Login", "user123", print_event_handler);
    register_event(system, 2, "Data Update", "data456", log_event_handler);
    register_event(system, 3, "System Error", "error789", count_event_handler);
    
    // Trigger events
    trigger_event(system, 1);
    trigger_event(system, 2);
    trigger_event(system, 3);
    trigger_event(system, 999); // Non-existent event
    
    destroy_event_system(system);
}

/**
 * Demonstrate function tables
 */
void demonstrate_function_tables(void) {
    print_separator("FUNCTION TABLES DEMONSTRATION");
    
    FunctionTable* tables[3];
    tables[0] = create_function_table("Print", print_data_processor, 1);
    tables[1] = create_function_table("Double", double_data_processor, 2);
    tables[2] = create_function_table("Square", square_data_processor, 3);
    
    int test_data = 5;
    
    printf("Processing data with value: %d\n", test_data);
    
    for (int i = 0; i < 3; i++) {
        if (tables[i]) {
            execute_function_table(tables[i], &test_data);
            safe_free(tables[i]);
        }
    }
}

/**
 * Demonstrate callback system
 */
void demonstrate_callback_system(void) {
    print_separator("CALLBACK SYSTEM DEMONSTRATION");
    
    CallbackRegistry* registry = create_callback_registry("Data Processing");
    if (!registry) {
        printf("Failed to create callback registry\n");
        return;
    }
    
    // Register callbacks
    register_callback(registry, print_event_handler);
    register_callback(registry, log_event_handler);
    register_callback(registry, count_event_handler);
    
    // Trigger callbacks
    trigger_callbacks(registry, "test data");
    
    destroy_callback_registry(registry);
}

/**
 * Demonstrate generic operations
 */
void demonstrate_generic_operations(void) {
    print_separator("GENERIC OPERATIONS DEMONSTRATION");
    
    // Test array
    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int count = sizeof(numbers) / sizeof(numbers[0]);
    
    printf("Original array: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    // Apply function to array
    printf("\nApplying double function to array:\n");
    apply_function_to_array(numbers, count, sizeof(int), double_data_processor);
    
    printf("Array after doubling: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    // Filter array
    int filtered[10];
    printf("\nFiltering positive numbers:\n");
    filter_array(numbers, count, sizeof(int), is_positive_int, filtered);
    
    printf("Filtered array: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", filtered[i]);
    }
    printf("\n");
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main(void) {
    printf("ADVANCED FUNCTION POINTERS DEMONSTRATION\n");
    printf("========================================\n");
    
    // Run demonstrations
    demonstrate_math_operations();
    demonstrate_string_operations();
    demonstrate_event_system();
    demonstrate_function_tables();
    demonstrate_callback_system();
    demonstrate_generic_operations();
    
    printf("\n=== KEY CONCEPTS COVERED ===\n");
    printf("1. Advanced function pointer usage and patterns\n");
    printf("2. Callback mechanisms and event handling\n");
    printf("3. Function pointer arrays and tables\n");
    printf("4. Generic function pointer operations\n");
    printf("5. Function pointer-based polymorphism\n");
    printf("6. Event-driven programming patterns\n");
    printf("7. Dynamic function dispatch and routing\n");
    printf("8. Function pointer safety and validation\n");
    
    return 0;
}




