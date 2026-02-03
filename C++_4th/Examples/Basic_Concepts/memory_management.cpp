#include <iostream>
#include <memory>
#include <vector>
#include <string>

// Demonstrates various memory management techniques in C++
class MemoryDemo {
private:
    int* raw_ptr;
    std::unique_ptr<int> unique_ptr;
    std::shared_ptr<int> shared_ptr;
    std::weak_ptr<int> weak_ptr;
    
public:
    MemoryDemo() : raw_ptr(nullptr) {
        std::cout << "MemoryDemo constructor called" << std::endl;
    }
    
    ~MemoryDemo() {
        std::cout << "MemoryDemo destructor called" << std::endl;
        // Clean up raw pointer if allocated
        if (raw_ptr) {
            delete raw_ptr;
            raw_ptr = nullptr;
        }
    }
    
    // Demonstrate raw pointer management
    void demonstrate_raw_pointers() {
        std::cout << "\n=== Raw Pointer Management ===" << std::endl;
        
        // Allocate memory
        raw_ptr = new int(42);
        std::cout << "Allocated raw pointer with value: " << *raw_ptr << std::endl;
        
        // Use the pointer
        *raw_ptr = 100;
        std::cout << "Modified value: " << *raw_ptr << std::endl;
        
        // Deallocate memory
        delete raw_ptr;
        raw_ptr = nullptr;
        std::cout << "Deallocated raw pointer" << std::endl;
    }
    
    // Demonstrate unique_ptr
    void demonstrate_unique_ptr() {
        std::cout << "\n=== Unique Pointer Management ===" << std::endl;
        
        // Create unique_ptr
        unique_ptr = std::make_unique<int>(200);
        std::cout << "Created unique_ptr with value: " << *unique_ptr << std::endl;
        
        // Transfer ownership
        std::unique_ptr<int> another_ptr = std::move(unique_ptr);
        std::cout << "Transferred ownership, new value: " << *another_ptr << std::endl;
        std::cout << "Original unique_ptr is now: " << (unique_ptr ? "valid" : "null") << std::endl;
        
        // Reset the pointer
        another_ptr.reset();
        std::cout << "Reset unique_ptr, it is now: " << (another_ptr ? "valid" : "null") << std::endl;
    }
    
    // Demonstrate shared_ptr
    void demonstrate_shared_ptr() {
        std::cout << "\n=== Shared Pointer Management ===" << std::endl;
        
        // Create shared_ptr
        shared_ptr = std::make_shared<int>(300);
        std::cout << "Created shared_ptr with value: " << *shared_ptr << std::endl;
        std::cout << "Reference count: " << shared_ptr.use_count() << std::endl;
        
        // Create another shared_ptr pointing to the same object
        std::shared_ptr<int> another_shared = shared_ptr;
        std::cout << "Created another shared_ptr, reference count: " << shared_ptr.use_count() << std::endl;
        
        // Create weak_ptr
        weak_ptr = shared_ptr;
        std::cout << "Created weak_ptr, reference count: " << shared_ptr.use_count() << std::endl;
        
        // Check if weak_ptr is valid
        if (auto locked = weak_ptr.lock()) {
            std::cout << "Weak_ptr is valid, value: " << *locked << std::endl;
        }
        
        // Reset one shared_ptr
        another_shared.reset();
        std::cout << "Reset one shared_ptr, reference count: " << shared_ptr.use_count() << std::endl;
        
        // Reset the original shared_ptr
        shared_ptr.reset();
        std::cout << "Reset original shared_ptr, reference count: " << shared_ptr.use_count() << std::endl;
        
        // Check if weak_ptr is still valid
        if (auto locked = weak_ptr.lock()) {
            std::cout << "Weak_ptr is still valid, value: " << *locked << std::endl;
        } else {
            std::cout << "Weak_ptr is no longer valid" << std::endl;
        }
    }
    
    // Demonstrate array allocation
    void demonstrate_array_allocation() {
        std::cout << "\n=== Array Allocation ===" << std::endl;
        
        // Raw array allocation
        int* raw_array = new int[5]{1, 2, 3, 4, 5};
        std::cout << "Raw array: ";
        for (int i = 0; i < 5; ++i) {
            std::cout << raw_array[i] << " ";
        }
        std::cout << std::endl;
        delete[] raw_array;
        
        // Smart pointer array allocation
        auto smart_array = std::make_unique<int[]>(5);
        for (int i = 0; i < 5; ++i) {
            smart_array[i] = (i + 1) * 10;
        }
        std::cout << "Smart array: ";
        for (int i = 0; i < 5; ++i) {
            std::cout << smart_array[i] << " ";
        }
        std::cout << std::endl;
        
        // Vector (recommended for dynamic arrays)
        std::vector<int> vec{100, 200, 300, 400, 500};
        std::cout << "Vector: ";
        for (int val : vec) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    
    // Demonstrate memory alignment
    void demonstrate_memory_alignment() {
        std::cout << "\n=== Memory Alignment ===" << std::endl;
        
        struct AlignedStruct {
            char c;      // 1 byte
            int i;       // 4 bytes
            double d;    // 8 bytes
        };
        
        std::cout << "Size of AlignedStruct: " << sizeof(AlignedStruct) << " bytes" << std::endl;
        std::cout << "Alignment of AlignedStruct: " << alignof(AlignedStruct) << " bytes" << std::endl;
        
        // Demonstrate alignment requirements
        std::cout << "Alignment of char: " << alignof(char) << " bytes" << std::endl;
        std::cout << "Alignment of int: " << alignof(int) << " bytes" << std::endl;
        std::cout << "Alignment of double: " << alignof(double) << " bytes" << std::endl;
    }
};

// RAII wrapper for file operations
class FileWrapper {
private:
    FILE* file;
    std::string filename;
    
public:
    FileWrapper(const std::string& name) : filename(name) {
        file = fopen(filename.c_str(), "w");
        if (file) {
            std::cout << "Opened file: " << filename << std::endl;
        } else {
            std::cout << "Failed to open file: " << filename << std::endl;
        }
    }
    
    ~FileWrapper() {
        if (file) {
            fclose(file);
            std::cout << "Closed file: " << filename << std::endl;
        }
    }
    
    // Delete copy constructor and assignment operator
    FileWrapper(const FileWrapper&) = delete;
    FileWrapper& operator=(const FileWrapper&) = delete;
    
    // Allow move constructor and assignment
    FileWrapper(FileWrapper&& other) noexcept 
        : file(other.file), filename(std::move(other.filename)) {
        other.file = nullptr;
        std::cout << "Moved file: " << filename << std::endl;
    }
    
    FileWrapper& operator=(FileWrapper&& other) noexcept {
        if (this != &other) {
            if (file) {
                fclose(file);
            }
            file = other.file;
            filename = std::move(other.filename);
            other.file = nullptr;
        }
        return *this;
    }
    
    void write(const std::string& content) {
        if (file) {
            fprintf(file, "%s", content.c_str());
        }
    }
};

// Demonstrate custom allocator
template<typename T>
class CustomAllocator {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    
    template<typename U>
    struct rebind {
        using other = CustomAllocator<U>;
    };
    
    CustomAllocator() = default;
    
    template<typename U>
    CustomAllocator(const CustomAllocator<U>&) {}
    
    pointer allocate(size_type n) {
        std::cout << "Custom allocator: allocating " << n << " objects of size " << sizeof(T) << std::endl;
        return static_cast<pointer>(::operator new(n * sizeof(T)));
    }
    
    void deallocate(pointer p, size_type n) {
        std::cout << "Custom allocator: deallocating " << n << " objects" << std::endl;
        ::operator delete(p);
    }
    
    template<typename U, typename... Args>
    void construct(U* p, Args&&... args) {
        new(p) U(std::forward<Args>(args)...);
    }
    
    template<typename U>
    void destroy(U* p) {
        p->~U();
    }
};

int main() {
    std::cout << "Memory Management Examples" << std::endl;
    std::cout << "=========================" << std::endl;
    
    // Create MemoryDemo object
    MemoryDemo demo;
    
    // Demonstrate various memory management techniques
    demo.demonstrate_raw_pointers();
    demo.demonstrate_unique_ptr();
    demo.demonstrate_shared_ptr();
    demo.demonstrate_array_allocation();
    demo.demonstrate_memory_alignment();
    
    // Demonstrate RAII with file operations
    std::cout << "\n=== RAII File Operations ===" << std::endl;
    {
        FileWrapper file("test.txt");
        file.write("Hello, World!\n");
        file.write("This is a test file.\n");
    } // File is automatically closed here
    
    // Demonstrate custom allocator
    std::cout << "\n=== Custom Allocator ===" << std::endl;
    std::vector<int, CustomAllocator<int>> custom_vec;
    custom_vec.push_back(1);
    custom_vec.push_back(2);
    custom_vec.push_back(3);
    
    std::cout << "Custom vector contents: ";
    for (int val : custom_vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    std::cout << "\nMemory management examples completed!" << std::endl;
    return 0;
}
