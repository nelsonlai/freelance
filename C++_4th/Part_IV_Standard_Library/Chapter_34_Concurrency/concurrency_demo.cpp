#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <future>
#include <vector>
#include <queue>
#include <chrono>
#include <random>
#include <functional>

// Demonstrates C++ concurrency features
int main() {
    std::cout << "C++ Concurrency Demonstration" << std::endl;
    std::cout << "=============================" << std::endl;
    
    // 1. Basic thread management
    std::cout << "\n1. BASIC THREAD MANAGEMENT:" << std::endl;
    
    auto worker_function = [](int id) {
        std::cout << "Thread " << id << " started" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "Thread " << id << " finished" << std::endl;
    };
    
    std::vector<std::thread> threads;
    
    // Create multiple threads
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back(worker_function, i);
    }
    
    // Wait for all threads to complete
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "All threads completed" << std::endl;
    
    // 2. Thread synchronization with mutex
    std::cout << "\n2. THREAD SYNCHRONIZATION WITH MUTEX:" << std::endl;
    
    std::mutex mtx;
    int shared_counter = 0;
    
    auto increment_function = [&mtx, &shared_counter](int id, int iterations) {
        for (int i = 0; i < iterations; ++i) {
            std::lock_guard<std::mutex> lock(mtx);
            int old_value = shared_counter;
            std::this_thread::sleep_for(std::chrono::microseconds(1));
            shared_counter = old_value + 1;
        }
    };
    
    std::vector<std::thread> sync_threads;
    
    for (int i = 0; i < 4; ++i) {
        sync_threads.emplace_back(increment_function, i, 1000);
    }
    
    for (auto& t : sync_threads) {
        t.join();
    }
    
    std::cout << "Shared counter value: " << shared_counter << std::endl;
    
    // 3. Atomic operations
    std::cout << "\n3. ATOMIC OPERATIONS:" << std::endl;
    
    std::atomic<int> atomic_counter(0);
    
    auto atomic_increment = [&atomic_counter](int iterations) {
        for (int i = 0; i < iterations; ++i) {
            atomic_counter.fetch_add(1);
        }
    };
    
    std::vector<std::thread> atomic_threads;
    
    for (int i = 0; i < 4; ++i) {
        atomic_threads.emplace_back(atomic_increment, 1000);
    }
    
    for (auto& t : atomic_threads) {
        t.join();
    }
    
    std::cout << "Atomic counter value: " << atomic_counter.load() << std::endl;
    
    // 4. Condition variables
    std::cout << "\n4. CONDITION VARIABLES:" << std::endl;
    
    std::mutex cv_mtx;
    std::condition_variable cv;
    bool ready = false;
    std::queue<int> work_queue;
    
    // Producer thread
    auto producer = [&cv_mtx, &cv, &ready, &work_queue]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        {
            std::lock_guard<std::mutex> lock(cv_mtx);
            for (int i = 0; i < 5; ++i) {
                work_queue.push(i);
            }
            ready = true;
        }
        
        cv.notify_one();
        std::cout << "Producer finished" << std::endl;
    };
    
    // Consumer thread
    auto consumer = [&cv_mtx, &cv, &ready, &work_queue]() {
        std::unique_lock<std::mutex> lock(cv_mtx);
        cv.wait(lock, [&ready] { return ready; });
        
        std::cout << "Consumer processing: ";
        while (!work_queue.empty()) {
            std::cout << work_queue.front() << " ";
            work_queue.pop();
        }
        std::cout << std::endl;
    };
    
    std::thread producer_thread(producer);
    std::thread consumer_thread(consumer);
    
    producer_thread.join();
    consumer_thread.join();
    
    // 5. Async programming with futures
    std::cout << "\n5. ASYNC PROGRAMMING WITH FUTURES:" << std::endl;
    
    auto compute_function = [](int n) -> int {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return n * n;
    };
    
    // Launch async tasks
    std::vector<std::future<int>> futures;
    
    for (int i = 1; i <= 5; ++i) {
        futures.push_back(std::async(std::launch::async, compute_function, i));
    }
    
    // Collect results
    std::cout << "Async results: ";
    for (auto& future : futures) {
        std::cout << future.get() << " ";
    }
    std::cout << std::endl;
    
    // 6. Promises and futures
    std::cout << "\n6. PROMISES AND FUTURES:" << std::endl;
    
    std::promise<int> promise;
    std::future<int> future = promise.get_future();
    
    auto promise_worker = [&promise]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        promise.set_value(42);
    };
    
    std::thread promise_thread(promise_worker);
    
    std::cout << "Waiting for promise result..." << std::endl;
    int result = future.get();
    std::cout << "Promise result: " << result << std::endl;
    
    promise_thread.join();
    
    // 7. Thread-safe container
    std::cout << "\n7. THREAD-SAFE CONTAINER:" << std::endl;
    
    class ThreadSafeQueue {
    private:
        std::queue<int> queue_;
        mutable std::mutex mtx_;
        std::condition_variable cv_;
        
    public:
        void push(int value) {
            std::lock_guard<std::mutex> lock(mtx_);
            queue_.push(value);
            cv_.notify_one();
        }
        
        bool try_pop(int& value) {
            std::lock_guard<std::mutex> lock(mtx_);
            if (queue_.empty()) {
                return false;
            }
            value = queue_.front();
            queue_.pop();
            return true;
        }
        
        void wait_and_pop(int& value) {
            std::unique_lock<std::mutex> lock(mtx_);
            cv_.wait(lock, [this] { return !queue_.empty(); });
            value = queue_.front();
            queue_.pop();
        }
        
        bool empty() const {
            std::lock_guard<std::mutex> lock(mtx_);
            return queue_.empty();
        }
    };
    
    ThreadSafeQueue ts_queue;
    
    // Producer
    auto producer_ts = [&ts_queue]() {
        for (int i = 0; i < 5; ++i) {
            ts_queue.push(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    };
    
    // Consumer
    auto consumer_ts = [&ts_queue]() {
        int value;
        for (int i = 0; i < 5; ++i) {
            ts_queue.wait_and_pop(value);
            std::cout << "Consumed: " << value << std::endl;
        }
    };
    
    std::thread producer_ts_thread(producer_ts);
    std::thread consumer_ts_thread(consumer_ts);
    
    producer_ts_thread.join();
    consumer_ts_thread.join();
    
    // 8. Thread pool simulation
    std::cout << "\n8. THREAD POOL SIMULATION:" << std::endl;
    
    class SimpleThreadPool {
    private:
        std::vector<std::thread> workers_;
        std::queue<std::function<void()>> tasks_;
        std::mutex queue_mutex_;
        std::condition_variable condition_;
        bool stop_;
        
    public:
        SimpleThreadPool(size_t num_threads) : stop_(false) {
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
                            
                            task = tasks_.front();
                            tasks_.pop();
                        }
                        
                        task();
                    }
                });
            }
        }
        
        ~SimpleThreadPool() {
            {
                std::unique_lock<std::mutex> lock(queue_mutex_);
                stop_ = true;
            }
            
            condition_.notify_all();
            
            for (std::thread& worker : workers_) {
                worker.join();
            }
        }
        
        template<typename F>
        void enqueue(F&& f) {
            {
                std::unique_lock<std::mutex> lock(queue_mutex_);
                tasks_.emplace(std::forward<F>(f));
            }
            condition_.notify_one();
        }
    };
    
    SimpleThreadPool pool(4);
    
    // Submit tasks to thread pool
    for (int i = 0; i < 8; ++i) {
        pool.enqueue([i]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cout << "Task " << i << " completed by thread " 
                      << std::this_thread::get_id() << std::endl;
        });
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
    // 9. Memory ordering with atomics
    std::cout << "\n9. MEMORY ORDERING WITH ATOMICS:" << std::endl;
    
    std::atomic<int> data(0);
    std::atomic<bool> ready_flag(false);
    
    auto writer = [&data, &ready_flag]() {
        data.store(42, std::memory_order_relaxed);
        ready_flag.store(true, std::memory_order_release);
    };
    
    auto reader = [&data, &ready_flag]() {
        while (!ready_flag.load(std::memory_order_acquire)) {
            std::this_thread::yield();
        }
        std::cout << "Data value: " << data.load(std::memory_order_relaxed) << std::endl;
    };
    
    std::thread writer_thread(writer);
    std::thread reader_thread(reader);
    
    writer_thread.join();
    reader_thread.join();
    
    // 10. Performance comparison
    std::cout << "\n10. PERFORMANCE COMPARISON:" << std::endl;
    
    const int num_iterations = 1000000;
    
    // Sequential execution
    auto start = std::chrono::high_resolution_clock::now();
    
    int sequential_sum = 0;
    for (int i = 0; i < num_iterations; ++i) {
        sequential_sum += i;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto sequential_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Sequential execution time: " << sequential_time.count() << " ms" << std::endl;
    std::cout << "Sequential sum: " << sequential_sum << std::endl;
    
    // Parallel execution
    start = std::chrono::high_resolution_clock::now();
    
    std::atomic<int> parallel_sum(0);
    const int num_threads = 4;
    const int chunk_size = num_iterations / num_threads;
    
    std::vector<std::thread> parallel_threads;
    
    for (int t = 0; t < num_threads; ++t) {
        int start_idx = t * chunk_size;
        int end_idx = (t == num_threads - 1) ? num_iterations : (t + 1) * chunk_size;
        
        parallel_threads.emplace_back([&parallel_sum, start_idx, end_idx]() {
            int local_sum = 0;
            for (int i = start_idx; i < end_idx; ++i) {
                local_sum += i;
            }
            parallel_sum.fetch_add(local_sum);
        });
    }
    
    for (auto& t : parallel_threads) {
        t.join();
    }
    
    end = std::chrono::high_resolution_clock::now();
    auto parallel_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Parallel execution time: " << parallel_time.count() << " ms" << std::endl;
    std::cout << "Parallel sum: " << parallel_sum.load() << std::endl;
    
    std::cout << "\nConcurrency demonstration completed!" << std::endl;
    return 0;
}
