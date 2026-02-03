#include <iostream>
#include <thread>
#include <atomic>
#include <future>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <chrono>
#include <random>

// Demonstrates advanced concurrency features
int main() {
    std::cout << "Advanced Concurrency Demonstration" << std::endl;
    std::cout << "===================================" << std::endl;
    
    // 1. Atomic Operations
    std::cout << "\n1. ATOMIC OPERATIONS:" << std::endl;
    
    std::atomic<int> atomic_counter(0);
    std::atomic<bool> atomic_flag(false);
    
    // Atomic operations
    atomic_counter.store(42);
    std::cout << "  Atomic counter stored: " << atomic_counter.load() << std::endl;
    
    int old_value = atomic_counter.exchange(100);
    std::cout << "  Atomic exchange: old=" << old_value << ", new=" << atomic_counter.load() << std::endl;
    
    bool expected = false;
    bool success = atomic_flag.compare_exchange_weak(expected, true);
    std::cout << "  Compare exchange: success=" << success << ", expected=" << expected << std::endl;
    
    // Atomic arithmetic
    int fetched = atomic_counter.fetch_add(10);
    std::cout << "  Fetch add: fetched=" << fetched << ", new=" << atomic_counter.load() << std::endl;
    
    // 2. Memory Ordering
    std::cout << "\n2. MEMORY ORDERING:" << std::endl;
    
    std::atomic<int> data(0);
    std::atomic<bool> ready(false);
    
    // Producer thread
    std::thread producer([&]() {
        data.store(42, std::memory_order_relaxed);
        ready.store(true, std::memory_order_release);
    });
    
    // Consumer thread
    std::thread consumer([&]() {
        while (!ready.load(std::memory_order_acquire)) {
            std::this_thread::yield();
        }
        int value = data.load(std::memory_order_relaxed);
        std::cout << "  Memory ordering: data=" << value << std::endl;
    });
    
    producer.join();
    consumer.join();
    
    // 3. Futures and Promises
    std::cout << "\n3. FUTURES AND PROMISES:" << std::endl;
    
    // Promise/Future
    std::promise<int> promise;
    std::future<int> future = promise.get_future();
    
    std::thread promise_thread([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        promise.set_value(42);
    });
    
    std::cout << "  Future result: " << future.get() << std::endl;
    promise_thread.join();
    
    // Packaged task
    std::packaged_task<int(int, int)> task([](int a, int b) { return a + b; });
    std::future<int> task_future = task.get_future();
    
    std::thread task_thread(std::move(task), 10, 20);
    std::cout << "  Packaged task result: " << task_future.get() << std::endl;
    task_thread.join();
    
    // Async
    auto async_future = std::async(std::launch::async, [](int x) { return x * x; }, 5);
    std::cout << "  Async result: " << async_future.get() << std::endl;
    
    // 4. Thread Pool Implementation
    std::cout << "\n4. THREAD POOL IMPLEMENTATION:" << std::endl;
    
    class ThreadPool {
    private:
        std::vector<std::thread> workers;
        std::queue<std::function<void()>> tasks;
        std::mutex queue_mutex;
        std::condition_variable condition;
        bool stop;
        
    public:
        ThreadPool(size_t threads) : stop(false) {
            for (size_t i = 0; i < threads; ++i) {
                workers.emplace_back([this] {
                    while (true) {
                        std::function<void()> task;
                        
                        {
                            std::unique_lock<std::mutex> lock(queue_mutex);
                            condition.wait(lock, [this] { return stop || !tasks.empty(); });
                            
                            if (stop && tasks.empty()) return;
                            
                            task = std::move(tasks.front());
                            tasks.pop();
                        }
                        
                        task();
                    }
                });
            }
        }
        
        template<class F, class... Args>
        auto enqueue(F&& f, Args&&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
            using return_type = typename std::result_of<F(Args...)>::type;
            
            auto task = std::make_shared<std::packaged_task<return_type()>>(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...)
            );
            
            std::future<return_type> res = task->get_future();
            
            {
                std::unique_lock<std::mutex> lock(queue_mutex);
                if (stop) {
                    throw std::runtime_error("enqueue on stopped ThreadPool");
                }
                tasks.emplace([task] { (*task)(); });
            }
            
            condition.notify_one();
            return res;
        }
        
        ~ThreadPool() {
            {
                std::unique_lock<std::mutex> lock(queue_mutex);
                stop = true;
            }
            
            condition.notify_all();
            for (std::thread& worker : workers) {
                worker.join();
            }
        }
    };
    
    ThreadPool pool(4);
    
    // Submit tasks to thread pool
    std::vector<std::future<int>> futures;
    for (int i = 0; i < 8; ++i) {
        futures.push_back(pool.enqueue([i]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            return i * i;
        }));
    }
    
    // Collect results
    std::cout << "  Thread pool results: ";
    for (auto& future : futures) {
        std::cout << future.get() << " ";
    }
    std::cout << std::endl;
    
    // 5. Lock-Free Data Structures
    std::cout << "\n5. LOCK-FREE DATA STRUCTURES:" << std::endl;
    
    // Simple lock-free stack
    template<typename T>
    class LockFreeStack {
    private:
        struct Node {
            T data;
            Node* next;
            Node(T const& data_) : data(data_) {}
        };
        
        std::atomic<Node*> head;
        
    public:
        LockFreeStack() : head(nullptr) {}
        
        void push(T const& data) {
            Node* new_node = new Node(data);
            new_node->next = head.load();
            while (!head.compare_exchange_weak(new_node->next, new_node)) {
                // Retry
            }
        }
        
        bool pop(T& result) {
            Node* old_head = head.load();
            while (old_head && !head.compare_exchange_weak(old_head, old_head->next)) {
                // Retry
            }
            if (old_head) {
                result = old_head->data;
                delete old_head;
                return true;
            }
            return false;
        }
        
        bool empty() const {
            return head.load() == nullptr;
        }
    };
    
    LockFreeStack<int> lock_free_stack;
    
    // Push elements
    for (int i = 0; i < 5; ++i) {
        lock_free_stack.push(i);
    }
    
    // Pop elements
    std::cout << "  Lock-free stack: ";
    int value;
    while (lock_free_stack.pop(value)) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    
    // 6. Producer-Consumer with Lock-Free Queue
    std::cout << "\n6. PRODUCER-CONSUMER WITH LOCK-FREE QUEUE:" << std::endl;
    
    // Simple lock-free queue using atomic pointers
    template<typename T>
    class LockFreeQueue {
    private:
        struct Node {
            std::atomic<T*> data;
            std::atomic<Node*> next;
            Node() : data(nullptr), next(nullptr) {}
        };
        
        std::atomic<Node*> head;
        std::atomic<Node*> tail;
        
    public:
        LockFreeQueue() {
            Node* dummy = new Node;
            head.store(dummy);
            tail.store(dummy);
        }
        
        void enqueue(T item) {
            Node* new_node = new Node;
            T* data = new T(item);
            new_node->data.store(data);
            
            Node* prev_tail = tail.exchange(new_node);
            prev_tail->next.store(new_node);
        }
        
        bool dequeue(T& result) {
            Node* head_node = head.load();
            Node* next = head_node->next.load();
            
            if (next == nullptr) {
                return false;
            }
            
            T* data = next->data.load();
            if (data == nullptr) {
                return false;
            }
            
            result = *data;
            head.store(next);
            delete data;
            delete head_node;
            return true;
        }
    };
    
    LockFreeQueue<int> lock_free_queue;
    std::atomic<bool> producer_done(false);
    
    // Producer thread
    std::thread producer_thread([&]() {
        for (int i = 0; i < 10; ++i) {
            lock_free_queue.enqueue(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        producer_done.store(true);
    });
    
    // Consumer thread
    std::thread consumer_thread([&]() {
        int item;
        while (!producer_done.load() || lock_free_queue.dequeue(item)) {
            if (lock_free_queue.dequeue(item)) {
                std::cout << "  Consumed: " << item << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(25));
        }
    });
    
    producer_thread.join();
    consumer_thread.join();
    
    // 7. Barrier Synchronization
    std::cout << "\n7. BARRIER SYNCHRONIZATION:" << std::endl;
    
    class Barrier {
    private:
        std::mutex mutex;
        std::condition_variable condition;
        size_t count;
        size_t generation;
        
    public:
        Barrier(size_t count_) : count(count_), generation(0) {}
        
        void wait() {
            std::unique_lock<std::mutex> lock(mutex);
            size_t gen = generation;
            
            if (--count == 0) {
                generation++;
                count = count;
                condition.notify_all();
            } else {
                condition.wait(lock, [this, gen] { return gen != generation; });
            }
        }
    };
    
    Barrier barrier(3);
    
    std::vector<std::thread> barrier_threads;
    for (int i = 0; i < 3; ++i) {
        barrier_threads.emplace_back([&barrier, i]() {
            std::cout << "  Thread " << i << " before barrier" << std::endl;
            barrier.wait();
            std::cout << "  Thread " << i << " after barrier" << std::endl;
        });
    }
    
    for (auto& t : barrier_threads) {
        t.join();
    }
    
    // 8. Read-Write Locks
    std::cout << "\n8. READ-WRITE LOCKS:" << std::endl;
    
    class ReadWriteLock {
    private:
        std::mutex mutex;
        std::condition_variable read_condition;
        std::condition_variable write_condition;
        int readers;
        bool writer;
        
    public:
        ReadWriteLock() : readers(0), writer(false) {}
        
        void read_lock() {
            std::unique_lock<std::mutex> lock(mutex);
            read_condition.wait(lock, [this] { return !writer; });
            readers++;
        }
        
        void read_unlock() {
            std::unique_lock<std::mutex> lock(mutex);
            readers--;
            if (readers == 0) {
                write_condition.notify_one();
            }
        }
        
        void write_lock() {
            std::unique_lock<std::mutex> lock(mutex);
            write_condition.wait(lock, [this] { return !writer && readers == 0; });
            writer = true;
        }
        
        void write_unlock() {
            std::unique_lock<std::mutex> lock(mutex);
            writer = false;
            read_condition.notify_all();
            write_condition.notify_one();
        }
    };
    
    ReadWriteLock rw_lock;
    std::atomic<int> shared_data(0);
    
    // Reader threads
    std::vector<std::thread> reader_threads;
    for (int i = 0; i < 3; ++i) {
        reader_threads.emplace_back([&rw_lock, &shared_data, i]() {
            rw_lock.read_lock();
            std::cout << "  Reader " << i << " read: " << shared_data.load() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            rw_lock.read_unlock();
        });
    }
    
    // Writer thread
    std::thread writer_thread([&rw_lock, &shared_data]() {
        rw_lock.write_lock();
        shared_data.store(42);
        std::cout << "  Writer wrote: " << shared_data.load() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        rw_lock.write_unlock();
    });
    
    for (auto& t : reader_threads) {
        t.join();
    }
    writer_thread.join();
    
    // 9. Performance Comparison
    std::cout << "\n9. PERFORMANCE COMPARISON:" << std::endl;
    
    const int num_operations = 1000000;
    
    // Mutex-based counter
    std::atomic<int> mutex_counter(0);
    std::mutex counter_mutex;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    std::vector<std::thread> mutex_threads;
    for (int i = 0; i < 4; ++i) {
        mutex_threads.emplace_back([&]() {
            for (int j = 0; j < num_operations / 4; ++j) {
                std::lock_guard<std::mutex> lock(counter_mutex);
                mutex_counter++;
            }
        });
    }
    
    for (auto& t : mutex_threads) {
        t.join();
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto mutex_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Atomic counter
    std::atomic<int> atomic_counter2(0);
    
    start = std::chrono::high_resolution_clock::now();
    
    std::vector<std::thread> atomic_threads;
    for (int i = 0; i < 4; ++i) {
        atomic_threads.emplace_back([&]() {
            for (int j = 0; j < num_operations / 4; ++j) {
                atomic_counter2++;
            }
        });
    }
    
    for (auto& t : atomic_threads) {
        t.join();
    }
    
    end = std::chrono::high_resolution_clock::now();
    auto atomic_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "  Mutex counter time: " << mutex_time.count() << " microseconds" << std::endl;
    std::cout << "  Atomic counter time: " << atomic_time.count() << " microseconds" << std::endl;
    std::cout << "  Atomic speedup: " << (double)mutex_time.count() / atomic_time.count() << "x" << std::endl;
    std::cout << "  Mutex counter value: " << mutex_counter.load() << std::endl;
    std::cout << "  Atomic counter value: " << atomic_counter2.load() << std::endl;
    
    // 10. Advanced Synchronization Patterns
    std::cout << "\n10. ADVANCED SYNCHRONIZATION PATTERNS:" << std::endl;
    
    // Semaphore implementation
    class Semaphore {
    private:
        std::mutex mutex;
        std::condition_variable condition;
        int count;
        
    public:
        Semaphore(int count_) : count(count_) {}
        
        void acquire() {
            std::unique_lock<std::mutex> lock(mutex);
            condition.wait(lock, [this] { return count > 0; });
            count--;
        }
        
        void release() {
            std::unique_lock<std::mutex> lock(mutex);
            count++;
            condition.notify_one();
        }
    };
    
    Semaphore semaphore(2);
    
    std::vector<std::thread> semaphore_threads;
    for (int i = 0; i < 5; ++i) {
        semaphore_threads.emplace_back([&semaphore, i]() {
            semaphore.acquire();
            std::cout << "  Thread " << i << " acquired semaphore" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            std::cout << "  Thread " << i << " releasing semaphore" << std::endl;
            semaphore.release();
        });
    }
    
    for (auto& t : semaphore_threads) {
        t.join();
    }
    
    std::cout << "\nAdvanced concurrency demonstration completed!" << std::endl;
    return 0;
}
