#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <iterator>
#include <functional>
#include <memory>

// Demonstrates STL overview and basic concepts
int main() {
    std::cout << "STL Overview Demonstration" << std::endl;
    std::cout << "=========================" << std::endl;
    
    // 1. STL Components Overview
    std::cout << "\n1. STL COMPONENTS OVERVIEW:" << std::endl;
    
    std::cout << "  STL consists of three main components:" << std::endl;
    std::cout << "    - Containers: Store data" << std::endl;
    std::cout << "    - Algorithms: Process data" << std::endl;
    std::cout << "    - Iterators: Access data" << std::endl;
    
    // 2. Container Types
    std::cout << "\n2. CONTAINER TYPES:" << std::endl;
    
    // Sequence containers
    std::cout << "  Sequence Containers:" << std::endl;
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::list<int> lst = {6, 7, 8, 9, 10};
    
    std::cout << "    vector: ";
    for (const auto& item : vec) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    
    std::cout << "    list: ";
    for (const auto& item : lst) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    
    // Associative containers
    std::cout << "  Associative Containers:" << std::endl;
    std::map<std::string, int> scores;
    scores["Alice"] = 95;
    scores["Bob"] = 87;
    scores["Charlie"] = 92;
    
    std::cout << "    map: ";
    for (const auto& pair : scores) {
        std::cout << pair.first << ":" << pair.second << " ";
    }
    std::cout << std::endl;
    
    std::set<int> unique_numbers = {1, 2, 2, 3, 3, 4, 5};
    std::cout << "    set: ";
    for (const auto& num : unique_numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // 3. Iterator Categories
    std::cout << "\n3. ITERATOR CATEGORIES:" << std::endl;
    
    // Input iterator
    std::cout << "  Input Iterator (read-only, forward):" << std::endl;
    std::istream_iterator<int> input_iter(std::cin);
    
    // Output iterator
    std::cout << "  Output Iterator (write-only, forward):" << std::endl;
    std::ostream_iterator<int> output_iter(std::cout, " ");
    
    // Forward iterator
    std::cout << "  Forward Iterator (read/write, forward):" << std::endl;
    std::vector<int>::iterator forward_iter = vec.begin();
    std::cout << "    First element: " << *forward_iter << std::endl;
    
    // Bidirectional iterator
    std::cout << "  Bidirectional Iterator (read/write, forward/backward):" << std::endl;
    std::list<int>::iterator bi_iter = lst.begin();
    ++bi_iter;
    --bi_iter;
    std::cout << "    Element: " << *bi_iter << std::endl;
    
    // Random access iterator
    std::cout << "  Random Access Iterator (read/write, random access):" << std::endl;
    std::vector<int>::iterator random_iter = vec.begin();
    random_iter += 2;
    std::cout << "    Element at position 2: " << *random_iter << std::endl;
    
    // 4. Algorithm Categories
    std::cout << "\n4. ALGORITHM CATEGORIES:" << std::endl;
    
    // Non-modifying algorithms
    std::cout << "  Non-modifying Algorithms:" << std::endl;
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Find
    auto it = std::find(numbers.begin(), numbers.end(), 5);
    if (it != numbers.end()) {
        std::cout << "    Found 5 at position: " << std::distance(numbers.begin(), it) << std::endl;
    }
    
    // Count
    int count = std::count(numbers.begin(), numbers.end(), 5);
    std::cout << "    Count of 5: " << count << std::endl;
    
    // Modifying algorithms
    std::cout << "  Modifying Algorithms:" << std::endl;
    std::vector<int> modifiable = {5, 2, 8, 1, 9, 3};
    
    // Sort
    std::sort(modifiable.begin(), modifiable.end());
    std::cout << "    Sorted: ";
    for (const auto& num : modifiable) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Transform
    std::transform(modifiable.begin(), modifiable.end(), modifiable.begin(),
                   [](int x) { return x * 2; });
    std::cout << "    Doubled: ";
    for (const auto& num : modifiable) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // 5. Function Objects
    std::cout << "\n5. FUNCTION OBJECTS:" << std::endl;
    
    // Built-in function objects
    std::vector<int> func_numbers = {1, 2, 3, 4, 5};
    
    // Plus
    std::cout << "  Plus function object: ";
    std::transform(func_numbers.begin(), func_numbers.end(), func_numbers.begin(),
                   std::bind(std::plus<int>(), std::placeholders::_1, 10));
    for (const auto& num : func_numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Custom function object
    class Square {
    public:
        int operator()(int x) const {
            return x * x;
        }
    };
    
    std::vector<int> square_numbers = {1, 2, 3, 4, 5};
    std::transform(square_numbers.begin(), square_numbers.end(), square_numbers.begin(), Square());
    
    std::cout << "  Custom function object (square): ";
    for (const auto& num : square_numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // 6. Lambda Functions
    std::cout << "\n6. LAMBDA FUNCTIONS:" << std::endl;
    
    std::vector<int> lambda_numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Lambda with capture
    int multiplier = 3;
    std::transform(lambda_numbers.begin(), lambda_numbers.end(), lambda_numbers.begin(),
                   [multiplier](int x) { return x * multiplier; });
    
    std::cout << "  Lambda (multiply by 3): ";
    for (const auto& num : lambda_numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Lambda with conditional
    std::vector<int> even_numbers;
    std::copy_if(lambda_numbers.begin(), lambda_numbers.end(), std::back_inserter(even_numbers),
                 [](int x) { return x % 2 == 0; });
    
    std::cout << "  Lambda (even numbers): ";
    for (const auto& num : even_numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // 7. Iterator Adapters
    std::cout << "\n7. ITERATOR ADAPTERS:" << std::endl;
    
    // Insert iterators
    std::vector<int> source = {1, 2, 3, 4, 5};
    std::vector<int> destination;
    
    std::copy(source.begin(), source.end(), std::back_inserter(destination));
    std::cout << "  Back inserter: ";
    for (const auto& num : destination) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Stream iterators
    std::cout << "  Stream iterator output: ";
    std::copy(source.begin(), source.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    
    // Reverse iterator
    std::cout << "  Reverse iterator: ";
    for (auto it = source.rbegin(); it != source.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // 8. Memory Management
    std::cout << "\n8. MEMORY MANAGEMENT:" << std::endl;
    
    // Smart pointers
    std::unique_ptr<int> unique_ptr = std::make_unique<int>(42);
    std::cout << "  Unique pointer: " << *unique_ptr << std::endl;
    
    std::shared_ptr<int> shared_ptr = std::make_shared<int>(100);
    std::shared_ptr<int> shared_copy = shared_ptr;
    std::cout << "  Shared pointer: " << *shared_ptr << " (use_count: " << shared_ptr.use_count() << ")" << std::endl;
    
    // Allocators
    std::vector<int, std::allocator<int>> allocator_vector;
    allocator_vector.push_back(1);
    allocator_vector.push_back(2);
    std::cout << "  Allocator vector: ";
    for (const auto& num : allocator_vector) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // 9. Exception Safety
    std::cout << "\n9. EXCEPTION SAFETY:" << std::endl;
    
    // Strong exception safety
    std::vector<int> safe_vector;
    try {
        safe_vector.push_back(1);
        safe_vector.push_back(2);
        safe_vector.push_back(3);
        
        // Simulate an exception
        throw std::runtime_error("Simulated exception");
        
    } catch (const std::exception& e) {
        std::cout << "  Exception caught: " << e.what() << std::endl;
        std::cout << "  Vector state preserved: ";
        for (const auto& num : safe_vector) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
    
    // 10. Performance Considerations
    std::cout << "\n10. PERFORMANCE CONSIDERATIONS:" << std::endl;
    
    // Container selection
    std::cout << "  Container Selection Guidelines:" << std::endl;
    std::cout << "    - vector: Fast random access, slow insertion/deletion in middle" << std::endl;
    std::cout << "    - list: Fast insertion/deletion, slow random access" << std::endl;
    std::cout << "    - map: Sorted, logarithmic operations" << std::endl;
    std::cout << "    - unordered_map: Hash table, constant average operations" << std::endl;
    
    // Algorithm complexity
    std::cout << "  Algorithm Complexity:" << std::endl;
    std::cout << "    - sort: O(n log n)" << std::endl;
    std::cout << "    - find: O(n)" << std::endl;
    std::cout << "    - binary_search: O(log n)" << std::endl;
    
    // 11. Best Practices
    std::cout << "\n11. BEST PRACTICES:" << std::endl;
    
    // Use appropriate containers
    std::cout << "  Use appropriate containers for your use case" << std::endl;
    
    // Prefer algorithms over loops
    std::vector<int> best_practice = {1, 2, 3, 4, 5};
    
    // Instead of manual loop
    int sum_manual = 0;
    for (const auto& num : best_practice) {
        sum_manual += num;
    }
    
    // Use algorithm
    int sum_algorithm = std::accumulate(best_practice.begin(), best_practice.end(), 0);
    
    std::cout << "  Manual sum: " << sum_manual << std::endl;
    std::cout << "  Algorithm sum: " << sum_algorithm << std::endl;
    
    // Use const correctness
    const std::vector<int> const_vector = {1, 2, 3, 4, 5};
    auto const_it = std::find(const_vector.begin(), const_vector.end(), 3);
    if (const_it != const_vector.end()) {
        std::cout << "  Found in const vector: " << *const_it << std::endl;
    }
    
    // 12. Common Headers
    std::cout << "\n12. COMMON HEADERS:" << std::endl;
    
    std::cout << "  Container headers:" << std::endl;
    std::cout << "    - <vector>, <list>, <deque>" << std::endl;
    std::cout << "    - <set>, <map>, <multiset>, <multimap>" << std::endl;
    std::cout << "    - <unordered_set>, <unordered_map>" << std::endl;
    
    std::cout << "  Algorithm headers:" << std::endl;
    std::cout << "    - <algorithm> (most algorithms)" << std::endl;
    std::cout << "    - <numeric> (mathematical algorithms)" << std::endl;
    
    std::cout << "  Iterator headers:" << std::endl;
    std::cout << "    - <iterator> (iterator adapters)" << std::endl;
    
    std::cout << "  Utility headers:" << std::endl;
    std::cout << "    - <functional> (function objects)" << std::endl;
    std::cout << "    - <memory> (smart pointers, allocators)" << std::endl;
    
    // 13. STL Design Principles
    std::cout << "\n13. STL DESIGN PRINCIPLES:" << std::endl;
    
    std::cout << "  Generic Programming:" << std::endl;
    std::cout << "    - Templates for type safety" << std::endl;
    std::cout << "    - Iterator abstraction" << std::endl;
    std::cout << "    - Algorithm/container separation" << std::endl;
    
    std::cout << "  Efficiency:" << std::endl;
    std::cout << "    - Zero-cost abstractions" << std::endl;
    std::cout << "    - Inline functions" << std::endl;
    std::cout << "    - Compile-time optimizations" << std::endl;
    
    std::cout << "  Extensibility:" << std::endl;
    std::cout << "    - Custom allocators" << std::endl;
    std::cout << "    - Custom function objects" << std::endl;
    std::cout << "    - Custom iterators" << std::endl;
    
    // 14. Example: Complete STL Usage
    std::cout << "\n14. EXAMPLE: COMPLETE STL USAGE:" << std::endl;
    
    // Read data
    std::vector<std::string> words = {"apple", "banana", "cherry", "date", "elderberry"};
    
    // Transform data
    std::vector<std::string> upper_words;
    std::transform(words.begin(), words.end(), std::back_inserter(upper_words),
                   [](const std::string& word) {
                       std::string upper = word;
                       std::transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
                       return upper;
                   });
    
    // Filter data
    std::vector<std::string> long_words;
    std::copy_if(upper_words.begin(), upper_words.end(), std::back_inserter(long_words),
                 [](const std::string& word) { return word.length() > 5; });
    
    // Sort data
    std::sort(long_words.begin(), long_words.end());
    
    // Display results
    std::cout << "  Original words: ";
    std::copy(words.begin(), words.end(), std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl;
    
    std::cout << "  Long upper words: ";
    std::copy(long_words.begin(), long_words.end(), std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl;
    
    std::cout << "\nSTL overview demonstration completed!" << std::endl;
    return 0;
}
