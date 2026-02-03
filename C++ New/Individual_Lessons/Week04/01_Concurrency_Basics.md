# Lesson 4.1: Concurrency Basics

## Learning Objectives
- Understand concurrent programming concepts
- Learn thread creation and management
- Master synchronization primitives
- Practice thread-safe programming
- Compare different concurrency models

## Prerequisites
- Completed Lesson 3.3 (STL Algorithms)
- Understanding of object-oriented programming
- Basic knowledge of operating systems

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Concurrency Concepts

#### What is Concurrency?
- **Concurrency:** Multiple tasks executing simultaneously
- **Parallelism:** Multiple tasks executing on different cores
- **Threads:** Lightweight processes sharing memory
- **Synchronization:** Coordinating access to shared resources

#### Benefits and Challenges
- **Benefits:** Better resource utilization, improved responsiveness
- **Challenges:** Race conditions, deadlocks, complexity

### 2. Thread Management

#### Thread Creation
```cpp
#include <thread>
#include <iostream>

void worker_function() {
    std::cout << "Worker thread executing" << std::endl;
}

int main() {
    std::thread t(worker_function);
    t.join();  // Wait for thread to complete
    return 0;
}
```

#### Thread Lifecycle
- **Creation:** std::thread constructor
- **Execution:** Function runs in parallel
- **Completion:** join() or detach()
- **Destruction:** Automatic cleanup

### 3. Synchronization Primitives

#### Mutex
- **Purpose:** Mutual exclusion
- **Usage:** Protect critical sections
- **Types:** std::mutex, std::recursive_mutex, std::timed_mutex

#### Lock Guards
- **RAII:** Automatic lock management
- **Types:** std::lock_guard, std::unique_lock
- **Benefits:** Exception safety, automatic unlocking

---

## Demonstration (25 minutes)

### Basic Thread Example
```cpp
#include <iostream>
#include <thread>
#include <vector>

void print_numbers(int start, int end) {
    for (int i = start; i < end; ++i) {
        std::cout << "Thread " << std::this_thread::get_id() 
                  << ": " << i << std::endl;
    }
}

int main() {
    std::cout << "Main thread ID: " << std::this_thread::get_id() << std::endl;
    
    // Create threads
    std::thread t1(print_numbers, 1, 6);
    std::thread t2(print_numbers, 6, 11);
    
    // Wait for threads to complete
    t1.join();
    t2.join();
    
    std::cout << "All threads completed" << std::endl;
    return 0;
}
```

### Synchronization Example
```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

std::mutex print_mutex;
int shared_counter = 0;

void increment_counter(int id) {
    for (int i = 0; i < 1000; ++i) {
        std::lock_guard<std::mutex> lock(print_mutex);
        ++shared_counter;
        std::cout << "Thread " << id << " incremented counter to " 
                  << shared_counter << std::endl;
    }
}

int main() {
    std::vector<std::thread> threads;
    
    // Create multiple threads
    for (int i = 0; i < 3; ++i) {
        threads.emplace_back(increment_counter, i);
    }
    
    // Wait for all threads
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "Final counter value: " << shared_counter << std::endl;
    return 0;
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Thread Management
Practice thread creation and management:

**Tasks:**
1. Create multiple threads with different functions
2. Implement thread pooling
3. Handle thread exceptions
4. Measure thread performance

### Activity 2: Synchronization
Implement thread synchronization:

**Tasks:**
1. Protect shared data with mutexes
2. Implement producer-consumer pattern
3. Handle deadlock scenarios
4. Use condition variables

### Activity 3: Real-World Applications
Apply concurrency to practical problems:

**Tasks:**
1. Implement parallel file processing
2. Build a concurrent web server
3. Create a multi-threaded game engine
4. Design a parallel sorting algorithm

---

## Key Concepts

### 1. Thread Safety
```cpp
// Thread-safe counter
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
};
```

### 2. Race Conditions
```cpp
// Race condition example
int shared_data = 0;

void unsafe_increment() {
    // Race condition: multiple threads can read same value
    int temp = shared_data;
    temp += 1;
    shared_data = temp;
}

void safe_increment() {
    std::lock_guard<std::mutex> lock(mtx);
    ++shared_data;  // Atomic operation
}
```

### 3. Deadlock Prevention
```cpp
// Deadlock prevention
void transfer_money(Account& from, Account& to, int amount) {
    // Always lock in same order
    std::lock(from.mutex, to.mutex);
    std::lock_guard<std::mutex> lock1(from.mutex, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(to.mutex, std::adopt_lock);
    
    from.balance -= amount;
    to.balance += amount;
}
```

---

## Best Practices

### 1. Thread Design
- Keep threads focused on single tasks
- Minimize shared data
- Use thread-local storage when possible
- Design for exception safety

### 2. Synchronization
- Use RAII for lock management
- Minimize critical section size
- Avoid nested locks
- Use lock-free data structures when appropriate

### 3. Performance
- Profile before optimizing
- Consider thread overhead
- Use thread pools for short tasks
- Balance parallelism with overhead

---

## Common Pitfalls

### 1. Race Conditions
```cpp
// Wrong: Race condition
int counter = 0;
void increment() {
    ++counter;  // Not atomic!
}

// Correct: Use mutex
std::mutex mtx;
void safe_increment() {
    std::lock_guard<std::mutex> lock(mtx);
    ++counter;
}
```

### 2. Deadlocks
```cpp
// Wrong: Potential deadlock
void function1() {
    std::lock_guard<std::mutex> lock1(mtx1);
    std::lock_guard<std::mutex> lock2(mtx2);
}

void function2() {
    std::lock_guard<std::mutex> lock2(mtx2);  // Different order!
    std::lock_guard<std::mutex> lock1(mtx1);
}
```

### 3. Thread Leaks
```cpp
// Wrong: Thread not joined
std::thread t(worker_function);
// t goes out of scope without join() - undefined behavior!

// Correct: Always join or detach
std::thread t(worker_function);
t.join();  // or t.detach();
```

---

## Assessment

### Quiz Questions
1. What is the difference between concurrency and parallelism?
2. How do you prevent race conditions?
3. What causes deadlocks and how do you prevent them?
4. When should you use threads vs processes?

### Practical Assessment
- Implement working concurrent programs
- Use synchronization primitives correctly
- Handle thread lifecycle properly
- Apply concurrency to real problems

---

## Homework Assignment

### Task 1: Concurrent Data Structures
Implement:
1. Thread-safe queue
2. Concurrent hash table
3. Lock-free stack
4. Producer-consumer system

### Task 2: Performance Analysis
Analyze performance of:
1. Different synchronization primitives
2. Thread pool vs thread creation
3. Lock-free vs lock-based algorithms
4. Memory usage patterns

### Task 3: Real-World Applications
Apply concurrency to:
1. Web server implementation
2. File processing system
3. Game engine components
4. Scientific computing tasks

---

## Next Lesson Preview

In the next lesson, we'll learn about smart pointers:
- Memory management with smart pointers
- unique_ptr, shared_ptr, and weak_ptr
- RAII principles
- Custom deleters

Make sure you understand thread basics before moving on!