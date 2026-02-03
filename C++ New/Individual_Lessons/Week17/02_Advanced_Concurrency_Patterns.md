# Week 17, Lesson 2: Advanced Concurrency Patterns

## 1. Learning Objectives

- Understand advanced concurrency patterns and their applications.
- Learn lock-free programming techniques and atomic operations.
- Explore memory ordering and synchronization primitives.
- Understand concurrent data structures and their implementation.
- Learn high-performance synchronization techniques.
- Explore advanced patterns like actors, pipelines, and MapReduce.
- Understand the trade-offs between performance and correctness.
- Learn best practices for concurrent programming.

## 2. Prerequisites

- Understanding of basic concurrency concepts
- Knowledge of threads, mutexes, and condition variables
- Familiarity with atomic operations
- Understanding of memory models
- Knowledge of C++ templates and generic programming

## 3. Lock-Free Programming

### 3.1 Lock-Free Concepts

**Lock-Free Programming:**
- Algorithms that don't use mutual exclusion primitives
- Based on atomic operations and memory ordering
- Higher performance but more complex design
- Requires careful consideration of race conditions

**Benefits:**
- No deadlocks
- Better scalability
- Higher performance
- No priority inversion

**Challenges:**
- Complex implementation
- Difficult debugging
- ABA problem
- Memory ordering complexity

### 3.2 Atomic Operations

**Atomic Operations:**
```cpp
std::atomic<int> counter{0};

// Basic operations
counter.fetch_add(1);           // Atomic increment
counter.fetch_sub(1);           // Atomic decrement
counter.exchange(42);           // Atomic exchange
counter.compare_exchange_weak(expected, desired);  // Compare and swap
```

**Memory Ordering:**
```cpp
// Relaxed ordering - no synchronization
counter.fetch_add(1, std::memory_order_relaxed);

// Acquire ordering - prevents reordering of subsequent operations
int value = counter.load(std::memory_order_acquire);

// Release ordering - prevents reordering of previous operations
counter.store(42, std::memory_order_release);

// Sequential consistency - strongest ordering
counter.fetch_add(1, std::memory_order_seq_cst);
```

### 3.3 Lock-Free Stack Implementation

```cpp
template<typename T>
class LockFreeStack {
private:
    struct Node {
        T data;
        Node* next;
        
        Node(const T& item) : data(item), next(nullptr) {}
    };
    
    std::atomic<Node*> head_{nullptr};
    
public:
    void push(const T& item) {
        Node* new_node = new Node(item);
        Node* old_head = head_.load();
        
        do {
            new_node->next = old_head;
        } while (!head_.compare_exchange_weak(old_head, new_node));
    }
    
    bool pop(T& result) {
        Node* old_head = head_.load();
        
        do {
            if (old_head == nullptr) {
                return false;  // Stack is empty
            }
        } while (!head_.compare_exchange_weak(old_head, old_head->next));
        
        result = old_head->data;
        delete old_head;
        return true;
    }
};
```

### 3.4 Lock-Free Queue Implementation

```cpp
template<typename T>
class LockFreeQueue {
private:
    struct Node {
        std::atomic<T*> data{nullptr};
        std::atomic<Node*> next{nullptr};
    };
    
    std::atomic<Node*> head_{new Node};
    std::atomic<Node*> tail_{head_.load()};
    
public:
    void enqueue(T item) {
        Node* new_node = new Node;
        T* data = new T(std::move(item));
        new_node->data.store(data);
        
        Node* prev_tail = tail_.exchange(new_node);
        prev_tail->next.store(new_node);
    }
    
    bool dequeue(T& result) {
        Node* head = head_.load();
        Node* next = head->next.load();
        
        if (next == nullptr) {
            return false;  // Queue is empty
        }
        
        T* data = next->data.load();
        if (data == nullptr) {
            return false;  // Data not ready
        }
        
        if (head_.compare_exchange_weak(head, next)) {
            result = std::move(*data);
            delete data;
            delete head;
            return true;
        }
        
        return false;
    }
};
```

## 4. Memory Ordering and Synchronization

### 4.1 Memory Ordering Concepts

**Memory Ordering Types:**
- **Relaxed**: No ordering constraints
- **Acquire**: Prevents reordering of subsequent operations
- **Release**: Prevents reordering of previous operations
- **Acq-Rel**: Combination of acquire and release
- **Sequential Consistency**: Strongest ordering

**Producer-Consumer Pattern:**
```cpp
class ProducerConsumer {
private:
    std::atomic<bool> flag_{false};
    std::atomic<int> data_{0};
    
public:
    void producer() {
        // Store data first
        data_.store(42, std::memory_order_relaxed);
        
        // Set flag with release ordering
        flag_.store(true, std::memory_order_release);
    }
    
    void consumer() {
        // Wait for flag with acquire ordering
        while (!flag_.load(std::memory_order_acquire)) {
            std::this_thread::yield();
        }
        
        // Read data (guaranteed to see the value written by producer)
        int value = data_.load(std::memory_order_relaxed);
        std::cout << "Consumer read: " << value << std::endl;
    }
};
```

### 4.2 Double-Checked Locking

```cpp
class Singleton {
private:
    static std::atomic<Singleton*> instance_;
    static std::mutex mutex_;
    
    Singleton() = default;
    
public:
    static Singleton* getInstance() {
        Singleton* instance = instance_.load(std::memory_order_acquire);
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mutex_);
            instance = instance_.load(std::memory_order_relaxed);
            if (instance == nullptr) {
                instance = new Singleton();
                instance_.store(instance, std::memory_order_release);
            }
        }
        return instance;
    }
};
```

### 4.3 Sequential Consistency

```cpp
void demonstrate_sequential_consistency() {
    std::atomic<int> x{0}, y{0};
    std::atomic<int> r1{0}, r2{0};
    
    std::thread t1([&]() {
        x.store(1, std::memory_order_seq_cst);
        r1.store(y.load(std::memory_order_seq_cst), std::memory_order_seq_cst);
    });
    
    std::thread t2([&]() {
        y.store(1, std::memory_order_seq_cst);
        r2.store(x.load(std::memory_order_seq_cst), std::memory_order_seq_cst);
    });
    
    t1.join();
    t2.join();
    
    // With sequential consistency, at least one of r1 or r2 must be 1
    std::cout << "r1: " << r1.load() << ", r2: " << r2.load() << std::endl;
}
```

## 5. Concurrent Data Structures

### 5.1 Thread-Safe Hash Map

```cpp
template<typename K, typename V>
class ConcurrentHashMap {
private:
    static constexpr size_t NUM_BUCKETS = 16;
    
    struct Bucket {
        std::shared_mutex mutex;
        std::unordered_map<K, V> data;
    };
    
    std::array<Bucket, NUM_BUCKETS> buckets_;
    
    size_t hash(const K& key) const {
        return std::hash<K>{}(key) % NUM_BUCKETS;
    }
    
public:
    void insert(const K& key, const V& value) {
        size_t bucket_index = hash(key);
        auto& bucket = buckets_[bucket_index];
        
        std::unique_lock<std::shared_mutex> lock(bucket.mutex);
        bucket.data[key] = value;
    }
    
    bool find(const K& key, V& value) const {
        size_t bucket_index = hash(key);
        const auto& bucket = buckets_[bucket_index];
        
        std::shared_lock<std::shared_mutex> lock(bucket.mutex);
        auto it = bucket.data.find(key);
        if (it != bucket.data.end()) {
            value = it->second;
            return true;
        }
        return false;
    }
};
```

### 5.2 Lock-Free Ring Buffer

```cpp
template<typename T, size_t Size>
class LockFreeRingBuffer {
private:
    static_assert((Size & (Size - 1)) == 0, "Size must be a power of 2");
    
    T buffer_[Size];
    std::atomic<size_t> write_pos_{0};
    std::atomic<size_t> read_pos_{0};
    
public:
    bool push(const T& item) {
        size_t current_write = write_pos_.load(std::memory_order_relaxed);
        size_t next_write = (current_write + 1) & (Size - 1);
        
        if (next_write == read_pos_.load(std::memory_order_acquire)) {
            return false;  // Buffer is full
        }
        
        buffer_[current_write] = item;
        write_pos_.store(next_write, std::memory_order_release);
        return true;
    }
    
    bool pop(T& item) {
        size_t current_read = read_pos_.load(std::memory_order_relaxed);
        
        if (current_read == write_pos_.load(std::memory_order_acquire)) {
            return false;  // Buffer is empty
        }
        
        item = buffer_[current_read];
        read_pos_.store((current_read + 1) & (Size - 1), std::memory_order_release);
        return true;
    }
};
```

### 5.3 Producer-Consumer Queue

```cpp
template<typename T>
class ProducerConsumerQueue {
private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable condition_;
    bool shutdown_{false};
    
public:
    void push(T item) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(std::move(item));
        condition_.notify_one();
    }
    
    bool pop(T& item, std::chrono::milliseconds timeout = std::chrono::milliseconds(100)) {
        std::unique_lock<std::mutex> lock(mutex_);
        
        if (!condition_.wait_for(lock, timeout, [this] { return !queue_.empty() || shutdown_; })) {
            return false;  // Timeout
        }
        
        if (queue_.empty()) {
            return false;  // Shutdown
        }
        
        item = std::move(queue_.front());
        queue_.pop();
        return true;
    }
    
    void shutdown() {
        std::lock_guard<std::mutex> lock(mutex_);
        shutdown_ = true;
        condition_.notify_all();
    }
};
```

## 6. High-Performance Synchronization

### 6.1 Spinlock Implementation

```cpp
class Spinlock {
private:
    std::atomic<bool> locked_{false};
    
public:
    void lock() {
        while (locked_.exchange(true, std::memory_order_acquire)) {
            // Spin until lock is acquired
            while (locked_.load(std::memory_order_relaxed)) {
                std::this_thread::yield();
            }
        }
    }
    
    void unlock() {
        locked_.store(false, std::memory_order_release);
    }
    
    bool try_lock() {
        return !locked_.exchange(true, std::memory_order_acquire);
    }
};
```

### 6.2 Read-Write Spinlock

```cpp
class ReadWriteSpinlock {
private:
    std::atomic<int> readers_{0};
    std::atomic<bool> writer_{false};
    
public:
    void lock_read() {
        while (writer_.load(std::memory_order_acquire)) {
            std::this_thread::yield();
        }
        readers_.fetch_add(1, std::memory_order_acquire);
    }
    
    void unlock_read() {
        readers_.fetch_sub(1, std::memory_order_release);
    }
    
    void lock_write() {
        while (writer_.exchange(true, std::memory_order_acquire)) {
            std::this_thread::yield();
        }
        
        while (readers_.load(std::memory_order_acquire) > 0) {
            std::this_thread::yield();
        }
    }
    
    void unlock_write() {
        writer_.store(false, std::memory_order_release);
    }
};
```

### 6.3 Thread Pool with Work Stealing

```cpp
class ThreadPool {
private:
    std::vector<std::thread> workers_;
    std::vector<std::queue<std::function<void()>>> task_queues_;
    std::vector<std::mutex> queue_mutexes_;
    std::atomic<bool> stop_{false};
    std::atomic<size_t> next_queue_{0};
    
    void worker_thread(size_t thread_id) {
        while (!stop_) {
            std::function<void()> task;
            
            // Try to get task from own queue
            {
                std::lock_guard<std::mutex> lock(queue_mutexes_[thread_id]);
                if (!task_queues_[thread_id].empty()) {
                    task = std::move(task_queues_[thread_id].front());
                    task_queues_[thread_id].pop();
                }
            }
            
            // If no task, try to steal from other queues
            if (!task) {
                for (size_t i = 0; i < task_queues_.size(); ++i) {
                    if (i == thread_id) continue;
                    
                    std::lock_guard<std::mutex> lock(queue_mutexes_[i]);
                    if (!task_queues_[i].empty()) {
                        task = std::move(task_queues_[i].front());
                        task_queues_[i].pop();
                        break;
                    }
                }
            }
            
            if (task) {
                task();
            } else {
                std::this_thread::yield();
            }
        }
    }
    
public:
    ThreadPool(size_t num_threads = std::thread::hardware_concurrency()) 
        : task_queues_(num_threads), queue_mutexes_(num_threads) {
        
        for (size_t i = 0; i < num_threads; ++i) {
            workers_.emplace_back(&ThreadPool::worker_thread, this, i);
        }
    }
    
    template<typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
        using return_type = decltype(f(args...));
        
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
        std::future<return_type> result = task->get_future();
        
        // Choose queue using round-robin
        size_t queue_index = next_queue_.fetch_add(1) % task_queues_.size();
        
        {
            std::lock_guard<std::mutex> lock(queue_mutexes_[queue_index]);
            task_queues_[queue_index].emplace([task]() { (*task)(); });
        }
        
        return result;
    }
};
```

### 6.4 Barrier Implementation

```cpp
class Barrier {
private:
    std::atomic<int> count_;
    std::atomic<int> generation_;
    int total_threads_;
    
public:
    Barrier(int total_threads) : count_(total_threads), generation_(0), total_threads_(total_threads) {}
    
    void wait() {
        int gen = generation_.load();
        
        if (count_.fetch_sub(1) == 1) {
            // Last thread to reach barrier
            count_.store(total_threads_);
            generation_.fetch_add(1);
        } else {
            // Wait for all threads
            while (generation_.load() == gen) {
                std::this_thread::yield();
            }
        }
    }
};
```

## 7. Advanced Concurrency Patterns

### 7.1 Actor Model

The Actor model provides a way to handle concurrency through message passing.

```cpp
template<typename MessageType>
class Actor {
private:
    std::queue<MessageType> mailbox_;
    std::mutex mailbox_mutex_;
    std::condition_variable mailbox_condition_;
    std::thread actor_thread_;
    std::atomic<bool> running_{true};
    
    virtual void process_message(const MessageType& message) = 0;
    
    void message_loop() {
        while (running_) {
            std::unique_lock<std::mutex> lock(mailbox_mutex_);
            mailbox_condition_.wait(lock, [this] { return !mailbox_.empty() || !running_; });
            
            if (!running_) break;
            
            MessageType message = std::move(mailbox_.front());
            mailbox_.pop();
            lock.unlock();
            
            process_message(message);
        }
    }
    
public:
    Actor() : actor_thread_(&Actor::message_loop, this) {}
    
    virtual ~Actor() {
        stop();
        if (actor_thread_.joinable()) {
            actor_thread_.join();
        }
    }
    
    void send_message(const MessageType& message) {
        std::lock_guard<std::mutex> lock(mailbox_mutex_);
        mailbox_.push(message);
        mailbox_condition_.notify_one();
    }
    
    void stop() {
        running_ = false;
        mailbox_condition_.notify_all();
    }
};
```

### 7.2 Pipeline Pattern

Pipelines process data through a series of stages.

```cpp
template<typename InputType, typename OutputType>
class Pipeline {
private:
    std::vector<std::function<OutputType(const InputType&)>> stages_;
    
public:
    void add_stage(std::function<OutputType(const InputType&)> stage) {
        stages_.push_back(stage);
    }
    
    OutputType process(const InputType& input) {
        auto current = input;
        for (const auto& stage : stages_) {
            current = stage(current);
        }
        return current;
    }
    
    template<typename StageType>
    void add_stage(StageType stage) {
        stages_.push_back([stage](const InputType& input) {
            return stage(input);
        });
    }
};

// Usage
Pipeline<int, int> pipeline;
pipeline.add_stage([](int x) { return x * 2; });
pipeline.add_stage([](int x) { return x + 1; });
pipeline.add_stage([](int x) { return x * x; });

int result = pipeline.process(5);  // ((5 * 2) + 1) * ((5 * 2) + 1) = 121
```

### 7.3 MapReduce Pattern

MapReduce processes large datasets in parallel.

```cpp
template<typename InputType, typename KeyType, typename ValueType>
class MapReduce {
private:
    std::function<std::vector<std::pair<KeyType, ValueType>>(const InputType&)> map_func_;
    std::function<ValueType(const std::vector<ValueType>&)> reduce_func_;
    
public:
    MapReduce(std::function<std::vector<std::pair<KeyType, ValueType>>(const InputType&)> map,
              std::function<ValueType(const std::vector<ValueType>&)> reduce)
        : map_func_(map), reduce_func_(reduce) {}
    
    std::map<KeyType, ValueType> execute(const std::vector<InputType>& inputs) {
        // Map phase
        std::map<KeyType, std::vector<ValueType>> intermediate;
        
        for (const auto& input : inputs) {
            auto pairs = map_func_(input);
            for (const auto& pair : pairs) {
                intermediate[pair.first].push_back(pair.second);
            }
        }
        
        // Reduce phase
        std::map<KeyType, ValueType> result;
        for (const auto& [key, values] : intermediate) {
            result[key] = reduce_func_(values);
        }
        
        return result;
    }
};

// Usage - Word count
MapReduce<std::string, std::string, int> word_count(
    [](const std::string& text) {
        std::vector<std::pair<std::string, int>> pairs;
        std::istringstream iss(text);
        std::string word;
        while (iss >> word) {
            pairs.emplace_back(word, 1);
        }
        return pairs;
    },
    [](const std::vector<int>& values) {
        return std::accumulate(values.begin(), values.end(), 0);
    }
);
```

## 8. Performance Considerations

### 8.1 Lock-Free vs Lock-Based

**Lock-Free Advantages:**
- No deadlocks
- Better scalability
- Higher performance under contention
- No priority inversion

**Lock-Free Disadvantages:**
- Complex implementation
- Difficult debugging
- ABA problem
- Memory ordering complexity
- Higher memory usage

**When to Use Lock-Free:**
- High contention scenarios
- Real-time systems
- When locks cause performance issues
- When deadlock prevention is critical

### 8.2 Memory Ordering Performance

**Performance Hierarchy (fastest to slowest):**
1. Relaxed - No synchronization overhead
2. Acquire/Release - Moderate overhead
3. Sequential Consistency - Highest overhead

**Best Practices:**
- Use relaxed ordering when possible
- Use acquire/release for synchronization
- Use sequential consistency only when necessary
- Understand the hardware memory model

### 8.3 Cache Coherence

**Cache Line Considerations:**
- False sharing can degrade performance
- Align data structures to cache lines
- Use padding to avoid false sharing
- Consider NUMA effects

**Example - Avoiding False Sharing:**
```cpp
struct alignas(64) Counter {  // Align to cache line
    std::atomic<int> value{0};
    char padding[64 - sizeof(std::atomic<int>)];
};
```

## 9. Common Pitfalls and Solutions

### 9.1 Lock-Free Programming Pitfalls

**Problem**: ABA Problem
**Solution**: Use hazard pointers or epoch-based reclamation

**Problem**: Memory ordering bugs
**Solution**: Use acquire/release ordering consistently

**Problem**: Infinite loops in compare-and-swap
**Solution**: Use exponential backoff or yield

**Problem**: Memory leaks in lock-free structures
**Solution**: Implement proper memory management

### 9.2 Concurrent Data Structure Pitfalls

**Problem**: Deadlocks with multiple locks
**Solution**: Use consistent lock ordering or lock-free approaches

**Problem**: Priority inversion
**Solution**: Use priority inheritance or lock-free algorithms

**Problem**: Starvation
**Solution**: Use fair locking mechanisms or work stealing

**Problem**: False sharing
**Solution**: Align data structures to cache lines

### 9.3 Performance Pitfalls

**Problem**: Oversynchronization
**Solution**: Use minimal synchronization and lock-free approaches

**Problem**: Cache misses
**Solution**: Optimize data layout and access patterns

**Problem**: Thread creation overhead
**Solution**: Use thread pools and work stealing

**Problem**: Memory allocation contention
**Solution**: Use per-thread allocators or lock-free allocators

## 10. Best Practices

### 10.1 Design Principles

**Start Simple:**
- Begin with lock-based approaches
- Profile and identify bottlenecks
- Gradually introduce lock-free techniques

**Measure Performance:**
- Benchmark different approaches
- Measure under realistic workloads
- Consider scalability characteristics

**Test Thoroughly:**
- Test with multiple threads
- Test with high contention
- Use stress testing tools

### 10.2 Implementation Guidelines

**Use Standard Library:**
- Prefer `std::atomic` over custom implementations
- Use `std::shared_mutex` for read-write scenarios
- Use `std::condition_variable` for complex synchronization

**Memory Ordering:**
- Start with sequential consistency
- Optimize with acquire/release ordering
- Use relaxed ordering only when safe

**Error Handling:**
- Handle allocation failures
- Implement timeout mechanisms
- Provide graceful degradation

### 10.3 Debugging and Testing

**Debugging Tools:**
- Thread sanitizer (TSan)
- Address sanitizer (ASan)
- Memory sanitizer (MSan)
- Valgrind Helgrind

**Testing Strategies:**
- Unit tests with multiple threads
- Stress testing with high contention
- Property-based testing
- Model checking for correctness

## 11. Advanced Topics

### 11.1 NUMA Considerations

**NUMA-Aware Programming:**
- Understand NUMA topology
- Use NUMA-aware allocation
- Minimize cross-NUMA communication
- Consider NUMA-aware data structures

### 11.2 Hardware Transactional Memory

**Transactional Memory:**
- Hardware support for transactions
- Fallback to locks when transactions fail
- Limited transaction size
- Not widely available

### 11.3 Lock-Free Memory Management

**Memory Reclamation Techniques:**
- Hazard pointers
- Epoch-based reclamation
- Reference counting
- Garbage collection

## 12. Summary

Advanced concurrency patterns provide powerful tools for building high-performance, scalable systems. Key takeaways include:

1. **Lock-free programming** provides high performance but requires careful design
2. **Memory ordering** is crucial for correct concurrent programming
3. **Concurrent data structures** must balance performance and correctness
4. **High-performance synchronization** requires understanding hardware behavior
5. **Advanced patterns** like actors and pipelines enable scalable architectures
6. **Atomic operations** provide building blocks for lock-free algorithms
7. **Thread pools and work stealing** improve resource utilization
8. **Proper synchronization** prevents data races and ensures correctness

Understanding these patterns and their appropriate application is essential for building high-performance concurrent systems.

## 13. Exercises

### Exercise 1: Lock-Free Stack
Implement a lock-free stack that can handle multiple threads pushing and popping elements.

### Exercise 2: Concurrent Hash Map
Implement a thread-safe hash map using fine-grained locking with separate locks for each bucket.

### Exercise 3: Producer-Consumer Queue
Implement a high-performance producer-consumer queue using atomic operations and memory ordering.

### Exercise 4: Thread Pool
Implement a thread pool with work stealing that can efficiently distribute tasks across multiple threads.

### Exercise 5: Actor System
Implement a simple actor system where actors can send messages to each other and process them concurrently.

## 14. Further Reading

- "C++ Concurrency in Action" by Anthony Williams
- "The Art of Multiprocessor Programming" by Maurice Herlihy and Nir Shavit
- "Java Concurrency in Practice" by Brian Goetz et al.
- "Programming Pearls" by Jon Bentley
- "Designing Data-Intensive Applications" by Martin Kleppmann
- "High Performance Computing" by Charles Severance and Kevin Dowd
- "Parallel and Concurrent Programming in Haskell" by Simon Marlow
