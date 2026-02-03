#include <iostream>
#include <optional>
#include <any>
#include <variant>
#include <tuple>
#include <utility>
#include <string>
#include <vector>

// Demonstrates C++ utilities
int main() {
    std::cout << "C++ Utilities Demonstration" << std::endl;
    std::cout << "==========================" << std::endl;
    
    // 1. std::optional
    std::cout << "\n1. STD::OPTIONAL:" << std::endl;
    
    auto safe_divide = [](double a, double b) -> std::optional<double> {
        if (b == 0.0) {
            return std::nullopt;
        }
        return a / b;
    };
    
    auto result1 = safe_divide(10.0, 2.0);
    if (result1) {
        std::cout << "  10.0 / 2.0 = " << *result1 << std::endl;
    }
    
    auto result2 = safe_divide(10.0, 0.0);
    if (result2) {
        std::cout << "This won't be printed" << std::endl;
    } else {
        std::cout << "  Division by zero - no result" << std::endl;
    }
    
    // Optional with value_or
    auto result3 = safe_divide(15.0, 3.0);
    double final_result = result3.value_or(0.0);
    std::cout << "  Result with value_or: " << final_result << std::endl;
    
    // Optional with has_value
    std::optional<std::string> maybe_string = "Hello, World!";
    if (maybe_string.has_value()) {
        std::cout << "  Optional string: " << maybe_string.value() << std::endl;
    }
    
    // 2. std::any
    std::cout << "\n2. STD::ANY:" << std::endl;
    
    std::any any_value;
    
    any_value = 42;
    std::cout << "  Any value (int): " << std::any_cast<int>(any_value) << std::endl;
    
    any_value = 3.14159;
    std::cout << "  Any value (double): " << std::any_cast<double>(any_value) << std::endl;
    
    any_value = std::string("Hello, Any!");
    std::cout << "  Any value (string): " << std::any_cast<std::string>(any_value) << std::endl;
    
    // Safe any_cast
    try {
        int wrong_cast = std::any_cast<int>(any_value);
    } catch (const std::bad_any_cast& e) {
        std::cout << "  Caught bad_any_cast: " << e.what() << std::endl;
    }
    
    // Check type
    if (any_value.type() == typeid(std::string)) {
        std::cout << "  Any value is a string" << std::endl;
    }
    
    // 3. std::variant
    std::cout << "\n3. STD::VARIANT:" << std::endl;
    
    std::variant<int, double, std::string> variant_value;
    
    variant_value = 42;
    std::cout << "  Variant value (int): " << std::get<int>(variant_value) << std::endl;
    
    variant_value = 3.14159;
    std::cout << "  Variant value (double): " << std::get<double>(variant_value) << std::endl;
    
    variant_value = std::string("Hello, Variant!");
    std::cout << "  Variant value (string): " << std::get<std::string>(variant_value) << std::endl;
    
    // Visit variant
    std::visit([](const auto& value) {
        std::cout << "  Visited variant value: " << value << std::endl;
    }, variant_value);
    
    // Check variant index
    std::cout << "  Variant index: " << variant_value.index() << std::endl;
    
    // Safe get with get_if
    if (auto* str_ptr = std::get_if<std::string>(&variant_value)) {
        std::cout << "  Variant contains string: " << *str_ptr << std::endl;
    }
    
    // 4. std::tuple
    std::cout << "\n4. STD::TUPLE:" << std::endl;
    
    std::tuple<int, double, std::string> my_tuple(42, 3.14159, "Hello, Tuple!");
    
    std::cout << "  Tuple elements:" << std::endl;
    std::cout << "    Element 0: " << std::get<0>(my_tuple) << std::endl;
    std::cout << "    Element 1: " << std::get<1>(my_tuple) << std::endl;
    std::cout << "    Element 2: " << std::get<2>(my_tuple) << std::endl;
    
    // Structured bindings with tuple
    auto [int_val, double_val, string_val] = my_tuple;
    std::cout << "  Structured binding: " << int_val << ", " << double_val << ", " << string_val << std::endl;
    
    // Make tuple
    auto auto_tuple = std::make_tuple(100, 2.71828, std::string("Auto tuple"));
    std::cout << "  Auto tuple size: " << std::tuple_size_v<decltype(auto_tuple)> << std::endl;
    
    // Tuple comparison
    auto tuple1 = std::make_tuple(1, 2.0, std::string("test"));
    auto tuple2 = std::make_tuple(1, 2.0, std::string("test"));
    auto tuple3 = std::make_tuple(2, 3.0, std::string("different"));
    
    std::cout << "  Tuple1 == Tuple2: " << (tuple1 == tuple2) << std::endl;
    std::cout << "  Tuple1 < Tuple3: " << (tuple1 < tuple3) << std::endl;
    
    // 5. std::pair
    std::cout << "\n5. STD::PAIR:" << std::endl;
    
    std::pair<int, std::string> my_pair(42, "Hello, Pair!");
    std::cout << "  Pair: (" << my_pair.first << ", " << my_pair.second << ")" << std::endl;
    
    // Make pair
    auto auto_pair = std::make_pair(100, std::string("Auto pair"));
    std::cout << "  Auto pair: (" << auto_pair.first << ", " << auto_pair.second << ")" << std::endl;
    
    // Structured bindings with pair
    auto [key, value] = auto_pair;
    std::cout << "  Structured binding: " << key << " -> " << value << std::endl;
    
    // Pair comparison
    auto pair1 = std::make_pair(1, std::string("a"));
    auto pair2 = std::make_pair(1, std::string("a"));
    auto pair3 = std::make_pair(2, std::string("b"));
    
    std::cout << "  Pair1 == Pair2: " << (pair1 == pair2) << std::endl;
    std::cout << "  Pair1 < Pair3: " << (pair1 < pair3) << std::endl;
    
    // 6. std::move and std::forward
    std::cout << "\n6. STD::MOVE AND STD::FORWARD:" << std::endl;
    
    std::string original = "Original string";
    std::cout << "  Original: " << original << std::endl;
    
    std::string moved = std::move(original);
    std::cout << "  After move - Original: '" << original << "'" << std::endl;
    std::cout << "  After move - Moved: " << moved << std::endl;
    
    // Perfect forwarding example
    auto perfect_forward = [](auto&& arg) -> decltype(auto) {
        return std::forward<decltype(arg)>(arg);
    };
    
    std::string test_string = "Test string";
    auto forwarded = perfect_forward(test_string);
    std::cout << "  Perfect forwarding: " << forwarded << std::endl;
    
    // 7. std::swap
    std::cout << "\n7. STD::SWAP:" << std::endl;
    
    int a = 10, b = 20;
    std::cout << "  Before swap: a=" << a << ", b=" << b << std::endl;
    
    std::swap(a, b);
    std::cout << "  After swap: a=" << a << ", b=" << b << std::endl;
    
    std::string str1 = "First";
    std::string str2 = "Second";
    std::cout << "  Before swap: str1=" << str1 << ", str2=" << str2 << std::endl;
    
    std::swap(str1, str2);
    std::cout << "  After swap: str1=" << str1 << ", str2=" << str2 << std::endl;
    
    // 8. std::exchange
    std::cout << "\n8. STD::EXCHANGE:" << std::endl;
    
    int x = 10;
    int old_x = std::exchange(x, 20);
    std::cout << "  Exchange: old_x=" << old_x << ", new_x=" << x << std::endl;
    
    std::string text = "Old text";
    std::string old_text = std::exchange(text, "New text");
    std::cout << "  Exchange: old_text=" << old_text << ", new_text=" << text << std::endl;
    
    // 9. std::clamp
    std::cout << "\n9. STD::CLAMP:" << std::endl;
    
    int value = 15;
    int clamped = std::clamp(value, 10, 20);
    std::cout << "  Clamp(15, 10, 20) = " << clamped << std::endl;
    
    double float_value = 3.14159;
    double clamped_float = std::clamp(float_value, 0.0, 3.0);
    std::cout << "  Clamp(3.14159, 0.0, 3.0) = " << clamped_float << std::endl;
    
    // 10. std::min, std::max, std::minmax
    std::cout << "\n10. STD::MIN, STD::MAX, STD::MINMAX:" << std::endl;
    
    int num1 = 10, num2 = 20;
    std::cout << "  Min(10, 20) = " << std::min(num1, num2) << std::endl;
    std::cout << "  Max(10, 20) = " << std::max(num1, num2) << std::endl;
    
    auto minmax_result = std::minmax(num1, num2);
    std::cout << "  Minmax(10, 20) = (" << minmax_result.first << ", " << minmax_result.second << ")" << std::endl;
    
    // Min/max with initializer list
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3};
    int min_val = std::min({numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5]});
    int max_val = std::max({numbers[0], numbers[1], numbers[2], numbers[3], numbers[4], numbers[5]});
    
    std::cout << "  Min from vector: " << min_val << std::endl;
    std::cout << "  Max from vector: " << max_val << std::endl;
    
    // 11. std::gcd and std::lcm
    std::cout << "\n11. STD::GCD AND STD::LCM:" << std::endl;
    
    int num_a = 48, num_b = 18;
    std::cout << "  GCD(48, 18) = " << std::gcd(num_a, num_b) << std::endl;
    std::cout << "  LCM(48, 18) = " << std::lcm(num_a, num_b) << std::endl;
    
    // 12. std::midpoint
    std::cout << "\n12. STD::MIDPOINT:" << std::endl;
    
    int start = 10, end = 20;
    int midpoint = std::midpoint(start, end);
    std::cout << "  Midpoint(10, 20) = " << midpoint << std::endl;
    
    double start_d = 1.5, end_d = 3.5;
    double midpoint_d = std::midpoint(start_d, end_d);
    std::cout << "  Midpoint(1.5, 3.5) = " << midpoint_d << std::endl;
    
    // 13. std::lerp
    std::cout << "\n13. STD::LERP:" << std::endl;
    
    double a_val = 1.0, b_val = 5.0;
    double t = 0.5;
    double lerp_result = std::lerp(a_val, b_val, t);
    std::cout << "  Lerp(1.0, 5.0, 0.5) = " << lerp_result << std::endl;
    
    // 14. Utility functions with containers
    std::cout << "\n14. UTILITY FUNCTIONS WITH CONTAINERS:" << std::endl;
    
    std::vector<int> vec = {1, 2, 3, 4, 5};
    
    // Find min/max in container
    auto min_it = std::min_element(vec.begin(), vec.end());
    auto max_it = std::max_element(vec.begin(), vec.end());
    
    std::cout << "  Min element: " << *min_it << " at position " << (min_it - vec.begin()) << std::endl;
    std::cout << "  Max element: " << *max_it << " at position " << (max_it - vec.begin()) << std::endl;
    
    // Minmax element
    auto minmax_it = std::minmax_element(vec.begin(), vec.end());
    std::cout << "  Minmax elements: " << *minmax_it.first << " and " << *minmax_it.second << std::endl;
    
    // 15. Advanced tuple operations
    std::cout << "\n15. ADVANCED TUPLE OPERATIONS:" << std::endl;
    
    auto tuple_a = std::make_tuple(1, 2.0, std::string("a"));
    auto tuple_b = std::make_tuple(2, 3.0, std::string("b"));
    
    // Tuple concatenation simulation
    auto concatenate_tuples = [](const auto& t1, const auto& t2) {
        return std::make_tuple(
            std::get<0>(t1), std::get<1>(t1), std::get<2>(t1),
            std::get<0>(t2), std::get<1>(t2), std::get<2>(t2)
        );
    };
    
    auto combined = concatenate_tuples(tuple_a, tuple_b);
    std::cout << "  Combined tuple size: " << std::tuple_size_v<decltype(combined)> << std::endl;
    
    // Tuple apply
    auto print_tuple = [](const auto&... args) {
        ((std::cout << "  " << args << " "), ...);
        std::cout << std::endl;
    };
    
    std::apply(print_tuple, tuple_a);
    
    std::cout << "\nC++ utilities demonstration completed!" << std::endl;
    return 0;
}
