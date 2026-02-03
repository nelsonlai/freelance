/*
 * UNION ADVANCED EXAMPLES
 * 
 * This file demonstrates advanced union concepts including std::variant, type erasure, and perfect forwarding:
 * - Advanced concepts and techniques
 * - Real-world applications and patterns
 * - Best practices and optimization
 * - Complex scenarios and edge cases
 * 
 * Learning Objectives:
 * - Master advanced UNION concepts
 * - Understand professional coding patterns
 * - Learn optimization techniques
 * - Apply knowledge in complex scenarios
 * - Develop problem-solving skills
 * 
 * Prerequisites:
 * - Solid understanding of basic UNION concepts
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
#include <algorithm>
#include <random>
#include <cstring>
#include <bit>
using namespace std;

// Advanced union with type erasure
template<typename... Types>
class TypeErasedUnion {
private:
    using VariantType = variant<Types...>;
    VariantType data;
    
public:
    template<typename T>
    TypeErasedUnion(T&& value) : data(forward<T>(value)) {}
    
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
    
    size_t index() const {
        return data.index();
    }
    
    string typeName() const {
        return visit([](const auto& value) -> string {
            return typeid(decltype(value)).name();
        });
    }
};

// Union with memory layout control
template<typename T>
struct MemoryLayoutUnion {
    union {
        T value;
        char bytes[sizeof(T)];
    };
    
    MemoryLayoutUnion() : value{} {}
    
    template<typename U>
    MemoryLayoutUnion(U&& val) : value(forward<U>(val)) {}
    
    void printBytes() const {
        cout << "Bytes: ";
        for (size_t i = 0; i < sizeof(T); ++i) {
            cout << static_cast<int>(bytes[i]) << " ";
        }
        cout << endl;
    }
    
    void printHex() const {
        cout << "Hex: ";
        for (size_t i = 0; i < sizeof(T); ++i) {
            cout << hex << static_cast<int>(bytes[i]) << " ";
        }
        cout << dec << endl;
    }
    
    void printBinary() const {
        cout << "Binary: ";
        for (size_t i = 0; i < sizeof(T); ++i) {
            for (int j = 7; j >= 0; --j) {
                cout << ((bytes[i] >> j) & 1);
            }
            cout << " ";
        }
        cout << endl;
    }
};

// Union with serialization
template<typename... Types>
class SerializableUnion {
private:
    variant<Types...> data;
    
public:
    template<typename T>
    SerializableUnion(T&& value) : data(forward<T>(value)) {}
    
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
    
    vector<uint8_t> serialize() const {
        vector<uint8_t> result;
        
        // Serialize type index
        uint8_t typeIndex = static_cast<uint8_t>(data.index());
        result.push_back(typeIndex);
        
        // Serialize data
        visit([&](const auto& value) {
            const uint8_t* ptr = reinterpret_cast<const uint8_t*>(&value);
            for (size_t i = 0; i < sizeof(value); ++i) {
                result.push_back(ptr[i]);
            }
        });
        
        return result;
    }
    
    static optional<SerializableUnion> deserialize(const vector<uint8_t>& data) {
        if (data.empty()) return nullopt;
        
        uint8_t typeIndex = data[0];
        if (typeIndex >= sizeof...(Types)) return nullopt;
        
        // This is a simplified deserialization
        // In practice, you'd need more sophisticated type handling
        return nullopt;
    }
};

// Union with reflection
template<typename... Types>
class ReflectiveUnion {
private:
    variant<Types...> data;
    
public:
    template<typename T>
    ReflectiveUnion(T&& value) : data(forward<T>(value)) {}
    
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
    
    string getTypeName() const {
        return visit([](const auto& value) -> string {
            return typeid(decltype(value)).name();
        });
    }
    
    size_t getTypeIndex() const {
        return data.index();
    }
    
    template<typename Visitor>
    auto visit(Visitor&& visitor) {
        return std::visit(forward<Visitor>(visitor), data);
    }
    
    template<typename Visitor>
    auto visit(Visitor&& visitor) const {
        return std::visit(forward<Visitor>(visitor), data);
    }
    
    void printInfo() const {
        cout << "Type: " << getTypeName() << endl;
        cout << "Index: " << getTypeIndex() << endl;
        cout << "Value: ";
        visit([](const auto& value) {
            cout << value << endl;
        });
    }
};

// Union with performance monitoring
template<typename... Types>
class MonitoredUnion {
private:
    variant<Types...> data;
    atomic<size_t> accessCount{0};
    atomic<size_t> typeChanges{0};
    
public:
    template<typename T>
    MonitoredUnion(T&& value) : data(forward<T>(value)) {}
    
    template<typename T>
    bool holds() const {
        accessCount.fetch_add(1, memory_order_relaxed);
        return holds_alternative<T>(data);
    }
    
    template<typename T>
    T& get() {
        accessCount.fetch_add(1, memory_order_relaxed);
        return get<T>(data);
    }
    
    template<typename T>
    const T& get() const {
        accessCount.fetch_add(1, memory_order_relaxed);
        return get<T>(data);
    }
    
    template<typename T>
    void set(T&& value) {
        if (!holds_alternative<T>(data)) {
            typeChanges.fetch_add(1, memory_order_relaxed);
        }
        data = forward<T>(value);
    }
    
    size_t getAccessCount() const {
        return accessCount.load(memory_order_relaxed);
    }
    
    size_t getTypeChanges() const {
        return typeChanges.load(memory_order_relaxed);
    }
    
    void printStats() const {
        cout << "Access count: " << getAccessCount() << endl;
        cout << "Type changes: " << getTypeChanges() << endl;
    }
};

// Union with thread safety
template<typename... Types>
class ThreadSafeUnion {
private:
    variant<Types...> data;
    mutable mutex dataMutex;
    
public:
    template<typename T>
    ThreadSafeUnion(T&& value) : data(forward<T>(value)) {}
    
    template<typename T>
    bool holds() const {
        lock_guard<mutex> lock(dataMutex);
        return holds_alternative<T>(data);
    }
    
    template<typename T>
    T get() const {
        lock_guard<mutex> lock(dataMutex);
        return get<T>(data);
    }
    
    template<typename T>
    void set(T&& value) {
        lock_guard<mutex> lock(dataMutex);
        data = forward<T>(value);
    }
    
    template<typename Visitor>
    auto visit(Visitor&& visitor) const {
        lock_guard<mutex> lock(dataMutex);
        return std::visit(forward<Visitor>(visitor), data);
    }
    
    template<typename Visitor>
    auto visit(Visitor&& visitor) {
        lock_guard<mutex> lock(dataMutex);
        return std::visit(forward<Visitor>(visitor), data);
    }
};

// Union with custom allocator
template<typename Allocator, typename... Types>
class AllocatedUnion {
private:
    using VariantType = variant<Types...>;
    VariantType data;
    Allocator allocator;
    
public:
    template<typename T>
    AllocatedUnion(T&& value, const Allocator& alloc = Allocator{}) 
        : data(forward<T>(value)), allocator(alloc) {}
    
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
    
    Allocator getAllocator() const {
        return allocator;
    }
};

// Union with move semantics
template<typename... Types>
class MoveableUnion {
private:
    variant<Types...> data;
    
public:
    template<typename T>
    MoveableUnion(T&& value) : data(forward<T>(value)) {}
    
    // Move constructor
    MoveableUnion(MoveableUnion&& other) noexcept : data(move(other.data)) {}
    
    // Move assignment
    MoveableUnion& operator=(MoveableUnion&& other) noexcept {
        if (this != &other) {
            data = move(other.data);
        }
        return *this;
    }
    
    // Delete copy constructor and assignment
    MoveableUnion(const MoveableUnion&) = delete;
    MoveableUnion& operator=(const MoveableUnion&) = delete;
    
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
    
    template<typename T>
    void set(T&& value) {
        data = forward<T>(value);
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

// Union with exception safety
template<typename... Types>
class ExceptionSafeUnion {
private:
    variant<Types...> data;
    
public:
    template<typename T>
    ExceptionSafeUnion(T&& value) noexcept(noexcept(variant<Types...>(forward<T>(value)))) 
        : data(forward<T>(value)) {}
    
    template<typename T>
    bool holds() const noexcept {
        return holds_alternative<T>(data);
    }
    
    template<typename T>
    T& get() & {
        if (!holds_alternative<T>(data)) {
            throw bad_variant_access{};
        }
        return get<T>(data);
    }
    
    template<typename T>
    const T& get() const & {
        if (!holds_alternative<T>(data)) {
            throw bad_variant_access{};
        }
        return get<T>(data);
    }
    
    template<typename T>
    T&& get() && {
        if (!holds_alternative<T>(data)) {
            throw bad_variant_access{};
        }
        return get<T>(move(data));
    }
    
    template<typename T>
    const T&& get() const && {
        if (!holds_alternative<T>(data)) {
            throw bad_variant_access{};
        }
        return get<T>(move(data));
    }
    
    template<typename T>
    void set(T&& value) noexcept(noexcept(data = forward<T>(value))) {
        data = forward<T>(value);
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

// Union with custom comparison
template<typename... Types>
class ComparableUnion {
private:
    variant<Types...> data;
    
public:
    template<typename T>
    ComparableUnion(T&& value) : data(forward<T>(value)) {}
    
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
    
    bool operator==(const ComparableUnion& other) const {
        return data == other.data;
    }
    
    bool operator!=(const ComparableUnion& other) const {
        return !(*this == other);
    }
    
    bool operator<(const ComparableUnion& other) const {
        return data < other.data;
    }
    
    bool operator<=(const ComparableUnion& other) const {
        return data <= other.data;
    }
    
    bool operator>(const ComparableUnion& other) const {
        return data > other.data;
    }
    
    bool operator>=(const ComparableUnion& other) const {
        return data >= other.data;
    }
};

int main() {
    cout << "=== UNION ADVANCED EXAMPLES ===" << endl << endl;
    
    // Example 1: Type erasure
    cout << "1. Type Erasure:" << endl;
    TypeErasedUnion<int, string, double> teu1(42);
    TypeErasedUnion<int, string, double> teu2(string("Hello"));
    TypeErasedUnion<int, string, double> teu3(3.14);
    
    cout << "teu1 type: " << teu1.typeName() << ", value: ";
    teu1.visit([](const auto& value) { cout << value << endl; });
    
    cout << "teu2 type: " << teu2.typeName() << ", value: ";
    teu2.visit([](const auto& value) { cout << value << endl; });
    
    cout << "teu3 type: " << teu3.typeName() << ", value: ";
    teu3.visit([](const auto& value) { cout << value << endl; });
    cout << endl;
    
    // Example 2: Memory layout control
    cout << "2. Memory Layout Control:" << endl;
    MemoryLayoutUnion<int> mlu(0x12345678);
    cout << "Value: " << mlu.value << endl;
    mlu.printBytes();
    mlu.printHex();
    mlu.printBinary();
    cout << endl;
    
    // Example 3: Serialization
    cout << "3. Serialization:" << endl;
    SerializableUnion<int, string, double> su1(42);
    SerializableUnion<int, string, double> su2(string("Hello"));
    
    auto serialized1 = su1.serialize();
    auto serialized2 = su2.serialize();
    
    cout << "Serialized int: ";
    for (uint8_t byte : serialized1) {
        cout << static_cast<int>(byte) << " ";
    }
    cout << endl;
    
    cout << "Serialized string: ";
    for (uint8_t byte : serialized2) {
        cout << static_cast<int>(byte) << " ";
    }
    cout << endl;
    cout << endl;
    
    // Example 4: Reflection
    cout << "4. Reflection:" << endl;
    ReflectiveUnion<int, string, double> ru1(42);
    ReflectiveUnion<int, string, double> ru2(string("World"));
    ReflectiveUnion<int, string, double> ru3(2.718);
    
    ru1.printInfo();
    ru2.printInfo();
    ru3.printInfo();
    cout << endl;
    
    // Example 5: Performance monitoring
    cout << "5. Performance Monitoring:" << endl;
    MonitoredUnion<int, string, double> mu(42);
    
    // Simulate some accesses
    for (int i = 0; i < 100; ++i) {
        mu.holds<int>();
        mu.get<int>();
    }
    
    mu.set(string("Performance test"));
    mu.set(3.14);
    
    mu.printStats();
    cout << endl;
    
    // Example 6: Thread safety
    cout << "6. Thread Safety:" << endl;
    ThreadSafeUnion<int, string, double> tsu(42);
    
    // Simulate concurrent access
    vector<thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([&tsu, i]() {
            tsu.set(i * 10);
            this_thread::sleep_for(chrono::milliseconds(10));
            tsu.visit([](const auto& value) {
                cout << "Thread value: " << value << endl;
            });
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    cout << endl;
    
    // Example 7: Move semantics
    cout << "7. Move Semantics:" << endl;
    MoveableUnion<int, string, double> mu1(42);
    MoveableUnion<int, string, double> mu2 = move(mu1);
    
    cout << "mu2 holds int: " << mu2.holds<int>() << endl;
    if (mu2.holds<int>()) {
        cout << "mu2 value: " << mu2.get<int>() << endl;
    }
    cout << endl;
    
    // Example 8: Exception safety
    cout << "8. Exception Safety:" << endl;
    ExceptionSafeUnion<int, string, double> esu(42);
    
    try {
        cout << "Value: " << esu.get<int>() << endl;
        cout << "String value: " << esu.get<string>() << endl;
    } catch (const bad_variant_access& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
    cout << endl;
    
    // Example 9: Custom comparison
    cout << "9. Custom Comparison:" << endl;
    ComparableUnion<int, string, double> cu1(42);
    ComparableUnion<int, string, double> cu2(42);
    ComparableUnion<int, string, double> cu3(24);
    
    cout << "cu1 == cu2: " << (cu1 == cu2) << endl;
    cout << "cu1 == cu3: " << (cu1 == cu3) << endl;
    cout << "cu1 < cu3: " << (cu1 < cu3) << endl;
    cout << endl;
    
    // Example 10: Advanced operations
    cout << "10. Advanced Operations:" << endl;
    vector<TypeErasedUnion<int, string, double>> unions = {
        TypeErasedUnion<int, string, double>(42),
        TypeErasedUnion<int, string, double>(string("Hello")),
        TypeErasedUnion<int, string, double>(3.14)
    };
    
    cout << "Union collection:" << endl;
    for (size_t i = 0; i < unions.size(); ++i) {
        cout << "  " << i << ": ";
        unions[i].visit([](const auto& value) {
            cout << value << " (" << typeid(decltype(value)).name() << ")";
        });
        cout << endl;
    }
    
    return 0;
}
