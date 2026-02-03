/*
 * POINTER INTERMEDIATE EXAMPLES
 * 
 * This file demonstrates intermediate pointer concepts:
 * - Dynamic memory allocation (new/delete)
 * - Pointers to pointers (double pointers)
 * - Array of pointers
 * - Pointer to array
 * - Function pointers
 * - Pointers to structures/classes
 * - Memory management best practices
 * - Common pitfalls and solutions
 * 
 * Learning Objectives:
 * - Master dynamic memory allocation
 * - Understand multi-level pointers
 * - Work with complex pointer scenarios
 * - Learn function pointers basics
 * - Understand memory management
 * 
 * Prerequisites:
 * - Completed pointer_beginner.cpp
 * - Understanding of basic pointer operations
 * - Familiarity with arrays and functions
 * - Basic understanding of structures
 * 
 * Key Topics Covered:
 * - new and delete operators
 * - Memory leaks and how to prevent them
 * - Double pointers and their uses
 * - Dynamic arrays
 * - Function pointers
 * - Pointers with structures
 */

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// ==============================================================================
// SECTION 1: DYNAMIC MEMORY ALLOCATION (new/delete)
// ==============================================================================
/*
 * DYNAMIC MEMORY ALLOCATION:
 * 
 * Stack vs Heap:
 * - Stack: Automatic storage, limited size, fast, automatic cleanup
 * - Heap: Dynamic storage, large size, slower, manual cleanup needed
 * 
 * Operators:
 * - new: Allocates memory on the heap
 * - delete: Frees memory allocated with new
 * - new[]: Allocates array on the heap
 * - delete[]: Frees array allocated with new[]
 * 
 * IMPORTANT: Every 'new' must have a corresponding 'delete'!
 */

void dynamicMemoryBasics() {
    cout << "=== DYNAMIC MEMORY ALLOCATION (new/delete) ===" << endl << endl;
    
    // Allocating a single integer
    cout << "1. Single Variable Allocation:" << endl;
    int* ptr = new int;        // Allocate memory for one int
    *ptr = 42;                 // Assign value
    cout << "   Value: " << *ptr << endl;
    cout << "   Address: " << ptr << endl;
    delete ptr;                // Free the memory
    ptr = nullptr;             // Good practice: set to nullptr after delete
    cout << "   Memory freed and pointer set to nullptr" << endl;
    cout << endl;
    
    // Allocating with initialization
    cout << "2. Allocation with Initialization:" << endl;
    int* ptr2 = new int(100);  // Allocate and initialize to 100
    cout << "   Value: " << *ptr2 << endl;
    delete ptr2;
    ptr2 = nullptr;
    cout << endl;
    
    // Allocating different types
    cout << "3. Different Types:" << endl;
    double* dPtr = new double(3.14);
    string* sPtr = new string("Hello");
    char* cPtr = new char('A');
    
    cout << "   Double: " << *dPtr << endl;
    cout << "   String: " << *sPtr << endl;
    cout << "   Char: " << *cPtr << endl;
    
    delete dPtr;
    delete sPtr;
    delete cPtr;
    cout << endl;
    
    // Memory leak demonstration (what NOT to do)
    cout << "4. Memory Leak Warning:" << endl;
    int* leakyPtr = new int(50);
    cout << "   Allocated memory: " << *leakyPtr << endl;
    // leakyPtr = nullptr;  // WRONG! This loses the address without freeing memory
    delete leakyPtr;        // CORRECT! Free first, then set to nullptr
    leakyPtr = nullptr;
    cout << "   Properly freed" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 2: DYNAMIC ARRAYS
// ==============================================================================
/*
 * DYNAMIC ARRAYS:
 * 
 * Static array: int arr[5];        (size must be known at compile time)
 * Dynamic array: int* arr = new int[size];  (size can be determined at runtime)
 * 
 * Syntax:
 * - Allocation: type* ptr = new type[size];
 * - Deallocation: delete[] ptr;  (Note the [] brackets!)
 * 
 * CRITICAL: Use delete[] for arrays, not delete!
 */

void dynamicArrays() {
    cout << "=== DYNAMIC ARRAYS ===" << endl << endl;
    
    // Get array size at runtime
    int size = 5;
    
    // Allocate dynamic array
    cout << "1. Creating Dynamic Array:" << endl;
    int* arr = new int[size];  // Allocate array of 5 integers
    
    // Initialize array
    for (int i = 0; i < size; i++) {
        arr[i] = (i + 1) * 10;
    }
    
    // Display array
    cout << "   Array contents: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // Proper deallocation
    delete[] arr;  // Use delete[] for arrays!
    arr = nullptr;
    cout << "   Array freed with delete[]" << endl;
    cout << endl;
    
    // Dynamic array with initialization (C++11)
    cout << "2. Array with Initialization (C++11):" << endl;
    int* arr2 = new int[5]{10, 20, 30, 40, 50};
    cout << "   Array: ";
    for (int i = 0; i < 5; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;
    delete[] arr2;
    cout << endl;
    
    // Dynamic array of strings
    cout << "3. Dynamic Array of Strings:" << endl;
    string* names = new string[3];
    names[0] = "Alice";
    names[1] = "Bob";
    names[2] = "Charlie";
    
    cout << "   Names: ";
    for (int i = 0; i < 3; i++) {
        cout << names[i] << " ";
    }
    cout << endl;
    delete[] names;
    cout << endl;
}

// ==============================================================================
// SECTION 3: POINTERS TO POINTERS (DOUBLE POINTERS)
// ==============================================================================
/*
 * DOUBLE POINTERS (POINTER TO POINTER):
 * 
 * A pointer that stores the address of another pointer.
 * 
 * Syntax: type** ptrName;
 * 
 * Uses:
 * - 2D dynamic arrays
 * - Modifying pointer in function
 * - Linked lists, trees
 * - String arrays (char** for command line args)
 * 
 * Levels of indirection:
 * - value: the actual value
 * - *ptr: value through one pointer
 * - **ptrPtr: value through two pointers
 */

void doublePointers() {
    cout << "=== POINTERS TO POINTERS (DOUBLE POINTERS) ===" << endl << endl;
    
    // Basic double pointer
    cout << "1. Basic Double Pointer:" << endl;
    int value = 100;
    int* ptr = &value;      // Pointer to int
    int** ptrPtr = &ptr;    // Pointer to pointer to int
    
    cout << "   value = " << value << endl;
    cout << "   &value = " << &value << endl;
    cout << endl;
    cout << "   ptr = " << ptr << " (address of value)" << endl;
    cout << "   *ptr = " << *ptr << " (value through ptr)" << endl;
    cout << "   &ptr = " << &ptr << " (address of ptr itself)" << endl;
    cout << endl;
    cout << "   ptrPtr = " << ptrPtr << " (address of ptr)" << endl;
    cout << "   *ptrPtr = " << *ptrPtr << " (value of ptr, i.e., address of value)" << endl;
    cout << "   **ptrPtr = " << **ptrPtr << " (value through two pointers)" << endl;
    cout << endl;
    
    // Modifying value through double pointer
    cout << "2. Modifying Through Double Pointer:" << endl;
    **ptrPtr = 200;  // Changes value
    cout << "   After **ptrPtr = 200:" << endl;
    cout << "   value = " << value << endl;
    cout << "   *ptr = " << *ptr << endl;
    cout << "   **ptrPtr = " << **ptrPtr << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 4: 2D DYNAMIC ARRAYS
// ==============================================================================
/*
 * 2D DYNAMIC ARRAYS:
 * 
 * Creating a 2D array dynamically requires:
 * 1. Allocate array of pointers (rows)
 * 2. Allocate array for each row (columns)
 * 
 * Deallocation must be in reverse order:
 * 1. Delete each row
 * 2. Delete array of pointers
 */

void twoDimensionalArrays() {
    cout << "=== 2D DYNAMIC ARRAYS ===" << endl << endl;
    
    int rows = 3;
    int cols = 4;
    
    cout << "Creating 3x4 2D array:" << endl;
    
    // Step 1: Allocate array of pointers (one for each row)
    int** matrix = new int*[rows];
    
    // Step 2: Allocate each row
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }
    
    // Initialize matrix
    int value = 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = value++;
        }
    }
    
    // Display matrix
    cout << "Matrix contents:" << endl;
    for (int i = 0; i < rows; i++) {
        cout << "   ";
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
    
    // Deallocation (IMPORTANT: reverse order!)
    // Step 1: Delete each row
    for (int i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    
    // Step 2: Delete array of pointers
    delete[] matrix;
    matrix = nullptr;
    
    cout << "Matrix freed properly" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 5: ARRAY OF POINTERS
// ==============================================================================
/*
 * ARRAY OF POINTERS:
 * 
 * An array where each element is a pointer.
 * 
 * Syntax: type* arrayName[size];
 * 
 * Uses:
 * - Array of strings (each pointer to a string)
 * - Array of dynamic arrays (jagged arrays)
 * - Array of objects
 */

void arrayOfPointers() {
    cout << "=== ARRAY OF POINTERS ===" << endl << endl;
    
    // Array of pointers to integers
    cout << "1. Array of Integer Pointers:" << endl;
    int a = 10, b = 20, c = 30;
    int* ptrArray[3];  // Array of 3 int pointers
    
    ptrArray[0] = &a;
    ptrArray[1] = &b;
    ptrArray[2] = &c;
    
    cout << "   Values through pointer array:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "   ptrArray[" << i << "] points to: " << *ptrArray[i] << endl;
    }
    cout << endl;
    
    // Array of pointers to strings (C-style strings)
    cout << "2. Array of String Pointers:" << endl;
    const char* fruits[4] = {
        "Apple",
        "Banana",
        "Cherry",
        "Date"
    };
    
    cout << "   Fruits:" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "   " << i << ": " << fruits[i] << endl;
    }
    cout << endl;
    
    // Array of pointers with dynamic allocation
    cout << "3. Dynamic Array of Pointers:" << endl;
    int** dynPtrArray = new int*[3];
    
    for (int i = 0; i < 3; i++) {
        dynPtrArray[i] = new int((i + 1) * 100);
    }
    
    cout << "   Dynamic pointer array values:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "   " << *dynPtrArray[i] << endl;
    }
    
    // Free memory
    for (int i = 0; i < 3; i++) {
        delete dynPtrArray[i];
    }
    delete[] dynPtrArray;
    cout << endl;
}

// ==============================================================================
// SECTION 6: POINTER TO ARRAY
// ==============================================================================
/*
 * POINTER TO ARRAY:
 * 
 * A single pointer that points to an entire array.
 * Different from array of pointers!
 * 
 * Syntax: type (*ptrName)[size];
 * Note: Parentheses are important!
 * 
 * type* ptrName[size];   - Array of pointers
 * type (*ptrName)[size]; - Pointer to array
 */

void pointerToArray() {
    cout << "=== POINTER TO ARRAY ===" << endl << endl;
    
    // Regular array
    int arr[5] = {10, 20, 30, 40, 50};
    
    // Pointer to array of 5 integers
    int (*ptr)[5] = &arr;
    
    cout << "Array: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    cout << "Through pointer to array: ";
    for (int i = 0; i < 5; i++) {
        cout << (*ptr)[i] << " ";
    }
    cout << endl;
    cout << endl;
    
    // Pointer to 2D array
    cout << "Pointer to 2D Array:" << endl;
    int matrix[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    
    int (*matrixPtr)[3] = matrix;  // Pointer to array of 3 ints
    
    cout << "2D Array through pointer:" << endl;
    for (int i = 0; i < 2; i++) {
        cout << "   ";
        for (int j = 0; j < 3; j++) {
            cout << matrixPtr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// ==============================================================================
// SECTION 7: FUNCTION POINTERS
// ==============================================================================
/*
 * FUNCTION POINTERS:
 * 
 * Pointers that point to functions instead of data.
 * 
 * Syntax: returnType (*ptrName)(paramTypes);
 * 
 * Uses:
 * - Callbacks
 * - Implementing strategy pattern
 * - Event handlers
 * - Plugin systems
 */

// Sample functions for function pointer demonstration
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

// Function that takes function pointer as parameter
int calculate(int a, int b, int (*operation)(int, int)) {
    return operation(a, b);
}

void functionPointers() {
    cout << "=== FUNCTION POINTERS ===" << endl << endl;
    
    // Declaring and using function pointer
    cout << "1. Basic Function Pointer:" << endl;
    int (*funcPtr)(int, int);  // Pointer to function taking two ints, returning int
    
    funcPtr = add;  // Point to add function
    cout << "   Using add: 5 + 3 = " << funcPtr(5, 3) << endl;
    
    funcPtr = subtract;  // Point to subtract function
    cout << "   Using subtract: 5 - 3 = " << funcPtr(5, 3) << endl;
    
    funcPtr = multiply;  // Point to multiply function
    cout << "   Using multiply: 5 * 3 = " << funcPtr(5, 3) << endl;
    cout << endl;
    
    // Function pointer as parameter
    cout << "2. Function Pointer as Parameter:" << endl;
    cout << "   calculate(10, 5, add) = " << calculate(10, 5, add) << endl;
    cout << "   calculate(10, 5, subtract) = " << calculate(10, 5, subtract) << endl;
    cout << "   calculate(10, 5, multiply) = " << calculate(10, 5, multiply) << endl;
    cout << endl;
    
    // Array of function pointers
    cout << "3. Array of Function Pointers:" << endl;
    int (*operations[3])(int, int) = {add, subtract, multiply};
    const char* names[3] = {"Addition", "Subtraction", "Multiplication"};
    
    for (int i = 0; i < 3; i++) {
        cout << "   " << names[i] << ": 8 and 4 = " << operations[i](8, 4) << endl;
    }
    cout << endl;
}

// ==============================================================================
// SECTION 8: POINTERS TO STRUCTURES
// ==============================================================================
/*
 * POINTERS TO STRUCTURES:
 * 
 * Two ways to access structure members through pointer:
 * 1. (*ptr).member  (dereference then access)
 * 2. ptr->member    (arrow operator - shorthand)
 * 
 * Arrow operator (->) is preferred for readability.
 */

struct Student {
    string name;
    int age;
    float gpa;
};

void pointersToStructures() {
    cout << "=== POINTERS TO STRUCTURES ===" << endl << endl;
    
    // Stack-allocated structure
    cout << "1. Pointer to Stack Structure:" << endl;
    Student student1 = {"Alice", 20, 3.8};
    Student* ptr1 = &student1;
    
    // Two ways to access members
    cout << "   Using (*ptr).member syntax:" << endl;
    cout << "   Name: " << (*ptr1).name << endl;
    cout << "   Age: " << (*ptr1).age << endl;
    cout << endl;
    
    cout << "   Using ptr->member syntax (preferred):" << endl;
    cout << "   Name: " << ptr1->name << endl;
    cout << "   Age: " << ptr1->age << endl;
    cout << "   GPA: " << ptr1->gpa << endl;
    cout << endl;
    
    // Modifying through pointer
    cout << "2. Modifying Structure Through Pointer:" << endl;
    ptr1->age = 21;
    ptr1->gpa = 3.9;
    cout << "   Updated age: " << student1.age << endl;
    cout << "   Updated GPA: " << student1.gpa << endl;
    cout << endl;
    
    // Dynamic structure allocation
    cout << "3. Dynamic Structure Allocation:" << endl;
    Student* ptr2 = new Student{"Bob", 22, 3.5};
    cout << "   Name: " << ptr2->name << endl;
    cout << "   Age: " << ptr2->age << endl;
    cout << "   GPA: " << ptr2->gpa << endl;
    
    delete ptr2;
    ptr2 = nullptr;
    cout << "   Structure freed" << endl;
    cout << endl;
    
    // Array of structures with pointers
    cout << "4. Array of Structures:" << endl;
    Student* students = new Student[3]{
        {"Charlie", 19, 3.6},
        {"Diana", 21, 3.9},
        {"Eve", 20, 3.7}
    };
    
    cout << "   Students:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "   " << (students + i)->name << " - Age: " 
             << (students + i)->age << ", GPA: " 
             << (students + i)->gpa << endl;
    }
    
    delete[] students;
    cout << endl;
}

// ==============================================================================
// SECTION 9: MEMORY MANAGEMENT BEST PRACTICES
// ==============================================================================
/*
 * MEMORY MANAGEMENT RULES:
 * 
 * 1. Every 'new' must have exactly one 'delete'
 * 2. Use 'delete[]' for arrays allocated with 'new[]'
 * 3. Set pointers to nullptr after deletion
 * 4. Check for nullptr before dereferencing
 * 5. Avoid memory leaks (losing pointer before deletion)
 * 6. Avoid double deletion (deleting same pointer twice)
 * 7. Consider using smart pointers (advanced topic)
 */

void memoryManagementBestPractices() {
    cout << "=== MEMORY MANAGEMENT BEST PRACTICES ===" << endl << endl;
    
    // Rule 1: Every new has a delete
    cout << "1. Every 'new' Needs a 'delete':" << endl;
    int* ptr1 = new int(42);
    cout << "   Allocated: " << *ptr1 << endl;
    delete ptr1;
    ptr1 = nullptr;
    cout << "   Freed and set to nullptr" << endl;
    cout << endl;
    
    // Rule 2: Use delete[] for arrays
    cout << "2. Use 'delete[]' for Arrays:" << endl;
    int* arr = new int[5]{1, 2, 3, 4, 5};
    cout << "   Array allocated" << endl;
    delete[] arr;  // Correct for arrays!
    arr = nullptr;
    cout << "   Array freed with delete[]" << endl;
    cout << endl;
    
    // Rule 3: Check before use
    cout << "3. Check for nullptr Before Use:" << endl;
    int* ptr2 = nullptr;
    if (ptr2 != nullptr) {
        cout << "   Value: " << *ptr2 << endl;
    } else {
        cout << "   Pointer is null, not dereferencing" << endl;
    }
    cout << endl;
    
    // Rule 4: Avoid memory leaks
    cout << "4. Avoiding Memory Leaks:" << endl;
    int* ptr3 = new int(100);
    cout << "   Allocated memory" << endl;
    // DON'T: ptr3 = nullptr;  (loses address, causes leak!)
    delete ptr3;  // DO: Free first
    ptr3 = nullptr;  // Then set to nullptr
    cout << "   Properly freed" << endl;
    cout << endl;
    
    // Rule 5: Avoid double deletion
    cout << "5. Avoiding Double Deletion:" << endl;
    int* ptr4 = new int(200);
    delete ptr4;
    ptr4 = nullptr;  // Setting to nullptr prevents accidental double delete
    // delete ptr4;  // Safe now - deleting nullptr is allowed and does nothing
    cout << "   Pointer set to nullptr after delete (safe)" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 10: COMMON PITFALLS
// ==============================================================================
/*
 * COMMON INTERMEDIATE POINTER MISTAKES:
 * 
 * 1. Memory leaks
 * 2. Dangling pointers
 * 3. Double deletion
 * 4. Mixing delete and delete[]
 * 5. Returning pointer to local variable
 * 6. Buffer overflows
 */

// WRONG: Returns pointer to local variable
int* badFunction() {
    int localVar = 42;
    return &localVar;  // DANGER! localVar is destroyed when function returns
}

// CORRECT: Returns dynamically allocated memory
int* goodFunction() {
    int* ptr = new int(42);
    return ptr;  // OK, but caller must delete this
}

void commonPitfalls() {
    cout << "=== COMMON PITFALLS ===" << endl << endl;
    
    // Pitfall 1: Memory leak
    cout << "1. Memory Leak (WRONG):" << endl;
    int* leak = new int(42);
    // leak = nullptr;  // WRONG! Lost the address without freeing
    delete leak;  // CORRECT!
    leak = nullptr;
    cout << "   Fixed: Always delete before reassigning" << endl;
    cout << endl;
    
    // Pitfall 2: Dangling pointer
    cout << "2. Dangling Pointer:" << endl;
    int* ptr = new int(100);
    delete ptr;
    // cout << *ptr;  // DANGER! Pointer is dangling (points to freed memory)
    ptr = nullptr;  // SOLUTION: Set to nullptr after delete
    cout << "   Fixed: Set to nullptr after delete" << endl;
    cout << endl;
    
    // Pitfall 3: Double deletion
    cout << "3. Double Deletion (WRONG):" << endl;
    int* ptr2 = new int(200);
    delete ptr2;
    // delete ptr2;  // DANGER! Double deletion causes crash
    ptr2 = nullptr;
    delete ptr2;  // Safe: deleting nullptr does nothing
    cout << "   Fixed: Setting to nullptr prevents double delete" << endl;
    cout << endl;
    
    // Pitfall 4: Mixing delete and delete[]
    cout << "4. Mixing delete and delete[] (WRONG):" << endl;
    int* arr = new int[5];
    // delete arr;  // WRONG! Should use delete[]
    delete[] arr;  // CORRECT!
    cout << "   Fixed: Use delete[] for arrays" << endl;
    cout << endl;
    
    // Pitfall 5: Pointer to local variable
    cout << "5. Returning Pointer to Local Variable:" << endl;
    // int* bad = badFunction();  // DANGER!
    int* good = goodFunction();    // OK, but must delete
    cout << "   Value: " << *good << endl;
    delete good;
    cout << "   Fixed: Use dynamic allocation or pass by reference" << endl;
    cout << endl;
}

// ==============================================================================
// MAIN FUNCTION - RUNS ALL EXAMPLES
// ==============================================================================

int main() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║        POINTER INTERMEDIATE TUTORIAL - C++                 ║" << endl;
    cout << "║                                                            ║" << endl;
    cout << "║  Master dynamic memory and advanced pointer concepts       ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    cout << "\n";
    
    dynamicMemoryBasics();
    dynamicArrays();
    doublePointers();
    twoDimensionalArrays();
    arrayOfPointers();
    pointerToArray();
    functionPointers();
    pointersToStructures();
    memoryManagementBestPractices();
    commonPitfalls();
    
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║  End of Pointer Intermediate Tutorial                      ║" << endl;
    cout << "║  Next: Move on to pointer_advanced.cpp                     ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    
    return 0;
}

