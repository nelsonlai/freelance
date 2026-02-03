# Week 18, Lesson 2: Advanced Memory Management

## 1. Learning Objectives

- Understand advanced memory management techniques and their applications.
- Learn custom allocators and their implementation strategies.
- Explore memory pools for efficient memory allocation.
- Understand memory-mapped files and their benefits.
- Learn advanced RAII patterns for resource management.
- Explore garbage collection concepts in C++.
- Understand thread-safe memory management techniques.
- Learn best practices for high-performance memory management.

## 2. Prerequisites

- Understanding of basic memory management concepts
- Knowledge of RAII and smart pointers
- Familiarity with system programming concepts
- Understanding of threading and concurrency
- Knowledge of C++ templates and generic programming

## 3. Custom Allocators

### 3.1 Allocator Concepts

**Standard Allocator Interface:**
```cpp
template<typename T>
class Allocator {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    
    pointer allocate(size_type n);
    void deallocate(pointer p, size_type n);
    
    template<typename U>
    bool operator==(const Allocator<U>& other) const;
    
    template<typename U>
    bool operator!=(const Allocator<U>& other) const;
};
```

**Allocator Benefits:**
- Control over memory allocation strategies
- Performance optimization for specific use cases
- Memory usage tracking and debugging
- Custom memory layouts and alignment

### 3.2 Linear Allocator

```cpp
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
```

**Linear Allocator Characteristics:**
- Very fast allocation (O(1))
- No individual deallocation
- Memory fragmentation free
- Suitable for temporary allocations
- Must reset entire allocator to free memory

### 3.3 Pool Allocator

```cpp
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
```

**Pool Allocator Characteristics:**
- Fixed-size object allocation
- Very fast allocation and deallocation
- No memory fragmentation
- Suitable for frequent allocation/deallocation
- Memory overhead per object

### 3.4 STL-Compatible Custom Allocator

```cpp
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
```

## 4. Memory Pools

### 4.1 Advanced Memory Pool

```cpp
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
```

### 4.2 Thread-Local Memory Pool

```cpp
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
```

### 4.3 RAII Wrapper for Pool-Allocated Memory

```cpp
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
```

## 5. Memory-Mapped Files

### 5.1 Memory-Mapped File Class

```cpp
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
```

### 5.2 Memory-Mapped File Writers and Readers

```cpp
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
```

**Memory-Mapped File Benefits:**
- Efficient file I/O operations
- Shared memory between processes
- Automatic paging by the operating system
- No need to load entire file into memory
- Direct memory access to file data

## 6. Advanced RAII Patterns

### 6.1 RAII Wrapper for System Resources

```cpp
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
```

### 6.2 RAII Wrapper for Mutex Locking

```cpp
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
```

### 6.3 Transaction-like Operations

```cpp
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
```

### 6.4 Temporary File Management

```cpp
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
```

## 7. Garbage Collection Concepts

### 7.1 Reference Counting Garbage Collector

```cpp
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
```

### 7.2 RAII Wrapper for Garbage Collected Objects

```cpp
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
```

## 8. Best Practices

### 8.1 Memory Management Guidelines

**Allocation Strategies:**
- Choose appropriate allocator for use case
- Consider allocation patterns and lifetime
- Use memory pools for frequent allocations
- Implement custom allocators for specific needs

**RAII Principles:**
- Acquire resources in constructors
- Release resources in destructors
- Use move semantics for resource transfer
- Implement proper exception safety

### 8.2 Performance Considerations

**Allocator Performance:**
- Linear allocators: O(1) allocation, no deallocation
- Pool allocators: O(1) allocation and deallocation
- General allocators: Variable performance
- Custom allocators: Optimized for specific patterns

**Memory Layout:**
- Consider cache line alignment
- Minimize memory fragmentation
- Use appropriate data structures
- Consider NUMA effects

### 8.3 Thread Safety

**Thread-Safe Allocators:**
- Use mutexes for shared allocators
- Consider lock-free allocators
- Use thread-local allocators when possible
- Avoid false sharing

**Resource Management:**
- Use RAII for automatic cleanup
- Implement proper locking strategies
- Consider lock-free data structures
- Use atomic operations when appropriate

## 9. Common Pitfalls and Solutions

### 9.1 Memory Management Pitfalls

**Problem**: Memory leaks
**Solution**: Use RAII and smart pointers

**Problem**: Double deletion
**Solution**: Use move semantics and proper ownership

**Problem**: Use after free
**Solution**: Use smart pointers and proper lifetime management

**Problem**: Memory fragmentation
**Solution**: Use appropriate allocators and data structures

### 9.2 RAII Pitfalls

**Problem**: Resource leaks in constructors
**Solution**: Use RAII wrappers and exception safety

**Problem**: Exception safety issues
**Solution**: Use RAII and proper exception handling

**Problem**: Resource sharing issues
**Solution**: Use shared_ptr and proper ownership semantics

### 9.3 Performance Pitfalls

**Problem**: Allocation overhead
**Solution**: Use memory pools and custom allocators

**Problem**: Cache misses
**Solution**: Consider data layout and alignment

**Problem**: Lock contention
**Solution**: Use thread-local storage and lock-free algorithms

## 10. Advanced Topics

### 10.1 Lock-Free Memory Management

**Lock-Free Allocators:**
- Use atomic operations
- Implement hazard pointers
- Use epoch-based reclamation
- Consider memory ordering

### 10.2 NUMA-Aware Memory Management

**NUMA Considerations:**
- Understand NUMA topology
- Use NUMA-aware allocation
- Minimize cross-NUMA communication
- Consider memory affinity

### 10.3 Memory-Mapped I/O

**Advanced File Operations:**
- Use memory-mapped files for large files
- Consider shared memory for IPC
- Implement efficient serialization
- Use appropriate synchronization

## 11. Summary

Advanced memory management techniques provide powerful tools for optimizing performance and managing resources effectively. Key takeaways include:

1. **Custom allocators** provide control over memory allocation strategies
2. **Memory pools** improve performance by reducing allocation overhead
3. **Memory-mapped files** enable efficient file I/O operations
4. **Advanced RAII patterns** ensure proper resource management
5. **Garbage collection concepts** can be implemented in C++
6. **Thread-safe memory management** is crucial for concurrent applications
7. **RAII wrappers** provide exception-safe resource management
8. **Understanding memory management** is essential for high-performance C++

Effective memory management requires understanding both the application requirements and the underlying system characteristics, combined with appropriate use of RAII and modern C++ features.

## 12. Exercises

### Exercise 1: Custom Allocator
Implement a custom allocator that tracks memory usage and provides statistics about allocations and deallocations.

### Exercise 2: Memory Pool
Create a memory pool that can handle different object sizes efficiently, with automatic block allocation and deallocation.

### Exercise 3: Memory-Mapped File
Implement a memory-mapped file system for storing and retrieving structured data efficiently.

### Exercise 4: RAII Wrapper
Create RAII wrappers for system resources like sockets, database connections, or hardware devices.

### Exercise 5: Garbage Collector
Implement a simple garbage collector with reference counting and automatic memory reclamation.

## 13. Further Reading

- "Effective Modern C++" by Scott Meyers
- "C++ Concurrency in Action" by Anthony Williams
- "Advanced C++ Programming Styles and Idioms" by James O. Coplien
- "The C++ Programming Language" by Bjarne Stroustrup
- "Memory Management: Algorithms and Implementation in C/C++" by Bill Blunden
- "Systems Programming: Designing and Developing Distributed Applications" by Richard John Anthony
- "Computer Systems: A Programmer's Perspective" by Randal E. Bryant and David R. O'Hallaron
