#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <array>
#include <set>
#include <multiset>
#include <map>
#include <multimap>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <priority_queue>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>

// Demonstrates STL containers and their usage
int main() {
    std::cout << "STL Containers Demonstration" << std::endl;
    std::cout << "============================" << std::endl;
    
    // 1. Sequence containers
    std::cout << "\n1. SEQUENCE CONTAINERS:" << std::endl;
    
    // Vector - dynamic array
    std::cout << "\nVector (Dynamic Array):" << std::endl;
    std::vector<int> vec = {1, 2, 3, 4, 5};
    
    std::cout << "Original vector: ";
    for (const auto& val : vec) std::cout << val << " ";
    std::cout << std::endl;
    
    vec.push_back(6);
    vec.insert(vec.begin() + 2, 10);
    vec.erase(vec.begin() + 4);
    
    std::cout << "Modified vector: ";
    for (const auto& val : vec) std::cout << val << " ";
    std::cout << std::endl;
    
    std::cout << "Vector size: " << vec.size() << ", capacity: " << vec.capacity() << std::endl;
    
    // List - doubly linked list
    std::cout << "\nList (Doubly Linked List):" << std::endl;
    std::list<int> lst = {1, 2, 3, 4, 5};
    
    std::cout << "Original list: ";
    for (const auto& val : lst) std::cout << val << " ";
    std::cout << std::endl;
    
    lst.push_front(0);
    lst.push_back(6);
    lst.insert(std::next(lst.begin(), 3), 10);
    
    std::cout << "Modified list: ";
    for (const auto& val : lst) std::cout << val << " ";
    std::cout << std::endl;
    
    // Deque - double-ended queue
    std::cout << "\nDeque (Double-Ended Queue):" << std::endl;
    std::deque<int> deq = {1, 2, 3, 4, 5};
    
    std::cout << "Original deque: ";
    for (const auto& val : deq) std::cout << val << " ";
    std::cout << std::endl;
    
    deq.push_front(0);
    deq.push_back(6);
    deq.insert(deq.begin() + 3, 10);
    
    std::cout << "Modified deque: ";
    for (const auto& val : deq) std::cout << val << " ";
    std::cout << std::endl;
    
    // Array - fixed-size array
    std::cout << "\nArray (Fixed-Size Array):" << std::endl;
    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    
    std::cout << "Array: ";
    for (const auto& val : arr) std::cout << val << " ";
    std::cout << std::endl;
    
    arr[2] = 10;
    std::cout << "Modified array: ";
    for (const auto& val : arr) std::cout << val << " ";
    std::cout << std::endl;
    
    // Forward list - singly linked list
    std::cout << "\nForward List (Singly Linked List):" << std::endl;
    std::forward_list<int> flst = {1, 2, 3, 4, 5};
    
    std::cout << "Original forward list: ";
    for (const auto& val : flst) std::cout << val << " ";
    std::cout << std::endl;
    
    flst.push_front(0);
    flst.insert_after(flst.begin(), 10);
    
    std::cout << "Modified forward list: ";
    for (const auto& val : flst) std::cout << val << " ";
    std::cout << std::endl;
    
    // 2. Associative containers
    std::cout << "\n2. ASSOCIATIVE CONTAINERS:" << std::endl;
    
    // Set - sorted unique elements
    std::cout << "\nSet (Sorted Unique Elements):" << std::endl;
    std::set<int> s = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    std::cout << "Set: ";
    for (const auto& val : s) std::cout << val << " ";
    std::cout << std::endl;
    
    s.insert(10);
    s.erase(5);
    
    std::cout << "Modified set: ";
    for (const auto& val : s) std::cout << val << " ";
    std::cout << std::endl;
    
    // Multiset - sorted elements allowing duplicates
    std::cout << "\nMultiset (Sorted Elements with Duplicates):" << std::endl;
    std::multiset<int> ms = {5, 2, 8, 1, 9, 3, 7, 4, 6, 2, 8};
    
    std::cout << "Multiset: ";
    for (const auto& val : ms) std::cout << val << " ";
    std::cout << std::endl;
    
    std::cout << "Count of 2: " << ms.count(2) << std::endl;
    std::cout << "Count of 8: " << ms.count(8) << std::endl;
    
    // Map - sorted key-value pairs
    std::cout << "\nMap (Sorted Key-Value Pairs):" << std::endl;
    std::map<std::string, int> m = {
        {"apple", 5},
        {"banana", 3},
        {"orange", 8},
        {"grape", 2}
    };
    
    std::cout << "Map: ";
    for (const auto& pair : m) {
        std::cout << pair.first << ":" << pair.second << " ";
    }
    std::cout << std::endl;
    
    m["kiwi"] = 4;
    m["apple"] = 6;
    
    std::cout << "Modified map: ";
    for (const auto& pair : m) {
        std::cout << pair.first << ":" << pair.second << " ";
    }
    std::cout << std::endl;
    
    // Multimap - sorted key-value pairs allowing duplicate keys
    std::cout << "\nMultimap (Sorted Key-Value Pairs with Duplicate Keys):" << std::endl;
    std::multimap<std::string, int> mm = {
        {"apple", 5},
        {"banana", 3},
        {"apple", 2},
        {"orange", 8},
        {"banana", 1}
    };
    
    std::cout << "Multimap: ";
    for (const auto& pair : mm) {
        std::cout << pair.first << ":" << pair.second << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Count of 'apple': " << mm.count("apple") << std::endl;
    std::cout << "Count of 'banana': " << mm.count("banana") << std::endl;
    
    // 3. Unordered containers
    std::cout << "\n3. UNORDERED CONTAINERS:" << std::endl;
    
    // Unordered set - hash table with unique elements
    std::cout << "\nUnordered Set (Hash Table with Unique Elements):" << std::endl;
    std::unordered_set<int> us = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    std::cout << "Unordered set: ";
    for (const auto& val : us) std::cout << val << " ";
    std::cout << std::endl;
    
    us.insert(10);
    us.erase(5);
    
    std::cout << "Modified unordered set: ";
    for (const auto& val : us) std::cout << val << " ";
    std::cout << std::endl;
    
    // Unordered map - hash table with key-value pairs
    std::cout << "\nUnordered Map (Hash Table with Key-Value Pairs):" << std::endl;
    std::unordered_map<std::string, int> um = {
        {"apple", 5},
        {"banana", 3},
        {"orange", 8},
        {"grape", 2}
    };
    
    std::cout << "Unordered map: ";
    for (const auto& pair : um) {
        std::cout << pair.first << ":" << pair.second << " ";
    }
    std::cout << std::endl;
    
    um["kiwi"] = 4;
    um["apple"] = 6;
    
    std::cout << "Modified unordered map: ";
    for (const auto& pair : um) {
        std::cout << pair.first << ":" << pair.second << " ";
    }
    std::cout << std::endl;
    
    // 4. Container adapters
    std::cout << "\n4. CONTAINER ADAPTERS:" << std::endl;
    
    // Stack - LIFO container
    std::cout << "\nStack (LIFO - Last In, First Out):" << std::endl;
    std::stack<int> stk;
    
    for (int i = 1; i <= 5; ++i) {
        stk.push(i);
        std::cout << "Pushed: " << i << std::endl;
    }
    
    std::cout << "Stack size: " << stk.size() << std::endl;
    
    while (!stk.empty()) {
        std::cout << "Popped: " << stk.top() << std::endl;
        stk.pop();
    }
    
    // Queue - FIFO container
    std::cout << "\nQueue (FIFO - First In, First Out):" << std::endl;
    std::queue<int> q;
    
    for (int i = 1; i <= 5; ++i) {
        q.push(i);
        std::cout << "Enqueued: " << i << std::endl;
    }
    
    std::cout << "Queue size: " << q.size() << std::endl;
    
    while (!q.empty()) {
        std::cout << "Dequeued: " << q.front() << std::endl;
        q.pop();
    }
    
    // Priority queue - heap-based priority queue
    std::cout << "\nPriority Queue (Heap-Based Priority Queue):" << std::endl;
    std::priority_queue<int> pq;
    
    std::vector<int> values = {3, 1, 4, 1, 5, 9, 2, 6};
    
    for (int val : values) {
        pq.push(val);
        std::cout << "Pushed: " << val << std::endl;
    }
    
    std::cout << "Priority queue size: " << pq.size() << std::endl;
    
    while (!pq.empty()) {
        std::cout << "Popped: " << pq.top() << std::endl;
        pq.pop();
    }
    
    // 5. Container performance comparison
    std::cout << "\n5. CONTAINER PERFORMANCE COMPARISON:" << std::endl;
    
    const size_t size = 100000;
    
    // Vector performance
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> vec_perf;
    for (size_t i = 0; i < size; ++i) {
        vec_perf.push_back(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto vec_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Vector insertion time: " << vec_time.count() << " ms" << std::endl;
    
    // List performance
    start = std::chrono::high_resolution_clock::now();
    std::list<int> list_perf;
    for (size_t i = 0; i < size; ++i) {
        list_perf.push_back(i);
    }
    end = std::chrono::high_resolution_clock::now();
    auto list_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "List insertion time: " << list_time.count() << " ms" << std::endl;
    
    // Set performance
    start = std::chrono::high_resolution_clock::now();
    std::set<int> set_perf;
    for (size_t i = 0; i < size; ++i) {
        set_perf.insert(i);
    }
    end = std::chrono::high_resolution_clock::now();
    auto set_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Set insertion time: " << set_time.count() << " ms" << std::endl;
    
    // Unordered set performance
    start = std::chrono::high_resolution_clock::now();
    std::unordered_set<int> uset_perf;
    for (size_t i = 0; i < size; ++i) {
        uset_perf.insert(i);
    }
    end = std::chrono::high_resolution_clock::now();
    auto uset_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "Unordered set insertion time: " << uset_time.count() << " ms" << std::endl;
    
    // 6. Container algorithms
    std::cout << "\n6. CONTAINER ALGORITHMS:" << std::endl;
    
    std::vector<int> algo_vec = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    std::cout << "Original vector: ";
    for (const auto& val : algo_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    // Sort
    std::sort(algo_vec.begin(), algo_vec.end());
    std::cout << "Sorted vector: ";
    for (const auto& val : algo_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    // Find
    auto it = std::find(algo_vec.begin(), algo_vec.end(), 5);
    if (it != algo_vec.end()) {
        std::cout << "Found 5 at position: " << (it - algo_vec.begin()) << std::endl;
    }
    
    // Count
    int count = std::count(algo_vec.begin(), algo_vec.end(), 5);
    std::cout << "Count of 5: " << count << std::endl;
    
    // Transform
    std::vector<int> doubled_vec(algo_vec.size());
    std::transform(algo_vec.begin(), algo_vec.end(), doubled_vec.begin(),
                   [](int x) { return x * 2; });
    
    std::cout << "Doubled vector: ";
    for (const auto& val : doubled_vec) std::cout << val << " ";
    std::cout << std::endl;
    
    // 7. Container with custom types
    std::cout << "\n7. CONTAINER WITH CUSTOM TYPES:" << std::endl;
    
    struct Person {
        std::string name;
        int age;
        
        Person(const std::string& name, int age) : name(name), age(age) {}
        
        bool operator<(const Person& other) const {
            return age < other.age;
        }
        
        friend std::ostream& operator<<(std::ostream& os, const Person& p) {
            os << p.name << " (" << p.age << ")";
            return os;
        }
    };
    
    std::set<Person> people;
    people.insert(Person("Alice", 25));
    people.insert(Person("Bob", 30));
    people.insert(Person("Charlie", 20));
    
    std::cout << "People (sorted by age): ";
    for (const auto& person : people) {
        std::cout << person << " ";
    }
    std::cout << std::endl;
    
    // 8. Container with iterators
    std::cout << "\n8. CONTAINER WITH ITERATORS:" << std::endl;
    
    std::vector<int> iter_vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    std::cout << "Vector: ";
    for (auto it = iter_vec.begin(); it != iter_vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Reverse iterator
    std::cout << "Reverse vector: ";
    for (auto it = iter_vec.rbegin(); it != iter_vec.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Const iterator
    std::cout << "Const vector: ";
    for (auto it = iter_vec.cbegin(); it != iter_vec.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // 9. Container with different allocators
    std::cout << "\n9. CONTAINER WITH DIFFERENT ALLOCATORS:" << std::endl;
    
    std::vector<int> vec_alloc;
    std::vector<int> vec_alloc2;
    
    vec_alloc.reserve(1000);
    vec_alloc2.reserve(1000);
    
    for (int i = 0; i < 1000; ++i) {
        vec_alloc.push_back(i);
        vec_alloc2.push_back(i * 2);
    }
    
    std::cout << "Vector 1 size: " << vec_alloc.size() << ", capacity: " << vec_alloc.capacity() << std::endl;
    std::cout << "Vector 2 size: " << vec_alloc2.size() << ", capacity: " << vec_alloc2.capacity() << std::endl;
    
    // 10. Container with move semantics
    std::cout << "\n10. CONTAINER WITH MOVE SEMANTICS:" << std::endl;
    
    std::vector<int> vec_move1 = {1, 2, 3, 4, 5};
    std::vector<int> vec_move2 = std::move(vec_move1);
    
    std::cout << "Vector 1 size after move: " << vec_move1.size() << std::endl;
    std::cout << "Vector 2 size after move: " << vec_move2.size() << std::endl;
    
    std::cout << "Vector 2 contents: ";
    for (const auto& val : vec_move2) std::cout << val << " ";
    std::cout << std::endl;
    
    std::cout << "\nSTL containers demonstration completed!" << std::endl;
    return 0;
}
