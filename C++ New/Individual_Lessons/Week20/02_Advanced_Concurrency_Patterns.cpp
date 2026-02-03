/*
 * Lesson 20.2: Advanced Concurrency Patterns
 * 
 * This file demonstrates advanced concurrency patterns including
 * lock-free programming, actor model, message passing, thread pools,
 * async programming, and advanced synchronization primitives.
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
#include <optional>
#include <variant>
#include <any>
#include <string_view>
#include <filesystem>
#include <execution>
#include <coroutine>
#include <concepts>
#include <ranges>
#include <barrier>
#include <latch>
#include <semaphore>
#include <stop_token>
#include <jthread>

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
        
        bool empty() const {
            Node* head = head_.load();
            Node* next = head->next.load();
            return next == nullptr;
        }
    };
    
    // Lock-free hash table using atomic operations
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
        LockFreeHashTable() {
            for (auto& bucket : buckets_) {
                bucket.store(nullptr);
            }
        }
        
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
        
        bool remove(const K& key) {
            size_t index = hash(key);
            Node* current = buckets_[index].load();
            Node* prev = nullptr;
            
            while (current != nullptr) {
                if (current->key == key) {
                    if (prev == nullptr) {
                        buckets_[index].store(current->next.load());
                    } else {
                        prev->next.store(current->next.load());
                    }
                    delete current;
                    return true;
                }
                prev = current;
                current = current->next.load();
            }
            
            return false;
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
        
        // Pop elements
        std::cout << "Stack elements: ";
        int value;
        while (stack.pop(value)) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
        
        // Test lock-free queue
        LockFreeQueue<std::string> queue;
        
        // Enqueue elements
        for (int i = 0; i < 5; ++i) {
            queue.enqueue("Item " + std::to_string(i));
        }
        
        // Dequeue elements
        std::cout << "Queue elements: ";
        std::string item;
        while (queue.dequeue(item)) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
        
        // Test lock-free hash table
        LockFreeHashTable<std::string, int> hash_table;
        
        // Insert elements
        hash_table.insert("Alice", 95);
        hash_table.insert("Bob", 87);
        hash_table.insert("Charlie", 92);
        
        // Find elements
        int score;
        if (hash_table.find("Alice", score)) {
            std::cout << "Alice's score: " << score << std::endl;
        }
        
        if (hash_table.find("Bob", score)) {
            std::cout << "Bob's score: " << score << std::endl;
        }
    }
}

// Example 2: Actor Model
namespace ActorModel {
    
    // Message base class
    class Message {
    public:
        virtual ~Message() = default;
        virtual void process() = 0;
    };
    
    // Actor base class
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
    
    // Counter actor
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
    
    // Calculator actor
    class CalculatorMessage : public Message {
    private:
        std::function<void(double)> callback_;
        double value1_, value2_;
        char operation_;
        
    public:
        CalculatorMessage(double v1, double v2, char op, std::function<void(double)> callback)
            : value1_(v1), value2_(v2), operation_(op), callback_(callback) {}
        
        void process() override {
            double result = 0;
            switch (operation_) {
                case '+': result = value1_ + value2_; break;
                case '-': result = value1_ - value2_; break;
                case '*': result = value1_ * value2_; break;
                case '/': result = (value2_ != 0) ? value1_ / value2_ : 0; break;
                default: result = 0; break;
            }
            callback_(result);
        }
    };
    
    class CalculatorActor : public Actor {
    public:
        void calculate(double v1, double v2, char op, std::function<void(double)> callback) {
            send_message(std::make_unique<CalculatorMessage>(v1, v2, op, callback));
        }
    };
    
    void demonstrateActorModel() {
        std::cout << "\n=== Actor Model ===" << std::endl;
        
        // Test counter actor
        CounterActor counter;
        
        // Increment counter
        for (int i = 0; i < 10; ++i) {
            counter.increment();
        }
        
        // Get count
        counter.get_count([](int count) {
            std::cout << "Counter value: " << count << std::endl;
        });
        
        // Test calculator actor
        CalculatorActor calculator;
        
        // Perform calculations
        calculator.calculate(10, 5, '+', [](double result) {
            std::cout << "10 + 5 = " << result << std::endl;
        });
        
        calculator.calculate(10, 5, '-', [](double result) {
            std::cout << "10 - 5 = " << result << std::endl;
        });
        
        calculator.calculate(10, 5, '*', [](double result) {
            std::cout << "10 * 5 = " << result << std::endl;
        });
        
        calculator.calculate(10, 5, '/', [](double result) {
            std::cout << "10 / 5 = " << result << std::endl;
        });
        
        // Wait for messages to be processed
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// Example 3: Thread Pool
namespace ThreadPool {
    
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
    
    void demonstrateThreadPool() {
        std::cout << "\n=== Thread Pool ===" << std::endl;
        
        ThreadPool pool(4);
        
        // Submit tasks
        std::vector<std::future<int>> results;
        
        for (int i = 0; i < 10; ++i) {
            results.emplace_back(pool.enqueue([i] {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                return i * i;
            }));
        }
        
        // Collect results
        std::cout << "Task results: ";
        for (auto& result : results) {
            std::cout << result.get() << " ";
        }
        std::cout << std::endl;
        
        // Submit tasks with different types
        auto string_task = pool.enqueue([] {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            return std::string("Hello from thread pool!");
        });
        
        auto double_task = pool.enqueue([] {
            std::this_thread::sleep_for(std::chrono::milliseconds(75));
            return 3.14159;
        });
        
        std::cout << "String result: " << string_task.get() << std::endl;
        std::cout << "Double result: " << double_task.get() << std::endl;
    }
}

// Example 4: Async Programming
namespace AsyncProgramming {
    
    // Async task manager
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
    
    // Promise-based async operations
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
    
    void demonstrateAsyncProgramming() {
        std::cout << "\n=== Async Programming ===" << std::endl;
        
        // Test async task manager
        AsyncTaskManager task_manager;
        
        // Submit multiple tasks
        for (int i = 0; i < 5; ++i) {
            task_manager.submit_task([i] {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                std::cout << "Task " << i << " completed" << std::endl;
            });
        }
        
        // Wait for all tasks to complete
        task_manager.wait_for_all();
        
        // Test promise-based async operations
        AsyncCalculator calculator;
        
        // Start multiple async operations
        auto future1 = calculator.calculate_async(5.0);
        auto future2 = calculator.process_string_async("hello world");
        auto future3 = calculator.generate_numbers_async(10);
        
        // Collect results
        std::cout << "Calculation result: " << future1.get() << std::endl;
        std::cout << "String result: " << future2.get() << std::endl;
        
        auto numbers = future3.get();
        std::cout << "Generated numbers: ";
        for (int num : numbers) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}

// Example 5: Advanced Synchronization Primitives
namespace AdvancedSynchronization {
    
    // Barrier synchronization
    void demonstrateBarrier() {
        std::cout << "\n=== Barrier Synchronization ===" << std::endl;
        
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
    
    // Latch synchronization
    void demonstrateLatch() {
        std::cout << "\n=== Latch Synchronization ===" << std::endl;
        
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
    
    // Semaphore synchronization
    void demonstrateSemaphore() {
        std::cout << "\n=== Semaphore Synchronization ===" << std::endl;
        
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
    
    // Stop token for cooperative cancellation
    void demonstrateStopToken() {
        std::cout << "\n=== Stop Token for Cooperative Cancellation ===" << std::endl;
        
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
    
    void demonstrateAdvancedSynchronization() {
        demonstrateBarrier();
        demonstrateLatch();
        demonstrateSemaphore();
        demonstrateStopToken();
    }
}

// Example 6: Message Passing
namespace MessagePassing {
    
    // Message types
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
    
    // Message queue
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
    
    // Message processor
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
    
    void demonstrateMessagePassing() {
        std::cout << "\n=== Message Passing ===" << std::endl;
        
        MessageQueue input_queue;
        MessageQueue output_queue;
        
        MessageProcessor processor(input_queue, output_queue);
        
        // Send messages
        input_queue.enqueue(Message(MessageType::DATA, "Hello World"));
        input_queue.enqueue(Message(MessageType::CONTROL, "Start Processing"));
        input_queue.enqueue(Message(MessageType::HEARTBEAT, "Ping"));
        input_queue.enqueue(Message(MessageType::DATA, "Another message"));
        
        // Process messages
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        // Collect responses
        std::cout << "Output queue size: " << output_queue.size() << std::endl;
        
        while (output_queue.size() > 0) {
            Message response = output_queue.dequeue();
            std::cout << "Response: " << response.content << std::endl;
        }
        
        processor.stop();
    }
}

int main() {
    std::cout << "=== Advanced Concurrency Patterns Demonstration ===" << std::endl;
    std::cout << "This program demonstrates advanced concurrency patterns including\n"
              << "lock-free programming, actor model, message passing, thread pools,\n"
              << "async programming, and advanced synchronization primitives.\n" << std::endl;
    
    // Demonstrate various concurrency patterns
    LockFreeProgramming::demonstrateLockFreeProgramming();
    ActorModel::demonstrateActorModel();
    ThreadPool::demonstrateThreadPool();
    AsyncProgramming::demonstrateAsyncProgramming();
    AdvancedSynchronization::demonstrateAdvancedSynchronization();
    MessagePassing::demonstrateMessagePassing();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Lock-free programming uses atomic operations for thread-safe data structures" << std::endl;
    std::cout << "2. Actor model provides message-based concurrency with isolated state" << std::endl;
    std::cout << "3. Thread pools efficiently manage worker threads for task execution" << std::endl;
    std::cout << "4. Async programming enables non-blocking operations and futures" << std::endl;
    std::cout << "5. Advanced synchronization primitives provide better coordination" << std::endl;
    std::cout << "6. Message passing enables loose coupling between concurrent components" << std::endl;
    std::cout << "7. Modern C++ provides powerful concurrency primitives and patterns" << std::endl;
    std::cout << "8. Proper concurrency design is essential for scalable applications" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC (C++20):
 * g++ -std=c++20 -Wall -Wextra -O2 -pthread -o advanced_concurrency 02_Advanced_Concurrency_Patterns.cpp
 * 
 * Using Clang (C++20):
 * clang++ -std=c++20 -Wall -Wextra -O2 -pthread -o advanced_concurrency 02_Advanced_Concurrency_Patterns.cpp
 * 
 * Using MSVC (Visual Studio 2019+):
 * cl /std:c++20 /EHsc /O2 02_Advanced_Concurrency_Patterns.cpp
 * 
 * Running:
 * ./advanced_concurrency (Linux/macOS)
 * advanced_concurrency.exe (Windows)
 * 
 * Note: This lesson requires C++20 for some features.
 * C++17 is the minimum required version for most features.
 * 
 * Advanced Concurrency Patterns Notes:
 * - Lock-free programming uses atomic operations for thread-safe data structures
 * - Actor model provides message-based concurrency with isolated state
 * - Thread pools efficiently manage worker threads for task execution
 * - Async programming enables non-blocking operations and futures
 * - Advanced synchronization primitives provide better coordination
 * - Message passing enables loose coupling between concurrent components
 * - Modern C++ provides powerful concurrency primitives and patterns
 * - Proper concurrency design is essential for scalable applications
 */"""
