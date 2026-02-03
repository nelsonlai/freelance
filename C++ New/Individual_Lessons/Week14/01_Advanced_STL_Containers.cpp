/*
 * Lesson 14.1: Advanced STL Containers
 * 
 * This file demonstrates advanced STL containers, custom allocators,
 * container adapters, and specialized containers.
 */

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <multiset>
#include <map>
#include <multimap>
#include <unordered_set>
#include <unordered_multiset>
#include <unordered_map>
#include <unordered_multimap>
#include <stack>
#include <queue>
#include <priority_queue>
#include <array>
#include <bitset>
#include <valarray>
#include <complex>
#include <tuple>
#include <pair>
#include <string>
#include <string_view>
#include <memory>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>
#include <random>
#include <chrono>

// Example 1: Advanced Vector Operations
namespace AdvancedVector {
    
    // Custom allocator for demonstration
    template<typename T>
    class CustomAllocator {
    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using reference = T&;
        using const_reference = const T&;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        
        template<typename U>
        struct rebind {
            using other = CustomAllocator<U>;
        };
        
        CustomAllocator() = default;
        template<typename U>
        CustomAllocator(const CustomAllocator<U>&) {}
        
        pointer allocate(size_type n) {
            std::cout << "CustomAllocator: Allocating " << n << " elements of size " << sizeof(T) << std::endl;
            return static_cast<pointer>(std::malloc(n * sizeof(T)));
        }
        
        void deallocate(pointer p, size_type n) {
            std::cout << "CustomAllocator: Deallocating " << n << " elements" << std::endl;
            std::free(p);
        }
        
        template<typename U>
        void construct(U* p, const U& value) {
            new(p) U(value);
        }
        
        template<typename U>
        void destroy(U* p) {
            p->~U();
        }
        
        bool operator==(const CustomAllocator&) const { return true; }
        bool operator!=(const CustomAllocator&) const { return false; }
    };
    
    // Vector with custom allocator
    using CustomVector = std::vector<int, CustomAllocator<int>>;
    
    // Advanced vector operations
    void demonstrateAdvancedVector() {
        std::cout << "=== Advanced Vector Operations ===" << std::endl;
        
        // Reserve and capacity management
        std::vector<int> vec;
        vec.reserve(1000);
        std::cout << "Capacity after reserve(1000): " << vec.capacity() << std::endl;
        
        // Emplace operations
        vec.emplace_back(42);
        vec.emplace_back(84);
        vec.emplace_back(126);
        
        // Insert with iterators
        vec.insert(vec.begin() + 1, {10, 20, 30});
        
        // Erase with iterators
        vec.erase(vec.begin() + 2, vec.begin() + 4);
        
        // Shrink to fit
        vec.shrink_to_fit();
        std::cout << "Capacity after shrink_to_fit: " << vec.capacity() << std::endl;
        
        // Data access
        std::cout << "Vector contents: ";
        for (const auto& elem : vec) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Custom allocator vector
        CustomVector custom_vec;
        custom_vec.reserve(10);
        custom_vec.emplace_back(1);
        custom_vec.emplace_back(2);
        custom_vec.emplace_back(3);
        
        std::cout << "Custom allocator vector: ";
        for (const auto& elem : custom_vec) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

// Example 2: Deque Operations
namespace DequeOperations {
    
    void demonstrateDeque() {
        std::cout << "\n=== Deque Operations ===" << std::endl;
        
        std::deque<int> dq;
        
        // Push operations
        dq.push_front(1);
        dq.push_front(2);
        dq.push_back(3);
        dq.push_back(4);
        
        std::cout << "Deque after push operations: ";
        for (const auto& elem : dq) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Pop operations
        dq.pop_front();
        dq.pop_back();
        
        std::cout << "Deque after pop operations: ";
        for (const auto& elem : dq) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Insert operations
        dq.insert(dq.begin() + 1, 10);
        dq.insert(dq.end(), {20, 30, 40});
        
        std::cout << "Deque after insert operations: ";
        for (const auto& elem : dq) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Erase operations
        dq.erase(dq.begin() + 2);
        dq.erase(dq.begin() + 1, dq.begin() + 3);
        
        std::cout << "Deque after erase operations: ";
        for (const auto& elem : dq) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

// Example 3: List Operations
namespace ListOperations {
    
    void demonstrateList() {
        std::cout << "\n=== List Operations ===" << std::endl;
        
        std::list<int> lst = {1, 2, 3, 4, 5};
        
        // Splice operations
        std::list<int> other_lst = {10, 20, 30};
        lst.splice(lst.begin(), other_lst);
        
        std::cout << "List after splice: ";
        for (const auto& elem : lst) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Merge operations
        std::list<int> merge_lst = {15, 25, 35};
        lst.merge(merge_lst);
        
        std::cout << "List after merge: ";
        for (const auto& elem : lst) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Unique operations
        lst.unique();
        
        std::cout << "List after unique: ";
        for (const auto& elem : lst) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Sort operations
        lst.sort();
        
        std::cout << "List after sort: ";
        for (const auto& elem : lst) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Reverse operations
        lst.reverse();
        
        std::cout << "List after reverse: ";
        for (const auto& elem : lst) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

// Example 4: Forward List Operations
namespace ForwardListOperations {
    
    void demonstrateForwardList() {
        std::cout << "\n=== Forward List Operations ===" << std::endl;
        
        std::forward_list<int> flst = {1, 2, 3, 4, 5};
        
        // Insert after operations
        flst.insert_after(flst.before_begin(), 0);
        flst.insert_after(flst.begin(), {10, 20, 30});
        
        std::cout << "Forward list after insert_after: ";
        for (const auto& elem : flst) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Erase after operations
        flst.erase_after(flst.before_begin());
        flst.erase_after(flst.begin(), flst.end());
        
        std::cout << "Forward list after erase_after: ";
        for (const auto& elem : flst) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Splice after operations
        std::forward_list<int> other_flst = {100, 200, 300};
        flst.splice_after(flst.before_begin(), other_flst);
        
        std::cout << "Forward list after splice_after: ";
        for (const auto& elem : flst) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

// Example 5: Set and Multiset Operations
namespace SetOperations {
    
    void demonstrateSet() {
        std::cout << "\n=== Set Operations ===" << std::endl;
        
        std::set<int> s = {5, 2, 8, 1, 9, 3};
        
        // Insert operations
        s.insert(4);
        s.insert({6, 7, 10});
        
        std::cout << "Set after insert: ";
        for (const auto& elem : s) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Find operations
        auto it = s.find(5);
        if (it != s.end()) {
            std::cout << "Found 5 in set" << std::endl;
        }
        
        // Lower and upper bound
        auto lower = s.lower_bound(4);
        auto upper = s.upper_bound(7);
        
        std::cout << "Elements in range [4, 7): ";
        for (auto it = lower; it != upper; ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        
        // Equal range
        auto range = s.equal_range(5);
        std::cout << "Equal range for 5: [" << *range.first << ", " << *range.second << ")" << std::endl;
        
        // Count operations
        std::cout << "Count of 5: " << s.count(5) << std::endl;
        std::cout << "Count of 11: " << s.count(11) << std::endl;
    }
    
    void demonstrateMultiset() {
        std::cout << "\n=== Multiset Operations ===" << std::endl;
        
        std::multiset<int> ms = {5, 2, 8, 1, 9, 3, 5, 2, 8};
        
        std::cout << "Multiset contents: ";
        for (const auto& elem : ms) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Count operations
        std::cout << "Count of 5: " << ms.count(5) << std::endl;
        std::cout << "Count of 2: " << ms.count(2) << std::endl;
        std::cout << "Count of 8: " << ms.count(8) << std::endl;
        
        // Equal range
        auto range = ms.equal_range(5);
        std::cout << "Equal range for 5: ";
        for (auto it = range.first; it != range.second; ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        
        // Erase operations
        ms.erase(5);
        std::cout << "Multiset after erasing all 5s: ";
        for (const auto& elem : ms) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

// Example 6: Map and Multimap Operations
namespace MapOperations {
    
    void demonstrateMap() {
        std::cout << "\n=== Map Operations ===" << std::endl;
        
        std::map<std::string, int> m;
        
        // Insert operations
        m.insert({"apple", 5});
        m.insert(std::make_pair("banana", 3));
        m["cherry"] = 8;
        m.emplace("date", 2);
        
        std::cout << "Map contents: ";
        for (const auto& pair : m) {
            std::cout << "{" << pair.first << ", " << pair.second << "} ";
        }
        std::cout << std::endl;
        
        // Find operations
        auto it = m.find("banana");
        if (it != m.end()) {
            std::cout << "Found banana: " << it->second << std::endl;
        }
        
        // Lower and upper bound
        auto lower = m.lower_bound("b");
        auto upper = m.upper_bound("d");
        
        std::cout << "Elements with keys starting with 'b' or 'c': ";
        for (auto it = lower; it != upper; ++it) {
            std::cout << "{" << it->first << ", " << it->second << "} ";
        }
        std::cout << std::endl;
        
        // Equal range
        auto range = m.equal_range("banana");
        std::cout << "Equal range for banana: [" << range.first->first << ", " << range.second->first << ")" << std::endl;
        
        // Count operations
        std::cout << "Count of banana: " << m.count("banana") << std::endl;
        std::cout << "Count of grape: " << m.count("grape") << std::endl;
    }
    
    void demonstrateMultimap() {
        std::cout << "\n=== Multimap Operations ===" << std::endl;
        
        std::multimap<std::string, int> mm;
        
        // Insert operations
        mm.insert({"apple", 5});
        mm.insert({"banana", 3});
        mm.insert({"apple", 7});
        mm.insert({"banana", 2});
        mm.insert({"cherry", 8});
        
        std::cout << "Multimap contents: ";
        for (const auto& pair : mm) {
            std::cout << "{" << pair.first << ", " << pair.second << "} ";
        }
        std::cout << std::endl;
        
        // Count operations
        std::cout << "Count of apple: " << mm.count("apple") << std::endl;
        std::cout << "Count of banana: " << mm.count("banana") << std::endl;
        std::cout << "Count of cherry: " << mm.count("cherry") << std::endl;
        
        // Equal range
        auto range = mm.equal_range("apple");
        std::cout << "Equal range for apple: ";
        for (auto it = range.first; it != range.second; ++it) {
            std::cout << "{" << it->first << ", " << it->second << "} ";
        }
        std::cout << std::endl;
        
        // Erase operations
        mm.erase("apple");
        std::cout << "Multimap after erasing all apples: ";
        for (const auto& pair : mm) {
            std::cout << "{" << pair.first << ", " << pair.second << "} ";
        }
        std::cout << std::endl;
    }
}

// Example 7: Unordered Containers
namespace UnorderedOperations {
    
    void demonstrateUnorderedSet() {
        std::cout << "\n=== Unordered Set Operations ===" << std::endl;
        
        std::unordered_set<int> us = {5, 2, 8, 1, 9, 3};
        
        // Insert operations
        us.insert(4);
        us.insert({6, 7, 10});
        
        std::cout << "Unordered set contents: ";
        for (const auto& elem : us) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Bucket operations
        std::cout << "Bucket count: " << us.bucket_count() << std::endl;
        std::cout << "Load factor: " << us.load_factor() << std::endl;
        std::cout << "Max load factor: " << us.max_load_factor() << std::endl;
        
        // Rehash operations
        us.rehash(20);
        std::cout << "Bucket count after rehash: " << us.bucket_count() << std::endl;
        
        // Reserve operations
        us.reserve(50);
        std::cout << "Bucket count after reserve: " << us.bucket_count() << std::endl;
        
        // Find operations
        auto it = us.find(5);
        if (it != us.end()) {
            std::cout << "Found 5 in unordered set" << std::endl;
        }
        
        // Count operations
        std::cout << "Count of 5: " << us.count(5) << std::endl;
        std::cout << "Count of 11: " << us.count(11) << std::endl;
    }
    
    void demonstrateUnorderedMap() {
        std::cout << "\n=== Unordered Map Operations ===" << std::endl;
        
        std::unordered_map<std::string, int> um;
        
        // Insert operations
        um.insert({"apple", 5});
        um.insert(std::make_pair("banana", 3));
        um["cherry"] = 8;
        um.emplace("date", 2);
        
        std::cout << "Unordered map contents: ";
        for (const auto& pair : um) {
            std::cout << "{" << pair.first << ", " << pair.second << "} ";
        }
        std::cout << std::endl;
        
        // Bucket operations
        std::cout << "Bucket count: " << um.bucket_count() << std::endl;
        std::cout << "Load factor: " << um.load_factor() << std::endl;
        
        // Find operations
        auto it = um.find("banana");
        if (it != um.end()) {
            std::cout << "Found banana: " << it->second << std::endl;
        }
        
        // Count operations
        std::cout << "Count of banana: " << um.count("banana") << std::endl;
        std::cout << "Count of grape: " << um.count("grape") << std::endl;
    }
}

// Example 8: Container Adapters
namespace ContainerAdapters {
    
    void demonstrateStack() {
        std::cout << "\n=== Stack Operations ===" << std::endl;
        
        std::stack<int> stk;
        
        // Push operations
        stk.push(1);
        stk.push(2);
        stk.push(3);
        stk.push(4);
        stk.push(5);
        
        std::cout << "Stack size: " << stk.size() << std::endl;
        std::cout << "Stack top: " << stk.top() << std::endl;
        
        // Pop operations
        while (!stk.empty()) {
            std::cout << "Popping: " << stk.top() << std::endl;
            stk.pop();
        }
    }
    
    void demonstrateQueue() {
        std::cout << "\n=== Queue Operations ===" << std::endl;
        
        std::queue<int> q;
        
        // Push operations
        q.push(1);
        q.push(2);
        q.push(3);
        q.push(4);
        q.push(5);
        
        std::cout << "Queue size: " << q.size() << std::endl;
        std::cout << "Queue front: " << q.front() << std::endl;
        std::cout << "Queue back: " << q.back() << std::endl;
        
        // Pop operations
        while (!q.empty()) {
            std::cout << "Popping: " << q.front() << std::endl;
            q.pop();
        }
    }
    
    void demonstratePriorityQueue() {
        std::cout << "\n=== Priority Queue Operations ===" << std::endl;
        
        std::priority_queue<int> pq;
        
        // Push operations
        pq.push(5);
        pq.push(2);
        pq.push(8);
        pq.push(1);
        pq.push(9);
        pq.push(3);
        
        std::cout << "Priority queue size: " << pq.size() << std::endl;
        std::cout << "Priority queue top: " << pq.top() << std::endl;
        
        // Pop operations
        std::cout << "Popping elements in priority order: ";
        while (!pq.empty()) {
            std::cout << pq.top() << " ";
            pq.pop();
        }
        std::cout << std::endl;
        
        // Custom comparator
        std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;
        min_pq.push(5);
        min_pq.push(2);
        min_pq.push(8);
        min_pq.push(1);
        min_pq.push(9);
        min_pq.push(3);
        
        std::cout << "Min priority queue (ascending order): ";
        while (!min_pq.empty()) {
            std::cout << min_pq.top() << " ";
            min_pq.pop();
        }
        std::cout << std::endl;
    }
}

// Example 9: Specialized Containers
namespace SpecializedContainers {
    
    void demonstrateArray() {
        std::cout << "\n=== Array Operations ===" << std::endl;
        
        std::array<int, 5> arr = {1, 2, 3, 4, 5};
        
        std::cout << "Array size: " << arr.size() << std::endl;
        std::cout << "Array max size: " << arr.max_size() << std::endl;
        std::cout << "Array empty: " << arr.empty() << std::endl;
        
        // Element access
        std::cout << "Array[0]: " << arr[0] << std::endl;
        std::cout << "Array.at(1): " << arr.at(1) << std::endl;
        std::cout << "Array.front(): " << arr.front() << std::endl;
        std::cout << "Array.back(): " << arr.back() << std::endl;
        std::cout << "Array.data(): " << arr.data() << std::endl;
        
        // Fill operations
        arr.fill(10);
        std::cout << "Array after fill(10): ";
        for (const auto& elem : arr) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Swap operations
        std::array<int, 5> other_arr = {20, 30, 40, 50, 60};
        arr.swap(other_arr);
        
        std::cout << "Array after swap: ";
        for (const auto& elem : arr) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
    
    void demonstrateBitset() {
        std::cout << "\n=== Bitset Operations ===" << std::endl;
        
        std::bitset<8> bs1("10101010");
        std::bitset<8> bs2("11110000");
        
        std::cout << "Bitset 1: " << bs1 << std::endl;
        std::cout << "Bitset 2: " << bs2 << std::endl;
        
        // Bitwise operations
        std::cout << "bs1 & bs2: " << (bs1 & bs2) << std::endl;
        std::cout << "bs1 | bs2: " << (bs1 | bs2) << std::endl;
        std::cout << "bs1 ^ bs2: " << (bs1 ^ bs2) << std::endl;
        std::cout << "~bs1: " << (~bs1) << std::endl;
        
        // Shift operations
        std::cout << "bs1 << 2: " << (bs1 << 2) << std::endl;
        std::cout << "bs1 >> 2: " << (bs1 >> 2) << std::endl;
        
        // Count operations
        std::cout << "bs1 count: " << bs1.count() << std::endl;
        std::cout << "bs1 size: " << bs1.size() << std::endl;
        std::cout << "bs1 any: " << bs1.any() << std::endl;
        std::cout << "bs1 none: " << bs1.none() << std::endl;
        std::cout << "bs1 all: " << bs1.all() << std::endl;
        
        // Element access
        std::cout << "bs1[0]: " << bs1[0] << std::endl;
        std::cout << "bs1[1]: " << bs1[1] << std::endl;
        
        // Set operations
        bs1.set(0);
        bs1.set(2, false);
        std::cout << "bs1 after set operations: " << bs1 << std::endl;
        
        bs1.reset(1);
        std::cout << "bs1 after reset(1): " << bs1 << std::endl;
        
        bs1.flip();
        std::cout << "bs1 after flip: " << bs1 << std::endl;
        
        // String conversion
        std::cout << "bs1 to string: " << bs1.to_string() << std::endl;
        std::cout << "bs1 to ulong: " << bs1.to_ulong() << std::endl;
    }
    
    void demonstrateValarray() {
        std::cout << "\n=== Valarray Operations ===" << std::endl;
        
        std::valarray<int> va1 = {1, 2, 3, 4, 5};
        std::valarray<int> va2 = {10, 20, 30, 40, 50};
        
        std::cout << "Valarray 1: ";
        for (const auto& elem : va1) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        std::cout << "Valarray 2: ";
        for (const auto& elem : va2) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Arithmetic operations
        std::valarray<int> sum = va1 + va2;
        std::cout << "va1 + va2: ";
        for (const auto& elem : sum) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        std::valarray<int> diff = va2 - va1;
        std::cout << "va2 - va1: ";
        for (const auto& elem : diff) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        std::valarray<int> mult = va1 * va2;
        std::cout << "va1 * va2: ";
        for (const auto& elem : mult) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Scalar operations
        std::valarray<int> scaled = va1 * 2;
        std::cout << "va1 * 2: ";
        for (const auto& elem : scaled) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Mathematical functions
        std::valarray<double> dva = {1.0, 4.0, 9.0, 16.0, 25.0};
        std::valarray<double> sqrt_vals = std::sqrt(dva);
        
        std::cout << "Square roots: ";
        for (const auto& elem : sqrt_vals) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        
        // Slice operations
        std::valarray<int> slice_vals = va1[std::slice(1, 3, 1)];
        std::cout << "Slice [1:4]: ";
        for (const auto& elem : slice_vals) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

// Example 10: Container Performance Comparison
namespace ContainerPerformance {
    
    void demonstratePerformanceComparison() {
        std::cout << "\n=== Container Performance Comparison ===" << std::endl;
        
        const size_t size = 100000;
        
        // Vector performance
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<int> vec;
        for (size_t i = 0; i < size; ++i) {
            vec.push_back(i);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto vec_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Vector push_back time: " << vec_time.count() << " microseconds" << std::endl;
        
        // Deque performance
        start = std::chrono::high_resolution_clock::now();
        std::deque<int> dq;
        for (size_t i = 0; i < size; ++i) {
            dq.push_back(i);
        }
        end = std::chrono::high_resolution_clock::now();
        auto dq_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Deque push_back time: " << dq_time.count() << " microseconds" << std::endl;
        
        // List performance
        start = std::chrono::high_resolution_clock::now();
        std::list<int> lst;
        for (size_t i = 0; i < size; ++i) {
            lst.push_back(i);
        }
        end = std::chrono::high_resolution_clock::now();
        auto lst_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "List push_back time: " << lst_time.count() << " microseconds" << std::endl;
        
        // Set performance
        start = std::chrono::high_resolution_clock::now();
        std::set<int> s;
        for (size_t i = 0; i < size; ++i) {
            s.insert(i);
        }
        end = std::chrono::high_resolution_clock::now();
        auto set_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Set insert time: " << set_time.count() << " microseconds" << std::endl;
        
        // Unordered set performance
        start = std::chrono::high_resolution_clock::now();
        std::unordered_set<int> us;
        for (size_t i = 0; i < size; ++i) {
            us.insert(i);
        }
        end = std::chrono::high_resolution_clock::now();
        auto us_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Unordered set insert time: " << us_time.count() << " microseconds" << std::endl;
        
        // Search performance comparison
        const int search_value = size / 2;
        
        // Vector search
        start = std::chrono::high_resolution_clock::now();
        auto vec_it = std::find(vec.begin(), vec.end(), search_value);
        end = std::chrono::high_resolution_clock::now();
        auto vec_search_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        std::cout << "Vector find time: " << vec_search_time.count() << " nanoseconds" << std::endl;
        
        // Set search
        start = std::chrono::high_resolution_clock::now();
        auto set_it = s.find(search_value);
        end = std::chrono::high_resolution_clock::now();
        auto set_search_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        std::cout << "Set find time: " << set_search_time.count() << " nanoseconds" << std::endl;
        
        // Unordered set search
        start = std::chrono::high_resolution_clock::now();
        auto us_it = us.find(search_value);
        end = std::chrono::high_resolution_clock::now();
        auto us_search_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        std::cout << "Unordered set find time: " << us_search_time.count() << " nanoseconds" << std::endl;
    }
}

int main() {
    std::cout << "=== Advanced STL Containers Demonstration ===" << std::endl;
    std::cout << "This program demonstrates advanced STL containers, custom allocators,\n"
              << "container adapters, and specialized containers.\n" << std::endl;
    
    // Demonstrate various advanced container concepts
    AdvancedVector::demonstrateAdvancedVector();
    DequeOperations::demonstrateDeque();
    ListOperations::demonstrateList();
    ForwardListOperations::demonstrateForwardList();
    SetOperations::demonstrateSet();
    SetOperations::demonstrateMultiset();
    MapOperations::demonstrateMap();
    MapOperations::demonstrateMultimap();
    UnorderedOperations::demonstrateUnorderedSet();
    UnorderedOperations::demonstrateUnorderedMap();
    ContainerAdapters::demonstrateStack();
    ContainerAdapters::demonstrateQueue();
    ContainerAdapters::demonstratePriorityQueue();
    SpecializedContainers::demonstrateArray();
    SpecializedContainers::demonstrateBitset();
    SpecializedContainers::demonstrateValarray();
    ContainerPerformance::demonstratePerformanceComparison();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Advanced vector operations include reserve, shrink_to_fit, and emplace" << std::endl;
    std::cout << "2. Deque provides efficient insertion/deletion at both ends" << std::endl;
    std::cout << "3. List offers efficient insertion/deletion anywhere and splice operations" << std::endl;
    std::cout << "4. Forward list is memory-efficient for single-direction traversal" << std::endl;
    std::cout << "5. Set and multiset provide ordered unique and non-unique elements" << std::endl;
    std::cout << "6. Map and multimap provide ordered key-value pairs" << std::endl;
    std::cout << "7. Unordered containers offer average O(1) operations with hash tables" << std::endl;
    std::cout << "8. Container adapters (stack, queue, priority_queue) provide specialized interfaces" << std::endl;
    std::cout << "9. Specialized containers (array, bitset, valarray) serve specific purposes" << std::endl;
    std::cout << "10. Container choice affects performance characteristics significantly" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o advanced_stl_containers 01_Advanced_STL_Containers.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o advanced_stl_containers 01_Advanced_STL_Containers.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 01_Advanced_STL_Containers.cpp
 * 
 * Running:
 * ./advanced_stl_containers (Linux/macOS)
 * advanced_stl_containers.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for some features.
 * C++17 is recommended for best container support.
 * 
 * Advanced STL Containers Notes:
 * - Advanced vector operations include reserve, shrink_to_fit, and emplace
 * - Deque provides efficient insertion/deletion at both ends
 * - List offers efficient insertion/deletion anywhere and splice operations
 * - Forward list is memory-efficient for single-direction traversal
 * - Set and multiset provide ordered unique and non-unique elements
 * - Map and multimap provide ordered key-value pairs
 * - Unordered containers offer average O(1) operations with hash tables
 * - Container adapters (stack, queue, priority_queue) provide specialized interfaces
 * - Specialized containers (array, bitset, valarray) serve specific purposes
 * - Container choice affects performance characteristics significantly
 */"""
