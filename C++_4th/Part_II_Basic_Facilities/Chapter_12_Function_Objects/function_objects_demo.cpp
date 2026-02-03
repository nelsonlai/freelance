#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <map>
#include <set>

// Demonstrates C++ function objects, lambdas, and advanced features
int main() {
    std::cout << "C++ Function Objects Demonstration" << std::endl;
    std::cout << "==================================" << std::endl;
    
    // 1. Basic function objects (functors)
    std::cout << "\n1. BASIC FUNCTION OBJECTS (FUNCTORS):" << std::endl;
    
    class MultiplyBy {
    private:
        int factor;
        
    public:
        MultiplyBy(int f) : factor(f) {}
        
        int operator()(int x) const {
            return x * factor;
        }
    };
    
    class IsEven {
    public:
        bool operator()(int x) const {
            return x % 2 == 0;
        }
    };
    
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Use function object
    MultiplyBy multiply_by_3(3);
    std::vector<int> multiplied;
    std::transform(numbers.begin(), numbers.end(), std::back_inserter(multiplied), multiply_by_3);
    
    std::cout << "Original: ";
    for (int num : numbers) std::cout << num << " ";
    std::cout << std::endl;
    
    std::cout << "Multiplied by 3: ";
    for (int num : multiplied) std::cout << num << " ";
    std::cout << std::endl;
    
    // Use predicate function object
    IsEven is_even;
    std::vector<int> evens;
    std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(evens), is_even);
    
    std::cout << "Even numbers: ";
    for (int num : evens) std::cout << num << " ";
    std::cout << std::endl;
    
    // 2. Stateful function objects
    std::cout << "\n2. STATEFUL FUNCTION OBJECTS:" << std::endl;
    
    class Counter {
    private:
        mutable int count;
        
    public:
        Counter() : count(0) {}
        
        int operator()(int x) const {
            ++count;
            return x + count;
        }
        
        int get_count() const { return count; }
    };
    
    Counter counter;
    std::vector<int> counted;
    std::transform(numbers.begin(), numbers.end(), std::back_inserter(counted), counter);
    
    std::cout << "Numbers with counter: ";
    for (int num : counted) std::cout << num << " ";
    std::cout << std::endl;
    std::cout << "Counter was called " << counter.get_count() << " times" << std::endl;
    
    // 3. Lambda expressions - basic syntax
    std::cout << "\n3. LAMBDA EXPRESSIONS - BASIC SYNTAX:" << std::endl;
    
    // Simple lambda
    auto square = [](int x) { return x * x; };
    std::cout << "square(5) = " << square(5) << std::endl;
    
    // Lambda with explicit return type
    auto add = [](int a, int b) -> int { return a + b; };
    std::cout << "add(3, 4) = " << add(3, 4) << std::endl;
    
    // Lambda with multiple statements
    auto complex_lambda = [](int x) -> int {
        if (x < 0) return -x;
        if (x > 10) return x * 2;
        return x;
    };
    std::cout << "complex_lambda(-5) = " << complex_lambda(-5) << std::endl;
    std::cout << "complex_lambda(15) = " << complex_lambda(15) << std::endl;
    std::cout << "complex_lambda(7) = " << complex_lambda(7) << std::endl;
    
    // 4. Lambda expressions - capture clauses
    std::cout << "\n4. LAMBDA EXPRESSIONS - CAPTURE CLAUSES:" << std::endl;
    
    int multiplier = 5;
    int offset = 10;
    
    // Capture by value
    auto capture_by_value = [multiplier](int x) { return x * multiplier; };
    std::cout << "capture_by_value(3) = " << capture_by_value(3) << std::endl;
    
    // Capture by reference
    int sum = 0;
    auto capture_by_reference = [&sum](int x) { sum += x; };
    for (int num : numbers) {
        capture_by_reference(num);
    }
    std::cout << "Sum of numbers (captured by reference): " << sum << std::endl;
    
    // Capture all by value
    auto capture_all_by_value = [=](int x) { return x * multiplier + offset; };
    std::cout << "capture_all_by_value(2) = " << capture_all_by_value(2) << std::endl;
    
    // Capture all by reference
    int count = 0;
    auto capture_all_by_reference = [&](int x) { 
        count++;
        return x * multiplier + offset; 
    };
    std::cout << "capture_all_by_reference(4) = " << capture_all_by_reference(4) << std::endl;
    std::cout << "Count: " << count << std::endl;
    
    // 5. Generic lambdas (C++14)
    std::cout << "\n5. GENERIC LAMBDAS (C++14):" << std::endl;
    
    auto generic_add = [](auto a, auto b) { return a + b; };
    std::cout << "generic_add(5, 3) = " << generic_add(5, 3) << std::endl;
    std::cout << "generic_add(3.14, 2.86) = " << generic_add(3.14, 2.86) << std::endl;
    std::cout << "generic_add(std::string(\"Hello\"), std::string(\" World\")) = " 
              << generic_add(std::string("Hello"), std::string(" World")) << std::endl;
    
    auto generic_max = [](auto a, auto b) { return (a > b) ? a : b; };
    std::cout << "generic_max(10, 20) = " << generic_max(10, 20) << std::endl;
    std::cout << "generic_max(3.14, 2.71) = " << generic_max(3.14, 2.71) << std::endl;
    
    // 6. Lambda with STL algorithms
    std::cout << "\n6. LAMBDA WITH STL ALGORITHMS:" << std::endl;
    
    std::vector<int> test_numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Find first even number
    auto first_even = std::find_if(test_numbers.begin(), test_numbers.end(), 
                                   [](int x) { return x % 2 == 0; });
    if (first_even != test_numbers.end()) {
        std::cout << "First even number: " << *first_even << std::endl;
    }
    
    // Count odd numbers
    int odd_count = std::count_if(test_numbers.begin(), test_numbers.end(),
                                  [](int x) { return x % 2 == 1; });
    std::cout << "Number of odd numbers: " << odd_count << std::endl;
    
    // Transform with lambda
    std::vector<int> doubled;
    std::transform(test_numbers.begin(), test_numbers.end(), std::back_inserter(doubled),
                   [](int x) { return x * 2; });
    
    std::cout << "Doubled numbers: ";
    for (int num : doubled) std::cout << num << " ";
    std::cout << std::endl;
    
    // 7. Function adapters - std::bind
    std::cout << "\n7. FUNCTION ADAPTERS - STD::BIND:" << std::endl;
    
    auto multiply = [](int a, int b, int c) { return a * b * c; };
    
    // Bind first argument
    auto multiply_by_2 = std::bind(multiply, 2, std::placeholders::_1, std::placeholders::_2);
    std::cout << "multiply_by_2(3, 4) = " << multiply_by_2(3, 4) << std::endl;
    
    // Bind first and second arguments
    auto multiply_by_2_and_3 = std::bind(multiply, 2, 3, std::placeholders::_1);
    std::cout << "multiply_by_2_and_3(4) = " << multiply_by_2_and_3(4) << std::endl;
    
    // Bind all arguments
    auto multiply_all = std::bind(multiply, 2, 3, 4);
    std::cout << "multiply_all() = " << multiply_all() << std::endl;
    
    // 8. Function adapters - std::function
    std::cout << "\n8. FUNCTION ADAPTERS - STD::FUNCTION:" << std::endl;
    
    std::function<int(int, int)> func;
    
    // Assign lambda to function
    func = [](int a, int b) { return a + b; };
    std::cout << "func(5, 3) = " << func(5, 3) << std::endl;
    
    // Assign function object to function
    func = MultiplyBy(2);
    std::cout << "func(5, 3) = " << func(5, 3) << std::endl;
    
    // Function in container
    std::vector<std::function<int(int, int)>> functions = {
        [](int a, int b) { return a + b; },
        [](int a, int b) { return a - b; },
        [](int a, int b) { return a * b; },
        [](int a, int b) { return (b != 0) ? a / b : 0; }
    };
    
    const char* operation_names[] = {"Add", "Subtract", "Multiply", "Divide"};
    int a = 10, b = 3;
    
    for (size_t i = 0; i < functions.size(); ++i) {
        std::cout << operation_names[i] << "(" << a << ", " << b << ") = " 
                  << functions[i](a, b) << std::endl;
    }
    
    // 9. STL function objects
    std::cout << "\n9. STL FUNCTION OBJECTS:" << std::endl;
    
    std::vector<int> stl_numbers = {1, 2, 3, 4, 5};
    
    // Arithmetic function objects
    std::cout << "Original: ";
    for (int num : stl_numbers) std::cout << num << " ";
    std::cout << std::endl;
    
    // Add 5 to each element
    std::transform(stl_numbers.begin(), stl_numbers.end(), stl_numbers.begin(),
                   std::bind(std::plus<int>(), std::placeholders::_1, 5));
    std::cout << "After adding 5: ";
    for (int num : stl_numbers) std::cout << num << " ";
    std::cout << std::endl;
    
    // Multiply by 2
    std::transform(stl_numbers.begin(), stl_numbers.end(), stl_numbers.begin(),
                   std::bind(std::multiplies<int>(), std::placeholders::_1, 2));
    std::cout << "After multiplying by 2: ";
    for (int num : stl_numbers) std::cout << num << " ";
    std::cout << std::endl;
    
    // 10. Comparison function objects
    std::cout << "\n10. COMPARISON FUNCTION OBJECTS:" << std::endl;
    
    std::vector<int> compare_numbers = {5, 2, 8, 1, 9, 3};
    
    std::cout << "Original: ";
    for (int num : compare_numbers) std::cout << num << " ";
    std::cout << std::endl;
    
    // Sort in ascending order
    std::sort(compare_numbers.begin(), compare_numbers.end(), std::less<int>());
    std::cout << "Sorted ascending: ";
    for (int num : compare_numbers) std::cout << num << " ";
    std::cout << std::endl;
    
    // Sort in descending order
    std::sort(compare_numbers.begin(), compare_numbers.end(), std::greater<int>());
    std::cout << "Sorted descending: ";
    for (int num : compare_numbers) std::cout << num << " ";
    std::cout << std::endl;
    
    // 11. Logical function objects
    std::cout << "\n11. LOGICAL FUNCTION OBJECTS:" << std::endl;
    
    std::vector<bool> bools1 = {true, false, true, false};
    std::vector<bool> bools2 = {true, true, false, false};
    std::vector<bool> result(bools1.size());
    
    // Logical AND
    std::transform(bools1.begin(), bools1.end(), bools2.begin(), result.begin(),
                   std::logical_and<bool>());
    std::cout << "Logical AND: ";
    for (bool b : result) std::cout << std::boolalpha << b << " ";
    std::cout << std::endl;
    
    // Logical OR
    std::transform(bools1.begin(), bools1.end(), bools2.begin(), result.begin(),
                   std::logical_or<bool>());
    std::cout << "Logical OR: ";
    for (bool b : result) std::cout << std::boolalpha << b << " ";
    std::cout << std::endl;
    
    // 12. Custom predicates
    std::cout << "\n12. CUSTOM PREDICATES:" << std::endl;
    
    class IsDivisibleBy {
    private:
        int divisor;
        
    public:
        IsDivisibleBy(int d) : divisor(d) {}
        
        bool operator()(int x) const {
            return x % divisor == 0;
        }
    };
    
    std::vector<int> predicate_numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Find numbers divisible by 3
    IsDivisibleBy divisible_by_3(3);
    std::vector<int> divisible_by_3_numbers;
    std::copy_if(predicate_numbers.begin(), predicate_numbers.end(),
                 std::back_inserter(divisible_by_3_numbers), divisible_by_3);
    
    std::cout << "Numbers divisible by 3: ";
    for (int num : divisible_by_3_numbers) std::cout << num << " ";
    std::cout << std::endl;
    
    // 13. Lambda with complex capture
    std::cout << "\n13. LAMBDA WITH COMPLEX CAPTURE:" << std::endl;
    
    std::map<std::string, int> word_counts = {
        {"hello", 5},
        {"world", 3},
        {"cpp", 10},
        {"lambda", 2}
    };
    
    int min_count = 3;
    auto filter_by_count = [&word_counts, min_count](const std::pair<std::string, int>& p) {
        return p.second >= min_count;
    };
    
    std::cout << "Words with count >= " << min_count << ": ";
    for (const auto& pair : word_counts) {
        if (filter_by_count(pair)) {
            std::cout << pair.first << "(" << pair.second << ") ";
        }
    }
    std::cout << std::endl;
    
    // 14. Lambda with mutable keyword
    std::cout << "\n14. LAMBDA WITH MUTABLE KEYWORD:" << std::endl;
    
    auto mutable_counter = [count = 0](int x) mutable -> int {
        count += x;
        return count;
    };
    
    std::cout << "mutable_counter(5) = " << mutable_counter(5) << std::endl;
    std::cout << "mutable_counter(3) = " << mutable_counter(3) << std::endl;
    std::cout << "mutable_counter(2) = " << mutable_counter(2) << std::endl;
    
    // 15. Function composition with lambdas
    std::cout << "\n15. FUNCTION COMPOSITION WITH LAMBDAS:" << std::endl;
    
    auto compose = [](auto f, auto g) {
        return [f, g](auto x) { return f(g(x)); };
    };
    
    auto add_one = [](int x) { return x + 1; };
    auto multiply_by_two = [](int x) { return x * 2; };
    auto square = [](int x) { return x * x; };
    
    auto composed1 = compose(add_one, multiply_by_two);
    auto composed2 = compose(square, add_one);
    auto composed3 = compose(composed1, composed2);
    
    std::cout << "composed1(5) = add_one(multiply_by_two(5)) = " << composed1(5) << std::endl;
    std::cout << "composed2(3) = square(add_one(3)) = " << composed2(3) << std::endl;
    std::cout << "composed3(2) = " << composed3(2) << std::endl;
    
    // 16. Lambda with std::for_each
    std::cout << "\n16. LAMBDA WITH STD::FOR_EACH:" << std::endl;
    
    std::vector<int> for_each_numbers = {1, 2, 3, 4, 5};
    int sum_for_each = 0;
    
    std::for_each(for_each_numbers.begin(), for_each_numbers.end(),
                  [&sum_for_each](int x) {
                      sum_for_each += x;
                      std::cout << "Added " << x << ", sum is now " << sum_for_each << std::endl;
                  });
    
    std::cout << "Final sum: " << sum_for_each << std::endl;
    
    // 17. Lambda with std::accumulate
    std::cout << "\n17. LAMBDA WITH STD::ACCUMULATE:" << std::endl;
    
    std::vector<int> accumulate_numbers = {1, 2, 3, 4, 5};
    
    int product = std::accumulate(accumulate_numbers.begin(), accumulate_numbers.end(), 1,
                                  [](int a, int b) { return a * b; });
    std::cout << "Product of numbers: " << product << std::endl;
    
    int sum_of_squares = std::accumulate(accumulate_numbers.begin(), accumulate_numbers.end(), 0,
                                         [](int a, int b) { return a + b * b; });
    std::cout << "Sum of squares: " << sum_of_squares << std::endl;
    
    // 18. Lambda with std::all_of, std::any_of, std::none_of
    std::cout << "\n18. LAMBDA WITH STD::ALL_OF, STD::ANY_OF, STD::NONE_OF:" << std::endl;
    
    std::vector<int> predicate_test = {2, 4, 6, 8, 10};
    
    bool all_even = std::all_of(predicate_test.begin(), predicate_test.end(),
                                [](int x) { return x % 2 == 0; });
    std::cout << "All numbers are even: " << std::boolalpha << all_even << std::endl;
    
    bool any_odd = std::any_of(predicate_test.begin(), predicate_test.end(),
                               [](int x) { return x % 2 == 1; });
    std::cout << "Any number is odd: " << std::boolalpha << any_odd << std::endl;
    
    bool none_negative = std::none_of(predicate_test.begin(), predicate_test.end(),
                                      [](int x) { return x < 0; });
    std::cout << "No number is negative: " << std::boolalpha << none_negative << std::endl;
    
    // 19. Lambda with std::remove_if
    std::cout << "\n19. LAMBDA WITH STD::REMOVE_IF:" << std::endl;
    
    std::vector<int> remove_test = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    std::cout << "Original: ";
    for (int num : remove_test) std::cout << num << " ";
    std::cout << std::endl;
    
    auto new_end = std::remove_if(remove_test.begin(), remove_test.end(),
                                  [](int x) { return x % 2 == 0; });
    remove_test.erase(new_end, remove_test.end());
    
    std::cout << "After removing even numbers: ";
    for (int num : remove_test) std::cout << num << " ";
    std::cout << std::endl;
    
    // 20. Lambda with std::partition
    std::cout << "\n20. LAMBDA WITH STD::PARTITION:" << std::endl;
    
    std::vector<int> partition_test = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    std::cout << "Original: ";
    for (int num : partition_test) std::cout << num << " ";
    std::cout << std::endl;
    
    auto partition_point = std::partition(partition_test.begin(), partition_test.end(),
                                          [](int x) { return x % 2 == 0; });
    
    std::cout << "After partitioning (evens first): ";
    for (int num : partition_test) std::cout << num << " ";
    std::cout << std::endl;
    
    std::cout << "\nFunction objects demonstration completed!" << std::endl;
    return 0;
}
