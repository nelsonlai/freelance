#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <deque>
#include <array>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <fstream>

// Demonstrates iterators and ranges
int main() {
    std::cout << "Iterators and Ranges Demonstration" << std::endl;
    std::cout << "==================================" << std::endl;
    
    // 1. Iterator categories
    std::cout << "\n1. ITERATOR CATEGORIES:" << std::endl;
    
    // Random access iterator (vector)
    std::cout << "\nRandom Access Iterator (vector):" << std::endl;
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    auto vec_it = vec.begin();
    std::cout << "Begin: " << *vec_it << std::endl;
    
    vec_it += 3;  // Random access
    std::cout << "After += 3: " << *vec_it << std::endl;
    
    vec_it -= 1;  // Random access
    std::cout << "After -= 1: " << *vec_it << std::endl;
    
    std::cout << "Distance from begin: " << (vec_it - vec.begin()) << std::endl;
    
    // Bidirectional iterator (list)
    std::cout << "\nBidirectional Iterator (list):" << std::endl;
    std::list<int> lst = {1, 2, 3, 4, 5};
    
    auto list_it = lst.begin();
    std::cout << "Begin: " << *list_it << std::endl;
    
    ++list_it;  // Forward
    std::cout << "After ++: " << *list_it << std::endl;
    
    --list_it;  // Backward
    std::cout << "After --: " << *list_it << std::endl;
    
    // Forward iterator (set)
    std::cout << "\nForward Iterator (set):" << std::endl;
    std::set<int> s = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    auto set_it = s.begin();
    std::cout << "Set elements: ";
    for (auto it = set_it; it != s.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // 2. Range-based for loops
    std::cout << "\n2. RANGE-BASED FOR LOOPS:" << std::endl;
    
    // Vector iteration
    std::cout << "\nVector iteration:" << std::endl;
    std::cout << "Values: ";
    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Map iteration
    std::cout << "\nMap iteration:" << std::endl;
    std::map<std::string, int> m = {
        {"apple", 5},
        {"banana", 3},
        {"orange", 8},
        {"grape", 2}
    };
    
    for (const auto& pair : m) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    
    // Array iteration
    std::cout << "\nArray iteration:" << std::endl;
    std::array<int, 5> arr = {10, 20, 30, 40, 50};
    
    for (const auto& val : arr) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // 3. Iterator adaptors
    std::cout << "\n3. ITERATOR ADAPTORS:" << std::endl;
    
    // Insert iterators
    std::cout << "\nInsert iterators:" << std::endl;
    std::vector<int> source = {1, 2, 3, 4, 5};
    std::vector<int> dest;
    
    // Back inserter
    std::copy(source.begin(), source.end(), std::back_inserter(dest));
    std::cout << "After back_inserter: ";
    for (const auto& val : dest) std::cout << val << " ";
    std::cout << std::endl;
    
    // Front inserter (with deque)
    std::deque<int> dq;
    std::copy(source.begin(), source.end(), std::front_inserter(dq));
    std::cout << "After front_inserter: ";
    for (const auto& val : dq) std::cout << val << " ";
    std::cout << std::endl;
    
    // Inserter
    std::set<int> target_set;
    std::copy(source.begin(), source.end(), std::inserter(target_set, target_set.begin()));
    std::cout << "After inserter: ";
    for (const auto& val : target_set) std::cout << val << " ";
    std::cout << std::endl;
    
    // Stream iterators
    std::cout << "\nStream iterators:" << std::endl;
    
    // Ostream iterator
    std::vector<int> stream_vec = {1, 2, 3, 4, 5};
    std::cout << "Ostream iterator: ";
    std::copy(stream_vec.begin(), stream_vec.end(), 
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    
    // Istream iterator (from string)
    std::stringstream ss("10 20 30 40 50");
    std::vector<int> input_vec;
    std::copy(std::istream_iterator<int>(ss), std::istream_iterator<int>(),
              std::back_inserter(input_vec));
    
    std::cout << "Istream iterator result: ";
    for (const auto& val : input_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    // Reverse iterators
    std::cout << "\nReverse iterators:" << std::endl;
    std::vector<int> reverse_vec = {1, 2, 3, 4, 5};
    
    std::cout << "Forward: ";
    for (auto it = reverse_vec.begin(); it != reverse_vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Reverse: ";
    for (auto it = reverse_vec.rbegin(); it != reverse_vec.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Move iterators
    std::cout << "\nMove iterators:" << std::endl;
    std::vector<std::string> source_strings = {"hello", "world", "cpp"};
    std::vector<std::string> dest_strings;
    
    std::move(source_strings.begin(), source_strings.end(),
              std::back_inserter(dest_strings));
    
    std::cout << "Source after move: ";
    for (const auto& str : source_strings) std::cout << "\"" << str << "\" ";
    std::cout << std::endl;
    
    std::cout << "Destination after move: ";
    for (const auto& str : dest_strings) std::cout << "\"" << str << "\" ";
    std::cout << std::endl;
    
    // 4. Iterator utilities
    std::cout << "\n4. ITERATOR UTILITIES:" << std::endl;
    
    std::vector<int> util_vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Distance
    auto it1 = util_vec.begin();
    auto it2 = util_vec.begin() + 5;
    std::cout << "Distance between iterators: " << std::distance(it1, it2) << std::endl;
    
    // Advance
    auto it3 = util_vec.begin();
    std::advance(it3, 3);
    std::cout << "After advance by 3: " << *it3 << std::endl;
    
    // Next/Prev
    auto it4 = util_vec.begin();
    auto next_it = std::next(it4, 2);
    auto prev_it = std::prev(next_it, 1);
    
    std::cout << "Next(2): " << *next_it << std::endl;
    std::cout << "Prev(1): " << *prev_it << std::endl;
    
    // Begin/End
    auto begin_it = std::begin(util_vec);
    auto end_it = std::end(util_vec);
    
    std::cout << "Begin: " << *begin_it << std::endl;
    std::cout << "End - 1: " << *(end_it - 1) << std::endl;
    
    // 5. Iterator invalidation
    std::cout << "\n5. ITERATOR INVALIDATION:" << std::endl;
    
    std::vector<int> inval_vec = {1, 2, 3, 4, 5};
    
    std::cout << "Original vector: ";
    for (const auto& val : inval_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    // Iterator becomes invalid after insertion
    auto invalid_it = inval_vec.begin() + 2;
    std::cout << "Iterator points to: " << *invalid_it << std::endl;
    
    inval_vec.insert(inval_vec.begin() + 1, 99);  // Insert at position 1
    
    std::cout << "After insertion: ";
    for (const auto& val : inval_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    // Note: invalid_it is now invalid and should not be used
    
    // 6. Iterator traits
    std::cout << "\n6. ITERATOR TRAITS:" << std::endl;
    
    using vec_iterator = std::vector<int>::iterator;
    using list_iterator = std::list<int>::iterator;
    
    std::cout << "Vector iterator category: " << 
        typeid(std::iterator_traits<vec_iterator>::iterator_category).name() << std::endl;
    std::cout << "List iterator category: " << 
        typeid(std::iterator_traits<list_iterator>::iterator_category).name() << std::endl;
    
    std::cout << "Vector iterator value type: " << 
        typeid(std::iterator_traits<vec_iterator>::value_type).name() << std::endl;
    std::cout << "Vector iterator difference type: " << 
        typeid(std::iterator_traits<vec_iterator>::difference_type).name() << std::endl;
    
    // 7. Custom iterator example
    std::cout << "\n7. CUSTOM ITERATOR EXAMPLE:" << std::endl;
    
    class SimpleContainer {
    private:
        int data[5] = {10, 20, 30, 40, 50};
        
    public:
        class iterator {
        private:
            int* ptr;
            
        public:
            iterator(int* p) : ptr(p) {}
            
            int& operator*() { return *ptr; }
            iterator& operator++() { ++ptr; return *this; }
            iterator operator++(int) { iterator temp = *this; ++ptr; return temp; }
            
            bool operator==(const iterator& other) const { return ptr == other.ptr; }
            bool operator!=(const iterator& other) const { return ptr != other.ptr; }
        };
        
        iterator begin() { return iterator(data); }
        iterator end() { return iterator(data + 5); }
    };
    
    SimpleContainer container;
    
    std::cout << "Custom container: ";
    for (const auto& val : container) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // 8. Iterator with algorithms
    std::cout << "\n8. ITERATORS WITH ALGORITHMS:" << std::endl;
    
    std::vector<int> algo_vec = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    // Find using iterators
    auto find_it = std::find(algo_vec.begin(), algo_vec.end(), 8);
    if (find_it != algo_vec.end()) {
        std::cout << "Found 8 at position: " << (find_it - algo_vec.begin()) << std::endl;
    }
    
    // Sort using iterators
    std::sort(algo_vec.begin(), algo_vec.end());
    
    std::cout << "Sorted vector: ";
    for (const auto& val : algo_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    // Transform using iterators
    std::vector<int> transform_result(algo_vec.size());
    std::transform(algo_vec.begin(), algo_vec.end(), transform_result.begin(),
                   [](int x) { return x * 2; });
    
    std::cout << "Transformed vector: ";
    for (const auto& val : transform_result) std::cout << val << " ";
    std::cout << std::endl;
    
    // 9. Iterator with different containers
    std::cout << "\n9. ITERATORS WITH DIFFERENT CONTAINERS:" << std::endl;
    
    // Deque
    std::deque<int> dq = {1, 2, 3, 4, 5};
    std::cout << "Deque: ";
    for (auto it = dq.begin(); it != dq.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Set
    std::set<int> set_container = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    std::cout << "Set: ";
    for (auto it = set_container.begin(); it != set_container.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Map
    std::map<std::string, int> map_container = {
        {"first", 1},
        {"second", 2},
        {"third", 3}
    };
    
    std::cout << "Map: ";
    for (auto it = map_container.begin(); it != map_container.end(); ++it) {
        std::cout << it->first << ":" << it->second << " ";
    }
    std::cout << std::endl;
    
    // 10. Iterator performance
    std::cout << "\n10. ITERATOR PERFORMANCE:" << std::endl;
    
    const size_t size = 1000000;
    std::vector<int> perf_vec(size);
    std::iota(perf_vec.begin(), perf_vec.end(), 0);
    
    // Iterator traversal
    auto start = std::chrono::high_resolution_clock::now();
    
    int sum = 0;
    for (auto it = perf_vec.begin(); it != perf_vec.end(); ++it) {
        sum += *it;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Iterator traversal time: " << duration.count() << " ms" << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    
    // Range-based for loop
    start = std::chrono::high_resolution_clock::now();
    
    sum = 0;
    for (const auto& val : perf_vec) {
        sum += val;
    }
    
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Range-based for loop time: " << duration.count() << " ms" << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    
    std::cout << "\nIterators and ranges demonstration completed!" << std::endl;
    return 0;
}
