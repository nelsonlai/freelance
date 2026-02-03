/*
 * Lesson 4.1: Concurrency Basics
 * 
 * This file demonstrates thread creation, synchronization primitives,
 * and concurrent programming concepts.
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <atomic>
#include <condition_variable>
#include <queue>

// Global variables for demonstration
std::mutex print_mutex;
int shared_counter = 0;
std::atomic<int> atomic_counter{0};

// Function to demonstrate basic thread creation
void demonstrateBasicThreads() {
    std::cout << "=== Basic Thread Demonstration ===" << std::endl;
    
    auto worker_function = [](int id) {
        std::lock_guard<std::mutex> lock(print_mutex);
        std::cout << "Worker thread " << id << " executing" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "Worker thread " << id << " completed" << std::endl;
    };
    
    std::cout << "Main thread ID: " << std::this_thread::get_id() << std::endl;
    
    // Create multiple threads
    std::vector<std::thread> threads;
    for (int i = 0; i < 3; ++i) {
        threads.emplace_back(worker_function, i);
    }
    
    // Wait for all threads to complete
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "All threads completed" << std::endl;
}

// Function to demonstrate thread safety issues
void demonstrateRaceConditions() {
    std::cout << "
=== Race Condition Demonstration ===" << std::endl;
    
    // Unsafe counter
    int unsafe_counter = 0;
    
    auto unsafe_increment = [&unsafe_counter](int iterations) {
        for (int i = 0; i < iterations; ++i) {
            // Race condition: multiple threads can read same value
            int temp = unsafe_counter;
            temp += 1;
            unsafe_counter = temp;
        }
    };
    
    // Safe counter with mutex
    int safe_counter = 0;
    std::mutex safe_mutex;
    
    auto safe_increment = [&safe_counter, &safe_mutex](int iterations) {
        for (int i = 0; i < iterations; ++i) {
            std::lock_guard<std::mutex> lock(safe_mutex);
            ++safe_counter;
        }
    };
    
    // Atomic counter
    auto atomic_increment = [](int iterations) {
        for (int i = 0; i < iterations; ++i) {
            ++atomic_counter;
        }
    };
    
    const int iterations = 1000;
    const int num_threads = 3;
    
    // Test unsafe counter
    std::vector<std::thread> unsafe_threads;
    for (int i = 0; i < num_threads; ++i) {
        unsafe_threads.emplace_back(unsafe_increment, iterations);
    }
    
    for (auto& t : unsafe_threads) {
        t.join();
    }
    
    std::cout << "Unsafe counter result: " << unsafe_counter 
              << " (expected: " << num_threads * iterations << ")" << std::endl;
    
    // Test safe counter
    std::vector<std::thread> safe_threads;
    for (int i = 0; i < num_threads; ++i) {
        safe_threads.emplace_back(safe_increment, iterations);
    }
    
    for (auto& t : safe_threads) {
        t.join();
    }
    
    std::cout << "Safe counter result: " << safe_counter 
              << " (expected: " << num_threads * iterations << ")" << std::endl;
    
    // Test atomic counter
    atomic_counter = 0;
    std::vector<std::thread> atomic_threads;
    for (int i = 0; i < num_threads; ++i) {
        atomic_threads.emplace_back(atomic_increment, iterations);
    }
    
    for (auto& t : atomic_threads) {
        t.join();
    }
    
    std::cout << "Atomic counter result: " << atomic_counter.load() 
              << " (expected: " << num_threads * iterations << ")" << std::endl;
}

// Thread-safe counter class
class ThreadSafeCounter {
private:
    mutable std::mutex mtx;
    int count = 0;
    
public:
    void increment() {
        std::lock_guard<std::mutex> lock(mtx);
        ++count;
    }
    
    int get() const {
        std::lock_guard<std::mutex> lock(mtx);
        return count;
    }
    
    void reset() {
        std::lock_guard<std::mutex> lock(mtx);
        count = 0;
    }
};

// Function to demonstrate thread-safe class
void demonstrateThreadSafeClass() {
    std::cout << "
=== Thread-Safe Class Demonstration ===" << std::endl;
    
    ThreadSafeCounter counter;
    
    auto increment_worker = [&counter](int iterations) {
        for (int i = 0; i < iterations; ++i) {
            counter.increment();
        }
    };
    
    const int iterations = 1000;
    const int num_threads = 3;
    
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(increment_worker, iterations);
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "Thread-safe counter result: " << counter.get() 
              << " (expected: " << num_threads * iterations << ")" << std::endl;
}

// Producer-consumer pattern
class ProducerConsumer {
private:
    std::queue<int> queue;
    std::mutex queue_mutex;
    std::condition_variable cv;
    bool finished = false;
    
public:
    void producer(int items) {
        for (int i = 0; i < items; ++i) {
            std::unique_lock<std::mutex> lock(queue_mutex);
            queue.push(i);
            std::cout << "Produced: " << i << std::endl;
            cv.notify_one();
        }
        
        // Signal completion
        {
            std::lock_guard<std::mutex> lock(queue_mutex);
            finished = true;
        }
        cv.notify_all();
    }
    
    void consumer(int id) {
        while (true) {
            std::unique_lock<std::mutex> lock(queue_mutex);
            cv.wait(lock, [this] { return !queue.empty() || finished; });
            
            if (finished && queue.empty()) {
                break;
            }
            
            if (!queue.empty()) {
                int item = queue.front();
                queue.pop();
                std::cout << "Consumer " << id << " consumed: " << item << std::endl;
            }
        }
    }
};

// Function to demonstrate producer-consumer pattern
void demonstrateProducerConsumer() {
    std::cout << "
=== Producer-Consumer Demonstration ===" << std::endl;
    
    ProducerConsumer pc;
    
    // Create producer thread
    std::thread producer_thread(&ProducerConsumer::producer, &pc, 10);
    
    // Create consumer threads
    std::vector<std::thread> consumer_threads;
    for (int i = 0; i < 2; ++i) {
        consumer_threads.emplace_back(&ProducerConsumer::consumer, &pc, i);
    }
    
    // Wait for all threads
    producer_thread.join();
    for (auto& t : consumer_threads) {
        t.join();
    }
    
    std::cout << "Producer-consumer demonstration completed" << std::endl;
}

// Deadlock prevention example
class Account {
public:
    std::mutex mtx;
    int balance;
    
    Account(int initial_balance) : balance(initial_balance) {}
    
    void withdraw(int amount) {
        std::lock_guard<std::mutex> lock(mtx);
        if (balance >= amount) {
            balance -= amount;
        }
    }
    
    void deposit(int amount) {
        std::lock_guard<std::mutex> lock(mtx);
        balance += amount;
    }
};

void transfer_money(Account& from, Account& to, int amount) {
    // Deadlock prevention: always lock in same order
    std::lock(from.mtx, to.mtx);
    std::lock_guard<std::mutex> lock1(from.mtx, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(to.mtx, std::adopt_lock);
    
    if (from.balance >= amount) {
        from.balance -= amount;
        to.balance += amount;
        std::cout << "Transferred " << amount << " from account 1 to account 2" << std::endl;
    }
}

// Function to demonstrate deadlock prevention
void demonstrateDeadlockPrevention() {
    std::cout << "
=== Deadlock Prevention Demonstration ===" << std::endl;
    
    Account account1(1000);
    Account account2(500);
    
    std::cout << "Initial balances - Account 1: " << account1.balance 
              << ", Account 2: " << account2.balance << std::endl;
    
    // Create multiple threads doing transfers
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(transfer_money, std::ref(account1), std::ref(account2), 100);
        threads.emplace_back(transfer_money, std::ref(account2), std::ref(account1), 50);
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "Final balances - Account 1: " << account1.balance 
              << ", Account 2: " << account2.balance << std::endl;
}

// Performance comparison
void demonstratePerformance() {
    std::cout << "
=== Performance Demonstration ===" << std::endl;
    
    const int iterations = 1000000;
    const int num_threads = 4;
    
    // Single-threaded execution
    auto start = std::chrono::high_resolution_clock::now();
    
    int single_threaded_sum = 0;
    for (int i = 0; i < iterations; ++i) {
        single_threaded_sum += i;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto single_threaded_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Single-threaded time: " << single_threaded_time.count() << " ms" << std::endl;
    
    // Multi-threaded execution
    start = std::chrono::high_resolution_clock::now();
    
    std::atomic<int> multi_threaded_sum{0};
    std::vector<std::thread> threads;
    
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&multi_threaded_sum, iterations, num_threads, i]() {
            int start_idx = i * (iterations / num_threads);
            int end_idx = (i + 1) * (iterations / num_threads);
            
            for (int j = start_idx; j < end_idx; ++j) {
                multi_threaded_sum += j;
            }
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    end = std::chrono::high_resolution_clock::now();
    auto multi_threaded_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Multi-threaded time: " << multi_threaded_time.count() << " ms" << std::endl;
    std::cout << "Speedup: " << (double)single_threaded_time.count() / multi_threaded_time.count() << "x" << std::endl;
}

int main() {
    std::cout << "=== Concurrency Basics Demonstration ===" << std::endl;
    std::cout << "This program demonstrates thread creation, synchronization primitives,
"
              << "and concurrent programming concepts.
" << std::endl;
    
    // Demonstrate various concurrency concepts
    demonstrateBasicThreads();
    demonstrateRaceConditions();
    demonstrateThreadSafeClass();
    demonstrateProducerConsumer();
    demonstrateDeadlockPrevention();
    demonstratePerformance();
    
    std::cout << "
=== Key Takeaways ===" << std::endl;
    std::cout << "1. Threads allow concurrent execution of tasks" << std::endl;
    std::cout << "2. Race conditions occur when multiple threads access shared data" << std::endl;
    std::cout << "3. Mutexes provide mutual exclusion for critical sections" << std::endl;
    std::cout << "4. Atomic operations are lock-free and thread-safe" << std::endl;
    std::cout << "5. Producer-consumer pattern is useful for task distribution" << std::endl;
    std::cout << "6. Deadlock prevention requires consistent lock ordering" << std::endl;
    std::cout << "7. Thread overhead can affect performance for small tasks" << std::endl;
    
    std::cout << "
Program completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -pthread -O2 -o concurrency_basics 01_Concurrency_Basics.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -pthread -O2 -o concurrency_basics 01_Concurrency_Basics.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 01_Concurrency_Basics.cpp
 * 
 * Running:
 * ./concurrency_basics (Linux/macOS)
 * concurrency_basics.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for threading support.
 * C++17 is recommended for best concurrency features.
 * 
 * Threading Notes:
 * - Always link with -pthread on Unix systems
 * - Thread creation has overhead, so use for substantial work
 * - Synchronization primitives have performance costs
 * - Consider thread pools for many short tasks
 */