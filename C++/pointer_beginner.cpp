/*
 * POINTER BEGINNER EXAMPLES
 * 
 * This file demonstrates basic pointer concepts for beginners:
 * - What are pointers and why do we need them?
 * - Basic pointer declaration and initialization
 * - Pointer operators (* and &)
 * - Pointer arithmetic basics
 * - Arrays and pointers relationship
 * - Common beginner mistakes and how to avoid them
 * 
 * Learning Objectives:
 * - Understand what pointers are and how they work
 * - Learn pointer syntax and basic operations
 * - Understand memory addresses and dereferencing
 * - Learn the relationship between arrays and pointers
 * - Avoid common pointer pitfalls
 * 
 * Prerequisites:
 * - Basic understanding of variables and data types
 * - Familiarity with basic C++ syntax
 * - Understanding of memory concept (basic)
 * 
 * Key Topics Covered:
 * - Pointer declaration and initialization
 * - Address-of operator (&)
 * - Dereference operator (*)
 * - NULL and nullptr
 * - Pointer arithmetic
 * - Arrays and pointers
 */

#include <iostream>
#include <string>
using namespace std;

// ==============================================================================
// SECTION 1: WHAT IS A POINTER?
// ==============================================================================
/*
 * A POINTER is a variable that stores the MEMORY ADDRESS of another variable.
 * 
 * Think of it like this:
 * - A regular variable is like a box that holds a value
 * - A pointer is like a note that tells you WHERE to find that box
 * 
 * Why do we need pointers?
 * 1. Dynamic memory allocation (allocate memory at runtime)
 * 2. Efficient passing of large data structures to functions
 * 3. Building complex data structures (linked lists, trees, etc.)
 * 4. Direct memory manipulation for system programming
 */

void whatIsPointer() {
    cout << "=== WHAT IS A POINTER? ===" << endl << endl;
    
    // Regular variable - stores a value
    int age = 25;
    
    // Pointer variable - stores a memory address
    // Syntax: type* pointerName;
    int* ptr = &age;  // ptr stores the ADDRESS of age
    
    cout << "Value of age: " << age << endl;
    cout << "Address of age: " << &age << endl;  // & = "address of" operator
    cout << "Value of ptr (address it points to): " << ptr << endl;
    cout << "Value at the address ptr points to: " << *ptr << endl;  // * = "dereference" operator
    cout << endl;
}

// ==============================================================================
// SECTION 2: POINTER DECLARATION AND INITIALIZATION
// ==============================================================================
/*
 * DECLARING POINTERS:
 * Syntax: dataType* pointerName;
 * 
 * The * indicates that this is a pointer variable.
 * The dataType tells what type of data it points to.
 * 
 * IMPORTANT: Always initialize pointers!
 * Uninitialized pointers contain garbage addresses and can cause crashes.
 */

void pointerDeclaration() {
    cout << "=== POINTER DECLARATION AND INITIALIZATION ===" << endl << endl;
    
    // Method 1: Declare and initialize separately
    int number = 42;
    int* ptr1;           // Declaration (dangerous if not initialized immediately)
    ptr1 = &number;      // Initialization with address of number
    
    // Method 2: Declare and initialize together (RECOMMENDED)
    int value = 100;
    int* ptr2 = &value;  // Better: declare and initialize in one line
    
    // Method 3: Initialize with nullptr (C++11)
    int* ptr3 = nullptr; // ptr3 doesn't point to anything yet (safe)
    
    // Method 4: Initialize with NULL (old C style, still valid)
    int* ptr4 = NULL;    // NULL is 0 (use nullptr instead in modern C++)
    
    cout << "ptr1 points to: " << *ptr1 << endl;
    cout << "ptr2 points to: " << *ptr2 << endl;
    cout << "ptr3 is: " << ptr3 << " (nullptr)" << endl;
    cout << "ptr4 is: " << ptr4 << " (NULL)" << endl;
    
    // Different data types
    double pi = 3.14159;
    double* doublePtr = &pi;
    
    char letter = 'A';
    char* charPtr = &letter;
    
    string name = "John";
    string* stringPtr = &name;
    
    cout << "\nDifferent pointer types:" << endl;
    cout << "Double pointer: " << *doublePtr << endl;
    cout << "Char pointer: " << *charPtr << endl;
    cout << "String pointer: " << *stringPtr << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 3: ADDRESS-OF OPERATOR (&)
// ==============================================================================
/*
 * The ADDRESS-OF OPERATOR (&) returns the memory address of a variable.
 * 
 * Think of it as: "Give me the address where this variable lives in memory"
 * 
 * Syntax: &variableName
 * 
 * Every variable in your program has:
 * 1. A VALUE (what it stores)
 * 2. An ADDRESS (where it's stored in memory)
 */

void addressOfOperator() {
    cout << "=== ADDRESS-OF OPERATOR (&) ===" << endl << endl;
    
    int x = 10;
    int y = 20;
    int z = 30;
    
    // Print values
    cout << "Values:" << endl;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
    cout << "z = " << z << endl;
    cout << endl;
    
    // Print addresses (note: addresses are different on each run)
    cout << "Addresses (in memory):" << endl;
    cout << "Address of x: " << &x << endl;
    cout << "Address of y: " << &y << endl;
    cout << "Address of z: " << &z << endl;
    cout << endl;
    
    // Store addresses in pointers
    int* ptrX = &x;
    int* ptrY = &y;
    int* ptrZ = &z;
    
    cout << "Pointers storing these addresses:" << endl;
    cout << "ptrX = " << ptrX << " (points to x)" << endl;
    cout << "ptrY = " << ptrY << " (points to y)" << endl;
    cout << "ptrZ = " << ptrZ << " (points to z)" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 4: DEREFERENCE OPERATOR (*)
// ==============================================================================
/*
 * The DEREFERENCE OPERATOR (*) accesses the value at the address stored in a pointer.
 * 
 * Think of it as: "Go to this address and get me the value stored there"
 * 
 * Syntax: *pointerName
 * 
 * Note: * has TWO different meanings in pointer context:
 * 1. In declaration: int* ptr;  (this is a pointer)
 * 2. In expression: *ptr;       (dereference - get the value)
 */

void dereferenceOperator() {
    cout << "=== DEREFERENCE OPERATOR (*) ===" << endl << endl;
    
    int score = 95;
    int* ptr = &score;
    
    cout << "Original variable:" << endl;
    cout << "score = " << score << endl;
    cout << "Address of score = " << &score << endl;
    cout << endl;
    
    cout << "Pointer variable:" << endl;
    cout << "ptr = " << ptr << " (address it stores)" << endl;
    cout << "*ptr = " << *ptr << " (value at that address)" << endl;
    cout << endl;
    
    // Modifying value through pointer (IMPORTANT CONCEPT)
    cout << "Modifying value through pointer:" << endl;
    *ptr = 100;  // Change the value at the address ptr points to
    
    cout << "After *ptr = 100:" << endl;
    cout << "score = " << score << " (changed!)" << endl;
    cout << "*ptr = " << *ptr << " (also changed)" << endl;
    cout << endl;
    
    // This demonstrates that ptr and score refer to the SAME memory location
    cout << "Key insight: ptr and &score are the same:" << endl;
    cout << "ptr == &score? " << (ptr == &score ? "YES" : "NO") << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 5: POINTER VISUALIZATION
// ==============================================================================
/*
 * Let's visualize how pointers work in memory:
 * 
 * Memory Address    Variable    Value
 * ---------------   --------    -----
 * 0x1000           num         42
 * 0x2000           ptr         0x1000  (points to num)
 * 
 * When we do: int num = 42;
 *             int* ptr = &num;
 * 
 * - num is stored at address 0x1000 and holds value 42
 * - ptr is stored at address 0x2000 and holds value 0x1000 (address of num)
 */

void pointerVisualization() {
    cout << "=== POINTER VISUALIZATION ===" << endl << endl;
    
    int num = 42;
    int* ptr = &num;
    
    // Let's look at all the information
    cout << "Variable 'num':" << endl;
    cout << "  Value of num: " << num << endl;
    cout << "  Address of num: " << &num << endl;
    cout << "  Size of num: " << sizeof(num) << " bytes" << endl;
    cout << endl;
    
    cout << "Pointer 'ptr':" << endl;
    cout << "  Value of ptr (address it stores): " << ptr << endl;
    cout << "  Address of ptr itself: " << &ptr << endl;
    cout << "  Value pointed to by ptr: " << *ptr << endl;
    cout << "  Size of ptr: " << sizeof(ptr) << " bytes" << endl;
    cout << endl;
    
    cout << "Verification:" << endl;
    cout << "  ptr == &num? " << (ptr == &num ? "YES" : "NO") << endl;
    cout << "  *ptr == num? " << (*ptr == num ? "YES" : "NO") << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 6: NULLPTR vs NULL
// ==============================================================================
/*
 * nullptr (C++11) is the modern way to represent a null pointer.
 * NULL is the old C-style way (actually just #define NULL 0).
 * 
 * ALWAYS use nullptr in modern C++!
 * 
 * A null pointer doesn't point to any valid memory location.
 * It's used to indicate "this pointer doesn't point to anything yet".
 */

void nullPointers() {
    cout << "=== NULL vs nullptr ===" << endl << endl;
    
    // Old way (C-style)
    int* ptr1 = NULL;
    
    // New way (C++11 and later) - RECOMMENDED
    int* ptr2 = nullptr;
    
    cout << "ptr1 (NULL): " << ptr1 << endl;
    cout << "ptr2 (nullptr): " << ptr2 << endl;
    cout << endl;
    
    // Checking if pointer is null
    if (ptr2 == nullptr) {
        cout << "ptr2 is a null pointer (doesn't point to anything)" << endl;
    }
    
    // Before dereferencing, ALWAYS check if pointer is not null
    int value = 100;
    int* ptr3 = &value;
    
    if (ptr3 != nullptr) {
        cout << "ptr3 is valid, dereferencing: " << *ptr3 << endl;
    }
    
    // WARNING: Never dereference a null pointer!
    // This would crash your program:
    // int* badPtr = nullptr;
    // cout << *badPtr;  // CRASH! Undefined behavior!
    
    cout << endl;
}

// ==============================================================================
// SECTION 7: POINTER ARITHMETIC
// ==============================================================================
/*
 * POINTER ARITHMETIC allows you to perform mathematical operations on pointers.
 * 
 * When you add/subtract from a pointer, it moves by the SIZE of the data type.
 * 
 * For example, if ptr points to an int (4 bytes):
 * - ptr + 1 moves forward by 4 bytes (one int)
 * - ptr + 2 moves forward by 8 bytes (two ints)
 * 
 * Allowed operations:
 * - ptr + n, ptr - n (move forward/backward)
 * - ptr++, ptr-- (increment/decrement)
 * - ptr1 - ptr2 (distance between two pointers)
 */

void pointerArithmetic() {
    cout << "=== POINTER ARITHMETIC ===" << endl << endl;
    
    int numbers[5] = {10, 20, 30, 40, 50};
    int* ptr = numbers;  // Points to first element
    
    cout << "Array: ";
    for (int i = 0; i < 5; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl << endl;
    
    // Accessing elements using pointer arithmetic
    cout << "Using pointer arithmetic:" << endl;
    cout << "*ptr = " << *ptr << " (first element)" << endl;
    cout << "*(ptr + 1) = " << *(ptr + 1) << " (second element)" << endl;
    cout << "*(ptr + 2) = " << *(ptr + 2) << " (third element)" << endl;
    cout << "*(ptr + 3) = " << *(ptr + 3) << " (fourth element)" << endl;
    cout << "*(ptr + 4) = " << *(ptr + 4) << " (fifth element)" << endl;
    cout << endl;
    
    // Incrementing pointer
    cout << "Incrementing pointer:" << endl;
    ptr = numbers;  // Reset to start
    for (int i = 0; i < 5; i++) {
        cout << "Address: " << ptr << ", Value: " << *ptr << endl;
        ptr++;  // Move to next element
    }
    cout << endl;
    
    // Pointer subtraction
    int* start = numbers;
    int* end = &numbers[4];
    cout << "Distance between start and end: " << (end - start) << " elements" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 8: ARRAYS AND POINTERS
// ==============================================================================
/*
 * IMPORTANT RELATIONSHIP: Arrays and pointers are closely related!
 * 
 * - An array name is essentially a pointer to its first element
 * - arr[i] is equivalent to *(arr + i)
 * - &arr[i] is equivalent to (arr + i)
 * 
 * Key differences:
 * - Array name is a CONSTANT pointer (can't be reassigned)
 * - Pointer is a variable (can be reassigned)
 */

void arraysAndPointers() {
    cout << "=== ARRAYS AND POINTERS ===" << endl << endl;
    
    int arr[5] = {100, 200, 300, 400, 500};
    int* ptr = arr;  // arr decays to pointer to first element
    
    cout << "Array name as pointer:" << endl;
    cout << "arr = " << arr << " (address of first element)" << endl;
    cout << "&arr[0] = " << &arr[0] << " (same as arr)" << endl;
    cout << "ptr = " << ptr << " (same as arr)" << endl;
    cout << endl;
    
    // Accessing array elements - multiple ways
    cout << "Different ways to access array elements:" << endl;
    cout << "Method 1 - Array subscript: arr[0] = " << arr[0] << endl;
    cout << "Method 2 - Pointer dereference: *arr = " << *arr << endl;
    cout << "Method 3 - Pointer variable: *ptr = " << *ptr << endl;
    cout << "Method 4 - Pointer arithmetic: *(arr + 0) = " << *(arr + 0) << endl;
    cout << endl;
    
    // Accessing second element
    cout << "Accessing second element (different ways):" << endl;
    cout << "arr[1] = " << arr[1] << endl;
    cout << "*(arr + 1) = " << *(arr + 1) << endl;
    cout << "ptr[1] = " << ptr[1] << endl;
    cout << "*(ptr + 1) = " << *(ptr + 1) << endl;
    cout << endl;
    
    // Traversing array with pointer
    cout << "Traversing array with pointer:" << endl;
    ptr = arr;  // Reset pointer to start
    for (int i = 0; i < 5; i++) {
        cout << "Element " << i << ": " << *ptr << endl;
        ptr++;
    }
    cout << endl;
}

// ==============================================================================
// SECTION 9: POINTERS AND FUNCTIONS
// ==============================================================================
/*
 * Pointers allow functions to modify variables from the calling function.
 * This is called "pass by reference" (using pointers).
 * 
 * Without pointers: Pass by value (function gets a COPY)
 * With pointers: Function can modify the original variable
 */

// Pass by value - function gets a copy
void incrementByValue(int x) {
    x++;  // Only modifies the copy
    cout << "  Inside incrementByValue: x = " << x << endl;
}

// Pass by pointer - function can modify original
void incrementByPointer(int* ptr) {
    (*ptr)++;  // Modifies the original variable
    cout << "  Inside incrementByPointer: *ptr = " << *ptr << endl;
}

// Swap two numbers using pointers
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void pointersAndFunctions() {
    cout << "=== POINTERS AND FUNCTIONS ===" << endl << endl;
    
    // Pass by value example
    int num1 = 10;
    cout << "Before incrementByValue: num1 = " << num1 << endl;
    incrementByValue(num1);
    cout << "After incrementByValue: num1 = " << num1 << " (unchanged!)" << endl;
    cout << endl;
    
    // Pass by pointer example
    int num2 = 10;
    cout << "Before incrementByPointer: num2 = " << num2 << endl;
    incrementByPointer(&num2);  // Pass address of num2
    cout << "After incrementByPointer: num2 = " << num2 << " (changed!)" << endl;
    cout << endl;
    
    // Swap example
    int x = 5, y = 10;
    cout << "Before swap: x = " << x << ", y = " << y << endl;
    swap(&x, &y);
    cout << "After swap: x = " << x << ", y = " << y << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 10: COMMON MISTAKES AND HOW TO AVOID THEM
// ==============================================================================
/*
 * COMMON POINTER MISTAKES (BEGINNERS BEWARE!):
 * 
 * 1. Uninitialized pointers (dangling pointers)
 * 2. Dereferencing null pointers
 * 3. Memory leaks (with dynamic memory)
 * 4. Pointer to local variable (returns from function)
 * 5. Forgetting to use & when getting address
 */

void commonMistakes() {
    cout << "=== COMMON MISTAKES AND HOW TO AVOID THEM ===" << endl << endl;
    
    // MISTAKE 1: Uninitialized pointer
    cout << "1. Uninitialized Pointer (DANGEROUS):" << endl;
    // int* badPtr;  // Contains garbage address
    // cout << *badPtr;  // CRASH! Undefined behavior!
    cout << "   SOLUTION: Always initialize pointers!" << endl;
    int* goodPtr = nullptr;  // Safe initialization
    cout << "   int* goodPtr = nullptr;" << endl;
    cout << endl;
    
    // MISTAKE 2: Dereferencing null pointer
    cout << "2. Dereferencing Null Pointer (DANGEROUS):" << endl;
    int* nullPtr = nullptr;
    // cout << *nullPtr;  // CRASH!
    cout << "   SOLUTION: Always check before dereferencing!" << endl;
    if (nullPtr != nullptr) {
        cout << *nullPtr;
    } else {
        cout << "   Pointer is null, not dereferencing." << endl;
    }
    cout << endl;
    
    // MISTAKE 3: Confusing pointer and value
    cout << "3. Confusing Pointer and Value:" << endl;
    int value = 42;
    int* ptr = &value;
    cout << "   ptr = " << ptr << " (address)" << endl;     // &value
    cout << "   *ptr = " << *ptr << " (value)" << endl;
    cout << "   Remember: * dereferences, & gets address" << endl;
    cout << endl;
    
    // MISTAKE 4: Modifying through wrong syntax
    cout << "4. Wrong Syntax for Modification:" << endl;
    int num = 10;
    int* p = &num;
    // p = 20;  // WRONG! This tries to change the address
    *p = 20;    // CORRECT! This changes the value
    cout << "   Use *p = 20 to modify value, not p = 20" << endl;
    cout << "   num is now: " << num << endl;
    cout << endl;
    
    // MISTAKE 5: Pointer size confusion
    cout << "5. Pointer Size:" << endl;
    int x = 100;
    int* px = &x;
    cout << "   Size of int: " << sizeof(x) << " bytes" << endl;
    cout << "   Size of pointer: " << sizeof(px) << " bytes" << endl;
    cout << "   (Pointer size depends on system: 4 bytes on 32-bit, 8 bytes on 64-bit)" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 11: CONST AND POINTERS
// ==============================================================================
/*
 * CONST with pointers can be tricky! Three different scenarios:
 * 
 * 1. Pointer to constant: const int* ptr
 *    - Can't change the VALUE through pointer
 *    - Can change WHERE the pointer points
 * 
 * 2. Constant pointer: int* const ptr
 *    - Can change the VALUE through pointer
 *    - Can't change WHERE the pointer points
 * 
 * 3. Constant pointer to constant: const int* const ptr
 *    - Can't change the VALUE
 *    - Can't change WHERE the pointer points
 */

void constAndPointers() {
    cout << "=== CONST AND POINTERS ===" << endl << endl;
    
    int x = 10, y = 20;
    
    // 1. Pointer to constant
    cout << "1. Pointer to Constant (const int* ptr):" << endl;
    const int* ptr1 = &x;
    cout << "   Value: " << *ptr1 << endl;
    // *ptr1 = 15;  // ERROR! Can't modify value
    ptr1 = &y;      // OK! Can change where it points
    cout << "   Changed pointer to point to y: " << *ptr1 << endl;
    cout << endl;
    
    // 2. Constant pointer
    cout << "2. Constant Pointer (int* const ptr):" << endl;
    int* const ptr2 = &x;
    cout << "   Value: " << *ptr2 << endl;
    *ptr2 = 15;     // OK! Can modify value
    // ptr2 = &y;   // ERROR! Can't change where it points
    cout << "   Modified value through pointer: " << *ptr2 << endl;
    cout << endl;
    
    // 3. Constant pointer to constant
    cout << "3. Constant Pointer to Constant (const int* const ptr):" << endl;
    const int* const ptr3 = &x;
    cout << "   Value: " << *ptr3 << endl;
    // *ptr3 = 25;  // ERROR! Can't modify value
    // ptr3 = &y;   // ERROR! Can't change where it points
    cout << "   This pointer can't be changed in any way!" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 12: POINTER BEST PRACTICES
// ==============================================================================
/*
 * BEST PRACTICES FOR USING POINTERS:
 * 
 * 1. Always initialize pointers (use nullptr if no initial value)
 * 2. Check for nullptr before dereferencing
 * 3. Set pointers to nullptr after freeing memory
 * 4. Use meaningful variable names
 * 5. Prefer references over pointers when possible
 * 6. Use smart pointers (covered in advanced) for dynamic memory
 * 7. Document which function owns/manages pointer
 * 8. Be careful with pointer arithmetic
 */

void bestPractices() {
    cout << "=== POINTER BEST PRACTICES ===" << endl << endl;
    
    // Practice 1: Initialize pointers
    int* ptr = nullptr;  // Good: initialized to nullptr
    cout << "1. Always initialize: int* ptr = nullptr;" << endl;
    cout << endl;
    
    // Practice 2: Check before use
    int value = 42;
    ptr = &value;
    if (ptr != nullptr) {  // Good: check before dereferencing
        cout << "2. Check before use: " << *ptr << endl;
    }
    cout << endl;
    
    // Practice 3: Meaningful names
    int studentAge = 20;
    int* studentAgePtr = &studentAge;  // Good: clear name
    cout << "3. Use meaningful names: studentAgePtr" << endl;
    cout << endl;
    
    // Practice 4: Const correctness
    const int maxScore = 100;
    const int* scorePtr = &maxScore;  // Good: const pointer to const data
    cout << "4. Use const when appropriate: const int* scorePtr" << endl;
    cout << endl;
    
    cout << "5. Document ownership and lifetime in comments" << endl;
    cout << "6. Prefer references when you don't need nullptr" << endl;
    cout << "7. Use smart pointers for dynamic memory (see advanced)" << endl;
    cout << endl;
}

// ==============================================================================
// MAIN FUNCTION - RUNS ALL EXAMPLES
// ==============================================================================

int main() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║        POINTER BEGINNER TUTORIAL - C++                     ║" << endl;
    cout << "║                                                            ║" << endl;
    cout << "║  Learn the fundamentals of pointers step by step          ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    cout << "\n";
    
    whatIsPointer();
    pointerDeclaration();
    addressOfOperator();
    dereferenceOperator();
    pointerVisualization();
    nullPointers();
    pointerArithmetic();
    arraysAndPointers();
    pointersAndFunctions();
    commonMistakes();
    constAndPointers();
    bestPractices();
    
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║  End of Pointer Beginner Tutorial                          ║" << endl;
    cout << "║  Next: Move on to pointer_intermediate.cpp                 ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    
    return 0;
}

