/**
 * Solution 9.7: Memory Pool Allocator
 * Week 9 - Advanced Memory Management
 * 
 * Description: Comprehensive memory pool implementation with efficient
 * allocation, deallocation, and memory management strategies.
 * 
 * Learning Objectives:
 * - Memory pool design and implementation
 * - Efficient memory allocation strategies
 * - Memory fragmentation prevention
 * - Pool-based memory management
 * - Performance optimization techniques
 * - Memory debugging and analysis
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

// ============================================================================
// MEMORY POOL STRUCTURES
// ============================================================================

/**
 * Structure representing a memory block in the pool
 */
typedef struct MemoryBlock {
    void *data;                 // Pointer to actual data
    size_t size;               // Size of the block
    bool is_free;              // Whether block is free
    struct MemoryBlock *next;  // Next block in the list
    struct MemoryBlock *prev;  // Previous block in the list
    uint32_t magic_number;     // Magic number for corruption detection
} MemoryBlock;

/**
 * Structure representing a memory pool
 */
typedef struct MemoryPool {
    void *pool_start;           // Start of the memory pool
    void *pool_end;             // End of the memory pool
    size_t pool_size;           // Total size of the pool
    size_t used_size;           // Amount of pool used
    size_t free_size;           // Amount of pool free
    MemoryBlock *free_list;     // List of free blocks
    MemoryBlock *used_list;     // List of used blocks
    int block_count;            // Number of blocks
    int free_block_count;       // Number of free blocks
    int used_block_count;       // Number of used blocks
    bool is_initialized;        // Whether pool is initialized
    char name[32];              // Pool name for debugging
} MemoryPool;

/**
 * Structure for memory pool statistics
 */
typedef struct PoolStats {
    size_t total_size;          // Total pool size
    size_t used_size;           // Used size
    size_t free_size;           // Free size
    int total_blocks;           // Total number of blocks
    int free_blocks;            // Number of free blocks
    int used_blocks;            // Number of used blocks
    float utilization;          // Utilization percentage
    int fragmentation_count;    // Number of fragmented areas
    size_t largest_free_block;  // Size of largest free block
    size_t smallest_free_block; // Size of smallest free block
} PoolStats;

/**
 * Structure for allocation request
 */
typedef struct AllocationRequest {
    size_t size;                // Requested size
    size_t alignment;           // Required alignment
    const char *file;           // Source file
    int line;                   // Source line
    uint64_t timestamp;         // Allocation timestamp
} AllocationRequest;

// Constants
#define MEMORY_MAGIC_NUMBER 0xDEADBEEF
#define DEFAULT_ALIGNMENT 8
#define MIN_BLOCK_SIZE sizeof(MemoryBlock)
#define MAX_POOL_NAME_LENGTH 31

// ============================================================================
// FUNCTION PROTOTYPES
// ============================================================================

// Pool creation and destruction
MemoryPool* create_memory_pool(size_t size, const char *name);
void destroy_memory_pool(MemoryPool *pool);
bool initialize_memory_pool(MemoryPool *pool, size_t size, const char *name);

// Memory allocation and deallocation
void* pool_alloc(MemoryPool *pool, size_t size);
void* pool_alloc_aligned(MemoryPool *pool, size_t size, size_t alignment);
void* pool_calloc(MemoryPool *pool, size_t num, size_t size);
bool pool_free(MemoryPool *pool, void *ptr);
bool pool_realloc(MemoryPool *pool, void *ptr, size_t new_size);

// Block management
MemoryBlock* find_free_block(MemoryPool *pool, size_t size);
MemoryBlock* split_block(MemoryBlock *block, size_t size);
bool merge_free_blocks(MemoryPool *pool, MemoryBlock *block);
MemoryBlock* create_block(void *data, size_t size, bool is_free);
void destroy_block(MemoryBlock *block);

// List management
void add_to_free_list(MemoryPool *pool, MemoryBlock *block);
void add_to_used_list(MemoryPool *pool, MemoryBlock *block);
void remove_from_free_list(MemoryPool *pool, MemoryBlock *block);
void remove_from_used_list(MemoryPool *pool, MemoryBlock *block);

// Analysis and statistics
PoolStats* get_pool_stats(MemoryPool *pool);
void print_pool_stats(const PoolStats *stats);
void print_pool_layout(MemoryPool *pool);
void analyze_pool_fragmentation(MemoryPool *pool);
bool validate_pool_integrity(MemoryPool *pool);

// Utility functions
size_t align_size(size_t size, size_t alignment);
void* align_pointer(void *ptr, size_t alignment);
bool is_power_of_two(size_t n);
uint64_t get_timestamp(void);
void print_memory_address(const void *ptr, const char *description);

// Debugging functions
void enable_pool_debugging(bool enable);
void print_allocation_info(const char *operation, void *ptr, size_t size, const char *file, int line);
void dump_pool_memory(MemoryPool *pool);

// Demonstration functions
void demonstrate_basic_pool_operations(void);
void demonstrate_aligned_allocation(void);
void demonstrate_fragmentation_handling(void);
void demonstrate_pool_statistics(void);

// ============================================================================
// POOL CREATION AND DESTRUCTION IMPLEMENTATION
// ============================================================================

/**
 * Create a new memory pool
 * 
 * Parameters:
 * - size: Size of the memory pool in bytes
 * - name: Name for the pool (for debugging)
 * 
 * Returns:
 * - Pointer to new MemoryPool on success
 * - NULL on failure
 */
MemoryPool* create_memory_pool(size_t size, const char *name) {
    if (size == 0) {
        printf("[ERROR] Cannot create pool with zero size\n");
        return NULL;
    }
    
    MemoryPool *pool = malloc(sizeof(MemoryPool));
    if (!pool) {
        printf("[ERROR] Memory allocation failed for memory pool structure\n");
        return NULL;
    }
    
    if (!initialize_memory_pool(pool, size, name)) {
        free(pool);
        return NULL;
    }
    
    printf("[CREATE_POOL] Created memory pool '%s' with size %zu bytes\n", name, size);
    return pool;
}

/**
 * Initialize memory pool
 * 
 * Parameters:
 * - pool: Pool to initialize
 * - size: Size of the pool
 * - name: Name for the pool
 * 
 * Returns:
 * - true on success
 * - false on failure
 */
bool initialize_memory_pool(MemoryPool *pool, size_t size, const char *name) {
    // Allocate the actual memory pool
    pool->pool_start = malloc(size);
    if (!pool->pool_start) {
        printf("[ERROR] Memory allocation failed for pool of %zu bytes\n", size);
        return false;
    }
    
    // Initialize pool parameters
    pool->pool_end = (char*)pool->pool_start + size;
    pool->pool_size = size;
    pool->used_size = 0;
    pool->free_size = size;
    pool->free_list = NULL;
    pool->used_list = NULL;
    pool->block_count = 0;
    pool->free_block_count = 0;
    pool->used_block_count = 0;
    pool->is_initialized = true;
    
    // Copy name
    strncpy(pool->name, name, MAX_POOL_NAME_LENGTH);
    pool->name[MAX_POOL_NAME_LENGTH] = '\0';
    
    // Create initial free block covering entire pool
    MemoryBlock *initial_block = create_block(pool->pool_start, size, true);
    if (!initial_block) {
        free(pool->pool_start);
        return false;
    }
    
    add_to_free_list(pool, initial_block);
    
    printf("[INITIALIZE_POOL] Initialized pool '%s' with %zu bytes\n", name, size);
    return true;
}

/**
 * Destroy memory pool and free all memory
 * 
 * Parameters:
 * - pool: Pool to destroy
 */
void destroy_memory_pool(MemoryPool *pool) {
    if (!pool) {
        printf("[ERROR] Cannot destroy NULL memory pool\n");
        return;
    }
    
    printf("[DESTROY_POOL] Destroying pool '%s'\n", pool->name);
    
    // Free all blocks
    MemoryBlock *current = pool->free_list;
    while (current) {
        MemoryBlock *next = current->next;
        destroy_block(current);
        current = next;
    }
    
    current = pool->used_list;
    while (current) {
        MemoryBlock *next = current->next;
        destroy_block(current);
        current = next;
    }
    
    // Free the pool memory
    if (pool->pool_start) {
        free(pool->pool_start);
    }
    
    free(pool);
    printf("[DESTROY_POOL] Pool destroyed successfully\n");
}

// ============================================================================
// MEMORY ALLOCATION AND DEALLOCATION IMPLEMENTATION
// ============================================================================

/**
 * Allocate memory from the pool
 * 
 * Parameters:
 * - pool: Memory pool
 * - size: Number of bytes to allocate
 * 
 * Returns:
 * - Pointer to allocated memory on success
 * - NULL on failure
 */
void* pool_alloc(MemoryPool *pool, size_t size) {
    return pool_alloc_aligned(pool, size, DEFAULT_ALIGNMENT);
}

/**
 * Allocate aligned memory from the pool
 * 
 * Parameters:
 * - pool: Memory pool
 * - size: Number of bytes to allocate
 * - alignment: Required alignment
 * 
 * Returns:
 * - Pointer to allocated memory on success
 * - NULL on failure
 */
void* pool_alloc_aligned(MemoryPool *pool, size_t size, size_t alignment) {
    if (!pool || size == 0) {
        printf("[ERROR] Invalid parameters for pool allocation\n");
        return NULL;
    }
    
    if (!pool->is_initialized) {
        printf("[ERROR] Pool '%s' is not initialized\n", pool->name);
        return NULL;
    }
    
    // Align size
    size_t aligned_size = align_size(size, alignment);
    
    // Find suitable free block
    MemoryBlock *block = find_free_block(pool, aligned_size);
    if (!block) {
        printf("[ERROR] No suitable free block found for %zu bytes in pool '%s'\n", 
               aligned_size, pool->name);
        return NULL;
    }
    
    // Split block if necessary
    if (block->size > aligned_size + MIN_BLOCK_SIZE) {
        MemoryBlock *new_block = split_block(block, aligned_size);
        if (new_block) {
            add_to_free_list(pool, new_block);
        }
    }
    
    // Remove from free list and add to used list
    remove_from_free_list(pool, block);
    block->is_free = false;
    block->magic_number = MEMORY_MAGIC_NUMBER;
    add_to_used_list(pool, block);
    
    // Update pool statistics
    pool->used_size += aligned_size;
    pool->free_size -= aligned_size;
    pool->used_block_count++;
    pool->free_block_count--;
    
    void *result = block->data;
    
    printf("[POOL_ALLOC] Allocated %zu bytes at %p in pool '%s'\n", 
           aligned_size, result, pool->name);
    
    return result;
}

/**
 * Allocate and zero-initialize memory from the pool
 * 
 * Parameters:
 * - pool: Memory pool
 * - num: Number of elements
 * - size: Size of each element
 * 
 * Returns:
 * - Pointer to allocated memory on success
 * - NULL on failure
 */
void* pool_calloc(MemoryPool *pool, size_t num, size_t size) {
    size_t total_size = num * size;
    void *ptr = pool_alloc(pool, total_size);
    
    if (ptr) {
        memset(ptr, 0, total_size);
        printf("[POOL_CALLOC] Allocated and zeroed %zu bytes at %p\n", total_size, ptr);
    }
    
    return ptr;
}

/**
 * Free memory back to the pool
 * 
 * Parameters:
 * - pool: Memory pool
 * - ptr: Pointer to free
 * 
 * Returns:
 * - true on success
 * - false on failure
 */
bool pool_free(MemoryPool *pool, void *ptr) {
    if (!pool || !ptr) {
        printf("[ERROR] Invalid parameters for pool free\n");
        return false;
    }
    
    // Find the block containing this pointer
    MemoryBlock *block = NULL;
    MemoryBlock *current = pool->used_list;
    
    while (current) {
        if (current->data == ptr) {
            block = current;
            break;
        }
        current = current->next;
    }
    
    if (!block) {
        printf("[ERROR] Pointer %p not found in pool '%s'\n", ptr, pool->name);
        return false;
    }
    
    // Validate magic number
    if (block->magic_number != MEMORY_MAGIC_NUMBER) {
        printf("[ERROR] Memory corruption detected at %p\n", ptr);
        return false;
    }
    
    // Remove from used list
    remove_from_used_list(pool, block);
    
    // Mark as free and add to free list
    block->is_free = true;
    block->magic_number = 0;
    add_to_free_list(pool, block);
    
    // Update pool statistics
    pool->used_size -= block->size;
    pool->free_size += block->size;
    pool->used_block_count--;
    pool->free_block_count++;
    
    // Try to merge with adjacent free blocks
    merge_free_blocks(pool, block);
    
    printf("[POOL_FREE] Freed %zu bytes at %p in pool '%s'\n", 
           block->size, ptr, pool->name);
    
    return true;
}

// ============================================================================
// BLOCK MANAGEMENT IMPLEMENTATION
// ============================================================================

/**
 * Find a suitable free block for allocation
 * 
 * Parameters:
 * - pool: Memory pool
 * - size: Required size
 * 
 * Returns:
 * - Pointer to suitable block
 * - NULL if no suitable block found
 */
MemoryBlock* find_free_block(MemoryPool *pool, size_t size) {
    MemoryBlock *current = pool->free_list;
    MemoryBlock *best_fit = NULL;
    size_t best_size = SIZE_MAX;
    
    // First fit strategy
    while (current) {
        if (current->size >= size) {
            if (current->size < best_size) {
                best_fit = current;
                best_size = current->size;
            }
        }
        current = current->next;
    }
    
    return best_fit;
}

/**
 * Split a block into two blocks
 * 
 * Parameters:
 * - block: Block to split
 * - size: Size for the first block
 * 
 * Returns:
 * - Pointer to the second block
 * - NULL on failure
 */
MemoryBlock* split_block(MemoryBlock *block, size_t size) {
    if (!block || block->size <= size + MIN_BLOCK_SIZE) {
        return NULL;
    }
    
    // Create new block for the remaining space
    void *new_data = (char*)block->data + size;
    size_t new_size = block->size - size;
    
    MemoryBlock *new_block = create_block(new_data, new_size, true);
    if (!new_block) {
        return NULL;
    }
    
    // Update original block size
    block->size = size;
    
    printf("[SPLIT_BLOCK] Split block: %zu bytes -> %zu + %zu bytes\n", 
           block->size + new_size, block->size, new_size);
    
    return new_block;
}

/**
 * Merge adjacent free blocks
 * 
 * Parameters:
 * - pool: Memory pool
 * - block: Block to merge
 * 
 * Returns:
 * - true if merging occurred
 * - false otherwise
 */
bool merge_free_blocks(MemoryPool *pool, MemoryBlock *block) {
    bool merged = false;
    
    // Try to merge with next block
    MemoryBlock *next_block = (MemoryBlock*)((char*)block + sizeof(MemoryBlock) + block->size);
    if ((char*)next_block < (char*)pool->pool_end && 
        next_block->is_free && next_block->magic_number == 0) {
        
        // Remove next block from free list
        remove_from_free_list(pool, next_block);
        
        // Merge blocks
        block->size += sizeof(MemoryBlock) + next_block->size;
        destroy_block(next_block);
        
        merged = true;
        printf("[MERGE_BLOCKS] Merged with next block\n");
    }
    
    // Try to merge with previous block
    // This is more complex and would require tracking previous blocks
    // For simplicity, we'll skip this for now
    
    return merged;
}

/**
 * Create a new memory block
 * 
 * Parameters:
 * - data: Pointer to data
 * - size: Size of the block
 * - is_free: Whether block is free
 * 
 * Returns:
 * - Pointer to new MemoryBlock
 * - NULL on failure
 */
MemoryBlock* create_block(void *data, size_t size, bool is_free) {
    MemoryBlock *block = malloc(sizeof(MemoryBlock));
    if (!block) {
        printf("[ERROR] Memory allocation failed for memory block\n");
        return NULL;
    }
    
    block->data = data;
    block->size = size;
    block->is_free = is_free;
    block->next = NULL;
    block->prev = NULL;
    block->magic_number = is_free ? 0 : MEMORY_MAGIC_NUMBER;
    
    return block;
}

/**
 * Destroy a memory block
 * 
 * Parameters:
 * - block: Block to destroy
 */
void destroy_block(MemoryBlock *block) {
    if (block) {
        free(block);
    }
}

// ============================================================================
// LIST MANAGEMENT IMPLEMENTATION
// ============================================================================

/**
 * Add block to free list
 * 
 * Parameters:
 * - pool: Memory pool
 * - block: Block to add
 */
void add_to_free_list(MemoryPool *pool, MemoryBlock *block) {
    if (!block) return;
    
    block->next = pool->free_list;
    block->prev = NULL;
    
    if (pool->free_list) {
        pool->free_list->prev = block;
    }
    
    pool->free_list = block;
    pool->free_block_count++;
    pool->block_count++;
}

/**
 * Add block to used list
 * 
 * Parameters:
 * - pool: Memory pool
 * - block: Block to add
 */
void add_to_used_list(MemoryPool *pool, MemoryBlock *block) {
    if (!block) return;
    
    block->next = pool->used_list;
    block->prev = NULL;
    
    if (pool->used_list) {
        pool->used_list->prev = block;
    }
    
    pool->used_list = block;
    pool->used_block_count++;
}

/**
 * Remove block from free list
 * 
 * Parameters:
 * - pool: Memory pool
 * - block: Block to remove
 */
void remove_from_free_list(MemoryPool *pool, MemoryBlock *block) {
    if (!block) return;
    
    if (block->prev) {
        block->prev->next = block->next;
    } else {
        pool->free_list = block->next;
    }
    
    if (block->next) {
        block->next->prev = block->prev;
    }
    
    pool->free_block_count--;
    pool->block_count--;
}

/**
 * Remove block from used list
 * 
 * Parameters:
 * - pool: Memory pool
 * - block: Block to remove
 */
void remove_from_used_list(MemoryPool *pool, MemoryBlock *block) {
    if (!block) return;
    
    if (block->prev) {
        block->prev->next = block->next;
    } else {
        pool->used_list = block->next;
    }
    
    if (block->next) {
        block->next->prev = block->prev;
    }
    
    pool->used_block_count--;
}

// ============================================================================
// ANALYSIS AND STATISTICS IMPLEMENTATION
// ============================================================================

/**
 * Get comprehensive pool statistics
 * 
 * Parameters:
 * - pool: Pool to analyze
 * 
 * Returns:
 * - Pointer to PoolStats structure
 */
PoolStats* get_pool_stats(MemoryPool *pool) {
    if (!pool) {
        printf("[ERROR] Cannot get stats for NULL pool\n");
        return NULL;
    }
    
    PoolStats *stats = malloc(sizeof(PoolStats));
    if (!stats) {
        printf("[ERROR] Memory allocation failed for pool stats\n");
        return NULL;
    }
    
    stats->total_size = pool->pool_size;
    stats->used_size = pool->used_size;
    stats->free_size = pool->free_size;
    stats->total_blocks = pool->block_count;
    stats->free_blocks = pool->free_block_count;
    stats->used_blocks = pool->used_block_count;
    stats->utilization = pool->pool_size > 0 ? (float)pool->used_size / pool->pool_size * 100 : 0;
    
    // Find largest and smallest free blocks
    stats->largest_free_block = 0;
    stats->smallest_free_block = SIZE_MAX;
    stats->fragmentation_count = 0;
    
    MemoryBlock *current = pool->free_list;
    while (current) {
        if (current->size > stats->largest_free_block) {
            stats->largest_free_block = current->size;
        }
        if (current->size < stats->smallest_free_block) {
            stats->smallest_free_block = current->size;
        }
        stats->fragmentation_count++;
        current = current->next;
    }
    
    if (stats->smallest_free_block == SIZE_MAX) {
        stats->smallest_free_block = 0;
    }
    
    return stats;
}

/**
 * Print pool statistics
 * 
 * Parameters:
 * - stats: Statistics to print
 */
void print_pool_stats(const PoolStats *stats) {
    if (!stats) {
        printf("[ERROR] Cannot print NULL statistics\n");
        return;
    }
    
    printf("\n=== MEMORY POOL STATISTICS ===\n");
    printf("Total size: %zu bytes (%.2f KB)\n", stats->total_size, stats->total_size / 1024.0);
    printf("Used size: %zu bytes (%.2f KB)\n", stats->used_size, stats->used_size / 1024.0);
    printf("Free size: %zu bytes (%.2f KB)\n", stats->free_size, stats->free_size / 1024.0);
    printf("Utilization: %.2f%%\n", stats->utilization);
    printf("Total blocks: %d\n", stats->total_blocks);
    printf("Free blocks: %d\n", stats->free_blocks);
    printf("Used blocks: %d\n", stats->used_blocks);
    printf("Fragmentation count: %d\n", stats->fragmentation_count);
    printf("Largest free block: %zu bytes\n", stats->largest_free_block);
    printf("Smallest free block: %zu bytes\n", stats->smallest_free_block);
}

/**
 * Print pool layout
 * 
 * Parameters:
 * - pool: Pool to print layout of
 */
void print_pool_layout(MemoryPool *pool) {
    if (!pool) {
        printf("[ERROR] Cannot print layout for NULL pool\n");
        return;
    }
    
    printf("\n=== POOL LAYOUT ===\n");
    printf("Pool '%s': %zu bytes\n", pool->name, pool->pool_size);
    printf("Start: %p, End: %p\n", pool->pool_start, pool->pool_end);
    
    printf("\nFree blocks:\n");
    MemoryBlock *current = pool->free_list;
    int block_num = 0;
    while (current) {
        printf("  Block %d: %p, size %zu bytes\n", 
               ++block_num, current->data, current->size);
        current = current->next;
    }
    
    printf("\nUsed blocks:\n");
    current = pool->used_list;
    block_num = 0;
    while (current) {
        printf("  Block %d: %p, size %zu bytes\n", 
               ++block_num, current->data, current->size);
        current = current->next;
    }
}

// ============================================================================
// UTILITY FUNCTIONS IMPLEMENTATION
// ============================================================================

/**
 * Align size to specified alignment
 * 
 * Parameters:
 * - size: Size to align
 * - alignment: Alignment requirement
 * 
 * Returns:
 * - Aligned size
 */
size_t align_size(size_t size, size_t alignment) {
    if (alignment == 0) return size;
    return (size + alignment - 1) & ~(alignment - 1);
}

/**
 * Align pointer to specified alignment
 * 
 * Parameters:
 * - ptr: Pointer to align
 * - alignment: Alignment requirement
 * 
 * Returns:
 * - Aligned pointer
 */
void* align_pointer(void *ptr, size_t alignment) {
    if (alignment == 0) return ptr;
    uintptr_t addr = (uintptr_t)ptr;
    return (void*)((addr + alignment - 1) & ~(alignment - 1));
}

/**
 * Check if number is power of two
 * 
 * Parameters:
 * - n: Number to check
 * 
 * Returns:
 * - true if power of two
 * - false otherwise
 */
bool is_power_of_two(size_t n) {
    return n > 0 && (n & (n - 1)) == 0;
}

/**
 * Get current timestamp
 * 
 * Returns:
 * - Current timestamp
 */
uint64_t get_timestamp(void) {
    return (uint64_t)time(NULL);
}

// ============================================================================
// DEMONSTRATION FUNCTIONS
// ============================================================================

/**
 * Demonstrate basic pool operations
 */
void demonstrate_basic_pool_operations(void) {
    printf("\n=== BASIC POOL OPERATIONS DEMONSTRATION ===\n");
    
    MemoryPool *pool = create_memory_pool(1024, "DemoPool");
    if (!pool) {
        printf("Failed to create memory pool\n");
        return;
    }
    
    // Allocate some memory
    void *ptr1 = pool_alloc(pool, 100);
    void *ptr2 = pool_alloc(pool, 200);
    void *ptr3 = pool_alloc(pool, 150);
    
    if (ptr1 && ptr2 && ptr3) {
        printf("Allocated memory successfully\n");
        
        // Use the memory
        memset(ptr1, 1, 100);
        memset(ptr2, 2, 200);
        memset(ptr3, 3, 150);
        
        printf("Memory initialized with test data\n");
    }
    
    // Print pool statistics
    PoolStats *stats = get_pool_stats(pool);
    if (stats) {
        print_pool_stats(stats);
        free(stats);
    }
    
    print_pool_layout(pool);
    
    // Free some memory
    if (ptr2) {
        pool_free(pool, ptr2);
        printf("Freed ptr2\n");
    }
    
    // Print updated statistics
    stats = get_pool_stats(pool);
    if (stats) {
        print_pool_stats(stats);
        free(stats);
    }
    
    destroy_memory_pool(pool);
}

/**
 * Demonstrate aligned allocation
 */
void demonstrate_aligned_allocation(void) {
    printf("\n=== ALIGNED ALLOCATION DEMONSTRATION ===\n");
    
    MemoryPool *pool = create_memory_pool(512, "AlignedPool");
    if (!pool) {
        printf("Failed to create memory pool\n");
        return;
    }
    
    // Allocate with different alignments
    void *ptr1 = pool_alloc_aligned(pool, 100, 4);
    void *ptr2 = pool_alloc_aligned(pool, 100, 8);
    void *ptr3 = pool_alloc_aligned(pool, 100, 16);
    
    if (ptr1 && ptr2 && ptr3) {
        printf("Aligned allocations:\n");
        printf("4-byte aligned: %p (address %% 4 = %lu)\n", 
               ptr1, (uintptr_t)ptr1 % 4);
        printf("8-byte aligned: %p (address %% 8 = %lu)\n", 
               ptr2, (uintptr_t)ptr2 % 8);
        printf("16-byte aligned: %p (address %% 16 = %lu)\n", 
               ptr3, (uintptr_t)ptr3 % 16);
    }
    
    destroy_memory_pool(pool);
}

/**
 * Demonstrate fragmentation handling
 */
void demonstrate_fragmentation_handling(void) {
    printf("\n=== FRAGMENTATION HANDLING DEMONSTRATION ===\n");
    
    MemoryPool *pool = create_memory_pool(1000, "FragmentationPool");
    if (!pool) {
        printf("Failed to create memory pool\n");
        return;
    }
    
    // Allocate several blocks
    void *ptrs[5];
    for (int i = 0; i < 5; i++) {
        ptrs[i] = pool_alloc(pool, 100);
    }
    
    printf("Allocated 5 blocks of 100 bytes each\n");
    
    PoolStats *stats = get_pool_stats(pool);
    if (stats) {
        print_pool_stats(stats);
        free(stats);
    }
    
    // Free every other block to create fragmentation
    for (int i = 1; i < 5; i += 2) {
        if (ptrs[i]) {
            pool_free(pool, ptrs[i]);
            ptrs[i] = NULL;
        }
    }
    
    printf("Freed blocks 1 and 3 to create fragmentation\n");
    
    stats = get_pool_stats(pool);
    if (stats) {
        print_pool_stats(stats);
        free(stats);
    }
    
    // Try to allocate a large block
    void *large_ptr = pool_alloc(pool, 300);
    if (large_ptr) {
        printf("Successfully allocated large block of 300 bytes\n");
        pool_free(pool, large_ptr);
    } else {
        printf("Failed to allocate large block due to fragmentation\n");
    }
    
    destroy_memory_pool(pool);
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main(void) {
    printf("MEMORY POOL ALLOCATOR DEMONSTRATION\n");
    printf("===================================\n");
    
    // Run demonstrations
    demonstrate_basic_pool_operations();
    demonstrate_aligned_allocation();
    demonstrate_fragmentation_handling();
    
    printf("\n=== KEY CONCEPTS COVERED ===\n");
    printf("1. Memory pool design and implementation\n");
    printf("2. Efficient memory allocation strategies\n");
    printf("3. Memory fragmentation prevention\n");
    printf("4. Pool-based memory management\n");
    printf("5. Performance optimization techniques\n");
    printf("6. Memory debugging and analysis\n");
    printf("7. Block management and merging\n");
    printf("8. Alignment and boundary handling\n");
    
    return 0;
}




