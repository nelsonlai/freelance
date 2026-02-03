#ifndef MINI_STL_THREAD_POOL_H
#define MINI_STL_THREAD_POOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <type_traits>

namespace mini_stl {

// Thread pool implementation
class ThreadPool {
public:
    // Constructor
    explicit ThreadPool(size_t threads = std::thread::hardware_concurrency());
    
    // Destructor
    ~ThreadPool();
    
    // Add task to the queue
    template<typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) 
        -> std::future<typename std::result_of<F(Args...)>::type>;
    
    // Get the number of worker threads
    size_t size() const { return workers_.size(); }
    
    // Check if the pool is empty (no active tasks)
    bool empty() const;
    
    // Wait for all tasks to complete
    void wait();
    
    // Stop the thread pool
    void stop();
    
    // Restart the thread pool
    void restart(size_t threads = std::thread::hardware_concurrency());

private:
    // Worker threads
    std::vector<std::thread> workers_;
    
    // Task queue
    std::queue<std::function<void()>> tasks_;
    
    // Synchronization
    mutable std::mutex queue_mutex_;
    std::condition_variable condition_;
    std::condition_variable finished_;
    
    // State
    bool stop_;
    std::atomic<size_t> active_tasks_;
    
    // Worker function
    void worker();
};

// Constructor
inline ThreadPool::ThreadPool(size_t threads) 
    : stop_(false), active_tasks_(0) {
    restart(threads);
}

// Destructor
inline ThreadPool::~ThreadPool() {
    stop();
}

// Worker function
inline void ThreadPool::worker() {
    while (true) {
        std::function<void()> task;
        
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            
            // Wait for task or stop signal
            condition_.wait(lock, [this] { 
                return stop_ || !tasks_.empty(); 
            });
            
            // If stopped and no tasks, exit
            if (stop_ && tasks_.empty()) {
                return;
            }
            
            // Get task from queue
            task = std::move(tasks_.front());
            tasks_.pop();
            ++active_tasks_;
        }
        
        // Execute task
        try {
            task();
        } catch (...) {
            // Handle exceptions in tasks
        }
        
        {
            std::lock_guard<std::mutex> lock(queue_mutex_);
            --active_tasks_;
            
            // Notify if no active tasks
            if (active_tasks_ == 0 && tasks_.empty()) {
                finished_.notify_all();
            }
        }
    }
}

// Add task to the queue
template<typename F, typename... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args) 
    -> std::future<typename std::result_of<F(Args...)>::type> {
    
    using return_type = typename std::result_of<F(Args...)>::type;
    
    // Create packaged task
    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );
    
    // Get future
    std::future<return_type> result = task->get_future();
    
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        
        // Don't allow enqueueing after stopping the pool
        if (stop_) {
            throw std::runtime_error("enqueue on stopped ThreadPool");
        }
        
        // Add task to queue
        tasks_.emplace([task]() { (*task)(); });
    }
    
    // Notify one worker
    condition_.notify_one();
    
    return result;
}

// Check if the pool is empty
inline bool ThreadPool::empty() const {
    std::lock_guard<std::mutex> lock(queue_mutex_);
    return tasks_.empty() && active_tasks_ == 0;
}

// Wait for all tasks to complete
inline void ThreadPool::wait() {
    std::unique_lock<std::mutex> lock(queue_mutex_);
    finished_.wait(lock, [this] { 
        return tasks_.empty() && active_tasks_ == 0; 
    });
}

// Stop the thread pool
inline void ThreadPool::stop() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        stop_ = true;
    }
    
    // Notify all workers
    condition_.notify_all();
    
    // Join all worker threads
    for (std::thread& worker : workers_) {
        if (worker.joinable()) {
            worker.join();
        }
    }
    
    workers_.clear();
}

// Restart the thread pool
inline void ThreadPool::restart(size_t threads) {
    stop();
    
    stop_ = false;
    active_tasks_ = 0;
    
    // Create worker threads
    for (size_t i = 0; i < threads; ++i) {
        workers_.emplace_back([this] { worker(); });
    }
}

// Async task executor
template<typename F, typename... Args>
auto async(F&& f, Args&&... args) 
    -> std::future<typename std::result_of<F(Args...)>::type> {
    
    static ThreadPool pool;
    return pool.enqueue(std::forward<F>(f), std::forward<Args>(args)...);
}

// Parallel for implementation
template<typename Iterator, typename Function>
void parallel_for(Iterator first, Iterator last, Function func, 
                  size_t num_threads = std::thread::hardware_concurrency()) {
    
    if (first == last) return;
    
    ThreadPool pool(num_threads);
    auto distance = std::distance(first, last);
    
    if (distance == 1) {
        func(*first);
        return;
    }
    
    // Divide work among threads
    size_t chunk_size = (distance + num_threads - 1) / num_threads;
    std::vector<std::future<void>> futures;
    
    for (size_t i = 0; i < num_threads; ++i) {
        auto start = std::next(first, i * chunk_size);
        auto end = std::next(first, std::min((i + 1) * chunk_size, static_cast<size_t>(distance)));
        
        if (start != end) {
            futures.push_back(pool.enqueue([start, end, func]() {
                for (auto it = start; it != end; ++it) {
                    func(*it);
                }
            }));
        }
    }
    
    // Wait for all tasks to complete
    for (auto& future : futures) {
        future.wait();
    }
}

// Parallel transform implementation
template<typename InputIterator, typename OutputIterator, typename Function>
void parallel_transform(InputIterator first, InputIterator last, 
                       OutputIterator result, Function func,
                       size_t num_threads = std::thread::hardware_concurrency()) {
    
    if (first == last) return;
    
    ThreadPool pool(num_threads);
    auto distance = std::distance(first, last);
    
    if (distance == 1) {
        *result = func(*first);
        return;
    }
    
    // Divide work among threads
    size_t chunk_size = (distance + num_threads - 1) / num_threads;
    std::vector<std::future<void>> futures;
    
    for (size_t i = 0; i < num_threads; ++i) {
        auto start = std::next(first, i * chunk_size);
        auto end = std::next(first, std::min((i + 1) * chunk_size, static_cast<size_t>(distance)));
        auto result_start = std::next(result, i * chunk_size);
        
        if (start != end) {
            futures.push_back(pool.enqueue([start, end, result_start, func]() {
                auto it = start;
                auto result_it = result_start;
                while (it != end) {
                    *result_it = func(*it);
                    ++it;
                    ++result_it;
                }
            }));
        }
    }
    
    // Wait for all tasks to complete
    for (auto& future : futures) {
        future.wait();
    }
}

// Parallel reduce implementation
template<typename Iterator, typename T, typename BinaryOperation>
T parallel_reduce(Iterator first, Iterator last, T init, BinaryOperation op,
                  size_t num_threads = std::thread::hardware_concurrency()) {
    
    if (first == last) return init;
    
    ThreadPool pool(num_threads);
    auto distance = std::distance(first, last);
    
    if (distance == 1) {
        return op(init, *first);
    }
    
    // Divide work among threads
    size_t chunk_size = (distance + num_threads - 1) / num_threads;
    std::vector<std::future<T>> futures;
    
    for (size_t i = 0; i < num_threads; ++i) {
        auto start = std::next(first, i * chunk_size);
        auto end = std::next(first, std::min((i + 1) * chunk_size, static_cast<size_t>(distance)));
        
        if (start != end) {
            futures.push_back(pool.enqueue([start, end, op]() -> T {
                T result = T{};
                auto it = start;
                if (it != end) {
                    result = *it;
                    ++it;
                }
                while (it != end) {
                    result = op(result, *it);
                    ++it;
                }
                return result;
            }));
        }
    }
    
    // Combine results
    T result = init;
    for (auto& future : futures) {
        result = op(result, future.get());
    }
    
    return result;
}

// Barrier synchronization primitive
class Barrier {
public:
    explicit Barrier(size_t count) : count_(count), current_(0), generation_(0) {}
    
    void wait() {
        std::unique_lock<std::mutex> lock(mutex_);
        auto gen = generation_;
        ++current_;
        
        if (current_ == count_) {
            ++generation_;
            current_ = 0;
            condition_.notify_all();
        } else {
            condition_.wait(lock, [this, gen] { return gen != generation_; });
        }
    }
    
private:
    std::mutex mutex_;
    std::condition_variable condition_;
    size_t count_;
    size_t current_;
    size_t generation_;
};

// Semaphore synchronization primitive
class Semaphore {
public:
    explicit Semaphore(size_t count = 0) : count_(count) {}
    
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
    
    bool try_acquire() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (count_ > 0) {
            --count_;
            return true;
        }
        return false;
    }
    
private:
    std::mutex mutex_;
    std::condition_variable condition_;
    size_t count_;
};

} // namespace mini_stl

#endif // MINI_STL_THREAD_POOL_H
