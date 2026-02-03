#include <iostream>
#include <memory>
#include <vector>
#include <string>

// Demonstrates pointers, arrays, and references in C++
int main() {
    std::cout << "Pointers, Arrays, and References Demonstration" << std::endl;
    std::cout << "=============================================" << std::endl;
    
    // 1. Pointer basics
    std::cout << "\n1. POINTER BASICS:" << std::endl;
    
    int x = 42;
    int* ptr = &x;  // Pointer to x
    
    std::cout << "Value of x: " << x << std::endl;
    std::cout << "Address of x: " << &x << std::endl;
    std::cout << "Value of ptr: " << ptr << std::endl;
    std::cout << "Dereferenced ptr: " << *ptr << std::endl;
    
    // Modify through pointer
    *ptr = 100;
    std::cout << "After *ptr = 100, x = " << x << std::endl;
    
    // 2. Pointer arithmetic
    std::cout << "\n2. POINTER ARITHMETIC:" << std::endl;
    
    int arr[5] = {10, 20, 30, 40, 50};
    int* arr_ptr = arr;  // Points to first element
    
    std::cout << "Array elements using pointer arithmetic:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "arr[" << i << "] = " << *(arr_ptr + i) << std::endl;
    }
    
    // Increment pointer
    std::cout << "Incrementing pointer:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "*arr_ptr = " << *arr_ptr << std::endl;
        arr_ptr++;
    }
    
    // 3. Arrays and array decay
    std::cout << "\n3. ARRAYS AND ARRAY DECAY:" << std::endl;
    
    int numbers[5] = {1, 2, 3, 4, 5};
    
    std::cout << "Array name as pointer: " << numbers << std::endl;
    std::cout << "Address of first element: " << &numbers[0] << std::endl;
    std::cout << "Size of array: " << sizeof(numbers) << " bytes" << std::endl;
    std::cout << "Size of first element: " << sizeof(numbers[0]) << " bytes" << std::endl;
    std::cout << "Number of elements: " << sizeof(numbers) / sizeof(numbers[0]) << std::endl;
    
    // Array decay in function calls
    auto print_array = [](int* arr, size_t size) {
        std::cout << "Array passed as pointer: ";
        for (size_t i = 0; i < size; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    };
    
    print_array(numbers, 5);
    
    // 4. Multidimensional arrays
    std::cout << "\n4. MULTIDIMENSIONAL ARRAYS:" << std::endl;
    
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    std::cout << "3x4 Matrix:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    // 5. References
    std::cout << "\n5. REFERENCES:" << std::endl;
    
    int original = 42;
    int& ref = original;  // Reference to original
    
    std::cout << "Original value: " << original << std::endl;
    std::cout << "Reference value: " << ref << std::endl;
    std::cout << "Address of original: " << &original << std::endl;
    std::cout << "Address of reference: " << &ref << std::endl;
    
    // Modify through reference
    ref = 100;
    std::cout << "After ref = 100, original = " << original << std::endl;
    
    // 6. Const references
    std::cout << "\n6. CONST REFERENCES:" << std::endl;
    
    const int const_val = 200;
    const int& const_ref = const_val;
    
    std::cout << "Const value: " << const_val << std::endl;
    std::cout << "Const reference: " << const_ref << std::endl;
    
    // const_ref = 300;  // This would cause a compile error
    
    // 7. Dynamic memory allocation
    std::cout << "\n7. DYNAMIC MEMORY ALLOCATION:" << std::endl;
    
    // Allocate single integer
    int* dynamic_int = new int(42);
    std::cout << "Dynamically allocated int: " << *dynamic_int << std::endl;
    delete dynamic_int;
    
    // Allocate array
    int* dynamic_array = new int[5]{1, 2, 3, 4, 5};
    std::cout << "Dynamically allocated array: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << dynamic_array[i] << " ";
    }
    std::cout << std::endl;
    delete[] dynamic_array;
    
    // 8. Smart pointers (RAII)
    std::cout << "\n8. SMART POINTERS (RAII):" << std::endl;
    
    // unique_ptr
    std::unique_ptr<int> unique_ptr = std::make_unique<int>(42);
    std::cout << "unique_ptr value: " << *unique_ptr << std::endl;
    
    // shared_ptr
    std::shared_ptr<int> shared_ptr = std::make_shared<int>(100);
    std::cout << "shared_ptr value: " << *shared_ptr << std::endl;
    std::cout << "Reference count: " << shared_ptr.use_count() << std::endl;
    
    // Create another shared_ptr
    std::shared_ptr<int> another_shared = shared_ptr;
    std::cout << "Reference count after copy: " << shared_ptr.use_count() << std::endl;
    
    // 9. Pointer to pointer
    std::cout << "\n9. POINTER TO POINTER:" << std::endl;
    
    int value = 42;
    int* ptr1 = &value;
    int** ptr2 = &ptr1;
    
    std::cout << "Value: " << value << std::endl;
    std::cout << "Pointer to value: " << ptr1 << std::endl;
    std::cout << "Pointer to pointer: " << ptr2 << std::endl;
    std::cout << "Dereference ptr2: " << *ptr2 << std::endl;
    std::cout << "Double dereference ptr2: " << **ptr2 << std::endl;
    
    // 10. Function pointers
    std::cout << "\n10. FUNCTION POINTERS:" << std::endl;
    
    auto add = [](int a, int b) { return a + b; };
    auto multiply = [](int a, int b) { return a * b; };
    
    int (*func_ptr)(int, int) = add;
    std::cout << "Function pointer (add): " << func_ptr(5, 3) << std::endl;
    
    func_ptr = multiply;
    std::cout << "Function pointer (multiply): " << func_ptr(5, 3) << std::endl;
    
    // 11. Array of pointers
    std::cout << "\n11. ARRAY OF POINTERS:" << std::endl;
    
    int a = 1, b = 2, c = 3;
    int* ptr_array[3] = {&a, &b, &c};
    
    std::cout << "Array of pointers: ";
    for (int i = 0; i < 3; ++i) {
        std::cout << *ptr_array[i] << " ";
    }
    std::cout << std::endl;
    
    // 12. Pointer to array
    std::cout << "\n12. POINTER TO ARRAY:" << std::endl;
    
    int arr2[5] = {10, 20, 30, 40, 50};
    int (*ptr_to_array)[5] = &arr2;
    
    std::cout << "Pointer to array: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << (*ptr_to_array)[i] << " ";
    }
    std::cout << std::endl;
    
    // 13. Memory safety demonstration
    std::cout << "\n13. MEMORY SAFETY:" << std::endl;
    
    // Dangling pointer example (dangerous!)
    int* dangling_ptr;
    {
        int local_var = 42;
        dangling_ptr = &local_var;
        std::cout << "Local variable: " << *dangling_ptr << std::endl;
    }  // local_var goes out of scope here
    
    // dangling_ptr now points to freed memory
    // std::cout << "Dangling pointer: " << *dangling_ptr << std::endl;  // Undefined behavior!
    
    std::cout << "Dangling pointer example (commented out for safety)" << std::endl;
    
    // 14. Reference vs pointer comparison
    std::cout << "\n14. REFERENCE VS POINTER:" << std::endl;
    
    int val = 42;
    int& ref_val = val;
    int* ptr_val = &val;
    
    std::cout << "Value: " << val << std::endl;
    std::cout << "Reference: " << ref_val << std::endl;
    std::cout << "Pointer: " << *ptr_val << std::endl;
    
    // References cannot be reassigned
    int another_val = 100;
    // ref_val = another_val;  // This assigns value, doesn't reassign reference
    
    // Pointers can be reassigned
    ptr_val = &another_val;
    std::cout << "Pointer after reassignment: " << *ptr_val << std::endl;
    
    std::cout << "\nPointers, arrays, and references demonstration completed!" << std::endl;
    return 0;
}
