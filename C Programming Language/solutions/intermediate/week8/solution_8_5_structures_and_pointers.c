/**
 * Solution 8.5: Advanced Structures and Pointers
 * Week 8 - Advanced Arrays and Strings
 * 
 * Description: Comprehensive structures with pointer manipulation and bit operations
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure definitions with various data types // self-defined data types
struct Point {
    int x, y;
};

struct Rectangle {
    struct Point top_left;
    struct Point top_right;
    struct Point bottom_left;
    struct Point bottom_right;
    unsigned int properties;  // Bit field for properties
};

struct Packet {    // Node for linked list
    int packet_id;
    char iphead[50];
    link_layer l2;
    struct Packet *next;  // For linked list, pointer to next node
};

// Bit manipulation structure
struct Flags {
    unsigned int is_active : 1;      // 1 bit
    unsigned int priority : 3;       // 3 bits (0-7)
    unsigned int category : 4;       // 4 bits (0-15)
    unsigned int reserved : 24;      // 24 bits
};


void demonstrate_structure_pointers() {
    printf("=== Structure Pointers and Arrow Operator ===\n");
    
    struct Point p1 = {10, 20}; // x = 10, y = 20
    struct Point *ptr = &p1; // ptr points to p1
    /*
    struct Point {
    int x, y;
    */
    
    // Different ways to access structure members
    printf("Using dot operator: p1.x = %d, p1.y = %d\n", p1.x, p1.y);
    printf("Using arrow operator: ptr->x = %d, ptr->y = %d\n", ptr->x, ptr->y);
    printf("Using dereference: (*ptr).x = %d, (*ptr).y = %d\n", (*ptr).x, (*ptr).y);
    
    // Pointer arithmetic with structures
    struct Point points[] = {{1, 2}, {3, 4}, {5, 6}};
    struct Point *p = points;
    
    printf("\nPointer arithmetic with structures:\n");
    for (int i = 0; i < 3; i++) {
        printf("Point %d: (%d, %d)\n", i, p->x, p->y);
        p++;  // Move to next structure
    }
    
    // Pre/post increment with structure pointers
    p = points;
    printf("\nPre/post increment demo:\n");
    printf("p->x = %d (current)\n", p->x);
    printf("(p++)->x = %d (post-increment)\n", (p++)->x);
    printf("(++p)->x = %d (pre-increment)\n", (++p)->x);
}

void bit_operations_demo() {
    printf("\n=== Bit Operations and Flags ===\n");
    
    // Basic bit operations
    unsigned int flags = 0;
    
    // Set bits (using OR)
    /*
    & = AND
    | = OR
    ~ = NOT
    ^ = XOR
    << = LEFT SHIFT
    >> = RIGHT SHIFT
    */
   /*
   |= OR assignment operator
   &= AND assignment operator
   ^= XOR assignment operator
   <<= LEFT SHIFT assignment operator
   >>= RIGHT SHIFT assignment operator
   */
    unsigned int x = (1 << 0); // x = 1 (00000001)
    unsigned int y = (1 << 2); // y = 4 (00000100)
    unsigned int z = (1 << 5); // z = 32 (00100000)
    // set bits 0, 2, 5 to 1    // or assignment operator
    flags |= (1 << 0);  // Set bit 0 (00000001)
    flags |= (1 << 2);  // Set bit 2 (00000100)
    flags |= (1 << 5);  // Set bit 5 (00100000)

    // clear bit 0, 2, 5 to 0    // and assignment operator with not
    flags &= ~(1 << 0);  // Clear bit 0 (00000001)
    flags &= ~(1 << 2);  // Clear bit 2 (00000100)
    flags &= ~(1 << 5);  // Clear bit 5 (00100000)

    // toggle bit 1 to 0    // xor assignment operator
    flags ^= (1 << 1);  // Toggle bit 1 (00000010)
    flags ^= (1 << 2);  // Toggle bit 1 (00000010)
    flags ^= (1 << 5);  // Toggle bit 1 (00000010)
    
    printf("After setting bits 0, 2, 5: flags = %u (binary: ", flags);
    for (int i = 7; i >= 0; i--) {
        printf("%d", (flags >> i) & 1);
    }
    printf(")\n");
    
    // Check bits (using AND)
    printf("Bit 0 is %s\n", (flags & (1 << 0)) ? "set" : "clear");
    printf("Bit 1 is %s\n", (flags & (1 << 1)) ? "set" : "clear");
    printf("Bit 2 is %s\n", (flags & (1 << 2)) ? "set" : "clear");
    
    // Clear bits (using AND with NOT)
    flags &= ~(1 << 2);  // Clear bit 2
    printf("After clearing bit 2: flags = %u\n", flags);
    
    // Toggle bits (using XOR)
    flags ^= (1 << 1);  // Toggle bit 1
    printf("After toggling bit 1: flags = %u\n", flags);
    
    // Bit field demonstration
    struct Flags status = {0};
    status.is_active = 1;
    status.priority = 5;
    status.category = 12;
    
    printf("\nBit fields: active=%d, priority=%d, category=%d\n", 
           status.is_active, status.priority, status.category);
}

void structure_array_manipulation() {
    printf("\n=== Structure Array Manipulation ===\n");
    /*
    struct Rectangle {
        struct Point top_left;
        struct Point top_right;
        struct Point bottom_left;
        struct Point bottom_right;
        unsigned int properties;  // Bit field for properties
    };
    */
    struct Rectangle rects[] = {
        {{1, 2}, {3, 4}, {5, 6}, {7, 8}, 0x12345678},
        {{9, 10}, {11, 12}, {13, 14}, {15, 16}, 0x87654321},
        {{17, 18}, {19, 20}, {21, 22}, {23, 24}, 0x12345678},
    };
    
    struct Rectangle *rect_ptr = rects;
    
    printf("Rectangle data:\n");
    for (int i = 0; i < 3; i++) {
        printf("Rect %d: (%d,%d) to (%d,%d), properties=0x%02X\n",
               i, rect_ptr->top_left.x, rect_ptr->top_left.y,
               rect_ptr->bottom_right.x, rect_ptr->bottom_right.y,
               rect_ptr->properties);
        rect_ptr++;
    }
    
    // Calculate areas using pointer arithmetic
    rect_ptr = rects;
    printf("\nAreas:\n");
    for (int i = 0; i < 3; i++) {
        int width = rect_ptr->bottom_right.x - rect_ptr->top_left.x;
        int height = rect_ptr->bottom_right.y - rect_ptr->top_left.y;
        printf("Rect %d area: %d\n", i, width * height);
        rect_ptr++;
    }
}

void linked_list_demo() {
    printf("\n=== Linked List with Structures ===\n");
    
    // Create nodes
    /*
    struct Student {
        int id;
        char name[50];
        float gpa;
        struct Student *next;  // For linked list, pointer to next node
    };
    */
    struct Student *head = (struct Student*)malloc(sizeof(struct Student));
    struct Student *second = (struct Student*)malloc(sizeof(struct Student));
    struct Student *third = (struct Student*)malloc(sizeof(struct Student));
    
    if (!head || !second || !third) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    // Initialize first node
    head->id = 101;
    strcpy(head->name, "Alice");
    head->gpa = 3.8;
    head->next = second;
    
    // Initialize second node
    second->id = 102;
    strcpy(second->name, "Bob");
    second->gpa = 3.6;
    second->next = third;
    
    // Initialize third node
    third->id = 103;
    strcpy(third->name, "Charlie");
    third->gpa = 3.9;
    third->next = NULL;
    
    // Traverse and print
    struct Student *current = head;
    printf("Student list:\n");
    while (current != NULL) {
        printf("ID: %d, Name: %s, GPA: %.1f\n", 
               current->id, current->name, current->gpa);
        current = current->next;
    }
    
    // Clean up memory
    free(head);
    free(second);
    free(third);
}

// ENUMS

void enum_demonstration() {
    printf("\n=== Enum ===\n");
    
    
    enum Color { RED, GREEN, BLUE };
    enum Color color = RED;
    printf("Color: %d\n", color);
    
    color = GREEN;
    printf("Color: %d\n", color);
    
    color = BLUE;
    printf("Color: %d\n", color);

    enum Weekday { MONDAY=1, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY };
    enum Weekday weekday = MONDAY;
    printf("Weekday: %d\n", weekday);
    
    weekday = TUESDAY;
    printf("Weekday: %d\n", weekday);
    switch (weekday) {
        case MONDAY:
            printf("Monday\n");
            break;
        case TUESDAY:
            printf("Tuesday\n");
            break;
        case WEDNESDAY:
            printf("Wednesday\n");
            break;
        case THURSDAY:
            printf("Thursday\n");
            break;
        case FRIDAY:
            printf("Friday\n");
            break;
        case SATURDAY:
            printf("Saturday\n");
            break;
        case SUNDAY:
            printf("Sunday\n");
            break;
    }
    
}

// UNIONS

void union_demonstration() {
    /*
    struct Flags {
    unsigned int is_active : 1;    
    unsigned int priority : 3;      
    unsigned int category : 4;      
    unsigned int reserved : 24;     
    };
    */
    union Data {
        int integer;
        float floating;
        char bytes[4];
        struct Flags flags;
    };

    printf("\n=== Union and Type Punning ===\n");
    
    union Data data;
    
    // Store as integer
    data.integer = 0x12345678;
    printf("As integer: 0x%08X (%d)\n", data.integer, data.integer);
    
    // View as float (type punning)
    printf("As float: %f\n", data.floating);
    
    // View as bytes
    printf("As bytes: ");
    for (int i = 0; i < 4; i++) {
        printf("0x%02X ", (unsigned char)data.bytes[i]);
    }
    printf("\n");
    
    // Store as float
    data.floating = 3.14159f;
    printf("\nAs float: %f\n", data.floating);
    printf("As integer: 0x%08X\n", data.integer);
    
    // Use bit fields
    data.integer = 0;
    data.flags.is_active = 1;
    data.flags.priority = 7;
    data.flags.category = 15;
    printf("Bit fields set: integer value = 0x%08X\n", data.integer);
}

void advanced_pointer_operations() {
    printf("\n=== Advanced Pointer Operations ===\n");
    
    struct Point points[] = {{1, 1}, {2, 4}, {3, 9}, {4, 16}};
    struct Point *p = points;
    struct Point *end = points + 4;
    
    // Pointer arithmetic with pre/post increment
    printf("Forward traversal with post-increment:\n");
    while (p < end) {
        printf("(%d, %d) ", p->x, p->y);
        p++;
    }
    printf("\n");
    
    // Backward traversal with pre-decrement
    printf("Backward traversal with pre-decrement:\n");
    p = end - 1;  // Point to last element
    while (p >= points) {
        printf("(%d, %d) ", p->x, p->y);
        p--;
    }
    printf("\n");
    
    // Complex pointer expressions
    p = points;
    printf("\nComplex expressions:\n");
    printf("p->x = %d\n", p->x);
    printf("(p++)->x = %d, now p->x = %d\n", (p++)->x, p->x);
    printf("(++p)->y = %d\n", (++p)->y);
    printf("(*p).x = %d\n", (*p).x);
}

void bitwise_operations_advanced() {
    printf("\n=== Advanced Bitwise Operations ===\n");
    
    unsigned int a = 0b11010011;  // Binary literal (if supported)
    unsigned int b = 0b10110101;
    
    printf("a = %u (0x%02X)\n", a, a);
    printf("b = %u (0x%02X)\n", b, b);
    
    printf("\nBitwise operations:\n");
    printf("a & b  = %u (0x%02X) - AND\n", a & b, a & b);
    printf("a | b  = %u (0x%02X) - OR\n", a | b, a | b);
    printf("a ^ b  = %u (0x%02X) - XOR\n", a ^ b, a ^ b);
    printf("~a     = %u (0x%02X) - NOT\n", ~a, ~a & 0xFF);
    printf("a << 2 = %u (0x%02X) - Left shift\n", a << 2, a << 2);
    printf("a >> 2 = %u (0x%02X) - Right shift\n", a >> 2, a >> 2);
    
    // Bit manipulation techniques
    printf("\nBit manipulation techniques:\n");
    
    // Count set bits
    unsigned int count = 0;
    unsigned int temp = a;
    while (temp) {
        count += temp & 1;
        temp >>= 1;
    }
    printf("Number of set bits in a: %u\n", count);
    
    // Check if power of 2
    printf("Is a power of 2? %s\n", (a && !(a & (a - 1))) ? "Yes" : "No");
    
    // Swap using XOR
    unsigned int x = 25, y = 30;
    printf("Before swap: x=%u, y=%u\n", x, y);
    x ^= y;
    y ^= x;
    x ^= y;
    printf("After XOR swap: x=%u, y=%u\n", x, y);
}

int main() {
    printf("ADVANCED STRUCTURES, POINTERS, AND BIT OPERATIONS\n");
    printf("=================================================\n\n");
    
    demonstrate_structure_pointers();
    bit_operations_demo();
    structure_array_manipulation();
    linked_list_demo();
    union_demonstration();
    advanced_pointer_operations();
    bitwise_operations_advanced();
    
    printf("\nConcepts Demonstrated:\n");
    printf("- Structure pointers and arrow operator\n");
    printf("- Pre/post increment with structure pointers\n");
    printf("- Bit operations and bit fields\n");
    printf("- Structure arrays and pointer arithmetic\n");
    printf("- Linked lists with dynamic memory\n");
    printf("- Unions and type punning\n");
    printf("- Advanced bitwise operations\n");
    printf("- Complex pointer expressions\n");
    
    return 0;
}
