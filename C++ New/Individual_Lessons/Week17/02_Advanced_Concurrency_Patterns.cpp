/*
 * Lesson 17.2: Advanced Concurrency Patterns
 * 
 * This file demonstrates advanced concurrency patterns including
 * lock-free programming, atomic operations, memory ordering,
 * concurrent data structures, and high-performance synchronization.
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
#include <shared_mutex>
#include <semaphore>
#include <latch>
#include <barrier>

// Example 1: Lock-Free Programming
namespace LockFreeProgramming {
    
    // Lock-free stack using atomic operations
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
        ~LockFreeStack() {
            // Clean up remaining nodes
            while (Node* node = head_.load()) {
                head_.store(node->next);
                delete node;
            }
        }
        
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
        
        bool empty() const {
            return head_.load() == nullptr;
        }
        
        size_t size() const {
            size_t count = 0;
            Node* current = head_.load();
            while (current != nullptr) {
                ++count;
                current = current->next;
            }
            return count;
        }
    };
    
    // Lock-free queue using atomic operations
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
        LockFreeQueue() {
            // Initialize with dummy node
        }
        
        ~LockFreeQueue() {
            while (Node* node = head_.load()) {
                head_.store(node->next);
                delete node;
            }
        }
        
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
        
        bool empty() const {
            Node* head = head_.load();
            Node* next = head->next.load();
            return next == nullptr;
        }
    };
    
    // Atomic counter with memory ordering
    class AtomicCounter {
    private:
        std::atomic<int> count_{0};
        
    public:
        void increment() {
            // Relaxed ordering for simple increment
            count_.fetch_add(1, std::memory_order_relaxed);
        }
        
        void decrement() {
            count_.fetch_sub(1, std::memory_order_relaxed);
        }
        
        int get() const {
            // Acquire ordering to ensure we see all previous writes
            return count_.load(std::memory_order_acquire);
        }
        
        bool compare_and_set(int expected, int desired) {
            // Sequential consistency for compare-and-swap
            return count_.compare_exchange_weak(expected, desired, std::memory_order_seq_cst);
        }
        
        int exchange(int new_value) {
            return count_.exchange(new_value, std::memory_order_acq_rel);
        }
    };
    
    void demonstrateLockFreeProgramming() {
        std::cout << "=== Lock-Free Programming ===" << std::endl;
        
        // Test lock-free stack
        LockFreeStack<int> stack;
        
        // Push elements
        for (int i = 0; i < 10; ++i) {
            stack.push(i);
        }
        
        std::cout << "Stack size: " << stack.size() << std::endl;
        
        // Pop elements
        int value;
        while (stack.pop(value)) {
            std::cout << "Popped: " << value << std::endl;
        }
        
        // Test lock-free queue
        LockFreeQueue<std::string> queue;
        
        // Enqueue elements
        for (int i = 0; i < 5; ++i) {
            queue.enqueue("Item " + std::to_string(i));
        }
        
        // Dequeue elements
        std::string item;
        while (queue.dequeue(item)) {
            std::cout << "Dequeued: " << item << std::endl;
        }
        
        // Test atomic counter
        AtomicCounter counter;
        
        // Simulate concurrent increments
        std::vector<std::thread> threads;
        for (int i = 0; i < 4; ++i) {
            threads.emplace_back([&counter]() {
                for (int j = 0; j < 1000; ++j) {
                    counter.increment();
                }
            });
        }
        
        for (auto& thread : threads) {
            thread.join();
        }
        
        std::cout << "Final counter value: " << counter.get() << std::endl;
    }
}

// Example 2: Memory Ordering and Synchronization
namespace MemoryOrdering {
    
    // Example demonstrating different memory orderings
    class MemoryOrderingExample {
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
            
            std::cout << "Sequential consistency - r1: " << r1.load() << ", r2: " << r2.load() << std::endl;
        }
    };
    
    // Double-checked locking pattern
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
        
        void doSomething() {
            std::cout << "Singleton instance doing something" << std::endl;
        }
    };
    
    std::atomic<Singleton*> Singleton::instance_{nullptr};
    std::mutex Singleton::mutex_;
    
    void demonstrateMemoryOrdering() {
        std::cout << "\n=== Memory Ordering ===" << std::endl;
        
        MemoryOrderingExample example;
        
        // Test producer-consumer with memory ordering
        std::thread producer_thread(&MemoryOrderingExample::producer, &example);
        std::thread consumer_thread(&MemoryOrderingExample::consumer, &example);
        
        producer_thread.join();
        consumer_thread.join();
        
        // Test sequential consistency
        example.demonstrate_sequential_consistency();
        
        // Test singleton with double-checked locking
        std::vector<std::thread> singleton_threads;
        for (int i = 0; i < 4; ++i) {
            singleton_threads.emplace_back([]() {
                Singleton* instance = Singleton::getInstance();
                instance->doSomething();
            });
        }
        
        for (auto& thread : singleton_threads) {
            thread.join();
        }
    }
}

// Example 3: Concurrent Data Structures
namespace ConcurrentDataStructures {
    
    // Thread-safe hash map using fine-grained locking
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
        
        bool remove(const K& key) {
            size_t bucket_index = hash(key);
            auto& bucket = buckets_[bucket_index];
            
            std::unique_lock<std::shared_mutex> lock(bucket.mutex);
            return bucket.data.erase(key) > 0;
        }
        
        size_t size() const {
            size_t total_size = 0;
            for (const auto& bucket : buckets_) {
                std::shared_lock<std::shared_mutex> lock(bucket.mutex);
                total_size += bucket.data.size();
            }
            return total_size;
        }
    };
    
    // Lock-free ring buffer
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
        
        bool empty() const {
            return read_pos_.load(std::memory_order_acquire) == 
                   write_pos_.load(std::memory_order_acquire);
        }
        
        bool full() const {
            size_t current_write = write_pos_.load(std::memory_order_acquire);
            size_t next_write = (current_write + 1) & (Size - 1);
            return next_write == read_pos_.load(std::memory_order_acquire);
        }
        
        size_t size() const {
            size_t write_pos = write_pos_.load(std::memory_order_acquire);
            size_t read_pos = read_pos_.load(std::memory_order_acquire);
            return (write_pos - read_pos) & (Size - 1);
        }
    };
    
    // Thread-safe producer-consumer queue
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
        
        bool empty() const {
            std::lock_guard<std::mutex> lock(mutex_);
            return queue_.empty();
        }
        
        size_t size() const {
            std::lock_guard<std::mutex> lock(mutex_);
            return queue_.size();
        }
    };
    
    void demonstrateConcurrentDataStructures() {
        std::cout << "\n=== Concurrent Data Structures ===" << std::endl;
        
        // Test concurrent hash map
        ConcurrentHashMap<std::string, int> hash_map;
        
        std::vector<std::thread> threads;
        for (int i = 0; i < 4; ++i) {
            threads.emplace_back([&hash_map, i]() {
                for (int j = 0; j < 100; ++j) {
                    std::string key = "key_" + std::to_string(i * 100 + j);
                    hash_map.insert(key, i * 100 + j);
                }
            });
        }
        
        for (auto& thread : threads) {
            thread.join();
        }
        
        std::cout << "Hash map size: " << hash_map.size() << std::endl;
        
        // Test lock-free ring buffer
        LockFreeRingBuffer<int, 16> ring_buffer;
        
        // Producer thread
        std::thread producer([&ring_buffer]() {
            for (int i = 0; i < 20; ++i) {
                while (!ring_buffer.push(i)) {
                    std::this_thread::yield();
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        });
        
        // Consumer thread
        std::thread consumer([&ring_buffer]() {
            int value;
            int count = 0;
            while (count < 20) {
                if (ring_buffer.pop(value)) {
                    std::cout << "Consumed: " << value << std::endl;
                    ++count;
                } else {
                    std::this_thread::yield();
                }
            }
        });
        
        producer.join();
        consumer.join();
        
        // Test producer-consumer queue
        ProducerConsumerQueue<std::string> pc_queue;
        
        std::thread producer2([&pc_queue]() {
            for (int i = 0; i < 10; ++i) {
                pc_queue.push("Message " + std::to_string(i));
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
            pc_queue.shutdown();
        });
        
        std::thread consumer2([&pc_queue]() {
            std::string message;
            while (pc_queue.pop(message)) {
                std::cout << "Received: " << message << std::endl;
            }
        });
        
        producer2.join();
        consumer2.join();
    }
}

// Example 4: High-Performance Synchronization
namespace HighPerformanceSynchronization {
    
    // Spinlock implementation
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
    
    // Read-write spinlock
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
    
    // Thread pool with work stealing
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
        
        ~ThreadPool() {
            stop_ = true;
            for (auto& worker : workers_) {
                if (worker.joinable()) {
                    worker.join();
                }
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
    
    // Barrier implementation
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
    
    void demonstrateHighPerformanceSynchronization() {
        std::cout << "\n=== High-Performance Synchronization ===" << std::endl;
        
        // Test spinlock
        Spinlock spinlock;
        std::atomic<int> counter{0};
        
        std::vector<std::thread> spinlock_threads;
        for (int i = 0; i < 4; ++i) {
            spinlock_threads.emplace_back([&spinlock, &counter]() {
                for (int j = 0; j < 1000; ++j) {
                    std::lock_guard<Spinlock> lock(spinlock);
                    counter.fetch_add(1);
                }
            });
        }
        
        for (auto& thread : spinlock_threads) {
            thread.join();
        }
        
        std::cout << "Spinlock counter: " << counter.load() << std::endl;
        
        // Test thread pool
        ThreadPool pool(4);
        
        std::vector<std::future<int>> futures;
        for (int i = 0; i < 10; ++i) {
            futures.push_back(pool.enqueue([](int value) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                return value * value;
            }, i));
        }
        
        int total = 0;
        for (auto& future : futures) {
            total += future.get();
        }
        
        std::cout << "Thread pool total: " << total << std::endl;
        
        // Test barrier
        Barrier barrier(4);
        std::atomic<int> barrier_counter{0};
        
        std::vector<std::thread> barrier_threads;
        for (int i = 0; i < 4; ++i) {
            barrier_threads.emplace_back([&barrier, &barrier_counter, i]() {
                std::cout << "Thread " << i << " before barrier" << std::endl;
                barrier.wait();
                std::cout << "Thread " << i << " after barrier" << std::endl;
                barrier_counter.fetch_add(1);
            });
        }
        
        for (auto& thread : barrier_threads) {
            thread.join();
        }
        
        std::cout << "Barrier threads completed: " << barrier_counter.load() << std::endl;
    }
}

// Example 5: Advanced Concurrency Patterns
namespace AdvancedConcurrencyPatterns {
    
    // Actor model implementation
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
    
    // Example actor for processing numbers
    class NumberProcessor : public Actor<int> {
    private:
        std::atomic<int> processed_count_{0};
        
        void process_message(const int& message) override {
            // Simulate processing
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            processed_count_.fetch_add(1);
            std::cout << "Processed number: " << message << std::endl;
        }
        
    public:
        int get_processed_count() const {
            return processed_count_.load();
        }
    };
    
    // Pipeline pattern
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
    
    // MapReduce pattern
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
    
    void demonstrateAdvancedConcurrencyPatterns() {
        std::cout << "\n=== Advanced Concurrency Patterns ===" << std::endl;
        
        // Test actor model
        NumberProcessor processor;
        
        // Send messages to actor
        for (int i = 0; i < 10; ++i) {
            processor.send_message(i);
        }
        
        // Wait for processing
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        
        std::cout << "Actor processed " << processor.get_processed_count() << " messages" << std::endl;
        
        // Test pipeline
        Pipeline<int, int> pipeline;
        
        pipeline.add_stage([](int x) { return x * 2; });
        pipeline.add_stage([](int x) { return x + 1; });
        pipeline.add_stage([](int x) { return x * x; });
        
        int result = pipeline.process(5);
        std::cout << "Pipeline result: " << result << std::endl;
        
        // Test MapReduce
        MapReduce<std::string, std::string, int> map_reduce(
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
        
        std::vector<std::string> texts = {
            "hello world hello",
            "world hello world",
            "hello hello world"
        };
        
        auto word_counts = map_reduce.execute(texts);
        
        std::cout << "Word counts:" << std::endl;
        for (const auto& [word, count] : word_counts) {
            std::cout << "  " << word << ": " << count << std::endl;
        }
    }
}

int main() {
    std::cout << "=== Advanced Concurrency Patterns Demonstration ===" << std::endl;
    std::cout << "This program demonstrates advanced concurrency patterns including\n"
              << "lock-free programming, memory ordering, concurrent data structures,\n"
              << "high-performance synchronization, and advanced patterns.\n" << std::endl;
    
    // Demonstrate various advanced concurrency patterns
    LockFreeProgramming::demonstrateLockFreeProgramming();
    MemoryOrdering::demonstrateMemoryOrdering();
    ConcurrentDataStructures::demonstrateConcurrentDataStructures();
    HighPerformanceSynchronization::demonstrateHighPerformanceSynchronization();
    AdvancedConcurrencyPatterns::demonstrateAdvancedConcurrencyPatterns();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Lock-free programming provides high performance but requires careful design" << std::endl;
    std::cout << "2. Memory ordering is crucial for correct concurrent programming" << std::endl;
    std::cout << "3. Concurrent data structures must balance performance and correctness" << std::endl;
    std::cout << "4. High-performance synchronization requires understanding hardware behavior" << std::endl;
    std::cout << "5. Advanced patterns like actors and pipelines enable scalable architectures" << std::endl;
    std::cout << "6. Atomic operations provide building blocks for lock-free algorithms" << std::endl;
    std::cout << "7. Thread pools and work stealing improve resource utilization" << std::endl;
    std::cout << "8. Proper synchronization prevents data races and ensures correctness" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++20 -Wall -Wextra -O2 -pthread -o advanced_concurrency_patterns 02_Advanced_Concurrency_Patterns.cpp
 * 
 * Using Clang:
 * clang++ -std=c++20 -Wall -Wextra -O2 -pthread -o advanced_concurrency_patterns 02_Advanced_Concurrency_Patterns.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++20 /EHsc /O2 02_Advanced_Concurrency_Patterns.cpp
 * 
 * Running:
 * ./advanced_concurrency_patterns (Linux/macOS)
 * advanced_concurrency_patterns.exe (Windows)
 * 
 * Note: This lesson requires C++20 for some features.
 * C++17 is the minimum required version.
 * 
 * Advanced Concurrency Patterns Notes:
 * - Lock-free programming provides high performance but requires careful design
 * - Memory ordering is crucial for correct concurrent programming
 * - Concurrent data structures must balance performance and correctness
 * - High-performance synchronization requires understanding hardware behavior
 * - Advanced patterns like actors and pipelines enable scalable architectures
 * - Atomic operations provide building blocks for lock-free algorithms
 * - Thread pools and work stealing improve resource utilization
 * - Proper synchronization prevents data races and ensures correctness
 */"""
