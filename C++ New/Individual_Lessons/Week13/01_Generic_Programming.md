# Lesson 13.1: Generic Programming

## Learning Objectives
- Master generic algorithms and data structures
- Understand iterator concepts and ranges
- Learn function objects and adapters
- Practice with modern generic programming patterns
- Explore STL algorithms and custom implementations

## Prerequisites
- Completed Lesson 12.2 (Advanced Templates)
- Understanding of templates and metaprogramming
- Knowledge of STL containers

## Duration
90 minutes

---

## Lecture Content (30 minutes)

### 1. Generic Algorithms

#### Algorithm Design Principles
```cpp
#include <algorithm>
#include <vector>
#include <iterator>

// Generic algorithm example
template<typename Iterator, typename Predicate>
Iterator find_if(Iterator first, Iterator last, Predicate pred) {
    for (auto it = first; it != last; ++it) {
        if (pred(*it)) {
            return it;
        }
    }
    return last;
}

// Generic algorithm with function object
template<typename Iterator, typename Function>
void for_each(Iterator first, Iterator last, Function func) {
    for (auto it = first; it != last; ++it) {
        func(*it);
    }
}

// Generic algorithm with binary operation
template<typename Iterator, typename T, typename BinaryOp>
T accumulate(Iterator first, Iterator last, T init, BinaryOp op) {
    T result = init;
    for (auto it = first; it != last; ++it) {
        result = op(result, *it);
    }
    return result;
}

// Usage examples
void demonstrateGenericAlgorithms() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Find first even number
    auto it = find_if(numbers.begin(), numbers.end(), 
                      [](int n) { return n % 2 == 0; });
    
    if (it != numbers.end()) {
        std::cout << "First even number: " << *it << std::endl;
    }
    
    // Accumulate with custom operation
    int product = accumulate(numbers.begin(), numbers.end(), 1, 
                            [](int a, int b) { return a * b; });
    std::cout << "Product of all numbers: " << product << std::endl;
}
```

### 2. Iterator Concepts

#### Iterator Categories
```cpp
#include <iterator>

// Input iterator concept
template<typename Iterator>
concept InputIterator = requires(Iterator it) {
    typename std::iterator_traits<Iterator>::iterator_category;
    typename std::iterator_traits<Iterator>::value_type;
    typename std::iterator_traits<Iterator>::difference_type;
    typename std::iterator_traits<Iterator>::pointer;
    typename std::iterator_traits<Iterator>::reference;
    
    *it;
    ++it;
    it++;
    it == it;
    it != it;
};

// Forward iterator concept
template<typename Iterator>
concept ForwardIterator = InputIterator<Iterator> && requires(Iterator it) {
    it++;
    ++it;
};

// Bidirectional iterator concept
template<typename Iterator>
concept BidirectionalIterator = ForwardIterator<Iterator> && requires(Iterator it) {
    --it;
    it--;
};

// Random access iterator concept
template<typename Iterator>
concept RandomAccessIterator = BidirectionalIterator<Iterator> && requires(Iterator it, int n) {
    it + n;
    n + it;
    it - n;
    it - it;
    it[n];
    it < it;
    it > it;
    it <= it;
    it >= it;
};

// Generic algorithm with iterator concepts
template<InputIterator Iterator, typename T>
Iterator find(Iterator first, Iterator last, const T& value) {
    for (auto it = first; it != last; ++it) {
        if (*it == value) {
            return it;
        }
    }
    return last;
}
```

### 3. Function Objects and Adapters

#### Function Objects
```cpp
// Function object for comparison
struct Less {
    template<typename T>
    bool operator()(const T& a, const T& b) const {
        return a < b;
    }
};

struct Greater {
    template<typename T>
    bool operator()(const T& a, const T& b) const {
        return a > b;
    }
};

// Function object for arithmetic operations
struct Plus {
    template<typename T>
    T operator()(const T& a, const T& b) const {
        return a + b;
    }
};

struct Multiply {
    template<typename T>
    T operator()(const T& a, const T& b) const {
        return a * b;
    }
};

// Function object with state
class Counter {
private:
    int count_;
    
public:
    Counter() : count_(0) {}
    
    template<typename T>
    void operator()(const T&) {
        ++count_;
    }
    
    int getCount() const { return count_; }
};

// Function object adapter
template<typename Predicate>
class Not {
private:
    Predicate pred_;
    
public:
    Not(Predicate pred) : pred_(pred) {}
    
    template<typename T>
    bool operator()(const T& value) const {
        return !pred_(value);
    }
};

// Usage
void demonstrateFunctionObjects() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Sort with function object
    std::sort(numbers.begin(), numbers.end(), Greater{});
    
    // Count elements
    Counter counter;
    std::for_each(numbers.begin(), numbers.end(), counter);
    std::cout << "Count: " << counter.getCount() << std::endl;
    
    // Find with negated predicate
    auto it = std::find_if(numbers.begin(), numbers.end(), 
                          Not{[](int n) { return n % 2 == 0; }});
    
    if (it != numbers.end()) {
        std::cout << "First odd number: " << *it << std::endl;
    }
}
```

### 4. Modern Generic Programming

#### Ranges and Views (C++20)
```cpp
#include <ranges>

// Range-based algorithms
template<std::ranges::range Range, typename Predicate>
auto filter_range(Range&& range, Predicate pred) {
    return range | std::views::filter(pred);
}

template<std::ranges::range Range, typename Function>
auto transform_range(Range&& range, Function func) {
    return range | std::views::transform(func);
}

// Generic range operations
template<std::ranges::range Range>
void print_range(Range&& range) {
    for (const auto& item : range) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

// Usage with ranges
void demonstrateRanges() {
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Filter even numbers
    auto even_numbers = numbers | std::views::filter([](int n) { return n % 2 == 0; });
    
    // Transform to squares
    auto squares = even_numbers | std::views::transform([](int n) { return n * n; });
    
    std::cout << "Even squares: ";
    for (const auto& square : squares) {
        std::cout << square << " ";
    }
    std::cout << std::endl;
}
```

---

## Demonstration (25 minutes)

### Generic Programming Examples
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>

// Custom generic container
template<typename T>
class GenericContainer {
private:
    std::vector<T> data_;
    
public:
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;
    
    void add(const T& item) {
        data_.push_back(item);
    }
    
    iterator begin() { return data_.begin(); }
    iterator end() { return data_.end(); }
    const_iterator begin() const { return data_.begin(); }
    const_iterator end() const { return data_.end(); }
    
    size_t size() const { return data_.size(); }
    
    // Generic algorithm methods
    template<typename Predicate>
    iterator find_if(Predicate pred) {
        return std::find_if(begin(), end(), pred);
    }
    
    template<typename Function>
    void for_each(Function func) {
        std::for_each(begin(), end(), func);
    }
    
    template<typename Predicate>
    void remove_if(Predicate pred) {
        data_.erase(std::remove_if(begin(), end(), pred), end());
    }
    
    template<typename Function>
    void transform(Function func) {
        std::transform(begin(), end(), begin(), func);
    }
    
    void display() const {
        std::cout << "Container: ";
        for (const auto& item : data_) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

// Generic algorithm library
namespace GenericAlgorithms {
    
    // Generic find algorithm
    template<typename Iterator, typename T>
    Iterator find(Iterator first, Iterator last, const T& value) {
        for (auto it = first; it != last; ++it) {
            if (*it == value) {
                return it;
            }
        }
        return last;
    }
    
    // Generic count algorithm
    template<typename Iterator, typename T>
    typename std::iterator_traits<Iterator>::difference_type
    count(Iterator first, Iterator last, const T& value) {
        typename std::iterator_traits<Iterator>::difference_type result = 0;
        for (auto it = first; it != last; ++it) {
            if (*it == value) {
                ++result;
            }
        }
        return result;
    }
    
    // Generic copy algorithm
    template<typename InputIterator, typename OutputIterator>
    OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result) {
        while (first != last) {
            *result = *first;
            ++first;
            ++result;
        }
        return result;
    }
    
    // Generic transform algorithm
    template<typename InputIterator, typename OutputIterator, typename UnaryOp>
    OutputIterator transform(InputIterator first, InputIterator last, 
                           OutputIterator result, UnaryOp op) {
        while (first != last) {
            *result = op(*first);
            ++first;
            ++result;
        }
        return result;
    }
    
    // Generic accumulate algorithm
    template<typename InputIterator, typename T, typename BinaryOp>
    T accumulate(InputIterator first, InputIterator last, T init, BinaryOp op) {
        T result = init;
        while (first != last) {
            result = op(result, *first);
            ++first;
        }
        return result;
    }
}

// Function object examples
struct Square {
    template<typename T>
    T operator()(const T& value) const {
        return value * value;
    }
};

struct IsEven {
    template<typename T>
    bool operator()(const T& value) const {
        return value % 2 == 0;
    }
};

struct IsOdd {
    template<typename T>
    bool operator()(const T& value) const {
        return value % 2 != 0;
    }
};

// Function object with state
class Accumulator {
private:
    int sum_;
    
public:
    Accumulator() : sum_(0) {}
    
    template<typename T>
    void operator()(const T& value) {
        sum_ += value;
    }
    
    int getSum() const { return sum_; }
    void reset() { sum_ = 0; }
};

void demonstrateGenericProgramming() {
    std::cout << "=== Generic Programming Demonstration ===" << std::endl;
    
    // Test with different types
    GenericContainer<int> int_container;
    GenericContainer<std::string> string_container;
    
    // Add elements
    for (int i = 1; i <= 10; ++i) {
        int_container.add(i);
    }
    
    string_container.add("apple");
    string_container.add("banana");
    string_container.add("cherry");
    string_container.add("date");
    string_container.add("elderberry");
    
    std::cout << "\nInteger container:" << std::endl;
    int_container.display();
    
    std::cout << "\nString container:" << std::endl;
    string_container.display();
    
    // Generic algorithms
    std::cout << "\nGeneric algorithms:" << std::endl;
    
    // Find element
    auto it = GenericAlgorithms::find(int_container.begin(), int_container.end(), 5);
    if (it != int_container.end()) {
        std::cout << "Found 5 in container" << std::endl;
    }
    
    // Count elements
    auto count = GenericAlgorithms::count(int_container.begin(), int_container.end(), 3);
    std::cout << "Count of 3: " << count << std::endl;
    
    // Transform elements
    int_container.transform(Square{});
    std::cout << "After squaring: ";
    int_container.display();
    
    // Remove elements
    int_container.remove_if(IsEven{});
    std::cout << "After removing evens: ";
    int_container.display();
    
    // Accumulate with function object
    Accumulator acc;
    int_container.for_each(acc);
    std::cout << "Sum of remaining elements: " << acc.getSum() << std::endl;
    
    // String operations
    std::cout << "\nString operations:" << std::endl;
    auto string_it = GenericAlgorithms::find(string_container.begin(), string_container.end(), "banana");
    if (string_it != string_container.end()) {
        std::cout << "Found 'banana' in string container" << std::endl;
    }
    
    // Count strings with specific length
    auto long_strings = GenericAlgorithms::count(string_container.begin(), string_container.end(), 
                                                [](const std::string& s) { return s.length() > 5; });
    std::cout << "Count of long strings: " << long_strings << std::endl;
}
```

---

## Hands-on Practice (35 minutes)

### Activity 1: Generic Algorithm Implementation
Implement generic algorithms:

**Tasks:**
1. Create generic search algorithms
2. Implement generic sorting algorithms
3. Build generic transformation algorithms
4. Test with different data types

### Activity 2: Iterator Design
Design iterator concepts:

**Tasks:**
1. Create custom iterator classes
2. Implement iterator categories
3. Build iterator adapters
4. Test iterator functionality

### Activity 3: Function Object Library
Build function object library:

**Tasks:**
1. Create reusable function objects
2. Implement function adapters
3. Build stateful function objects
4. Test function object composition

---

## Key Concepts

### 1. Generic Algorithm Design
```cpp
// Generic algorithm template
template<typename Iterator, typename Predicate>
Iterator find_if(Iterator first, Iterator last, Predicate pred) {
    for (auto it = first; it != last; ++it) {
        if (pred(*it)) {
            return it;
        }
    }
    return last;
}

// Usage with different types
std::vector<int> numbers = {1, 2, 3, 4, 5};
auto it = find_if(numbers.begin(), numbers.end(), 
                  [](int n) { return n % 2 == 0; });
```

### 2. Iterator Concepts
```cpp
// Iterator requirements
template<typename Iterator>
concept InputIterator = requires(Iterator it) {
    *it;        // Dereference
    ++it;       // Increment
    it == it;   // Equality
    it != it;   // Inequality
};

// Algorithm with iterator concepts
template<InputIterator Iterator, typename T>
Iterator find(Iterator first, Iterator last, const T& value);
```

### 3. Function Object Composition
```cpp
// Function object composition
template<typename F, typename G>
class Compose {
private:
    F f_;
    G g_;
    
public:
    Compose(F f, G g) : f_(f), g_(g) {}
    
    template<typename T>
    auto operator()(const T& value) const {
        return f_(g_(value));
    }
};

// Usage
auto composed = Compose{Square{}, [](int n) { return n + 1; }};
int result = composed(5);  // (5 + 1) * (5 + 1) = 36
```

---

## Best Practices

### 1. Generic Algorithm Design
- Use iterator concepts for type safety
- Provide both iterator and range versions
- Support custom comparison and transformation functions
- Document algorithm complexity and requirements

### 2. Iterator Implementation
- Implement all required iterator operations
- Provide proper iterator categories
- Support const and non-const iterators
- Handle iterator invalidation correctly

### 3. Function Object Design
- Make function objects stateless when possible
- Use templates for type flexibility
- Provide clear operator() implementations
- Support function object composition

---

## Common Pitfalls

### 1. Iterator Invalidation
```cpp
// Wrong: iterator invalidation
std::vector<int> vec = {1, 2, 3, 4, 5};
auto it = vec.begin();
vec.push_back(6);  // Iterator may be invalidated
*it;  // Undefined behavior

// Correct: use indices or refresh iterators
std::vector<int> vec = {1, 2, 3, 4, 5};
size_t index = 0;
vec.push_back(6);
vec[index];  // Safe
```

### 2. Template Instantiation Issues
```cpp
// Wrong: incomplete type in template
template<typename T>
class Container {
    T data_;  // T might be incomplete
};

// Correct: use pointers or references
template<typename T>
class Container {
    T* data_;  // T can be incomplete
};
```

### 3. Function Object State Issues
```cpp
// Wrong: shared state
class Counter {
    static int count_;  // Shared across instances
public:
    void operator()(int) { ++count_; }
};

// Correct: instance state
class Counter {
    int count_;  // Instance-specific
public:
    Counter() : count_(0) {}
    void operator()(int) { ++count_; }
};
```

---

## Assessment

### Quiz Questions
1. What are the benefits of generic programming?
2. How do iterator concepts improve type safety?
3. When should you use function objects vs function pointers?
4. What are the advantages of generic algorithms?

### Practical Assessment
- Implement generic algorithms correctly
- Design proper iterator interfaces
- Create reusable function objects
- Apply generic programming patterns

---

## Homework Assignment

### Task 1: Generic Algorithm Library
Implement:
1. A library of generic algorithms
2. Iterator-based and range-based versions
3. Custom comparison and transformation functions
4. Performance testing and optimization

### Task 2: Iterator Implementation
Create:
1. Custom iterator classes for different containers
2. Iterator adapters and utilities
3. Iterator concept validation
4. Iterator performance testing

### Task 3: Function Object Framework
Design:
1. A framework of reusable function objects
2. Function object composition utilities
3. Stateful function object management
4. Function object testing and validation

---

## Next Lesson Preview

In the next lesson, we'll learn about STL algorithms:
- Standard algorithm categories
- Algorithm complexity and performance
- Custom algorithm implementations
- Algorithm optimization techniques

Make sure you understand generic programming before moving on!
