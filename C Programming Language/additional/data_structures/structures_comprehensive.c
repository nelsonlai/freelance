/**
 * Comprehensive Structures in C
 * Advanced structure usage, nested structures, bit fields, unions, and padding
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Basic structure
struct Point {
    int x, y;
};

// Structure with different data types
struct Student {
    int id;
    char name[50];
    float gpa;
    char grade;
    struct Point location;  // Nested structure
};

// Structure with bit fields
struct StatusRegister {
    unsigned int ready : 1;        // 1 bit
    unsigned int error : 1;        // 1 bit
    unsigned int mode : 3;         // 3 bits (0-7)
    unsigned int priority : 4;     // 4 bits (0-15)
    unsigned int reserved : 7;     // 7 bits
    unsigned int interrupt : 1;    // 1 bit
    unsigned int padding : 15;     // 15 bits padding
};

// Packed structure (compiler-specific)
struct __attribute__((packed)) PackedStruct {
    char c;
    int i;
    short s;
};

// Regular structure for comparison
struct RegularStruct {
    char c;
    int i;
    short s;
};

// Union for different data interpretations
union DataUnion {
    int integer;
    float floating_point;
    char bytes[4];
    struct {
        unsigned short low;
        unsigned short high;
    } words;
};

// Complex structure with pointers
struct Employee {
    int id;
    char *name;                    // Dynamic string
    struct Employee *manager;      // Self-referencing pointer
    struct Employee **subordinates; // Array of pointers
    int subordinate_count;
    struct {                       // Anonymous structure
        int day, month, year;
    } hire_date;
};

// Structure with function pointer
struct Calculator {
    char name[20];
    double (*operation)(double, double);
};

// Function prototypes
double add_op(double a, double b);
double subtract_op(double a, double b);
double multiply_op(double a, double b);
double divide_op(double a, double b);

void demonstrate_basic_structures() {
    printf("=== Basic Structure Usage ===\n");
    
    struct Point p1 = {10, 20};
    struct Point p2;
    
    // Different initialization methods
    p2.x = 30;
    p2.y = 40;
    
    printf("Point 1: (%d, %d)\n", p1.x, p1.y);
    printf("Point 2: (%d, %d)\n", p2.x, p2.y);
    
    // Structure assignment
    struct Point p3 = p1;  // Copy entire structure
    printf("Point 3 (copy of p1): (%d, %d)\n", p3.x, p3.y);
    
    // Array of structures
    struct Point points[] = {{1, 1}, {2, 4}, {3, 9}, {4, 16}};
    printf("\nArray of points:\n");
    for (int i = 0; i < 4; i++) {
        printf("Point %d: (%d, %d)\n", i, points[i].x, points[i].y);
    }
}

void demonstrate_nested_structures() {
    printf("\n=== Nested Structures ===\n");
    
    struct Student student1 = {
        .id = 12345,
        .name = "John Doe",
        .gpa = 3.75,
        .grade = 'A',
        .location = {100, 200}  // Nested structure initialization
    };
    
    printf("Student Information:\n");
    printf("ID: %d\n", student1.id);
    printf("Name: %s\n", student1.name);
    printf("GPA: %.2f\n", student1.gpa);
    printf("Grade: %c\n", student1.grade);
    printf("Location: (%d, %d)\n", student1.location.x, student1.location.y);
    
    // Accessing nested structure members
    student1.location.x = 150;
    student1.location.y = 250;
    printf("Updated location: (%d, %d)\n", student1.location.x, student1.location.y);
}

void demonstrate_bit_fields() {
    printf("\n=== Bit Fields ===\n");
    
    struct StatusRegister status = {0};
    
    // Set individual bit fields
    status.ready = 1;
    status.error = 0;
    status.mode = 5;        // 3 bits can hold 0-7
    status.priority = 12;   // 4 bits can hold 0-15
    status.interrupt = 1;
    
    printf("Status Register:\n");
    printf("Ready: %u\n", status.ready);
    printf("Error: %u\n", status.error);
    printf("Mode: %u\n", status.mode);
    printf("Priority: %u\n", status.priority);
    printf("Interrupt: %u\n", status.interrupt);
    
    // View as raw integer
    printf("Raw value: 0x%08X\n", *(unsigned int*)&status);
    printf("Size of bit field structure: %zu bytes\n", sizeof(status));
    
    // Demonstrate bit field limitations
    status.mode = 8;  // This will overflow (3 bits can only hold 0-7)
    printf("Mode after setting to 8: %u (should be 0 due to overflow)\n", status.mode);
}

void demonstrate_structure_padding() {
    printf("\n=== Structure Padding and Alignment ===\n");
    
    struct RegularStruct regular;
    struct PackedStruct packed;
    
    printf("Regular structure:\n");
    printf("Size: %zu bytes\n", sizeof(struct RegularStruct));
    printf("char offset: %zu\n", (char*)&regular.c - (char*)&regular);
    printf("int offset: %zu\n", (char*)&regular.i - (char*)&regular);
    printf("short offset: %zu\n", (char*)&regular.s - (char*)&regular);
    
    printf("\nPacked structure:\n");
    printf("Size: %zu bytes\n", sizeof(struct PackedStruct));
    printf("char offset: %zu\n", (char*)&packed.c - (char*)&packed);
    printf("int offset: %zu\n", (char*)&packed.i - (char*)&packed);
    printf("short offset: %zu\n", (char*)&packed.s - (char*)&packed);
    
    // Demonstrate alignment requirements
    printf("\nAlignment requirements:\n");
    printf("char alignment: %zu\n", _Alignof(char));
    printf("int alignment: %zu\n", _Alignof(int));
    printf("double alignment: %zu\n", _Alignof(double));
}

void demonstrate_unions() {
    printf("\n=== Unions ===\n");
    
    union DataUnion data;
    
    // Store as integer
    data.integer = 0x12345678;
    printf("Stored as integer: 0x%08X\n", data.integer);
    printf("Viewed as float: %f\n", data.floating_point);
    printf("Viewed as bytes: ");
    for (int i = 0; i < 4; i++) {
        printf("0x%02X ", (unsigned char)data.bytes[i]);
    }
    printf("\n");
    printf("High word: 0x%04X, Low word: 0x%04X\n", data.words.high, data.words.low);
    
    // Store as float
    data.floating_point = 3.14159f;
    printf("\nStored as float: %f\n", data.floating_point);
    printf("Viewed as integer: 0x%08X\n", data.integer);
    
    printf("Union size: %zu bytes (size of largest member)\n", sizeof(union DataUnion));
}

void demonstrate_structure_pointers() {
    printf("\n=== Structure Pointers ===\n");
    
    struct Student student = {1001, "Alice Smith", 3.85, 'A', {50, 75}};
    struct Student *ptr = &student;
    
    // Different ways to access structure members through pointers
    printf("Using dot operator: %s\n", student.name);
    printf("Using arrow operator: %s\n", ptr->name);
    printf("Using dereference: %s\n", (*ptr).name);
    
    // Modify through pointer
    ptr->gpa = 3.90;
    strcpy(ptr->name, "Alice Johnson");
    
    printf("After modification: %s, GPA: %.2f\n", student.name, student.gpa);
    
    // Array of structure pointers
    struct Student *students[3];
    students[0] = &student;
    students[1] = malloc(sizeof(struct Student));
    students[2] = malloc(sizeof(struct Student));
    
    if (students[1] && students[2]) {
        *students[1] = (struct Student){1002, "Bob Wilson", 3.60, 'B', {60, 80}};
        *students[2] = (struct Student){1003, "Carol Davis", 3.95, 'A', {70, 90}};
        
        printf("\nArray of structure pointers:\n");
        for (int i = 0; i < 3; i++) {
            printf("%d: %s (GPA: %.2f)\n", 
                   students[i]->id, students[i]->name, students[i]->gpa);
        }
        
        free(students[1]);
        free(students[2]);
    }
}

void demonstrate_self_referencing_structures() {
    printf("\n=== Self-Referencing Structures (Linked List) ===\n");
    
    // Create a simple linked list
    struct Employee *ceo = malloc(sizeof(struct Employee));
    struct Employee *manager1 = malloc(sizeof(struct Employee));
    struct Employee *manager2 = malloc(sizeof(struct Employee));
    struct Employee *employee1 = malloc(sizeof(struct Employee));
    
    if (!ceo || !manager1 || !manager2 || !employee1) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    // Initialize CEO
    ceo->id = 1;
    ceo->name = strdup("John CEO");
    ceo->manager = NULL;  // CEO has no manager
    ceo->subordinates = malloc(2 * sizeof(struct Employee*));
    ceo->subordinate_count = 2;
    ceo->subordinates[0] = manager1;
    ceo->subordinates[1] = manager2;
    ceo->hire_date = (struct {int day, month, year;}){1, 1, 2020};
    
    // Initialize managers
    manager1->id = 2;
    manager1->name = strdup("Jane Manager");
    manager1->manager = ceo;
    manager1->subordinates = malloc(1 * sizeof(struct Employee*));
    manager1->subordinate_count = 1;
    manager1->subordinates[0] = employee1;
    manager1->hire_date = (struct {int day, month, year;}){15, 3, 2020};
    
    manager2->id = 3;
    manager2->name = strdup("Bob Manager");
    manager2->manager = ceo;
    manager2->subordinates = NULL;
    manager2->subordinate_count = 0;
    manager2->hire_date = (struct {int day, month, year;}){20, 4, 2020};
    
    // Initialize employee
    employee1->id = 4;
    employee1->name = strdup("Alice Employee");
    employee1->manager = manager1;
    employee1->subordinates = NULL;
    employee1->subordinate_count = 0;
    employee1->hire_date = (struct {int day, month, year;}){10, 6, 2021};
    
    // Print organizational structure
    printf("Organizational Structure:\n");
    printf("%s (ID: %d) - CEO\n", ceo->name, ceo->id);
    for (int i = 0; i < ceo->subordinate_count; i++) {
        struct Employee *mgr = ceo->subordinates[i];
        printf("  %s (ID: %d) - Manager\n", mgr->name, mgr->id);
        for (int j = 0; j < mgr->subordinate_count; j++) {
            struct Employee *emp = mgr->subordinates[j];
            printf("    %s (ID: %d) - Employee\n", emp->name, emp->id);
        }
    }
    
    // Clean up
    free(employee1->name);
    free(employee1);
    free(manager2->name);
    free(manager2);
    free(manager1->name);
    free(manager1->subordinates);
    free(manager1);
    free(ceo->name);
    free(ceo->subordinates);
    free(ceo);
}

void demonstrate_function_pointers_in_structures() {
    printf("\n=== Function Pointers in Structures ===\n");
    
    struct Calculator calculators[] = {
        {"Addition", add_op},
        {"Subtraction", subtract_op},
        {"Multiplication", multiply_op},
        {"Division", divide_op}
    };
    
    double a = 15.0, b = 3.0;
    int num_calcs = sizeof(calculators) / sizeof(calculators[0]);
    
    printf("Performing operations on %.1f and %.1f:\n", a, b);
    for (int i = 0; i < num_calcs; i++) {
        double result = calculators[i].operation(a, b);
        printf("%s: %.2f\n", calculators[i].name, result);
    }
}

void demonstrate_flexible_array_members() {
    printf("\n=== Flexible Array Members ===\n");
    
    // Structure with flexible array member
    struct FlexibleArray {
        int size;
        int data[];  // Flexible array member (C99 feature)
    };
    
    int n = 5;
    struct FlexibleArray *flex = malloc(sizeof(struct FlexibleArray) + n * sizeof(int));
    
    if (flex) {
        flex->size = n;
        for (int i = 0; i < n; i++) {
            flex->data[i] = i * i;
        }
        
        printf("Flexible array with %d elements:\n", flex->size);
        for (int i = 0; i < flex->size; i++) {
            printf("data[%d] = %d\n", i, flex->data[i]);
        }
        
        free(flex);
    }
}

// Function implementations for calculator
double add_op(double a, double b) { return a + b; }
double subtract_op(double a, double b) { return a - b; }
double multiply_op(double a, double b) { return a * b; }
double divide_op(double a, double b) { return b != 0 ? a / b : 0; }

int main() {
    printf("COMPREHENSIVE STRUCTURES IN C\n");
    printf("=============================\n\n");
    
    demonstrate_basic_structures();
    demonstrate_nested_structures();
    demonstrate_bit_fields();
    demonstrate_structure_padding();
    demonstrate_unions();
    demonstrate_structure_pointers();
    demonstrate_self_referencing_structures();
    demonstrate_function_pointers_in_structures();
    demonstrate_flexible_array_members();
    
    printf("\nKey Concepts Covered:\n");
    printf("- Basic structure declaration and usage\n");
    printf("- Nested structures and initialization\n");
    printf("- Bit fields for memory-efficient storage\n");
    printf("- Structure padding and alignment\n");
    printf("- Unions for different data interpretations\n");
    printf("- Structure pointers and member access\n");
    printf("- Self-referencing structures (linked lists)\n");
    printf("- Function pointers in structures\n");
    printf("- Flexible array members (C99)\n");
    
    return 0;
}
