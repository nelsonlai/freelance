/*
 * Lesson 19.1: Advanced Concurrency Models
 * 
 * This file demonstrates advanced concurrency models including
 * actor model, message passing, coroutines, async/await patterns,
 * and advanced synchronization primitives.
 */

#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include <future>
#include <condition_variable>
#include <random>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <cassert>
#include <limits>
#include <array>
#include <tuple>
#include <type_traits>
#include <coroutine>
#include <generator>

// Example 1: Actor Model
namespace ActorModel {
    
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
    
    // Counter actor
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
    
    void demonstrateActorModel() {
        std::cout << "=== Actor Model ===" << std::endl;
        
        ActorSystem system;
        
        // Create counter actors
        auto* counter1 = system.add_actor<CounterActor>("Counter1");
        auto* counter2 = system.add_actor<CounterActor>("Counter2");
        
        // Start all actors
        system.start_all();
        
        // Send messages to actors
        counter1->send_message(std::make_unique<CounterMessage>("increment"));
        counter1->send_message(std::make_unique<CounterMessage>("increment"));
        counter1->send_message(std::make_unique<CounterMessage>("add", 5));
        counter1->send_message(std::make_unique<CounterMessage>("get"));
        
        counter2->send_message(std::make_unique<CounterMessage>("increment"));
        counter2->send_message(std::make_unique<CounterMessage>("add", 10));
        counter2->send_message(std::make_unique<CounterMessage>("get"));
        
        // Wait for messages to be processed
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        std::cout << "Actor system has " << system.get_actor_count() << " actors" << std::endl;
        
        // Stop all actors
        system.stop_all();
    }
}

// Example 2: Message Passing
namespace MessagePassing {
    
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
    
    // Example message handler
    class EchoHandler : public MessageHandler {
    public:
        void handle_message(const std::string& from, const std::string& type, const std::string& data) override {
            std::cout << "EchoHandler received from " << from << " [" << type << "]: " << data << std::endl;
        }
    };
    
    void demonstrateMessagePassing() {
        std::cout << "\n=== Message Passing ===" << std::endl;
        
        MessagePassingSystem system;
        system.start();
        
        // Create processes with handlers
        auto process1 = std::make_unique<MessageProcess>("Process1", &system, std::make_unique<EchoHandler>());
        auto process2 = std::make_unique<MessageProcess>("Process2", &system, std::make_unique<EchoHandler>());
        
        process1->start();
        process2->start();
        
        // Send messages between processes
        process1->send_message("Process2", "greeting", "Hello from Process1!");
        process2->send_message("Process1", "response", "Hello back from Process2!");
        
        process1->send_message("Process2", "data", "Some important data");
        process2->send_message("Process1", "ack", "Data received");
        
        // Wait for messages to be processed
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        // Stop processes
        process1->stop();
        process2->stop();
        
        system.stop();
    }
}

// Example 3: Coroutines (C++20)
namespace Coroutines {
    
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
    
    void demonstrateCoroutines() {
        std::cout << "\n=== Coroutines ===" << std::endl;
        
        // Test task coroutine
        std::cout << "Fibonacci task (10):" << std::endl;
        auto task = fibonacci_task(10);
        
        while (!task.done()) {
            if (task.resume()) {
                std::cout << "Yielded: " << task.get_value() << std::endl;
            }
        }
        
        std::cout << "Final result: " << task.get_value() << std::endl;
        
        // Test generator coroutine
        std::cout << "\nFibonacci generator (10):" << std::endl;
        auto generator = fibonacci_generator(10);
        
        for (int value : generator) {
            std::cout << "Generated: " << value << std::endl;
        }
    }
}

// Example 4: Async/Await Patterns
namespace AsyncAwait {
    
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
    
    void demonstrateAsyncAwait() {
        std::cout << "\n=== Async/Await Patterns ===" << std::endl;
        
        AsyncOperations async_ops;
        
        // Start multiple async operations
        auto sleep_task = async_ops.async_sleep(1000);
        auto compute_task = async_ops.async_compute<int>([]() { return 42 * 2; });
        auto file_task = async_ops.async_read_file("test.txt");
        auto network_task = async_ops.async_network_request("http://example.com");
        
        std::cout << "Started multiple async operations" << std::endl;
        
        // Wait for results
        try {
            compute_task.get();
            std::cout << "Computation result: " << compute_task.get() << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Computation error: " << e.what() << std::endl;
        }
        
        try {
            std::string file_content = file_task.get();
            std::cout << "File content: " << file_content << std::endl;
        } catch (const std::exception& e) {
            std::cout << "File read error: " << e.what() << std::endl;
        }
        
        try {
            std::string network_response = network_task.get();
            std::cout << "Network response: " << network_response << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Network error: " << e.what() << std::endl;
        }
        
        try {
            sleep_task.get();
            std::cout << "Sleep completed" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Sleep error: " << e.what() << std::endl;
        }
        
        std::cout << "All async operations completed" << std::endl;
    }
}

// Example 5: Advanced Synchronization Primitives
namespace AdvancedSynchronization {
    
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
    
    void demonstrateAdvancedSynchronization() {
        std::cout << "\n=== Advanced Synchronization Primitives ===" << std::endl;
        
        // Test read-write lock
        ReadWriteLock rw_lock;
        std::vector<int> shared_data = {1, 2, 3, 4, 5};
        
        std::vector<std::thread> threads;
        
        // Reader threads
        for (int i = 0; i < 3; ++i) {
            threads.emplace_back([&rw_lock, &shared_data, i]() {
                ReadLock lock(rw_lock);
                std::cout << "Reader " << i << " reading data: ";
                for (int value : shared_data) {
                    std::cout << value << " ";
                }
                std::cout << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            });
        }
        
        // Writer thread
        threads.emplace_back([&rw_lock, &shared_data]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            WriteLock lock(rw_lock);
            std::cout << "Writer modifying data" << std::endl;
            for (int& value : shared_data) {
                value *= 2;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        });
        
        for (auto& thread : threads) {
            thread.join();
        }
        
        // Test barrier
        Barrier barrier(3);
        std::cout << "\nTesting barrier with 3 threads:" << std::endl;
        
        for (int i = 0; i < 3; ++i) {
            threads.emplace_back([&barrier, i]() {
                std::cout << "Thread " << i << " reached barrier" << std::endl;
                barrier.wait();
                std::cout << "Thread " << i << " passed barrier" << std::endl;
            });
        }
        
        for (auto& thread : threads) {
            thread.join();
        }
        
        // Test semaphore
        Semaphore semaphore(2);
        std::cout << "\nTesting semaphore with 5 threads:" << std::endl;
        
        threads.clear();
        for (int i = 0; i < 5; ++i) {
            threads.emplace_back([&semaphore, i]() {
                semaphore.acquire();
                std::cout << "Thread " << i << " acquired semaphore" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                semaphore.release();
                std::cout << "Thread " << i << " released semaphore" << std::endl;
            });
        }
        
        for (auto& thread : threads) {
            thread.join();
        }
    }
}

int main() {
    std::cout << "=== Advanced Concurrency Models Demonstration ===" << std::endl;
    std::cout << "This program demonstrates advanced concurrency models including\n"
              << "actor model, message passing, coroutines, async/await patterns,\n"
              << "and advanced synchronization primitives.\n" << std::endl;
    
    // Demonstrate various concurrency models
    ActorModel::demonstrateActorModel();
    MessagePassing::demonstrateMessagePassing();
    Coroutines::demonstrateCoroutines();
    AsyncAwait::demonstrateAsyncAwait();
    AdvancedSynchronization::demonstrateAdvancedSynchronization();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Actor model provides message-based concurrency with isolated state" << std::endl;
    std::cout << "2. Message passing enables communication between concurrent entities" << std::endl;
    std::cout << "3. Coroutines provide cooperative multitasking with suspend/resume semantics" << std::endl;
    std::cout << "4. Async/await patterns simplify asynchronous programming" << std::endl;
    std::cout << "5. Advanced synchronization primitives provide fine-grained control" << std::endl;
    std::cout << "6. Read-write locks optimize for multiple readers and single writer" << std::endl;
    std::cout << "7. Barriers synchronize multiple threads at specific points" << std::endl;
    std::cout << "8. Semaphores control access to shared resources" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++20 -Wall -Wextra -O2 -pthread -o advanced_concurrency_models 01_Advanced_Concurrency_Models.cpp
 * 
 * Using Clang:
 * clang++ -std=c++20 -Wall -Wextra -O2 -pthread -o advanced_concurrency_models 01_Advanced_Concurrency_Models.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++20 /EHsc /O2 01_Advanced_Concurrency_Models.cpp
 * 
 * Running:
 * ./advanced_concurrency_models (Linux/macOS)
 * advanced_concurrency_models.exe (Windows)
 * 
 * Note: This lesson requires C++20 for coroutines.
 * C++17 is the minimum required version for other features.
 * 
 * Advanced Concurrency Models Notes:
 * - Actor model provides message-based concurrency with isolated state
 * - Message passing enables communication between concurrent entities
 * - Coroutines provide cooperative multitasking with suspend/resume semantics
 * - Async/await patterns simplify asynchronous programming
 * - Advanced synchronization primitives provide fine-grained control
 * - Read-write locks optimize for multiple readers and single writer
 * - Barriers synchronize multiple threads at specific points
 * - Semaphores control access to shared resources
 */"""
