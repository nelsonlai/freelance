/*
 * Lesson 6.1: Pointers Fundamentals
 * 
 * This file demonstrates pointer concepts, operations,
 * arithmetic, and dynamic memory allocation.
 */

#include <iostream>
#include <memory>
#include <vector>

// Function to demonstrate basic pointer concepts
void demonstrateBasicPointers() {
    std::cout << "=== Basic Pointers Demonstration ===" << std::endl;
    
    int x = 42;
    int* ptr = &x;
    
    std::cout << "Variable x: " << x << std::endl;
    std::cout << "Address of x: " << &x << std::endl;
    std::cout << "Pointer ptr: " << ptr << std::endl;
    std::cout << "Value at ptr: " << *ptr << std::endl;
    
    // Modify through pointer
    *ptr = 100;
    std::cout << "After modification through pointer: x = " << x << std::endl;
    
    // Pointer to different types
    char c = 'A';
    char* char_ptr = &c;
    std::cout << "Char: " << c << ", Address: " << (void*)char_ptr << std::endl;
    
    double d = 3.14159;
    double* double_ptr = &d;
    std::cout << "Double: " << d << ", Address: " << double_ptr << std::endl;
}

// Function to demonstrate pointer arithmetic
void demonstratePointerArithmetic() {
    std::cout << "=== Pointer Arithmetic Demonstration ===" << std::endl;
    
    int arr[5] = {10, 20, 30, 40, 50};
    int* ptr = arr;
    
    std::cout << "Array elements using pointer arithmetic:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "arr[" << i << "] = " << *(ptr + i) 
                  << " (address: " << (ptr + i) << ")" << std::endl;
    }
    
    // Pointer arithmetic operations
    std::cout << "=== Pointer Arithmetic Demonstration ===" << std::endl;
    std::cout << "Pointer arithmetic operations:" << std::endl;
    std::cout << "Initial ptr: " << ptr << std::endl;
    
    ptr++;
    std::cout << "After ptr++: " << ptr << " (value: " << *ptr << ")" << std::endl;
    
    ptr += 2;
    std::cout << "After ptr += 2: " << ptr << " (value: " << *ptr << ")" << std::endl;
    
    ptr--;
    std::cout << "After ptr--: " << ptr << " (value: " << *ptr << ")" << std::endl;
    
    // Pointer difference
    int* start = arr;
    int* end = arr + 5;
    std::ptrdiff_t diff = end - start;
    std::cout << "Pointer difference: " << diff << std::endl;
}

// Function to demonstrate dynamic memory allocation
void demonstrateDynamicMemory() {
    std::cout << "=== Dynamic Memory Allocation Demonstration ===" << std::endl;
    
    // Single object allocation
    int* single_ptr = new int(42);
    std::cout << "Single object: " << *single_ptr << std::endl;
    delete single_ptr;
    
    // Array allocation
    int size = 5;
    int* array_ptr = new int[size];
    
    // Initialize array
    for (int i = 0; i < size; ++i) {
        array_ptr[i] = i * 10;
    }
    
    std::cout << "Dynamic array:" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << "array_ptr[" << i << "] = " << array_ptr[i] << std::endl;
    }
    
    delete[] array_ptr;
    
    // Allocation with error checking
    std::cout << "=== Allocation with error checking:" << std::endl;
    std::cout << "Allocation with error checking:" << std::endl;
    int* safe_ptr = new(std::nothrow) int[1000000];
    if (safe_ptr == nullptr) {
        std::cout << "Allocation failed!" << std::endl;
    } else {
        std::cout << "Allocation successful!" << std::endl;
        delete[] safe_ptr;
    }
}

// Function to demonstrate pointer to pointer
void demonstratePointerToPointer() {
    std::cout << "=== Pointer to Pointer Demonstration ===" << std::endl;
    
    int x = 42;
    int* ptr1 = &x;
    int** ptr2 = &ptr1;
    
    std::cout << "Variable x: " << x << std::endl;
    std::cout << "Address of x: " << &x << std::endl;
    std::cout << "ptr1: " << ptr1 << " (points to x)" << std::endl;
    std::cout << "ptr2: " << ptr2 << " (points to ptr1)" << std::endl;
    
    std::cout << "=== Accessing through different levels:" << std::endl;
    std::cout << "Direct access: " << x << std::endl;
    std::cout << "Single indirection: " << *ptr1 << std::endl;
    std::cout << "Double indirection: " << **ptr2 << std::endl;
    
    // Modify through different levels
    **ptr2 = 100;
    std::cout << "After **ptr2 = 100: x = " << x << std::endl;
}

// Function to demonstrate pointer arrays
void demonstratePointerArrays() {
    std::cout << "=== Pointer Arrays Demonstration ===" << std::endl;
    
    // Array of pointers
    int a = 10, b = 20, c = 30;
    int* ptr_array[3] = {&a, &b, &c};
    
    std::cout << "Array of pointers:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << "ptr_array[" << i << "] = " << ptr_array[i] 
                  << " (value: " << *ptr_array[i] << ")" << std::endl;
    }
    
    // Modify through pointer array
    *ptr_array[1] = 200;
    std::cout << "After *ptr_array[1] = 200: b = " << b << std::endl;
    
    // Array of function pointers
    auto add = [](int a, int b) -> int { return a + b; };
    auto multiply = [](int a, int b) -> int { return a * b; };
    auto subtract = [](int a, int b) -> int { return a - b; };
    
    int (*func_ptr_array[3])(int, int) = {add, multiply, subtract};
    
    std::cout << "=== Function pointer array:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        int result = func_ptr_array[i](10, 5);
        std::cout << "Function " << i << " result: " << result << std::endl;
    }
}

// Function to demonstrate pointer safety
void demonstratePointerSafety() {
    std::cout << "=== Pointer Safety Demonstration ===" << std::endl;
    
    // Safe pointer usage
    int* ptr = new int(42);
    
    if (ptr != nullptr) {
        std::cout << "Pointer is valid: " << *ptr << std::endl;
        delete ptr;
        ptr = nullptr;  // Prevent dangling pointer
        
        if (ptr == nullptr) {
            std::cout << "Pointer set to nullptr after deletion" << std::endl;
        }
    }
    
    // Smart pointer usage
    std::cout << "=== Smart pointer usage:" << std::endl;
    std::unique_ptr<int> smart_ptr = std::make_unique<int>(100);
    std::cout << "Smart pointer value: " << *smart_ptr << std::endl;
    // Automatic cleanup when smart_ptr goes out of scope
}

// Function to demonstrate pointer comparison
void demonstratePointerComparison() {
    std::cout << "=== Pointer Comparison Demonstration ===" << std::endl;
    
    int arr[5] = {1, 2, 3, 4, 5};
    int* ptr1 = arr;
    int* ptr2 = arr + 2;
    int* ptr3 = arr + 4;
    
    std::cout << "Pointer comparison:" << std::endl;
    std::cout << "ptr1: " << ptr1 << " (value: " << *ptr1 << ")" << std::endl;
    std::cout << "ptr2: " << ptr2 << " (value: " << *ptr2 << ")" << std::endl;
    std::cout << "ptr3: " << ptr3 << " (value: " << *ptr3 << ")" << std::endl;
    
    std::cout << "=== Comparisons:" << std::endl;
    std::cout << "ptr1 < ptr2: " << (ptr1 < ptr2) << std::endl;
    std::cout << "ptr2 < ptr3: " << (ptr2 < ptr3) << std::endl;
    std::cout << "ptr1 == ptr1: " << (ptr1 == ptr1) << std::endl;
    std::cout << "ptr1 != ptr2: " << (ptr1 != ptr2) << std::endl;
}

// Function to demonstrate const pointers
void demonstrateConstPointers() {
    std::cout << "=== Const Pointers Demonstration ===" << std::endl;
    
    int x = 42;
    int y = 100;
    
    // Pointer to const
    const int* ptr_to_const = &x;
    std::cout << "Pointer to const: " << *ptr_to_const << std::endl;
    // *ptr_to_const = 50;  // Error: cannot modify through const pointer
    ptr_to_const = &y;  // OK: can change what pointer points to
    
    // Const pointer
    int* const const_ptr = &x;
    std::cout << "Const pointer: " << *const_ptr << std::endl;
    *const_ptr = 50;  // OK: can modify value
    // const_ptr = &y;  // Error: cannot change what pointer points to
    
    // Const pointer to const
    const int* const both_const = &x;
    std::cout << "Const pointer to const: " << *both_const << std::endl;
    // *both_const = 60;  // Error: cannot modify value
    // both_const = &y;   // Error: cannot change what pointer points to
}

// Function to demonstrate void pointers
void demonstrateVoidPointers() {
    std::cout << "=== Void Pointers Demonstration ===" << std::endl;
    
    int int_val = 42;
    double double_val = 3.14159;
    char char_val = 'A';
    
    void* void_ptr;
    
    // Point to different types
    void_ptr = &int_val;
    std::cout << "Void pointer to int: " << *(int*)void_ptr << std::endl;
    
    void_ptr = &double_val;
    std::cout << "Void pointer to double: " << *(double*)void_ptr << std::endl;
    
    void_ptr = &char_val;
    std::cout << "Void pointer to char: " << *(char*)void_ptr << std::endl;
    
    // Note: void pointers cannot be dereferenced directly
    // Must be cast to appropriate type first
}

int main() {
    std::cout << "=== Pointers Fundamentals Demonstration ===" << std::endl;
    std::cout << "This program demonstrates pointer concepts, operations,"
              << "arithmetic, and dynamic memory allocation." << std::endl;
    
    // Demonstrate various pointer concepts
    demonstrateBasicPointers();
    demonstratePointerArithmetic();
    demonstrateDynamicMemory();
    demonstratePointerToPointer();
    demonstratePointerArrays();
    demonstratePointerSafety();
    demonstratePointerComparison();
    demonstrateConstPointers();
    demonstrateVoidPointers();
    
    std::cout << "=== Key Takeaways ===" << std::endl;
    std::cout << "1. Pointers store memory addresses" << std::endl;
    std::cout << "2. Pointer arithmetic allows navigation through memory" << std::endl;
    std::cout << "3. Dynamic memory allocation enables runtime memory management" << std::endl;
    std::cout << "4. Pointer safety is crucial to prevent crashes" << std::endl;
    std::cout << "5. Smart pointers provide automatic memory management" << std::endl;
    std::cout << "6. Const pointers prevent accidental modifications" << std::endl;
    std::cout << "7. Void pointers provide type-erased storage" << std::endl;
    
    std::cout << "Program completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o pointers_fundamentals 01_Pointers_Fundamentals.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o pointers_fundamentals 01_Pointers_Fundamentals.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 01_Pointers_Fundamentals.cpp
 * 
 * Running:
 * ./pointers_fundamentals (Linux/macOS)
 * pointers_fundamentals.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for smart pointers.
 * C++17 is recommended for best pointer support.
 * 
 * Pointer Notes:
 * - Always initialize pointers
 * - Check for null before dereferencing
 * - Use smart pointers when possible
 * - Be careful with pointer arithmetic
 * - Match new with delete, new[] with delete[]
 */