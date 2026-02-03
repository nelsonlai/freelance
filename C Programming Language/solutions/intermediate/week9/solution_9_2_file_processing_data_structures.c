/**
 * Solution 9.2: File Processing and Data Structures
 * Week 9 - Advanced File Operations and Data Management
 * 
 * Description: Comprehensive file processing with advanced data structures
 * including linked lists, binary trees, and hash tables for data organization.
 * 
 * Learning Objectives:
 * - File I/O operations (reading, writing, parsing)
 * - Dynamic data structures implementation
 * - Data parsing and validation
 * - Memory management for file data
 * - Error handling in file operations
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// ============================================================================
// DATA STRUCTURES FOR FILE PROCESSING
// ============================================================================

/**
 * Structure to represent a student record
 * Contains all necessary information for a student
 */
typedef struct Student {
    int id;                     // Student ID (unique identifier)
    char name[50];              // Student name
    char email[100];            // Student email
    float gpa;                  // Grade Point Average
    int age;                    // Student age
    struct Student *next;       // Pointer to next student (for linked list)
} Student;

/**
 * Structure for a binary tree node containing student data
 * Used for efficient searching and sorting
 */
typedef struct TreeNode {
    Student *student;           // Pointer to student data
    struct TreeNode *left;      // Left child (smaller ID)
    struct TreeNode *right;     // Right child (larger ID)
    int height;                 // Height for AVL balancing
} TreeNode;

/**
 * Structure for hash table entry
 * Used for O(1) average case lookup
 */
typedef struct HashEntry {
    Student *student;           // Pointer to student data
    struct HashEntry *next;     // Pointer for collision handling
} HashEntry;

/**
 * Structure for hash table
 * Contains array of hash entries and metadata
 */
typedef struct HashTable {
    HashEntry **table;          // Array of hash entry pointers
    int size;                   // Size of the hash table
    int count;                  // Number of entries in the table
} HashTable;

/**
 * Structure for file statistics
 * Tracks processing information
 */
typedef struct FileStats {
    int total_records;          // Total records processed
    int valid_records;          // Valid records found
    int invalid_records;        // Invalid records found
    int duplicate_records;      // Duplicate records found
    float processing_time;      // Time taken to process file
} FileStats;

// ============================================================================
// FUNCTION PROTOTYPES
// ============================================================================

// Student management functions
Student* create_student(int id, const char *name, const char *email, float gpa, int age);
void free_student(Student *student);
void print_student(const Student *student);

// Linked list operations
Student* add_student_to_list(Student *head, Student *new_student);
Student* find_student_by_id(Student *head, int id);
Student* remove_student_from_list(Student *head, int id);
void print_student_list(Student *head);
int count_students(Student *head);
void free_student_list(Student *head);

// Binary tree operations
TreeNode* create_tree_node(Student *student);
TreeNode* insert_student_to_tree(TreeNode *root, Student *student);
TreeNode* find_student_in_tree(TreeNode *root, int id);
TreeNode* delete_student_from_tree(TreeNode *root, int id);
void print_tree_inorder(TreeNode *root);
void print_tree_preorder(TreeNode *root);
void print_tree_postorder(TreeNode *root);
int tree_height(TreeNode *root);
TreeNode* balance_tree(TreeNode *root);
TreeNode* rotate_left(TreeNode *root);
TreeNode* rotate_right(TreeNode *root);
void free_tree(TreeNode *root);

// Hash table operations
HashTable* create_hash_table(int size);
int hash_function(int id, int table_size);
bool insert_student_to_hash(HashTable *ht, Student *student);
Student* find_student_in_hash(HashTable *ht, int id);
bool delete_student_from_hash(HashTable *ht, int id);
void print_hash_table(HashTable *ht);
void free_hash_table(HashTable *ht);

// File processing functions
bool parse_student_line(const char *line, Student **student);
bool validate_student_data(const Student *student);
FileStats* process_student_file(const char *filename, Student **list_head, 
                               TreeNode **tree_root, HashTable **hash_table);
bool save_students_to_file(const char *filename, Student *head);
void print_file_stats(const FileStats *stats);

// Utility functions
void trim_whitespace(char *str);
bool is_valid_email(const char *email);
bool is_valid_gpa(float gpa);
void clear_input_buffer(void);

// ============================================================================
// STUDENT MANAGEMENT IMPLEMENTATION
// ============================================================================

/**
 * Create a new student record
 * 
 * Parameters:
 * - id: Student ID
 * - name: Student name
 * - email: Student email
 * - gpa: Grade Point Average
 * - age: Student age
 * 
 * Returns:
 * - Pointer to new Student structure on success
 * - NULL on failure
 */
Student* create_student(int id, const char *name, const char *email, float gpa, int age) {
    // Validate input parameters
    if (id <= 0 || !name || !email || gpa < 0.0 || gpa > 4.0 || age < 0) {
        printf("[ERROR] Invalid student data\n");
        return NULL;
    }
    
    // Allocate memory for new student
    Student *student = malloc(sizeof(Student));
    if (!student) {
        printf("[ERROR] Memory allocation failed for student\n");
        return NULL;
    }
    
    // Initialize student data
    student->id = id;
    strncpy(student->name, name, sizeof(student->name) - 1);
    student->name[sizeof(student->name) - 1] = '\0';
    
    strncpy(student->email, email, sizeof(student->email) - 1);
    student->email[sizeof(student->email) - 1] = '\0';
    
    student->gpa = gpa;
    student->age = age;
    student->next = NULL;
    
    printf("[CREATE_STUDENT] Created student: ID=%d, Name=%s\n", id, name);
    return student;
}

/**
 * Free memory allocated for a student
 * 
 * Parameters:
 * - student: Pointer to student to free
 */
void free_student(Student *student) {
    if (student) {
        printf("[FREE_STUDENT] Freeing student: ID=%d, Name=%s\n", 
               student->id, student->name);
        free(student);
    }
}

/**
 * Print student information
 * 
 * Parameters:
 * - student: Pointer to student to print
 */
void print_student(const Student *student) {
    if (!student) {
        printf("[ERROR] Cannot print NULL student\n");
        return;
    }
    
    printf("Student ID: %d\n", student->id);
    printf("Name: %s\n", student->name);
    printf("Email: %s\n", student->email);
    printf("GPA: %.2f\n", student->gpa);
    printf("Age: %d\n", student->age);
    printf("---\n");
}

// ============================================================================
// LINKED LIST IMPLEMENTATION
// ============================================================================

/**
 * Add a student to the linked list
 * 
 * Parameters:
 * - head: Pointer to head of the list
 * - new_student: Student to add
 * 
 * Returns:
 * - Pointer to new head of the list
 */
Student* add_student_to_list(Student *head, Student *new_student) {
    if (!new_student) {
        printf("[ERROR] Cannot add NULL student to list\n");
        return head;
    }
    
    // Check for duplicate ID
    if (find_student_by_id(head, new_student->id)) {
        printf("[WARNING] Student with ID %d already exists in list\n", 
               new_student->id);
        return head;
    }
    
    // Add to beginning of list (simple insertion)
    new_student->next = head;
    printf("[ADD_TO_LIST] Added student %d to list\n", new_student->id);
    return new_student;
}

/**
 * Find a student by ID in the linked list
 * 
 * Parameters:
 * - head: Pointer to head of the list
 * - id: Student ID to search for
 * 
 * Returns:
 * - Pointer to student if found
 * - NULL if not found
 */
Student* find_student_by_id(Student *head, int id) {
    Student *current = head;
    
    while (current) {
        if (current->id == id) {
            printf("[FIND_IN_LIST] Found student %d\n", id);
            return current;
        }
        current = current->next;
    }
    
    printf("[FIND_IN_LIST] Student %d not found in list\n", id);
    return NULL;
}

/**
 * Remove a student from the linked list
 * 
 * Parameters:
 * - head: Pointer to head of the list
 * - id: Student ID to remove
 * 
 * Returns:
 * - Pointer to new head of the list
 */
Student* remove_student_from_list(Student *head, int id) {
    if (!head) {
        printf("[ERROR] Cannot remove from empty list\n");
        return NULL;
    }
    
    // Special case: removing the head
    if (head->id == id) {
        Student *new_head = head->next;
        printf("[REMOVE_FROM_LIST] Removed student %d from head\n", id);
        free_student(head);
        return new_head;
    }
    
    // Find the student to remove
    Student *current = head;
    while (current->next && current->next->id != id) {
        current = current->next;
    }
    
    if (current->next) {
        Student *to_remove = current->next;
        current->next = to_remove->next;
        printf("[REMOVE_FROM_LIST] Removed student %d\n", id);
        free_student(to_remove);
    } else {
        printf("[REMOVE_FROM_LIST] Student %d not found\n", id);
    }
    
    return head;
}

/**
 * Print all students in the linked list
 * 
 * Parameters:
 * - head: Pointer to head of the list
 */
void print_student_list(Student *head) {
    if (!head) {
        printf("Student list is empty\n");
        return;
    }
    
    printf("\n=== STUDENT LIST ===\n");
    Student *current = head;
    int count = 0;
    
    while (current) {
        printf("Student %d:\n", ++count);
        print_student(current);
        current = current->next;
    }
}

/**
 * Count the number of students in the list
 * 
 * Parameters:
 * - head: Pointer to head of the list
 * 
 * Returns:
 * - Number of students in the list
 */
int count_students(Student *head) {
    int count = 0;
    Student *current = head;
    
    while (current) {
        count++;
        current = current->next;
    }
    
    return count;
}

/**
 * Free all memory used by the student list
 * 
 * Parameters:
 * - head: Pointer to head of the list
 */
void free_student_list(Student *head) {
    Student *current = head;
    
    while (current) {
        Student *next = current->next;
        free_student(current);
        current = next;
    }
    
    printf("[FREE_LIST] Freed entire student list\n");
}

// ============================================================================
// BINARY TREE IMPLEMENTATION (AVL Tree)
// ============================================================================

/**
 * Create a new tree node
 * 
 * Parameters:
 * - student: Student data for the node
 * 
 * Returns:
 * - Pointer to new TreeNode on success
 * - NULL on failure
 */
TreeNode* create_tree_node(Student *student) {
    if (!student) {
        printf("[ERROR] Cannot create tree node with NULL student\n");
        return NULL;
    }
    
    TreeNode *node = malloc(sizeof(TreeNode));
    if (!node) {
        printf("[ERROR] Memory allocation failed for tree node\n");
        return NULL;
    }
    
    node->student = student;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    
    printf("[CREATE_TREE_NODE] Created tree node for student %d\n", student->id);
    return node;
}

/**
 * Get the height of a tree node
 * 
 * Parameters:
 * - node: Tree node to get height of
 * 
 * Returns:
 * - Height of the node (0 for NULL)
 */
int tree_height(TreeNode *node) {
    return node ? node->height : 0;
}

/**
 * Get the maximum of two integers
 * 
 * Parameters:
 * - a: First integer
 * - b: Second integer
 * 
 * Returns:
 * - Maximum of a and b
 */
int max(int a, int b) {
    return (a > b) ? a : b;
}

/**
 * Update the height of a tree node
 * 
 * Parameters:
 * - node: Tree node to update
 */
void update_height(TreeNode *node) {
    if (node) {
        node->height = 1 + max(tree_height(node->left), tree_height(node->right));
    }
}

/**
 * Perform left rotation on tree
 * 
 * Parameters:
 * - root: Root of subtree to rotate
 * 
 * Returns:
 * - New root after rotation
 */
TreeNode* rotate_left(TreeNode *root) {
    TreeNode *new_root = root->right;
    TreeNode *subtree = new_root->left;
    
    // Perform rotation
    new_root->left = root;
    root->right = subtree;
    
    // Update heights
    update_height(root);
    update_height(new_root);
    
    printf("[ROTATE_LEFT] Performed left rotation\n");
    return new_root;
}

/**
 * Perform right rotation on tree
 * 
 * Parameters:
 * - root: Root of subtree to rotate
 * 
 * Returns:
 * - New root after rotation
 */
TreeNode* rotate_right(TreeNode *root) {
    TreeNode *new_root = root->left;
    TreeNode *subtree = new_root->right;
    
    // Perform rotation
    new_root->right = root;
    root->left = subtree;
    
    // Update heights
    update_height(root);
    update_height(new_root);
    
    printf("[ROTATE_RIGHT] Performed right rotation\n");
    return new_root;
}

/**
 * Get the balance factor of a tree node
 * 
 * Parameters:
 * - node: Tree node to get balance factor of
 * 
 * Returns:
 * - Balance factor (height difference)
 */
int get_balance(TreeNode *node) {
    return node ? tree_height(node->left) - tree_height(node->right) : 0;
}

/**
 * Balance the tree using AVL rotations
 * 
 * Parameters:
 * - root: Root of tree to balance
 * 
 * Returns:
 * - Balanced tree root
 */
TreeNode* balance_tree(TreeNode *root) {
    if (!root) return NULL;
    
    // Update height
    update_height(root);
    
    // Get balance factor
    int balance = get_balance(root);
    
    // Left Left Case
    if (balance > 1 && get_balance(root->left) >= 0) {
        return rotate_right(root);
    }
    
    // Right Right Case
    if (balance < -1 && get_balance(root->right) <= 0) {
        return rotate_left(root);
    }
    
    // Left Right Case
    if (balance > 1 && get_balance(root->left) < 0) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }
    
    // Right Left Case
    if (balance < -1 && get_balance(root->right) > 0) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }
    
    return root;
}

/**
 * Insert a student into the binary tree
 * 
 * Parameters:
 * - root: Root of the tree
 * - student: Student to insert
 * 
 * Returns:
 * - New root of the tree
 */
TreeNode* insert_student_to_tree(TreeNode *root, Student *student) {
    if (!student) {
        printf("[ERROR] Cannot insert NULL student into tree\n");
        return root;
    }
    
    // Base case: create new node
    if (!root) {
        return create_tree_node(student);
    }
    
    // Recursive insertion
    if (student->id < root->student->id) {
        root->left = insert_student_to_tree(root->left, student);
    } else if (student->id > root->student->id) {
        root->right = insert_student_to_tree(root->right, student);
    } else {
        printf("[WARNING] Student with ID %d already exists in tree\n", 
               student->id);
        return root;
    }
    
    // Balance the tree
    return balance_tree(root);
}

/**
 * Find a student in the binary tree
 * 
 * Parameters:
 * - root: Root of the tree
 * - id: Student ID to search for
 * 
 * Returns:
 * - Pointer to TreeNode containing the student
 * - NULL if not found
 */
TreeNode* find_student_in_tree(TreeNode *root, int id) {
    if (!root) {
        return NULL;
    }
    
    if (id < root->student->id) {
        return find_student_in_tree(root->left, id);
    } else if (id > root->student->id) {
        return find_student_in_tree(root->right, id);
    } else {
        printf("[FIND_IN_TREE] Found student %d\n", id);
        return root;
    }
}

/**
 * Print tree in inorder traversal (sorted by ID)
 * 
 * Parameters:
 * - root: Root of the tree
 */
void print_tree_inorder(TreeNode *root) {
    if (root) {
        print_tree_inorder(root->left);
        print_student(root->student);
        print_tree_inorder(root->right);
    }
}

/**
 * Free all memory used by the tree
 * 
 * Parameters:
 * - root: Root of the tree
 */
void free_tree(TreeNode *root) {
    if (root) {
        free_tree(root->left);
        free_tree(root->right);
        free_student(root->student);
        free(root);
    }
}

// ============================================================================
// HASH TABLE IMPLEMENTATION
// ============================================================================

/**
 * Create a new hash table
 * 
 * Parameters:
 * - size: Size of the hash table
 * 
 * Returns:
 * - Pointer to new HashTable on success
 * - NULL on failure
 */
HashTable* create_hash_table(int size) {
    if (size <= 0) {
        printf("[ERROR] Invalid hash table size: %d\n", size);
        return NULL;
    }
    
    HashTable *ht = malloc(sizeof(HashTable));
    if (!ht) {
        printf("[ERROR] Memory allocation failed for hash table\n");
        return NULL;
    }
    
    ht->table = calloc(size, sizeof(HashEntry*));
    if (!ht->table) {
        printf("[ERROR] Memory allocation failed for hash table array\n");
        free(ht);
        return NULL;
    }
    
    ht->size = size;
    ht->count = 0;
    
    printf("[CREATE_HASH_TABLE] Created hash table with size %d\n", size);
    return ht;
}

/**
 * Hash function for student IDs
 * 
 * Parameters:
 * - id: Student ID to hash
 * - table_size: Size of the hash table
 * 
 * Returns:
 * - Hash value (index in table)
 */
int hash_function(int id, int table_size) {
    return id % table_size;
}

/**
 * Insert a student into the hash table
 * 
 * Parameters:
 * - ht: Hash table
 * - student: Student to insert
 * 
 * Returns:
 * - true on success
 * - false on failure
 */
bool insert_student_to_hash(HashTable *ht, Student *student) {
    if (!ht || !student) {
        printf("[ERROR] Invalid parameters for hash insert\n");
        return false;
    }
    
    // Check if student already exists
    if (find_student_in_hash(ht, student->id)) {
        printf("[WARNING] Student with ID %d already exists in hash table\n", 
               student->id);
        return false;
    }
    
    // Calculate hash index
    int index = hash_function(student->id, ht->size);
    
    // Create new hash entry
    HashEntry *entry = malloc(sizeof(HashEntry));
    if (!entry) {
        printf("[ERROR] Memory allocation failed for hash entry\n");
        return false;
    }
    
    entry->student = student;
    entry->next = ht->table[index];
    ht->table[index] = entry;
    ht->count++;
    
    printf("[INSERT_TO_HASH] Inserted student %d at index %d\n", 
           student->id, index);
    return true;
}

/**
 * Find a student in the hash table
 * 
 * Parameters:
 * - ht: Hash table
 * - id: Student ID to search for
 * 
 * Returns:
 * - Pointer to student if found
 * - NULL if not found
 */
Student* find_student_in_hash(HashTable *ht, int id) {
    if (!ht) {
        printf("[ERROR] Hash table is NULL\n");
        return NULL;
    }
    
    int index = hash_function(id, ht->size);
    HashEntry *entry = ht->table[index];
    
    while (entry) {
        if (entry->student->id == id) {
            printf("[FIND_IN_HASH] Found student %d at index %d\n", id, index);
            return entry->student;
        }
        entry = entry->next;
    }
    
    printf("[FIND_IN_HASH] Student %d not found in hash table\n", id);
    return NULL;
}

/**
 * Print all entries in the hash table
 * 
 * Parameters:
 * - ht: Hash table to print
 */
void print_hash_table(HashTable *ht) {
    if (!ht) {
        printf("[ERROR] Cannot print NULL hash table\n");
        return;
    }
    
    printf("\n=== HASH TABLE ===\n");
    for (int i = 0; i < ht->size; i++) {
        HashEntry *entry = ht->table[i];
        if (entry) {
            printf("Index %d:\n", i);
            while (entry) {
                print_student(entry->student);
                entry = entry->next;
            }
        }
    }
}

/**
 * Free all memory used by the hash table
 * 
 * Parameters:
 * - ht: Hash table to free
 */
void free_hash_table(HashTable *ht) {
    if (!ht) return;
    
    for (int i = 0; i < ht->size; i++) {
        HashEntry *entry = ht->table[i];
        while (entry) {
            HashEntry *next = entry->next;
            free_student(entry->student);
            free(entry);
            entry = next;
        }
    }
    
    free(ht->table);
    free(ht);
    printf("[FREE_HASH_TABLE] Freed hash table\n");
}

// ============================================================================
// FILE PROCESSING IMPLEMENTATION
// ============================================================================

/**
 * Parse a line from the student file
 * 
 * Parameters:
 * - line: Line to parse
 * - student: Pointer to store parsed student
 * 
 * Returns:
 * - true on successful parsing
 * - false on parsing error
 */
bool parse_student_line(const char *line, Student **student) {
    if (!line || !student) {
        printf("[ERROR] Invalid parameters for parsing\n");
        return false;
    }
    
    // Expected format: ID,Name,Email,GPA,Age
    int id, age;
    char name[50], email[100];
    float gpa;
    
    int parsed = sscanf(line, "%d,%49[^,],%99[^,],%f,%d", 
                        &id, name, email, &gpa, &age);
    
    if (parsed != 5) {
        printf("[ERROR] Failed to parse line: %s\n", line);
        return false;
    }
    
    // Trim whitespace from name and email
    trim_whitespace(name);
    trim_whitespace(email);
    
    // Create student
    *student = create_student(id, name, email, gpa, age);
    return (*student != NULL);
}

/**
 * Validate student data
 * 
 * Parameters:
 * - student: Student to validate
 * 
 * Returns:
 * - true if data is valid
 * - false if data is invalid
 */
bool validate_student_data(const Student *student) {
    if (!student) {
        printf("[ERROR] Cannot validate NULL student\n");
        return false;
    }
    
    // Validate ID
    if (student->id <= 0) {
        printf("[VALIDATION] Invalid student ID: %d\n", student->id);
        return false;
    }
    
    // Validate name
    if (strlen(student->name) == 0) {
        printf("[VALIDATION] Empty student name\n");
        return false;
    }
    
    // Validate email
    if (!is_valid_email(student->email)) {
        printf("[VALIDATION] Invalid email: %s\n", student->email);
        return false;
    }
    
    // Validate GPA
    if (!is_valid_gpa(student->gpa)) {
        printf("[VALIDATION] Invalid GPA: %.2f\n", student->gpa);
        return false;
    }
    
    // Validate age
    if (student->age < 0 || student->age > 150) {
        printf("[VALIDATION] Invalid age: %d\n", student->age);
        return false;
    }
    
    return true;
}

/**
 * Process a student file and populate data structures
 * 
 * Parameters:
 * - filename: Name of the file to process
 * - list_head: Pointer to store linked list head
 * - tree_root: Pointer to store tree root
 * - hash_table: Pointer to store hash table
 * 
 * Returns:
 * - Pointer to FileStats structure
 */
FileStats* process_student_file(const char *filename, Student **list_head, 
                               TreeNode **tree_root, HashTable **hash_table) {
    if (!filename || !list_head || !tree_root || !hash_table) {
        printf("[ERROR] Invalid parameters for file processing\n");
        return NULL;
    }
    
    // Initialize data structures
    *list_head = NULL;
    *tree_root = NULL;
    *hash_table = create_hash_table(100);  // Hash table of size 100
    
    if (!*hash_table) {
        printf("[ERROR] Failed to create hash table\n");
        return NULL;
    }
    
    // Initialize file statistics
    FileStats *stats = malloc(sizeof(FileStats));
    if (!stats) {
        printf("[ERROR] Memory allocation failed for file stats\n");
        return NULL;
    }
    
    stats->total_records = 0;
    stats->valid_records = 0;
    stats->invalid_records = 0;
    stats->duplicate_records = 0;
    stats->processing_time = 0.0;
    
    // Open file
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("[ERROR] Cannot open file: %s\n", filename);
        free(stats);
        return NULL;
    }
    
    printf("[FILE_PROCESSING] Processing file: %s\n", filename);
    
    char line[256];
    int line_number = 0;
    
    // Process each line
    while (fgets(line, sizeof(line), file)) {
        line_number++;
        stats->total_records++;
        
        // Remove newline character
        line[strcspn(line, "\n")] = '\0';
        
        // Skip empty lines
        if (strlen(line) == 0) {
            continue;
        }
        
        // Parse student data
        Student *student = NULL;
        if (!parse_student_line(line, &student)) {
            stats->invalid_records++;
            printf("[FILE_PROCESSING] Invalid data on line %d\n", line_number);
            continue;
        }
        
        // Validate student data
        if (!validate_student_data(student)) {
            stats->invalid_records++;
            free_student(student);
            continue;
        }
        
        // Check for duplicates
        if (find_student_by_id(*list_head, student->id)) {
            stats->duplicate_records++;
            free_student(student);
            continue;
        }
        
        // Add to data structures
        *list_head = add_student_to_list(*list_head, student);
        *tree_root = insert_student_to_tree(*tree_root, student);
        insert_student_to_hash(*hash_table, student);
        
        stats->valid_records++;
    }
    
    fclose(file);
    
    printf("[FILE_PROCESSING] File processing complete\n");
    printf("Total records: %d\n", stats->total_records);
    printf("Valid records: %d\n", stats->valid_records);
    printf("Invalid records: %d\n", stats->invalid_records);
    printf("Duplicate records: %d\n", stats->duplicate_records);
    
    return stats;
}

/**
 * Save students to a file
 * 
 * Parameters:
 * - filename: Name of the file to save to
 * - head: Head of the student list
 * 
 * Returns:
 * - true on success
 * - false on failure
 */
bool save_students_to_file(const char *filename, Student *head) {
    if (!filename || !head) {
        printf("[ERROR] Invalid parameters for saving file\n");
        return false;
    }
    
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("[ERROR] Cannot create file: %s\n", filename);
        return false;
    }
    
    printf("[SAVE_FILE] Saving students to: %s\n", filename);
    
    Student *current = head;
    while (current) {
        fprintf(file, "%d,%s,%s,%.2f,%d\n", 
                current->id, current->name, current->email, 
                current->gpa, current->age);
        current = current->next;
    }
    
    fclose(file);
    printf("[SAVE_FILE] File saved successfully\n");
    return true;
}

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

/**
 * Trim whitespace from string
 * 
 * Parameters:
 * - str: String to trim
 */
void trim_whitespace(char *str) {
    if (!str) return;
    
    // Trim leading whitespace
    char *start = str;
    while (isspace(*start)) start++;
    
    // Trim trailing whitespace
    char *end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) end--;
    
    // Move trimmed string to beginning
    memmove(str, start, end - start + 1);
    str[end - start + 1] = '\0';
}

/**
 * Validate email format
 * 
 * Parameters:
 * - email: Email to validate
 * 
 * Returns:
 * - true if email is valid
 * - false if email is invalid
 */
bool is_valid_email(const char *email) {
    if (!email || strlen(email) == 0) {
        return false;
    }
    
    // Simple email validation
    bool has_at = false;
    bool has_dot = false;
    
    for (int i = 0; email[i]; i++) {
        if (email[i] == '@') {
            has_at = true;
        } else if (email[i] == '.' && has_at) {
            has_dot = true;
        }
    }
    
    return has_at && has_dot;
}

/**
 * Validate GPA range
 * 
 * Parameters:
 * - gpa: GPA to validate
 * 
 * Returns:
 * - true if GPA is valid
 * - false if GPA is invalid
 */
bool is_valid_gpa(float gpa) {
    return gpa >= 0.0 && gpa <= 4.0;
}

/**
 * Print file processing statistics
 * 
 * Parameters:
 * - stats: Statistics to print
 */
void print_file_stats(const FileStats *stats) {
    if (!stats) {
        printf("[ERROR] Cannot print NULL statistics\n");
        return;
    }
    
    printf("\n=== FILE PROCESSING STATISTICS ===\n");
    printf("Total records processed: %d\n", stats->total_records);
    printf("Valid records: %d\n", stats->valid_records);
    printf("Invalid records: %d\n", stats->invalid_records);
    printf("Duplicate records: %d\n", stats->duplicate_records);
    printf("Success rate: %.2f%%\n", 
           stats->total_records > 0 ? 
           (float)stats->valid_records / stats->total_records * 100 : 0);
}

// ============================================================================
// DEMONSTRATION FUNCTIONS
// ============================================================================

/**
 * Demonstrate data structure operations
 */
void demonstrate_data_structures(void) {
    printf("\n=== DATA STRUCTURE DEMONSTRATIONS ===\n");
    
    // Create sample students
    Student *s1 = create_student(1, "Alice Johnson", "alice@email.com", 3.8, 20);
    Student *s2 = create_student(2, "Bob Smith", "bob@email.com", 3.2, 21);
    Student *s3 = create_student(3, "Charlie Brown", "charlie@email.com", 3.9, 19);
    
    if (s1 && s2 && s3) {
        // Demonstrate linked list
        printf("\n--- Linked List Operations ---\n");
        Student *list_head = NULL;
        list_head = add_student_to_list(list_head, s1);
        list_head = add_student_to_list(list_head, s2);
        list_head = add_student_to_list(list_head, s3);
        
        printf("Student count: %d\n", count_students(list_head));
        print_student_list(list_head);
        
        // Demonstrate binary tree
        printf("\n--- Binary Tree Operations ---\n");
        TreeNode *tree_root = NULL;
        tree_root = insert_student_to_tree(tree_root, s1);
        tree_root = insert_student_to_tree(tree_root, s2);
        tree_root = insert_student_to_tree(tree_root, s3);
        
        printf("Tree traversal (inorder):\n");
        print_tree_inorder(tree_root);
        
        // Demonstrate hash table
        printf("\n--- Hash Table Operations ---\n");
        HashTable *ht = create_hash_table(10);
        insert_student_to_hash(ht, s1);
        insert_student_to_hash(ht, s2);
        insert_student_to_hash(ht, s3);
        
        print_hash_table(ht);
        
        // Clean up
        free_student_list(list_head);
        free_tree(tree_root);
        free_hash_table(ht);
    }
}

/**
 * Create a sample student file for testing
 */
void create_sample_file(void) {
    printf("\n=== CREATING SAMPLE FILE ===\n");
    
    FILE *file = fopen("students_sample.txt", "w");
    if (!file) {
        printf("[ERROR] Cannot create sample file\n");
        return;
    }
    
    // Write sample student data
    fprintf(file, "1,Alice Johnson,alice@email.com,3.8,20\n");
    fprintf(file, "2,Bob Smith,bob@email.com,3.2,21\n");
    fprintf(file, "3,Charlie Brown,charlie@email.com,3.9,19\n");
    fprintf(file, "4,Diana Prince,diana@email.com,3.7,22\n");
    fprintf(file, "5,Eve Wilson,eve@email.com,3.5,20\n");
    
    fclose(file);
    printf("[SAMPLE_FILE] Created students_sample.txt\n");
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main(void) {
    printf("FILE PROCESSING AND DATA STRUCTURES DEMONSTRATION\n");
    printf("==================================================\n");
    
    // Create sample file for testing
    create_sample_file();
    
    // Demonstrate data structures
    demonstrate_data_structures();
    
    // Process the sample file
    printf("\n=== FILE PROCESSING DEMONSTRATION ===\n");
    
    Student *list_head = NULL;
    TreeNode *tree_root = NULL;
    HashTable *hash_table = NULL;
    
    FileStats *stats = process_student_file("students_sample.txt", 
                                          &list_head, &tree_root, &hash_table);
    
    if (stats) {
        print_file_stats(stats);
        
        // Demonstrate searching in different data structures
        printf("\n--- Searching Demonstrations ---\n");
        
        Student *found_list = find_student_by_id(list_head, 3);
        TreeNode *found_tree = find_student_in_tree(tree_root, 3);
        Student *found_hash = find_student_in_hash(hash_table, 3);
        
        if (found_list && found_tree && found_hash) {
            printf("Student found in all data structures:\n");
            print_student(found_list);
        }
        
        // Save processed data to new file
        save_students_to_file("students_processed.txt", list_head);
        
        // Clean up
        free_student_list(list_head);
        free_tree(tree_root);
        free_hash_table(hash_table);
        free(stats);
    }
    
    printf("\n=== KEY CONCEPTS COVERED ===\n");
    printf("1. File I/O operations (reading, writing, parsing)\n");
    printf("2. Dynamic data structures (linked lists, binary trees, hash tables)\n");
    printf("3. Data validation and error handling\n");
    printf("4. Memory management for complex data structures\n");
    printf("5. Algorithm implementation (AVL tree balancing)\n");
    printf("6. Hash table collision handling\n");
    printf("7. File processing and data organization\n");
    printf("8. Comprehensive error handling and validation\n");
    
    return 0;
}




