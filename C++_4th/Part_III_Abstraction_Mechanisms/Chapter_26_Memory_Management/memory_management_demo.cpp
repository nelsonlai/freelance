#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
#include <random>

// Demonstrates memory management techniques
int main() {
    std::cout << "Memory Management Demonstration" << std::endl;
    std::cout << "===============================" << std::endl;
    
    // 1. Custom Allocators
    std::cout << "\n1. CUSTOM ALLOCATORS:" << std::endl;
    
    template<typename T>
    class StackAllocator {
    private:
        char* memory;
        size_t size;
        size_t offset;
        
    public:
        StackAllocator(size_t s) : size(s), offset(0) {
            memory = static_cast<char*>(std::aligned_alloc(alignof(T), size));
            std::cout << "  Stack allocator created with " << size << " bytes" << std::endl;
        }
        
        ~StackAllocator() {
            std::free(memory);
            std::cout << "  Stack allocator destroyed" << std::endl;
        }
        
        T* allocate(size_t n) {
            size_t bytes = n * sizeof(T);
            if (offset + bytes > size) {
                throw std::bad_alloc();
            }
            T* ptr = reinterpret_cast<T*>(memory + offset);
            offset += bytes;
            std::cout << "  Allocated " << n << " elements at offset " << (offset - bytes) << std::endl;
            return ptr;
        }
        
        void deallocate(T*, size_t) {
            // Stack allocator doesn't support individual deallocation
        }
        
        size_t getUsedBytes() const { return offset; }
        size_t getTotalBytes() const { return size; }
    };
    
    StackAllocator<int> stack_alloc(1024);
    
    int* arr1 = stack_alloc.allocate(10);
    int* arr2 = stack_alloc.allocate(5);
    
    // Initialize arrays
    for (int i = 0; i < 10; ++i) arr1[i] = i;
    for (int i = 0; i < 5; ++i) arr2[i] = i * 2;
    
    std::cout << "  Array 1: ";
    for (int i = 0; i < 10; ++i) std::cout << arr1[i] << " ";
    std::cout << std::endl;
    
    std::cout << "  Array 2: ";
    for (int i = 0; i < 5; ++i) std::cout << arr2[i] << " ";
    std::cout << std::endl;
    
    std::cout << "  Used bytes: " << stack_alloc.getUsedBytes() << "/" << stack_alloc.getTotalBytes() << std::endl;
    
    // 2. Memory Alignment
    std::cout << "\n2. MEMORY ALIGNMENT:" << std::endl;
    
    struct AlignedStruct {
        alignas(16) double data[4];  // 16-byte aligned
        int id;
    };
    
    struct UnalignedStruct {
        double data[4];
        int id;
    };
    
    std::cout << "  AlignedStruct size: " << sizeof(AlignedStruct) << " bytes" << std::endl;
    std::cout << "  UnalignedStruct size: " << sizeof(UnalignedStruct) << " bytes" << std::endl;
    std::cout << "  AlignedStruct alignment: " << alignof(AlignedStruct) << " bytes" << std::endl;
    std::cout << "  UnalignedStruct alignment: " << alignof(UnalignedStruct) << " bytes" << std::endl;
    
    // Aligned allocation
    AlignedStruct* aligned_ptr = static_cast<AlignedStruct*>(
        std::aligned_alloc(alignof(AlignedStruct), sizeof(AlignedStruct))
    );
    
    if (aligned_ptr) {
        std::cout << "  Aligned allocation successful" << std::endl;
        std::free(aligned_ptr);
    }
    
    // 3. Smart Pointers
    std::cout << "\n3. SMART POINTERS:" << std::endl;
    
    class ManagedObject {
    private:
        int id;
        std::string data;
    public:
        ManagedObject(int i, const std::string& d) : id(i), data(d) {
            std::cout << "  ManagedObject " << id << " created" << std::endl;
        }
        
        ~ManagedObject() {
            std::cout << "  ManagedObject " << id << " destroyed" << std::endl;
        }
        
        int getId() const { return id; }
        const std::string& getData() const { return data; }
    };
    
    // unique_ptr
    std::cout << "  Using unique_ptr:" << std::endl;
    auto unique_obj = std::make_unique<ManagedObject>(1, "Unique data");
    std::cout << "    ID: " << unique_obj->getId() << ", Data: " << unique_obj->getData() << std::endl;
    
    // Transfer ownership
    auto unique_obj2 = std::move(unique_obj);
    if (!unique_obj) {
        std::cout << "    Original unique_ptr is now empty" << std::endl;
    }
    
    // shared_ptr
    std::cout << "  Using shared_ptr:" << std::endl;
    auto shared_obj = std::make_shared<ManagedObject>(2, "Shared data");
    auto shared_copy = shared_obj;
    std::cout << "    Reference count: " << shared_obj.use_count() << std::endl;
    std::cout << "    ID: " << shared_obj->getId() << ", Data: " << shared_obj->getData() << std::endl;
    
    // weak_ptr
    std::cout << "  Using weak_ptr:" << std::endl;
    std::weak_ptr<ManagedObject> weak_obj = shared_obj;
    std::cout << "    Weak pointer reference count: " << weak_obj.use_count() << std::endl;
    
    if (auto locked = weak_obj.lock()) {
        std::cout << "    Weak pointer locked successfully" << std::endl;
    }
    
    // 4. Memory Pools
    std::cout << "\n4. MEMORY POOLS:" << std::endl;
    
    class MemoryPool {
    private:
        struct Block {
            Block* next;
            bool in_use;
        };
        
        std::vector<std::unique_ptr<char[]>> memory_blocks;
        Block* free_list;
        std::mutex mutex_;
        size_t block_size_;
        size_t num_blocks_;
        
    public:
        MemoryPool(size_t block_size, size_t num_blocks) 
            : block_size_(block_size), num_blocks_(num_blocks), free_list_(nullptr) {
            
            // Allocate memory blocks
            for (size_t i = 0; i < num_blocks; ++i) {
                memory_blocks.push_back(std::make_unique<char[]>(block_size_));
                Block* block = reinterpret_cast<Block*>(memory_blocks.back().get());
                block->next = free_list_;
                block->in_use = false;
                free_list_ = block;
            }
            
            std::cout << "  Memory pool created with " << num_blocks << " blocks of " << block_size << " bytes each" << std::endl;
        }
        
        void* allocate() {
            std::lock_guard<std::mutex> lock(mutex_);
            
            if (free_list_ == nullptr) {
                std::cout << "  Memory pool exhausted" << std::endl;
                return nullptr;
            }
            
            Block* block = free_list_;
            free_list_ = block->next;
            block->in_use = true;
            
            std::cout << "  Allocated block from pool" << std::endl;
            return reinterpret_cast<void*>(block);
        }
        
        void deallocate(void* ptr) {
            if (ptr == nullptr) return;
            
            std::lock_guard<std::mutex> lock(mutex_);
            
            Block* block = reinterpret_cast<Block*>(ptr);
            block->in_use = false;
            block->next = free_list_;
            free_list_ = block;
            
            std::cout << "  Deallocated block to pool" << std::endl;
        }
        
        size_t getAvailableBlocks() const {
            std::lock_guard<std::mutex> lock(mutex_);
            size_t count = 0;
            Block* current = free_list_;
            while (current) {
                count++;
                current = current->next;
            }
            return count;
        }
    };
    
    MemoryPool pool(sizeof(int), 10);
    
    // Allocate some blocks
    std::vector<void*> allocated_blocks;
    for (int i = 0; i < 5; ++i) {
        void* block = pool.allocate();
        if (block) {
            *static_cast<int*>(block) = i;
            allocated_blocks.push_back(block);
        }
    }
    
    std::cout << "  Available blocks: " << pool.getAvailableBlocks() << std::endl;
    
    // Deallocate blocks
    for (void* block : allocated_blocks) {
        pool.deallocate(block);
    }
    
    std::cout << "  Available blocks after deallocation: " << pool.getAvailableBlocks() << std::endl;
    
    // 5. RAII and Exception Safety
    std::cout << "\n5. RAII AND EXCEPTION SAFETY:" << std::endl;
    
    class RAIIFile {
    private:
        FILE* file;
        std::string filename;
    public:
        RAIIFile(const std::string& name) : filename(name) {
            file = fopen(filename.c_str(), "w");
            if (!file) {
                throw std::runtime_error("Cannot open file: " + filename);
            }
            std::cout << "  File opened: " << filename << std::endl;
        }
        
        ~RAIIFile() {
            if (file) {
                fclose(file);
                std::cout << "  File closed: " << filename << std::endl;
            }
        }
        
        // Delete copy constructor and assignment
        RAIIFile(const RAIIFile&) = delete;
        RAIIFile& operator=(const RAIIFile&) = delete;
        
        // Move constructor
        RAIIFile(RAIIFile&& other) noexcept : file(other.file), filename(std::move(other.filename)) {
            other.file = nullptr;
            std::cout << "  File moved" << std::endl;
        }
        
        // Move assignment
        RAIIFile& operator=(RAIIFile&& other) noexcept {
            if (this != &other) {
                if (file) fclose(file);
                file = other.file;
                filename = std::move(other.filename);
                other.file = nullptr;
                std::cout << "  File move assigned" << std::endl;
            }
            return *this;
        }
        
        void write(const std::string& data) {
            if (file) {
                fprintf(file, "%s\n", data.c_str());
                std::cout << "  Written to file: " << data << std::endl;
            }
        }
    };
    
    try {
        RAIIFile file("test.txt");
        file.write("Hello, World!");
        file.write("This is RAII in action");
        
        // File automatically closed when going out of scope
    } catch (const std::exception& e) {
        std::cout << "  Exception: " << e.what() << std::endl;
    }
    
    // 6. Memory Leak Detection
    std::cout << "\n6. MEMORY LEAK DETECTION:" << std::endl;
    
    class LeakDetector {
    private:
        static std::atomic<int> allocation_count;
        static std::atomic<int> deallocation_count;
    public:
        static void* allocate(size_t size) {
            void* ptr = std::malloc(size);
            if (ptr) {
                allocation_count.fetch_add(1);
                std::cout << "  Allocation #" << allocation_count.load() << " (" << size << " bytes)" << std::endl;
            }
            return ptr;
        }
        
        static void deallocate(void* ptr) {
            if (ptr) {
                deallocation_count.fetch_add(1);
                std::cout << "  Deallocation #" << deallocation_count.load() << std::endl;
                std::free(ptr);
            }
        }
        
        static void report() {
            int allocs = allocation_count.load();
            int deallocs = deallocation_count.load();
            std::cout << "  Total allocations: " << allocs << std::endl;
            std::cout << "  Total deallocations: " << deallocs << std::endl;
            std::cout << "  Potential leaks: " << (allocs - deallocs) << std::endl;
        }
    };
    
    std::atomic<int> LeakDetector::allocation_count{0};
    std::atomic<int> LeakDetector::deallocation_count{0};
    
    // Simulate some allocations
    void* ptr1 = LeakDetector::allocate(100);
    void* ptr2 = LeakDetector::allocate(200);
    LeakDetector::deallocate(ptr1);
    // ptr2 is intentionally not deallocated to demonstrate leak detection
    
    LeakDetector::report();
    
    // Clean up
    LeakDetector::deallocate(ptr2);
    
    // 7. Performance Comparison
    std::cout << "\n7. PERFORMANCE COMPARISON:" << std::endl;
    
    const int num_allocations = 10000;
    
    // Traditional new/delete
    auto start = std::chrono::high_resolution_clock::now();
    
    std::vector<int*> traditional_ptrs;
    for (int i = 0; i < num_allocations; ++i) {
        traditional_ptrs.push_back(new int(i));
    }
    
    for (int* ptr : traditional_ptrs) {
        delete ptr;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto traditional_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Smart pointers
    start = std::chrono::high_resolution_clock::now();
    
    std::vector<std::unique_ptr<int>> smart_ptrs;
    for (int i = 0; i < num_allocations; ++i) {
        smart_ptrs.push_back(std::make_unique<int>(i));
    }
    
    end = std::chrono::high_resolution_clock::now();
    auto smart_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "  Traditional new/delete time: " << traditional_time.count() << " microseconds" << std::endl;
    std::cout << "  Smart pointers time: " << smart_time.count() << " microseconds" << std::endl;
    std::cout << "  Smart pointers overhead: " << (double)smart_time.count() / traditional_time.count() << "x" << std::endl;
    
    std::cout << "\nMemory management demonstration completed!" << std::endl;
    return 0;
}
