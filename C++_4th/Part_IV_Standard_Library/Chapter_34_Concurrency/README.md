# Chapter 34: Concurrency

## 📘 Learning Objectives

After completing this chapter, you will:
- Master thread creation and management
- Understand synchronization primitives
- Learn about atomic operations and memory ordering
- Master async programming with futures and promises
- Understand thread-safe programming patterns

## 🎯 Key Concepts

### 1. Thread Management

- **std::thread**: Thread creation and management
- **Thread functions**: Function objects, lambdas, member functions
- **Thread lifecycle**: Creation, execution, joining, detaching
- **Thread IDs**: Identification and comparison
- **Hardware concurrency**: CPU core detection

### 2. Synchronization Primitives

- **std::mutex**: Mutual exclusion locks
- **std::lock_guard**: RAII mutex wrapper
- **std::unique_lock**: Flexible mutex wrapper
- **std::shared_mutex**: Reader-writer locks
- **std::condition_variable**: Thread synchronization

### 3. Atomic Operations

- **std::atomic**: Atomic data types
- **Memory ordering**: Sequential, acquire, release, relaxed
- **Atomic operations**: Load, store, exchange, compare_exchange
- **Lock-free programming**: Atomic-based synchronization

### 4. Async Programming

- **std::async**: Asynchronous function execution
- **std::future**: Future value access
- **std::promise**: Promise value setting
- **std::packaged_task**: Function wrapper for async execution

### 5. Thread-Safe Patterns

- **Thread-safe containers**: Concurrent data structures
- **Producer-consumer patterns**: Work queues and pipelines
- **Thread pools**: Managed thread execution
- **Lock-free data structures**: Atomic-based containers

## 🧩 Practice Exercises

### Exercise 34.1: Thread Creation
Create and manage multiple threads.

### Exercise 34.2: Synchronization
Use mutexes and condition variables.

### Exercise 34.3: Atomic Operations
Implement lock-free programming.

### Exercise 34.4: Async Programming
Use futures and promises for async execution.

## 💻 Code Examples

### Thread Management
```cpp
#include <iostream>
#include <thread>
#include <vector>

void worker_function(int id) {
    std::cout << "Thread " << id << " is working" << std::endl;
}

int main() {
    std::vector<std::thread> threads;
    
    // Create multiple threads
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back(worker_function, i);
    }
    
    // Wait for all threads to complete
    for (auto& t : threads) {
        t.join();
    }
    
    return 0;
}
```

### Synchronization
```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

std::mutex mtx;
int shared_data = 0;

void increment_data(int id) {
    for (int i = 0; i < 1000; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        shared_data++;
    }
}

int main() {
    std::vector<std::thread> threads;
    
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back(increment_data, i);
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "Final value: " << shared_data << std::endl;
    return 0;
}
```

## 🎓 Key Takeaways

1. **Use RAII for synchronization**: lock_guard and unique_lock
2. **Prefer atomic operations**: For simple synchronization
3. **Use async for I/O**: Don't block threads unnecessarily
4. **Design for thread safety**: Consider concurrent access
5. **Avoid data races**: Use proper synchronization

## 🔗 Next Steps

After mastering concurrency, proceed to Chapter 35 to learn about I/O and file handling.

## 📚 Additional Resources

- C++ Reference: Thread Support
- C++ Core Guidelines: Concurrency
- Practice with concurrent programming patterns
