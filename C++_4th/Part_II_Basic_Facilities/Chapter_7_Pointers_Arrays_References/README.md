# Chapter 7: Pointers, Arrays, and References

## 📘 Learning Objectives

After completing this chapter, you will:
- Master pointers and pointer arithmetic
- Understand arrays and array decay
- Learn references and const references
- Master dynamic memory management
- Understand RAII principles
- Learn smart pointers

## 🎯 Key Concepts

### 1. Pointers

- **Pointer**: Variable that stores memory address
- **Dereference**: Access value at pointer address
- **Address-of**: Get address of variable
- **Null pointer**: Pointer that points to nothing

### 2. Arrays

- **Array**: Collection of elements of same type
- **Array decay**: Array name converts to pointer to first element
- **Multidimensional arrays**: Arrays of arrays
- **Array bounds**: C++ doesn't check array bounds

### 3. References

- **Reference**: Alias for another variable
- **Const reference**: Read-only reference
- **Reference binding**: Must be initialized
- **Reference vs pointer**: References cannot be reassigned

### 4. Dynamic Memory

- **new/delete**: Allocate/deallocate memory
- **new[]/delete[]**: Allocate/deallocate arrays
- **Memory leaks**: Forgotten deallocation
- **Dangling pointers**: Pointers to freed memory

### 5. RAII (Resource Acquisition Is Initialization)

- **RAII**: Resource management through object lifetime
- **Smart pointers**: Automatic memory management
- **unique_ptr**: Exclusive ownership
- **shared_ptr**: Shared ownership
- **weak_ptr**: Non-owning reference

## 🧩 Practice Exercises

### Exercise 7.1: Pointer Basics
Create programs demonstrating pointer operations and arithmetic.

### Exercise 7.2: Array Manipulation
Write programs using arrays and multidimensional arrays.

### Exercise 7.3: Reference Usage
Demonstrate references and const references.

### Exercise 7.4: Dynamic Memory
Show dynamic memory allocation and RAII patterns.

## 💻 Code Examples

### Pointer Basics
```cpp
#include <iostream>

int main() {
    int x = 42;
    int* ptr = &x;  // Pointer to x
    
    std::cout << "Value: " << x << std::endl;
    std::cout << "Address: " << &x << std::endl;
    std::cout << "Pointer value: " << ptr << std::endl;
    std::cout << "Dereferenced: " << *ptr << std::endl;
    
    *ptr = 100;  // Modify through pointer
    std::cout << "New value: " << x << std::endl;
    
    return 0;
}
```

### Array Operations
```cpp
#include <iostream>

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    
    // Array access
    for (int i = 0; i < 5; ++i) {
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }
    
    // Pointer arithmetic
    int* ptr = arr;
    for (int i = 0; i < 5; ++i) {
        std::cout << "*(ptr + " << i << ") = " << *(ptr + i) << std::endl;
    }
    
    return 0;
}
```

## 🎓 Key Takeaways

1. **Pointers**: Powerful but dangerous - use carefully
2. **Arrays**: Fixed size, decay to pointers
3. **References**: Safer than pointers, cannot be null
4. **Memory management**: Use RAII and smart pointers
5. **Const correctness**: Use const to prevent modifications

## 🔗 Next Steps

After mastering pointers, arrays, and references, proceed to Chapter 8 to learn about structures, unions, and enumerations.

## 📚 Additional Resources

- C++ Reference: Pointers and References
- C++ Core Guidelines: Memory Management
- Practice with memory debugging tools
