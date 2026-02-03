/*
 * TEMPLATE ADVANCED EXAMPLES
 * 
 * This file demonstrates advanced template concepts including metaprogramming, type traits, and expression templates:
 * - Advanced concepts and techniques
 * - Real-world applications and patterns
 * - Best practices and optimization
 * - Complex scenarios and edge cases
 * 
 * Learning Objectives:
 * - Master advanced TEMPLATE concepts
 * - Understand professional coding patterns
 * - Learn optimization techniques
 * - Apply knowledge in complex scenarios
 * - Develop problem-solving skills
 * 
 * Prerequisites:
 * - Solid understanding of basic TEMPLATE concepts
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
#include <type_traits>
#include <memory>
#include <algorithm>
#include <functional>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <variant>
#include <any>
#include <optional>
using namespace std;

// Advanced SFINAE with enable_if
template<typename T>
typename enable_if<is_arithmetic<T>::value, T>::type
safeDivide(T a, T b) {
    if (b == 0) {
        throw invalid_argument("Division by zero");
    }
    return a / b;
}

template<typename T>
typename enable_if<!is_arithmetic<T>::value, string>::type
safeDivide(T a, T b) {
    return "Cannot divide non-arithmetic types";
}

// Template with concepts (C++20 style simulation)
template<typename T>
concept Numeric = is_arithmetic_v<T>;

template<typename T>
concept Printable = requires(T t) {
    cout << t;
};

template<Numeric T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

template<Printable T>
void printValue(T value) {
    cout << "Value: " << value << endl;
}

// Advanced template metaprogramming
template<int N>
struct PowerOf2 {
    static const int value = 2 * PowerOf2<N - 1>::value;
};

template<>
struct PowerOf2<0> {
    static const int value = 1;
};

// Template with type lists
template<typename... Types>
struct TypeList {};

template<typename List>
struct Size;

template<typename... Types>
struct Size<TypeList<Types...>> {
    static const size_t value = sizeof...(Types);
};

// Template with type at index
template<typename List, size_t Index>
struct TypeAt;

template<typename Head, typename... Tail, size_t Index>
struct TypeAt<TypeList<Head, Tail...>, Index> {
    using type = typename TypeAt<TypeList<Tail...>, Index - 1>::type;
};

template<typename Head, typename... Tail>
struct TypeAt<TypeList<Head, Tail...>, 0> {
    using type = Head;
};

// Template with conditional compilation
template<typename T>
struct IsPointer {
    static const bool value = false;
};

template<typename T>
struct IsPointer<T*> {
    static const bool value = true;
};

// Template with perfect forwarding and variadic
template<typename... Args>
class PerfectForwardingClass {
private:
    tuple<Args...> args;
    
public:
    PerfectForwardingClass(Args&&... args) : args(forward<Args>(args)...) {}
    
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

// Template with CRTP and polymorphism
template<typename Derived>
class BaseCRTP {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
    
    void commonFunction() {
        cout << "Common functionality from base" << endl;
    }
    
    // Virtual function for polymorphism
    virtual void virtualFunction() {
        cout << "Base virtual function" << endl;
    }
    
    virtual ~BaseCRTP() = default;
};

class ConcreteCRTP : public BaseCRTP<ConcreteCRTP> {
public:
    void implementation() {
        cout << "Concrete implementation" << endl;
    }
    
    void virtualFunction() override {
        cout << "Concrete virtual function" << endl;
    }
};

// Template with policy-based design
template<typename T, typename Allocator = allocator<T>>
class PolicyBasedVector {
private:
    vector<T, Allocator> data;
    
public:
    void push_back(const T& value) {
        data.push_back(value);
    }
    
    void push_back(T&& value) {
        data.push_back(move(value));
    }
    
    T& operator[](size_t index) {
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        return data[index];
    }
    
    size_t size() const { return data.size(); }
    
    void display() const {
        for (const auto& item : data) {
            cout << item << " ";
        }
        cout << endl;
    }
};

// Template with expression templates
template<typename T>
class Vector {
private:
    vector<T> data;
    
public:
    Vector(size_t size) : data(size) {}
    
    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }
    
    size_t size() const { return data.size(); }
    
    template<typename Expr>
    Vector& operator=(const Expr& expr) {
        for (size_t i = 0; i < size(); ++i) {
            data[i] = expr[i];
        }
        return *this;
    }
};

template<typename LHS, typename RHS>
class VectorAdd {
private:
    const LHS& lhs;
    const RHS& rhs;
    
public:
    VectorAdd(const LHS& l, const RHS& r) : lhs(l), rhs(r) {}
    
    T operator[](size_t index) const {
        return lhs[index] + rhs[index];
    }
};

template<typename T>
Vector<T> operator+(const Vector<T>& lhs, const Vector<T>& rhs) {
    return VectorAdd<Vector<T>, Vector<T>>(lhs, rhs);
}

// Template with type erasure
template<typename... Types>
class TypeEraser {
private:
    variant<Types...> data;
    
public:
    template<typename T>
    TypeEraser(T&& value) : data(forward<T>(value)) {}
    
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
    
    template<typename Visitor>
    auto visit(Visitor&& visitor) {
        return std::visit(forward<Visitor>(visitor), data);
    }
    
    template<typename Visitor>
    auto visit(Visitor&& visitor) const {
        return std::visit(forward<Visitor>(visitor), data);
    }
};

// Template with reflection (simulation)
template<typename T>
struct Reflection {
    static string getTypeName() {
        return typeid(T).name();
    }
    
    static bool isNumeric() {
        return is_arithmetic_v<T>;
    }
    
    static bool isPointer() {
        return is_pointer_v<T>;
    }
    
    static bool isReference() {
        return is_reference_v<T>;
    }
    
    static void printInfo() {
        cout << "Type: " << getTypeName() << endl;
        cout << "Numeric: " << isNumeric() << endl;
        cout << "Pointer: " << isPointer() << endl;
        cout << "Reference: " << isReference() << endl;
    }
};

// Template with performance monitoring
template<typename T>
class MonitoredTemplate {
private:
    T data;
    atomic<size_t> accessCount{0};
    atomic<size_t> modificationCount{0};
    
public:
    MonitoredTemplate(T value) : data(value) {}
    
    T get() const {
        accessCount.fetch_add(1, memory_order_relaxed);
        return data;
    }
    
    void set(T value) {
        data = value;
        modificationCount.fetch_add(1, memory_order_relaxed);
    }
    
    size_t getAccessCount() const {
        return accessCount.load(memory_order_relaxed);
    }
    
    size_t getModificationCount() const {
        return modificationCount.load(memory_order_relaxed);
    }
    
    void printStats() const {
        cout << "Access count: " << getAccessCount() << endl;
        cout << "Modification count: " << getModificationCount() << endl;
    }
};

// Template with thread safety
template<typename T>
class ThreadSafeTemplate {
private:
    T data;
    mutable mutex dataMutex;
    
public:
    ThreadSafeTemplate(T value) : data(value) {}
    
    T get() const {
        lock_guard<mutex> lock(dataMutex);
        return data;
    }
    
    void set(T value) {
        lock_guard<mutex> lock(dataMutex);
        data = value;
    }
    
    template<typename F>
    auto apply(F&& func) -> decltype(func(data)) {
        lock_guard<mutex> lock(dataMutex);
        return func(data);
    }
};

// Template with caching
template<typename T, typename Key = T>
class CachedTemplate {
private:
    map<Key, T> cache;
    mutex cacheMutex;
    
public:
    template<typename F>
    T getOrCompute(const Key& key, F&& computeFunc) {
        {
            lock_guard<mutex> lock(cacheMutex);
            auto it = cache.find(key);
            if (it != cache.end()) {
                return it->second;
            }
        }
        
        T result = computeFunc();
        
        {
            lock_guard<mutex> lock(cacheMutex);
            cache[key] = result;
        }
        
        return result;
    }
    
    size_t cacheSize() const {
        lock_guard<mutex> lock(cacheMutex);
        return cache.size();
    }
};

// Template with move semantics
template<typename T>
class MoveableTemplate {
private:
    T data;
    
public:
    MoveableTemplate(T value) : data(move(value)) {}
    
    MoveableTemplate(MoveableTemplate&& other) noexcept : data(move(other.data)) {}
    
    MoveableTemplate& operator=(MoveableTemplate&& other) noexcept {
        if (this != &other) {
            data = move(other.data);
        }
        return *this;
    }
    
    T& get() { return data; }
    const T& get() const { return data; }
    
    void set(T value) { data = move(value); }
};

// Template with exception safety
template<typename T>
class ExceptionSafeTemplate {
private:
    T data;
    
public:
    ExceptionSafeTemplate(T value) noexcept(noexcept(T(value))) : data(value) {}
    
    T get() const noexcept {
        return data;
    }
    
    void set(T value) noexcept(noexcept(data = value)) {
        data = value;
    }
    
    template<typename F>
    auto apply(F&& func) -> decltype(func(data)) {
        try {
            return func(data);
        } catch (...) {
            throw;
        }
    }
};

int main() {
    cout << "=== TEMPLATE ADVANCED EXAMPLES ===" << endl << endl;
    
    // Example 1: Advanced SFINAE
    cout << "1. Advanced SFINAE:" << endl;
    cout << "10 / 2 = " << safeDivide(10, 2) << endl;
    cout << "15.0 / 3.0 = " << safeDivide(15.0, 3.0) << endl;
    cout << "String division: " << safeDivide(string("hello"), string("world")) << endl;
    cout << endl;
    
    // Example 2: Concepts (C++20 style)
    cout << "2. Concepts (C++20 style):" << endl;
    cout << "Max of 5 and 10: " << maximum(5, 10) << endl;
    cout << "Max of 3.14 and 2.71: " << maximum(3.14, 2.71) << endl;
    
    printValue(42);
    printValue(string("Hello World"));
    cout << endl;
    
    // Example 3: Advanced metaprogramming
    cout << "3. Advanced Metaprogramming:" << endl;
    cout << "2^0 = " << PowerOf2<0>::value << endl;
    cout << "2^5 = " << PowerOf2<5>::value << endl;
    cout << "2^10 = " << PowerOf2<10>::value << endl;
    cout << endl;
    
    // Example 4: Type lists
    cout << "4. Type Lists:" << endl;
    using MyTypes = TypeList<int, string, double, char>;
    cout << "Type list size: " << Size<MyTypes>::value << endl;
    cout << "Type at index 0: " << typeid(TypeAt<MyTypes, 0>::type).name() << endl;
    cout << "Type at index 1: " << typeid(TypeAt<MyTypes, 1>::type).name() << endl;
    cout << endl;
    
    // Example 5: Conditional compilation
    cout << "5. Conditional Compilation:" << endl;
    cout << "Is int* a pointer: " << IsPointer<int*>::value << endl;
    cout << "Is int a pointer: " << IsPointer<int>::value << endl;
    cout << "Is string* a pointer: " << IsPointer<string*>::value << endl;
    cout << endl;
    
    // Example 6: Perfect forwarding
    cout << "6. Perfect Forwarding:" << endl;
    PerfectForwardingClass pfc(42, string("Hello"), 3.14);
    pfc.printAll();
    cout << endl;
    
    // Example 7: CRTP with polymorphism
    cout << "7. CRTP with Polymorphism:" << endl;
    ConcreteCRTP concrete;
    concrete.interface();
    concrete.commonFunction();
    concrete.virtualFunction();
    cout << endl;
    
    // Example 8: Policy-based design
    cout << "8. Policy-based Design:" << endl;
    PolicyBasedVector<int> pbv;
    pbv.push_back(10);
    pbv.push_back(20);
    pbv.push_back(30);
    pbv.display();
    cout << endl;
    
    // Example 9: Type erasure
    cout << "9. Type Erasure:" << endl;
    TypeEraser<int, string, double> te1(42);
    TypeEraser<int, string, double> te2(string("Hello"));
    TypeEraser<int, string, double> te3(3.14);
    
    te1.visit([](const auto& value) { cout << "Value: " << value << endl; });
    te2.visit([](const auto& value) { cout << "Value: " << value << endl; });
    te3.visit([](const auto& value) { cout << "Value: " << value << endl; });
    cout << endl;
    
    // Example 10: Reflection
    cout << "10. Reflection:" << endl;
    Reflection<int>::printInfo();
    cout << endl;
    Reflection<string>::printInfo();
    cout << endl;
    
    // Example 11: Performance monitoring
    cout << "11. Performance Monitoring:" << endl;
    MonitoredTemplate<int> mt(42);
    
    for (int i = 0; i < 10; ++i) {
        mt.get();
    }
    
    mt.set(100);
    mt.set(200);
    
    mt.printStats();
    cout << endl;
    
    // Example 12: Thread safety
    cout << "12. Thread Safety:" << endl;
    ThreadSafeTemplate<int> tst(42);
    
    vector<thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&tst, i]() {
            tst.set(i * 10);
            cout << "Thread " << i << ": " << tst.get() << endl;
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    cout << endl;
    
    // Example 13: Caching
    cout << "13. Caching:" << endl;
    CachedTemplate<int, int> cache;
    
    auto computeFunc = []() {
        cout << "Computing..." << endl;
        return 42;
    };
    
    cout << "First call: " << cache.getOrCompute(1, computeFunc) << endl;
    cout << "Second call: " << cache.getOrCompute(1, computeFunc) << endl;
    cout << "Cache size: " << cache.cacheSize() << endl;
    cout << endl;
    
    // Example 14: Move semantics
    cout << "14. Move Semantics:" << endl;
    MoveableTemplate<string> mt1("Hello");
    MoveableTemplate<string> mt2 = move(mt1);
    
    cout << "Moved value: " << mt2.get() << endl;
    cout << endl;
    
    // Example 15: Exception safety
    cout << "15. Exception Safety:" << endl;
    ExceptionSafeTemplate<int> est(42);
    
    try {
        cout << "Value: " << est.get() << endl;
        est.set(100);
        cout << "New value: " << est.get() << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    return 0;
}
