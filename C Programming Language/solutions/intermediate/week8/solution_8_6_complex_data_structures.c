/**
 * Solution 8.6: Complex Data Structures with Pointers
 * Week 8 - Advanced Arrays and Strings
 * 
 * Description: Advanced data structures combining arrays, structures, and pointers
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Complex structure definitions
struct Address {
    char street[100];
    char city[50];
    char state[20];
    int zip_code;
};

struct Person {
    int id;
    char name[50];
    int age;
    struct Address address;
    struct Person *next;      // For linked list
    struct Person **friends;  // Array of pointers to friends
    int friend_count;
};

struct Company {
    char name[100];
    struct Person *employees;  // Linked list of employees
    int employee_count;
    struct Address headquarters;
};

// Tree node structure
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Hash table structure
#define HASH_SIZE 10
struct HashEntry {
    int key;
    char value[50];
    struct HashEntry *next;
};

struct HashTable {
    struct HashEntry *buckets[HASH_SIZE];
};

// Function prototypes
struct Person* create_person(int id, const char* name, int age);
void add_friend(struct Person *person, struct Person *friend);
void print_person_details(struct Person *person);
struct TreeNode* create_tree_node(int data);
struct TreeNode* insert_tree_node(struct TreeNode *root, int data);
void inorder_traversal(struct TreeNode *root);
unsigned int hash_function(int key);
void hash_insert(struct HashTable *table, int key, const char* value);
char* hash_search(struct HashTable *table, int key);

void demonstrate_complex_structures() {
    printf("=== Complex Structure Manipulation ===\n");
    
    // Create people
    struct Person *john = create_person(1, "John Doe", 30);
    struct Person *jane = create_person(2, "Jane Smith", 28);
    struct Person *bob = create_person(3, "Bob Johnson", 32);
    
    if (!john || !jane || !bob) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    // Set addresses using structure assignment
    strcpy(john->address.street, "123 Main St");
    strcpy(john->address.city, "New York");
    strcpy(john->address.state, "NY");
    john->address.zip_code = 10001;
    
    strcpy(jane->address.street, "456 Oak Ave");
    strcpy(jane->address.city, "Los Angeles");
    strcpy(jane->address.state, "CA");
    jane->address.zip_code = 90210;
    
    // Add friendships
    add_friend(john, jane);
    add_friend(john, bob);
    add_friend(jane, bob);
    
    // Print details
    print_person_details(john);
    print_person_details(jane);
    
    // Clean up
    free(john->friends);
    free(jane->friends);
    free(bob->friends);
    free(john);
    free(jane);
    free(bob);
}

void demonstrate_linked_list_operations() {
    printf("\n=== Advanced Linked List Operations ===\n");
    
    struct Person *head = NULL;
    struct Person *current = NULL;
    
    // Create a linked list of employees
    for (int i = 1; i <= 5; i++) {
        char name[20];
        sprintf(name, "Employee%d", i);
        
        struct Person *new_person = create_person(100 + i, name, 25 + i);
        if (!new_person) continue;
        
        if (head == NULL) {
            head = new_person;
            current = head;
        } else {
            current->next = new_person;
            current = new_person;
        }
    }
    
    // Traverse and print
    printf("Employee list:\n");
    current = head;
    int position = 1;
    while (current != NULL) {
        printf("%d. ID: %d, Name: %s, Age: %d\n", 
               position++, current->id, current->name, current->age);
        current = current->next;
    }
    
    // Find employee by ID using pointer traversal
    int search_id = 103;
    current = head;
    while (current != NULL && current->id != search_id) {
        current = current->next;
    }
    
    if (current != NULL) {
        printf("Found employee: %s (ID: %d)\n", current->name, current->id);
    }
    
    // Delete the list
    while (head != NULL) {
        struct Person *temp = head;
        head = head->next;
        free(temp);
    }
}

void demonstrate_binary_tree() {
    printf("\n=== Binary Tree Operations ===\n");
    
    struct TreeNode *root = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(values) / sizeof(values[0]);
    
    // Insert nodes
    printf("Inserting values: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
        root = insert_tree_node(root, values[i]);
    }
    printf("\n");
    
    // Traverse tree
    printf("Inorder traversal: ");
    inorder_traversal(root);
    printf("\n");
    
    // Tree structure visualization (simplified)
    printf("\nTree structure (conceptual):\n");
    printf("       50\n");
    printf("      /  \\\n");
    printf("    30    70\n");
    printf("   / \\   / \\\n");
    printf("  20 40 60 80\n");
}

void demonstrate_hash_table() {
    printf("\n=== Hash Table Implementation ===\n");
    
    struct HashTable table = {0};  // Initialize all buckets to NULL
    
    // Insert key-value pairs
    hash_insert(&table, 1, "Apple");
    hash_insert(&table, 11, "Banana");  // Will collide with key 1
    hash_insert(&table, 2, "Cherry");
    hash_insert(&table, 12, "Date");    // Will collide with key 2
    hash_insert(&table, 3, "Elderberry");
    
    // Search for values
    printf("Hash table contents:\n");
    for (int i = 1; i <= 15; i++) {
        char *value = hash_search(&table, i);
        if (value) {
            printf("Key %d: %s\n", i, value);
        }
    }
    
    // Show hash distribution
    printf("\nHash table bucket distribution:\n");
    for (int i = 0; i < HASH_SIZE; i++) {
        printf("Bucket %d: ", i);
        struct HashEntry *entry = table.buckets[i];
        while (entry) {
            printf("[%d:%s] ", entry->key, entry->value);
            entry = entry->next;
        }
        printf("\n");
    }
    
    // Clean up hash table
    for (int i = 0; i < HASH_SIZE; i++) {
        struct HashEntry *entry = table.buckets[i];
        while (entry) {
            struct HashEntry *temp = entry;
            entry = entry->next;
            free(temp);
        }
    }
}

void demonstrate_array_of_pointers() {
    printf("\n=== Array of Pointers to Structures ===\n");
    
    // Create array of pointers to Person structures
    struct Person *people[5];
    char names[][20] = {"Alice", "Bob", "Charlie", "Diana", "Eve"};
    
    // Initialize array with people
    for (int i = 0; i < 5; i++) {
        people[i] = create_person(i + 1, names[i], 20 + i * 2);
        if (!people[i]) {
            printf("Memory allocation failed for person %d\n", i);
            continue;
        }
    }
    
    // Sort array by age using pointer manipulation
    printf("Before sorting by age:\n");
    for (int i = 0; i < 5; i++) {
        if (people[i]) {
            printf("%s: %d years old\n", people[i]->name, people[i]->age);
        }
    }
    
    // Simple bubble sort on pointers
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4 - i; j++) {
            if (people[j] && people[j + 1] && 
                people[j]->age > people[j + 1]->age) {
                // Swap pointers
                struct Person *temp = people[j];
                people[j] = people[j + 1];
                people[j + 1] = temp;
            }
        }
    }
    
    printf("\nAfter sorting by age:\n");
    for (int i = 0; i < 5; i++) {
        if (people[i]) {
            printf("%s: %d years old\n", people[i]->name, people[i]->age);
        }
    }
    
    // Clean up
    for (int i = 0; i < 5; i++) {
        if (people[i]) {
            free(people[i]);
        }
    }
}

void demonstrate_pointer_arithmetic_with_structures() {
    printf("\n=== Pointer Arithmetic with Structures ===\n");
    
    // Create array of structures
    struct Person people[3];
    
    // Initialize using pointer arithmetic
    struct Person *p = people;
    for (int i = 0; i < 3; i++) {
        p->id = i + 1;
        sprintf(p->name, "Person%d", i + 1);
        p->age = 25 + i * 5;
        p->next = NULL;
        p->friends = NULL;
        p->friend_count = 0;
        p++;  // Move to next structure
    }
    
    // Access using different pointer techniques
    printf("Accessing structures with different methods:\n");
    
    // Method 1: Array indexing
    for (int i = 0; i < 3; i++) {
        printf("people[%d]: %s, age %d\n", i, people[i].name, people[i].age);
    }
    
    // Method 2: Pointer arithmetic
    printf("\nUsing pointer arithmetic:\n");
    p = people;
    for (int i = 0; i < 3; i++) {
        printf("*(people + %d): %s, age %d\n", i, (p + i)->name, (p + i)->age);
    }
    
    // Method 3: Pointer increment
    printf("\nUsing pointer increment:\n");
    p = people;
    for (int i = 0; i < 3; i++) {
        printf("p[%d]: %s, age %d\n", i, p->name, p->age);
        p++;
    }
}

// Function implementations
struct Person* create_person(int id, const char* name, int age) {
    struct Person *person = (struct Person*)malloc(sizeof(struct Person));
    if (!person) return NULL;
    
    person->id = id;
    strncpy(person->name, name, sizeof(person->name) - 1);
    person->name[sizeof(person->name) - 1] = '\0';
    person->age = age;
    person->next = NULL;
    person->friends = NULL;
    person->friend_count = 0;
    
    // Initialize address to empty
    memset(&person->address, 0, sizeof(struct Address));
    
    return person;
}

void add_friend(struct Person *person, struct Person *friend) {
    if (!person || !friend) return;
    
    // Reallocate friends array
    person->friends = (struct Person**)realloc(person->friends, 
        (person->friend_count + 1) * sizeof(struct Person*));
    
    if (person->friends) {
        person->friends[person->friend_count] = friend;
        person->friend_count++;
    }
}

void print_person_details(struct Person *person) {
    if (!person) return;
    
    printf("\n--- Person Details ---\n");
    printf("ID: %d\n", person->id);
    printf("Name: %s\n", person->name);
    printf("Age: %d\n", person->age);
    printf("Address: %s, %s, %s %d\n", 
           person->address.street, person->address.city, 
           person->address.state, person->address.zip_code);
    
    printf("Friends (%d): ", person->friend_count);
    for (int i = 0; i < person->friend_count; i++) {
        printf("%s", person->friends[i]->name);
        if (i < person->friend_count - 1) printf(", ");
    }
    printf("\n");
}

struct TreeNode* create_tree_node(int data) {
    struct TreeNode *node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (node) {
        node->data = data;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

struct TreeNode* insert_tree_node(struct TreeNode *root, int data) {
    if (root == NULL) {
        return create_tree_node(data);
    }
    
    if (data < root->data) {
        root->left = insert_tree_node(root->left, data);
    } else if (data > root->data) {
        root->right = insert_tree_node(root->right, data);
    }
    
    return root;
}

void inorder_traversal(struct TreeNode *root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->data);
        inorder_traversal(root->right);
    }
}

unsigned int hash_function(int key) {
    return key % HASH_SIZE;
}

void hash_insert(struct HashTable *table, int key, const char* value) {
    unsigned int index = hash_function(key);
    
    struct HashEntry *entry = (struct HashEntry*)malloc(sizeof(struct HashEntry));
    if (!entry) return;
    
    entry->key = key;
    strncpy(entry->value, value, sizeof(entry->value) - 1);
    entry->value[sizeof(entry->value) - 1] = '\0';
    
    // Insert at beginning of chain (collision handling)
    entry->next = table->buckets[index];
    table->buckets[index] = entry;
}

char* hash_search(struct HashTable *table, int key) {
    unsigned int index = hash_function(key);
    struct HashEntry *entry = table->buckets[index];
    
    while (entry) {
        if (entry->key == key) {
            return entry->value;
        }
        entry = entry->next;
    }
    
    return NULL;
}

int main() {
    printf("COMPLEX DATA STRUCTURES WITH POINTERS AND STRUCTURES\n");
    printf("===================================================\n\n");
    
    demonstrate_complex_structures();
    demonstrate_linked_list_operations();
    demonstrate_binary_tree();
    demonstrate_hash_table();
    demonstrate_array_of_pointers();
    demonstrate_pointer_arithmetic_with_structures();
    
    printf("\nAdvanced Concepts Demonstrated:\n");
    printf("- Complex nested structures\n");
    printf("- Linked list operations with pointers\n");
    printf("- Binary tree implementation\n");
    printf("- Hash table with collision handling\n");
    printf("- Array of pointers to structures\n");
    printf("- Pointer arithmetic with structures\n");
    printf("- Dynamic memory management\n");
    printf("- Structure member access (. vs ->)\n");
    
    return 0;
}
