#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <atomic>

// Thread pool implementation for advanced concurrency
class ThreadPool {
public:
    ThreadPool(size_t num_threads = std::thread::hardware_concurrency());
    ~ThreadPool();
    
    // Add task to the pool
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) 
        -> std::future<typename std::result_of<F(Args...)>::type>;
    
    // Get number of threads
    size_t size() const { return workers_.size(); }
    
    // Check if pool is stopped
    bool is_stopped() const { return stop_; }
    
    // Wait for all tasks to complete
    void wait_for_all();
    
    // Shutdown the pool
    void shutdown();

private:
    // Worker threads
    std::vector<std::thread> workers_;
    
    // Task queue
    std::queue<std::function<void()>> tasks_;
    
    // Synchronization
    mutable std::mutex queue_mutex_;
    std::condition_variable condition_;
    std::atomic<bool> stop_;
    
    // Task counter
    std::atomic<int> active_tasks_;
    std::condition_variable finished_condition_;
};

// Constructor
inline ThreadPool::ThreadPool(size_t num_threads) 
    : stop_(false), active_tasks_(0) {
    
    // Create worker threads
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
                
                active_tasks_.fetch_add(1);
                task();
                active_tasks_.fetch_sub(1);
                
                finished_condition_.notify_all();
            }
        });
    }
}

// Destructor
inline ThreadPool::~ThreadPool() {
    shutdown();
}

// Add task to the pool
template<class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args) 
    -> std::future<typename std::result_of<F(Args...)>::type> {
    
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
        
        tasks_.emplace([task] { (*task)(); });
    }
    
    condition_.notify_one();
    return result;
}

// Wait for all tasks to complete
inline void ThreadPool::wait_for_all() {
    std::unique_lock<std::mutex> lock(queue_mutex_);
    finished_condition_.wait(lock, [this] { 
        return tasks_.empty() && active_tasks_.load() == 0; 
    });
}

// Shutdown the pool
inline void ThreadPool::shutdown() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        stop_ = true;
    }
    
    condition_.notify_all();
    
    for (std::thread& worker : workers_) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

#endif // THREAD_POOL_H
