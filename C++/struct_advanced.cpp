/*
 * STRUCT ADVANCED EXAMPLES
 * 
 * This file demonstrates advanced struct concepts including templates, CRTP, move semantics, and metaprogramming:
 * - Advanced concepts and techniques
 * - Real-world applications and patterns
 * - Best practices and optimization
 * - Complex scenarios and edge cases
 * 
 * Learning Objectives:
 * - Master advanced STRUCT concepts
 * - Understand professional coding patterns
 * - Learn optimization techniques
 * - Apply knowledge in complex scenarios
 * - Develop problem-solving skills
 * 
 * Prerequisites:
 * - Solid understanding of basic STRUCT concepts
 * - Familiarity with intermediate C++ features
 * - Understanding of memory management
 * - Knowledge of STL containers and algorithms
 * 
 * Key Topics Covered:
 * - Advanced syntax and features
 * - Performance optimization
 * - Error handling and safety
 * - Modern C++ practices
 * - Real-world applications
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <type_traits>
#include <variant>
#include <any>
#include <optional>
#include <functional>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
using namespace std;

// Advanced struct with CRTP (Curiously Recurring Template Pattern)
template<typename Derived>
struct BaseStruct {
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
    
    void commonFunction() {
        cout << "Common functionality from base" << endl;
    }
};

struct ConcreteStruct : BaseStruct<ConcreteStruct> {
    void implementation() {
        cout << "Concrete implementation" << endl;
    }
};

// Struct with SFINAE (Substitution Failure Is Not An Error)
template<typename T>
struct TypeTraits {
    static constexpr bool is_numeric = is_arithmetic_v<T>;
    static constexpr bool is_pointer = is_pointer_v<T>;
    static constexpr bool is_reference = is_reference_v<T>;
    
    static void printInfo() {
        cout << "Type info - Numeric: " << is_numeric 
             << ", Pointer: " << is_pointer 
             << ", Reference: " << is_reference << endl;
    }
};

// Struct with perfect forwarding
template<typename... Args>
struct PerfectForwardingStruct {
    tuple<Args...> args;
    
    PerfectForwardingStruct(Args&&... args) : args(forward<Args>(args)...) {}
    
    template<size_t Index>
    auto get() -> decltype(get<Index>(args)) {
        return get<Index>(args);
    }
    
    void printAll() {
        printAllImpl(make_index_sequence<sizeof...(Args)>{});
    }
    
private:
    template<size_t... Is>
    void printAllImpl(index_sequence<Is...>) {
        ((cout << "Arg " << Is << ": " << get<Is>(args) << endl), ...);
    }
};

// Struct with RAII and move semantics
class ResourceManager {
private:
    string resourceName;
    bool isAcquired;
    mutex resourceMutex;
    
public:
    ResourceManager(const string& name) : resourceName(name), isAcquired(false) {
        acquire();
    }
    
    ~ResourceManager() {
        release();
    }
    
    // Move constructor
    ResourceManager(ResourceManager&& other) noexcept 
        : resourceName(move(other.resourceName)), 
          isAcquired(other.isAcquired),
          resourceMutex(move(other.resourceMutex)) {
        other.isAcquired = false;
    }
    
    // Move assignment
    ResourceManager& operator=(ResourceManager&& other) noexcept {
        if (this != &other) {
            release();
            resourceName = move(other.resourceName);
            isAcquired = other.isAcquired;
            resourceMutex = move(other.resourceMutex);
            other.isAcquired = false;
        }
        return *this;
    }
    
    // Delete copy constructor and assignment
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    
    void useResource() {
        lock_guard<mutex> lock(resourceMutex);
        if (isAcquired) {
            cout << "Using resource: " << resourceName << endl;
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }
    
private:
    void acquire() {
        lock_guard<mutex> lock(resourceMutex);
        cout << "Acquiring resource: " << resourceName << endl;
        isAcquired = true;
    }
    
    void release() {
        lock_guard<mutex> lock(resourceMutex);
        if (isAcquired) {
            cout << "Releasing resource: " << resourceName << endl;
            isAcquired = false;
        }
    }
};

// Struct with atomic operations
struct AtomicCounter {
    atomic<int> count{0};
    atomic<bool> running{true};
    
    void increment() {
        count.fetch_add(1, memory_order_relaxed);
    }
    
    void decrement() {
        count.fetch_sub(1, memory_order_relaxed);
    }
    
    int getCount() const {
        return count.load(memory_order_relaxed);
    }
    
    void stop() {
        running.store(false, memory_order_relaxed);
    }
    
    bool isRunning() const {
        return running.load(memory_order_relaxed);
    }
};

// Struct with variant (C++17)
struct VariantStruct {
    variant<int, string, double, vector<int>> data;
    
    template<typename T>
    VariantStruct(T&& value) : data(forward<T>(value)) {}
    
    template<typename T>
    bool holds() const {
        return holds_alternative<T>(data);
    }
    
    template<typename T>
    T& get() {
        return get<T>(data);
    }
    
    template<typename T>
    const T& get() const {
        return get<T>(data);
    }
    
    void visit(auto&& visitor) {
        visit(visitor, data);
    }
    
    string toString() const {
        return visit([](const auto& value) -> string {
            if constexpr (is_same_v<decay_t<decltype(value)>, int>) {
                return "int: " + to_string(value);
            } else if constexpr (is_same_v<decay_t<decltype(value)>, string>) {
                return "string: " + value;
            } else if constexpr (is_same_v<decay_t<decltype(value)>, double>) {
                return "double: " + to_string(value);
            } else if constexpr (is_same_v<decay_t<decltype(value)>, vector<int>>) {
                return "vector: [" + to_string(value.size()) + " elements]";
            } else {
                return "unknown type";
            }
        }, data);
    }
};

// Struct with any (C++17)
struct AnyStruct {
    any data;
    
    template<typename T>
    void set(T&& value) {
        data = forward<T>(value);
    }
    
    template<typename T>
    bool is() const {
        return data.type() == typeid(T);
    }
    
    template<typename T>
    T& get() {
        return any_cast<T&>(data);
    }
    
    template<typename T>
    const T& get() const {
        return any_cast<const T&>(data);
    }
    
    string getTypeName() const {
        return data.type().name();
    }
    
    bool hasValue() const {
        return data.has_value();
    }
};

// Struct with optional (C++17)
struct OptionalStruct {
    optional<string> name;
    optional<int> age;
    optional<double> gpa;
    
    void setName(const string& n) { name = n; }
    void setAge(int a) { age = a; }
    void setGpa(double g) { gpa = g; }
    
    void printInfo() const {
        cout << "Name: " << (name ? *name : "Not set") << endl;
        cout << "Age: " << (age ? to_string(*age) : "Not set") << endl;
        cout << "GPA: " << (gpa ? to_string(*gpa) : "Not set") << endl;
    }
    
    bool isComplete() const {
        return name.has_value() && age.has_value() && gpa.has_value();
    }
};

// Struct with concepts (C++20 style simulation)
template<typename T>
concept Numeric = is_arithmetic_v<T>;

template<typename T>
concept Printable = requires(T t) {
    cout << t;
};

template<Numeric T>
struct NumericStruct {
    T value;
    
    NumericStruct(T v) : value(v) {}
    
    auto operator+(const NumericStruct& other) const {
        return NumericStruct{value + other.value};
    }
    
    auto operator*(const NumericStruct& other) const {
        return NumericStruct{value * other.value};
    }
    
    void print() const {
        cout << "Numeric value: " << value << endl;
    }
};

// Struct with coroutines (C++20 simulation)
struct CoroutineStruct {
    struct promise_type {
        int current_value;
        
        CoroutineStruct get_return_object() {
            return CoroutineStruct{coroutine_handle<promise_type>::from_promise(*this)};
        }
        
        suspend_never initial_suspend() { return {}; }
        suspend_never final_suspend() noexcept { return {}; }
        
        void return_void() {}
        
        suspend_always yield_value(int value) {
            current_value = value;
            return {};
        }
        
        void unhandled_exception() {}
    };
    
    coroutine_handle<promise_type> coro;
    
    CoroutineStruct(coroutine_handle<promise_type> h) : coro(h) {}
    
    ~CoroutineStruct() {
        if (coro) coro.destroy();
    }
    
    // Move constructor
    CoroutineStruct(CoroutineStruct&& other) noexcept : coro(other.coro) {
        other.coro = {};
    }
    
    // Move assignment
    CoroutineStruct& operator=(CoroutineStruct&& other) noexcept {
        if (this != &other) {
            if (coro) coro.destroy();
            coro = other.coro;
            other.coro = {};
        }
        return *this;
    }
    
    // Delete copy
    CoroutineStruct(const CoroutineStruct&) = delete;
    CoroutineStruct& operator=(const CoroutineStruct&) = delete;
    
    bool next() {
        if (!coro) return false;
        coro.resume();
        return !coro.done();
    }
    
    int getValue() const {
        return coro ? coro.promise().current_value : 0;
    }
};

// Coroutine generator
CoroutineStruct generateNumbers(int start, int end) {
    for (int i = start; i <= end; ++i) {
        co_yield i;
    }
}

// Struct with reflection (simulation)
struct ReflectiveStruct {
    string name;
    int value;
    double precision;
    
    template<typename Visitor>
    void visitFields(Visitor&& visitor) {
        visitor("name", name);
        visitor("value", value);
        visitor("precision", precision);
    }
    
    void printFields() const {
        cout << "Fields:" << endl;
        cout << "  name: " << name << endl;
        cout << "  value: " << value << endl;
        cout << "  precision: " << precision << endl;
    }
};

int main() {
    cout << "=== STRUCT ADVANCED EXAMPLES ===" << endl << endl;
    
    // Example 1: CRTP
    cout << "1. CRTP (Curiously Recurring Template Pattern):" << endl;
    ConcreteStruct concrete;
    concrete.interface();
    concrete.commonFunction();
    cout << endl;
    
    // Example 2: SFINAE
    cout << "2. SFINAE (Substitution Failure Is Not An Error):" << endl;
    TypeTraits<int>::printInfo();
    TypeTraits<int*>::printInfo();
    TypeTraits<string&>::printInfo();
    cout << endl;
    
    // Example 3: Perfect forwarding
    cout << "3. Perfect Forwarding:" << endl;
    PerfectForwardingStruct pfs(42, "hello", 3.14, vector<int>{1, 2, 3});
    pfs.printAll();
    cout << endl;
    
    // Example 4: RAII and move semantics
    cout << "4. RAII and Move Semantics:" << endl;
    {
        ResourceManager rm1("Database");
        rm1.useResource();
        
        ResourceManager rm2 = move(rm1);
        rm2.useResource();
    }  // Resources automatically released
    cout << endl;
    
    // Example 5: Atomic operations
    cout << "5. Atomic Operations:" << endl;
    AtomicCounter counter;
    
    // Simulate multiple threads
    vector<thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&counter]() {
            while (counter.isRunning()) {
                counter.increment();
                this_thread::sleep_for(chrono::milliseconds(10));
            }
        });
    }
    
    this_thread::sleep_for(chrono::milliseconds(100));
    counter.stop();
    
    for (auto& t : threads) {
        t.join();
    }
    
    cout << "Final count: " << counter.getCount() << endl;
    cout << endl;
    
    // Example 6: Variant
    cout << "6. Variant (C++17):" << endl;
    VariantStruct vs1(42);
    VariantStruct vs2(string("Hello"));
    VariantStruct vs3(3.14);
    VariantStruct vs4(vector<int>{1, 2, 3, 4, 5});
    
    cout << "vs1: " << vs1.toString() << endl;
    cout << "vs2: " << vs2.toString() << endl;
    cout << "vs3: " << vs3.toString() << endl;
    cout << "vs4: " << vs4.toString() << endl;
    cout << endl;
    
    // Example 7: Any
    cout << "7. Any (C++17):" << endl;
    AnyStruct anyStruct;
    anyStruct.set(42);
    cout << "Type: " << anyStruct.getTypeName() << endl;
    cout << "Value: " << anyStruct.get<int>() << endl;
    
    anyStruct.set(string("Hello World"));
    cout << "Type: " << anyStruct.getTypeName() << endl;
    cout << "Value: " << anyStruct.get<string>() << endl;
    cout << endl;
    
    // Example 8: Optional
    cout << "8. Optional (C++17):" << endl;
    OptionalStruct optStruct;
    optStruct.printInfo();
    cout << "Complete: " << (optStruct.isComplete() ? "Yes" : "No") << endl;
    
    optStruct.setName("Alice");
    optStruct.setAge(25);
    optStruct.setGpa(3.8);
    optStruct.printInfo();
    cout << "Complete: " << (optStruct.isComplete() ? "Yes" : "No") << endl;
    cout << endl;
    
    // Example 9: Concepts
    cout << "9. Concepts (C++20 style):" << endl;
    NumericStruct<int> ns1(42);
    NumericStruct<double> ns2(3.14);
    
    ns1.print();
    ns2.print();
    
    auto sum = ns1 + NumericStruct<int>(10);
    sum.print();
    cout << endl;
    
    // Example 10: Coroutines (simulation)
    cout << "10. Coroutines (C++20 simulation):" << endl;
    auto gen = generateNumbers(1, 5);
    while (gen.next()) {
        cout << "Generated: " << gen.getValue() << endl;
    }
    cout << endl;
    
    // Example 11: Reflection (simulation)
    cout << "11. Reflection (simulation):" << endl;
    ReflectiveStruct rs{"Test", 42, 3.14159};
    rs.printFields();
    
    rs.visitFields([](const string& name, const auto& value) {
        cout << "Field " << name << " = " << value << endl;
    });
    
    return 0;
}
