/*
 * Lesson 15.2: Advanced Memory Management
 * 
 * This file demonstrates advanced memory management techniques,
 * custom allocators, memory pools, and RAII patterns.
 */

#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include <unordered_map>
#include <algorithm>
#include <chrono>
#include <random>
#include <thread>
#include <mutex>
#include <atomic>
#include <new>
#include <cstdlib>
#include <cstring>

// Example 1: Custom Allocators
namespace CustomAllocators {
    
    // Stack-based allocator
    template<size_t Size>
    class StackAllocator {
    private:
        alignas(alignof(std::max_align_t)) char buffer_[Size];
        size_t offset_;
        
    public:
        using value_type = void;
        using pointer = void*;
        using const_pointer = const void*;
        using size_type = size_t;
        using difference_type = std::ptrdiff_t;
        
        StackAllocator() : offset_(0) {}
        
        pointer allocate(size_type bytes) {
            size_type aligned_size = (bytes + alignof(std::max_align_t) - 1) & ~(alignof(std::max_align_t) - 1);
            
            if (offset_ + aligned_size > Size) {
                throw std::bad_alloc();
            }
            
            pointer result = buffer_ + offset_;
            offset_ += aligned_size;
            return result;
        }
        
        void deallocate(pointer, size_type) {
            // Stack allocator doesn't support individual deallocation
        }
        
        size_type max_size() const {
            return Size;
        }
        
        void reset() {
            offset_ = 0;
        }
        
        size_type used() const {
            return offset_;
        }
    };
    
    // Pool allocator
    template<typename T, size_t PoolSize>
    class PoolAllocator {
    private:
        struct Node {
            Node* next;
        };
        
        alignas(alignof(T)) char pool_[PoolSize * sizeof(T)];
        Node* free_list_;
        size_t allocated_count_;
        
    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using size_type = size_t;
        using difference_type = std::ptrdiff_t;
        
        PoolAllocator() : free_list_(nullptr), allocated_count_(0) {
            // Initialize free list
            for (size_t i = 0; i < PoolSize; ++i) {
                Node* node = reinterpret_cast<Node*>(pool_ + i * sizeof(T));
                node->next = free_list_;
                free_list_ = node;
            }
        }
        
        pointer allocate(size_type n) {
            if (n != 1) {
                throw std::bad_alloc();
            }
            
            if (!free_list_) {
                throw std::bad_alloc();
            }
            
            Node* node = free_list_;
            free_list_ = free_list_->next;
            ++allocated_count_;
            
            return reinterpret_cast<pointer>(node);
        }
        
        void deallocate(pointer p, size_type n) {
            if (n != 1) return;
            
            Node* node = reinterpret_cast<Node*>(p);
            node->next = free_list_;
            free_list_ = node;
            --allocated_count_;
        }
        
        size_type max_size() const {
            return PoolSize;
        }
        
        size_type allocated() const {
            return allocated_count_;
        }
        
        size_type available() const {
            return PoolSize - allocated_count_;
        }
    };
    
    // Thread-safe allocator
    template<typename Allocator>
    class ThreadSafeAllocator {
    private:
        Allocator allocator_;
        mutable std::mutex mutex_;
        
    public:
        using value_type = typename Allocator::value_type;
        using pointer = typename Allocator::pointer;
        using const_pointer = typename Allocator::const_pointer;
        using size_type = typename Allocator::size_type;
        using difference_type = typename Allocator::difference_type;
        
        pointer allocate(size_type n) {
            std::lock_guard<std::mutex> lock(mutex_);
            return allocator_.allocate(n);
        }
        
        void deallocate(pointer p, size_type n) {
            std::lock_guard<std::mutex> lock(mutex_);
            allocator_.deallocate(p, n);
        }
        
        size_type max_size() const {
            std::lock_guard<std::mutex> lock(mutex_);
            return allocator_.max_size();
        }
    };
    
    void demonstrateCustomAllocators() {
        std::cout << "=== Custom Allocators ===" << std::endl;
        
        // Stack allocator
        StackAllocator<1024> stack_alloc;
        
        auto ptr1 = stack_alloc.allocate(100);
        auto ptr2 = stack_alloc.allocate(200);
        
        std::cout << "Stack allocator used: " << stack_alloc.used() << " bytes" << std::endl;
        
        stack_alloc.reset();
        std::cout << "Stack allocator after reset: " << stack_alloc.used() << " bytes" << std::endl;
        
        // Pool allocator
        PoolAllocator<int, 100> pool_alloc;
        
        std::vector<int*, PoolAllocator<int, 100>> vec(pool_alloc);
        
        for (int i = 0; i < 10; ++i) {
            int* ptr = pool_alloc.allocate(1);
            *ptr = i;
            vec.push_back(ptr);
        }
        
        std::cout << "Pool allocator allocated: " << pool_alloc.allocated() << " objects" << std::endl;
        std::cout << "Pool allocator available: " << pool_alloc.available() << " objects" << std::endl;
        
        // Deallocate some objects
        for (int i = 0; i < 5; ++i) {
            pool_alloc.deallocate(vec.back(), 1);
            vec.pop_back();
        }
        
        std::cout << "Pool allocator after deallocation: " << pool_alloc.allocated() << " objects" << std::endl;
        
        // Thread-safe allocator
        ThreadSafeAllocator<PoolAllocator<int, 100>> thread_safe_alloc;
        
        std::vector<std::thread> threads;
        for (int i = 0; i < 5; ++i) {
            threads.emplace_back([&thread_safe_alloc, i]() {
                for (int j = 0; j < 10; ++j) {
                    int* ptr = thread_safe_alloc.allocate(1);
                    *ptr = i * 10 + j;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    thread_safe_alloc.deallocate(ptr, 1);
                }
            });
        }
        
        for (auto& t : threads) {
            t.join();
        }
        
        std::cout << "Thread-safe allocator test completed" << std::endl;
    }
}

// Example 2: Memory Pools
namespace MemoryPools {
    
    // Fixed-size memory pool
    template<typename T, size_t BlockSize>
    class FixedSizePool {
    private:
        struct Block {
            alignas(alignof(T)) char data_[BlockSize];
            Block* next;
        };
        
        std::vector<std::unique_ptr<Block>> blocks_;
        Block* free_list_;
        size_t block_count_;
        
    public:
        FixedSizePool() : free_list_(nullptr), block_count_(0) {}
        
        void* allocate() {
            if (!free_list_) {
                allocate_new_block();
            }
            
            Block* block = free_list_;
            free_list_ = free_list_->next;
            
            return block->data_;
        }
        
        void deallocate(void* ptr) {
            if (!ptr) return;
            
            Block* block = reinterpret_cast<Block*>(
                static_cast<char*>(ptr) - offsetof(Block, data_)
            );
            
            block->next = free_list_;
            free_list_ = block;
        }
        
        size_t block_count() const {
            return block_count_;
        }
        
    private:
        void allocate_new_block() {
            auto block = std::make_unique<Block>();
            block->next = free_list_;
            free_list_ = block.get();
            blocks_.push_back(std::move(block));
            ++block_count_;
        }
    };
    
    // Variable-size memory pool
    class VariableSizePool {
    private:
        struct Chunk {
            size_t size;
            bool free;
            Chunk* next;
            Chunk* prev;
        };
        
        static constexpr size_t MIN_CHUNK_SIZE = sizeof(Chunk);
        static constexpr size_t ALIGNMENT = alignof(std::max_align_t);
        
        char* memory_;
        size_t total_size_;
        Chunk* free_list_;
        
    public:
        explicit VariableSizePool(size_t size) : total_size_(size) {
            memory_ = static_cast<char*>(std::aligned_alloc(ALIGNMENT, size));
            if (!memory_) {
                throw std::bad_alloc();
            }
            
            Chunk* chunk = reinterpret_cast<Chunk*>(memory_);
            chunk->size = size - sizeof(Chunk);
            chunk->free = true;
            chunk->next = nullptr;
            chunk->prev = nullptr;
            
            free_list_ = chunk;
        }
        
        ~VariableSizePool() {
            std::free(memory_);
        }
        
        void* allocate(size_t size) {
            size_t aligned_size = (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
            size_t total_size = aligned_size + sizeof(Chunk);
            
            Chunk* chunk = find_free_chunk(total_size);
            if (!chunk) {
                return nullptr;
            }
            
            split_chunk(chunk, total_size);
            chunk->free = false;
            
            return reinterpret_cast<char*>(chunk) + sizeof(Chunk);
        }
        
        void deallocate(void* ptr) {
            if (!ptr) return;
            
            Chunk* chunk = reinterpret_cast<Chunk*>(
                static_cast<char*>(ptr) - sizeof(Chunk)
            );
            
            chunk->free = true;
            merge_free_chunks(chunk);
        }
        
        size_t total_size() const {
            return total_size_;
        }
        
        size_t used_size() const {
            size_t used = 0;
            Chunk* chunk = reinterpret_cast<Chunk*>(memory_);
            
            while (chunk) {
                if (!chunk->free) {
                    used += chunk->size + sizeof(Chunk);
                }
                chunk = chunk->next;
            }
            
            return used;
        }
        
    private:
        Chunk* find_free_chunk(size_t size) {
            Chunk* chunk = free_list_;
            while (chunk) {
                if (chunk->size >= size) {
                    return chunk;
                }
                chunk = chunk->next;
            }
            return nullptr;
        }
        
        void split_chunk(Chunk* chunk, size_t size) {
            if (chunk->size > size + sizeof(Chunk)) {
                Chunk* new_chunk = reinterpret_cast<Chunk*>(
                    reinterpret_cast<char*>(chunk) + size
                );
                new_chunk->size = chunk->size - size;
                new_chunk->free = true;
                new_chunk->next = chunk->next;
                new_chunk->prev = chunk;
                
                if (chunk->next) {
                    chunk->next->prev = new_chunk;
                }
                
                chunk->size = size - sizeof(Chunk);
                chunk->next = new_chunk;
            }
        }
        
        void merge_free_chunks(Chunk* chunk) {
            // Merge with next chunk if it's free
            if (chunk->next && chunk->next->free) {
                chunk->size += chunk->next->size + sizeof(Chunk);
                chunk->next = chunk->next->next;
                if (chunk->next) {
                    chunk->next->prev = chunk;
                }
            }
            
            // Merge with previous chunk if it's free
            if (chunk->prev && chunk->prev->free) {
                chunk->prev->size += chunk->size + sizeof(Chunk);
                chunk->prev->next = chunk->next;
                if (chunk->next) {
                    chunk->next->prev = chunk->prev;
                }
            }
        }
    };
    
    void demonstrateMemoryPools() {
        std::cout << "\n=== Memory Pools ===" << std::endl;
        
        // Fixed-size pool
        FixedSizePool<int, 64> fixed_pool;
        
        std::vector<int*> ptrs;
        for (int i = 0; i < 10; ++i) {
            int* ptr = static_cast<int*>(fixed_pool.allocate());
            *ptr = i;
            ptrs.push_back(ptr);
        }
        
        std::cout << "Fixed-size pool allocated " << ptrs.size() << " objects" << std::endl;
        std::cout << "Fixed-size pool block count: " << fixed_pool.block_count() << std::endl;
        
        // Deallocate some objects
        for (int i = 0; i < 5; ++i) {
            fixed_pool.deallocate(ptrs[i]);
        }
        
        std::cout << "Fixed-size pool after deallocation" << std::endl;
        
        // Variable-size pool
        VariableSizePool variable_pool(1024);
        
        void* ptr1 = variable_pool.allocate(100);
        void* ptr2 = variable_pool.allocate(200);
        void* ptr3 = variable_pool.allocate(50);
        
        std::cout << "Variable-size pool used: " << variable_pool.used_size() << " bytes" << std::endl;
        std::cout << "Variable-size pool total: " << variable_pool.total_size() << " bytes" << std::endl;
        
        variable_pool.deallocate(ptr2);
        std::cout << "Variable-size pool after deallocation: " << variable_pool.used_size() << " bytes" << std::endl;
        
        variable_pool.deallocate(ptr1);
        variable_pool.deallocate(ptr3);
        std::cout << "Variable-size pool after all deallocations: " << variable_pool.used_size() << " bytes" << std::endl;
    }
}

// Example 3: RAII Patterns
namespace RAIIPatterns {
    
    // Resource wrapper
    template<typename T, typename Deleter>
    class ResourceWrapper {
    private:
        T resource_;
        Deleter deleter_;
        
    public:
        ResourceWrapper(T resource, Deleter deleter) : resource_(resource), deleter_(deleter) {}
        
        ~ResourceWrapper() {
            if (resource_) {
                deleter_(resource_);
            }
        }
        
        ResourceWrapper(const ResourceWrapper&) = delete;
        ResourceWrapper& operator=(const ResourceWrapper&) = delete;
        
        ResourceWrapper(ResourceWrapper&& other) noexcept : resource_(other.resource_), deleter_(other.deleter_) {
            other.resource_ = T{};
        }
        
        ResourceWrapper& operator=(ResourceWrapper&& other) noexcept {
            if (this != &other) {
                if (resource_) {
                    deleter_(resource_);
                }
                resource_ = other.resource_;
                deleter_ = other.deleter_;
                other.resource_ = T{};
            }
            return *this;
        }
        
        T get() const { return resource_; }
        T release() {
            T temp = resource_;
            resource_ = T{};
            return temp;
        }
        
        explicit operator bool() const { return static_cast<bool>(resource_); }
    };
    
    // File handle wrapper
    class FileHandle {
    private:
        FILE* file_;
        
    public:
        explicit FileHandle(const char* filename, const char* mode) : file_(nullptr) {
            file_ = std::fopen(filename, mode);
            if (!file_) {
                throw std::runtime_error("Failed to open file");
            }
        }
        
        ~FileHandle() {
            if (file_) {
                std::fclose(file_);
            }
        }
        
        FileHandle(const FileHandle&) = delete;
        FileHandle& operator=(const FileHandle&) = delete;
        
        FileHandle(FileHandle&& other) noexcept : file_(other.file_) {
            other.file_ = nullptr;
        }
        
        FileHandle& operator=(FileHandle&& other) noexcept {
            if (this != &other) {
                if (file_) {
                    std::fclose(file_);
                }
                file_ = other.file_;
                other.file_ = nullptr;
            }
            return *this;
        }
        
        FILE* get() const { return file_; }
        FILE* release() {
            FILE* temp = file_;
            file_ = nullptr;
            return temp;
        }
        
        explicit operator bool() const { return file_ != nullptr; }
    };
    
    // Lock wrapper
    template<typename Mutex>
    class LockWrapper {
    private:
        Mutex& mutex_;
        bool locked_;
        
    public:
        explicit LockWrapper(Mutex& mutex) : mutex_(mutex), locked_(true) {
            mutex_.lock();
        }
        
        ~LockWrapper() {
            if (locked_) {
                mutex_.unlock();
            }
        }
        
        LockWrapper(const LockWrapper&) = delete;
        LockWrapper& operator=(const LockWrapper&) = delete;
        
        LockWrapper(LockWrapper&& other) noexcept : mutex_(other.mutex_), locked_(other.locked_) {
            other.locked_ = false;
        }
        
        LockWrapper& operator=(LockWrapper&& other) noexcept {
            if (this != &other) {
                if (locked_) {
                    mutex_.unlock();
                }
                mutex_ = other.mutex_;
                locked_ = other.locked_;
                other.locked_ = false;
            }
            return *this;
        }
        
        void unlock() {
            if (locked_) {
                mutex_.unlock();
                locked_ = false;
            }
        }
        
        bool is_locked() const { return locked_; }
    };
    
    // Memory pool wrapper
    template<typename Pool>
    class PoolWrapper {
    private:
        Pool& pool_;
        void* ptr_;
        
    public:
        PoolWrapper(Pool& pool, size_t size) : pool_(pool), ptr_(nullptr) {
            ptr_ = pool_.allocate(size);
            if (!ptr_) {
                throw std::bad_alloc();
            }
        }
        
        ~PoolWrapper() {
            if (ptr_) {
                pool_.deallocate(ptr_);
            }
        }
        
        PoolWrapper(const PoolWrapper&) = delete;
        PoolWrapper& operator=(const PoolWrapper&) = delete;
        
        PoolWrapper(PoolWrapper&& other) noexcept : pool_(other.pool_), ptr_(other.ptr_) {
            other.ptr_ = nullptr;
        }
        
        PoolWrapper& operator=(PoolWrapper&& other) noexcept {
            if (this != &other) {
                if (ptr_) {
                    pool_.deallocate(ptr_);
                }
                pool_ = other.pool_;
                ptr_ = other.ptr_;
                other.ptr_ = nullptr;
            }
            return *this;
        }
        
        void* get() const { return ptr_; }
        void* release() {
            void* temp = ptr_;
            ptr_ = nullptr;
            return temp;
        }
        
        explicit operator bool() const { return ptr_ != nullptr; }
    };
    
    void demonstrateRAIIPatterns() {
        std::cout << "\n=== RAII Patterns ===" << std::endl;
        
        // Resource wrapper
        {
            ResourceWrapper<int*, std::function<void(int*)>> resource(
                new int(42),
                [](int* ptr) { delete ptr; }
            );
            
            std::cout << "Resource value: " << *resource.get() << std::endl;
        }
        std::cout << "Resource automatically cleaned up" << std::endl;
        
        // File handle wrapper
        try {
            FileHandle file("test.txt", "w");
            if (file) {
                std::fprintf(file.get(), "Hello, World!\n");
                std::cout << "File written successfully" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "File error: " << e.what() << std::endl;
        }
        
        // Lock wrapper
        std::mutex mutex;
        {
            LockWrapper<std::mutex> lock(mutex);
            std::cout << "Lock acquired, doing critical work..." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        std::cout << "Lock automatically released" << std::endl;
        
        // Memory pool wrapper
        MemoryPools::VariableSizePool pool(1024);
        {
            PoolWrapper<MemoryPools::VariableSizePool> pool_ptr(pool, 100);
            if (pool_ptr) {
                std::cout << "Memory allocated from pool" << std::endl;
            }
        }
        std::cout << "Memory automatically returned to pool" << std::endl;
    }
}

// Example 4: Memory Optimization Techniques
namespace MemoryOptimization {
    
    // Object pool for reuse
    template<typename T>
    class ObjectPool {
    private:
        std::vector<std::unique_ptr<T>> objects_;
        std::vector<T*> available_;
        std::mutex mutex_;
        
    public:
        ObjectPool(size_t initial_size = 10) {
            objects_.reserve(initial_size);
            available_.reserve(initial_size);
            
            for (size_t i = 0; i < initial_size; ++i) {
                objects_.push_back(std::make_unique<T>());
                available_.push_back(objects_.back().get());
            }
        }
        
        T* acquire() {
            std::lock_guard<std::mutex> lock(mutex_);
            
            if (available_.empty()) {
                objects_.push_back(std::make_unique<T>());
                available_.push_back(objects_.back().get());
            }
            
            T* obj = available_.back();
            available_.pop_back();
            return obj;
        }
        
        void release(T* obj) {
            if (!obj) return;
            
            std::lock_guard<std::mutex> lock(mutex_);
            available_.push_back(obj);
        }
        
        size_t size() const {
            std::lock_guard<std::mutex> lock(mutex_);
            return objects_.size();
        }
        
        size_t available() const {
            std::lock_guard<std::mutex> lock(mutex_);
            return available_.size();
        }
    };
    
    // Memory-mapped file wrapper
    class MemoryMappedFile {
    private:
        void* data_;
        size_t size_;
        int fd_;
        
    public:
        MemoryMappedFile(const char* filename, size_t size) : data_(nullptr), size_(size), fd_(-1) {
            // Simplified implementation - in real code, use mmap on Unix or MapViewOfFile on Windows
            fd_ = open(filename, O_RDWR | O_CREAT, 0644);
            if (fd_ == -1) {
                throw std::runtime_error("Failed to open file");
            }
            
            if (ftruncate(fd_, size) == -1) {
                close(fd_);
                throw std::runtime_error("Failed to set file size");
            }
            
            data_ = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0);
            if (data_ == MAP_FAILED) {
                close(fd_);
                throw std::runtime_error("Failed to map file");
            }
        }
        
        ~MemoryMappedFile() {
            if (data_ != MAP_FAILED) {
                munmap(data_, size_);
            }
            if (fd_ != -1) {
                close(fd_);
            }
        }
        
        MemoryMappedFile(const MemoryMappedFile&) = delete;
        MemoryMappedFile& operator=(const MemoryMappedFile&) = delete;
        
        void* data() const { return data_; }
        size_t size() const { return size_; }
    };
    
    // Cache-friendly data structure
    template<typename T>
    class CacheFriendlyVector {
    private:
        T* data_;
        size_t size_;
        size_t capacity_;
        
    public:
        CacheFriendlyVector() : data_(nullptr), size_(0), capacity_(0) {}
        
        ~CacheFriendlyVector() {
            delete[] data_;
        }
        
        void push_back(const T& value) {
            if (size_ >= capacity_) {
                reserve(capacity_ == 0 ? 1 : capacity_ * 2);
            }
            data_[size_++] = value;
        }
        
        void reserve(size_t new_capacity) {
            if (new_capacity > capacity_) {
                T* new_data = new T[new_capacity];
                std::copy(data_, data_ + size_, new_data);
                delete[] data_;
                data_ = new_data;
                capacity_ = new_capacity;
            }
        }
        
        T& operator[](size_t index) { return data_[index]; }
        const T& operator[](size_t index) const { return data_[index]; }
        
        size_t size() const { return size_; }
        size_t capacity() const { return capacity_; }
        
        // Cache-friendly iteration
        template<typename Func>
        void for_each(Func func) {
            for (size_t i = 0; i < size_; ++i) {
                func(data_[i]);
            }
        }
    };
    
    void demonstrateMemoryOptimization() {
        std::cout << "\n=== Memory Optimization Techniques ===" << std::endl;
        
        // Object pool
        ObjectPool<std::string> string_pool;
        
        std::vector<std::string*> strings;
        for (int i = 0; i < 10; ++i) {
            std::string* str = string_pool.acquire();
            *str = "String " + std::to_string(i);
            strings.push_back(str);
        }
        
        std::cout << "Object pool size: " << string_pool.size() << std::endl;
        std::cout << "Object pool available: " << string_pool.available() << std::endl;
        
        // Release some objects
        for (int i = 0; i < 5; ++i) {
            string_pool.release(strings[i]);
        }
        
        std::cout << "Object pool after release: " << string_pool.available() << std::endl;
        
        // Cache-friendly vector
        CacheFriendlyVector<int> cache_vec;
        
        for (int i = 0; i < 1000; ++i) {
            cache_vec.push_back(i);
        }
        
        std::cout << "Cache-friendly vector size: " << cache_vec.size() << std::endl;
        std::cout << "Cache-friendly vector capacity: " << cache_vec.capacity() << std::endl;
        
        // Performance comparison
        const size_t size = 1000000;
        
        // Standard vector
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<int> std_vec;
        for (size_t i = 0; i < size; ++i) {
            std_vec.push_back(i);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto std_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        // Cache-friendly vector
        start = std::chrono::high_resolution_clock::now();
        CacheFriendlyVector<int> cache_vec2;
        for (size_t i = 0; i < size; ++i) {
            cache_vec2.push_back(i);
        }
        end = std::chrono::high_resolution_clock::now();
        auto cache_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Standard vector time: " << std_time.count() << " microseconds" << std::endl;
        std::cout << "Cache-friendly vector time: " << cache_time.count() << " microseconds" << std::endl;
        std::cout << "Performance ratio: " << (double)std_time.count() / cache_time.count() << std::endl;
    }
}

int main() {
    std::cout << "=== Advanced Memory Management Demonstration ===" << std::endl;
    std::cout << "This program demonstrates advanced memory management techniques,\n"
              << "custom allocators, memory pools, and RAII patterns.\n" << std::endl;
    
    // Demonstrate various advanced memory management concepts
    CustomAllocators::demonstrateCustomAllocators();
    MemoryPools::demonstrateMemoryPools();
    RAIIPatterns::demonstrateRAIIPatterns();
    MemoryOptimization::demonstrateMemoryOptimization();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Custom allocators provide specialized memory management strategies" << std::endl;
    std::cout << "2. Memory pools improve performance by reducing allocation overhead" << std::endl;
    std::cout << "3. RAII patterns ensure automatic resource cleanup and exception safety" << std::endl;
    std::cout << "4. Memory optimization techniques can significantly improve performance" << std::endl;
    std::cout << "5. Object pools reduce memory fragmentation and allocation costs" << std::endl;
    std::cout << "6. Cache-friendly data structures improve memory access patterns" << std::endl;
    std::cout << "7. Proper memory management is crucial for program stability and performance" << std::endl;
    std::cout << "8. RAII eliminates many common memory management errors" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -pthread -o advanced_memory_management 02_Advanced_Memory_Management.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -pthread -o advanced_memory_management 02_Advanced_Memory_Management.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 02_Advanced_Memory_Management.cpp
 * 
 * Running:
 * ./advanced_memory_management (Linux/macOS)
 * advanced_memory_management.exe (Windows)
 * 
 * Note: This lesson requires C++17 or later for some features.
 * Some features may require platform-specific headers and libraries.
 * 
 * Advanced Memory Management Notes:
 * - Custom allocators provide specialized memory management strategies
 * - Memory pools improve performance by reducing allocation overhead
 * - RAII patterns ensure automatic resource cleanup and exception safety
 * - Memory optimization techniques can significantly improve performance
 * - Object pools reduce memory fragmentation and allocation costs
 * - Cache-friendly data structures improve memory access patterns
 * - Proper memory management is crucial for program stability and performance
 * - RAII eliminates many common memory management errors
 */"""
