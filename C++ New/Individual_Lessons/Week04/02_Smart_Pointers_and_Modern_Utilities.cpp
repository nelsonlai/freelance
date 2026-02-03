/*
 * Lesson 4.2: Smart Pointers and Modern Utilities
 * 
 * This file demonstrates unique_ptr, shared_ptr, weak_ptr,
 * custom deleters, and RAII principles.
 */

#include <iostream>
#include <memory>
#include <vector>
#include <functional>

// Resource class for demonstration
class Resource {
public:
    Resource(int id) : id_(id) {
        std::cout << "Resource " << id_ << " created" << std::endl;
    }
    
    ~Resource() {
        std::cout << "Resource " << id_ << " destroyed" << std::endl;
    }
    
    void use() const {
        std::cout << "Using resource " << id_ << std::endl;
    }
    
    int getId() const { return id_; }
    
private:
    int id_;
};

// Function to demonstrate unique_ptr
void demonstrateUniquePtr() {
    std::cout << "=== unique_ptr Demonstration ===" << std::endl;
    
    // Create unique_ptr with make_unique
    std::unique_ptr<Resource> ptr = std::make_unique<Resource>(1);
    ptr->use();
    
    // Check if pointer is valid
    if (ptr) {
        std::cout << "Pointer is valid" << std::endl;
    }
    
    // Transfer ownership
    std::unique_ptr<Resource> ptr2 = std::move(ptr);
    if (!ptr) {
        std::cout << "ptr is now nullptr after move" << std::endl;
    }
    
    if (ptr2) {
        std::cout << "ptr2 owns the resource" << std::endl;
        ptr2->use();
    }
    
    // Reset pointer
    ptr2.reset();
    if (!ptr2) {
        std::cout << "ptr2 is now nullptr after reset" << std::endl;
    }
    
    // Create array with unique_ptr
    std::unique_ptr<Resource[]> array_ptr = std::make_unique<Resource[]>(3);
    for (int i = 0; i < 3; ++i) {
        std::cout << "Array element " << i << " created" << std::endl;
    }
    
    std::cout << "unique_ptr demonstration completed" << std::endl;
}

// Function to demonstrate shared_ptr
void demonstrateSharedPtr() {
    std::cout << "
=== shared_ptr Demonstration ===" << std::endl;
    
    // Create shared_ptr with make_shared
    std::shared_ptr<Resource> ptr1 = std::make_shared<Resource>(2);
    std::cout << "Reference count: " << ptr1.use_count() << std::endl;
    
    // Share ownership
    std::shared_ptr<Resource> ptr2 = ptr1;
    std::cout << "Reference count after sharing: " << ptr1.use_count() << std::endl;
    
    // Use both pointers
    ptr1->use();
    ptr2->use();
    
    // Create another shared_ptr
    std::shared_ptr<Resource> ptr3 = ptr1;
    std::cout << "Reference count after third pointer: " << ptr1.use_count() << std::endl;
    
    // Reset one pointer
    ptr1.reset();
    std::cout << "Reference count after reset: " << ptr2.use_count() << std::endl;
    
    // Check if pointer is valid
    if (ptr1) {
        std::cout << "ptr1 is still valid" << std::endl;
    } else {
        std::cout << "ptr1 is now nullptr" << std::endl;
    }
    
    // Use remaining pointers
    ptr2->use();
    ptr3->use();
    
    std::cout << "shared_ptr demonstration completed" << std::endl;
}

// Function to demonstrate weak_ptr
void demonstrateWeakPtr() {
    std::cout << "
=== weak_ptr Demonstration ===" << std::endl;
    
    std::shared_ptr<Resource> shared = std::make_shared<Resource>(3);
    std::weak_ptr<Resource> weak = shared;
    
    std::cout << "Shared reference count: " << shared.use_count() << std::endl;
    std::cout << "Weak reference count: " << weak.use_count() << std::endl;
    
    // Check if object exists
    if (auto locked = weak.lock()) {
        std::cout << "Object exists, reference count: " << locked.use_count() << std::endl;
        locked->use();
    }
    
    // Reset shared_ptr
    shared.reset();
    std::cout << "Shared pointer reset" << std::endl;
    
    // Check if object still exists
    if (auto locked = weak.lock()) {
        std::cout << "Object still exists" << std::endl;
    } else {
        std::cout << "Object has been destroyed" << std::endl;
    }
    
    // Check if weak_ptr is expired
    if (weak.expired()) {
        std::cout << "Weak pointer is expired" << std::endl;
    }
    
    std::cout << "weak_ptr demonstration completed" << std::endl;
}

// Custom deleter example
void demonstrateCustomDeleters() {
    std::cout << "
=== Custom Deleters Demonstration ===" << std::endl;
    
    // Custom deleter for arrays
    auto array_deleter = [](int* ptr) {
        std::cout << "Custom array deleter called" << std::endl;
        delete[] ptr;
    };
    
    std::unique_ptr<int[], decltype(array_deleter)> 
        array_ptr(new int[5], array_deleter);
    
    // Initialize array
    for (int i = 0; i < 5; ++i) {
        array_ptr[i] = i * 10;
    }
    
    std::cout << "Array contents: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << array_ptr[i] << " ";
    }
    std::cout << std::endl;
    
    // Custom deleter for C-style resources
    auto c_deleter = [](void* ptr) {
        std::cout << "Custom C deleter called" << std::endl;
        free(ptr);
    };
    
    std::unique_ptr<void, decltype(c_deleter)> 
        c_ptr(malloc(1024), c_deleter);
    
    if (c_ptr) {
        std::cout << "C-style memory allocated" << std::endl;
    }
    
    std::cout << "Custom deleters demonstration completed" << std::endl;
}

// RAII example with smart pointers
class FileManager {
private:
    std::unique_ptr<FILE, decltype(&fclose)> file_;
    std::string filename_;
    
public:
    FileManager(const std::string& filename) 
        : file_(fopen(filename.c_str(), "w"), &fclose), filename_(filename) {
        if (!file_) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
        std::cout << "File " << filename_ << " opened" << std::endl;
    }
    
    void write(const std::string& data) {
        if (file_) {
            fputs(data.c_str(), file_.get());
            fputs("
", file_.get());
            std::cout << "Written to file: " << data << std::endl;
        }
    }
    
    ~FileManager() {
        if (file_) {
            std::cout << "File " << filename_ << " closed" << std::endl;
        }
    }
};

// Function to demonstrate RAII with smart pointers
void demonstrateRAII() {
    std::cout << "
=== RAII with Smart Pointers Demonstration ===" << std::endl;
    
    try {
        FileManager file("test.txt");
        file.write("Hello, World!");
        file.write("This is a test file");
        
        // File will be automatically closed when file goes out of scope
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    std::cout << "RAII demonstration completed" << std::endl;
}

// Circular reference prevention example
class Node {
public:
    std::shared_ptr<Node> parent;
    std::weak_ptr<Node> child;  // Use weak_ptr to break cycle
    int value;
    
    Node(int val) : value(val) {
        std::cout << "Node " << value << " created" << std::endl;
    }
    
    ~Node() {
        std::cout << "Node " << value << " destroyed" << std::endl;
    }
    
    void setChild(std::shared_ptr<Node> child_node) {
        child = child_node;
        child_node->parent = shared_from_this();
    }
    
    void use() const {
        std::cout << "Using node " << value << std::endl;
    }
    
    std::shared_ptr<Node> shared_from_this() {
        return std::shared_ptr<Node>(this);
    }
};

// Function to demonstrate circular reference prevention
void demonstrateCircularReferencePrevention() {
    std::cout << "
=== Circular Reference Prevention Demonstration ===" << std::endl;
    
    // Create nodes
    auto parent = std::make_shared<Node>(1);
    auto child = std::make_shared<Node>(2);
    
    // Set up parent-child relationship
    parent->setChild(child);
    
    std::cout << "Parent reference count: " << parent.use_count() << std::endl;
    std::cout << "Child reference count: " << child.use_count() << std::endl;
    
    // Use nodes
    parent->use();
    if (auto locked_child = parent->child.lock()) {
        locked_child->use();
    }
    
    // Reset parent
    parent.reset();
    std::cout << "Parent reset" << std::endl;
    
    // Check if child is still accessible
    if (auto locked_child = child->child.lock()) {
        std::cout << "Child is still accessible" << std::endl;
    } else {
        std::cout << "Child is no longer accessible" << std::endl;
    }
    
    std::cout << "Circular reference prevention demonstration completed" << std::endl;
}

// Performance comparison
void demonstratePerformance() {
    std::cout << "
=== Performance Demonstration ===" << std::endl;
    
    const int iterations = 1000000;
    
    // Raw pointer performance
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < iterations; ++i) {
        int* ptr = new int(i);
        delete ptr;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto raw_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Raw pointer time: " << raw_time.count() << " microseconds" << std::endl;
    
    // unique_ptr performance
    start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < iterations; ++i) {
        auto ptr = std::make_unique<int>(i);
    }
    
    end = std::chrono::high_resolution_clock::now();
    auto unique_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "unique_ptr time: " << unique_time.count() << " microseconds" << std::endl;
    
    // shared_ptr performance
    start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < iterations; ++i) {
        auto ptr = std::make_shared<int>(i);
    }
    
    end = std::chrono::high_resolution_clock::now();
    auto shared_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "shared_ptr time: " << shared_time.count() << " microseconds" << std::endl;
    
    // Performance comparison
    std::cout << "unique_ptr overhead: " << (double)unique_time.count() / raw_time.count() << "x" << std::endl;
    std::cout << "shared_ptr overhead: " << (double)shared_time.count() / raw_time.count() << "x" << std::endl;
}

int main() {
    std::cout << "=== Smart Pointers and Modern Utilities Demonstration ===" << std::endl;
    std::cout << "This program demonstrates unique_ptr, shared_ptr, weak_ptr,
"
              << "custom deleters, and RAII principles.
" << std::endl;
    
    // Demonstrate various smart pointer concepts
    demonstrateUniquePtr();
    demonstrateSharedPtr();
    demonstrateWeakPtr();
    demonstrateCustomDeleters();
    demonstrateRAII();
    demonstrateCircularReferencePrevention();
    demonstratePerformance();
    
    std::cout << "
=== Key Takeaways ===" << std::endl;
    std::cout << "1. unique_ptr provides exclusive ownership with zero overhead" << std::endl;
    std::cout << "2. shared_ptr enables shared ownership with reference counting" << std::endl;
    std::cout << "3. weak_ptr breaks circular references and provides safe access" << std::endl;
    std::cout << "4. Custom deleters allow smart pointers to manage any resource" << std::endl;
    std::cout << "5. RAII with smart pointers ensures exception-safe resource management" << std::endl;
    std::cout << "6. Smart pointers prevent memory leaks and dangling pointers" << std::endl;
    std::cout << "7. Performance overhead varies between smart pointer types" << std::endl;
    
    std::cout << "
Program completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o smart_pointers 02_Smart_Pointers_and_Modern_Utilities.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o smart_pointers 02_Smart_Pointers_and_Modern_Utilities.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 02_Smart_Pointers_and_Modern_Utilities.cpp
 * 
 * Running:
 * ./smart_pointers (Linux/macOS)
 * smart_pointers.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for smart pointer support.
 * C++17 is recommended for best smart pointer features.
 * 
 * Smart Pointer Notes:
 * - Prefer make_unique and make_shared over new
 * - Use unique_ptr for exclusive ownership
 * - Use shared_ptr for shared ownership
 * - Use weak_ptr to break circular references
 * - Smart pointers provide exception safety
 */