#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <thread>
#include <future>
#include <atomic>
#include <coroutine>

// Demonstrates advanced C++ topics
int main() {
    std::cout << "Advanced Topics Demonstration" << std::endl;
    std::cout << "=============================" << std::endl;
    
    // 1. Coroutines (C++20)
    std::cout << "\n1. COROUTINES (C++20):" << std::endl;
    
    // Simple coroutine generator
    template<typename T>
    struct Generator {
        struct promise_type {
            T current_value;
            
            Generator get_return_object() {
                return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
            }
            
            std::suspend_always initial_suspend() { return {}; }
            std::suspend_always final_suspend() noexcept { return {}; }
            
            std::suspend_always yield_value(T value) {
                current_value = value;
                return {};
            }
            
            void return_void() {}
            void unhandled_exception() {}
        };
        
        std::coroutine_handle<promise_type> coro;
        
        Generator(std::coroutine_handle<promise_type> h) : coro(h) {}
        
        ~Generator() {
            if (coro) coro.destroy();
        }
        
        bool next() {
            coro.resume();
            return !coro.done();
        }
        
        T value() const {
            return coro.promise().current_value;
        }
    };
    
    // Fibonacci generator
    Generator<int> fibonacci() {
        int a = 0, b = 1;
        while (true) {
            co_yield a;
            auto temp = a + b;
            a = b;
            b = temp;
        }
    }
    
    std::cout << "  Fibonacci sequence: ";
    auto fib = fibonacci();
    for (int i = 0; i < 10; ++i) {
        if (fib.next()) {
            std::cout << fib.value() << " ";
        }
    }
    std::cout << std::endl;
    
    // 2. Modules (C++20)
    std::cout << "\n2. MODULES (C++20):" << std::endl;
    std::cout << "  Modules provide a new way to organize code" << std::endl;
    std::cout << "  Example module structure:" << std::endl;
    std::cout << "    module math;" << std::endl;
    std::cout << "    export int add(int a, int b) { return a + b; }" << std::endl;
    std::cout << "    import math;" << std::endl;
    std::cout << "    int result = add(5, 3);" << std::endl;
    
    // 3. Ranges (C++20)
    std::cout << "\n3. RANGES (C++20):" << std::endl;
    
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Using ranges (if available)
    #if __cpp_lib_ranges >= 201911L
    std::cout << "  Ranges available - using modern syntax" << std::endl;
    #else
    std::cout << "  Ranges not available - using traditional syntax" << std::endl;
    #endif
    
    // Traditional approach
    std::vector<int> even_numbers;
    std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(even_numbers),
                 [](int n) { return n % 2 == 0; });
    
    std::cout << "  Even numbers: ";
    for (int n : even_numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    
    // 4. Concepts (C++20)
    std::cout << "\n4. CONCEPTS (C++20):" << std::endl;
    
    // Define concepts
    template<typename T>
    concept Addable = requires(T a, T b) {
        a + b;
    };
    
    template<typename T>
    concept Printable = requires(T t) {
        std::cout << t;
    };
    
    // Use concepts
    template<Addable T>
    T add_concept(T a, T b) {
        return a + b;
    }
    
    template<Printable T>
    void print_concept(T value) {
        std::cout << "  Concept value: " << value << std::endl;
    }
    
    std::cout << "  Add concept result: " << add_concept(5, 3) << std::endl;
    print_concept(42);
    
    // 5. Three-way Comparison (C++20)
    std::cout << "\n5. THREE-WAY COMPARISON (C++20):" << std::endl;
    
    class Comparable {
    private:
        int value;
        
    public:
        Comparable(int v) : value(v) {}
        
        auto operator<=>(const Comparable& other) const = default;
        
        int get_value() const { return value; }
    };
    
    Comparable a(5), b(3), c(5);
    
    std::cout << "  a < b: " << (a < b) << std::endl;
    std::cout << "  a > b: " << (a > b) << std::endl;
    std::cout << "  a == c: " << (a == c) << std::endl;
    
    // 6. Designated Initializers (C++20)
    std::cout << "\n6. DESIGNATED INITIALIZERS (C++20):" << std::endl;
    
    struct Point {
        int x, y, z;
    };
    
    // Designated initializers
    Point p{.x = 1, .y = 2, .z = 3};
    std::cout << "  Point: (" << p.x << ", " << p.y << ", " << p.z << ")" << std::endl;
    
    // 7. Lambda Improvements
    std::cout << "\n7. LAMBDA IMPROVEMENTS:" << std::endl;
    
    // Lambda with template parameters (C++20)
    auto lambda_template = []<typename T>(T value) {
        return value * 2;
    };
    
    std::cout << "  Lambda template int: " << lambda_template(5) << std::endl;
    std::cout << "  Lambda template double: " << lambda_template(2.5) << std::endl;
    
    // Lambda with capture initialization
    int multiplier = 3;
    auto lambda_capture = [multiplier = multiplier * 2](int x) {
        return x * multiplier;
    };
    
    std::cout << "  Lambda capture result: " << lambda_capture(5) << std::endl;
    
    // 8. Smart Pointers Advanced Usage
    std::cout << "\n8. SMART POINTERS ADVANCED USAGE:" << std::endl;
    
    // Custom deleter
    auto custom_deleter = [](int* ptr) {
        std::cout << "  Custom deleter called" << std::endl;
        delete ptr;
    };
    
    std::unique_ptr<int, decltype(custom_deleter)> custom_ptr(new int(42), custom_deleter);
    std::cout << "  Custom pointer value: " << *custom_ptr << std::endl;
    
    // Shared pointer with custom deleter
    auto shared_deleter = [](int* ptr) {
        std::cout << "  Shared deleter called" << std::endl;
        delete ptr;
    };
    
    std::shared_ptr<int> shared_custom(new int(100), shared_deleter);
    std::cout << "  Shared custom pointer value: " << *shared_custom << std::endl;
    
    // 9. Memory Management Advanced
    std::cout << "\n9. MEMORY MANAGEMENT ADVANCED:" << std::endl;
    
    // Aligned allocation
    auto aligned_ptr = std::aligned_alloc(64, 1024);
    if (aligned_ptr) {
        std::cout << "  Aligned allocation successful" << std::endl;
        std::free(aligned_ptr);
    }
    
    // Memory mapping simulation
    class MemoryPool {
    private:
        char* memory;
        size_t size;
        size_t offset;
        
    public:
        MemoryPool(size_t s) : size(s), offset(0) {
            memory = static_cast<char*>(std::aligned_alloc(64, size));
        }
        
        ~MemoryPool() {
            std::free(memory);
        }
        
        void* allocate(size_t bytes) {
            if (offset + bytes > size) {
                return nullptr;
            }
            void* ptr = memory + offset;
            offset += bytes;
            return ptr;
        }
        
        void reset() {
            offset = 0;
        }
    };
    
    MemoryPool pool(1024);
    int* pool_int = static_cast<int*>(pool.allocate(sizeof(int)));
    if (pool_int) {
        *pool_int = 42;
        std::cout << "  Pool allocated value: " << *pool_int << std::endl;
    }
    
    // 10. Advanced Concurrency
    std::cout << "\n10. ADVANCED CONCURRENCY:" << std::endl;
    
    // Atomic operations with memory ordering
    std::atomic<int> atomic_counter(0);
    std::atomic<bool> atomic_flag(false);
    
    // Memory ordering
    atomic_counter.store(42, std::memory_order_relaxed);
    atomic_flag.store(true, std::memory_order_release);
    
    std::cout << "  Atomic counter: " << atomic_counter.load(std::memory_order_acquire) << std::endl;
    std::cout << "  Atomic flag: " << atomic_flag.load(std::memory_order_relaxed) << std::endl;
    
    // Lock-free data structure
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
    };
    
    LockFreeStack<int> lock_free_stack;
    lock_free_stack.push(1);
    lock_free_stack.push(2);
    lock_free_stack.push(3);
    
    int value;
    std::cout << "  Lock-free stack: ";
    while (lock_free_stack.pop(value)) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
    
    // 11. Template Metaprogramming Advanced
    std::cout << "\n11. TEMPLATE METAPROGRAMMING ADVANCED:" << std::endl;
    
    // Type list manipulation
    template<typename... Types>
    struct TypeList {};
    
    template<typename List>
    struct Size;
    
    template<typename... Types>
    struct Size<TypeList<Types...>> {
        static const size_t value = sizeof...(Types);
    };
    
    using IntList = TypeList<int, double, std::string>;
    std::cout << "  Type list size: " << Size<IntList>::value << std::endl;
    
    // Compile-time string
    template<char... Chars>
    struct String {
        static constexpr char value[] = {Chars..., '\0'};
    };
    
    using HelloString = String<'H', 'e', 'l', 'l', 'o'>;
    std::cout << "  Compile-time string: " << HelloString::value << std::endl;
    
    // 12. Reflection (Future C++)
    std::cout << "\n12. REFLECTION (FUTURE C++):" << std::endl;
    std::cout << "  Reflection will allow runtime inspection of types" << std::endl;
    std::cout << "  Example (hypothetical):" << std::endl;
    std::cout << "    struct Point { int x, y; };" << std::endl;
    std::cout << "    auto fields = reflect(Point{});" << std::endl;
    std::cout << "    for (auto field : fields) {" << std::endl;
    std::cout << "      std::cout << field.name << std::endl;" << std::endl;
    std::cout << "    }" << std::endl;
    
    // 13. Networking (Future C++)
    std::cout << "\n13. NETWORKING (FUTURE C++):" << std::endl;
    std::cout << "  Networking library will provide:" << std::endl;
    std::cout << "    - TCP/UDP sockets" << std::endl;
    std::cout << "    - HTTP client/server" << std::endl;
    std::cout << "    - Asynchronous I/O" << std::endl;
    std::cout << "    - Coroutine integration" << std::endl;
    
    // 14. Graphics (Future C++)
    std::cout << "\n14. GRAPHICS (FUTURE C++):" << std::endl;
    std::cout << "  Graphics library will provide:" << std::endl;
    std::cout << "    - 2D/3D rendering" << std::endl;
    std::cout << "    - Shader support" << std::endl;
    std::cout << "    - GPU compute" << std::endl;
    std::cout << "    - Cross-platform graphics" << std::endl;
    
    // 15. Performance Optimization
    std::cout << "\n15. PERFORMANCE OPTIMIZATION:" << std::endl;
    
    // Branch prediction
    std::vector<int> sorted_data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> unsorted_data = {5, 2, 8, 1, 9, 3, 7, 4, 6, 10};
    
    auto start = std::chrono::high_resolution_clock::now();
    
    int sum_sorted = 0;
    for (int value : sorted_data) {
        if (value > 5) {
            sum_sorted += value;
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto sorted_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    start = std::chrono::high_resolution_clock::now();
    
    int sum_unsorted = 0;
    for (int value : unsorted_data) {
        if (value > 5) {
            sum_unsorted += value;
        }
    }
    
    end = std::chrono::high_resolution_clock::now();
    auto unsorted_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    std::cout << "  Sorted data time: " << sorted_time.count() << " ns" << std::endl;
    std::cout << "  Unsorted data time: " << unsorted_time.count() << " ns" << std::endl;
    std::cout << "  Branch prediction speedup: " << (double)unsorted_time.count() / sorted_time.count() << "x" << std::endl;
    
    // Cache optimization
    const int matrix_size = 1000;
    std::vector<std::vector<int>> matrix(matrix_size, std::vector<int>(matrix_size, 1));
    
    // Row-major access (cache-friendly)
    start = std::chrono::high_resolution_clock::now();
    
    int sum_row_major = 0;
    for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
            sum_row_major += matrix[i][j];
        }
    }
    
    end = std::chrono::high_resolution_clock::now();
    auto row_major_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Column-major access (cache-unfriendly)
    start = std::chrono::high_resolution_clock::now();
    
    int sum_col_major = 0;
    for (int j = 0; j < matrix_size; ++j) {
        for (int i = 0; i < matrix_size; ++i) {
            sum_col_major += matrix[i][j];
        }
    }
    
    end = std::chrono::high_resolution_clock::now();
    auto col_major_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "  Row-major time: " << row_major_time.count() << " μs" << std::endl;
    std::cout << "  Column-major time: " << col_major_time.count() << " μs" << std::endl;
    std::cout << "  Cache optimization speedup: " << (double)col_major_time.count() / row_major_time.count() << "x" << std::endl;
    
    std::cout << "\nAdvanced topics demonstration completed!" << std::endl;
    return 0;
}
