/*
 * Lesson 15.1: Advanced Concurrency
 * 
 * This file demonstrates advanced concurrency concepts, thread pools,
 * async programming, and concurrent data structures.
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <future>
#include <async>
#include <vector>
#include <queue>
#include <memory>
#include <chrono>
#include <random>
#include <algorithm>
#include <functional>
#include <exception>
#include <stdexcept>

// Example 1: Thread Pool Implementation
namespace ThreadPool {
    
    class ThreadPool {
    private:
        std::vector<std::thread> workers_;
        std::queue<std::function<void()>> tasks_;
        std::mutex queue_mutex_;
        std::condition_variable condition_;
        std::atomic<bool> stop_;
        
    public:
        ThreadPool(size_t num_threads) : stop_(false) {
            for (size_t i = 0; i < num_threads; ++i) {
                workers_.emplace_back([this] {
                    while (true) {
                        std::function<void()> task;
                        
                        {
                            std::unique_lock<std::mutex> lock(queue_mutex_);
                            condition_.wait(lock, [this] { return stop_ || !tasks_.empty(); });
                            
                            if (stop_ && tasks_.empty()) {
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
            {
                std::unique_lock<std::mutex> lock(queue_mutex_);
                stop_ = true;
            }
            
            condition_.notify_all();
            
            for (std::thread& worker : workers_) {
                worker.join();
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
                
                if (stop_) {
                    throw std::runtime_error("enqueue on stopped ThreadPool");
                }
                
                tasks_.emplace([task]() { (*task)(); });
            }
            
            condition_.notify_one();
            return result;
        }
        
        size_t size() const { return workers_.size(); }
        bool empty() const { return tasks_.empty(); }
    };
    
    void demonstrateThreadPool() {
        std::cout << "=== Thread Pool Demonstration ===" << std::endl;
        
        ThreadPool pool(4);
        
        // Enqueue some tasks
        std::vector<std::future<int>> results;
        
        for (int i = 0; i < 8; ++i) {
            results.emplace_back(pool.enqueue([i] {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                return i * i;
            }));
        }
        
        // Wait for all tasks to complete
        for (auto& result : results) {
            std::cout << "Result: " << result.get() << std::endl;
        }
        
        std::cout << "Thread pool size: " << pool.size() << std::endl;
    }
}

// Example 2: Advanced Async Programming
namespace AdvancedAsync {
    
    // Async with custom executor
    template<typename Executor, typename F, typename... Args>
    auto async_with_executor(Executor& executor, F&& f, Args&&... args) {
        using return_type = typename std::result_of<F(Args...)>::type;
        
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
        std::future<return_type> result = task->get_future();
        
        executor.enqueue([task]() { (*task)(); });
        
        return result;
    }
    
    // Async with timeout
    template<typename F, typename... Args>
    auto async_with_timeout(std::chrono::milliseconds timeout, F&& f, Args&&... args) {
        using return_type = typename std::result_of<F(Args...)>::type;
        
        auto future = std::async(std::launch::async, std::forward<F>(f), std::forward<Args>(args)...);
        
        if (future.wait_for(timeout) == std::future_status::timeout) {
            throw std::runtime_error("Async operation timed out");
        }
        
        return future.get();
    }
    
    // Async with retry
    template<typename F, typename... Args>
    auto async_with_retry(size_t max_retries, F&& f, Args&&... args) {
        using return_type = typename std::result_of<F(Args...)>::type;
        
        for (size_t attempt = 0; attempt < max_retries; ++attempt) {
            try {
                return std::async(std::launch::async, std::forward<F>(f), std::forward<Args>(args)...).get();
            } catch (const std::exception& e) {
                if (attempt == max_retries - 1) {
                    throw;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100 * (attempt + 1)));
            }
        }
        
        throw std::runtime_error("Max retries exceeded");
    }
    
    // Async with progress callback
    template<typename F, typename ProgressCallback, typename... Args>
    auto async_with_progress(F&& f, ProgressCallback&& progress, Args&&... args) {
        using return_type = typename std::result_of<F(Args...)>::type;
        
        auto future = std::async(std::launch::async, [&]() {
            progress(0);
            auto result = f(args...);
            progress(100);
            return result;
        });
        
        return future;
    }
    
    void demonstrateAdvancedAsync() {
        std::cout << "\n=== Advanced Async Programming ===" << std::endl;
        
        // Async with timeout
        try {
            auto result = async_with_timeout(std::chrono::milliseconds(500), []() {
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                return 42;
            });
            std::cout << "Async with timeout result: " << result << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Async with timeout error: " << e.what() << std::endl;
        }
        
        // Async with retry
        try {
            auto result = async_with_retry(3, []() {
                static int attempts = 0;
                if (++attempts < 3) {
                    throw std::runtime_error("Simulated failure");
                }
                return attempts;
            });
            std::cout << "Async with retry result: " << result << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Async with retry error: " << e.what() << std::endl;
        }
        
        // Async with progress
        auto future = async_with_progress([]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            return 100;
        }, [](int progress) {
            std::cout << "Progress: " << progress << "%" << std::endl;
        });
        
        std::cout << "Async with progress result: " << future.get() << std::endl;
    }
}

// Example 3: Concurrent Data Structures
namespace ConcurrentDataStructures {
    
    // Thread-safe queue
    template<typename T>
    class ConcurrentQueue {
    private:
        std::queue<T> queue_;
        mutable std::mutex mutex_;
        std::condition_variable condition_;
        
    public:
        void push(T item) {
            {
                std::lock_guard<std::mutex> lock(mutex_);
                queue_.push(item);
            }
            condition_.notify_one();
        }
        
        bool try_pop(T& item) {
            std::lock_guard<std::mutex> lock(mutex_);
            if (queue_.empty()) {
                return false;
            }
            item = queue_.front();
            queue_.pop();
            return true;
        }
        
        void pop(T& item) {
            std::unique_lock<std::mutex> lock(mutex_);
            condition_.wait(lock, [this] { return !queue_.empty(); });
            item = queue_.front();
            queue_.pop();
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
    
    // Thread-safe stack
    template<typename T>
    class ConcurrentStack {
    private:
        std::stack<T> stack_;
        mutable std::mutex mutex_;
        
    public:
        void push(T item) {
            std::lock_guard<std::mutex> lock(mutex_);
            stack_.push(item);
        }
        
        bool try_pop(T& item) {
            std::lock_guard<std::mutex> lock(mutex_);
            if (stack_.empty()) {
                return false;
            }
            item = stack_.top();
            stack_.pop();
            return true;
        }
        
        bool empty() const {
            std::lock_guard<std::mutex> lock(mutex_);
            return stack_.empty();
        }
        
        size_t size() const {
            std::lock_guard<std::mutex> lock(mutex_);
            return stack_.size();
        }
    };
    
    // Thread-safe hash map
    template<typename K, typename V>
    class ConcurrentHashMap {
    private:
        std::unordered_map<K, V> map_;
        mutable std::shared_mutex mutex_;
        
    public:
        void insert(const K& key, const V& value) {
            std::unique_lock<std::shared_mutex> lock(mutex_);
            map_[key] = value;
        }
        
        bool find(const K& key, V& value) const {
            std::shared_lock<std::shared_mutex> lock(mutex_);
            auto it = map_.find(key);
            if (it != map_.end()) {
                value = it->second;
                return true;
            }
            return false;
        }
        
        bool erase(const K& key) {
            std::unique_lock<std::shared_mutex> lock(mutex_);
            return map_.erase(key) > 0;
        }
        
        size_t size() const {
            std::shared_lock<std::shared_mutex> lock(mutex_);
            return map_.size();
        }
        
        bool empty() const {
            std::shared_lock<std::shared_mutex> lock(mutex_);
            return map_.empty();
        }
    };
    
    // Lock-free ring buffer
    template<typename T, size_t Size>
    class LockFreeRingBuffer {
    private:
        std::array<T, Size> buffer_;
        std::atomic<size_t> head_{0};
        std::atomic<size_t> tail_{0};
        
    public:
        bool push(const T& item) {
            size_t current_head = head_.load();
            size_t next_head = (current_head + 1) % Size;
            
            if (next_head == tail_.load()) {
                return false; // Buffer is full
            }
            
            buffer_[current_head] = item;
            head_.store(next_head);
            return true;
        }
        
        bool pop(T& item) {
            size_t current_tail = tail_.load();
            
            if (current_tail == head_.load()) {
                return false; // Buffer is empty
            }
            
            item = buffer_[current_tail];
            tail_.store((current_tail + 1) % Size);
            return true;
        }
        
        bool empty() const {
            return tail_.load() == head_.load();
        }
        
        bool full() const {
            size_t current_head = head_.load();
            size_t next_head = (current_head + 1) % Size;
            return next_head == tail_.load();
        }
        
        size_t size() const {
            size_t current_head = head_.load();
            size_t current_tail = tail_.load();
            return (current_head - current_tail + Size) % Size;
        }
    };
    
    void demonstrateConcurrentDataStructures() {
        std::cout << "\n=== Concurrent Data Structures ===" << std::endl;
        
        // Concurrent queue
        ConcurrentQueue<int> queue;
        
        // Producer thread
        std::thread producer([&queue]() {
            for (int i = 0; i < 10; ++i) {
                queue.push(i);
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        });
        
        // Consumer thread
        std::thread consumer([&queue]() {
            for (int i = 0; i < 10; ++i) {
                int item;
                queue.pop(item);
                std::cout << "Consumed: " << item << std::endl;
            }
        });
        
        producer.join();
        consumer.join();
        
        // Concurrent stack
        ConcurrentStack<int> stack;
        
        std::vector<std::thread> threads;
        for (int i = 0; i < 5; ++i) {
            threads.emplace_back([&stack, i]() {
                for (int j = 0; j < 3; ++j) {
                    stack.push(i * 10 + j);
                }
            });
        }
        
        for (auto& t : threads) {
            t.join();
        }
        
        std::cout << "Stack size: " << stack.size() << std::endl;
        
        // Concurrent hash map
        ConcurrentHashMap<std::string, int> map;
        
        std::vector<std::thread> map_threads;
        for (int i = 0; i < 5; ++i) {
            map_threads.emplace_back([&map, i]() {
                for (int j = 0; j < 10; ++j) {
                    std::string key = "key_" + std::to_string(i) + "_" + std::to_string(j);
                    map.insert(key, i * 10 + j);
                }
            });
        }
        
        for (auto& t : map_threads) {
            t.join();
        }
        
        std::cout << "Map size: " << map.size() << std::endl;
        
        // Lock-free ring buffer
        LockFreeRingBuffer<int, 10> ring_buffer;
        
        std::vector<std::thread> ring_threads;
        for (int i = 0; i < 3; ++i) {
            ring_threads.emplace_back([&ring_buffer, i]() {
                for (int j = 0; j < 5; ++j) {
                    while (!ring_buffer.push(i * 10 + j)) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    }
                }
            });
        }
        
        for (auto& t : ring_threads) {
            t.join();
        }
        
        std::cout << "Ring buffer size: " << ring_buffer.size() << std::endl;
    }
}

// Example 4: Advanced Synchronization
namespace AdvancedSynchronization {
    
    // Read-write lock
    class ReadWriteLock {
    private:
        std::shared_mutex mutex_;
        std::condition_variable_any read_condition_;
        std::condition_variable_any write_condition_;
        std::atomic<int> readers_{0};
        std::atomic<bool> writing_{false};
        
    public:
        void read_lock() {
            std::unique_lock<std::shared_mutex> lock(mutex_);
            read_condition_.wait(lock, [this] { return !writing_; });
            ++readers_;
        }
        
        void read_unlock() {
            std::lock_guard<std::shared_mutex> lock(mutex_);
            --readers_;
            if (readers_ == 0) {
                write_condition_.notify_one();
            }
        }
        
        void write_lock() {
            std::unique_lock<std::shared_mutex> lock(mutex_);
            write_condition_.wait(lock, [this] { return readers_ == 0 && !writing_; });
            writing_ = true;
        }
        
        void write_unlock() {
            std::lock_guard<std::shared_mutex> lock(mutex_);
            writing_ = false;
            read_condition_.notify_all();
            write_condition_.notify_one();
        }
    };
    
    // Barrier synchronization
    class Barrier {
    private:
        std::mutex mutex_;
        std::condition_variable condition_;
        size_t count_;
        size_t waiting_;
        size_t generation_;
        
    public:
        explicit Barrier(size_t count) : count_(count), waiting_(0), generation_(0) {}
        
        void wait() {
            std::unique_lock<std::mutex> lock(mutex_);
            size_t gen = generation_;
            
            if (++waiting_ == count_) {
                waiting_ = 0;
                ++generation_;
                condition_.notify_all();
            } else {
                condition_.wait(lock, [this, gen] { return gen != generation_; });
            }
        }
    };
    
    // Semaphore
    class Semaphore {
    private:
        std::mutex mutex_;
        std::condition_variable condition_;
        std::atomic<int> count_;
        
    public:
        explicit Semaphore(int initial_count) : count_(initial_count) {}
        
        void acquire() {
            std::unique_lock<std::mutex> lock(mutex_);
            condition_.wait(lock, [this] { return count_ > 0; });
            --count_;
        }
        
        void release() {
            std::lock_guard<std::mutex> lock(mutex_);
            ++count_;
            condition_.notify_one();
        }
        
        int count() const { return count_.load(); }
    };
    
    // Countdown latch
    class CountdownLatch {
    private:
        std::mutex mutex_;
        std::condition_variable condition_;
        std::atomic<int> count_;
        
    public:
        explicit CountdownLatch(int initial_count) : count_(initial_count) {}
        
        void countdown() {
            if (count_.fetch_sub(1) == 1) {
                condition_.notify_all();
            }
        }
        
        void wait() {
            std::unique_lock<std::mutex> lock(mutex_);
            condition_.wait(lock, [this] { return count_ == 0; });
        }
        
        int count() const { return count_.load(); }
    };
    
    void demonstrateAdvancedSynchronization() {
        std::cout << "\n=== Advanced Synchronization ===" << std::endl;
        
        // Barrier demonstration
        Barrier barrier(3);
        
        std::vector<std::thread> barrier_threads;
        for (int i = 0; i < 3; ++i) {
            barrier_threads.emplace_back([&barrier, i]() {
                std::cout << "Thread " << i << " reached barrier" << std::endl;
                barrier.wait();
                std::cout << "Thread " << i << " passed barrier" << std::endl;
            });
        }
        
        for (auto& t : barrier_threads) {
            t.join();
        }
        
        // Semaphore demonstration
        Semaphore semaphore(2);
        
        std::vector<std::thread> semaphore_threads;
        for (int i = 0; i < 5; ++i) {
            semaphore_threads.emplace_back([&semaphore, i]() {
                semaphore.acquire();
                std::cout << "Thread " << i << " acquired semaphore" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                semaphore.release();
                std::cout << "Thread " << i << " released semaphore" << std::endl;
            });
        }
        
        for (auto& t : semaphore_threads) {
            t.join();
        }
        
        // Countdown latch demonstration
        CountdownLatch latch(3);
        
        std::vector<std::thread> latch_threads;
        for (int i = 0; i < 3; ++i) {
            latch_threads.emplace_back([&latch, i]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(100 * (i + 1)));
                std::cout << "Thread " << i << " finished work" << std::endl;
                latch.countdown();
            });
        }
        
        std::thread waiter([&latch]() {
            std::cout << "Waiter thread waiting for all threads to finish" << std::endl;
            latch.wait();
            std::cout << "All threads finished!" << std::endl;
        });
        
        for (auto& t : latch_threads) {
            t.join();
        }
        waiter.join();
    }
}

// Example 5: Parallel Algorithms
namespace ParallelAlgorithms {
    
    // Parallel for loop
    template<typename Iterator, typename Function>
    void parallel_for(Iterator first, Iterator last, Function func, size_t num_threads = 0) {
        if (num_threads == 0) {
            num_threads = std::thread::hardware_concurrency();
        }
        
        const size_t total_size = std::distance(first, last);
        const size_t chunk_size = total_size / num_threads;
        
        std::vector<std::thread> threads;
        
        for (size_t i = 0; i < num_threads; ++i) {
            auto chunk_first = first + i * chunk_size;
            auto chunk_last = (i == num_threads - 1) ? last : chunk_first + chunk_size;
            
            threads.emplace_back([chunk_first, chunk_last, func]() {
                for (auto it = chunk_first; it != chunk_last; ++it) {
                    func(*it);
                }
            });
        }
        
        for (auto& t : threads) {
            t.join();
        }
    }
    
    // Parallel reduce
    template<typename Iterator, typename T, typename BinaryOp>
    T parallel_reduce(Iterator first, Iterator last, T init, BinaryOp op, size_t num_threads = 0) {
        if (num_threads == 0) {
            num_threads = std::thread::hardware_concurrency();
        }
        
        const size_t total_size = std::distance(first, last);
        const size_t chunk_size = total_size / num_threads;
        
        std::vector<std::future<T>> futures;
        
        for (size_t i = 0; i < num_threads; ++i) {
            auto chunk_first = first + i * chunk_size;
            auto chunk_last = (i == num_threads - 1) ? last : chunk_first + chunk_size;
            
            futures.emplace_back(std::async(std::launch::async, [chunk_first, chunk_last, init, op]() {
                T result = init;
                for (auto it = chunk_first; it != chunk_last; ++it) {
                    result = op(result, *it);
                }
                return result;
            }));
        }
        
        T final_result = init;
        for (auto& future : futures) {
            final_result = op(final_result, future.get());
        }
        
        return final_result;
    }
    
    // Parallel transform
    template<typename InputIterator, typename OutputIterator, typename UnaryOp>
    void parallel_transform(InputIterator first, InputIterator last, OutputIterator result, UnaryOp op, size_t num_threads = 0) {
        if (num_threads == 0) {
            num_threads = std::thread::hardware_concurrency();
        }
        
        const size_t total_size = std::distance(first, last);
        const size_t chunk_size = total_size / num_threads;
        
        std::vector<std::thread> threads;
        
        for (size_t i = 0; i < num_threads; ++i) {
            auto chunk_first = first + i * chunk_size;
            auto chunk_last = (i == num_threads - 1) ? last : chunk_first + chunk_size;
            auto chunk_result = result + i * chunk_size;
            
            threads.emplace_back([chunk_first, chunk_last, chunk_result, op]() {
                std::transform(chunk_first, chunk_last, chunk_result, op);
            });
        }
        
        for (auto& t : threads) {
            t.join();
        }
    }
    
    // Parallel sort
    template<typename Iterator>
    void parallel_sort(Iterator first, Iterator last, size_t num_threads = 0) {
        if (num_threads == 0) {
            num_threads = std::thread::hardware_concurrency();
        }
        
        const size_t total_size = std::distance(first, last);
        
        if (total_size < 1000 || num_threads == 1) {
            std::sort(first, last);
            return;
        }
        
        const size_t chunk_size = total_size / num_threads;
        
        std::vector<std::thread> threads;
        
        // Sort chunks in parallel
        for (size_t i = 0; i < num_threads; ++i) {
            auto chunk_first = first + i * chunk_size;
            auto chunk_last = (i == num_threads - 1) ? last : chunk_first + chunk_size;
            
            threads.emplace_back([chunk_first, chunk_last]() {
                std::sort(chunk_first, chunk_last);
            });
        }
        
        for (auto& t : threads) {
            t.join();
        }
        
        // Merge sorted chunks
        for (size_t i = 1; i < num_threads; ++i) {
            auto chunk_first = first + i * chunk_size;
            auto chunk_last = (i == num_threads - 1) ? last : chunk_first + chunk_size;
            
            std::inplace_merge(first, chunk_first, chunk_last);
        }
    }
    
    void demonstrateParallelAlgorithms() {
        std::cout << "\n=== Parallel Algorithms ===" << std::endl;
        
        const size_t size = 1000000;
        std::vector<int> data(size);
        
        // Fill with random data
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 1000);
        
        for (auto& elem : data) {
            elem = dis(gen);
        }
        
        // Parallel for
        auto start = std::chrono::high_resolution_clock::now();
        parallel_for(data.begin(), data.end(), [](int& x) { x *= 2; });
        auto end = std::chrono::high_resolution_clock::now();
        auto parallel_for_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Parallel for time: " << parallel_for_time.count() << " microseconds" << std::endl;
        
        // Parallel reduce
        start = std::chrono::high_resolution_clock::now();
        int sum = parallel_reduce(data.begin(), data.end(), 0, std::plus<int>());
        end = std::chrono::high_resolution_clock::now();
        auto parallel_reduce_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Parallel reduce time: " << parallel_reduce_time.count() << " microseconds" << std::endl;
        std::cout << "Sum: " << sum << std::endl;
        
        // Parallel transform
        std::vector<int> result(size);
        
        start = std::chrono::high_resolution_clock::now();
        parallel_transform(data.begin(), data.end(), result.begin(), [](int x) { return x * x; });
        end = std::chrono::high_resolution_clock::now();
        auto parallel_transform_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Parallel transform time: " << parallel_transform_time.count() << " microseconds" << std::endl;
        
        // Parallel sort
        std::vector<int> sort_data(data);
        
        start = std::chrono::high_resolution_clock::now();
        parallel_sort(sort_data.begin(), sort_data.end());
        end = std::chrono::high_resolution_clock::now();
        auto parallel_sort_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Parallel sort time: " << parallel_sort_time.count() << " microseconds" << std::endl;
        
        // Performance comparison
        std::vector<int> std_data(data);
        
        start = std::chrono::high_resolution_clock::now();
        std::sort(std_data.begin(), std_data.end());
        end = std::chrono::high_resolution_clock::now();
        auto std_sort_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Standard sort time: " << std_sort_time.count() << " microseconds" << std::endl;
        std::cout << "Parallel sort speedup: " << (double)std_sort_time.count() / parallel_sort_time.count() << "x" << std::endl;
    }
}

int main() {
    std::cout << "=== Advanced Concurrency Demonstration ===" << std::endl;
    std::cout << "This program demonstrates advanced concurrency concepts, thread pools,\n"
              << "async programming, and concurrent data structures.\n" << std::endl;
    
    // Demonstrate various advanced concurrency concepts
    ThreadPool::demonstrateThreadPool();
    AdvancedAsync::demonstrateAdvancedAsync();
    ConcurrentDataStructures::demonstrateConcurrentDataStructures();
    AdvancedSynchronization::demonstrateAdvancedSynchronization();
    ParallelAlgorithms::demonstrateParallelAlgorithms();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Thread pools provide efficient task execution and resource management" << std::endl;
    std::cout << "2. Advanced async programming enables complex asynchronous operations" << std::endl;
    std::cout << "3. Concurrent data structures ensure thread-safe access to shared data" << std::endl;
    std::cout << "4. Advanced synchronization primitives solve complex coordination problems" << std::endl;
    std::cout << "5. Parallel algorithms can significantly improve performance for large datasets" << std::endl;
    std::cout << "6. Lock-free data structures eliminate contention and improve scalability" << std::endl;
    std::cout << "7. Proper synchronization is crucial for correct concurrent program behavior" << std::endl;
    std::cout << "8. Performance optimization requires careful consideration of thread overhead" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -pthread -o advanced_concurrency 01_Advanced_Concurrency.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -pthread -o advanced_concurrency 01_Advanced_Concurrency.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 01_Advanced_Concurrency.cpp
 * 
 * Running:
 * ./advanced_concurrency (Linux/macOS)
 * advanced_concurrency.exe (Windows)
 * 
 * Note: This lesson requires C++17 or later for some features.
 * C++20 is recommended for best concurrency support.
 * 
 * Advanced Concurrency Notes:
 * - Thread pools provide efficient task execution and resource management
 * - Advanced async programming enables complex asynchronous operations
 * - Concurrent data structures ensure thread-safe access to shared data
 * - Advanced synchronization primitives solve complex coordination problems
 * - Parallel algorithms can significantly improve performance for large datasets
 * - Lock-free data structures eliminate contention and improve scalability
 * - Proper synchronization is crucial for correct concurrent program behavior
 * - Performance optimization requires careful consideration of thread overhead
 */"""
