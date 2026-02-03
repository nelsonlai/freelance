# Week 20, Lesson 2: Advanced Concurrency Patterns

## 1. Learning Objectives
- Understand advanced concurrency patterns and their applications.
- Learn about lock-free programming and atomic operations.
- Explore the actor model for message-based concurrency.
- Understand thread pools and their efficient management.
- Learn about async programming and futures.
- Explore advanced synchronization primitives.
- Understand message passing patterns for loose coupling.

## 2. Introduction to Advanced Concurrency

Advanced concurrency patterns go beyond basic threading and provide sophisticated approaches to managing concurrent execution. These patterns address scalability, performance, and maintainability challenges in concurrent systems.

### 2.1 Why Advanced Concurrency Patterns?
- **Scalability**: Handle large numbers of concurrent operations efficiently
- **Performance**: Minimize contention and overhead
- **Maintainability**: Provide clear separation of concerns
- **Reliability**: Reduce race conditions and deadlocks
- **Flexibility**: Enable dynamic adaptation to workload

### 2.2 Common Advanced Patterns
- **Lock-Free Programming**: Data structures without mutexes
- **Actor Model**: Message-based concurrency
- **Thread Pools**: Efficient thread management
- **Async Programming**: Non-blocking operations
- **Message Passing**: Loose coupling between components
- **Advanced Synchronization**: Better coordination primitives

## 3. Lock-Free Programming

Lock-free programming uses atomic operations to create thread-safe data structures without traditional locking mechanisms.

### 3.1 Benefits of Lock-Free Programming
- **No Deadlocks**: Atomic operations cannot deadlock
- **Better Performance**: Avoids mutex overhead
- **Scalability**: Reduces contention between threads
- **Responsiveness**: Threads don't block waiting for locks

### 3.2 Lock-Free Stack
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
                return false;
            }
        } while (!head_.compare_exchange_weak(old_head, old_head->next));
        
        result = old_head->data;
        delete old_head;
        return true;
    }
    
    bool empty() const {
        return head_.load() == nullptr;
    }
};
```

### 3.3 Lock-Free Queue
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
    void enqueue(const T& item) {
        Node* new_node = new Node;
        T* data = new T(item);
        new_node->data.store(data);
        
        Node* prev_tail = tail_.exchange(new_node);
        prev_tail->next.store(new_node);
    }
    
    bool dequeue(T& result) {
        Node* head = head_.load();
        Node* next = head->next.load();
        
        if (next == nullptr) {
            return false;
        }
        
        T* data = next->data.load();
        if (data == nullptr) {
            return false;
        }
        
        result = *data;
        delete data;
        
        head_.store(next);
        delete head;
        return true;
    }
};
```

### 3.4 Lock-Free Hash Table
```cpp
template<typename K, typename V>
class LockFreeHashTable {
private:
    struct Node {
        K key;
        V value;
        std::atomic<Node*> next{nullptr};
        
        Node(const K& k, const V& v) : key(k), value(v) {}
    };
    
    static constexpr size_t BUCKET_COUNT = 1024;
    std::array<std::atomic<Node*>, BUCKET_COUNT> buckets_;
    
    size_t hash(const K& key) const {
        return std::hash<K>{}(key) % BUCKET_COUNT;
    }
    
public:
    void insert(const K& key, const V& value) {
        size_t index = hash(key);
        Node* new_node = new Node(key, value);
        
        Node* old_head = buckets_[index].load();
        
        do {
            new_node->next.store(old_head);
        } while (!buckets_[index].compare_exchange_weak(old_head, new_node));
    }
    
    bool find(const K& key, V& value) const {
        size_t index = hash(key);
        Node* current = buckets_[index].load();
        
        while (current != nullptr) {
            if (current->key == key) {
                value = current->value;
                return true;
            }
            current = current->next.load();
        }
        
        return false;
    }
};
```

## 4. Actor Model

The actor model provides message-based concurrency where actors communicate through asynchronous messages.

### 4.1 Actor Model Principles
- **Isolation**: Actors have isolated state
- **Message Passing**: Communication through messages
- **Asynchronous**: Non-blocking message delivery
- **Location Transparency**: Actors can be local or remote

### 4.2 Actor Base Class
```cpp
class Actor {
private:
    std::queue<std::unique_ptr<Message>> mailbox_;
    std::mutex mailbox_mutex_;
    std::condition_variable mailbox_cv_;
    std::atomic<bool> running_{true};
    std::thread worker_thread_;
    
public:
    Actor() : worker_thread_(&Actor::process_messages, this) {}
    
    virtual ~Actor() {
        stop();
    }
    
    void send_message(std::unique_ptr<Message> message) {
        {
            std::lock_guard<std::mutex> lock(mailbox_mutex_);
            mailbox_.push(std::move(message));
        }
        mailbox_cv_.notify_one();
    }
    
    void stop() {
        running_.store(false);
        mailbox_cv_.notify_all();
        if (worker_thread_.joinable()) {
            worker_thread_.join();
        }
    }
    
private:
    void process_messages() {
        while (running_.load()) {
            std::unique_ptr<Message> message;
            
            {
                std::unique_lock<std::mutex> lock(mailbox_mutex_);
                mailbox_cv_.wait(lock, [this] { 
                    return !mailbox_.empty() || !running_.load(); 
                });
                
                if (!running_.load()) {
                    break;
                }
                
                message = std::move(mailbox_.front());
                mailbox_.pop();
            }
            
            message->process();
        }
    }
};
```

### 4.3 Counter Actor Example
```cpp
class CounterMessage : public Message {
private:
    std::function<void(int)> callback_;
    int value_;
    
public:
    CounterMessage(int value, std::function<void(int)> callback) 
        : value_(value), callback_(callback) {}
    
    void process() override {
        callback_(value_);
    }
};

class CounterActor : public Actor {
private:
    std::atomic<int> count_{0};
    
public:
    void increment(int value = 1) {
        send_message(std::make_unique<CounterMessage>(value, [this](int v) {
            count_.fetch_add(v);
        }));
    }
    
    void get_count(std::function<void(int)> callback) {
        send_message(std::make_unique<CounterMessage>(0, [this, callback](int) {
            callback(count_.load());
        }));
    }
};
```

## 5. Thread Pools

Thread pools efficiently manage a fixed number of worker threads to execute tasks.

### 5.1 Thread Pool Implementation
```cpp
class ThreadPool {
private:
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;
    std::mutex queue_mutex_;
    std::condition_variable condition_;
    std::atomic<bool> stop_{false};
    
public:
    ThreadPool(size_t num_threads) {
        for (size_t i = 0; i < num_threads; ++i) {
            workers_.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    
                    {
                        std::unique_lock<std::mutex> lock(queue_mutex_);
                        condition_.wait(lock, [this] { 
                            return stop_.load() || !tasks_.empty(); 
                        });
                        
                        if (stop_.load() && tasks_.empty()) {
                            return;
                        }
                        
                        task = std::move(tasks_.front());
                        tasks_.pop();
                    }
                    
                    task();
                }
            });
        }
    }
    
    ~ThreadPool() {
        stop_.store(true);
        condition_.notify_all();
        
        for (std::thread& worker : workers_) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }
    
    template<typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
        using return_type = typename std::result_of<F(Args...)>::type;
        
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
        std::future<return_type> result = task->get_future();
        
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            if (stop_.load()) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }
            
            tasks_.emplace([task] { (*task)(); });
        }
        
        condition_.notify_one();
        return result;
    }
};
```

### 5.2 Thread Pool Benefits
- **Resource Management**: Fixed number of threads
- **Task Queuing**: Automatic task scheduling
- **Load Balancing**: Even distribution of work
- **Performance**: Reduced thread creation overhead

## 6. Async Programming

Async programming enables non-blocking operations and futures for better resource utilization.

### 6.1 Async Task Manager
```cpp
class AsyncTaskManager {
private:
    std::vector<std::future<void>> tasks_;
    std::mutex tasks_mutex_;
    
public:
    template<typename F, typename... Args>
    void submit_task(F&& f, Args&&... args) {
        std::lock_guard<std::mutex> lock(tasks_mutex_);
        
        auto task = std::async(std::launch::async, std::forward<F>(f), std::forward<Args>(args)...);
        tasks_.push_back(std::move(task));
    }
    
    void wait_for_all() {
        std::lock_guard<std::mutex> lock(tasks_mutex_);
        
        for (auto& task : tasks_) {
            if (task.valid()) {
                task.wait();
            }
        }
    }
    
    void clear_completed() {
        std::lock_guard<std::mutex> lock(tasks_mutex_);
        
        tasks_.erase(
            std::remove_if(tasks_.begin(), tasks_.end(),
                [](const std::future<void>& task) {
                    return !task.valid() || task.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
                }),
            tasks_.end()
        );
    }
};
```

### 6.2 Promise-Based Async Operations
```cpp
class AsyncCalculator {
public:
    std::future<double> calculate_async(double value) {
        return std::async(std::launch::async, [value] {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            return value * value * 3.14159;
        });
    }
    
    std::future<std::string> process_string_async(const std::string& input) {
        return std::async(std::launch::async, [input] {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            std::string result = input;
            std::transform(result.begin(), result.end(), result.begin(), ::toupper);
            return result;
        });
    }
    
    std::future<std::vector<int>> generate_numbers_async(int count) {
        return std::async(std::launch::async, [count] {
            std::this_thread::sleep_for(std::chrono::milliseconds(75));
            std::vector<int> numbers;
            for (int i = 0; i < count; ++i) {
                numbers.push_back(i * i);
            }
            return numbers;
        });
    }
};
```

## 7. Advanced Synchronization Primitives

Modern C++ provides advanced synchronization primitives for better coordination.

### 7.1 Barrier Synchronization
```cpp
void demonstrateBarrier() {
    constexpr int num_threads = 4;
    std::barrier sync_point(num_threads);
    
    std::vector<std::thread> threads;
    
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([i, &sync_point] {
            std::cout << "Thread " << i << " starting work" << std::endl;
            
            // Simulate work
            std::this_thread::sleep_for(std::chrono::milliseconds(100 * (i + 1)));
            
            std::cout << "Thread " << i << " finished work, waiting at barrier" << std::endl;
            
            // Wait at barrier
            sync_point.arrive_and_wait();
            
            std::cout << "Thread " << i << " passed barrier" << std::endl;
        });
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
}
```

### 7.2 Latch Synchronization
```cpp
void demonstrateLatch() {
    constexpr int num_threads = 5;
    std::latch start_latch(1);
    std::latch finish_latch(num_threads);
    
    std::vector<std::thread> threads;
    
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([i, &start_latch, &finish_latch] {
            std::cout << "Thread " << i << " waiting to start" << std::endl;
            
            // Wait for start signal
            start_latch.wait();
            
            std::cout << "Thread " << i << " started work" << std::endl;
            
            // Simulate work
            std::this_thread::sleep_for(std::chrono::milliseconds(100 * (i + 1)));
            
            std::cout << "Thread " << i << " finished work" << std::endl;
            
            // Signal completion
            finish_latch.count_down();
        });
    }
    
    // Start all threads
    std::cout << "Starting all threads..." << std::endl;
    start_latch.count_down();
    
    // Wait for all threads to finish
    finish_latch.wait();
    std::cout << "All threads finished!" << std::endl;
    
    for (auto& thread : threads) {
        thread.join();
    }
}
```

### 7.3 Semaphore Synchronization
```cpp
void demonstrateSemaphore() {
    constexpr int max_concurrent = 3;
    std::counting_semaphore<max_concurrent> semaphore(max_concurrent);
    
    std::vector<std::thread> threads;
    
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([i, &semaphore] {
            std::cout << "Thread " << i << " requesting resource" << std::endl;
            
            // Acquire semaphore
            semaphore.acquire();
            
            std::cout << "Thread " << i << " acquired resource" << std::endl;
            
            // Simulate work
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            
            std::cout << "Thread " << i << " releasing resource" << std::endl;
            
            // Release semaphore
            semaphore.release();
        });
    }
    
    for (auto& thread : threads) {
        thread.join();
    }
}
```

### 7.4 Stop Token for Cooperative Cancellation
```cpp
void demonstrateStopToken() {
    std::stop_source stop_source;
    std::stop_token stop_token = stop_source.get_token();
    
    std::vector<std::jthread> threads;
    
    for (int i = 0; i < 3; ++i) {
        threads.emplace_back([i, stop_token] {
            while (!stop_token.stop_requested()) {
                std::cout << "Thread " << i << " working..." << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            std::cout << "Thread " << i << " stopped" << std::endl;
        });
    }
    
    // Let threads work for a bit
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
    // Request stop
    std::cout << "Requesting stop..." << std::endl;
    stop_source.request_stop();
    
    // Threads will automatically join when going out of scope
}
```

## 8. Message Passing

Message passing enables loose coupling between concurrent components.

### 8.1 Message Types
```cpp
enum class MessageType {
    DATA,
    CONTROL,
    HEARTBEAT
};

struct Message {
    MessageType type;
    std::string content;
    std::chrono::steady_clock::time_point timestamp;
    
    Message(MessageType t, const std::string& c) 
        : type(t), content(c), timestamp(std::chrono::steady_clock::now()) {}
};
```

### 8.2 Message Queue
```cpp
class MessageQueue {
private:
    std::queue<Message> messages_;
    std::mutex mutex_;
    std::condition_variable cv_;
    
public:
    void enqueue(const Message& message) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            messages_.push(message);
        }
        cv_.notify_one();
    }
    
    Message dequeue() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this] { return !messages_.empty(); });
        
        Message message = messages_.front();
        messages_.pop();
        return message;
    }
    
    bool try_dequeue(Message& message, std::chrono::milliseconds timeout) {
        std::unique_lock<std::mutex> lock(mutex_);
        
        if (cv_.wait_for(lock, timeout, [this] { return !messages_.empty(); })) {
            message = messages_.front();
            messages_.pop();
            return true;
        }
        
        return false;
    }
    
    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return messages_.size();
    }
};
```

### 8.3 Message Processor
```cpp
class MessageProcessor {
private:
    MessageQueue& input_queue_;
    MessageQueue& output_queue_;
    std::atomic<bool> running_{true};
    std::thread worker_thread_;
    
public:
    MessageProcessor(MessageQueue& input, MessageQueue& output) 
        : input_queue_(input), output_queue_(output), 
          worker_thread_(&MessageProcessor::process_messages, this) {}
    
    ~MessageProcessor() {
        stop();
    }
    
    void stop() {
        running_.store(false);
        if (worker_thread_.joinable()) {
            worker_thread_.join();
        }
    }
    
private:
    void process_messages() {
        while (running_.load()) {
            Message message;
            if (input_queue_.try_dequeue(message, std::chrono::milliseconds(100))) {
                // Process message
                switch (message.type) {
                    case MessageType::DATA:
                        process_data_message(message);
                        break;
                    case MessageType::CONTROL:
                        process_control_message(message);
                        break;
                    case MessageType::HEARTBEAT:
                        process_heartbeat_message(message);
                        break;
                }
            }
        }
    }
    
    void process_data_message(const Message& message) {
        std::string processed = "Processed: " + message.content;
        output_queue_.enqueue(Message(MessageType::DATA, processed));
    }
    
    void process_control_message(const Message& message) {
        std::string response = "Control response: " + message.content;
        output_queue_.enqueue(Message(MessageType::CONTROL, response));
    }
    
    void process_heartbeat_message(const Message& message) {
        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - message.timestamp);
        std::string response = "Heartbeat received, latency: " + std::to_string(duration.count()) + "ms";
        output_queue_.enqueue(Message(MessageType::HEARTBEAT, response));
    }
};
```

## 9. Best Practices

### 9.1 Lock-Free Programming
1. **Use atomic operations**: Prefer atomic operations over mutexes when possible
2. **Handle ABA problem**: Be aware of the ABA problem in lock-free data structures
3. **Memory ordering**: Understand memory ordering semantics
4. **Testing**: Thoroughly test lock-free implementations
5. **Performance**: Profile to ensure performance benefits

### 9.2 Actor Model
1. **Message design**: Design clear and simple message interfaces
2. **State isolation**: Keep actor state isolated and immutable when possible
3. **Error handling**: Implement proper error handling in actors
4. **Supervision**: Implement supervision hierarchies for fault tolerance
5. **Testing**: Test actors in isolation and in combination

### 9.3 Thread Pools
1. **Size determination**: Choose appropriate thread pool size
2. **Task design**: Design tasks to be independent and stateless
3. **Resource management**: Properly manage thread pool lifecycle
4. **Load balancing**: Ensure even distribution of work
5. **Monitoring**: Monitor thread pool performance and utilization

### 9.4 Async Programming
1. **Future handling**: Properly handle futures and exceptions
2. **Resource cleanup**: Ensure proper cleanup of async resources
3. **Error propagation**: Implement proper error propagation
4. **Cancellation**: Support task cancellation when appropriate
5. **Performance**: Avoid blocking operations in async contexts

## 10. Common Pitfalls and How to Avoid Them

### 10.1 Lock-Free Programming Issues
```cpp
// Problem: ABA problem in lock-free stack
// Solution: Use hazard pointers or epoch-based reclamation

// Problem: Memory ordering issues
// Solution: Use appropriate memory ordering semantics

// Problem: Complex lock-free algorithms
// Solution: Use proven implementations or libraries
```

### 10.2 Actor Model Issues
```cpp
// Problem: Message ordering issues
// Solution: Implement proper message sequencing

// Problem: Deadlock in actor communication
// Solution: Design acyclic communication patterns

// Problem: Actor state corruption
// Solution: Keep state immutable and use message passing
```

### 10.3 Thread Pool Issues
```cpp
// Problem: Thread pool starvation
// Solution: Monitor and adjust thread pool size

// Problem: Task dependencies
// Solution: Use futures or async patterns for dependencies

// Problem: Resource leaks
// Solution: Implement proper cleanup and shutdown
```

## 11. Exercises

### 11.1 Basic Exercises
1. **Lock-Free Stack**: Implement a lock-free stack with proper memory ordering.
2. **Actor Communication**: Create actors that communicate through messages.
3. **Thread Pool**: Implement a simple thread pool with task queuing.
4. **Async Operations**: Create async operations using futures.

### 11.2 Intermediate Exercises
1. **Lock-Free Queue**: Implement a lock-free queue with proper synchronization.
2. **Actor Supervision**: Implement actor supervision and error handling.
3. **Thread Pool Monitoring**: Add monitoring and metrics to thread pool.
4. **Message Passing**: Implement a message passing system between components.

### 11.3 Advanced Exercises
1. **Lock-Free Hash Table**: Implement a lock-free hash table with rehashing.
2. **Actor System**: Build a complete actor system with supervision.
3. **Advanced Thread Pool**: Implement work-stealing thread pool.
4. **Distributed Actors**: Extend actor model for distributed systems.

## 12. Summary

Advanced concurrency patterns provide sophisticated approaches to managing concurrent execution:

- **Lock-Free Programming**: Uses atomic operations for thread-safe data structures
- **Actor Model**: Provides message-based concurrency with isolated state
- **Thread Pools**: Efficiently manage worker threads for task execution
- **Async Programming**: Enables non-blocking operations and futures
- **Advanced Synchronization**: Provides better coordination primitives
- **Message Passing**: Enables loose coupling between concurrent components

These patterns address scalability, performance, and maintainability challenges in concurrent systems. Understanding and applying these patterns is essential for building high-performance, scalable applications.

## 13. Additional Resources

- [C++ Concurrency in Action](https://www.manning.com/books/c-plus-plus-concurrency-in-action)
- [The Art of Multiprocessor Programming](https://www.elsevier.com/books/the-art-of-multiprocessor-programming/herlihy/978-0-12-415950-1)
- [Actor Model](https://en.wikipedia.org/wiki/Actor_model)
- [Lock-Free Programming](https://preshing.com/20120612/an-introduction-to-lock-free-programming/)
- [C++ Reference - Concurrency](https://en.cppreference.com/w/cpp/thread)

## 14. Next Steps

After completing this lesson, you should:
1. Practice implementing lock-free data structures
2. Build actor-based systems for concurrent processing
3. Implement thread pools for efficient task execution
4. Use async programming patterns in your applications
5. Explore distributed concurrency patterns and systems
