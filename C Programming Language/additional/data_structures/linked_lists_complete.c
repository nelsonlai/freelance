/**
 * Complete Linked Lists Implementation
 * Comprehensive demonstration of various linked list types and operations
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Node structures for different list types
struct SinglyNode {
    int data;
    struct SinglyNode *next;
};

struct DoublyNode {
    int data;
    struct DoublyNode *prev;
    struct DoublyNode *next;
};

struct CircularNode {
    int data;
    struct CircularNode *next;
};

// List structures
struct SinglyLinkedList {
    struct SinglyNode *head;
    struct SinglyNode *tail;
    int size;
};

struct DoublyLinkedList {
    struct DoublyNode *head;
    struct DoublyNode *tail;
    int size;
};

// Function prototypes for singly linked list
struct SinglyLinkedList* create_singly_list();
void singly_insert_front(struct SinglyLinkedList *list, int data);
void singly_insert_back(struct SinglyLinkedList *list, int data);
void singly_insert_at(struct SinglyLinkedList *list, int index, int data);
bool singly_delete_front(struct SinglyLinkedList *list);
bool singly_delete_back(struct SinglyLinkedList *list);
bool singly_delete_at(struct SinglyLinkedList *list, int index);
bool singly_delete_value(struct SinglyLinkedList *list, int value);
int singly_find(struct SinglyLinkedList *list, int value);
void singly_print(struct SinglyLinkedList *list);
void singly_reverse(struct SinglyLinkedList *list);
void singly_sort(struct SinglyLinkedList *list);
void singly_free(struct SinglyLinkedList *list);

// Function prototypes for doubly linked list
struct DoublyLinkedList* create_doubly_list();
void doubly_insert_front(struct DoublyLinkedList *list, int data);
void doubly_insert_back(struct DoublyLinkedList *list, int data);
void doubly_insert_at(struct DoublyLinkedList *list, int index, int data);
bool doubly_delete_front(struct DoublyLinkedList *list);
bool doubly_delete_back(struct DoublyLinkedList *list);
bool doubly_delete_at(struct DoublyLinkedList *list, int index);
void doubly_print_forward(struct DoublyLinkedList *list);
void doubly_print_backward(struct DoublyLinkedList *list);
void doubly_free(struct DoublyLinkedList *list);

// Function prototypes for circular linked list
struct CircularNode* circular_create_node(int data);
struct CircularNode* circular_insert_front(struct CircularNode *last, int data);
struct CircularNode* circular_insert_back(struct CircularNode *last, int data);
struct CircularNode* circular_delete_node(struct CircularNode *last, int value);
void circular_print(struct CircularNode *last);
void circular_free(struct CircularNode *last);

void demonstrate_singly_linked_list() {
    printf("=== Singly Linked List ===\n");
    
    struct SinglyLinkedList *list = create_singly_list();
    
    // Insert operations
    printf("Inserting elements: 10, 20, 30, 40, 50\n");
    singly_insert_back(list, 10);
    singly_insert_back(list, 20);
    singly_insert_back(list, 30);
    singly_insert_back(list, 40);
    singly_insert_back(list, 50);
    
    printf("List: ");
    singly_print(list);
    printf("Size: %d\n", list->size);
    
    // Insert at specific positions
    printf("\nInserting 5 at front and 25 at index 3\n");
    singly_insert_front(list, 5);
    singly_insert_at(list, 3, 25);
    
    printf("List: ");
    singly_print(list);
    
    // Search operations
    int search_value = 25;
    int index = singly_find(list, search_value);
    printf("Found %d at index: %d\n", search_value, index);
    
    // Delete operations
    printf("\nDeleting front and back elements\n");
    singly_delete_front(list);
    singly_delete_back(list);
    
    printf("List: ");
    singly_print(list);
    
    printf("Deleting value 25\n");
    singly_delete_value(list, 25);
    printf("List: ");
    singly_print(list);
    
    // Reverse the list
    printf("\nReversing the list\n");
    singly_reverse(list);
    printf("Reversed list: ");
    singly_print(list);
    
    // Sort the list
    printf("Sorting the list\n");
    singly_sort(list);
    printf("Sorted list: ");
    singly_print(list);
    
    singly_free(list);
}

void demonstrate_doubly_linked_list() {
    printf("\n=== Doubly Linked List ===\n");
    
    struct DoublyLinkedList *list = create_doubly_list();
    
    // Insert operations
    printf("Inserting elements: 100, 200, 300, 400\n");
    doubly_insert_back(list, 100);
    doubly_insert_back(list, 200);
    doubly_insert_back(list, 300);
    doubly_insert_back(list, 400);
    
    printf("Forward: ");
    doubly_print_forward(list);
    printf("Backward: ");
    doubly_print_backward(list);
    
    // Insert at front and specific position
    printf("\nInserting 50 at front and 250 at index 3\n");
    doubly_insert_front(list, 50);
    doubly_insert_at(list, 3, 250);
    
    printf("Forward: ");
    doubly_print_forward(list);
    printf("Backward: ");
    doubly_print_backward(list);
    
    // Delete operations
    printf("\nDeleting front and back elements\n");
    doubly_delete_front(list);
    doubly_delete_back(list);
    
    printf("Forward: ");
    doubly_print_forward(list);
    
    doubly_free(list);
}

void demonstrate_circular_linked_list() {
    printf("\n=== Circular Linked List ===\n");
    
    struct CircularNode *last = NULL;
    
    // Insert operations
    printf("Inserting elements: 1, 2, 3, 4, 5\n");
    last = circular_insert_back(last, 1);
    last = circular_insert_back(last, 2);
    last = circular_insert_back(last, 3);
    last = circular_insert_back(last, 4);
    last = circular_insert_back(last, 5);
    
    printf("Circular list: ");
    circular_print(last);
    
    // Insert at front
    printf("Inserting 0 at front\n");
    last = circular_insert_front(last, 0);
    printf("Circular list: ");
    circular_print(last);
    
    // Delete operations
    printf("Deleting node with value 3\n");
    last = circular_delete_node(last, 3);
    printf("Circular list: ");
    circular_print(last);
    
    circular_free(last);
}

void demonstrate_advanced_operations() {
    printf("\n=== Advanced List Operations ===\n");
    
    struct SinglyLinkedList *list1 = create_singly_list();
    struct SinglyLinkedList *list2 = create_singly_list();
    
    // Create two sorted lists
    int arr1[] = {1, 3, 5, 7, 9};
    int arr2[] = {2, 4, 6, 8, 10};
    
    for (int i = 0; i < 5; i++) {
        singly_insert_back(list1, arr1[i]);
        singly_insert_back(list2, arr2[i]);
    }
    
    printf("List 1: ");
    singly_print(list1);
    printf("List 2: ");
    singly_print(list2);
    
    // Merge two sorted lists
    struct SinglyLinkedList *merged = merge_sorted_lists(list1, list2);
    printf("Merged list: ");
    singly_print(merged);
    
    // Detect cycle (create a cycle first)
    if (list1->tail) {
        list1->tail->next = list1->head->next;  // Create cycle
    }
    
    bool has_cycle = detect_cycle(list1);
    printf("List 1 has cycle: %s\n", has_cycle ? "Yes" : "No");
    
    // Remove cycle before freeing
    if (list1->tail) {
        list1->tail->next = NULL;
    }
    
    singly_free(list1);
    singly_free(list2);
    singly_free(merged);
}

// Singly Linked List Implementation
struct SinglyLinkedList* create_singly_list() {
    struct SinglyLinkedList *list = malloc(sizeof(struct SinglyLinkedList));
    if (list) {
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
    }
    return list;
}

void singly_insert_front(struct SinglyLinkedList *list, int data) {
    if (!list) return;
    
    struct SinglyNode *new_node = malloc(sizeof(struct SinglyNode));
    if (!new_node) return;
    
    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
    
    if (!list->tail) {
        list->tail = new_node;
    }
    
    list->size++;
}

void singly_insert_back(struct SinglyLinkedList *list, int data) {
    if (!list) return;
    
    struct SinglyNode *new_node = malloc(sizeof(struct SinglyNode));
    if (!new_node) return;
    
    new_node->data = data;
    new_node->next = NULL;
    
    if (!list->head) {
        list->head = list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    
    list->size++;
}

void singly_insert_at(struct SinglyLinkedList *list, int index, int data) {
    if (!list || index < 0 || index > list->size) return;
    
    if (index == 0) {
        singly_insert_front(list, data);
        return;
    }
    
    if (index == list->size) {
        singly_insert_back(list, data);
        return;
    }
    
    struct SinglyNode *new_node = malloc(sizeof(struct SinglyNode));
    if (!new_node) return;
    
    new_node->data = data;
    
    struct SinglyNode *current = list->head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    
    new_node->next = current->next;
    current->next = new_node;
    list->size++;
}

bool singly_delete_front(struct SinglyLinkedList *list) {
    if (!list || !list->head) return false;
    
    struct SinglyNode *temp = list->head;
    list->head = list->head->next;
    
    if (!list->head) {
        list->tail = NULL;
    }
    
    free(temp);
    list->size--;
    return true;
}

bool singly_delete_back(struct SinglyLinkedList *list) {
    if (!list || !list->head) return false;
    
    if (list->head == list->tail) {
        free(list->head);
        list->head = list->tail = NULL;
        list->size--;
        return true;
    }
    
    struct SinglyNode *current = list->head;
    while (current->next != list->tail) {
        current = current->next;
    }
    
    free(list->tail);
    list->tail = current;
    current->next = NULL;
    list->size--;
    return true;
}

bool singly_delete_value(struct SinglyLinkedList *list, int value) {
    if (!list || !list->head) return false;
    
    if (list->head->data == value) {
        return singly_delete_front(list);
    }
    
    struct SinglyNode *current = list->head;
    while (current->next && current->next->data != value) {
        current = current->next;
    }
    
    if (!current->next) return false;
    
    struct SinglyNode *temp = current->next;
    current->next = temp->next;
    
    if (temp == list->tail) {
        list->tail = current;
    }
    
    free(temp);
    list->size--;
    return true;
}

int singly_find(struct SinglyLinkedList *list, int value) {
    if (!list) return -1;
    
    struct SinglyNode *current = list->head;
    int index = 0;
    
    while (current) {
        if (current->data == value) {
            return index;
        }
        current = current->next;
        index++;
    }
    
    return -1;
}

void singly_print(struct SinglyLinkedList *list) {
    if (!list) return;
    
    struct SinglyNode *current = list->head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void singly_reverse(struct SinglyLinkedList *list) {
    if (!list || !list->head) return;
    
    struct SinglyNode *prev = NULL;
    struct SinglyNode *current = list->head;
    struct SinglyNode *next = NULL;
    
    list->tail = list->head;
    
    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    list->head = prev;
}

void singly_sort(struct SinglyLinkedList *list) {
    if (!list || !list->head || list->size < 2) return;
    
    // Bubble sort implementation
    bool swapped;
    do {
        swapped = false;
        struct SinglyNode *current = list->head;
        
        while (current->next) {
            if (current->data > current->next->data) {
                // Swap data
                int temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

void singly_free(struct SinglyLinkedList *list) {
    if (!list) return;
    
    struct SinglyNode *current = list->head;
    while (current) {
        struct SinglyNode *temp = current;
        current = current->next;
        free(temp);
    }
    
    free(list);
}

// Doubly Linked List Implementation
struct DoublyLinkedList* create_doubly_list() {
    struct DoublyLinkedList *list = malloc(sizeof(struct DoublyLinkedList));
    if (list) {
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
    }
    return list;
}

void doubly_insert_front(struct DoublyLinkedList *list, int data) {
    if (!list) return;
    
    struct DoublyNode *new_node = malloc(sizeof(struct DoublyNode));
    if (!new_node) return;
    
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = list->head;
    
    if (list->head) {
        list->head->prev = new_node;
    } else {
        list->tail = new_node;
    }
    
    list->head = new_node;
    list->size++;
}

void doubly_insert_back(struct DoublyLinkedList *list, int data) {
    if (!list) return;
    
    struct DoublyNode *new_node = malloc(sizeof(struct DoublyNode));
    if (!new_node) return;
    
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = list->tail;
    
    if (list->tail) {
        list->tail->next = new_node;
    } else {
        list->head = new_node;
    }
    
    list->tail = new_node;
    list->size++;
}

void doubly_insert_at(struct DoublyLinkedList *list, int index, int data) {
    if (!list || index < 0 || index > list->size) return;
    
    if (index == 0) {
        doubly_insert_front(list, data);
        return;
    }
    
    if (index == list->size) {
        doubly_insert_back(list, data);
        return;
    }
    
    struct DoublyNode *new_node = malloc(sizeof(struct DoublyNode));
    if (!new_node) return;
    
    new_node->data = data;
    
    struct DoublyNode *current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    
    new_node->next = current;
    new_node->prev = current->prev;
    current->prev->next = new_node;
    current->prev = new_node;
    
    list->size++;
}

bool doubly_delete_front(struct DoublyLinkedList *list) {
    if (!list || !list->head) return false;
    
    struct DoublyNode *temp = list->head;
    list->head = list->head->next;
    
    if (list->head) {
        list->head->prev = NULL;
    } else {
        list->tail = NULL;
    }
    
    free(temp);
    list->size--;
    return true;
}

bool doubly_delete_back(struct DoublyLinkedList *list) {
    if (!list || !list->tail) return false;
    
    struct DoublyNode *temp = list->tail;
    list->tail = list->tail->prev;
    
    if (list->tail) {
        list->tail->next = NULL;
    } else {
        list->head = NULL;
    }
    
    free(temp);
    list->size--;
    return true;
}

void doubly_print_forward(struct DoublyLinkedList *list) {
    if (!list) return;
    
    struct DoublyNode *current = list->head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void doubly_print_backward(struct DoublyLinkedList *list) {
    if (!list) return;
    
    struct DoublyNode *current = list->tail;
    while (current) {
        printf("%d ", current->data);
        current = current->prev;
    }
    printf("\n");
}

void doubly_free(struct DoublyLinkedList *list) {
    if (!list) return;
    
    struct DoublyNode *current = list->head;
    while (current) {
        struct DoublyNode *temp = current;
        current = current->next;
        free(temp);
    }
    
    free(list);
}

// Circular Linked List Implementation
struct CircularNode* circular_create_node(int data) {
    struct CircularNode *new_node = malloc(sizeof(struct CircularNode));
    if (new_node) {
        new_node->data = data;
        new_node->next = new_node;  // Points to itself initially
    }
    return new_node;
}

struct CircularNode* circular_insert_back(struct CircularNode *last, int data) {
    struct CircularNode *new_node = circular_create_node(data);
    if (!new_node) return last;
    
    if (!last) {
        return new_node;
    }
    
    new_node->next = last->next;
    last->next = new_node;
    return new_node;  // New node becomes the last node
}

struct CircularNode* circular_insert_front(struct CircularNode *last, int data) {
    struct CircularNode *new_node = circular_create_node(data);
    if (!new_node) return last;
    
    if (!last) {
        return new_node;
    }
    
    new_node->next = last->next;
    last->next = new_node;
    return last;  // Last node remains the same
}

void circular_print(struct CircularNode *last) {
    if (!last) {
        printf("Empty list\n");
        return;
    }
    
    struct CircularNode *current = last->next;  // Start from first node
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != last->next);
    printf("\n");
}

struct CircularNode* circular_delete_node(struct CircularNode *last, int value) {
    if (!last) return NULL;
    
    // If only one node
    if (last->next == last && last->data == value) {
        free(last);
        return NULL;
    }
    
    struct CircularNode *current = last->next;
    struct CircularNode *prev = last;
    
    // Find the node to delete
    do {
        if (current->data == value) {
            prev->next = current->next;
            
            // If deleting the last node
            if (current == last) {
                last = prev;
            }
            
            free(current);
            return last;
        }
        prev = current;
        current = current->next;
    } while (current != last->next);
    
    return last;  // Node not found
}

void circular_free(struct CircularNode *last) {
    if (!last) return;
    
    struct CircularNode *current = last->next;
    while (current != last) {
        struct CircularNode *temp = current;
        current = current->next;
        free(temp);
    }
    free(last);
}

// Advanced operations
struct SinglyLinkedList* merge_sorted_lists(struct SinglyLinkedList *list1, struct SinglyLinkedList *list2) {
    struct SinglyLinkedList *merged = create_singly_list();
    if (!merged) return NULL;
    
    struct SinglyNode *p1 = list1->head;
    struct SinglyNode *p2 = list2->head;
    
    while (p1 && p2) {
        if (p1->data <= p2->data) {
            singly_insert_back(merged, p1->data);
            p1 = p1->next;
        } else {
            singly_insert_back(merged, p2->data);
            p2 = p2->next;
        }
    }
    
    while (p1) {
        singly_insert_back(merged, p1->data);
        p1 = p1->next;
    }
    
    while (p2) {
        singly_insert_back(merged, p2->data);
        p2 = p2->next;
    }
    
    return merged;
}

bool detect_cycle(struct SinglyLinkedList *list) {
    if (!list || !list->head) return false;
    
    struct SinglyNode *slow = list->head;
    struct SinglyNode *fast = list->head;
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            return true;
        }
    }
    
    return false;
}

int main() {
    printf("COMPLETE LINKED LISTS IMPLEMENTATION\n");
    printf("====================================\n\n");
    
    demonstrate_singly_linked_list();
    demonstrate_doubly_linked_list();
    demonstrate_circular_linked_list();
    demonstrate_advanced_operations();
    
    printf("\nKey Concepts Covered:\n");
    printf("- Singly linked list with full operations\n");
    printf("- Doubly linked list with bidirectional traversal\n");
    printf("- Circular linked list implementation\n");
    printf("- Insert/delete operations at various positions\n");
    printf("- Search and traversal algorithms\n");
    printf("- List reversal and sorting\n");
    printf("- Advanced operations (merge, cycle detection)\n");
    printf("- Memory management and cleanup\n");
    
    return 0;
}
