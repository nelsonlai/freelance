/**
 * Stack Memory and Memory Management
 * Comprehensive demonstration of stack memory, memory allocation, and leak detection
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Global variables for memory tracking
static size_t total_allocated = 0;
static size_t total_freed = 0;
static int allocation_count = 0;

// Memory tracking structure
typedef struct MemoryBlock {
    void *ptr;
    size_t size;
    const char *file;
    int line;
    struct MemoryBlock *next;
} MemoryBlock;

static MemoryBlock *memory_list = NULL;

// Memory tracking functions
void* debug_malloc(size_t size, const char *file, int line);
void debug_free(void *ptr, const char *file, int line);
void print_memory_stats();
void detect_memory_leaks();

/* Macro definitions for memory allocation and free */
#define MALLOC(size) debug_malloc(size, __FILE__, __LINE__)
#define FREE(ptr) debug_free(ptr, __FILE__, __LINE__)

void demonstrate_stack_memory() {
    printf("=== Stack Memory Demonstration ===\n");
    
    // Local variables are allocated on stack
    int stack_var = 42;
    char stack_array[100];
    
    printf("Stack variable address: %p\n", (void*)&stack_var);
    printf("Stack array address: %p\n", (void*)stack_array);
    
    // Show stack growth direction
    int var1 = 1;
    int var2 = 2;
    int var3 = 3;
    
    printf("\nStack growth direction:\n");
    printf("var1 address: %p\n", (void*)&var1);
    printf("var2 address: %p\n", (void*)&var2);
    printf("var3 address: %p\n", (void*)&var3);
    
    if (&var2 < &var1) {
        printf("Stack grows downward (higher to lower addresses)\n");
    } else {
        printf("Stack grows upward (lower to higher addresses)\n");
    }
    
    // Demonstrate automatic cleanup
    {
        int block_var = 100;
        char block_array[50];
        printf("\nInside block - block_var address: %p\n", (void*)&block_var);
        printf("Inside block - block_array address: %p\n", (void*)block_array);
        // Variables automatically freed when leaving scope
    }
    printf("Exited block - variables automatically cleaned up\n");
}

void demonstrate_stack_overflow() {
    printf("\n=== Stack Overflow Demonstration ===\n");
    
    // Large stack allocation
    printf("Allocating large array on stack...\n");
    
    // This might cause stack overflow on some systems
    // char large_array[1000000];  // 1MB array - commented to prevent crash
    
    printf("Note: Large stack allocations can cause stack overflow!\n");
    printf("Stack size is limited (typically 1-8 MB)\n");
    
    // Recursive function can also cause stack overflow
    printf("Recursive calls also consume stack space\n");
}

void recursive_function(int depth) {
    char local_array[1000];  // Each call allocates 1KB on stack
    
    if (depth <= 0) {
        printf("Reached maximum recursion depth\n");
        return;
    }
    
    if (depth % 100 == 0) {
        printf("Recursion depth: %d\n", depth);
    }
    
    recursive_function(depth - 1);
}

void demonstrate_heap_allocation() {
    printf("\n=== Heap Memory Allocation ===\n");
    
    // malloc - allocate uninitialized memory
    int *ptr1 = (int*)MALLOC(sizeof(int) * 10);
    if (ptr1) {
        printf("Allocated 10 integers with malloc at %p\n", (void*)ptr1);
        for (int i = 0; i < 10; i++) {
            ptr1[i] = i * i;
        }
    }
    
    // calloc - allocate zero-initialized memory
    int *ptr2 = (int*)calloc(10, sizeof(int));
    if (ptr2) {
        printf("Allocated 10 integers with calloc at %p\n", (void*)ptr2);
        printf("Values after calloc (should be zero): ");
        for (int i = 0; i < 5; i++) {
            printf("%d ", ptr2[i]);
        }
        printf("\n");
    }
    
    // realloc - resize memory block
    ptr2 = (int*)realloc(ptr2, sizeof(int) * 20);
    if (ptr2) {
        printf("Reallocated to 20 integers at %p\n", (void*)ptr2);
        for (int i = 10; i < 20; i++) {
            ptr2[i] = i;
        }
    }
    
    // Show memory addresses
    printf("\nMemory addresses:\n");
    printf("Stack variable address: %p\n", (void*)&ptr1);
    printf("Heap memory address: %p\n", (void*)ptr1);
    printf("Difference: %ld bytes\n", abs((char*)ptr1 - (char*)&ptr1));
    
    // Free memory
    FREE(ptr1);
    free(ptr2);  // Using standard free for calloc/realloc
}

void demonstrate_memory_leaks() {
    printf("\n=== Memory Leak Demonstration ===\n");
    
    // Intentional memory leak
    char *leaked_memory = (char*)MALLOC(1000);
    if (leaked_memory) {
        strcpy(leaked_memory, "This memory will be leaked!");
        printf("Allocated 1000 bytes: %s\n", leaked_memory);
        // Intentionally not freeing this memory
    }
    
    // Another leak
    int *another_leak = (int*)MALLOC(sizeof(int) * 50);
    if (another_leak) {
        printf("Allocated 50 integers at %p\n", (void*)another_leak);
        // Not freeing this either
    }
    
    // Proper allocation and deallocation
    char *proper_memory = (char*)MALLOC(500);
    if (proper_memory) {
        strcpy(proper_memory, "This memory will be properly freed");
        printf("Allocated 500 bytes: %s\n", proper_memory);
        FREE(proper_memory);  // Properly freed
    }
}

void demonstrate_double_free() {
    printf("\n=== Double Free Detection ===\n");
    
    char *ptr = (char*)MALLOC(100);
    if (ptr) {
        strcpy(ptr, "Test string");
        printf("Allocated and initialized: %s\n", ptr);
        
        FREE(ptr);
        printf("Memory freed once\n");
        
        // Attempt double free (our debug function should catch this)
        FREE(ptr);
        printf("Attempted double free - should be detected\n");
    }
}

void demonstrate_use_after_free() {
    printf("\n=== Use After Free Detection ===\n");
    
    int *ptr = (int*)MALLOC(sizeof(int) * 10);
    if (ptr) {
        for (int i = 0; i < 10; i++) {
            ptr[i] = i;
        }
        printf("Initialized array\n");
        
        FREE(ptr);
        printf("Memory freed\n");
        
        // Use after free (dangerous!)
        printf("Attempting to use freed memory (dangerous!):\n");
        // printf("First element: %d\n", ptr[0]);  // Commented to prevent crash
        printf("Note: This would be undefined behavior!\n");
    }
}

void demonstrate_memory_alignment() {
    printf("\n=== Memory Alignment ===\n");
    
    struct TestStruct {
        char c;     // 1 byte
        int i;      // 4 bytes
        char c2;    // 1 byte
        double d;   // 8 bytes
    };
    
    printf("Size of char: %zu\n", sizeof(char));
    printf("Size of int: %zu\n", sizeof(int));
    printf("Size of double: %zu\n", sizeof(double));
    printf("Size of struct: %zu (note padding for alignment)\n", sizeof(struct TestStruct));
    
    struct TestStruct s;
    printf("\nStruct member addresses:\n");
    printf("c:  %p (offset: %zu)\n", (void*)&s.c, (char*)&s.c - (char*)&s);
    printf("i:  %p (offset: %zu)\n", (void*)&s.i, (char*)&s.i - (char*)&s);
    printf("c2: %p (offset: %zu)\n", (void*)&s.c2, (char*)&s.c2 - (char*)&s);
    printf("d:  %p (offset: %zu)\n", (void*)&s.d, (char*)&s.d - (char*)&s);
}

// Memory tracking implementation
void* debug_malloc(size_t size, const char *file, int line) {
    void *ptr = malloc(size);
    if (!ptr) return NULL;
    
    // Track allocation
    MemoryBlock *block = malloc(sizeof(MemoryBlock));
    if (block) {
        block->ptr = ptr;
        block->size = size;
        block->file = file;
        block->line = line;
        block->next = memory_list;
        memory_list = block;
        
        total_allocated += size;
        allocation_count++;
        
        printf("[MALLOC] %zu bytes at %p (%s:%d)\n", size, ptr, file, line);
    }
    
    return ptr;
}

void debug_free(void *ptr, const char *file, int line) {
    if (!ptr) return;
    
    // Find and remove from tracking list
    MemoryBlock *current = memory_list;
    MemoryBlock *prev = NULL;
    
    while (current) {
        if (current->ptr == ptr) {
            // Found the block
            if (prev) {
                prev->next = current->next;
            } else {
                memory_list = current->next;
            }
            
            total_freed += current->size;
            printf("[FREE] %zu bytes at %p (%s:%d)\n", current->size, ptr, file, line);
            
            free(current);
            free(ptr);
            return;
        }
        prev = current;
        current = current->next;
    }
    
    printf("[ERROR] Double free or invalid free at %p (%s:%d)\n", ptr, file, line);
}

void print_memory_stats() {
    printf("\n=== Memory Statistics ===\n");
    printf("Total allocated: %zu bytes\n", total_allocated);
    printf("Total freed: %zu bytes\n", total_freed);
    printf("Net allocated: %zu bytes\n", total_allocated - total_freed);
    printf("Active allocations: %d\n", allocation_count);
}

void detect_memory_leaks() {
    printf("\n=== Memory Leak Detection ===\n");
    
    if (!memory_list) {
        printf("No memory leaks detected!\n");
        return;
    }
    
    printf("Memory leaks detected:\n");
    MemoryBlock *current = memory_list;
    size_t total_leaked = 0;
    int leak_count = 0;
    
    while (current) {
        printf("LEAK: %zu bytes at %p (allocated at %s:%d)\n", 
               current->size, current->ptr, current->file, current->line);
        total_leaked += current->size;
        leak_count++;
        current = current->next;
    }
    
    printf("Total leaked: %zu bytes in %d allocations\n", total_leaked, leak_count);
}

int main() {
    printf("STACK MEMORY AND MEMORY MANAGEMENT DEMONSTRATION\n");
    printf("===============================================\n\n");
    
    demonstrate_stack_memory();
    demonstrate_stack_overflow();
    
    printf("\nTesting recursive calls (limited depth):\n");
    recursive_function(500);  // Limited to prevent actual overflow
    
    demonstrate_heap_allocation();
    demonstrate_memory_leaks();
    demonstrate_double_free();
    demonstrate_use_after_free();
    demonstrate_memory_alignment();
    
    print_memory_stats();
    detect_memory_leaks();
    
    printf("\nKey Concepts Covered:\n");
    printf("- Stack memory characteristics and limitations\n");
    printf("- Stack vs heap memory allocation\n");
    printf("- Memory allocation functions (malloc, calloc, realloc)\n");
    printf("- Memory leak detection and prevention\n");
    printf("- Double free and use-after-free errors\n");
    printf("- Memory alignment and padding\n");
    printf("- Memory debugging techniques\n");
    
    return 0;
}
