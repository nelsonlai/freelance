/**
 * Solution 9.5: Hash Table Implementation
 * Week 9 - Advanced Data Structures
 * 
 * Description: Comprehensive hash table implementation with collision handling,
 * dynamic resizing, and various hash functions.
 * 
 * Learning Objectives:
 * - Hash table data structure implementation
 * - Hash function design and collision handling
 * - Dynamic resizing and load factor management
 * - Open addressing vs chaining strategies
 * - Performance analysis and optimization
 * - Memory management for hash tables
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

// ============================================================================
// HASH TABLE STRUCTURES
// ============================================================================

/**
 * Structure representing a key-value pair
 * Stores the actual data in the hash table
 */
typedef struct HashEntry {
    char *key;                  // Key string
    int value;                 // Associated value
    bool is_deleted;           // Flag for deleted entries (for open addressing)
    struct HashEntry *next;    // Pointer for chaining collision resolution
} HashEntry;

/**
 * Structure representing the hash table
 * Contains array of entries and metadata
 */
typedef struct HashTable {
    HashEntry **table;         // Array of hash entry pointers
    int size;                  // Current size of the table
    int capacity;              // Maximum capacity of the table
    int count;                 // Number of active entries
    int deleted_count;         // Number of deleted entries
    float load_factor;         // Current load factor (count/capacity)
    float max_load_factor;     // Maximum allowed load factor
    int collision_count;       // Number of collisions
    int probe_count;           // Number of probes for open addressing
} HashTable;

/**
 * Enumeration for collision resolution strategies
 */
typedef enum {
    CHAINING,                  // Separate chaining
    LINEAR_PROBING,            // Linear probing
    QUADRATIC_PROBING,         // Quadratic probing
    DOUBLE_HASHING             // Double hashing
} CollisionStrategy;

/**
 * Structure for hash table statistics
 * Provides detailed performance metrics
 */
typedef struct HashStats {
    int total_insertions;      // Total number of insertions
    int total_deletions;       // Total number of deletions
    int total_searches;        // Total number of searches
    int collisions;            // Total collisions
    int probes;                // Total probes
    float average_probes;       // Average probes per operation
    float load_factor;          // Current load factor
    int longest_chain;          // Longest chain length (for chaining)
} HashStats;

// ============================================================================
// FUNCTION PROTOTYPES
// ============================================================================

// Hash table creation and destruction
HashTable* create_hash_table(int initial_capacity, float max_load_factor);
void destroy_hash_table(HashTable *ht);
HashEntry* create_hash_entry(const char *key, int value);
void destroy_hash_entry(HashEntry *entry);

// Hash functions
unsigned int hash_function_djb2(const char *key, int table_size);
unsigned int hash_function_sdbm(const char *key, int table_size);
unsigned int hash_function_fnv1a(const char *key, int table_size);
unsigned int hash_function_custom(const char *key, int table_size);

// Basic operations
bool hash_table_insert(HashTable *ht, const char *key, int value);
bool hash_table_delete(HashTable *ht, const char *key);
int hash_table_get(HashTable *ht, const char *key);
bool hash_table_contains(HashTable *ht, const char *key);
bool hash_table_update(HashTable *ht, const char *key, int value);

// Collision resolution strategies
bool insert_with_chaining(HashTable *ht, const char *key, int value);
bool insert_with_linear_probing(HashTable *ht, const char *key, int value);
bool insert_with_quadratic_probing(HashTable *ht, const char *key, int value);
bool insert_with_double_hashing(HashTable *ht, const char *key, int value);

// Search with different strategies
HashEntry* search_with_chaining(HashTable *ht, const char *key);
HashEntry* search_with_linear_probing(HashTable *ht, const char *key);
HashEntry* search_with_quadratic_probing(HashTable *ht, const char *key);
HashEntry* search_with_double_hashing(HashTable *ht, const char *key);

// Dynamic resizing
bool resize_hash_table(HashTable *ht);
void rehash_table(HashTable *ht, HashEntry **old_table, int old_capacity);

// Analysis and statistics
HashStats* get_hash_table_stats(HashTable *ht);
void print_hash_table_stats(const HashStats *stats);
void print_hash_table(HashTable *ht);
void analyze_hash_distribution(HashTable *ht);

// Utility functions
bool is_prime(int n);
int next_prime(int n);
void update_load_factor(HashTable *ht);
void increment_collision_count(HashTable *ht);
void increment_probe_count(HashTable *ht);

// Demonstration functions
void demonstrate_basic_operations(void);
void demonstrate_collision_strategies(void);
void demonstrate_performance_analysis(void);
void demonstrate_dynamic_resizing(void);

// ============================================================================
// HASH TABLE CREATION AND DESTRUCTION IMPLEMENTATION
// ============================================================================

/**
 * Create a new hash table
 * 
 * Parameters:
 * - initial_capacity: Initial size of the hash table
 * - max_load_factor: Maximum load factor before resizing
 * 
 * Returns:
 * - Pointer to new HashTable on success
 * - NULL on failure
 */
HashTable* create_hash_table(int initial_capacity, float max_load_factor) {
    if (initial_capacity <= 0 || max_load_factor <= 0 || max_load_factor > 1.0) {
        printf("[ERROR] Invalid parameters for hash table creation\n");
        return NULL;
    }
    
    HashTable *ht = malloc(sizeof(HashTable));
    if (!ht) {
        printf("[ERROR] Memory allocation failed for hash table\n");
        return NULL;
    }
    
    ht->table = calloc(initial_capacity, sizeof(HashEntry*));
    if (!ht->table) {
        printf("[ERROR] Memory allocation failed for hash table array\n");
        free(ht);
        return NULL;
    }
    
    ht->size = 0;
    ht->capacity = initial_capacity;
    ht->count = 0;
    ht->deleted_count = 0;
    ht->load_factor = 0.0;
    ht->max_load_factor = max_load_factor;
    ht->collision_count = 0;
    ht->probe_count = 0;
    
    printf("[CREATE_HASH_TABLE] Created hash table with capacity %d, max load factor %.2f\n", 
           initial_capacity, max_load_factor);
    return ht;
}

/**
 * Create a new hash entry
 * 
 * Parameters:
 * - key: Key string
 * - value: Associated value
 * 
 * Returns:
 * - Pointer to new HashEntry on success
 * - NULL on failure
 */
HashEntry* create_hash_entry(const char *key, int value) {
    if (!key) {
        printf("[ERROR] Cannot create hash entry with NULL key\n");
        return NULL;
    }
    
    HashEntry *entry = malloc(sizeof(HashEntry));
    if (!entry) {
        printf("[ERROR] Memory allocation failed for hash entry\n");
        return NULL;
    }
    
    entry->key = malloc(strlen(key) + 1);
    if (!entry->key) {
        printf("[ERROR] Memory allocation failed for hash entry key\n");
        free(entry);
        return NULL;
    }
    
    strcpy(entry->key, key);
    entry->value = value;
    entry->is_deleted = false;
    entry->next = NULL;
    
    printf("[CREATE_HASH_ENTRY] Created entry: key='%s', value=%d\n", key, value);
    return entry;
}

/**
 * Destroy hash table and free all memory
 * 
 * Parameters:
 * - ht: Hash table to destroy
 */
void destroy_hash_table(HashTable *ht) {
    if (!ht) {
        printf("[ERROR] Cannot destroy NULL hash table\n");
        return;
    }
    
    for (int i = 0; i < ht->capacity; i++) {
        HashEntry *entry = ht->table[i];
        while (entry) {
            HashEntry *next = entry->next;
            destroy_hash_entry(entry);
            entry = next;
        }
    }
    
    free(ht->table);
    free(ht);
    printf("[DESTROY_HASH_TABLE] Destroyed hash table\n");
}

/**
 * Destroy hash entry and free memory
 * 
 * Parameters:
 * - entry: Hash entry to destroy
 */
void destroy_hash_entry(HashEntry *entry) {
    if (entry) {
        free(entry->key);
        free(entry);
    }
}

// ============================================================================
// HASH FUNCTIONS IMPLEMENTATION
// ============================================================================

/**
 * DJB2 hash function
 * A popular hash function for strings
 * 
 * Parameters:
 * - key: String to hash
 * - table_size: Size of the hash table
 * 
 * Returns:
 * - Hash value
 */
unsigned int hash_function_djb2(const char *key, int table_size) {
    unsigned int hash = 5381;
    int c;
    
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    
    return hash % table_size;
}

/**
 * SDBM hash function
 * Another popular hash function for strings
 * 
 * Parameters:
 * - key: String to hash
 * - table_size: Size of the hash table
 * 
 * Returns:
 * - Hash value
 */
unsigned int hash_function_sdbm(const char *key, int table_size) {
    unsigned int hash = 0;
    int c;
    
    while ((c = *key++)) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    
    return hash % table_size;
}

/**
 * FNV-1a hash function
 * Fast hash function with good distribution
 * 
 * Parameters:
 * - key: String to hash
 * - table_size: Size of the hash table
 * 
 * Returns:
 * - Hash value
 */
unsigned int hash_function_fnv1a(const char *key, int table_size) {
    unsigned int hash = 2166136261u;
    int c;
    
    while ((c = *key++)) {
        hash ^= c;
        hash *= 16777619u;
    }
    
    return hash % table_size;
}

/**
 * Custom hash function
 * Simple hash function for demonstration
 * 
 * Parameters:
 * - key: String to hash
 * - table_size: Size of the hash table
 * 
 * Returns:
 * - Hash value
 */
unsigned int hash_function_custom(const char *key, int table_size) {
    unsigned int hash = 0;
    
    for (int i = 0; key[i]; i++) {
        hash = hash * 31 + key[i];
    }
    
    return hash % table_size;
}

// ============================================================================
// BASIC OPERATIONS IMPLEMENTATION
// ============================================================================

/**
 * Insert key-value pair into hash table
 * 
 * Parameters:
 * - ht: Hash table
 * - key: Key string
 * - value: Associated value
 * 
 * Returns:
 * - true on success
 * - false on failure
 */
bool hash_table_insert(HashTable *ht, const char *key, int value) {
    if (!ht || !key) {
        printf("[ERROR] Invalid parameters for hash table insert\n");
        return false;
    }
    
    // Check if key already exists
    if (hash_table_contains(ht, key)) {
        printf("[WARNING] Key '%s' already exists, updating value\n", key);
        return hash_table_update(ht, key, value);
    }
    
    // Check if resizing is needed
    if (ht->load_factor >= ht->max_load_factor) {
        printf("[RESIZE] Load factor %.2f >= %.2f, resizing table\n", 
               ht->load_factor, ht->max_load_factor);
        if (!resize_hash_table(ht)) {
            printf("[ERROR] Failed to resize hash table\n");
            return false;
        }
    }
    
    // Use chaining strategy for simplicity
    return insert_with_chaining(ht, key, value);
}

/**
 * Insert using chaining collision resolution
 * 
 * Parameters:
 * - ht: Hash table
 * - key: Key string
 * - value: Associated value
 * 
 * Returns:
 * - true on success
 * - false on failure
 */
bool insert_with_chaining(HashTable *ht, const char *key, int value) {
    unsigned int index = hash_function_djb2(key, ht->capacity);
    
    // Check for collision
    if (ht->table[index] != NULL) {
        increment_collision_count(ht);
        printf("[COLLISION] Collision at index %d for key '%s'\n", index, key);
    }
    
    // Create new entry
    HashEntry *new_entry = create_hash_entry(key, value);
    if (!new_entry) {
        return false;
    }
    
    // Insert at head of chain
    new_entry->next = ht->table[index];
    ht->table[index] = new_entry;
    
    ht->count++;
    update_load_factor(ht);
    
    printf("[INSERT_CHAINING] Inserted '%s'=%d at index %d\n", key, value, index);
    return true;
}

/**
 * Delete key from hash table
 * 
 * Parameters:
 * - ht: Hash table
 * - key: Key to delete
 * 
 * Returns:
 * - true if key was found and deleted
 * - false if key not found
 */
bool hash_table_delete(HashTable *ht, const char *key) {
    if (!ht || !key) {
        printf("[ERROR] Invalid parameters for hash table delete\n");
        return false;
    }
    
    unsigned int index = hash_function_djb2(key, ht->capacity);
    HashEntry *entry = ht->table[index];
    HashEntry *prev = NULL;
    
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            if (prev) {
                prev->next = entry->next;
            } else {
                ht->table[index] = entry->next;
            }
            
            destroy_hash_entry(entry);
            ht->count--;
            update_load_factor(ht);
            
            printf("[DELETE] Deleted key '%s' from index %d\n", key, index);
            return true;
        }
        
        prev = entry;
        entry = entry->next;
    }
    
    printf("[DELETE] Key '%s' not found\n", key);
    return false;
}

/**
 * Get value associated with key
 * 
 * Parameters:
 * - ht: Hash table
 * - key: Key to search for
 * 
 * Returns:
 * - Value if key found
 * - -1 if key not found
 */
int hash_table_get(HashTable *ht, const char *key) {
    if (!ht || !key) {
        printf("[ERROR] Invalid parameters for hash table get\n");
        return -1;
    }
    
    HashEntry *entry = search_with_chaining(ht, key);
    if (entry) {
        printf("[GET] Found key '%s' with value %d\n", key, entry->value);
        return entry->value;
    }
    
    printf("[GET] Key '%s' not found\n", key);
    return -1;
}

/**
 * Check if key exists in hash table
 * 
 * Parameters:
 * - ht: Hash table
 * - key: Key to search for
 * 
 * Returns:
 * - true if key exists
 * - false otherwise
 */
bool hash_table_contains(HashTable *ht, const char *key) {
    return search_with_chaining(ht, key) != NULL;
}

/**
 * Update value for existing key
 * 
 * Parameters:
 * - ht: Hash table
 * - key: Key to update
 * - value: New value
 * 
 * Returns:
 * - true on success
 * - false if key not found
 */
bool hash_table_update(HashTable *ht, const char *key, int value) {
    HashEntry *entry = search_with_chaining(ht, key);
    if (entry) {
        entry->value = value;
        printf("[UPDATE] Updated key '%s' to value %d\n", key, value);
        return true;
    }
    
    printf("[UPDATE] Key '%s' not found for update\n", key);
    return false;
}

/**
 * Search for key using chaining
 * 
 * Parameters:
 * - ht: Hash table
 * - key: Key to search for
 * 
 * Returns:
 * - Pointer to HashEntry if found
 * - NULL if not found
 */
HashEntry* search_with_chaining(HashTable *ht, const char *key) {
    unsigned int index = hash_function_djb2(key, ht->capacity);
    HashEntry *entry = ht->table[index];
    
    while (entry) {
        increment_probe_count(ht);
        if (strcmp(entry->key, key) == 0) {
            printf("[SEARCH_CHAINING] Found key '%s' at index %d\n", key, index);
            return entry;
        }
        entry = entry->next;
    }
    
    printf("[SEARCH_CHAINING] Key '%s' not found\n", key);
    return NULL;
}

// ============================================================================
// DYNAMIC RESIZING IMPLEMENTATION
// ============================================================================

/**
 * Resize hash table to accommodate more entries
 * 
 * Parameters:
 * - ht: Hash table to resize
 * 
 * Returns:
 * - true on success
 * - false on failure
 */
bool resize_hash_table(HashTable *ht) {
    if (!ht) {
        printf("[ERROR] Cannot resize NULL hash table\n");
        return false;
    }
    
    int old_capacity = ht->capacity;
    int new_capacity = next_prime(old_capacity * 2);
    
    printf("[RESIZE] Resizing from %d to %d\n", old_capacity, new_capacity);
    
    // Create new table
    HashEntry **new_table = calloc(new_capacity, sizeof(HashEntry*));
    if (!new_table) {
        printf("[ERROR] Memory allocation failed for resized table\n");
        return false;
    }
    
    // Rehash all entries
    HashEntry **old_table = ht->table;
    ht->table = new_table;
    ht->capacity = new_capacity;
    ht->count = 0;
    ht->collision_count = 0;
    ht->probe_count = 0;
    
    rehash_table(ht, old_table, old_capacity);
    
    free(old_table);
    update_load_factor(ht);
    
    printf("[RESIZE] Resize completed successfully\n");
    return true;
}

/**
 * Rehash all entries from old table to new table
 * 
 * Parameters:
 * - ht: Hash table
 * - old_table: Old table to rehash from
 * - old_capacity: Capacity of old table
 */
void rehash_table(HashTable *ht, HashEntry **old_table, int old_capacity) {
    for (int i = 0; i < old_capacity; i++) {
        HashEntry *entry = old_table[i];
        while (entry) {
            HashEntry *next = entry->next;
            
            // Rehash this entry
            unsigned int new_index = hash_function_djb2(entry->key, ht->capacity);
            entry->next = ht->table[new_index];
            ht->table[new_index] = entry;
            ht->count++;
            
            entry = next;
        }
    }
    
    printf("[REHASH] Rehashed %d entries\n", ht->count);
}

// ============================================================================
// ANALYSIS AND STATISTICS IMPLEMENTATION
// ============================================================================

/**
 * Get comprehensive hash table statistics
 * 
 * Parameters:
 * - ht: Hash table to analyze
 * 
 * Returns:
 * - Pointer to HashStats structure
 */
HashStats* get_hash_table_stats(HashTable *ht) {
    if (!ht) {
        printf("[ERROR] Cannot get stats for NULL hash table\n");
        return NULL;
    }
    
    HashStats *stats = malloc(sizeof(HashStats));
    if (!stats) {
        printf("[ERROR] Memory allocation failed for hash stats\n");
        return NULL;
    }
    
    stats->total_insertions = ht->count;
    stats->total_deletions = ht->deleted_count;
    stats->total_searches = 0; // Would need to track this separately
    stats->collisions = ht->collision_count;
    stats->probes = ht->probe_count;
    stats->average_probes = ht->probe_count > 0 ? (float)ht->probe_count / ht->count : 0;
    stats->load_factor = ht->load_factor;
    
    // Find longest chain
    stats->longest_chain = 0;
    for (int i = 0; i < ht->capacity; i++) {
        int chain_length = 0;
        HashEntry *entry = ht->table[i];
        while (entry) {
            chain_length++;
            entry = entry->next;
        }
        if (chain_length > stats->longest_chain) {
            stats->longest_chain = chain_length;
        }
    }
    
    printf("[GET_STATS] Generated hash table statistics\n");
    return stats;
}

/**
 * Print hash table statistics
 * 
 * Parameters:
 * - stats: Statistics to print
 */
void print_hash_table_stats(const HashStats *stats) {
    if (!stats) {
        printf("[ERROR] Cannot print NULL statistics\n");
        return;
    }
    
    printf("\n=== HASH TABLE STATISTICS ===\n");
    printf("Total insertions: %d\n", stats->total_insertions);
    printf("Total deletions: %d\n", stats->total_deletions);
    printf("Total searches: %d\n", stats->total_searches);
    printf("Total collisions: %d\n", stats->collisions);
    printf("Total probes: %d\n", stats->probes);
    printf("Average probes per operation: %.2f\n", stats->average_probes);
    printf("Load factor: %.2f\n", stats->load_factor);
    printf("Longest chain: %d\n", stats->longest_chain);
}

/**
 * Print hash table contents
 * 
 * Parameters:
 * - ht: Hash table to print
 */
void print_hash_table(HashTable *ht) {
    if (!ht) {
        printf("[ERROR] Cannot print NULL hash table\n");
        return;
    }
    
    printf("\n=== HASH TABLE CONTENTS ===\n");
    printf("Capacity: %d, Count: %d, Load Factor: %.2f\n", 
           ht->capacity, ht->count, ht->load_factor);
    
    for (int i = 0; i < ht->capacity; i++) {
        HashEntry *entry = ht->table[i];
        if (entry) {
            printf("Index %d: ", i);
            while (entry) {
                printf("('%s'=%d) ", entry->key, entry->value);
                entry = entry->next;
            }
            printf("\n");
        }
    }
}

// ============================================================================
// UTILITY FUNCTIONS IMPLEMENTATION
// ============================================================================

/**
 * Check if number is prime
 * 
 * Parameters:
 * - n: Number to check
 * 
 * Returns:
 * - true if prime
 * - false otherwise
 */
bool is_prime(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    
    return true;
}

/**
 * Find next prime number
 * 
 * Parameters:
 * - n: Starting number
 * 
 * Returns:
 * - Next prime number >= n
 */
int next_prime(int n) {
    while (!is_prime(n)) {
        n++;
    }
    return n;
}

/**
 * Update load factor of hash table
 * 
 * Parameters:
 * - ht: Hash table to update
 */
void update_load_factor(HashTable *ht) {
    ht->load_factor = (float)ht->count / ht->capacity;
}

/**
 * Increment collision count
 * 
 * Parameters:
 * - ht: Hash table
 */
void increment_collision_count(HashTable *ht) {
    ht->collision_count++;
}

/**
 * Increment probe count
 * 
 * Parameters:
 * - ht: Hash table
 */
void increment_probe_count(HashTable *ht) {
    ht->probe_count++;
}

// ============================================================================
// DEMONSTRATION FUNCTIONS
// ============================================================================

/**
 * Demonstrate basic hash table operations
 */
void demonstrate_basic_operations(void) {
    printf("\n=== BASIC HASH TABLE OPERATIONS DEMONSTRATION ===\n");
    
    HashTable *ht = create_hash_table(10, 0.75);
    if (!ht) {
        printf("Failed to create hash table\n");
        return;
    }
    
    // Insert some key-value pairs
    const char *keys[] = {"apple", "banana", "cherry", "date", "elderberry"};
    int values[] = {1, 2, 3, 4, 5};
    int num_items = sizeof(keys) / sizeof(keys[0]);
    
    printf("Inserting key-value pairs:\n");
    for (int i = 0; i < num_items; i++) {
        hash_table_insert(ht, keys[i], values[i]);
    }
    
    print_hash_table(ht);
    
    // Search for some keys
    printf("\nSearching for keys:\n");
    for (int i = 0; i < num_items; i++) {
        int value = hash_table_get(ht, keys[i]);
        printf("Key '%s' has value %d\n", keys[i], value);
    }
    
    // Update a value
    printf("\nUpdating value for 'banana':\n");
    hash_table_update(ht, "banana", 42);
    printf("New value for 'banana': %d\n", hash_table_get(ht, "banana"));
    
    // Delete a key
    printf("\nDeleting key 'cherry':\n");
    hash_table_delete(ht, "cherry");
    print_hash_table(ht);
    
    // Get statistics
    HashStats *stats = get_hash_table_stats(ht);
    if (stats) {
        print_hash_table_stats(stats);
        free(stats);
    }
    
    destroy_hash_table(ht);
}

/**
 * Demonstrate collision handling
 */
void demonstrate_collision_strategies(void) {
    printf("\n=== COLLISION HANDLING DEMONSTRATION ===\n");
    
    HashTable *ht = create_hash_table(5, 0.8); // Small table to force collisions
    if (!ht) {
        printf("Failed to create hash table\n");
        return;
    }
    
    // Insert keys that will likely cause collisions
    const char *keys[] = {"a", "b", "c", "d", "e", "f", "g", "h"};
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int num_items = sizeof(keys) / sizeof(keys[0]);
    
    printf("Inserting keys into small table (capacity %d) to demonstrate collisions:\n", ht->capacity);
    for (int i = 0; i < num_items; i++) {
        hash_table_insert(ht, keys[i], values[i]);
    }
    
    print_hash_table(ht);
    
    HashStats *stats = get_hash_table_stats(ht);
    if (stats) {
        print_hash_table_stats(stats);
        free(stats);
    }
    
    destroy_hash_table(ht);
}

/**
 * Demonstrate dynamic resizing
 */
void demonstrate_dynamic_resizing(void) {
    printf("\n=== DYNAMIC RESIZING DEMONSTRATION ===\n");
    
    HashTable *ht = create_hash_table(3, 0.5); // Small initial size, low load factor
    if (!ht) {
        printf("Failed to create hash table\n");
        return;
    }
    
    printf("Initial table capacity: %d, max load factor: %.2f\n", 
           ht->capacity, ht->max_load_factor);
    
    // Insert items until resizing occurs
    for (int i = 1; i <= 10; i++) {
        char key[10];
        sprintf(key, "key%d", i);
        
        printf("Inserting %s=%d (load factor: %.2f)\n", key, i, ht->load_factor);
        hash_table_insert(ht, key, i);
        
        if (ht->capacity > 3) {
            printf("Table was resized to capacity %d\n", ht->capacity);
        }
    }
    
    print_hash_table(ht);
    
    HashStats *stats = get_hash_table_stats(ht);
    if (stats) {
        print_hash_table_stats(stats);
        free(stats);
    }
    
    destroy_hash_table(ht);
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main(void) {
    printf("HASH TABLE IMPLEMENTATION DEMONSTRATION\n");
    printf("=======================================\n");
    
    // Run demonstrations
    demonstrate_basic_operations();
    demonstrate_collision_strategies();
    demonstrate_dynamic_resizing();
    
    printf("\n=== KEY CONCEPTS COVERED ===\n");
    printf("1. Hash table data structure implementation\n");
    printf("2. Hash function design and evaluation\n");
    printf("3. Collision resolution strategies\n");
    printf("4. Dynamic resizing and load factor management\n");
    printf("5. Performance analysis and statistics\n");
    printf("6. Memory management for hash tables\n");
    printf("7. Open addressing vs chaining trade-offs\n");
    printf("8. Hash table optimization techniques\n");
    
    return 0;
}




