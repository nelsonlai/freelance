/*
 * Lesson 6.2: Arrays and Pointers
 * 
 * This file demonstrates array declaration, initialization,
 * array-pointer relationship, and multi-dimensional arrays.
 */

#include <iostream>
#include <algorithm>
#include <numeric>

// Function to demonstrate basic arrays
void demonstrateBasicArrays() {
    std::cout << "=== Basic Arrays Demonstration ===" << std::endl;
    
    // Array declaration and initialization
    int arr[5] = {10, 20, 30, 40, 50};
    
    std::cout << "Array elements:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }
    
    std::cout << "Array size: " << sizeof(arr) / sizeof(arr[0]) << std::endl;
    std::cout << "Total memory: " << sizeof(arr) << " bytes" << std::endl;
    
    // Partial initialization
    int partial_arr[5] = {1, 2};
    std::cout << "Partially initialized array:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "partial_arr[" << i << "] = " << partial_arr[i] << std::endl;
    }
    
    // Array without size specification
    int auto_arr[] = {100, 200, 300};
    std::cout << "Auto-sized array:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << "auto_arr[" << i << "] = " << auto_arr[i] << std::endl;
    }
}

// Function to demonstrate array-pointer relationship
void demonstrateArrayPointerRelationship() {
    std::cout << " === Array-Pointer Relationship ===" << std::endl;
    
    int arr[5] = {1, 2, 3, 4, 5};
    int* ptr = arr;  // arr is equivalent to &arr[0]
    
    std::cout << "Array address: " << arr << std::endl;
    std::cout << "Pointer address: " << ptr << std::endl;
    std::cout << "First element address: " << &arr[0] << std::endl;
    
    std::cout << "Equivalent access methods:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "arr[" << i << "] = " << arr[i] 
                  << ", *(arr + " << i << ") = " << *(arr + i)
                  << ", ptr[" << i << "] = " << ptr[i] 
                  << ", *(ptr + " << i << ") = " << *(ptr + i) << std::endl;
    }
    
    // Array arithmetic
    std::cout << "Array arithmetic:" << std::endl;
    std::cout << "arr + 1: " << arr + 1 << " (points to second element)" << std::endl;
    std::cout << "arr + 2: " << arr + 2 << " (points to third element)" << std::endl;
    std::cout << "arr + 4: " << arr + 4 << " (points to last element)" << std::endl;
}

// Function to demonstrate multi-dimensional arrays
void demonstrateMultiDimensionalArrays() {
    std::cout << "=== Multi-dimensional Arrays ===" << std::endl;
    
    // 2D array
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    std::cout << "2D Array (3x4 matrix):" << std::endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << matrix[i][j] << "	";
        }
        std::cout << std::endl;
    }
    
    // 3D array
    int cube[2][3][4] = {
        {
            {1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12}
        },
        {
            {13, 14, 15, 16},
            {17, 18, 19, 20},
            {21, 22, 23, 24}
        }
    };
    
    std::cout << "3D Array (2x3x4 cube):" << std::endl;

    for (int i = 0; i < 2; ++i) {
        std::cout << "Layer " << i << ":" << std::endl;
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 4; ++k) {
                std::cout << cube[i][j][k] << "	";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

// Function to demonstrate dynamic arrays
void demonstrateDynamicArrays() {
    std::cout << "=== Dynamic Arrays ===" << std::endl;
    
    // Allocate dynamic array
    int size = 5;
    int* dynamic_arr = new int[size];
    
    // Initialize array
    for (int i = 0; i < size; ++i) {
        dynamic_arr[i] = (i + 1) * 10;
    }
    
    std::cout << "Dynamic array:" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << "dynamic_arr[" << i << "] = " << dynamic_arr[i] << std::endl;
    }
    
    // Resize array (create new larger array)
    int new_size = 8;
    int* resized_arr = new int[new_size];
    
    // Copy old elements
    for (int i = 0; i < size; ++i) {
        resized_arr[i] = dynamic_arr[i];
    }
    
    // Initialize new elements
    for (int i = size; i < new_size; ++i) {
        resized_arr[i] = (i + 1) * 10;
    }
    
    std::cout << "=== Dynamic Arrays ===" << std::endl;
    std::cout << "Resized array:" << std::endl;
    for (int i = 0; i < new_size; ++i) {
        std::cout << "resized_arr[" << i << "] = " << resized_arr[i] << std::endl;
    }
    
    // Cleanup
    delete[] dynamic_arr;
    delete[] resized_arr;
}

// Function to demonstrate array algorithms
void demonstrateArrayAlgorithms() {
    std::cout << "=== Array Algorithms ===" << std::endl;
    
    int arr[10] = {64, 34, 25, 12, 22, 11, 90, 5, 77, 30};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    std::cout << "Original array:" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    // Find maximum element
    int max_element = *std::max_element(arr, arr + size);
    std::cout << "Maximum element: " << max_element << std::endl;
    
    // Find minimum element
    int min_element = *std::min_element(arr, arr + size);
    std::cout << "Minimum element: " << min_element << std::endl;
    
    // Calculate sum
    int sum = std::accumulate(arr, arr + size, 0);
    std::cout << "Sum of elements: " << sum << std::endl;
    
    // Sort array
    std::sort(arr, arr + size);
    std::cout << "Sorted array:" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    // Binary search (array must be sorted)
    int target = 25;
    bool found = std::binary_search(arr, arr + size, target);
    std::cout << "Target " << target << " found: " << (found ? "Yes" : "No") << std::endl;
}

// Function to demonstrate array bounds
void demonstrateArrayBounds() {
    std::cout << "=== Array Bounds Demonstration ===" << std::endl;
    
    int arr[5] = {1, 2, 3, 4, 5};
    
    std::cout << "Valid array access:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }
    
    std::cout << "Invalid array access (undefined behavior):" << std::endl;
    std::cout << "arr[5] = " << arr[5] << " (out of bounds!)" << std::endl;
    std::cout << "arr[-1] = " << arr[-1] << " (out of bounds!)" << std::endl;
    
    // Demonstrate how to safely check bounds
    std::cout << "Safe array access:" << std::endl;
    int index = 3;
    if (index >= 0 && index < 5) {
        std::cout << "arr[" << index << "] = " << arr[index] << std::endl;
    } else {
        std::cout << "Index " << index << " is out of bounds!" << std::endl;
    }
}

// Function to demonstrate array passing to functions
void processArray(int arr[], size_t size) {
    std::cout << "=== Array Passing to Functions ===" << std::endl;
    
    std::cout << "Array in function:" << std::endl;
    for (size_t i = 0; i < size; ++i) {
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }
    
    // Modify array elements
    for (size_t i = 0; i < size; ++i) {
        arr[i] *= 2;
    }
    
    std::cout << "Array after modification:" << std::endl;
    for (size_t i = 0; i < size; ++i) {
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }
}

// Function to demonstrate array size calculation
void demonstrateArraySize() {
    std::cout << "=== Array Size Calculation ===" << std::endl;
    
    int arr[7] = {1, 2, 3, 4, 5, 6, 7};
    
    // Method 1: sizeof operator
    size_t size1 = sizeof(arr) / sizeof(arr[0]);
    std::cout << "Size using sizeof: " << size1 << std::endl;
    
    // Method 2: end - begin pointers
    size_t size2 = arr + 7 - arr;
    std::cout << "Size using pointer arithmetic: " << size2 << std::endl;
    
    // Method 3: std::end - std::begin (C++11)
    size_t size3 = std::end(arr) - std::begin(arr);
    std::cout << "Size using std::end/std::begin: " << size3 << std::endl;
    
    // Note: These methods only work for arrays, not pointers
    int* ptr = arr;
    // size_t wrong_size = sizeof(ptr) / sizeof(ptr[0]);  // Wrong!
    std::cout << "sizeof(ptr): " << sizeof(ptr) << " (pointer size, not array size!)" << std::endl;
}

// Function to demonstrate array initialization
void demonstrateArrayInitialization() {
    std::cout << "=== Array Initialization ===" << std::endl;
    
    // Zero initialization
    int zero_arr[5] = {};
    std::cout << "Zero-initialized array:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "zero_arr[" << i << "] = " << zero_arr[i] << std::endl;
    }
    
    // Partial initialization
    int partial_arr[5] = {10, 20};
    std::cout << "=== Array Initialization ===" << std::endl;
    std::cout << "Partially initialized array:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "partial_arr[" << i << "] = " << partial_arr[i] << std::endl;
    }
    
    // Designated initializers (C++20)
    int designated_arr[5] = {[0] = 100, [2] = 200, [4] = 300};
    std::cout << "=== Array Initialization ===" << std::endl;
    std::cout << "Designated initializers:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "designated_arr[" << i << "] = " << designated_arr[i] << std::endl;
    }
}

int main() {
    std::cout << "=== Arrays and Pointers Demonstration ===" << std::endl;
    std::cout << "This program demonstrates array declaration, initialization," << std::endl;
    std::cout << "array-pointer relationship, and multi-dimensional arrays." << std::endl;
    
    // Demonstrate various array concepts
    demonstrateBasicArrays();
    demonstrateArrayPointerRelationship();
    demonstrateMultiDimensionalArrays();
    demonstrateDynamicArrays();
    demonstrateArrayAlgorithms();
    demonstrateArrayBounds();
    demonstrateArraySize();
    demonstrateArrayInitialization();
    
    // Demonstrate array passing
    int test_arr[5] = {1, 2, 3, 4, 5};
    processArray(test_arr, 5);
    
    std::cout << "=== Key Takeaways ===" << std::endl;
    std::cout << "1. Arrays provide contiguous memory storage" << std::endl;
    std::cout << "2. Arrays and pointers are closely related" << std::endl;
    std::cout << "3. Multi-dimensional arrays are arrays of arrays" << std::endl;
    std::cout << "4. Dynamic arrays allow runtime size determination" << std::endl;
    std::cout << "5. Array bounds checking is the programmer's responsibility" << std::endl;
    std::cout << "6. Arrays decay to pointers when passed to functions" << std::endl;
    std::cout << "7. Use sizeof to calculate array size safely" << std::endl;
    
    std::cout << "Program completed successfully!" << std::endl;    
    std::cout << "Program completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o arrays_pointers 02_Arrays_and_Pointers.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o arrays_pointers 02_Arrays_and_Pointers.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 02_Arrays_and_Pointers.cpp
 * 
 * Running:
 * ./arrays_pointers (Linux/macOS)
 * arrays_pointers.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for std::begin/std::end.
 * C++17 is recommended for best array support.
 * 
 * Array Notes:
 * - Arrays are fixed-size containers
 * - Array bounds are not checked by default
 * - Arrays decay to pointers when passed to functions
 * - Use std::array for safer array operations
 * - Multi-dimensional arrays use row-major storage
 */