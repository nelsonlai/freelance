/*
 * Lesson 10.3: Copy and Move Semantics
 * 
 * This file demonstrates deep vs shallow copying, move semantics,
 * perfect forwarding, and Rule of Zero implementation.
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <utility>

// Example 1: Shallow vs Deep Copy Demonstration
class ShallowCopyExample {
private:
    int* data_;
    size_t size_;
    std::string name_;
    
public:
    ShallowCopyExample(size_t size, const std::string& name = "ShallowCopy")
        : size_(size), name_(name) {
        data_ = new int[size_];
        std::iota(data_, data_ + size_, 1);
        std::cout << "ShallowCopyExample created: " << name_ << std::endl;
    }
    
    // Shallow copy constructor (problematic)
    ShallowCopyExample(const ShallowCopyExample& other)
        : data_(other.data_), size_(other.size_), name_(other.name_ + " (ShallowCopy)") {
        std::cout << "Shallow copy constructor called for: " << name_ << std::endl;
        // Both objects now share the same memory!
    }
    
    // Shallow copy assignment (problematic)
    ShallowCopyExample& operator=(const ShallowCopyExample& other) {
        if (this != &other) {
            data_ = other.data_;  // Shallow copy!
            size_ = other.size_;
            name_ = other.name_ + " (ShallowAssigned)";
        }
        return *this;
    }
    
    ~ShallowCopyExample() {
        std::cout << "ShallowCopyExample destroyed: " << name_ << std::endl;
        delete[] data_;  // This will cause double deletion!
    }
    
    void display() const {
        std::cout << name_ << ": [";
        for (size_t i = 0; i < size_; ++i) {
            std::cout << data_[i];
            if (i < size_ - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
    
    void modify(int index, int value) {
        if (index < size_) {
            data_[index] = value;
        }
    }
};

class DeepCopyExample {
private:
    int* data_;
    size_t size_;
    std::string name_;
    
public:
    DeepCopyExample(size_t size, const std::string& name = "DeepCopy")
        : size_(size), name_(name) {
        data_ = new int[size_];
        std::iota(data_, data_ + size_, 1);
        std::cout << "DeepCopyExample created: " << name_ << std::endl;
    }
    
    // Deep copy constructor (correct)
    DeepCopyExample(const DeepCopyExample& other)
        : size_(other.size_), name_(other.name_ + " (DeepCopy)") {
        data_ = new int[size_];
        std::copy(other.data_, other.data_ + size_, data_);
        std::cout << "Deep copy constructor called for: " << name_ << std::endl;
    }
    
    // Deep copy assignment (correct)
    DeepCopyExample& operator=(const DeepCopyExample& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            name_ = other.name_ + " (DeepAssigned)";
            data_ = new int[size_];
            std::copy(other.data_, other.data_ + size_, data_);
        }
        return *this;
    }
    
    ~DeepCopyExample() {
        std::cout << "DeepCopyExample destroyed: " << name_ << std::endl;
        delete[] data_;
    }
    
    void display() const {
        std::cout << name_ << ": [";
        for (size_t i = 0; i < size_; ++i) {
            std::cout << data_[i];
            if (i < size_ - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
    
    void modify(int index, int value) {
        if (index < size_) {
            data_[index] = value;
        }
    }
};

// Example 2: Move Semantics Demonstration
class MoveSemanticsExample {
private:
    std::string name_;
    std::vector<int> data_;
    std::unique_ptr<std::string> description_;
    
public:
    MoveSemanticsExample(const std::string& name, size_t size)
        : name_(name), data_(size) {
        std::iota(data_.begin(), data_.end(), 1);
        description_ = std::make_unique<std::string>("Description for " + name);
        std::cout << "MoveSemanticsExample created: " << name_ << std::endl;
    }
    
    // Copy constructor
    MoveSemanticsExample(const MoveSemanticsExample& other)
        : name_(other.name_ + " (Copy)"), data_(other.data_) {
        if (other.description_) {
            description_ = std::make_unique<std::string>(*other.description_);
        }
        std::cout << "Copy constructor called for: " << name_ << std::endl;
    }
    
    // Copy assignment
    MoveSemanticsExample& operator=(const MoveSemanticsExample& other) {
        if (this != &other) {
            name_ = other.name_ + " (Assigned)";
            data_ = other.data_;
            if (other.description_) {
                description_ = std::make_unique<std::string>(*other.description_);
            }
        }
        return *this;
    }
    
    // Move constructor
    MoveSemanticsExample(MoveSemanticsExample&& other) noexcept
        : name_(std::move(other.name_)),
          data_(std::move(other.data_)),
          description_(std::move(other.description_)) {
        std::cout << "Move constructor called for: " << name_ << std::endl;
    }
    
    // Move assignment
    MoveSemanticsExample& operator=(MoveSemanticsExample&& other) noexcept {
        if (this != &other) {
            name_ = std::move(other.name_);
            data_ = std::move(other.data_);
            description_ = std::move(other.description_);
        }
        return *this;
    }
    
    ~MoveSemanticsExample() {
        std::cout << "MoveSemanticsExample destroyed: " << name_ << std::endl;
    }
    
    void display() const {
        std::cout << name_ << ": [";
        for (size_t i = 0; i < data_.size(); ++i) {
            std::cout << data_[i];
            if (i < data_.size() - 1) std::cout << ", ";
        }
        std::cout << "]";
        if (description_) {
            std::cout << " (" << *description_ << ")";
        }
        std::cout << std::endl;
    }
    
    void modify(int index, int value) {
        if (index < data_.size()) {
            data_[index] = value;
        }
    }
    
    const std::string& getName() const { return name_; }
    size_t getDataSize() const { return data_.size(); }
};

// Example 3: Perfect Forwarding
template<typename T>
class PerfectForwardingExample {
private:
    T data_;
    
public:
    // Perfect forwarding constructor
    template<typename U>
    PerfectForwardingExample(U&& data) : data_(std::forward<U>(data)) {
        std::cout << "PerfectForwardingExample created with forwarding" << std::endl;
    }
    
    // Perfect forwarding assignment
    template<typename U>
    PerfectForwardingExample& operator=(U&& data) {
        data_ = std::forward<U>(data);
        return *this;
    }
    
    void display() const {
        std::cout << "PerfectForwardingExample data: " << data_ << std::endl;
    }
    
    const T& getData() const { return data_; }
};

// Example 4: Rule of Zero Implementation
class RuleOfZeroExample {
private:
    std::string name_;
    std::vector<int> data_;
    std::unique_ptr<std::string> description_;
    std::shared_ptr<std::string> shared_info_;
    
public:
    RuleOfZeroExample(const std::string& name, size_t size)
        : name_(name), data_(size) {
        std::iota(data_.begin(), data_.end(), 1);
        description_ = std::make_unique<std::string>("Description for " + name);
        shared_info_ = std::make_shared<std::string>("Shared info for " + name);
        std::cout << "RuleOfZeroExample created: " << name_ << std::endl;
    }
    
    // No need to implement destructor, copy constructor, etc.
    // Smart pointers and standard containers handle everything automatically
    
    void display() const {
        std::cout << name_ << ": [";
        for (size_t i = 0; i < data_.size(); ++i) {
            std::cout << data_[i];
            if (i < data_.size() - 1) std::cout << ", ";
        }
        std::cout << "]";
        if (description_) {
            std::cout << " (" << *description_ << ")";
        }
        if (shared_info_) {
            std::cout << " [Shared: " << *shared_info_ << "]";
        }
        std::cout << std::endl;
    }
    
    void modify(int index, int value) {
        if (index < data_.size()) {
            data_[index] = value;
        }
    }
    
    const std::string& getName() const { return name_; }
    size_t getDataSize() const { return data_.size(); }
};

// Example 5: Performance Comparison
class PerformanceTestClass {
private:
    std::string name_;
    std::vector<int> data_;
    
public:
    PerformanceTestClass(const std::string& name, size_t size)
        : name_(name), data_(size) {
        std::iota(data_.begin(), data_.end(), 0);
    }
    
    // Copy constructor
    PerformanceTestClass(const PerformanceTestClass& other)
        : name_(other.name_), data_(other.data_) {
        // std::cout << "Copy constructor called" << std::endl;
    }
    
    // Move constructor
    PerformanceTestClass(PerformanceTestClass&& other) noexcept
        : name_(std::move(other.name_)), data_(std::move(other.data_)) {
        // std::cout << "Move constructor called" << std::endl;
    }
    
    // Copy assignment
    PerformanceTestClass& operator=(const PerformanceTestClass& other) {
        if (this != &other) {
            name_ = other.name_;
            data_ = other.data_;
        }
        return *this;
    }
    
    // Move assignment
    PerformanceTestClass& operator=(PerformanceTestClass&& other) noexcept {
        if (this != &other) {
            name_ = std::move(other.name_);
            data_ = std::move(other.data_);
        }
        return *this;
    }
    
    size_t getDataSize() const { return data_.size(); }
    const std::string& getName() const { return name_; }
};

// Function to demonstrate shallow vs deep copy
void demonstrateShallowVsDeepCopy() {
    std::cout << "=== Shallow vs Deep Copy Demonstration ===" << std::endl;
    
    std::cout << "\n--- Deep Copy (Correct) ---" << std::endl;
    {
        DeepCopyExample deep1("Deep1", 5);
        deep1.display();
        
        DeepCopyExample deep2 = deep1;  // Deep copy
        deep2.display();
        
        deep1.modify(0, 99);
        std::cout << "After modifying deep1:" << std::endl;
        deep1.display();
        deep2.display();  // deep2 is unaffected
        
        DeepCopyExample deep3("Deep3", 3);
        deep3 = deep1;  // Deep assignment
        deep3.display();
        
        deep1.modify(1, 88);
        std::cout << "After modifying deep1 again:" << std::endl;
        deep1.display();
        deep3.display();  // deep3 is unaffected
    }
    
    std::cout << "\n--- Shallow Copy (Problematic) ---" << std::endl;
    std::cout << "Note: Shallow copy will cause issues when objects are destroyed" << std::endl;
    
    // Uncomment the following to see shallow copy problems:
    /*
    {
        ShallowCopyExample shallow1("Shallow1", 5);
        shallow1.display();
        
        ShallowCopyExample shallow2 = shallow1;  // Shallow copy
        shallow2.display();
        
        shallow1.modify(0, 99);
        std::cout << "After modifying shallow1:" << std::endl;
        shallow1.display();
        shallow2.display();  // shallow2 is also affected!
        
        // This will cause double deletion when objects are destroyed
    }
    */
}

// Function to demonstrate move semantics
void demonstrateMoveSemantics() {
    std::cout << "\n=== Move Semantics Demonstration ===" << std::endl;
    
    MoveSemanticsExample obj1("Object1", 5);
    obj1.display();
    
    std::cout << "\n--- Copy Semantics ---" << std::endl;
    MoveSemanticsExample obj2 = obj1;  // Copy constructor
    obj2.display();
    
    std::cout << "\n--- Move Semantics ---" << std::endl;
    MoveSemanticsExample obj3 = std::move(obj1);  // Move constructor
    obj3.display();
    std::cout << "obj1 after move (should be empty): " << obj1.getName() << std::endl;
    
    std::cout << "\n--- Move Assignment ---" << std::endl;
    MoveSemanticsExample obj4("Object4", 3);
    obj4 = std::move(obj2);  // Move assignment
    obj4.display();
    std::cout << "obj2 after move assignment: " << obj2.getName() << std::endl;
}

// Function to demonstrate perfect forwarding
void demonstratePerfectForwarding() {
    std::cout << "\n=== Perfect Forwarding Demonstration ===" << std::endl;
    
    std::string str = "Hello";
    
    std::cout << "\n--- Lvalue Reference ---" << std::endl;
    PerfectForwardingExample<std::string> pf1(str);
    pf1.display();
    
    std::cout << "\n--- Rvalue Reference (std::move) ---" << std::endl;
    PerfectForwardingExample<std::string> pf2(std::move(str));
    pf2.display();
    
    std::cout << "\n--- Temporary Object ---" << std::endl;
    PerfectForwardingExample<std::string> pf3("World");
    pf3.display();
    
    std::cout << "\n--- Perfect Forwarding Assignment ---" << std::endl;
    pf1 = "Perfect Forwarding";
    pf1.display();
    
    std::cout << "\n--- Perfect Forwarding with Different Types ---" << std::endl;
    PerfectForwardingExample<int> pf4(42);
    PerfectForwardingExample<double> pf5(3.14159);
    PerfectForwardingExample<std::string> pf6(std::string("Constructed"));
    
    pf4.display();
    pf5.display();
    pf6.display();
}

// Function to demonstrate Rule of Zero
void demonstrateRuleOfZero() {
    std::cout << "\n=== Rule of Zero Demonstration ===" << std::endl;
    
    RuleOfZeroExample roc1("RuleOfZero1", 5);
    roc1.display();
    
    std::cout << "\n--- Copy Constructor (Compiler-Generated) ---" << std::endl;
    RuleOfZeroExample roc2 = roc1;
    roc2.display();
    
    std::cout << "\n--- Move Constructor (Compiler-Generated) ---" << std::endl;
    RuleOfZeroExample roc3 = std::move(roc1);
    roc3.display();
    std::cout << "roc1 after move: " << roc1.getName() << std::endl;
    
    std::cout << "\n--- Copy Assignment (Compiler-Generated) ---" << std::endl;
    RuleOfZeroExample roc4("RuleOfZero4", 3);
    roc4 = roc2;
    roc4.display();
    
    std::cout << "\n--- Move Assignment (Compiler-Generated) ---" << std::endl;
    RuleOfZeroExample roc5("RuleOfZero5", 2);
    roc5 = std::move(roc2);
    roc5.display();
    std::cout << "roc2 after move assignment: " << roc2.getName() << std::endl;
    
    std::cout << "\n--- Modifying Objects ---" << std::endl;
    roc3.modify(0, 99);
    roc4.modify(1, 88);
    roc5.modify(0, 77);
    
    std::cout << "After modifications:" << std::endl;
    roc3.display();
    roc4.display();
    roc5.display();
}

// Function to demonstrate performance comparison
void demonstratePerformanceComparison() {
    std::cout << "\n=== Performance Comparison ===" << std::endl;
    
    const size_t size = 1000000;
    
    // Create original object
    PerformanceTestClass original("Original", size);
    
    std::cout << "Testing with " << size << " elements..." << std::endl;
    
    // Test copy performance
    std::cout << "\n--- Copy Performance ---" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    PerformanceTestClass copied = original;
    auto end = std::chrono::high_resolution_clock::now();
    auto copy_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Copy time: " << copy_time.count() << " microseconds" << std::endl;
    std::cout << "Copied object size: " << copied.getDataSize() << std::endl;
    
    // Test move performance
    std::cout << "\n--- Move Performance ---" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    PerformanceTestClass moved = std::move(original);
    end = std::chrono::high_resolution_clock::now();
    auto move_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Move time: " << move_time.count() << " microseconds" << std::endl;
    std::cout << "Moved object size: " << moved.getDataSize() << std::endl;
    std::cout << "Original object size after move: " << original.getDataSize() << std::endl;
    
    if (move_time.count() > 0) {
        std::cout << "Move is " << (double)copy_time.count() / move_time.count() 
                  << "x faster than copy" << std::endl;
    } else {
        std::cout << "Move is significantly faster than copy" << std::endl;
    }
}

// Function to demonstrate value categories
void demonstrateValueCategories() {
    std::cout << "\n=== Value Categories Demonstration ===" << std::endl;
    
    std::string str = "Hello";
    
    // lvalue - has identity and can be assigned
    std::string& lvalue_ref = str;
    std::cout << "lvalue reference: " << lvalue_ref << std::endl;
    
    // rvalue reference
    std::string&& rvalue_ref = std::move(str);
    std::cout << "rvalue reference: " << rvalue_ref << std::endl;
    
    // prvalue - pure rvalue (temporary)
    std::string prvalue = "World";
    std::cout << "prvalue: " << prvalue << std::endl;
    
    // xvalue - expiring value
    std::string xvalue = std::move(prvalue);
    std::cout << "xvalue: " << xvalue << std::endl;
    std::cout << "prvalue after move: " << prvalue << std::endl;
}

// Function to demonstrate copy elision
void demonstrateCopyElision() {
    std::cout << "\n=== Copy Elision Demonstration ===" << std::endl;
    
    class CopyElisionExample {
    private:
        std::string name_;
        
    public:
        CopyElisionExample(const std::string& name) : name_(name) {
            std::cout << "CopyElisionExample constructor: " << name_ << std::endl;
        }
        
        CopyElisionExample(const CopyElisionExample& other) : name_(other.name_ + " (Copy)") {
            std::cout << "CopyElisionExample copy constructor: " << name_ << std::endl;
        }
        
        static CopyElisionExample createObject(const std::string& name) {
            return CopyElisionExample(name);  // RVO - no copy
        }
    };
    
    std::cout << "--- Return Value Optimization (RVO) ---" << std::endl;
    CopyElisionExample obj1 = CopyElisionExample::createObject("RVO Test");
    
    std::cout << "--- Named Return Value Optimization (NRVO) ---" << std::endl;
    auto createNamedObject = [](const std::string& name) -> CopyElisionExample {
        CopyElisionExample obj(name);
        return obj;  // NRVO - no copy
    };
    
    CopyElisionExample obj2 = createNamedObject("NRVO Test");
}

int main() {
    std::cout << "=== Copy and Move Semantics Demonstration ===" << std::endl;
    std::cout << "This program demonstrates deep vs shallow copying, move semantics,\n"
              << "perfect forwarding, and Rule of Zero implementation.\n" << std::endl;
    
    // Demonstrate various copy and move concepts
    demonstrateShallowVsDeepCopy();
    demonstrateMoveSemantics();
    demonstratePerfectForwarding();
    demonstrateRuleOfZero();
    demonstratePerformanceComparison();
    demonstrateValueCategories();
    demonstrateCopyElision();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Deep copy creates independent copies of resources" << std::endl;
    std::cout << "2. Move semantics transfer ownership without copying" << std::endl;
    std::cout << "3. Perfect forwarding preserves value categories" << std::endl;
    std::cout << "4. Rule of Zero simplifies resource management" << std::endl;
    std::cout << "5. Move operations are typically much faster than copy operations" << std::endl;
    std::cout << "6. Smart pointers enable Rule of Zero implementation" << std::endl;
    std::cout << "7. Copy elision optimizes away unnecessary copies" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o copy_move_semantics 03_Copy_and_Move_Semantics.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o copy_move_semantics 03_Copy_and_Move_Semantics.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 03_Copy_and_Move_Semantics.cpp
 * 
 * Running:
 * ./copy_move_semantics (Linux/macOS)
 * copy_move_semantics.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for move semantics and smart pointers.
 * C++17 is recommended for best copy and move semantics support.
 * 
 * Copy/Move Semantics Notes:
 * - Always implement deep copy for pointer members
 * - Use move semantics for performance optimization
 * - Mark move operations as noexcept
 * - Apply Rule of Zero with smart pointers
 * - Use perfect forwarding for generic code
 * - Let compiler optimize with copy elision
 * - Handle self-assignment in copy operations
 */"""
