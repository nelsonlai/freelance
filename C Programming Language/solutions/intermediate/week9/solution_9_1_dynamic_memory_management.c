/**
 * Solution 9.1: Dynamic Memory Management System
 * Week 9 - Advanced Memory Management
 * 
 * Description: Comprehensive demonstration of dynamic memory allocation,
 * memory tracking, leak detection, and custom memory management techniques.
 * 
 * Learning Objectives:
 * - Understand malloc, calloc, realloc, and free
 * - Implement memory tracking and leak detection
 * - Create custom memory management functions
 * - Handle memory allocation failures gracefully
 * - Understand memory alignment and fragmentation
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

// ============================================================================
// MEMORY TRACKING STRUCTURES AND GLOBAL VARIABLES
// ============================================================================

/**
 * Structure to track each memory allocation
 * This allows us to keep track of all allocated memory blocks
 * and detect memory leaks, double frees, etc.
 */
typedef struct MemoryBlock {
    void *ptr;                    // Pointer to the allocated memory
    size_t size;                  // Size of the allocated block
    const char *file;             // Source file where allocation occurred
    int line;                     // Line number where allocation occurred
    struct MemoryBlock *next;     // Pointer to next block in linked list
    uint32_t magic_number;        // Magic number to detect corruption
} MemoryBlock;

// Global variables for memory tracking
static MemoryBlock *memory_list = NULL;    // Head of linked list of allocations
static size_t total_allocated = 0;         // Total bytes allocated
static size_t total_freed = 0;             // Total bytes freed
static int allocation_count = 0;            // Number of active allocations
static int leak_detection_enabled = 1;     // Flag to enable/disable leak detection

// Magic number to detect memory corruption
#define MEMORY_MAGIC_NUMBER 0xDEADBEEF

// ============================================================================
// FUNCTION PROTOTYPES
// ============================================================================

// Core memory management functions
void* debug_malloc(size_t size, const char *file, int line);
void* debug_calloc(size_t num, size_t size, const char *file, int line);
void* debug_realloc(void *ptr, size_t size, const char *file, int line);
void debug_free(void *ptr, const char *file, int line);

// Memory tracking and statistics
void print_memory_stats(void);
void detect_memory_leaks(void);
void print_allocation_list(void);
void enable_leak_detection(bool enable);

// Advanced memory management functions
void* safe_malloc(size_t size);
void* aligned_malloc(size_t size, size_t alignment);
void memory_copy(void *dest, const void *src, size_t n);
void memory_zero(void *ptr, size_t n);

// Memory pool implementation
typedef struct MemoryPool {
    void *pool_start;             // Start of the memory pool
    void *pool_end;               // End of the memory pool
    void *current_ptr;            // Current position in pool
    size_t pool_size;             // Total size of the pool
    size_t used_size;             // Amount of pool used
} MemoryPool;

MemoryPool* create_memory_pool(size_t size);
void* pool_alloc(MemoryPool *pool, size_t size);
void destroy_memory_pool(MemoryPool *pool);
void reset_memory_pool(MemoryPool *pool);

// Macro definitions for easy debugging
#define MALLOC(size) debug_malloc(size, __FILE__, __LINE__)
#define CALLOC(num, size) debug_calloc(num, size, __FILE__, __LINE__)
#define REALLOC(ptr, size) debug_realloc(ptr, size, __FILE__, __LINE__)
#define FREE(ptr) debug_free(ptr, __FILE__, __LINE__)

// ============================================================================
// CORE MEMORY MANAGEMENT IMPLEMENTATION
// ============================================================================

/**
 * Custom malloc with memory tracking
 * 
 * Parameters:
 * - size: Number of bytes to allocate
 * - file: Source file name (usually __FILE__)
 * - line: Line number (usually __LINE__)
 * 
 * Returns:
 * - Pointer to allocated memory on success
 * - NULL on failure
 * 
 * Side effects:
 * - Adds allocation to tracking list
 * - Updates global statistics
 * - Prints allocation information if debugging enabled
 */
void* debug_malloc(size_t size, const char *file, int line) {
    // Allocate the requested memory using standard malloc
    void *ptr = malloc(size);
    
    // Check if allocation failed
    if (!ptr) {
        printf("[ERROR] malloc failed: %zu bytes (%s:%d)\n", size, file, line);
        return NULL;
    }
    
    // Only track if leak detection is enabled
    if (leak_detection_enabled) {
        // Allocate a tracking block
        MemoryBlock *block = malloc(sizeof(MemoryBlock));
        if (!block) {
            printf("[ERROR] Failed to allocate tracking block\n");
            free(ptr);  // Clean up the original allocation
            return NULL;
        }
        
        // Initialize the tracking block
        block->ptr = ptr;
        block->size = size;
        block->file = file;
        block->line = line;
        block->magic_number = MEMORY_MAGIC_NUMBER;
        
        // Add to the front of the linked list
        block->next = memory_list;
        memory_list = block;
        
        // Update global statistics
        total_allocated += size;
        allocation_count++;
        
        // Print allocation information
        printf("[MALLOC] %zu bytes at %p (%s:%d)\n", size, ptr, file, line);
    }
    
    return ptr;
}

/**
 * Custom calloc with memory tracking
 * 
 * Parameters:
 * - num: Number of elements
 * - size: Size of each element
 * - file: Source file name
 * - line: Line number
 * 
 * Returns:
 * - Pointer to zero-initialized memory on success
 * - NULL on failure
 */
void* debug_calloc(size_t num, size_t size, const char *file, int line) {
    // Calculate total size needed
    size_t total_size = num * size;
    
    // Allocate using our debug malloc
    void *ptr = debug_malloc(total_size, file, line);
    
    // If allocation succeeded, zero out the memory
    if (ptr) {
        memset(ptr, 0, total_size);
        printf("[CALLOC] %zu elements of %zu bytes = %zu total bytes at %p (%s:%d)\n", 
               num, size, total_size, ptr, file, line);
    }
    
    return ptr;
}

/**
 * Custom realloc with memory tracking
 * 
 * Parameters:
 * - ptr: Pointer to existing memory block
 * - size: New size needed
 * - file: Source file name
 * - line: Line number
 * 
 * Returns:
 * - Pointer to resized memory on success
 * - NULL on failure
 */
void* debug_realloc(void *ptr, size_t size, const char *file, int line) {
    // Handle NULL pointer case (equivalent to malloc)
    if (!ptr) {
        return debug_malloc(size, file, line);
    }
    
    // Handle zero size case (equivalent to free)
    if (size == 0) {
        debug_free(ptr, file, line);
        return NULL;
    }
    
    // Find the existing allocation in our tracking list
    MemoryBlock *current = memory_list;
    MemoryBlock *prev = NULL;
    size_t old_size = 0;
    
    while (current) {
        if (current->ptr == ptr) {
            old_size = current->size;
            break;
        }
        prev = current;
        current = current->next;
    }
    
    // Perform the reallocation
    void *new_ptr = realloc(ptr, size);
    if (!new_ptr) {
        printf("[ERROR] realloc failed: %zu bytes (%s:%d)\n", size, file, line);
        return NULL;
    }
    
    // Update tracking information
    if (leak_detection_enabled && current) {
        // Update the existing block
        current->ptr = new_ptr;
        current->size = size;
        current->file = file;
        current->line = line;
        
        // Update global statistics
        total_allocated = total_allocated - old_size + size;
        
        printf("[REALLOC] %p -> %p (%zu -> %zu bytes) (%s:%d)\n", 
               ptr, new_ptr, old_size, size, file, line);
    }
    
    return new_ptr;
}

/**
 * Custom free with memory tracking and validation
 * 
 * Parameters:
 * - ptr: Pointer to memory to free
 * - file: Source file name
 * - line: Line number
 * 
 * Side effects:
 * - Removes allocation from tracking list
 * - Updates global statistics
 * - Detects double free attempts
 */
void debug_free(void *ptr, const char *file, int line) {
    // Handle NULL pointer (free(NULL) is safe)
    if (!ptr) {
        printf("[FREE] NULL pointer (%s:%d)\n", file, line);
        return;
    }
    
    // Find the allocation in our tracking list
    MemoryBlock *current = memory_list;
    MemoryBlock *prev = NULL;
    
    while (current) {
        if (current->ptr == ptr) {
            // Validate magic number to detect corruption
            if (current->magic_number != MEMORY_MAGIC_NUMBER) {
                printf("[ERROR] Memory corruption detected at %p (%s:%d)\n", 
                       ptr, file, line);
            }
            
            // Remove from tracking list
            if (prev) {
                prev->next = current->next;
            } else {
                memory_list = current->next;
            }
            
            // Update global statistics
            total_freed += current->size;
            allocation_count--;
            
            printf("[FREE] %zu bytes at %p (%s:%d)\n", 
                   current->size, ptr, file, line);
            
            // Free the tracking block
            free(current);
            
            // Free the actual memory
            free(ptr);
            return;
        }
        prev = current;
        current = current->next;
    }
    
    // If we get here, the pointer wasn't found in our tracking list
    printf("[ERROR] Double free or invalid free at %p (%s:%d)\n", 
           ptr, file, line);
}

// ============================================================================
// MEMORY TRACKING AND STATISTICS FUNCTIONS
// ============================================================================

/**
 * Print comprehensive memory statistics
 * Shows total allocated, freed, active allocations, and memory usage
 */
void print_memory_stats(void) {
    printf("\n=== MEMORY STATISTICS ===\n");
    printf("Total allocated: %zu bytes (%.2f KB)\n", 
           total_allocated, total_allocated / 1024.0);
    printf("Total freed: %zu bytes (%.2f KB)\n", 
           total_freed, total_freed / 1024.0);
    printf("Net allocated: %zu bytes (%.2f KB)\n", 
           total_allocated - total_freed, 
           (total_allocated - total_freed) / 1024.0);
    printf("Active allocations: %d\n", allocation_count);
    printf("Memory efficiency: %.2f%%\n", 
           allocation_count > 0 ? (double)total_freed / total_allocated * 100 : 0);
}

/**
 * Detect and report memory leaks
 * Scans through all tracked allocations and reports unfreed memory
 */
void detect_memory_leaks(void) {
    printf("\n=== MEMORY LEAK DETECTION ===\n");
    
    if (!memory_list) {
        printf("No memory leaks detected! All memory properly freed.\n");
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
    
    printf("Total leaked: %zu bytes (%.2f KB) in %d allocations\n", 
           total_leaked, total_leaked / 1024.0, leak_count);
}

/**
 * Print detailed list of all active allocations
 * Useful for debugging and understanding memory usage patterns
 */
void print_allocation_list(void) {
    printf("\n=== ACTIVE ALLOCATIONS ===\n");
    
    if (!memory_list) {
        printf("No active allocations.\n");
        return;
    }
    
    MemoryBlock *current = memory_list;
    int count = 0;
    
    while (current) {
        printf("%d. %zu bytes at %p (%s:%d)\n", 
               ++count, current->size, current->ptr, 
               current->file, current->line);
        current = current->next;
    }
    
    printf("Total active allocations: %d\n", count);
}

/**
 * Enable or disable memory leak detection
 * 
 * Parameters:
 * - enable: true to enable tracking, false to disable
 */
void enable_leak_detection(bool enable) {
    leak_detection_enabled = enable;
    printf("Memory leak detection %s\n", enable ? "enabled" : "disabled");
}

// ============================================================================
// ADVANCED MEMORY MANAGEMENT FUNCTIONS
// ============================================================================

/**
 * Safe malloc that handles allocation failures gracefully
 * 
 * Parameters:
 * - size: Number of bytes to allocate
 * 
 * Returns:
 * - Pointer to allocated memory on success
 * - NULL on failure (with error message)
 */
void* safe_malloc(size_t size) {
    void *ptr = malloc(size);
    if (!ptr) {
        printf("[ERROR] Memory allocation failed: %zu bytes\n", size);
        printf("Possible causes: insufficient memory, heap corruption\n");
    }
    return ptr;
}

/**
 * Allocate memory with specific alignment
 * 
 * Parameters:
 * - size: Number of bytes to allocate
 * - alignment: Required alignment (must be power of 2)
 * 
 * Returns:
 * - Pointer to aligned memory on success
 * - NULL on failure
 */
void* aligned_malloc(size_t size, size_t alignment) {
    // Validate alignment (must be power of 2)
    if (alignment == 0 || (alignment & (alignment - 1)) != 0) {
        printf("[ERROR] Invalid alignment: %zu (must be power of 2)\n", alignment);
        return NULL;
    }
    
    // Allocate extra space for alignment and pointer storage
    size_t total_size = size + alignment + sizeof(void*);
    void *raw_ptr = malloc(total_size);
    
    if (!raw_ptr) {
        return NULL;
    }
    
    // Calculate aligned address
    uintptr_t addr = (uintptr_t)raw_ptr + sizeof(void*);
    uintptr_t aligned_addr = (addr + alignment - 1) & ~(alignment - 1);
    
    // Store original pointer before aligned address
    void **ptr_store = (void**)(aligned_addr - sizeof(void*));
    *ptr_store = raw_ptr;
    
    printf("[ALIGNED_MALLOC] %zu bytes aligned to %zu bytes at %p\n", 
           size, alignment, (void*)aligned_addr);
    
    return (void*)aligned_addr;
}

/**
 * Free memory allocated with aligned_malloc
 * 
 * Parameters:
 * - ptr: Pointer returned by aligned_malloc
 */
void aligned_free(void *ptr) {
    if (!ptr) return;
    
    // Retrieve original pointer
    void **ptr_store = (void**)((uintptr_t)ptr - sizeof(void*));
    void *raw_ptr = *ptr_store;
    
    free(raw_ptr);
    printf("[ALIGNED_FREE] Freed aligned memory at %p\n", ptr);
}

/**
 * Safe memory copy function
 * 
 * Parameters:
 * - dest: Destination buffer
 * - src: Source buffer
 * - n: Number of bytes to copy
 * 
 * Side effects:
 * - Copies n bytes from src to dest
 * - Handles overlapping regions safely
 */
void memory_copy(void *dest, const void *src, size_t n) {
    if (!dest || !src || n == 0) {
        printf("[WARNING] Invalid parameters for memory_copy\n");
        return;
    }
    
    // Use memmove for safe copying (handles overlapping regions)
    memmove(dest, src, n);
    printf("[MEMORY_COPY] Copied %zu bytes from %p to %p\n", n, src, dest);
}

/**
 * Zero out memory region
 * 
 * Parameters:
 * - ptr: Pointer to memory region
 * - n: Number of bytes to zero
 */
void memory_zero(void *ptr, size_t n) {
    if (!ptr || n == 0) {
        printf("[WARNING] Invalid parameters for memory_zero\n");
        return;
    }
    
    memset(ptr, 0, n);
    printf("[MEMORY_ZERO] Zeroed %zu bytes at %p\n", n, ptr);
}

// ============================================================================
// MEMORY POOL IMPLEMENTATION
// ============================================================================

/**
 * Create a memory pool for efficient allocation
 * 
 * Parameters:
 * - size: Size of the memory pool in bytes
 * 
 * Returns:
 * - Pointer to MemoryPool structure on success
 * - NULL on failure
 */
MemoryPool* create_memory_pool(size_t size) {
    // Allocate the pool structure
    MemoryPool *pool = malloc(sizeof(MemoryPool));
    if (!pool) {
        printf("[ERROR] Failed to allocate memory pool structure\n");
        return NULL;
    }
    
    // Allocate the actual memory pool
    pool->pool_start = malloc(size);
    if (!pool->pool_start) {
        printf("[ERROR] Failed to allocate memory pool of %zu bytes\n", size);
        free(pool);
        return NULL;
    }
    
    // Initialize pool parameters
    pool->pool_end = (char*)pool->pool_start + size;
    pool->current_ptr = pool->pool_start;
    pool->pool_size = size;
    pool->used_size = 0;
    
    printf("[MEMORY_POOL] Created pool of %zu bytes at %p\n", 
           size, pool->pool_start);
    
    return pool;
}

/**
 * Allocate memory from a memory pool
 * 
 * Parameters:
 * - pool: Pointer to the memory pool
 * - size: Number of bytes to allocate
 * 
 * Returns:
 * - Pointer to allocated memory on success
 * - NULL on failure (insufficient space)
 */
void* pool_alloc(MemoryPool *pool, size_t size) {
    if (!pool || size == 0) {
        printf("[ERROR] Invalid parameters for pool_alloc\n");
        return NULL;
    }
    
    // Check if there's enough space
    if (pool->used_size + size > pool->pool_size) {
        printf("[ERROR] Insufficient space in memory pool: need %zu, have %zu\n", 
               size, pool->pool_size - pool->used_size);
        return NULL;
    }
    
    // Allocate from current position
    void *ptr = pool->current_ptr;
    pool->current_ptr = (char*)pool->current_ptr + size;
    pool->used_size += size;
    
    printf("[POOL_ALLOC] Allocated %zu bytes at %p (pool usage: %zu/%zu)\n", 
           size, ptr, pool->used_size, pool->pool_size);
    
    return ptr;
}

/**
 * Reset memory pool to initial state
 * 
 * Parameters:
 * - pool: Pointer to the memory pool
 */
void reset_memory_pool(MemoryPool *pool) {
    if (!pool) {
        printf("[ERROR] Invalid memory pool for reset\n");
        return;
    }
    
    pool->current_ptr = pool->pool_start;
    pool->used_size = 0;
    
    printf("[POOL_RESET] Reset memory pool (usage: %zu/%zu)\n", 
           pool->used_size, pool->pool_size);
}

/**
 * Destroy memory pool and free all associated memory
 * 
 * Parameters:
 * - pool: Pointer to the memory pool
 */
void destroy_memory_pool(MemoryPool *pool) {
    if (!pool) {
        printf("[ERROR] Invalid memory pool for destruction\n");
        return;
    }
    
    printf("[POOL_DESTROY] Destroying memory pool of %zu bytes\n", pool->pool_size);
    
    free(pool->pool_start);
    free(pool);
}

// ============================================================================
// DEMONSTRATION FUNCTIONS
// ============================================================================

/**
 * Demonstrate basic memory allocation and deallocation
 */
void demonstrate_basic_allocation(void) {
    printf("\n=== BASIC MEMORY ALLOCATION DEMONSTRATION ===\n");
    
    // Allocate various data types
    int *int_array = (int*)MALLOC(sizeof(int) * 10);
    char *string = (char*)MALLOC(50);
    double *double_ptr = (double*)MALLOC(sizeof(double));
    
    if (int_array && string && double_ptr) {
        // Initialize the allocated memory
        for (int i = 0; i < 10; i++) {
            int_array[i] = i * i;
        }
        strcpy(string, "Hello, Dynamic Memory!");
        *double_ptr = 3.14159;
        
        // Use the allocated memory
        printf("Integer array: ");
        for (int i = 0; i < 10; i++) {
            printf("%d ", int_array[i]);
        }
        printf("\n");
        printf("String: %s\n", string);
        printf("Double value: %.5f\n", *double_ptr);
        
        // Free the memory
        FREE(int_array);
        FREE(string);
        FREE(double_ptr);
    }
}

/**
 * Demonstrate memory reallocation
 */
void demonstrate_reallocation(void) {
    printf("\n=== MEMORY REALLOCATION DEMONSTRATION ===\n");
    
    // Start with small allocation
    int *array = (int*)MALLOC(sizeof(int) * 5);
    if (array) {
        // Initialize
        for (int i = 0; i < 5; i++) {
            array[i] = i;
        }
        
        printf("Original array (5 elements): ");
        for (int i = 0; i < 5; i++) {
            printf("%d ", array[i]);
        }
        printf("\n");
        
        // Reallocate to larger size
        array = (int*)REALLOC(array, sizeof(int) * 10);
        if (array) {
            // Initialize new elements
            for (int i = 5; i < 10; i++) {
                array[i] = i * 2;
            }
            
            printf("Reallocated array (10 elements): ");
            for (int i = 0; i < 10; i++) {
                printf("%d ", array[i]);
            }
            printf("\n");
            
            // Reallocate to smaller size
            array = (int*)REALLOC(array, sizeof(int) * 3);
            if (array) {
                printf("Shrunk array (3 elements): ");
                for (int i = 0; i < 3; i++) {
                    printf("%d ", array[i]);
                }
                printf("\n");
            }
            
            FREE(array);
        }
    }
}

/**
 * Demonstrate memory leaks and detection
 */
void demonstrate_memory_leaks(void) {
    printf("\n=== MEMORY LEAK DEMONSTRATION ===\n");
    
    // Intentionally create memory leaks
    char *leak1 = (char*)MALLOC(100);
    int *leak2 = (int*)MALLOC(sizeof(int) * 20);
    double *leak3 = (double*)MALLOC(sizeof(double) * 5);
    
    if (leak1 && leak2 && leak3) {
        strcpy(leak1, "This memory will be leaked!");
        printf("Created intentional memory leaks\n");
        
        // Only free one of them
        FREE(leak1);
        printf("Freed leak1, but leak2 and leak3 remain allocated\n");
    }
    
    // Demonstrate proper allocation and cleanup
    char *proper = (char*)MALLOC(200);
    if (proper) {
        strcpy(proper, "This memory will be properly freed");
        printf("Proper allocation: %s\n", proper);
        FREE(proper);
    }
}

/**
 * Demonstrate memory pool usage
 */
void demonstrate_memory_pool(void) {
    printf("\n=== MEMORY POOL DEMONSTRATION ===\n");
    
    // Create a memory pool
    MemoryPool *pool = create_memory_pool(1024);
    if (!pool) {
        printf("Failed to create memory pool\n");
        return;
    }
    
    // Allocate various items from the pool
    int *int_array = (int*)pool_alloc(pool, sizeof(int) * 10);
    char *string = (char*)pool_alloc(pool, 50);
    double *double_ptr = (double*)pool_alloc(pool, sizeof(double));
    
    if (int_array && string && double_ptr) {
        // Initialize and use the memory
        for (int i = 0; i < 10; i++) {
            int_array[i] = i * 3;
        }
        strcpy(string, "Memory Pool String");
        *double_ptr = 2.71828;
        
        printf("Pool allocations:\n");
        printf("Integer array: ");
        for (int i = 0; i < 10; i++) {
            printf("%d ", int_array[i]);
        }
        printf("\n");
        printf("String: %s\n", string);
        printf("Double: %.5f\n", *double_ptr);
        
        // Reset the pool (all allocations become invalid)
        reset_memory_pool(pool);
        printf("Memory pool reset - all previous allocations are now invalid\n");
        
        // Allocate again from the reset pool
        char *new_string = (char*)pool_alloc(pool, 30);
        if (new_string) {
            strcpy(new_string, "New allocation after reset");
            printf("New allocation: %s\n", new_string);
        }
    }
    
    // Destroy the memory pool
    destroy_memory_pool(pool);
}

/**
 * Demonstrate aligned memory allocation
 */
void demonstrate_aligned_allocation(void) {
    printf("\n=== ALIGNED MEMORY ALLOCATION DEMONSTRATION ===\n");
    
    // Allocate memory with different alignments
    void *ptr1 = aligned_malloc(100, 4);   // 4-byte alignment
    void *ptr2 = aligned_malloc(200, 8);   // 8-byte alignment
    void *ptr3 = aligned_malloc(300, 16);  // 16-byte alignment
    
    if (ptr1 && ptr2 && ptr3) {
        printf("Aligned allocations successful:\n");
        printf("4-byte aligned: %p (address %% 4 = %lu)\n", 
               ptr1, (uintptr_t)ptr1 % 4);
        printf("8-byte aligned: %p (address %% 8 = %lu)\n", 
               ptr2, (uintptr_t)ptr2 % 8);
        printf("16-byte aligned: %p (address %% 16 = %lu)\n", 
               ptr3, (uintptr_t)ptr3 % 16);
        
        // Use the aligned memory
        int *int_ptr = (int*)ptr1;
        *int_ptr = 42;
        printf("Stored value in aligned memory: %d\n", *int_ptr);
        
        // Free aligned memory
        aligned_free(ptr1);
        aligned_free(ptr2);
        aligned_free(ptr3);
    }
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main(void) {
    printf("DYNAMIC MEMORY MANAGEMENT SYSTEM DEMONSTRATION\n");
    printf("==============================================\n");
    
    // Enable memory leak detection
    enable_leak_detection(true);
    
    // Run demonstrations
    demonstrate_basic_allocation();
    demonstrate_reallocation();
    demonstrate_memory_leaks();
    demonstrate_memory_pool();
    demonstrate_aligned_allocation();
    
    // Print final statistics
    print_memory_stats();
    print_allocation_list();
    detect_memory_leaks();
    
    printf("\n=== KEY CONCEPTS COVERED ===\n");
    printf("1. Dynamic memory allocation (malloc, calloc, realloc, free)\n");
    printf("2. Memory tracking and leak detection\n");
    printf("3. Safe memory management practices\n");
    printf("4. Memory alignment and optimization\n");
    printf("5. Custom memory pool implementation\n");
    printf("6. Error handling and validation\n");
    printf("7. Memory statistics and debugging\n");
    printf("8. Advanced memory management techniques\n");
    
    return 0;
}
