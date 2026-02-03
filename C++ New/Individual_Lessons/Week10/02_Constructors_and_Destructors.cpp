/*
 * Lesson 10.2: Constructors and Destructors
 * 
 * This file demonstrates constructor types, destructor implementation,
 * RAII principles, copy and move semantics, and the Rule of Three/Five/Zero.
 */

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <fstream>
#include <mutex>
#include <stdexcept>

// Example 1: Basic Constructor and Destructor
class Student {
private:
    std::string name_;
    int age_;
    double gpa_;
    static int total_students_;
    
public:
    // Default constructor
    Student() : name_("Unknown"), age_(18), gpa_(0.0) {
        total_students_++;
        std::cout << "Default Student created: " << name_ << std::endl;
    }
    
    // Parameterized constructor
    Student(const std::string& name, int age, double gpa)
        : name_(name), age_(age), gpa_(gpa) {
        if (gpa < 0.0 || gpa > 4.0) {
            throw std::invalid_argument("GPA must be between 0.0 and 4.0");
        }
        total_students_++;
        std::cout << "Student created: " << name_ << " (Age: " << age_ 
                  << ", GPA: " << gpa_ << ")" << std::endl;
    }
    
    // Copy constructor
    Student(const Student& other)
        : name_(other.name_ + " (Copy)"), age_(other.age_), gpa_(other.gpa_) {
        total_students_++;
        std::cout << "Student copied: " << name_ << std::endl;
    }
    
    // Copy assignment operator
    Student& operator=(const Student& other) {
        if (this != &other) {
            name_ = other.name_ + " (Assigned)";
            age_ = other.age_;
            gpa_ = other.gpa_;
        }
        return *this;
    }
    
    // Move constructor
    Student(Student&& other) noexcept
        : name_(std::move(other.name_)), age_(other.age_), gpa_(other.gpa_) {
        total_students_++;
        other.age_ = 0;
        other.gpa_ = 0.0;
        std::cout << "Student moved: " << name_ << std::endl;
    }
    
    // Move assignment operator
    Student& operator=(Student&& other) noexcept {
        if (this != &other) {
            name_ = std::move(other.name_);
            age_ = other.age_;
            gpa_ = other.gpa_;
            other.age_ = 0;
            other.gpa_ = 0.0;
        }
        return *this;
    }
    
    // Destructor
    ~Student() {
        total_students_--;
        std::cout << "Student destroyed: " << name_ << std::endl;
    }
    
    // Getters
    const std::string& getName() const { return name_; }
    int getAge() const { return age_; }
    double getGPA() const { return gpa_; }
    
    // Static member function
    static int getTotalStudents() { return total_students_; }
    
    // Display information
    void display() const {
        std::cout << "Student: " << name_ << ", Age: " << age_ 
                  << ", GPA: " << gpa_ << std::endl;
    }
};

int Student::total_students_ = 0;

// Example 2: RAII with File Management
class FileManager {
private:
    std::string filename_;
    std::fstream file_;
    bool is_open_;
    
public:
    // Constructor
    FileManager(const std::string& filename) 
        : filename_(filename), is_open_(false) {
        file_.open(filename_, std::ios::in | std::ios::out | std::ios::app);
        if (!file_.is_open()) {
            throw std::runtime_error("Cannot open file: " + filename_);
        }
        is_open_ = true;
        std::cout << "File opened: " << filename_ << std::endl;
    }
    
    // Destructor
    ~FileManager() {
        if (is_open_) {
            file_.close();
            std::cout << "File closed: " << filename_ << std::endl;
        }
    }
    
    // Copy constructor (deleted to prevent copying)
    FileManager(const FileManager&) = delete;
    
    // Copy assignment operator (deleted)
    FileManager& operator=(const FileManager&) = delete;
    
    // Move constructor
    FileManager(FileManager&& other) noexcept
        : filename_(std::move(other.filename_)), 
          file_(std::move(other.file_)),
          is_open_(other.is_open_) {
        other.is_open_ = false;
        std::cout << "FileManager moved: " << filename_ << std::endl;
    }
    
    // Move assignment operator
    FileManager& operator=(FileManager&& other) noexcept {
        if (this != &other) {
            if (is_open_) {
                file_.close();
            }
            filename_ = std::move(other.filename_);
            file_ = std::move(other.file_);
            is_open_ = other.is_open_;
            other.is_open_ = false;
        }
        return *this;
    }
    
    // File operations
    void write(const std::string& content) {
        if (!is_open_) {
            throw std::runtime_error("File is not open");
        }
        file_ << content << std::endl;
        std::cout << "Written to file: " << content << std::endl;
    }
    
    std::string read() {
        if (!is_open_) {
            throw std::runtime_error("File is not open");
        }
        file_.seekg(0, std::ios::beg);
        std::string content((std::istreambuf_iterator<char>(file_)),
                           std::istreambuf_iterator<char>());
        return content;
    }
    
    bool isOpen() const { return is_open_; }
    const std::string& getFilename() const { return filename_; }
};

// Example 3: RAII with Mutex (Lock Guard)
class LockGuard {
private:
    std::mutex& mutex_;
    bool locked_;
    
public:
    // Constructor - acquires lock
    LockGuard(std::mutex& m) : mutex_(m), locked_(true) {
        mutex_.lock();
        std::cout << "Lock acquired" << std::endl;
    }
    
    // Destructor - releases lock
    ~LockGuard() {
        if (locked_) {
            mutex_.unlock();
            std::cout << "Lock released" << std::endl;
        }
    }
    
    // Prevent copying (lock should not be copied)
    LockGuard(const LockGuard&) = delete;
    LockGuard& operator=(const LockGuard&) = delete;
    
    // Prevent moving (lock should not be moved)
    LockGuard(LockGuard&&) = delete;
    LockGuard& operator=(LockGuard&&) = delete;
};

// Example 4: Resource Manager with Rule of Three
class ResourceManager {
private:
    int* data_;
    size_t size_;
    std::string name_;
    
public:
    // Constructor
    ResourceManager(size_t size, const std::string& name = "Resource")
        : size_(size), name_(name) {
        data_ = new int[size_];
        std::fill(data_, data_ + size_, 0);
        std::cout << "ResourceManager created: " << name_ 
                  << " (size: " << size_ << ")" << std::endl;
    }
    
    // Destructor
    ~ResourceManager() {
        delete[] data_;
        std::cout << "ResourceManager destroyed: " << name_ << std::endl;
    }
    
    // Copy constructor
    ResourceManager(const ResourceManager& other)
        : size_(other.size_), name_(other.name_ + " (Copy)") {
        data_ = new int[size_];
        std::copy(other.data_, other.data_ + size_, data_);
        std::cout << "ResourceManager copied: " << name_ << std::endl;
    }
    
    // Copy assignment operator
    ResourceManager& operator=(const ResourceManager& other) {
        if (this != &other) {
            delete[] data_;
            size_ = other.size_;
            name_ = other.name_ + " (Assigned)";
            data_ = new int[size_];
            std::copy(other.data_, other.data_ + size_, data_);
        }
        return *this;
    }
    
    // Accessor methods
    int& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }
    
    const int& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }
    
    size_t size() const { return size_; }
    const std::string& getName() const { return name_; }
    
    void fill(int value) {
        std::fill(data_, data_ + size_, value);
    }
    
    void display() const {
        std::cout << name_ << ": [";
        for (size_t i = 0; i < size_; ++i) {
            std::cout << data_[i];
            if (i < size_ - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
};

// Example 5: Modern Resource Manager with Rule of Five
class ModernResourceManager {
private:
    std::unique_ptr<int[]> data_;
    size_t size_;
    std::string name_;
    
public:
    // Constructor
    ModernResourceManager(size_t size, const std::string& name = "ModernResource")
        : size_(size), name_(name) {
        data_ = std::make_unique<int[]>(size_);
        std::fill(data_.get(), data_.get() + size_, 0);
        std::cout << "ModernResourceManager created: " << name_ 
                  << " (size: " << size_ << ")" << std::endl;
    }
    
    // Destructor (defaulted - smart pointer handles cleanup)
    ~ModernResourceManager() = default;
    
    // Copy constructor
    ModernResourceManager(const ModernResourceManager& other)
        : size_(other.size_), name_(other.name_ + " (Copy)") {
        data_ = std::make_unique<int[]>(size_);
        std::copy(other.data_.get(), other.data_.get() + size_, data_.get());
        std::cout << "ModernResourceManager copied: " << name_ << std::endl;
    }
    
    // Copy assignment operator
    ModernResourceManager& operator=(const ModernResourceManager& other) {
        if (this != &other) {
            data_ = std::make_unique<int[]>(other.size_);
            size_ = other.size_;
            name_ = other.name_ + " (Assigned)";
            std::copy(other.data_.get(), other.data_.get() + size_, data_.get());
        }
        return *this;
    }
    
    // Move constructor
    ModernResourceManager(ModernResourceManager&& other) noexcept
        : data_(std::move(other.data_)), size_(other.size_), name_(std::move(other.name_)) {
        other.size_ = 0;
        std::cout << "ModernResourceManager moved: " << name_ << std::endl;
    }
    
    // Move assignment operator
    ModernResourceManager& operator=(ModernResourceManager&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
            size_ = other.size_;
            name_ = std::move(other.name_);
            other.size_ = 0;
        }
        return *this;
    }
    
    // Accessor methods
    int& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }
    
    const int& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }
    
    size_t size() const { return size_; }
    const std::string& getName() const { return name_; }
    
    void fill(int value) {
        std::fill(data_.get(), data_.get() + size_, value);
    }
    
    void display() const {
        std::cout << name_ << ": [";
        for (size_t i = 0; i < size_; ++i) {
            std::cout << data_[i];
            if (i < size_ - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
};

// Example 6: Rule of Zero Implementation
class RuleOfZeroClass {
private:
    std::string name_;
    std::vector<int> data_;
    std::unique_ptr<std::string> description_;
    
public:
    // Constructor
    RuleOfZeroClass(const std::string& name, const std::vector<int>& data)
        : name_(name), data_(data) {
        description_ = std::make_unique<std::string>("This is " + name);
        std::cout << "RuleOfZeroClass created: " << name_ << std::endl;
    }
    
    // No need to implement destructor, copy constructor, etc.
    // Compiler-generated versions work correctly with smart pointers and standard containers
    
    // Getters
    const std::string& getName() const { return name_; }
    const std::vector<int>& getData() const { return data_; }
    const std::string& getDescription() const { return *description_; }
    
    void display() const {
        std::cout << "RuleOfZeroClass: " << name_ << std::endl;
        std::cout << "Description: " << *description_ << std::endl;
        std::cout << "Data: [";
        for (size_t i = 0; i < data_.size(); ++i) {
            std::cout << data_[i];
            if (i < data_.size() - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
};

// Function to demonstrate basic constructors and destructors
void demonstrateBasicConstructorsDestructors() {
    std::cout << "=== Basic Constructors and Destructors ===" << std::endl;
    
    std::cout << "Creating students..." << std::endl;
    Student s1;  // Default constructor
    Student s2("Alice", 20, 3.8);  // Parameterized constructor
    Student s3("Bob", 22, 3.5);    // Parameterized constructor
    
    std::cout << "\nTotal students: " << Student::getTotalStudents() << std::endl;
    
    s1.display();
    s2.display();
    s3.display();
    
    std::cout << "\nStudents will be destroyed when leaving scope..." << std::endl;
}

// Function to demonstrate RAII
void demonstrateRAII() {
    std::cout << "\n=== RAII Demonstration ===" << std::endl;
    
    try {
        // Create file manager (RAII)
        FileManager file("test_file.txt");
        
        if (file.isOpen()) {
            file.write("Hello, RAII!");
            file.write("This is a test file.");
            
            std::string content = file.read();
            std::cout << "File content: " << content << std::endl;
        }
        
        // File will be automatically closed when file goes out of scope
        std::cout << "File manager will be destroyed automatically..." << std::endl;
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

// Function to demonstrate mutex RAII
void demonstrateMutexRAII() {
    std::cout << "\n=== Mutex RAII Demonstration ===" << std::endl;
    
    static std::mutex shared_mutex;
    static int shared_counter = 0;
    
    // Lock will be acquired in constructor, released in destructor
    {
        LockGuard lock(shared_mutex);
        shared_counter++;
        std::cout << "Counter incremented to: " << shared_counter << std::endl;
        // Lock will be automatically released when lock goes out of scope
    }
    
    std::cout << "Lock automatically released" << std::endl;
}

// Function to demonstrate Rule of Three
void demonstrateRuleOfThree() {
    std::cout << "\n=== Rule of Three Demonstration ===" << std::endl;
    
    ResourceManager rm1(5, "Manager1");
    rm1.fill(10);
    rm1.display();
    
    // Copy constructor
    ResourceManager rm2 = rm1;
    rm2[0] = 99;
    rm2.display();
    
    // Copy assignment
    ResourceManager rm3(3, "Manager3");
    rm3 = rm1;
    rm3[1] = 88;
    rm3.display();
    
    std::cout << "All managers will be destroyed automatically..." << std::endl;
}

// Function to demonstrate Rule of Five
void demonstrateRuleOfFive() {
    std::cout << "\n=== Rule of Five Demonstration ===" << std::endl;
    
    ModernResourceManager mrm1(5, "ModernManager1");
    mrm1.fill(20);
    mrm1.display();
    
    // Copy constructor
    ModernResourceManager mrm2 = mrm1;
    mrm2[0] = 99;
    mrm2.display();
    
    // Move constructor
    ModernResourceManager mrm3 = std::move(mrm1);
    mrm3[1] = 77;
    mrm3.display();
    
    std::cout << "mrm1 size after move: " << mrm1.size() << std::endl;
    
    // Move assignment
    ModernResourceManager mrm4(3, "ModernManager4");
    mrm4 = std::move(mrm2);
    mrm4[2] = 66;
    mrm4.display();
    
    std::cout << "All modern managers will be destroyed automatically..." << std::endl;
}

// Function to demonstrate Rule of Zero
void demonstrateRuleOfZero() {
    std::cout << "\n=== Rule of Zero Demonstration ===" << std::endl;
    
    RuleOfZeroClass roc1("Object1", {1, 2, 3, 4, 5});
    roc1.display();
    
    // Copy constructor (compiler-generated)
    RuleOfZeroClass roc2 = roc1;
    roc2.display();
    
    // Move constructor (compiler-generated)
    RuleOfZeroClass roc3 = std::move(roc1);
    roc3.display();
    
    std::cout << "All Rule of Zero objects will be destroyed automatically..." << std::endl;
}

// Function to demonstrate constructor exceptions
void demonstrateConstructorExceptions() {
    std::cout << "\n=== Constructor Exceptions Demonstration ===" << std::endl;
    
    try {
        Student s("Charlie", 19, 5.0);  // Invalid GPA
    } catch (const std::invalid_argument& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    try {
        FileManager file("nonexistent_file.txt");
    } catch (const std::runtime_error& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

// Function to demonstrate constructor delegation
void demonstrateConstructorDelegation() {
    std::cout << "\n=== Constructor Delegation Demonstration ===" << std::endl;
    
    class DelegatedClass {
    private:
        int value_;
        std::string name_;
        
    public:
        // Target constructor
        DelegatedClass(int value, const std::string& name)
            : value_(value), name_(name) {
            std::cout << "DelegatedClass created: " << name_ << " = " << value_ << std::endl;
        }
        
        // Delegating constructors
        DelegatedClass() : DelegatedClass(0, "Default") {}
        DelegatedClass(int value) : DelegatedClass(value, "Unnamed") {}
        DelegatedClass(const std::string& name) : DelegatedClass(42, name) {}
    };
    
    DelegatedClass dc1;
    DelegatedClass dc2(100);
    DelegatedClass dc3("Custom");
    DelegatedClass dc4(200, "Full");
}

int main() {
    std::cout << "=== Constructors and Destructors Demonstration ===" << std::endl;
    std::cout << "This program demonstrates constructor types, destructor implementation,\n"
              << "RAII principles, copy and move semantics, and the Rule of Three/Five/Zero.\n" << std::endl;
    
    // Demonstrate various constructor and destructor concepts
    demonstrateBasicConstructorsDestructors();
    demonstrateRAII();
    demonstrateMutexRAII();
    demonstrateRuleOfThree();
    demonstrateRuleOfFive();
    demonstrateRuleOfZero();
    demonstrateConstructorExceptions();
    demonstrateConstructorDelegation();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Constructors initialize objects and acquire resources" << std::endl;
    std::cout << "2. Destructors clean up resources (RAII principle)" << std::endl;
    std::cout << "3. Initializer lists are more efficient than assignment" << std::endl;
    std::cout << "4. Copy semantics ensure proper object duplication" << std::endl;
    std::cout << "5. Move semantics improve performance for temporary objects" << std::endl;
    std::cout << "6. Rule of Three/Five/Zero guides resource management" << std::endl;
    std::cout << "7. Smart pointers help implement Rule of Zero" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -pthread -o constructors_destructors 02_Constructors_and_Destructors.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -pthread -o constructors_destructors 02_Constructors_and_Destructors.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 02_Constructors_and_Destructors.cpp
 * 
 * Running:
 * ./constructors_destructors (Linux/macOS)
 * constructors_destructors.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for smart pointers and move semantics.
 * C++17 is recommended for best constructor and destructor support.
 * 
 * Constructor/Destructor Notes:
 * - Use initializer lists for member initialization
 * - Implement RAII for automatic resource management
 * - Follow Rule of Three/Five/Zero for resource management
 * - Use smart pointers to avoid manual memory management
 * - Make destructors virtual in base classes
 * - Handle constructor exceptions properly
 * - Use constructor delegation to reduce code duplication
 */"""
