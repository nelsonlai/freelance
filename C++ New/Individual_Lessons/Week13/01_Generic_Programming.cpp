/*
 * Lesson 13.1: Generic Programming
 * 
 * This file demonstrates generic algorithms, iterator concepts,
 * function objects, and modern generic programming patterns.
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>
#include <memory>
#include <cmath>

// Example 1: Generic Algorithm Library
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
    
    // Generic find_if algorithm
    template<typename Iterator, typename Predicate>
    Iterator find_if(Iterator first, Iterator last, Predicate pred) {
        for (auto it = first; it != last; ++it) {
            if (pred(*it)) {
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
    
    // Generic count_if algorithm
    template<typename Iterator, typename Predicate>
    typename std::iterator_traits<Iterator>::difference_type
    count_if(Iterator first, Iterator last, Predicate pred) {
        typename std::iterator_traits<Iterator>::difference_type result = 0;
        for (auto it = first; it != last; ++it) {
            if (pred(*it)) {
                ++result;
            }
        }
        return result;
    }
    
    // Generic for_each algorithm
    template<typename Iterator, typename Function>
    Function for_each(Iterator first, Iterator last, Function func) {
        for (auto it = first; it != last; ++it) {
            func(*it);
        }
        return func;
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
    
    // Generic reverse algorithm
    template<typename BidirectionalIterator>
    void reverse(BidirectionalIterator first, BidirectionalIterator last) {
        while ((first != last) && (first != --last)) {
            std::iter_swap(first, last);
            ++first;
        }
    }
    
    // Generic sort algorithm (bubble sort for demonstration)
    template<typename RandomAccessIterator, typename Compare>
    void sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
        for (auto i = first; i != last; ++i) {
            for (auto j = first; j != last - 1; ++j) {
                if (comp(*(j + 1), *j)) {
                    std::iter_swap(j, j + 1);
                }
            }
        }
    }
    
    // Generic unique algorithm
    template<typename ForwardIterator, typename BinaryPredicate>
    ForwardIterator unique(ForwardIterator first, ForwardIterator last, BinaryPredicate pred) {
        if (first == last) return last;
        
        ForwardIterator result = first;
        while (++first != last) {
            if (!pred(*result, *first)) {
                *(++result) = *first;
            }
        }
        return ++result;
    }
}

// Example 2: Function Objects
struct Square {
    template<typename T>
    T operator()(const T& value) const {
        return value * value;
    }
};

struct Cube {
    template<typename T>
    T operator()(const T& value) const {
        return value * value * value;
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

struct IsPrime {
    template<typename T>
    bool operator()(const T& value) const {
        if (value < 2) return false;
        for (T i = 2; i * i <= value; ++i) {
            if (value % i == 0) return false;
        }
        return true;
    }
};

struct Greater {
    template<typename T>
    bool operator()(const T& a, const T& b) const {
        return a > b;
    }
};

struct Less {
    template<typename T>
    bool operator()(const T& a, const T& b) const {
        return a < b;
    }
};

// Function object with state
class Accumulator {
private:
    int sum_;
    int count_;
    
public:
    Accumulator() : sum_(0), count_(0) {}
    
    template<typename T>
    void operator()(const T& value) {
        sum_ += value;
        ++count_;
    }
    
    int getSum() const { return sum_; }
    int getCount() const { return count_; }
    double getAverage() const { return count_ > 0 ? static_cast<double>(sum_) / count_ : 0.0; }
    void reset() { sum_ = 0; count_ = 0; }
};

// Function object for string operations
struct StringLength {
    template<typename T>
    bool operator()(const T& a, const T& b) const {
        return a.length() < b.length();
    }
};

struct StringContains {
    std::string substring_;
    
    StringContains(const std::string& substring) : substring_(substring) {}
    
    bool operator()(const std::string& str) const {
        return str.find(substring_) != std::string::npos;
    }
};

// Example 3: Generic Container
template<typename T>
class GenericContainer {
private:
    std::vector<T> data_;
    
public:
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;
    using value_type = T;
    
    // Constructors
    GenericContainer() = default;
    GenericContainer(std::initializer_list<T> init) : data_(init) {}
    
    // Iterator support
    iterator begin() { return data_.begin(); }
    iterator end() { return data_.end(); }
    const_iterator begin() const { return data_.begin(); }
    const_iterator end() const { return data_.end(); }
    
    // Capacity
    size_t size() const { return data_.size(); }
    bool empty() const { return data_.empty(); }
    void reserve(size_t capacity) { data_.reserve(capacity); }
    
    // Element access
    T& operator[](size_t index) { return data_[index]; }
    const T& operator[](size_t index) const { return data_[index]; }
    T& at(size_t index) { return data_.at(index); }
    const T& at(size_t index) const { return data_.at(index); }
    
    // Modifiers
    void add(const T& item) { data_.push_back(item); }
    void add(T&& item) { data_.push_back(std::move(item)); }
    void insert(iterator pos, const T& item) { data_.insert(pos, item); }
    void erase(iterator pos) { data_.erase(pos); }
    void clear() { data_.clear(); }
    
    // Generic algorithm methods
    template<typename Predicate>
    iterator find_if(Predicate pred) {
        return GenericAlgorithms::find_if(begin(), end(), pred);
    }
    
    template<typename T>
    iterator find(const T& value) {
        return GenericAlgorithms::find(begin(), end(), value);
    }
    
    template<typename Function>
    void for_each(Function func) {
        GenericAlgorithms::for_each(begin(), end(), func);
    }
    
    template<typename Predicate>
    void remove_if(Predicate pred) {
        data_.erase(std::remove_if(begin(), end(), pred), end());
    }
    
    template<typename Function>
    void transform(Function func) {
        GenericAlgorithms::transform(begin(), end(), begin(), func);
    }
    
    template<typename Predicate>
    size_t count_if(Predicate pred) const {
        return GenericAlgorithms::count_if(begin(), end(), pred);
    }
    
    template<typename T>
    size_t count(const T& value) const {
        return GenericAlgorithms::count(begin(), end(), value);
    }
    
    template<typename BinaryOp>
    T accumulate(T init, BinaryOp op) const {
        return GenericAlgorithms::accumulate(begin(), end(), init, op);
    }
    
    template<typename Compare>
    void sort(Compare comp) {
        GenericAlgorithms::sort(begin(), end(), comp);
    }
    
    void reverse() {
        GenericAlgorithms::reverse(begin(), end());
    }
    
    template<typename BinaryPredicate>
    void unique(BinaryPredicate pred) {
        auto new_end = GenericAlgorithms::unique(begin(), end(), pred);
        data_.erase(new_end, end());
    }
    
    void display() const {
        std::cout << "Container: ";
        for (const auto& item : data_) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
    
    void display(const std::string& label) const {
        std::cout << label << ": ";
        display();
    }
};

// Example 4: Iterator Adapters
template<typename Iterator>
class reverse_iterator {
private:
    Iterator base_;
    
public:
    using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
    using value_type = typename std::iterator_traits<Iterator>::value_type;
    using difference_type = typename std::iterator_traits<Iterator>::difference_type;
    using pointer = typename std::iterator_traits<Iterator>::pointer;
    using reference = typename std::iterator_traits<Iterator>::reference;
    
    reverse_iterator(Iterator base) : base_(base) {}
    
    reference operator*() const {
        Iterator temp = base_;
        return *--temp;
    }
    
    pointer operator->() const {
        Iterator temp = base_;
        return &*--temp;
    }
    
    reverse_iterator& operator++() {
        --base_;
        return *this;
    }
    
    reverse_iterator operator++(int) {
        reverse_iterator temp = *this;
        --base_;
        return temp;
    }
    
    reverse_iterator& operator--() {
        ++base_;
        return *this;
    }
    
    reverse_iterator operator--(int) {
        reverse_iterator temp = *this;
        ++base_;
        return temp;
    }
    
    bool operator==(const reverse_iterator& other) const {
        return base_ == other.base_;
    }
    
    bool operator!=(const reverse_iterator& other) const {
        return base_ != other.base_;
    }
};

// Example 5: Generic Algorithm with Ranges
template<typename Range, typename Predicate>
auto filter_range(const Range& range, Predicate pred) {
    std::vector<typename Range::value_type> result;
    for (const auto& item : range) {
        if (pred(item)) {
            result.push_back(item);
        }
    }
    return result;
}

template<typename Range, typename Function>
auto transform_range(const Range& range, Function func) {
    std::vector<decltype(func(std::declval<typename Range::value_type>()))> result;
    for (const auto& item : range) {
        result.push_back(func(item));
    }
    return result;
}

// Function to demonstrate generic algorithms
void demonstrateGenericAlgorithms() {
    std::cout << "=== Generic Algorithms Demonstration ===" << std::endl;
    
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    std::cout << "\nOriginal numbers: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Find operations
    auto it = GenericAlgorithms::find(numbers.begin(), numbers.end(), 5);
    if (it != numbers.end()) {
        std::cout << "Found 5 at position: " << std::distance(numbers.begin(), it) << std::endl;
    }
    
    auto even_it = GenericAlgorithms::find_if(numbers.begin(), numbers.end(), IsEven{});
    if (even_it != numbers.end()) {
        std::cout << "First even number: " << *even_it << std::endl;
    }
    
    // Count operations
    auto count_5 = GenericAlgorithms::count(numbers.begin(), numbers.end(), 5);
    std::cout << "Count of 5: " << count_5 << std::endl;
    
    auto count_even = GenericAlgorithms::count_if(numbers.begin(), numbers.end(), IsEven{});
    std::cout << "Count of even numbers: " << count_even << std::endl;
    
    // Transform operations
    std::vector<int> squares;
    GenericAlgorithms::transform(numbers.begin(), numbers.end(), 
                                std::back_inserter(squares), Square{});
    
    std::cout << "Squares: ";
    for (const auto& square : squares) {
        std::cout << square << " ";
    }
    std::cout << std::endl;
    
    // Accumulate operations
    int sum = GenericAlgorithms::accumulate(numbers.begin(), numbers.end(), 0, 
                                          [](int a, int b) { return a + b; });
    std::cout << "Sum: " << sum << std::endl;
    
    int product = GenericAlgorithms::accumulate(numbers.begin(), numbers.end(), 1, 
                                              [](int a, int b) { return a * b; });
    std::cout << "Product: " << product << std::endl;
    
    // Sort operations
    std::vector<int> sorted_numbers = numbers;
    GenericAlgorithms::sort(sorted_numbers.begin(), sorted_numbers.end(), Greater{});
    
    std::cout << "Sorted (descending): ";
    for (const auto& num : sorted_numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// Function to demonstrate function objects
void demonstrateFunctionObjects() {
    std::cout << "\n=== Function Objects Demonstration ===" << std::endl;
    
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    std::cout << "\nOriginal numbers: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Function objects with state
    Accumulator acc;
    GenericAlgorithms::for_each(numbers.begin(), numbers.end(), acc);
    std::cout << "Sum: " << acc.getSum() << std::endl;
    std::cout << "Count: " << acc.getCount() << std::endl;
    std::cout << "Average: " << acc.getAverage() << std::endl;
    
    // Transform with function objects
    std::vector<int> cubes;
    GenericAlgorithms::transform(numbers.begin(), numbers.end(), 
                                std::back_inserter(cubes), Cube{});
    
    std::cout << "Cubes: ";
    for (const auto& cube : cubes) {
        std::cout << cube << " ";
    }
    std::cout << std::endl;
    
    // Filter with function objects
    auto even_numbers = filter_range(numbers, IsEven{});
    std::cout << "Even numbers: ";
    for (const auto& num : even_numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    auto odd_numbers = filter_range(numbers, IsOdd{});
    std::cout << "Odd numbers: ";
    for (const auto& num : odd_numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    auto prime_numbers = filter_range(numbers, IsPrime{});
    std::cout << "Prime numbers: ";
    for (const auto& num : prime_numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// Function to demonstrate generic containers
void demonstrateGenericContainers() {
    std::cout << "\n=== Generic Containers Demonstration ===" << std::endl;
    
    // Integer container
    GenericContainer<int> int_container = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int_container.display("Integer container");
    
    // Find operations
    auto it = int_container.find(5);
    if (it != int_container.end()) {
        std::cout << "Found 5 in container" << std::endl;
    }
    
    auto even_it = int_container.find_if(IsEven{});
    if (even_it != int_container.end()) {
        std::cout << "First even number: " << *even_it << std::endl;
    }
    
    // Count operations
    std::cout << "Count of 5: " << int_container.count(5) << std::endl;
    std::cout << "Count of even numbers: " << int_container.count_if(IsEven{}) << std::endl;
    
    // Transform operations
    int_container.transform(Square{});
    int_container.display("After squaring");
    
    // Sort operations
    int_container.sort(Less{});
    int_container.display("After sorting (ascending)");
    
    int_container.sort(Greater{});
    int_container.display("After sorting (descending)");
    
    // Remove operations
    int_container.remove_if(IsEven{});
    int_container.display("After removing evens");
    
    // Accumulate operations
    int sum = int_container.accumulate(0, [](int a, int b) { return a + b; });
    std::cout << "Sum of remaining numbers: " << sum << std::endl;
    
    // String container
    GenericContainer<std::string> string_container = {"apple", "banana", "cherry", "date", "elderberry"};
    string_container.display("String container");
    
    // String operations
    auto banana_it = string_container.find("banana");
    if (banana_it != string_container.end()) {
        std::cout << "Found 'banana' in string container" << std::endl;
    }
    
    auto long_strings = string_container.count_if([](const std::string& s) { return s.length() > 5; });
    std::cout << "Count of long strings: " << long_strings << std::endl;
    
    // Sort strings by length
    string_container.sort(StringLength{});
    string_container.display("After sorting by length");
    
    // Find strings containing specific substring
    auto contains_a = string_container.find_if(StringContains("a"));
    if (contains_a != string_container.end()) {
        std::cout << "First string containing 'a': " << *contains_a << std::endl;
    }
}

// Function to demonstrate iterator adapters
void demonstrateIteratorAdapters() {
    std::cout << "\n=== Iterator Adapters Demonstration ===" << std::endl;
    
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    std::cout << "Original numbers: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Reverse iterator
    std::cout << "Reverse order: ";
    for (auto it = numbers.rbegin(); it != numbers.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Custom reverse iterator
    reverse_iterator<std::vector<int>::iterator> rev_it(numbers.end());
    reverse_iterator<std::vector<int>::iterator> rev_end(numbers.begin());
    
    std::cout << "Custom reverse order: ";
    while (rev_it != rev_end) {
        std::cout << *rev_it << " ";
        ++rev_it;
    }
    std::cout << std::endl;
}

// Function to demonstrate range operations
void demonstrateRangeOperations() {
    std::cout << "\n=== Range Operations Demonstration ===" << std::endl;
    
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    std::cout << "Original numbers: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Filter range
    auto even_numbers = filter_range(numbers, IsEven{});
    std::cout << "Even numbers: ";
    for (const auto& num : even_numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    auto prime_numbers = filter_range(numbers, IsPrime{});
    std::cout << "Prime numbers: ";
    for (const auto& num : prime_numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Transform range
    auto squares = transform_range(numbers, Square{});
    std::cout << "Squares: ";
    for (const auto& square : squares) {
        std::cout << square << " ";
    }
    std::cout << std::endl;
    
    auto cubes = transform_range(numbers, Cube{});
    std::cout << "Cubes: ";
    for (const auto& cube : cubes) {
        std::cout << cube << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "=== Generic Programming Demonstration ===" << std::endl;
    std::cout << "This program demonstrates generic algorithms, iterator concepts,\n"
              << "function objects, and modern generic programming patterns.\n" << std::endl;
    
    // Demonstrate various generic programming concepts
    demonstrateGenericAlgorithms();
    demonstrateFunctionObjects();
    demonstrateGenericContainers();
    demonstrateIteratorAdapters();
    demonstrateRangeOperations();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Generic programming enables code reuse across different types" << std::endl;
    std::cout << "2. Generic algorithms work with any type that meets the requirements" << std::endl;
    std::cout << "3. Iterator concepts provide type-safe access to container elements" << std::endl;
    std::cout << "4. Function objects offer more flexibility than function pointers" << std::endl;
    std::cout << "5. Generic containers provide type-safe storage and operations" << std::endl;
    std::cout << "6. Iterator adapters extend the functionality of existing iterators" << std::endl;
    std::cout << "7. Range operations simplify working with collections" << std::endl;
    std::cout << "8. Generic programming promotes code efficiency and maintainability" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o generic_programming 01_Generic_Programming.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o generic_programming 01_Generic_Programming.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 01_Generic_Programming.cpp
 * 
 * Running:
 * ./generic_programming (Linux/macOS)
 * generic_programming.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for some features.
 * C++17 is recommended for best generic programming support.
 * 
 * Generic Programming Notes:
 * - Generic algorithms work with any type meeting requirements
 * - Iterator concepts provide type-safe access to elements
 * - Function objects offer flexibility and state management
 * - Generic containers provide type-safe storage and operations
 * - Iterator adapters extend existing iterator functionality
 * - Range operations simplify collection manipulation
 * - Generic programming promotes code reuse and efficiency
 * - Template metaprogramming enables compile-time optimizations
 */"""
