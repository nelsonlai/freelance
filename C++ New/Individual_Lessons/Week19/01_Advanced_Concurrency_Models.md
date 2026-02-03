# Week 19, Lesson 1: Advanced Concurrency Models

## 1. Learning Objectives

- Understand advanced concurrency models and their applications.
- Learn the actor model for message-based concurrency.
- Explore message passing patterns for inter-process communication.
- Understand coroutines and cooperative multitasking.
- Learn async/await patterns for asynchronous programming.
- Explore advanced synchronization primitives.
- Understand read-write locks, barriers, and semaphores.
- Learn best practices for advanced concurrency programming.

## 2. Prerequisites

- Understanding of basic concurrency concepts
- Knowledge of threads, mutexes, and condition variables
- Familiarity with C++17 and C++20 features
- Understanding of asynchronous programming concepts
- Knowledge of synchronization primitives

## 3. Actor Model

### 3.1 Actor Model Concepts

**Actor Model Principles:**
- Actors are independent concurrent entities
- Actors communicate only through messages
- Actors have isolated state
- Actors process messages sequentially
- Actors can create other actors

**Actor Model Benefits:**
- Natural concurrency model
- No shared mutable state
- Fault tolerance through isolation
- Scalability through message passing
- Easy to reason about and test

### 3.2 Actor Implementation

```cpp
// Message base class
class Message {
public:
    virtual ~Message() = default;
    virtual std::string get_type() const = 0;
};

// Actor base class
class Actor {
private:
    std::queue<std::unique_ptr<Message>> message_queue_;
    std::mutex queue_mutex_;
    std::condition_variable queue_cv_;
    std::atomic<bool> running_;
    std::thread actor_thread_;
    
protected:
    virtual void handle_message(std::unique_ptr<Message> message) = 0;
    
public:
    Actor() : running_(false) {}
    
    virtual ~Actor() {
        stop();
    }
    
    // Non-copyable
    Actor(const Actor&) = delete;
    Actor& operator=(const Actor&) = delete;
    
    // Start actor
    void start() {
        if (running_) {
            return;
        }
        
        running_ = true;
        actor_thread_ = std::thread(&Actor::actor_loop, this);
    }
    
    // Stop actor
    void stop() {
        if (running_) {
            running_ = false;
            queue_cv_.notify_all();
            if (actor_thread_.joinable()) {
                actor_thread_.join();
            }
        }
    }
    
    // Send message to actor
    void send_message(std::unique_ptr<Message> message) {
        if (!running_) {
            return;
        }
        
        {
            std::lock_guard<std::mutex> lock(queue_mutex_);
            message_queue_.push(std::move(message));
        }
        queue_cv_.notify_one();
    }
    
    // Check if actor is running
    bool is_running() const {
        return running_;
    }
    
private:
    void actor_loop() {
        while (running_) {
            std::unique_ptr<Message> message;
            
            {
                std::unique_lock<std::mutex> lock(queue_mutex_);
                queue_cv_.wait(lock, [this] { return !message_queue_.empty() || !running_; });
                
                if (!running_) {
                    break;
                }
                
                if (!message_queue_.empty()) {
                    message = std::move(message_queue_.front());
                    message_queue_.pop();
                }
            }
            
            if (message) {
                handle_message(std::move(message));
            }
        }
    }
};
```

### 3.3 Counter Actor Example

```cpp
// Counter message
class CounterMessage : public Message {
private:
    std::string operation_;
    int value_;
    
public:
    CounterMessage(const std::string& operation, int value = 0) 
        : operation_(operation), value_(value) {}
    
    std::string get_type() const override {
        return "CounterMessage";
    }
    
    const std::string& get_operation() const { return operation_; }
    int get_value() const { return value_; }
};

// Counter actor
class CounterActor : public Actor {
private:
    int counter_;
    std::string name_;
    
public:
    CounterActor(const std::string& name) : counter_(0), name_(name) {}
    
    void handle_message(std::unique_ptr<Message> message) override {
        auto* counter_msg = dynamic_cast<CounterMessage*>(message.get());
        if (!counter_msg) {
            return;
        }
        
        const std::string& operation = counter_msg->get_operation();
        
        if (operation == "increment") {
            ++counter_;
            std::cout << "[" << name_ << "] Counter incremented to: " << counter_ << std::endl;
        } else if (operation == "decrement") {
            --counter_;
            std::cout << "[" << name_ << "] Counter decremented to: " << counter_ << std::endl;
        } else if (operation == "add") {
            counter_ += counter_msg->get_value();
            std::cout << "[" << name_ << "] Counter added " << counter_msg->get_value() << ", now: " << counter_ << std::endl;
        } else if (operation == "get") {
            std::cout << "[" << name_ << "] Current counter value: " << counter_ << std::endl;
        }
    }
    
    int get_counter() const { return counter_; }
};
```

### 3.4 Actor System

```cpp
// Actor system
class ActorSystem {
private:
    std::vector<std::unique_ptr<Actor>> actors_;
    std::mutex actors_mutex_;
    
public:
    ActorSystem() = default;
    
    ~ActorSystem() {
        stop_all();
    }
    
    // Add actor to system
    template<typename T, typename... Args>
    T* add_actor(Args&&... args) {
        std::lock_guard<std::mutex> lock(actors_mutex_);
        
        auto actor = std::make_unique<T>(std::forward<Args>(args)...);
        T* ptr = actor.get();
        actors_.push_back(std::move(actor));
        return ptr;
    }
    
    // Start all actors
    void start_all() {
        std::lock_guard<std::mutex> lock(actors_mutex_);
        
        for (auto& actor : actors_) {
            actor->start();
        }
    }
    
    // Stop all actors
    void stop_all() {
        std::lock_guard<std::mutex> lock(actors_mutex_);
        
        for (auto& actor : actors_) {
            actor->stop();
        }
    }
    
    // Get actor count
    size_t get_actor_count() const {
        std::lock_guard<std::mutex> lock(actors_mutex_);
        return actors_.size();
    }
};
```

## 4. Message Passing

### 4.1 Message Passing Concepts

**Message Passing Benefits:**
- Decoupled communication
- Asynchronous processing
- Fault isolation
- Scalability
- Natural distribution

**Message Passing Patterns:**
- Point-to-point messaging
- Publish-subscribe
- Request-reply
- Broadcast messaging

### 4.2 Message Passing System

```cpp
// Message passing system
class MessagePassingSystem {
private:
    struct Message {
        std::string from;
        std::string to;
        std::string type;
        std::string data;
        std::chrono::steady_clock::time_point timestamp;
        
        Message(const std::string& from, const std::string& to, const std::string& type, const std::string& data)
            : from(from), to(to), type(type), data(data), timestamp(std::chrono::steady_clock::now()) {}
    };
    
    std::map<std::string, std::queue<Message>> message_queues_;
    std::mutex queues_mutex_;
    std::condition_variable queue_cv_;
    std::atomic<bool> running_;
    std::thread message_thread_;
    
public:
    MessagePassingSystem() : running_(false) {}
    
    ~MessagePassingSystem() {
        stop();
    }
    
    // Start message passing system
    void start() {
        if (running_) {
            return;
        }
        
        running_ = true;
        message_thread_ = std::thread(&MessagePassingSystem::message_loop, this);
    }
    
    // Stop message passing system
    void stop() {
        if (running_) {
            running_ = false;
            queue_cv_.notify_all();
            if (message_thread_.joinable()) {
                message_thread_.join();
            }
        }
    }
    
    // Send message
    void send_message(const std::string& from, const std::string& to, const std::string& type, const std::string& data) {
        if (!running_) {
            return;
        }
        
        {
            std::lock_guard<std::mutex> lock(queues_mutex_);
            message_queues_[to].emplace(from, to, type, data);
        }
        queue_cv_.notify_one();
    }
    
    // Receive message
    std::optional<Message> receive_message(const std::string& recipient) {
        std::lock_guard<std::mutex> lock(queues_mutex_);
        
        auto it = message_queues_.find(recipient);
        if (it != message_queues_.end() && !it->second.empty()) {
            Message msg = it->second.front();
            it->second.pop();
            return msg;
        }
        
        return std::nullopt;
    }
    
    // Check if has messages
    bool has_messages(const std::string& recipient) const {
        std::lock_guard<std::mutex> lock(queues_mutex_);
        
        auto it = message_queues_.find(recipient);
        return it != message_queues_.end() && !it->second.empty();
    }
    
private:
    void message_loop() {
        while (running_) {
            std::unique_lock<std::mutex> lock(queues_mutex_);
            queue_cv_.wait(lock, [this] { return !message_queues_.empty() || !running_; });
            
            if (!running_) {
                break;
            }
            
            // Process messages
            for (auto& [recipient, queue] : message_queues_) {
                while (!queue.empty()) {
                    Message msg = queue.front();
                    queue.pop();
                    
                    // Process message (in real implementation, this would call registered handlers)
                    std::cout << "Message from " << msg.from << " to " << msg.to 
                              << " [" << msg.type << "]: " << msg.data << std::endl;
                }
            }
        }
    }
};
```

### 4.3 Message Process

```cpp
// Message handler interface
class MessageHandler {
public:
    virtual ~MessageHandler() = default;
    virtual void handle_message(const std::string& from, const std::string& type, const std::string& data) = 0;
};

// Process with message handling
class MessageProcess {
private:
    std::string name_;
    MessagePassingSystem* system_;
    std::unique_ptr<MessageHandler> handler_;
    std::atomic<bool> running_;
    std::thread process_thread_;
    
public:
    MessageProcess(const std::string& name, MessagePassingSystem* system, std::unique_ptr<MessageHandler> handler)
        : name_(name), system_(system), handler_(std::move(handler)), running_(false) {}
    
    ~MessageProcess() {
        stop();
    }
    
    // Start process
    void start() {
        if (running_) {
            return;
        }
        
        running_ = true;
        process_thread_ = std::thread(&MessageProcess::process_loop, this);
    }
    
    // Stop process
    void stop() {
        if (running_) {
            running_ = false;
            if (process_thread_.joinable()) {
                process_thread_.join();
            }
        }
    }
    
    // Send message
    void send_message(const std::string& to, const std::string& type, const std::string& data) {
        if (system_ && running_) {
            system_->send_message(name_, to, type, data);
        }
    }
    
    // Get process name
    const std::string& get_name() const { return name_; }
    
private:
    void process_loop() {
        while (running_) {
            if (system_->has_messages(name_)) {
                auto message = system_->receive_message(name_);
                if (message && handler_) {
                    handler_->handle_message(message->from, message->type, message->data);
                }
            }
            
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
};
```

## 5. Coroutines

### 5.1 Coroutine Concepts

**Coroutine Benefits:**
- Cooperative multitasking
- Suspend and resume execution
- Efficient for I/O operations
- Natural async programming
- Memory efficient

**Coroutine Types:**
- Generator coroutines
- Task coroutines
- Async coroutines

### 5.2 Task Coroutine

```cpp
// Simple coroutine task
template<typename T>
class Task {
public:
    struct promise_type {
        T value;
        std::exception_ptr exception;
        
        Task get_return_object() {
            return Task{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        
        void unhandled_exception() {
            exception = std::current_exception();
        }
        
        std::suspend_always yield_value(T val) {
            value = val;
            return {};
        }
        
        void return_value(T val) {
            value = val;
        }
    };
    
    using handle_type = std::coroutine_handle<promise_type>;
    
private:
    handle_type coro_;
    
public:
    Task(handle_type h) : coro_(h) {}
    
    ~Task() {
        if (coro_) {
            coro_.destroy();
        }
    }
    
    // Non-copyable
    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;
    
    // Movable
    Task(Task&& other) noexcept : coro_(other.coro_) {
        other.coro_ = {};
    }
    
    Task& operator=(Task&& other) noexcept {
        if (this != &other) {
            if (coro_) {
                coro_.destroy();
            }
            coro_ = other.coro_;
            other.coro_ = {};
        }
        return *this;
    }
    
    // Resume coroutine
    bool resume() {
        if (!coro_ || coro_.done()) {
            return false;
        }
        
        coro_.resume();
        return !coro_.done();
    }
    
    // Check if coroutine is done
    bool done() const {
        return !coro_ || coro_.done();
    }
    
    // Get value
    T get_value() const {
        if (coro_ && !coro_.done()) {
            return coro_.promise().value;
        }
        return {};
    }
    
    // Get exception
    std::exception_ptr get_exception() const {
        if (coro_ && !coro_.done()) {
            return coro_.promise().exception;
        }
        return nullptr;
    }
};
```

### 5.3 Generator Coroutine

```cpp
// Coroutine generator
template<typename T>
class Generator {
public:
    struct promise_type {
        T value;
        std::exception_ptr exception;
        
        Generator get_return_object() {
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        
        void unhandled_exception() {
            exception = std::current_exception();
        }
        
        std::suspend_always yield_value(T val) {
            value = val;
            return {};
        }
        
        void return_void() {}
    };
    
    using handle_type = std::coroutine_handle<promise_type>;
    
private:
    handle_type coro_;
    
public:
    Generator(handle_type h) : coro_(h) {}
    
    ~Generator() {
        if (coro_) {
            coro_.destroy();
        }
    }
    
    // Non-copyable
    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;
    
    // Movable
    Generator(Generator&& other) noexcept : coro_(other.coro_) {
        other.coro_ = {};
    }
    
    Generator& operator=(Generator&& other) noexcept {
        if (this != &other) {
            if (coro_) {
                coro_.destroy();
            }
            coro_ = other.coro_;
            other.coro_ = {};
        }
        return *this;
    }
    
    // Iterator interface
    struct iterator {
        Generator* gen;
        
        iterator(Generator* g) : gen(g) {
            if (gen && !gen->done()) {
                gen->resume();
            }
        }
        
        iterator& operator++() {
            if (gen && !gen->done()) {
                gen->resume();
            }
            return *this;
        }
        
        bool operator!=(const iterator& other) const {
            return gen != other.gen || (gen && !gen->done());
        }
        
        T operator*() const {
            return gen ? gen->get_value() : T{};
        }
    };
    
    iterator begin() {
        return iterator(this);
    }
    
    iterator end() {
        return iterator(nullptr);
    }
    
    // Resume coroutine
    bool resume() {
        if (!coro_ || coro_.done()) {
            return false;
        }
        
        coro_.resume();
        return !coro_.done();
    }
    
    // Check if coroutine is done
    bool done() const {
        return !coro_ || coro_.done();
    }
    
    // Get current value
    T get_value() const {
        if (coro_ && !coro_.done()) {
            return coro_.promise().value;
        }
        return {};
    }
};
```

### 5.4 Coroutine Examples

```cpp
// Example coroutine functions
Task<int> fibonacci_task(int n) {
    if (n <= 1) {
        co_return n;
    }
    
    int a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        co_yield a + b;
        int temp = a + b;
        a = b;
        b = temp;
    }
    
    co_return b;
}

Generator<int> fibonacci_generator(int n) {
    int a = 0, b = 1;
    
    if (n >= 1) co_yield a;
    if (n >= 2) co_yield b;
    
    for (int i = 2; i < n; ++i) {
        int temp = a + b;
        a = b;
        b = temp;
        co_yield b;
    }
}
```

## 6. Async/Await Patterns

### 6.1 Async Task

```cpp
// Async task with promise
template<typename T>
class AsyncTask {
private:
    std::promise<T> promise_;
    std::future<T> future_;
    
public:
    AsyncTask() : future_(promise_.get_future()) {}
    
    // Non-copyable
    AsyncTask(const AsyncTask&) = delete;
    AsyncTask& operator=(const AsyncTask&) = delete;
    
    // Movable
    AsyncTask(AsyncTask&& other) noexcept 
        : promise_(std::move(other.promise_)), future_(std::move(other.future_)) {}
    
    AsyncTask& operator=(AsyncTask&& other) noexcept {
        if (this != &other) {
            promise_ = std::move(other.promise_);
            future_ = std::move(other.future_);
        }
        return *this;
    }
    
    // Set result
    void set_result(T value) {
        promise_.set_value(value);
    }
    
    // Set exception
    void set_exception(std::exception_ptr exception) {
        promise_.set_exception(exception);
    }
    
    // Get future
    std::future<T>& get_future() {
        return future_;
    }
    
    // Wait for result
    T get() {
        return future_.get();
    }
    
    // Check if ready
    bool is_ready() const {
        return future_.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
    }
};
```

### 6.2 Async Executor

```cpp
// Async executor
class AsyncExecutor {
private:
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;
    std::mutex tasks_mutex_;
    std::condition_variable tasks_cv_;
    std::atomic<bool> running_;
    
public:
    AsyncExecutor(size_t num_workers = std::thread::hardware_concurrency()) : running_(true) {
        for (size_t i = 0; i < num_workers; ++i) {
            workers_.emplace_back(&AsyncExecutor::worker_loop, this);
        }
    }
    
    ~AsyncExecutor() {
        shutdown();
    }
    
    // Submit task
    template<typename F, typename... Args>
    auto submit(F&& f, Args&&... args) -> AsyncTask<std::invoke_result_t<F, Args...>> {
        using ReturnType = std::invoke_result_t<F, Args...>;
        
        AsyncTask<ReturnType> task;
        
        {
            std::lock_guard<std::mutex> lock(tasks_mutex_);
            tasks_.emplace([task = std::move(task), f = std::forward<F>(f), args...]() mutable {
                try {
                    if constexpr (std::is_void_v<ReturnType>) {
                        f(args...);
                        task.set_result();
                    } else {
                        task.set_result(f(args...));
                    }
                } catch (...) {
                    task.set_exception(std::current_exception());
                }
            });
        }
        
        tasks_cv_.notify_one();
        return task;
    }
    
    // Shutdown executor
    void shutdown() {
        if (running_) {
            running_ = false;
            tasks_cv_.notify_all();
            
            for (auto& worker : workers_) {
                if (worker.joinable()) {
                    worker.join();
                }
            }
        }
    }
    
private:
    void worker_loop() {
        while (running_) {
            std::function<void()> task;
            
            {
                std::unique_lock<std::mutex> lock(tasks_mutex_);
                tasks_cv_.wait(lock, [this] { return !tasks_.empty() || !running_; });
                
                if (!running_) {
                    break;
                }
                
                if (!tasks_.empty()) {
                    task = std::move(tasks_.front());
                    tasks_.pop();
                }
            }
            
            if (task) {
                task();
            }
        }
    }
};
```

### 6.3 Async Operations

```cpp
// Async operations
class AsyncOperations {
private:
    AsyncExecutor executor_;
    
public:
    AsyncOperations() : executor_(4) {}
    
    // Async sleep
    AsyncTask<void> async_sleep(int milliseconds) {
        return executor_.submit([milliseconds]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
        });
    }
    
    // Async computation
    template<typename T>
    AsyncTask<T> async_compute(std::function<T()> computation) {
        return executor_.submit(computation);
    }
    
    // Async file read (simulated)
    AsyncTask<std::string> async_read_file(const std::string& filename) {
        return executor_.submit([filename]() -> std::string {
            // Simulate file reading
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            return "Content of " + filename;
        });
    }
    
    // Async network request (simulated)
    AsyncTask<std::string> async_network_request(const std::string& url) {
        return executor_.submit([url]() -> std::string {
            // Simulate network request
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            return "Response from " + url;
        });
    }
};
```

## 7. Advanced Synchronization Primitives

### 7.1 Read-Write Lock

```cpp
// Read-write lock
class ReadWriteLock {
private:
    std::mutex mutex_;
    std::condition_variable read_cv_;
    std::condition_variable write_cv_;
    int readers_;
    int writers_;
    bool writing_;
    
public:
    ReadWriteLock() : readers_(0), writers_(0), writing_(false) {}
    
    // Read lock
    void read_lock() {
        std::unique_lock<std::mutex> lock(mutex_);
        read_cv_.wait(lock, [this] { return writers_ == 0 && !writing_; });
        ++readers_;
    }
    
    // Read unlock
    void read_unlock() {
        std::lock_guard<std::mutex> lock(mutex_);
        --readers_;
        if (readers_ == 0) {
            write_cv_.notify_one();
        }
    }
    
    // Write lock
    void write_lock() {
        std::unique_lock<std::mutex> lock(mutex_);
        ++writers_;
        write_cv_.wait(lock, [this] { return readers_ == 0 && !writing_; });
        writing_ = true;
    }
    
    // Write unlock
    void write_unlock() {
        std::lock_guard<std::mutex> lock(mutex_);
        writing_ = false;
        --writers_;
        if (writers_ > 0) {
            write_cv_.notify_one();
        } else {
            read_cv_.notify_all();
        }
    }
};
```

### 7.2 RAII Read-Write Lock Wrappers

```cpp
// RAII read lock
class ReadLock {
private:
    ReadWriteLock& rw_lock_;
    
public:
    explicit ReadLock(ReadWriteLock& lock) : rw_lock_(lock) {
        rw_lock_.read_lock();
    }
    
    ~ReadLock() {
        rw_lock_.read_unlock();
    }
    
    // Non-copyable
    ReadLock(const ReadLock&) = delete;
    ReadLock& operator=(const ReadLock&) = delete;
    
    // Non-movable
    ReadLock(ReadLock&&) = delete;
    ReadLock& operator=(ReadLock&&) = delete;
};

// RAII write lock
class WriteLock {
private:
    ReadWriteLock& rw_lock_;
    
public:
    explicit WriteLock(ReadWriteLock& lock) : rw_lock_(lock) {
        rw_lock_.write_lock();
    }
    
    ~WriteLock() {
        rw_lock_.write_unlock();
    }
    
    // Non-copyable
    WriteLock(const WriteLock&) = delete;
    WriteLock& operator=(const WriteLock&) = delete;
    
    // Non-movable
    WriteLock(WriteLock&&) = delete;
    WriteLock& operator=(WriteLock&&) = delete;
};
```

### 7.3 Barrier Synchronization

```cpp
// Barrier synchronization
class Barrier {
private:
    std::mutex mutex_;
    std::condition_variable cv_;
    int count_;
    int waiting_;
    int generation_;
    
public:
    explicit Barrier(int count) : count_(count), waiting_(0), generation_(0) {}
    
    // Wait at barrier
    void wait() {
        std::unique_lock<std::mutex> lock(mutex_);
        int gen = generation_;
        
        ++waiting_;
        
        if (waiting_ == count_) {
            ++generation_;
            waiting_ = 0;
            cv_.notify_all();
        } else {
            cv_.wait(lock, [this, gen] { return gen != generation_; });
        }
    }
};
```

### 7.4 Semaphore

```cpp
// Semaphore
class Semaphore {
private:
    std::mutex mutex_;
    std::condition_variable cv_;
    int count_;
    
public:
    explicit Semaphore(int initial_count = 0) : count_(initial_count) {}
    
    // Acquire (wait)
    void acquire() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this] { return count_ > 0; });
        --count_;
    }
    
    // Release (signal)
    void release() {
        std::lock_guard<std::mutex> lock(mutex_);
        ++count_;
        cv_.notify_one();
    }
    
    // Try acquire
    bool try_acquire() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (count_ > 0) {
            --count_;
            return true;
        }
        return false;
    }
    
    // Get count
    int get_count() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return count_;
    }
};
```

## 8. Best Practices

### 8.1 Concurrency Model Selection

**Actor Model:**
- Use for message-based systems
- Good for fault tolerance
- Suitable for distributed systems
- Natural for event-driven architectures

**Message Passing:**
- Use for loose coupling
- Good for scalability
- Suitable for microservices
- Natural for asynchronous processing

**Coroutines:**
- Use for I/O-bound operations
- Good for cooperative multitasking
- Suitable for generators
- Natural for async programming

### 8.2 Performance Considerations

**Actor Model:**
- Message queue overhead
- Actor creation cost
- Message serialization
- Actor isolation benefits

**Message Passing:**
- Message copying overhead
- Queue management cost
- Network latency (distributed)
- Decoupling benefits

**Coroutines:**
- Stack allocation overhead
- Suspend/resume cost
- Memory efficiency benefits
- I/O optimization benefits

### 8.3 Error Handling

**Actor Model:**
- Handle actor failures
- Implement supervision trees
- Use dead letter queues
- Monitor actor health

**Message Passing:**
- Handle message failures
- Implement retry mechanisms
- Use message acknowledgments
- Monitor message queues

**Coroutines:**
- Handle coroutine exceptions
- Implement proper cleanup
- Use RAII patterns
- Monitor coroutine state

## 9. Common Pitfalls and Solutions

### 9.1 Actor Model Pitfalls

**Problem**: Actor message queue overflow
**Solution**: Implement backpressure and message dropping

**Problem**: Actor deadlocks
**Solution**: Avoid circular message dependencies

**Problem**: Actor memory leaks
**Solution**: Implement proper actor lifecycle management

### 9.2 Message Passing Pitfalls

**Problem**: Message ordering issues
**Solution**: Use sequence numbers and ordering guarantees

**Problem**: Message loss
**Solution**: Implement acknowledgments and retry mechanisms

**Problem**: Message duplication
**Solution**: Use unique message IDs and deduplication

### 9.3 Coroutine Pitfalls

**Problem**: Coroutine stack overflow
**Solution**: Limit coroutine depth and use iterative algorithms

**Problem**: Coroutine memory leaks
**Solution**: Implement proper coroutine cleanup and RAII

**Problem**: Coroutine exception handling
**Solution**: Use proper exception propagation and handling

## 10. Advanced Topics

### 10.1 Distributed Concurrency

**Distributed Actor Systems:**
- Actor location transparency
- Network communication
- Fault tolerance across nodes
- Load balancing

**Distributed Message Passing:**
- Message routing
- Network protocols
- Failure detection
- Consistency guarantees

### 10.2 Performance Optimization

**Actor Model Optimization:**
- Actor pooling
- Message batching
- Actor affinity
- Memory optimization

**Message Passing Optimization:**
- Message compression
- Connection pooling
- Batch processing
- Network optimization

### 10.3 Monitoring and Debugging

**Actor System Monitoring:**
- Actor performance metrics
- Message queue monitoring
- Actor health checks
- System-wide metrics

**Message Passing Monitoring:**
- Message throughput
- Queue depth monitoring
- Network latency
- Error rates

## 11. Summary

Advanced concurrency models provide powerful tools for building scalable and maintainable concurrent systems. Key takeaways include:

1. **Actor model** provides message-based concurrency with isolated state
2. **Message passing** enables communication between concurrent entities
3. **Coroutines** provide cooperative multitasking with suspend/resume semantics
4. **Async/await patterns** simplify asynchronous programming
5. **Advanced synchronization primitives** provide fine-grained control
6. **Read-write locks** optimize for multiple readers and single writer
7. **Barriers** synchronize multiple threads at specific points
8. **Semaphores** control access to shared resources

Effective use of advanced concurrency models requires understanding both the application requirements and the characteristics of different concurrency patterns, combined with proper implementation and testing.

## 12. Exercises

### Exercise 1: Actor System
Implement an actor system with multiple actor types that can communicate through messages, including proper error handling and lifecycle management.

### Exercise 2: Message Passing System
Create a message passing system that supports different message types, routing, and delivery guarantees.

### Exercise 3: Coroutine Generator
Implement a coroutine-based generator for various mathematical sequences (Fibonacci, prime numbers, etc.).

### Exercise 4: Async Operations
Create an async operations framework that can handle I/O operations, computations, and network requests with proper error handling.

### Exercise 5: Synchronization Primitives
Implement and test advanced synchronization primitives including read-write locks, barriers, and semaphores with performance benchmarks.

## 13. Further Reading

- "Concurrency in Action" by Anthony Williams
- "Programming Erlang: Software for a Concurrent World" by Joe Armstrong
- "Reactive Programming with RxJava" by Tomasz Nurkiewicz and Ben Christensen
- "C++ Concurrency in Action" by Anthony Williams
- "Actor Model of Computation" by Carl Hewitt
- "Coroutines in C++20" by Rainer Grimm
- "Asynchronous Programming in C++" by Packt Publishing
