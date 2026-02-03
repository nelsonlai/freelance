#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <future>
#include <thread>
#include "thread_pool.h"
#include "lock_free_queue.h"

// Demonstrates advanced projects for Part IV
int main() {
    std::cout << "Advanced Projects Demonstration" << std::endl;
    std::cout << "===============================" << std::endl;
    
    // 1. Thread Pool demonstration
    std::cout << "\n1. THREAD POOL DEMONSTRATION:" << std::endl;
    
    ThreadPool pool(4);
    
    std::cout << "Thread pool created with " << pool.size() << " threads" << std::endl;
    
    // Submit tasks to thread pool
    std::vector<std::future<int>> futures;
    
    for (int i = 0; i < 10; ++i) {
        auto future = pool.enqueue([i]() -> int {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::cout << "Task " << i << " completed by thread " 
                      << std::this_thread::get_id() << std::endl;
            return i * i;
        });
        futures.push_back(std::move(future));
    }
    
    // Collect results
    std::cout << "Results: ";
    for (auto& future : futures) {
        std::cout << future.get() << " ";
    }
    std::cout << std::endl;
    
    // 2. Lock-free queue demonstration
    std::cout << "\n2. LOCK-FREE QUEUE DEMONSTRATION:" << std::endl;
    
    LockFreeQueue<int> lf_queue;
    
    // Producer thread
    auto producer = [&lf_queue]() {
        for (int i = 0; i < 5; ++i) {
            lf_queue.enqueue(i);
            std::cout << "Produced: " << i << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    };
    
    // Consumer thread
    auto consumer = [&lf_queue]() {
        int value;
        for (int i = 0; i < 5; ++i) {
            if (lf_queue.dequeue(value)) {
                std::cout << "Consumed: " << value << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(75));
        }
    };
    
    std::thread producer_thread(producer);
    std::thread consumer_thread(consumer);
    
    producer_thread.join();
    consumer_thread.join();
    
    // 3. Performance comparison
    std::cout << "\n3. PERFORMANCE COMPARISON:" << std::endl;
    
    const int num_tasks = 1000;
    const int task_size = 1000;
    
    // Sequential execution
    auto start = std::chrono::high_resolution_clock::now();
    
    std::vector<int> sequential_result;
    for (int i = 0; i < num_tasks; ++i) {
        int sum = 0;
        for (int j = 0; j < task_size; ++j) {
            sum += j;
        }
        sequential_result.push_back(sum);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto sequential_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Sequential execution time: " << sequential_time.count() << " ms" << std::endl;
    
    // Parallel execution with thread pool
    start = std::chrono::high_resolution_clock::now();
    
    std::vector<std::future<int>> parallel_futures;
    for (int i = 0; i < num_tasks; ++i) {
        auto future = pool.enqueue([task_size]() -> int {
            int sum = 0;
            for (int j = 0; j < task_size; ++j) {
                sum += j;
            }
            return sum;
        });
        parallel_futures.push_back(std::move(future));
    }
    
    std::vector<int> parallel_result;
    for (auto& future : parallel_futures) {
        parallel_result.push_back(future.get());
    }
    
    end = std::chrono::high_resolution_clock::now();
    auto parallel_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Parallel execution time: " << parallel_time.count() << " ms" << std::endl;
    std::cout << "Speedup: " << (double)sequential_time.count() / parallel_time.count() << "x" << std::endl;
    
    // 4. Matrix multiplication with thread pool
    std::cout << "\n4. MATRIX MULTIPLICATION WITH THREAD POOL:" << std::endl;
    
    const int matrix_size = 500;
    
    // Create matrices
    std::vector<std::vector<double>> matrix_a(matrix_size, std::vector<double>(matrix_size));
    std::vector<std::vector<double>> matrix_b(matrix_size, std::vector<double>(matrix_size));
    std::vector<std::vector<double>> matrix_c(matrix_size, std::vector<double>(matrix_size));
    
    // Fill matrices with random values
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    
    for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
            matrix_a[i][j] = dis(gen);
            matrix_b[i][j] = dis(gen);
        }
    }
    
    // Parallel matrix multiplication
    start = std::chrono::high_resolution_clock::now();
    
    std::vector<std::future<void>> matrix_futures;
    const int num_threads = pool.size();
    const int rows_per_thread = matrix_size / num_threads;
    
    for (int t = 0; t < num_threads; ++t) {
        int start_row = t * rows_per_thread;
        int end_row = (t == num_threads - 1) ? matrix_size : (t + 1) * rows_per_thread;
        
        auto future = pool.enqueue([&matrix_a, &matrix_b, &matrix_c, start_row, end_row, matrix_size]() {
            for (int i = start_row; i < end_row; ++i) {
                for (int j = 0; j < matrix_size; ++j) {
                    double sum = 0.0;
                    for (int k = 0; k < matrix_size; ++k) {
                        sum += matrix_a[i][k] * matrix_b[k][j];
                    }
                    matrix_c[i][j] = sum;
                }
            }
        });
        matrix_futures.push_back(std::move(future));
    }
    
    // Wait for completion
    for (auto& future : matrix_futures) {
        future.get();
    }
    
    end = std::chrono::high_resolution_clock::now();
    auto matrix_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Matrix multiplication (" << matrix_size << "x" << matrix_size 
              << ") time: " << matrix_time.count() << " ms" << std::endl;
    
    // 5. Producer-consumer with lock-free queue
    std::cout << "\n5. PRODUCER-CONSUMER WITH LOCK-FREE QUEUE:" << std::endl;
    
    LockFreeQueue<std::string> message_queue;
    std::atomic<bool> stop_production(false);
    
    // Multiple producers
    auto producer_func = [&message_queue, &stop_production](int producer_id) {
        for (int i = 0; i < 10; ++i) {
            if (stop_production.load()) break;
            
            std::string message = "Producer " + std::to_string(producer_id) + 
                                 " message " + std::to_string(i);
            message_queue.enqueue(message);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    };
    
    // Consumer
    auto consumer_func = [&message_queue]() {
        std::string message;
        int count = 0;
        while (count < 30) {  // Expect 30 messages total
            if (message_queue.dequeue(message)) {
                std::cout << "Consumed: " << message << std::endl;
                count++;
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }
    };
    
    // Start producers and consumer
    std::vector<std::thread> producer_threads;
    for (int i = 0; i < 3; ++i) {
        producer_threads.emplace_back(producer_func, i);
    }
    
    std::thread consumer_thread(consumer_func);
    
    // Wait for producers to finish
    for (auto& t : producer_threads) {
        t.join();
    }
    
    // Stop production and wait for consumer
    stop_production.store(true);
    consumer_thread.join();
    
    // 6. Task scheduling with priorities
    std::cout << "\n6. TASK SCHEDULING WITH PRIORITIES:" << std::endl;
    
    struct Task {
        int priority;
        std::string name;
        std::function<void()> function;
        
        Task(int p, const std::string& n, std::function<void()> f) 
            : priority(p), name(n), function(f) {}
        
        bool operator<(const Task& other) const {
            return priority > other.priority;  // Higher priority first
        }
    };
    
    std::priority_queue<Task> task_queue;
    
    // Add tasks with different priorities
    task_queue.emplace(1, "Low priority task", []() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "Low priority task completed" << std::endl;
    });
    
    task_queue.emplace(3, "High priority task", []() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "High priority task completed" << std::endl;
    });
    
    task_queue.emplace(2, "Medium priority task", []() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "Medium priority task completed" << std::endl;
    });
    
    // Execute tasks in priority order
    std::vector<std::future<void>> priority_futures;
    while (!task_queue.empty()) {
        Task task = task_queue.top();
        task_queue.pop();
        
        auto future = pool.enqueue([task]() {
            std::cout << "Executing: " << task.name << std::endl;
            task.function();
        });
        priority_futures.push_back(std::move(future));
    }
    
    // Wait for all tasks to complete
    for (auto& future : priority_futures) {
        future.get();
    }
    
    // 7. Memory pool demonstration
    std::cout << "\n7. MEMORY POOL DEMONSTRATION:" << std::endl;
    
    class MemoryPool {
    private:
        struct Block {
            Block* next;
            bool in_use;
        };
        
        std::vector<std::unique_ptr<char[]>> memory_blocks_;
        Block* free_list_;
        std::mutex mutex_;
        size_t block_size_;
        size_t num_blocks_;
        
    public:
        MemoryPool(size_t block_size, size_t num_blocks) 
            : block_size_(block_size), num_blocks_(num_blocks), free_list_(nullptr) {
            
            // Allocate memory blocks
            for (size_t i = 0; i < num_blocks; ++i) {
                memory_blocks_.push_back(std::make_unique<char[]>(block_size_));
                Block* block = reinterpret_cast<Block*>(memory_blocks_.back().get());
                block->next = free_list_;
                block->in_use = false;
                free_list_ = block;
            }
        }
        
        void* allocate() {
            std::lock_guard<std::mutex> lock(mutex_);
            
            if (free_list_ == nullptr) {
                return nullptr;  // Pool exhausted
            }
            
            Block* block = free_list_;
            free_list_ = block->next;
            block->in_use = true;
            
            return reinterpret_cast<void*>(block);
        }
        
        void deallocate(void* ptr) {
            if (ptr == nullptr) return;
            
            std::lock_guard<std::mutex> lock(mutex_);
            
            Block* block = reinterpret_cast<Block*>(ptr);
            block->in_use = false;
            block->next = free_list_;
            free_list_ = block;
        }
    };
    
    MemoryPool pool_mem(sizeof(int), 100);
    
    // Test memory pool
    std::vector<void*> allocated_ptrs;
    
    // Allocate some memory
    for (int i = 0; i < 10; ++i) {
        void* ptr = pool_mem.allocate();
        if (ptr != nullptr) {
            *static_cast<int*>(ptr) = i;
            allocated_ptrs.push_back(ptr);
        }
    }
    
    std::cout << "Allocated " << allocated_ptrs.size() << " blocks from memory pool" << std::endl;
    
    // Deallocate memory
    for (void* ptr : allocated_ptrs) {
        pool_mem.deallocate(ptr);
    }
    
    std::cout << "Deallocated all blocks back to memory pool" << std::endl;
    
    // 8. Shutdown thread pool
    std::cout << "\n8. SHUTDOWN THREAD POOL:" << std::endl;
    
    pool.shutdown();
    std::cout << "Thread pool shutdown completed" << std::endl;
    
    std::cout << "\nAdvanced projects demonstration completed!" << std::endl;
    return 0;
}
