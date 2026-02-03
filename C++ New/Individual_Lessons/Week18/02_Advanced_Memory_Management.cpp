/*
 * Lesson 18.2: Advanced Memory Management
 * 
 * This file demonstrates advanced memory management techniques including
 * custom allocators, memory pools, garbage collection concepts,
 * memory-mapped files, and advanced RAII patterns.
 */

#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include <future>
#include <condition_variable>
#include <random>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <cassert>
#include <limits>
#include <array>
#include <tuple>
#include <type_traits>
#include <new>
#include <cstdlib>
#include <cstring>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

// Example 1: Custom Allocators
namespace CustomAllocators {
    
    // Simple linear allocator
    class LinearAllocator {
    private:
        void* memory_;
        size_t size_;
        size_t offset_;
        
    public:
        LinearAllocator(size_t size) : size_(size), offset_(0) {
            memory_ = std::aligned_alloc(64, size);  // Cache line aligned
            if (!memory_) {
                throw std::bad_alloc();
            }
        }
        
        ~LinearAllocator() {
            std::free(memory_);
        }
        
        void* allocate(size_t size, size_t alignment = alignof(std::max_align_t)) {
            // Calculate aligned offset
            size_t aligned_offset = (offset_ + alignment - 1) & ~(alignment - 1);
            
            if (aligned_offset + size > size_) {
                return nullptr;  // Out of memory
            }
            
            void* ptr = static_cast<char*>(memory_) + aligned_offset;
            offset_ = aligned_offset + size;
            return ptr;
        }
        
        void deallocate(void* ptr, size_t size) {
            // Linear allocator doesn't support individual deallocation
            // Reset the entire allocator to free all memory
        }
        
        void reset() {
            offset_ = 0;
        }
        
        size_t used() const {
            return offset_;
        }
        
        size_t available() const {
            return size_ - offset_;
        }
    };
    
    // Pool allocator for fixed-size objects
    template<typename T>
    class PoolAllocator {
    private:
        struct Block {
            alignas(T) char data[sizeof(T)];
            Block* next;
        };
        
        Block* free_list_;
        std::vector<std::unique_ptr<Block[]>> blocks_;
        size_t block_size_;
        size_t current_block_;
        size_t current_offset_;
        
    public:
        PoolAllocator(size_t block_size = 1024) 
            : free_list_(nullptr), block_size_(block_size), current_block_(0), current_offset_(0) {
            allocate_block();
        }
        
        T* allocate() {
            if (free_list_) {
                Block* block = free_list_;
                free_list_ = block->next;
                return reinterpret_cast<T*>(block->data);
            }
            
            if (current_offset_ >= block_size_) {
                allocate_block();
            }
            
            Block* block = &blocks_[current_block_][current_offset_];
            ++current_offset_;
            return reinterpret_cast<T*>(block->data);
        }
        
        void deallocate(T* ptr) {
            if (!ptr) return;
            
            Block* block = reinterpret_cast<Block*>(ptr);
            block->next = free_list_;
            free_list_ = block;
        }
        
    private:
        void allocate_block() {
            blocks_.emplace_back(std::make_unique<Block[]>(block_size_));
            current_block_ = blocks_.size() - 1;
            current_offset_ = 0;
        }
    };
    
    // STL-compatible custom allocator
    template<typename T>
    class CustomAllocator {
    private:
        PoolAllocator<T>* pool_;
        
    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        
        CustomAllocator() : pool_(new PoolAllocator<T>()) {}
        
        CustomAllocator(const CustomAllocator& other) : pool_(other.pool_) {}
        
        template<typename U>
        CustomAllocator(const CustomAllocator<U>& other) : pool_(new PoolAllocator<T>()) {}
        
        ~CustomAllocator() {
            delete pool_;
        }
        
        pointer allocate(size_type n) {
            if (n == 1) {
                return pool_->allocate();
            } else {
                return static_cast<pointer>(std::aligned_alloc(alignof(T), n * sizeof(T)));
            }
        }
        
        void deallocate(pointer p, size_type n) {
            if (n == 1) {
                pool_->deallocate(p);
            } else {
                std::free(p);
            }
        }
        
        template<typename U>
        bool operator==(const CustomAllocator<U>& other) const {
            return pool_ == other.pool_;
        }
        
        template<typename U>
        bool operator!=(const CustomAllocator<U>& other) const {
            return !(*this == other);
        }
    };
    
    void demonstrateCustomAllocators() {
        std::cout << "=== Custom Allocators ===" << std::endl;
        
        // Test linear allocator
        LinearAllocator linear_alloc(1024);
        
        int* ptr1 = static_cast<int*>(linear_alloc.allocate(sizeof(int)));
        int* ptr2 = static_cast<int*>(linear_alloc.allocate(sizeof(int)));
        
        if (ptr1 && ptr2) {
            *ptr1 = 42;
            *ptr2 = 84;
            
            std::cout << "Linear allocator - ptr1: " << *ptr1 << ", ptr2: " << *ptr2 << std::endl;
            std::cout << "Used: " << linear_alloc.used() << " bytes" << std::endl;
            std::cout << "Available: " << linear_alloc.available() << " bytes" << std::endl;
        }
        
        // Test pool allocator
        PoolAllocator<int> pool_alloc;
        
        std::vector<int*> ptrs;
        for (int i = 0; i < 10; ++i) {
            int* ptr = pool_alloc.allocate();
            if (ptr) {
                *ptr = i * i;
                ptrs.push_back(ptr);
            }
        }
        
        std::cout << "Pool allocator - allocated " << ptrs.size() << " integers" << std::endl;
        for (auto* ptr : ptrs) {
            std::cout << *ptr << " ";
        }
        std::cout << std::endl;
        
        // Deallocate some pointers
        for (size_t i = 0; i < ptrs.size(); i += 2) {
            pool_alloc.deallocate(ptrs[i]);
        }
        
        // Test STL-compatible allocator
        std::vector<int, CustomAllocator<int>> custom_vec;
        for (int i = 0; i < 5; ++i) {
            custom_vec.push_back(i * i);
        }
        
        std::cout << "Custom allocator vector: ";
        for (const auto& value : custom_vec) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
}

// Example 2: Memory Pools
namespace MemoryPools {
    
    // Advanced memory pool with different block sizes
    class AdvancedMemoryPool {
    private:
        struct Block {
            void* memory;
            size_t size;
            bool in_use;
            Block* next;
        };
        
        std::vector<Block> blocks_;
        std::mutex mutex_;
        
    public:
        AdvancedMemoryPool() = default;
        
        ~AdvancedMemoryPool() {
            for (auto& block : blocks_) {
                if (block.memory) {
                    std::free(block.memory);
                }
            }
        }
        
        void* allocate(size_t size) {
            std::lock_guard<std::mutex> lock(mutex_);
            
            // Try to find an existing free block
            for (auto& block : blocks_) {
                if (!block.in_use && block.size >= size) {
                    block.in_use = true;
                    return block.memory;
                }
            }
            
            // Allocate new block
            Block new_block;
            new_block.memory = std::aligned_alloc(64, size);
            new_block.size = size;
            new_block.in_use = true;
            new_block.next = nullptr;
            
            if (!new_block.memory) {
                throw std::bad_alloc();
            }
            
            blocks_.push_back(new_block);
            return new_block.memory;
        }
        
        void deallocate(void* ptr) {
            if (!ptr) return;
            
            std::lock_guard<std::mutex> lock(mutex_);
            
            for (auto& block : blocks_) {
                if (block.memory == ptr) {
                    block.in_use = false;
                    break;
                }
            }
        }
        
        size_t get_used_blocks() const {
            std::lock_guard<std::mutex> lock(mutex_);
            return std::count_if(blocks_.begin(), blocks_.end(), [](const Block& b) { return b.in_use; });
        }
        
        size_t get_total_blocks() const {
            std::lock_guard<std::mutex> lock(mutex_);
            return blocks_.size();
        }
    };
    
    // Thread-local memory pool
    class ThreadLocalPool {
    private:
        static thread_local AdvancedMemoryPool pool_;
        
    public:
        static void* allocate(size_t size) {
            return pool_.allocate(size);
        }
        
        static void deallocate(void* ptr) {
            pool_.deallocate(ptr);
        }
        
        static size_t get_used_blocks() {
            return pool_.get_used_blocks();
        }
        
        static size_t get_total_blocks() {
            return pool_.get_total_blocks();
        }
    };
    
    thread_local AdvancedMemoryPool ThreadLocalPool::pool_;
    
    // RAII wrapper for pool-allocated memory
    template<typename T>
    class PoolPtr {
    private:
        T* ptr_;
        
    public:
        PoolPtr() : ptr_(nullptr) {}
        
        explicit PoolPtr(T* ptr) : ptr_(ptr) {}
        
        ~PoolPtr() {
            if (ptr_) {
                ptr_->~T();
                ThreadLocalPool::deallocate(ptr_);
            }
        }
        
        // Non-copyable
        PoolPtr(const PoolPtr&) = delete;
        PoolPtr& operator=(const PoolPtr&) = delete;
        
        // Movable
        PoolPtr(PoolPtr&& other) noexcept : ptr_(other.ptr_) {
            other.ptr_ = nullptr;
        }
        
        PoolPtr& operator=(PoolPtr&& other) noexcept {
            if (this != &other) {
                if (ptr_) {
                    ptr_->~T();
                    ThreadLocalPool::deallocate(ptr_);
                }
                ptr_ = other.ptr_;
                other.ptr_ = nullptr;
            }
            return *this;
        }
        
        T* get() const { return ptr_; }
        T& operator*() const { return *ptr_; }
        T* operator->() const { return ptr_; }
        
        explicit operator bool() const { return ptr_ != nullptr; }
        
        void reset(T* ptr = nullptr) {
            if (ptr_) {
                ptr_->~T();
                ThreadLocalPool::deallocate(ptr_);
            }
            ptr_ = ptr;
        }
        
        T* release() {
            T* old_ptr = ptr_;
            ptr_ = nullptr;
            return old_ptr;
        }
    };
    
    template<typename T, typename... Args>
    PoolPtr<T> make_pool_ptr(Args&&... args) {
        void* memory = ThreadLocalPool::allocate(sizeof(T));
        if (!memory) {
            throw std::bad_alloc();
        }
        
        T* ptr = new(memory) T(std::forward<Args>(args)...);
        return PoolPtr<T>(ptr);
    }
    
    void demonstrateMemoryPools() {
        std::cout << "\n=== Memory Pools ===" << std::endl;
        
        // Test advanced memory pool
        AdvancedMemoryPool pool;
        
        std::vector<void*> ptrs;
        for (int i = 0; i < 10; ++i) {
            void* ptr = pool.allocate(64);
            if (ptr) {
                ptrs.push_back(ptr);
            }
        }
        
        std::cout << "Advanced pool - allocated " << ptrs.size() << " blocks" << std::endl;
        std::cout << "Used blocks: " << pool.get_used_blocks() << std::endl;
        std::cout << "Total blocks: " << pool.get_total_blocks() << std::endl;
        
        // Deallocate some blocks
        for (size_t i = 0; i < ptrs.size(); i += 2) {
            pool.deallocate(ptrs[i]);
        }
        
        std::cout << "After deallocation - used blocks: " << pool.get_used_blocks() << std::endl;
        
        // Test thread-local pool
        std::vector<std::thread> threads;
        for (int i = 0; i < 4; ++i) {
            threads.emplace_back([i]() {
                std::vector<PoolPtr<int>> ptrs;
                for (int j = 0; j < 5; ++j) {
                    ptrs.push_back(make_pool_ptr<int>(i * 10 + j));
                }
                
                std::cout << "Thread " << i << " - used blocks: " << ThreadLocalPool::get_used_blocks() << std::endl;
            });
        }
        
        for (auto& thread : threads) {
            thread.join();
        }
        
        std::cout << "After threads - used blocks: " << ThreadLocalPool::get_used_blocks() << std::endl;
    }
}

// Example 3: Memory-Mapped Files
namespace MemoryMappedFiles {
    
    class MemoryMappedFile {
    private:
        void* mapped_memory_;
        size_t size_;
        int fd_;
        
    public:
        MemoryMappedFile(const std::string& filename, size_t size = 0) 
            : mapped_memory_(nullptr), size_(size), fd_(-1) {
            
            fd_ = open(filename.c_str(), O_RDWR | O_CREAT, 0644);
            if (fd_ == -1) {
                throw std::runtime_error("Failed to open file: " + filename);
            }
            
            if (size_ == 0) {
                // Get file size
                size_ = lseek(fd_, 0, SEEK_END);
                lseek(fd_, 0, SEEK_SET);
            } else {
                // Set file size
                if (ftruncate(fd_, size_) == -1) {
                    close(fd_);
                    throw std::runtime_error("Failed to set file size");
                }
            }
            
            mapped_memory_ = mmap(nullptr, size_, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0);
            if (mapped_memory_ == MAP_FAILED) {
                close(fd_);
                throw std::runtime_error("Failed to map file to memory");
            }
        }
        
        ~MemoryMappedFile() {
            if (mapped_memory_ != nullptr) {
                munmap(mapped_memory_, size_);
            }
            if (fd_ != -1) {
                close(fd_);
            }
        }
        
        // Non-copyable
        MemoryMappedFile(const MemoryMappedFile&) = delete;
        MemoryMappedFile& operator=(const MemoryMappedFile&) = delete;
        
        // Movable
        MemoryMappedFile(MemoryMappedFile&& other) noexcept 
            : mapped_memory_(other.mapped_memory_), size_(other.size_), fd_(other.fd_) {
            other.mapped_memory_ = nullptr;
            other.size_ = 0;
            other.fd_ = -1;
        }
        
        MemoryMappedFile& operator=(MemoryMappedFile&& other) noexcept {
            if (this != &other) {
                if (mapped_memory_ != nullptr) {
                    munmap(mapped_memory_, size_);
                }
                if (fd_ != -1) {
                    close(fd_);
                }
                
                mapped_memory_ = other.mapped_memory_;
                size_ = other.size_;
                fd_ = other.fd_;
                
                other.mapped_memory_ = nullptr;
                other.size_ = 0;
                other.fd_ = -1;
            }
            return *this;
        }
        
        void* data() const { return mapped_memory_; }
        size_t size() const { return size_; }
        
        template<typename T>
        T* as() const {
            return static_cast<T*>(mapped_memory_);
        }
        
        void sync() {
            if (mapped_memory_ != nullptr) {
                msync(mapped_memory_, size_, MS_SYNC);
            }
        }
    };
    
    // RAII wrapper for memory-mapped file operations
    class MappedFileWriter {
    private:
        MemoryMappedFile file_;
        size_t offset_;
        
    public:
        MappedFileWriter(const std::string& filename, size_t size) 
            : file_(filename, size), offset_(0) {}
        
        template<typename T>
        void write(const T& value) {
            if (offset_ + sizeof(T) > file_.size()) {
                throw std::runtime_error("Write beyond file size");
            }
            
            T* ptr = static_cast<T*>(file_.data()) + offset_ / sizeof(T);
            *ptr = value;
            offset_ += sizeof(T);
        }
        
        void write_raw(const void* data, size_t size) {
            if (offset_ + size > file_.size()) {
                throw std::runtime_error("Write beyond file size");
            }
            
            std::memcpy(static_cast<char*>(file_.data()) + offset_, data, size);
            offset_ += size;
        }
        
        void sync() {
            file_.sync();
        }
    };
    
    class MappedFileReader {
    private:
        MemoryMappedFile file_;
        size_t offset_;
        
    public:
        MappedFileReader(const std::string& filename) 
            : file_(filename), offset_(0) {}
        
        template<typename T>
        T read() {
            if (offset_ + sizeof(T) > file_.size()) {
                throw std::runtime_error("Read beyond file size");
            }
            
            T* ptr = static_cast<T*>(file_.data()) + offset_ / sizeof(T);
            T value = *ptr;
            offset_ += sizeof(T);
            return value;
        }
        
        void read_raw(void* data, size_t size) {
            if (offset_ + size > file_.size()) {
                throw std::runtime_error("Read beyond file size");
            }
            
            std::memcpy(data, static_cast<char*>(file_.data()) + offset_, size);
            offset_ += size;
        }
        
        void seek(size_t new_offset) {
            if (new_offset > file_.size()) {
                throw std::runtime_error("Seek beyond file size");
            }
            offset_ = new_offset;
        }
    };
    
    void demonstrateMemoryMappedFiles() {
        std::cout << "\n=== Memory-Mapped Files ===" << std::endl;
        
        const std::string filename = "test_mapped_file.dat";
        const size_t file_size = 1024;
        
        try {
            // Write to memory-mapped file
            MappedFileWriter writer(filename, file_size);
            
            writer.write(42);
            writer.write(3.14);
            writer.write(std::string("Hello, World!"));
            
            writer.sync();
            
            std::cout << "Written to memory-mapped file" << std::endl;
            
            // Read from memory-mapped file
            MappedFileReader reader(filename);
            
            int int_value = reader.read<int>();
            double double_value = reader.read<double>();
            std::string string_value = reader.read<std::string>();
            
            std::cout << "Read from memory-mapped file:" << std::endl;
            std::cout << "  int: " << int_value << std::endl;
            std::cout << "  double: " << double_value << std::endl;
            std::cout << "  string: " << string_value << std::endl;
            
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
        
        // Clean up
        std::remove(filename.c_str());
    }
}

// Example 4: Advanced RAII Patterns
namespace AdvancedRAII {
    
    // RAII wrapper for system resources
    class FileHandle {
    private:
        int fd_;
        
    public:
        FileHandle() : fd_(-1) {}
        
        explicit FileHandle(int fd) : fd_(fd) {}
        
        ~FileHandle() {
            if (fd_ != -1) {
                close(fd_);
            }
        }
        
        // Non-copyable
        FileHandle(const FileHandle&) = delete;
        FileHandle& operator=(const FileHandle&) = delete;
        
        // Movable
        FileHandle(FileHandle&& other) noexcept : fd_(other.fd_) {
            other.fd_ = -1;
        }
        
        FileHandle& operator=(FileHandle&& other) noexcept {
            if (this != &other) {
                if (fd_ != -1) {
                    close(fd_);
                }
                fd_ = other.fd_;
                other.fd_ = -1;
            }
            return *this;
        }
        
        int get() const { return fd_; }
        
        explicit operator bool() const { return fd_ != -1; }
        
        void reset(int fd = -1) {
            if (fd_ != -1) {
                close(fd_);
            }
            fd_ = fd;
        }
        
        int release() {
            int old_fd = fd_;
            fd_ = -1;
            return old_fd;
        }
    };
    
    // RAII wrapper for mutex locking
    class MutexLock {
    private:
        std::mutex& mutex_;
        bool locked_;
        
    public:
        explicit MutexLock(std::mutex& m) : mutex_(m), locked_(false) {
            mutex_.lock();
            locked_ = true;
        }
        
        ~MutexLock() {
            if (locked_) {
                mutex_.unlock();
            }
        }
        
        // Non-copyable
        MutexLock(const MutexLock&) = delete;
        MutexLock& operator=(const MutexLock&) = delete;
        
        // Non-movable
        MutexLock(MutexLock&&) = delete;
        MutexLock& operator=(MutexLock&&) = delete;
        
        void unlock() {
            if (locked_) {
                mutex_.unlock();
                locked_ = false;
            }
        }
        
        void lock() {
            if (!locked_) {
                mutex_.lock();
                locked_ = true;
            }
        }
        
        bool is_locked() const { return locked_; }
    };
    
    // RAII wrapper for transaction-like operations
    class Transaction {
    private:
        std::vector<std::function<void()>> rollback_actions_;
        bool committed_;
        
    public:
        Transaction() : committed_(false) {}
        
        ~Transaction() {
            if (!committed_) {
                rollback();
            }
        }
        
        // Non-copyable
        Transaction(const Transaction&) = delete;
        Transaction& operator=(const Transaction&) = delete;
        
        // Non-movable
        Transaction(Transaction&&) = delete;
        Transaction& operator=(Transaction&&) = delete;
        
        void add_rollback_action(std::function<void()> action) {
            rollback_actions_.push_back(action);
        }
        
        void commit() {
            committed_ = true;
            rollback_actions_.clear();
        }
        
        void rollback() {
            for (auto it = rollback_actions_.rbegin(); it != rollback_actions_.rend(); ++it) {
                (*it)();
            }
            rollback_actions_.clear();
        }
        
        bool is_committed() const { return committed_; }
    };
    
    // RAII wrapper for temporary file
    class TemporaryFile {
    private:
        std::string filename_;
        FileHandle handle_;
        
    public:
        TemporaryFile() {
            filename_ = "/tmp/temp_file_" + std::to_string(std::chrono::high_resolution_clock::now().time_since_epoch().count());
            handle_ = FileHandle(open(filename_.c_str(), O_RDWR | O_CREAT | O_EXCL, 0644));
            if (!handle_) {
                throw std::runtime_error("Failed to create temporary file");
            }
        }
        
        ~TemporaryFile() {
            if (!filename_.empty()) {
                std::remove(filename_.c_str());
            }
        }
        
        // Non-copyable
        TemporaryFile(const TemporaryFile&) = delete;
        TemporaryFile& operator=(const TemporaryFile&) = delete;
        
        // Movable
        TemporaryFile(TemporaryFile&& other) noexcept 
            : filename_(std::move(other.filename_)), handle_(std::move(other.handle_)) {
            other.filename_.clear();
        }
        
        TemporaryFile& operator=(TemporaryFile&& other) noexcept {
            if (this != &other) {
                if (!filename_.empty()) {
                    std::remove(filename_.c_str());
                }
                filename_ = std::move(other.filename_);
                handle_ = std::move(other.handle_);
                other.filename_.clear();
            }
            return *this;
        }
        
        const std::string& filename() const { return filename_; }
        FileHandle& handle() { return handle_; }
        const FileHandle& handle() const { return handle_; }
    };
    
    void demonstrateAdvancedRAII() {
        std::cout << "\n=== Advanced RAII Patterns ===" << std::endl;
        
        // Test file handle
        FileHandle file(open("/dev/null", O_WRONLY));
        if (file) {
            std::cout << "File handle created successfully" << std::endl;
        }
        
        // Test mutex lock
        std::mutex mtx;
        std::vector<int> shared_data;
        
        {
            MutexLock lock(mtx);
            shared_data.push_back(42);
            std::cout << "Mutex locked, added data" << std::endl;
        }  // Mutex automatically unlocked
        
        std::cout << "Mutex unlocked automatically" << std::endl;
        
        // Test transaction
        {
            Transaction tx;
            int value = 0;
            
            tx.add_rollback_action([&value]() {
                value = 0;
                std::cout << "Rollback: value reset to 0" << std::endl;
            });
            
            value = 100;
            std::cout << "Transaction: value set to " << value << std::endl;
            
            // Transaction will rollback automatically if not committed
        }  // Rollback happens here
        
        // Test temporary file
        try {
            TemporaryFile temp_file;
            std::cout << "Temporary file created: " << temp_file.filename() << std::endl;
            
            // File will be automatically deleted when temp_file goes out of scope
        } catch (const std::exception& e) {
            std::cout << "Error creating temporary file: " << e.what() << std::endl;
        }
    }
}

// Example 5: Garbage Collection Concepts
namespace GarbageCollection {
    
    // Simple reference counting garbage collector
    class ReferenceCountedGC {
    private:
        struct Object {
            void* data;
            size_t size;
            size_t ref_count;
            std::function<void(void*)> destructor;
        };
        
        std::unordered_map<void*, Object> objects_;
        std::mutex mutex_;
        
    public:
        template<typename T>
        T* allocate(T value = T{}) {
            std::lock_guard<std::mutex> lock(mutex_);
            
            T* ptr = new T(std::move(value));
            objects_[ptr] = {
                ptr,
                sizeof(T),
                1,
                [](void* p) { delete static_cast<T*>(p); }
            };
            
            return ptr;
        }
        
        template<typename T>
        void add_reference(T* ptr) {
            if (!ptr) return;
            
            std::lock_guard<std::mutex> lock(mutex_);
            auto it = objects_.find(ptr);
            if (it != objects_.end()) {
                ++it->second.ref_count;
            }
        }
        
        template<typename T>
        void remove_reference(T* ptr) {
            if (!ptr) return;
            
            std::lock_guard<std::mutex> lock(mutex_);
            auto it = objects_.find(ptr);
            if (it != objects_.end()) {
                --it->second.ref_count;
                if (it->second.ref_count == 0) {
                    it->second.destructor(ptr);
                    objects_.erase(it);
                }
            }
        }
        
        size_t get_object_count() const {
            std::lock_guard<std::mutex> lock(mutex_);
            return objects_.size();
        }
        
        size_t get_total_references() const {
            std::lock_guard<std::mutex> lock(mutex_);
            size_t total = 0;
            for (const auto& [ptr, obj] : objects_) {
                total += obj.ref_count;
            }
            return total;
        }
    };
    
    // RAII wrapper for garbage collected objects
    template<typename T>
    class GCRef {
    private:
        T* ptr_;
        ReferenceCountedGC* gc_;
        
    public:
        GCRef() : ptr_(nullptr), gc_(nullptr) {}
        
        GCRef(T* ptr, ReferenceCountedGC* gc) : ptr_(ptr), gc_(gc) {
            if (gc_) {
                gc_->add_reference(ptr_);
            }
        }
        
        ~GCRef() {
            if (gc_ && ptr_) {
                gc_->remove_reference(ptr_);
            }
        }
        
        // Copyable
        GCRef(const GCRef& other) : ptr_(other.ptr_), gc_(other.gc_) {
            if (gc_) {
                gc_->add_reference(ptr_);
            }
        }
        
        GCRef& operator=(const GCRef& other) {
            if (this != &other) {
                if (gc_ && ptr_) {
                    gc_->remove_reference(ptr_);
                }
                ptr_ = other.ptr_;
                gc_ = other.gc_;
                if (gc_) {
                    gc_->add_reference(ptr_);
                }
            }
            return *this;
        }
        
        // Movable
        GCRef(GCRef&& other) noexcept : ptr_(other.ptr_), gc_(other.gc_) {
            other.ptr_ = nullptr;
            other.gc_ = nullptr;
        }
        
        GCRef& operator=(GCRef&& other) noexcept {
            if (this != &other) {
                if (gc_ && ptr_) {
                    gc_->remove_reference(ptr_);
                }
                ptr_ = other.ptr_;
                gc_ = other.gc_;
                other.ptr_ = nullptr;
                other.gc_ = nullptr;
            }
            return *this;
        }
        
        T* get() const { return ptr_; }
        T& operator*() const { return *ptr_; }
        T* operator->() const { return ptr_; }
        
        explicit operator bool() const { return ptr_ != nullptr; }
    };
    
    void demonstrateGarbageCollection() {
        std::cout << "\n=== Garbage Collection Concepts ===" << std::endl;
        
        ReferenceCountedGC gc;
        
        // Create some objects
        auto ptr1 = gc.allocate<int>(42);
        auto ptr2 = gc.allocate<std::string>("Hello, World!");
        
        std::cout << "Created objects - count: " << gc.get_object_count() << std::endl;
        std::cout << "Total references: " << gc.get_total_references() << std::endl;
        
        // Create references
        GCRef<int> ref1(ptr1, &gc);
        GCRef<int> ref2(ptr1, &gc);
        GCRef<std::string> ref3(ptr2, &gc);
        
        std::cout << "After creating references - count: " << gc.get_object_count() << std::endl;
        std::cout << "Total references: " << gc.get_total_references() << std::endl;
        
        // Remove some references
        ref1 = GCRef<int>();
        ref3 = GCRef<std::string>();
        
        std::cout << "After removing some references - count: " << gc.get_object_count() << std::endl;
        std::cout << "Total references: " << gc.get_total_references() << std::endl;
        
        // Remove all references
        ref2 = GCRef<int>();
        
        std::cout << "After removing all references - count: " << gc.get_object_count() << std::endl;
        std::cout << "Total references: " << gc.get_total_references() << std::endl;
    }
}

int main() {
    std::cout << "=== Advanced Memory Management Demonstration ===" << std::endl;
    std::cout << "This program demonstrates advanced memory management techniques including\n"
              << "custom allocators, memory pools, memory-mapped files, advanced RAII patterns,\n"
              << "and garbage collection concepts.\n" << std::endl;
    
    // Demonstrate various memory management techniques
    CustomAllocators::demonstrateCustomAllocators();
    MemoryPools::demonstrateMemoryPools();
    MemoryMappedFiles::demonstrateMemoryMappedFiles();
    AdvancedRAII::demonstrateAdvancedRAII();
    GarbageCollection::demonstrateGarbageCollection();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Custom allocators provide control over memory allocation strategies" << std::endl;
    std::cout << "2. Memory pools improve performance by reducing allocation overhead" << std::endl;
    std::cout << "3. Memory-mapped files enable efficient file I/O operations" << std::endl;
    std::cout << "4. Advanced RAII patterns ensure proper resource management" << std::endl;
    std::cout << "5. Garbage collection concepts can be implemented in C++" << std::endl;
    std::cout << "6. Thread-safe memory management is crucial for concurrent applications" << std::endl;
    std::cout << "7. RAII wrappers provide exception-safe resource management" << std::endl;
    std::cout << "8. Understanding memory management is essential for high-performance C++" << std::endl;
    
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
 * Note: This lesson requires C++17 for some features.
 * Memory-mapped files require POSIX-compatible systems.
 * 
 * Advanced Memory Management Notes:
 * - Custom allocators provide control over memory allocation strategies
 * - Memory pools improve performance by reducing allocation overhead
 * - Memory-mapped files enable efficient file I/O operations
 * - Advanced RAII patterns ensure proper resource management
 * - Garbage collection concepts can be implemented in C++
 * - Thread-safe memory management is crucial for concurrent applications
 * - RAII wrappers provide exception-safe resource management
 * - Understanding memory management is essential for high-performance C++
 */"""
