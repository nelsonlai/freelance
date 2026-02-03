/*
 * ENUM ADVANCED EXAMPLES
 * 
 * This file demonstrates advanced enum concepts including reflection, serialization, and template metaprogramming:
 * - Advanced concepts and techniques
 * - Real-world applications and patterns
 * - Best practices and optimization
 * - Complex scenarios and edge cases
 * 
 * Learning Objectives:
 * - Master advanced ENUM concepts
 * - Understand professional coding patterns
 * - Learn optimization techniques
 * - Apply knowledge in complex scenarios
 * - Develop problem-solving skills
 * 
 * Prerequisites:
 * - Solid understanding of basic ENUM concepts
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
#include <map>
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
using namespace std;

// Advanced enum with reflection
template<typename Enum>
struct EnumReflection {
    static constexpr size_t count = 0;
    static constexpr const char* name(Enum) { return "Unknown"; }
    static constexpr Enum fromString(const string&) { return static_cast<Enum>(0); }
};

// Macro for enum reflection
#define ENUM_REFLECTION(EnumType, ...) \
template<> \
struct EnumReflection<EnumType> { \
    static constexpr size_t count = __VA_ARGS__##_count; \
    static constexpr const char* names[] = { __VA_ARGS__##_names }; \
    static constexpr EnumType values[] = { __VA_ARGS__##_values }; \
    \
    static constexpr const char* name(EnumType e) { \
        for (size_t i = 0; i < count; ++i) { \
            if (values[i] == e) return names[i]; \
        } \
        return "Unknown"; \
    } \
    \
    static constexpr EnumType fromString(const string& str) { \
        for (size_t i = 0; i < count; ++i) { \
            if (names[i] == str) return values[i]; \
        } \
        return static_cast<EnumType>(0); \
    } \
};

// Define enum with reflection
enum class Color {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    PURPLE
};

// Define reflection for Color enum
#define COLOR_NAMES "Red", "Green", "Blue", "Yellow", "Purple"
#define COLOR_VALUES Color::RED, Color::GREEN, Color::BLUE, Color::YELLOW, Color::PURPLE
#define COLOR_COUNT 5

ENUM_REFLECTION(Color, COLOR)

// Advanced enum with associated data
template<typename T>
struct EnumWithData {
    enum class Type { VALUE, ERROR } type;
    T data;
    string message;
    
    EnumWithData(T value) : type(Type::VALUE), data(value), message("") {}
    EnumWithData(Type t, const string& msg) : type(t), data{}, message(msg) {}
    
    bool isValue() const { return type == Type::VALUE; }
    bool isError() const { return type == Type::ERROR; }
    
    T getValue() const { return data; }
    string getError() const { return message; }
    
    template<typename F>
    auto map(F&& f) -> EnumWithData<decltype(f(data))> {
        if (isValue()) {
            return EnumWithData<decltype(f(data))>(f(data));
        } else {
            return EnumWithData<decltype(f(data))>(Type::ERROR, message);
        }
    }
    
    template<typename F>
    auto flatMap(F&& f) -> decltype(f(data)) {
        if (isValue()) {
            return f(data);
        } else {
            return decltype(f(data))(Type::ERROR, message);
        }
    }
};

// Enum with bitwise operations
enum class FilePermission : uint8_t {
    NONE = 0x00,
    READ = 0x01,
    WRITE = 0x02,
    EXECUTE = 0x04,
    ALL = READ | WRITE | EXECUTE
};

// Bitwise operators for enum
constexpr FilePermission operator|(FilePermission a, FilePermission b) {
    return static_cast<FilePermission>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

constexpr FilePermission operator&(FilePermission a, FilePermission b) {
    return static_cast<FilePermission>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

constexpr FilePermission operator^(FilePermission a, FilePermission b) {
    return static_cast<FilePermission>(static_cast<uint8_t>(a) ^ static_cast<uint8_t>(b));
}

constexpr FilePermission operator~(FilePermission a) {
    return static_cast<FilePermission>(~static_cast<uint8_t>(a));
}

constexpr bool hasPermission(FilePermission perms, FilePermission required) {
    return (perms & required) == required;
}

// Enum with serialization
template<typename Enum>
struct EnumSerializer {
    static string serialize(Enum e) {
        return to_string(static_cast<underlying_type_t<Enum>>(e));
    }
    
    static optional<Enum> deserialize(const string& str) {
        try {
            auto value = stoi(str);
            return static_cast<Enum>(value);
        } catch (...) {
            return nullopt;
        }
    }
};

// Enum with validation
template<typename Enum>
struct EnumValidator {
    static bool isValid(Enum e) {
        return static_cast<underlying_type_t<Enum>>(e) >= 0;
    }
    
    static vector<Enum> getAllValues() {
        vector<Enum> values;
        for (size_t i = 0; i < EnumReflection<Enum>::count; ++i) {
            values.push_back(EnumReflection<Enum>::values[i]);
        }
        return values;
    }
};

// Enum with state machine
template<typename State, typename Event>
class StateMachine {
private:
    State currentState;
    map<pair<State, Event>, State> transitions;
    
public:
    StateMachine(State initialState) : currentState(initialState) {}
    
    void addTransition(State from, Event event, State to) {
        transitions[{from, event}] = to;
    }
    
    bool processEvent(Event event) {
        auto it = transitions.find({currentState, event});
        if (it != transitions.end()) {
            currentState = it->second;
            return true;
        }
        return false;
    }
    
    State getCurrentState() const { return currentState; }
    
    bool canProcess(Event event) const {
        return transitions.find({currentState, event}) != transitions.end();
    }
};

// Enum with visitor pattern
template<typename Enum>
struct EnumVisitor {
    virtual void visit(Enum e) = 0;
    virtual ~EnumVisitor() = default;
};

template<typename Enum>
struct EnumAcceptor {
    virtual void accept(EnumVisitor<Enum>& visitor) = 0;
    virtual ~EnumAcceptor() = default;
};

// Enum with factory pattern
template<typename Enum>
struct EnumFactory {
    static optional<Enum> create(const string& name) {
        return EnumReflection<Enum>::fromString(name);
    }
    
    static vector<Enum> createAll() {
        return EnumValidator<Enum>::getAllValues();
    }
    
    static Enum createRandom() {
        static random_device rd;
        static mt19937 gen(rd());
        uniform_int_distribution<> dis(0, EnumReflection<Enum>::count - 1);
        return EnumReflection<Enum>::values[dis(gen)];
    }
};

// Enum with observer pattern
template<typename Enum>
class EnumObserver {
public:
    virtual void onEnumChanged(Enum oldValue, Enum newValue) = 0;
    virtual ~EnumObserver() = default;
};

template<typename Enum>
class ObservableEnum {
private:
    Enum value;
    vector<shared_ptr<EnumObserver<Enum>>> observers;
    mutex observerMutex;
    
public:
    ObservableEnum(Enum initialValue) : value(initialValue) {}
    
    void setValue(Enum newValue) {
        if (value != newValue) {
            Enum oldValue = value;
            value = newValue;
            notifyObservers(oldValue, newValue);
        }
    }
    
    Enum getValue() const { return value; }
    
    void addObserver(shared_ptr<EnumObserver<Enum>> observer) {
        lock_guard<mutex> lock(observerMutex);
        observers.push_back(observer);
    }
    
    void removeObserver(shared_ptr<EnumObserver<Enum>> observer) {
        lock_guard<mutex> lock(observerMutex);
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }
    
private:
    void notifyObservers(Enum oldValue, Enum newValue) {
        lock_guard<mutex> lock(observerMutex);
        for (auto& observer : observers) {
            observer->onEnumChanged(oldValue, newValue);
        }
    }
};

// Enum with caching
template<typename Enum>
class EnumCache {
private:
    map<Enum, string> nameCache;
    map<string, Enum> valueCache;
    mutex cacheMutex;
    
public:
    string getName(Enum e) {
        {
            lock_guard<mutex> lock(cacheMutex);
            auto it = nameCache.find(e);
            if (it != nameCache.end()) {
                return it->second;
            }
        }
        
        string name = EnumReflection<Enum>::name(e);
        
        {
            lock_guard<mutex> lock(cacheMutex);
            nameCache[e] = name;
        }
        
        return name;
    }
    
    optional<Enum> getValue(const string& name) {
        {
            lock_guard<mutex> lock(cacheMutex);
            auto it = valueCache.find(name);
            if (it != valueCache.end()) {
                return it->second;
            }
        }
        
        auto value = EnumReflection<Enum>::fromString(name);
        
        {
            lock_guard<mutex> lock(cacheMutex);
            if (value != static_cast<Enum>(0)) {
                valueCache[name] = value;
            }
        }
        
        return value;
    }
};

// Enum with performance monitoring
template<typename Enum>
class EnumPerformanceMonitor {
private:
    map<Enum, atomic<size_t>> accessCounts;
    atomic<size_t> totalAccesses{0};
    
public:
    void recordAccess(Enum e) {
        accessCounts[e].fetch_add(1, memory_order_relaxed);
        totalAccesses.fetch_add(1, memory_order_relaxed);
    }
    
    size_t getAccessCount(Enum e) const {
        auto it = accessCounts.find(e);
        return it != accessCounts.end() ? it->second.load(memory_order_relaxed) : 0;
    }
    
    size_t getTotalAccesses() const {
        return totalAccesses.load(memory_order_relaxed);
    }
    
    void printStats() const {
        cout << "Enum Performance Stats:" << endl;
        cout << "Total accesses: " << getTotalAccesses() << endl;
        for (const auto& pair : accessCounts) {
            cout << "  " << EnumReflection<Enum>::name(pair.first) 
                 << ": " << pair.second.load(memory_order_relaxed) << endl;
        }
    }
};

int main() {
    cout << "=== ENUM ADVANCED EXAMPLES ===" << endl << endl;
    
    // Example 1: Enum reflection
    cout << "1. Enum Reflection:" << endl;
    cout << "Color enum values:" << endl;
    for (size_t i = 0; i < EnumReflection<Color>::count; ++i) {
        auto color = EnumReflection<Color>::values[i];
        cout << "  " << EnumReflection<Color>::name(color) << " = " 
             << static_cast<int>(color) << endl;
    }
    
    auto color = EnumReflection<Color>::fromString("Blue");
    cout << "From string 'Blue': " << EnumReflection<Color>::name(color) << endl;
    cout << endl;
    
    // Example 2: Enum with associated data
    cout << "2. Enum with Associated Data:" << endl;
    EnumWithData<int> result1(42);
    EnumWithData<int> result2(EnumWithData<int>::Type::ERROR, "Division by zero");
    
    cout << "Result 1 - Value: " << result1.getValue() << endl;
    cout << "Result 2 - Error: " << result2.getError() << endl;
    
    auto doubled = result1.map([](int x) { return x * 2; });
    cout << "Doubled result: " << doubled.getValue() << endl;
    cout << endl;
    
    // Example 3: Bitwise operations
    cout << "3. Bitwise Operations:" << endl;
    FilePermission perms = FilePermission::READ | FilePermission::WRITE;
    cout << "Permissions: " << static_cast<int>(perms) << endl;
    
    if (hasPermission(perms, FilePermission::READ)) {
        cout << "Has read permission" << endl;
    }
    if (hasPermission(perms, FilePermission::EXECUTE)) {
        cout << "Has execute permission" << endl;
    } else {
        cout << "No execute permission" << endl;
    }
    
    perms = perms | FilePermission::EXECUTE;
    cout << "After adding execute: " << static_cast<int>(perms) << endl;
    cout << endl;
    
    // Example 4: Serialization
    cout << "4. Serialization:" << endl;
    Color c = Color::GREEN;
    string serialized = EnumSerializer<Color>::serialize(c);
    cout << "Serialized: " << serialized << endl;
    
    auto deserialized = EnumSerializer<Color>::deserialize(serialized);
    if (deserialized) {
        cout << "Deserialized: " << EnumReflection<Color>::name(*deserialized) << endl;
    }
    cout << endl;
    
    // Example 5: State machine
    cout << "5. State Machine:" << endl;
    enum class State { IDLE, LOADING, PROCESSING, COMPLETED, ERROR };
    enum class Event { START, LOAD_COMPLETE, PROCESS_COMPLETE, ERROR_OCCURRED, RESET };
    
    StateMachine<State, Event> sm(State::IDLE);
    sm.addTransition(State::IDLE, Event::START, State::LOADING);
    sm.addTransition(State::LOADING, Event::LOAD_COMPLETE, State::PROCESSING);
    sm.addTransition(State::PROCESSING, Event::PROCESS_COMPLETE, State::COMPLETED);
    sm.addTransition(State::PROCESSING, Event::ERROR_OCCURRED, State::ERROR);
    sm.addTransition(State::ERROR, Event::RESET, State::IDLE);
    
    cout << "Initial state: " << static_cast<int>(sm.getCurrentState()) << endl;
    sm.processEvent(Event::START);
    cout << "After START: " << static_cast<int>(sm.getCurrentState()) << endl;
    sm.processEvent(Event::LOAD_COMPLETE);
    cout << "After LOAD_COMPLETE: " << static_cast<int>(sm.getCurrentState()) << endl;
    cout << endl;
    
    // Example 6: Factory pattern
    cout << "6. Factory Pattern:" << endl;
    auto color1 = EnumFactory<Color>::create("Red");
    if (color1) {
        cout << "Created color: " << EnumReflection<Color>::name(*color1) << endl;
    }
    
    auto randomColor = EnumFactory<Color>::createRandom();
    cout << "Random color: " << EnumReflection<Color>::name(randomColor) << endl;
    cout << endl;
    
    // Example 7: Observer pattern
    cout << "7. Observer Pattern:" << endl;
    class ColorObserver : public EnumObserver<Color> {
    public:
        void onEnumChanged(Color oldValue, Color newValue) override {
            cout << "Color changed from " << EnumReflection<Color>::name(oldValue) 
                 << " to " << EnumReflection<Color>::name(newValue) << endl;
        }
    };
    
    ObservableEnum<Color> observableColor(Color::RED);
    auto observer = make_shared<ColorObserver>();
    observableColor.addObserver(observer);
    
    observableColor.setValue(Color::GREEN);
    observableColor.setValue(Color::BLUE);
    cout << endl;
    
    // Example 8: Caching
    cout << "8. Caching:" << endl;
    EnumCache<Color> cache;
    
    // First access (cache miss)
    auto start = chrono::high_resolution_clock::now();
    string name1 = cache.getName(Color::PURPLE);
    auto end = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::nanoseconds>(end - start);
    
    // Second access (cache hit)
    start = chrono::high_resolution_clock::now();
    string name2 = cache.getName(Color::PURPLE);
    end = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::nanoseconds>(end - start);
    
    cout << "Name: " << name1 << endl;
    cout << "First access: " << duration1.count() << " ns" << endl;
    cout << "Second access: " << duration2.count() << " ns" << endl;
    cout << endl;
    
    // Example 9: Performance monitoring
    cout << "9. Performance Monitoring:" << endl;
    EnumPerformanceMonitor<Color> monitor;
    
    // Simulate some accesses
    for (int i = 0; i < 1000; ++i) {
        Color randomColor = EnumFactory<Color>::createRandom();
        monitor.recordAccess(randomColor);
    }
    
    monitor.printStats();
    cout << endl;
    
    // Example 10: Advanced enum operations
    cout << "10. Advanced Enum Operations:" << endl;
    vector<Color> allColors = EnumValidator<Color>::getAllValues();
    cout << "All colors: ";
    for (const auto& color : allColors) {
        cout << EnumReflection<Color>::name(color) << " ";
    }
    cout << endl;
    
    // Filter colors
    vector<Color> primaryColors;
    copy_if(allColors.begin(), allColors.end(), back_inserter(primaryColors),
        [](Color c) { return c == Color::RED || c == Color::GREEN || c == Color::BLUE; });
    
    cout << "Primary colors: ";
    for (const auto& color : primaryColors) {
        cout << EnumReflection<Color>::name(color) << " ";
    }
    cout << endl;
    
    return 0;
}
