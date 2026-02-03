#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

// Demonstrates strings and string views
int main() {
    std::cout << "Strings and String Views Demonstration" << std::endl;
    std::cout << "=======================================" << std::endl;
    
    // 1. Basic String Operations
    std::cout << "\n1. BASIC STRING OPERATIONS:" << std::endl;
    
    std::string str1 = "Hello";
    std::string str2 = "World";
    std::string str3 = str1 + ", " + str2 + "!";
    
    std::cout << "  str1: " << str1 << std::endl;
    std::cout << "  str2: " << str2 << std::endl;
    std::cout << "  str3: " << str3 << std::endl;
    
    // String length and capacity
    std::cout << "  str3 length: " << str3.length() << std::endl;
    std::cout << "  str3 size: " << str3.size() << std::endl;
    std::cout << "  str3 capacity: " << str3.capacity() << std::endl;
    
    // String access
    std::cout << "  First character: " << str3[0] << std::endl;
    std::cout << "  Last character: " << str3.back() << std::endl;
    std::cout << "  Character at index 7: " << str3.at(7) << std::endl;
    
    // 2. String Modification
    std::cout << "\n2. STRING MODIFICATION:" << std::endl;
    
    std::string modifiable = "Hello";
    std::cout << "  Original: " << modifiable << std::endl;
    
    modifiable += " World";
    std::cout << "  After +=: " << modifiable << std::endl;
    
    modifiable.append("!");
    std::cout << "  After append: " << modifiable << std::endl;
    
    modifiable.insert(5, ", ");
    std::cout << "  After insert: " << modifiable << std::endl;
    
    modifiable.replace(0, 5, "Hi");
    std::cout << "  After replace: " << modifiable << std::endl;
    
    modifiable.erase(2, 2);
    std::cout << "  After erase: " << modifiable << std::endl;
    
    // 3. String Searching
    std::cout << "\n3. STRING SEARCHING:" << std::endl;
    
    std::string text = "The quick brown fox jumps over the lazy dog";
    std::cout << "  Text: " << text << std::endl;
    
    // Find substring
    size_t pos = text.find("fox");
    if (pos != std::string::npos) {
        std::cout << "  'fox' found at position: " << pos << std::endl;
    }
    
    // Find character
    pos = text.find('q');
    if (pos != std::string::npos) {
        std::cout << "  'q' found at position: " << pos << std::endl;
    }
    
    // Find last occurrence
    pos = text.rfind('o');
    if (pos != std::string::npos) {
        std::cout << "  Last 'o' found at position: " << pos << std::endl;
    }
    
    // Find first of
    pos = text.find_first_of("aeiou");
    if (pos != std::string::npos) {
        std::cout << "  First vowel found at position: " << pos << std::endl;
    }
    
    // Find first not of
    pos = text.find_first_not_of("The ");
    if (pos != std::string::npos) {
        std::cout << "  First non-space character after 'The ' at position: " << pos << std::endl;
    }
    
    // 4. String Comparison
    std::cout << "\n4. STRING COMPARISON:" << std::endl;
    
    std::string str_a = "apple";
    std::string str_b = "banana";
    std::string str_c = "apple";
    
    std::cout << "  str_a: " << str_a << std::endl;
    std::cout << "  str_b: " << str_b << std::endl;
    std::cout << "  str_c: " << str_c << std::endl;
    
    std::cout << "  str_a == str_b: " << (str_a == str_b) << std::endl;
    std::cout << "  str_a == str_c: " << (str_a == str_c) << std::endl;
    std::cout << "  str_a < str_b: " << (str_a < str_b) << std::endl;
    std::cout << "  str_a.compare(str_b): " << str_a.compare(str_b) << std::endl;
    
    // Case-insensitive comparison
    auto case_insensitive_compare = [](const std::string& a, const std::string& b) {
        return std::lexicographical_compare(
            a.begin(), a.end(),
            b.begin(), b.end(),
            [](char c1, char c2) {
                return std::tolower(c1) < std::tolower(c2);
            }
        );
    };
    
    std::string str_d = "Apple";
    std::cout << "  str_a < str_d (case-sensitive): " << (str_a < str_d) << std::endl;
    std::cout << "  str_a < str_d (case-insensitive): " << case_insensitive_compare(str_a, str_d) << std::endl;
    
    // 5. String Conversion
    std::cout << "\n5. STRING CONVERSION:" << std::endl;
    
    // String to number
    std::string number_str = "12345";
    int number = std::stoi(number_str);
    std::cout << "  String to int: " << number_str << " -> " << number << std::endl;
    
    std::string float_str = "3.14159";
    double float_num = std::stod(float_str);
    std::cout << "  String to double: " << float_str << " -> " << float_num << std::endl;
    
    // Number to string
    int int_val = 42;
    std::string int_str = std::to_string(int_val);
    std::cout << "  Int to string: " << int_val << " -> " << int_str << std::endl;
    
    double double_val = 2.71828;
    std::string double_str = std::to_string(double_val);
    std::cout << "  Double to string: " << double_val << " -> " << double_str << std::endl;
    
    // String stream
    std::stringstream ss;
    ss << "Number: " << 42 << ", Value: " << 3.14;
    std::string stream_str = ss.str();
    std::cout << "  String stream: " << stream_str << std::endl;
    
    // 6. String Formatting
    std::cout << "\n6. STRING FORMATTING:" << std::endl;
    
    // Using stringstream for formatting
    std::stringstream fmt_ss;
    fmt_ss << std::fixed << std::setprecision(2) << 3.14159;
    std::cout << "  Formatted number: " << fmt_ss.str() << std::endl;
    
    // Padding
    std::string padded = "42";
    padded.insert(0, 3 - padded.length(), '0');
    std::cout << "  Padded string: " << padded << std::endl;
    
    // 7. String Views
    std::cout << "\n7. STRING VIEWS:" << std::endl;
    
    std::string long_string = "This is a very long string that we want to process";
    std::string_view view1(long_string);
    std::string_view view2(long_string, 10);  // First 10 characters
    std::string_view view3(long_string.c_str() + 5, 15);  // Substring
    
    std::cout << "  Original string: " << long_string << std::endl;
    std::cout << "  View1: " << view1 << std::endl;
    std::cout << "  View2: " << view2 << std::endl;
    std::cout << "  View3: " << view3 << std::endl;
    
    // String view operations
    std::cout << "  View1 length: " << view1.length() << std::endl;
    std::cout << "  View1 empty: " << view1.empty() << std::endl;
    std::cout << "  View1 front: " << view1.front() << std::endl;
    std::cout << "  View1 back: " << view1.back() << std::endl;
    
    // String view searching
    size_t view_pos = view1.find("very");
    if (view_pos != std::string_view::npos) {
        std::cout << "  'very' found in view at position: " << view_pos << std::endl;
    }
    
    // 8. String Algorithms
    std::cout << "\n8. STRING ALGORITHMS:" << std::endl;
    
    std::string algorithm_str = "Hello World";
    std::cout << "  Original: " << algorithm_str << std::endl;
    
    // Transform to uppercase
    std::transform(algorithm_str.begin(), algorithm_str.end(), algorithm_str.begin(), ::toupper);
    std::cout << "  Uppercase: " << algorithm_str << std::endl;
    
    // Transform to lowercase
    std::transform(algorithm_str.begin(), algorithm_str.end(), algorithm_str.begin(), ::tolower);
    std::cout << "  Lowercase: " << algorithm_str << std::endl;
    
    // Reverse
    std::reverse(algorithm_str.begin(), algorithm_str.end());
    std::cout << "  Reversed: " << algorithm_str << std::endl;
    
    // Sort characters
    std::sort(algorithm_str.begin(), algorithm_str.end());
    std::cout << "  Sorted: " << algorithm_str << std::endl;
    
    // 9. String Tokenization
    std::cout << "\n9. STRING TOKENIZATION:" << std::endl;
    
    std::string tokenize_str = "apple,banana,cherry,date";
    std::cout << "  Original: " << tokenize_str << std::endl;
    
    std::vector<std::string> tokens;
    std::stringstream token_stream(tokenize_str);
    std::string token;
    
    while (std::getline(token_stream, token, ',')) {
        tokens.push_back(token);
    }
    
    std::cout << "  Tokens: ";
    for (const auto& t : tokens) {
        std::cout << "[" << t << "] ";
    }
    std::cout << std::endl;
    
    // 10. String Validation
    std::cout << "\n10. STRING VALIDATION:" << std::endl;
    
    auto is_numeric = [](const std::string& str) -> bool {
        return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
    };
    
    auto is_alpha = [](const std::string& str) -> bool {
        return !str.empty() && std::all_of(str.begin(), str.end(), ::isalpha);
    };
    
    auto is_alphanumeric = [](const std::string& str) -> bool {
        return !str.empty() && std::all_of(str.begin(), str.end(), ::isalnum);
    };
    
    std::vector<std::string> test_strings = {"123", "abc", "abc123", "hello world", "123.45"};
    
    for (const auto& test_str : test_strings) {
        std::cout << "  '" << test_str << "': ";
        std::cout << "numeric=" << is_numeric(test_str) << ", ";
        std::cout << "alpha=" << is_alpha(test_str) << ", ";
        std::cout << "alphanumeric=" << is_alphanumeric(test_str) << std::endl;
    }
    
    // 11. String Performance
    std::cout << "\n11. STRING PERFORMANCE:" << std::endl;
    
    const int num_iterations = 10000;
    
    // String concatenation performance
    auto start = std::chrono::high_resolution_clock::now();
    
    std::string result = "";
    for (int i = 0; i < num_iterations; ++i) {
        result += "a";
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto concatenation_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // String stream performance
    start = std::chrono::high_resolution_clock::now();
    
    std::stringstream ss_perf;
    for (int i = 0; i < num_iterations; ++i) {
        ss_perf << "a";
    }
    std::string result2 = ss_perf.str();
    
    end = std::chrono::high_resolution_clock::now();
    auto stream_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "  Concatenation time: " << concatenation_time.count() << " microseconds" << std::endl;
    std::cout << "  String stream time: " << stream_time.count() << " microseconds" << std::endl;
    std::cout << "  Concatenation speedup: " << (double)stream_time.count() / concatenation_time.count() << "x" << std::endl;
    
    // 12. Advanced String Operations
    std::cout << "\n12. ADVANCED STRING OPERATIONS:" << std::endl;
    
    std::string advanced_str = "  Hello, World!  ";
    std::cout << "  Original: '" << advanced_str << "'" << std::endl;
    
    // Trim whitespace
    auto trim = [](std::string& str) {
        str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
        str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), str.end());
    };
    
    trim(advanced_str);
    std::cout << "  Trimmed: '" << advanced_str << "'" << std::endl;
    
    // Split into words
    std::string sentence = "The quick brown fox jumps over the lazy dog";
    std::vector<std::string> words;
    std::istringstream word_stream(sentence);
    std::string word;
    
    while (word_stream >> word) {
        words.push_back(word);
    }
    
    std::cout << "  Words: ";
    for (const auto& w : words) {
        std::cout << "[" << w << "] ";
    }
    std::cout << std::endl;
    
    // Join words
    std::string joined = "";
    for (size_t i = 0; i < words.size(); ++i) {
        if (i > 0) joined += " ";
        joined += words[i];
    }
    std::cout << "  Joined: " << joined << std::endl;
    
    // 13. String View Performance
    std::cout << "\n13. STRING VIEW PERFORMANCE:" << std::endl;
    
    std::string large_string(10000, 'a');
    std::string_view large_view(large_string);
    
    // String operations
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        std::string substr = large_string.substr(100, 100);
    }
    end = std::chrono::high_resolution_clock::now();
    auto string_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // String view operations
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        std::string_view substr_view = large_view.substr(100, 100);
    }
    end = std::chrono::high_resolution_clock::now();
    auto view_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "  String operations time: " << string_time.count() << " microseconds" << std::endl;
    std::cout << "  String view operations time: " << view_time.count() << " microseconds" << std::endl;
    std::cout << "  String view speedup: " << (double)string_time.count() / view_time.count() << "x" << std::endl;
    
    std::cout << "\nStrings and string views demonstration completed!" << std::endl;
    return 0;
}
