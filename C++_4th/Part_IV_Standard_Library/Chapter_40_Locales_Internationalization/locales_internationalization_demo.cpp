#include <iostream>
#include <locale>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

// Demonstrates locales and internationalization
int main() {
    std::cout << "Locales and Internationalization Demonstration" << std::endl;
    std::cout << "==============================================" << std::endl;
    
    // 1. Basic Locale Operations
    std::cout << "\n1. BASIC LOCALE OPERATIONS:" << std::endl;
    
    // Get current locale
    std::locale current_locale = std::locale();
    std::cout << "  Current locale: " << current_locale.name() << std::endl;
    
    // Set specific locale
    try {
        std::locale::global(std::locale("en_US.UTF-8"));
        std::cout << "  Set locale to: " << std::locale().name() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "  Failed to set en_US.UTF-8: " << e.what() << std::endl;
    }
    
    // Try different locales
    std::vector<std::string> locales = {"C", "POSIX", "en_US", "de_DE", "fr_FR"};
    for (const auto& loc_name : locales) {
        try {
            std::locale test_locale(loc_name);
            std::cout << "  Available locale: " << loc_name << std::endl;
        } catch (const std::exception& e) {
            std::cout << "  Unavailable locale: " << loc_name << std::endl;
        }
    }
    
    // 2. Number Formatting
    std::cout << "\n2. NUMBER FORMATTING:" << std::endl;
    
    double number = 1234567.89;
    
    // Default formatting
    std::cout << "  Default formatting: " << number << std::endl;
    
    // Format with different locales
    try {
        std::locale german_locale("de_DE");
        std::cout.imbue(german_locale);
        std::cout << "  German formatting: " << number << std::endl;
    } catch (const std::exception& e) {
        std::cout << "  German locale not available" << std::endl;
    }
    
    // Reset to default
    std::cout.imbue(std::locale());
    
    // Manual formatting
    std::cout << "  Fixed precision: " << std::fixed << std::setprecision(2) << number << std::endl;
    std::cout << "  Scientific notation: " << std::scientific << number << std::endl;
    
    // Reset formatting
    std::cout << std::defaultfloat;
    
    // 3. Currency Formatting
    std::cout << "\n3. CURRENCY FORMATTING:" << std::endl;
    
    double amount = 1234.56;
    
    // Use money_put facet
    try {
        std::locale us_locale("en_US");
        const std::money_put<char>& money_putter = std::use_facet<std::money_put<char>>(us_locale);
        
        std::ostringstream oss;
        oss.imbue(us_locale);
        
        long cents = static_cast<long>(amount * 100);
        money_putter.put(oss, false, oss, ' ', cents);
        
        std::cout << "  US currency: " << oss.str() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "  Currency formatting not available" << std::endl;
    }
    
    // 4. Date and Time Formatting
    std::cout << "\n4. DATE AND TIME FORMATTING:" << std::endl;
    
    std::time_t now = std::time(nullptr);
    std::tm* timeinfo = std::localtime(&now);
    
    // Format with different locales
    char buffer[100];
    
    // Default locale
    std::strftime(buffer, sizeof(buffer), "%c", timeinfo);
    std::cout << "  Default date/time: " << buffer << std::endl;
    
    // US format
    std::strftime(buffer, sizeof(buffer), "%m/%d/%Y %I:%M:%S %p", timeinfo);
    std::cout << "  US format: " << buffer << std::endl;
    
    // European format
    std::strftime(buffer, sizeof(buffer), "%d.%m.%Y %H:%M:%S", timeinfo);
    std::cout << "  European format: " << buffer << std::endl;
    
    // ISO format
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    std::cout << "  ISO format: " << buffer << std::endl;
    
    // 5. Character Classification
    std::cout << "\n5. CHARACTER CLASSIFICATION:" << std::endl;
    
    std::string test_chars = "Hello123!@#";
    std::cout << "  Test string: " << test_chars << std::endl;
    
    for (char c : test_chars) {
        std::cout << "  '" << c << "': ";
        std::cout << "alpha=" << std::isalpha(c) << ", ";
        std::cout << "digit=" << std::isdigit(c) << ", ";
        std::cout << "alnum=" << std::isalnum(c) << ", ";
        std::cout << "space=" << std::isspace(c) << ", ";
        std::cout << "punct=" << std::ispunct(c) << std::endl;
    }
    
    // 6. String Collation
    std::cout << "\n6. STRING COLLATION:" << std::endl;
    
    std::vector<std::string> words = {"apple", "Apple", "banana", "Banana", "cherry"};
    std::cout << "  Original order: ";
    for (const auto& word : words) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
    
    // Sort with default locale
    std::sort(words.begin(), words.end());
    std::cout << "  Sorted (default): ";
    for (const auto& word : words) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
    
    // Case-insensitive sort
    std::sort(words.begin(), words.end(), [](const std::string& a, const std::string& b) {
        return std::lexicographical_compare(
            a.begin(), a.end(),
            b.begin(), b.end(),
            [](char c1, char c2) {
                return std::tolower(c1) < std::tolower(c2);
            }
        );
    });
    
    std::cout << "  Case-insensitive sort: ";
    for (const auto& word : words) {
        std::cout << word << " ";
    }
    std::cout << std::endl;
    
    // 7. Unicode and Wide Characters
    std::cout << "\n7. UNICODE AND WIDE CHARACTERS:" << std::endl;
    
    // Wide string
    std::wstring wide_str = L"Hello, 世界!";
    std::wcout << L"  Wide string: " << wide_str << std::endl;
    
    // Convert between wide and narrow strings
    std::string narrow_str = "Hello, World!";
    std::wstring converted_wide;
    
    // Simple conversion (ASCII only)
    for (char c : narrow_str) {
        converted_wide += static_cast<wchar_t>(c);
    }
    std::wcout << L"  Converted wide: " << converted_wide << std::endl;
    
    // 8. Locale-Specific Sorting
    std::cout << "\n8. LOCALE-SPECIFIC SORTING:" << std::endl;
    
    std::vector<std::string> names = {"Zoe", "Ångström", "Émile", "François", "José"};
    std::cout << "  Original names: ";
    for (const auto& name : names) {
        std::cout << name << " ";
    }
    std::cout << std::endl;
    
    // Default sort
    std::vector<std::string> default_sorted = names;
    std::sort(default_sorted.begin(), default_sorted.end());
    std::cout << "  Default sort: ";
    for (const auto& name : default_sorted) {
        std::cout << name << " ";
    }
    std::cout << std::endl;
    
    // 9. Text Processing with Locales
    std::cout << "\n9. TEXT PROCESSING WITH LOCALES:" << std::endl;
    
    std::string text = "The Quick Brown Fox Jumps Over The Lazy Dog";
    std::cout << "  Original text: " << text << std::endl;
    
    // Convert to lowercase using locale
    std::string lower_text = text;
    std::transform(lower_text.begin(), lower_text.end(), lower_text.begin(),
                  [](char c) { return std::tolower(c); });
    std::cout << "  Lowercase: " << lower_text << std::endl;
    
    // Convert to uppercase using locale
    std::string upper_text = text;
    std::transform(upper_text.begin(), upper_text.end(), upper_text.begin(),
                  [](char c) { return std::toupper(c); });
    std::cout << "  Uppercase: " << upper_text << std::endl;
    
    // 10. File I/O with Locales
    std::cout << "\n10. FILE I/O WITH LOCALES:" << std::endl;
    
    // Write to file with specific locale
    std::ofstream file("locale_test.txt");
    if (file.is_open()) {
        file.imbue(std::locale("en_US"));
        file << "Number: " << std::fixed << std::setprecision(2) << 1234.56 << std::endl;
        file << "Date: " << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S") << std::endl;
        file.close();
        std::cout << "  File written with locale formatting" << std::endl;
    }
    
    // Read from file
    std::ifstream read_file("locale_test.txt");
    if (read_file.is_open()) {
        std::string line;
        while (std::getline(read_file, line)) {
            std::cout << "  File content: " << line << std::endl;
        }
        read_file.close();
    }
    
    // 11. Custom Locale Facets
    std::cout << "\n11. CUSTOM LOCALE FACETS:" << std::endl;
    
    // Simple custom facet example
    class CustomFacet : public std::locale::facet {
    public:
        static std::locale::id id;
        
        CustomFacet() : std::locale::facet(1) {}
        
        std::string format_number(int n) const {
            return "Custom: " + std::to_string(n);
        }
    };
    
    std::locale::id CustomFacet::id;
    
    // Create custom locale
    std::locale custom_locale(std::locale(), new CustomFacet());
    
    // Use custom facet
    const CustomFacet& custom_facet = std::use_facet<CustomFacet>(custom_locale);
    std::cout << "  Custom formatting: " << custom_facet.format_number(42) << std::endl;
    
    // 12. Locale Performance
    std::cout << "\n12. LOCALE PERFORMANCE:" << std::endl;
    
    const int num_iterations = 100000;
    std::string test_string = "Hello, World!";
    
    // Performance test: locale-aware operations
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < num_iterations; ++i) {
        std::string result;
        std::transform(test_string.begin(), test_string.end(), std::back_inserter(result),
                      [](char c) { return std::tolower(c); });
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto locale_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // Performance test: simple operations
    start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < num_iterations; ++i) {
        std::string result;
        std::transform(test_string.begin(), test_string.end(), std::back_inserter(result),
                      [](char c) { return (c >= 'A' && c <= 'Z') ? c + 32 : c; });
    }
    
    end = std::chrono::high_resolution_clock::now();
    auto simple_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "  Locale-aware operations time: " << locale_time.count() << " microseconds" << std::endl;
    std::cout << "  Simple operations time: " << simple_time.count() << " microseconds" << std::endl;
    std::cout << "  Locale overhead: " << (double)locale_time.count() / simple_time.count() << "x" << std::endl;
    
    // 13. Best Practices
    std::cout << "\n13. BEST PRACTICES:" << std::endl;
    
    // Always check if locale is available
    auto safe_locale_set = [](const std::string& locale_name) -> bool {
        try {
            std::locale test_locale(locale_name);
            std::locale::global(test_locale);
            return true;
        } catch (const std::exception& e) {
            std::cout << "  Failed to set locale " << locale_name << ": " << e.what() << std::endl;
            return false;
        }
    };
    
    // Use locale-specific operations
    std::string user_input = "  Hello, World!  ";
    
    // Trim whitespace using locale
    auto trim_locale = [](std::string& str) {
        auto start = str.begin();
        auto end = str.end();
        
        // Find first non-space character
        while (start != end && std::isspace(*start)) {
            ++start;
        }
        
        // Find last non-space character
        while (start != end && std::isspace(*(end - 1))) {
            --end;
        }
        
        str = std::string(start, end);
    };
    
    trim_locale(user_input);
    std::cout << "  Trimmed input: '" << user_input << "'" << std::endl;
    
    // Use appropriate character classification
    std::string mixed_text = "Hello123!@#";
    int alpha_count = 0, digit_count = 0, punct_count = 0;
    
    for (char c : mixed_text) {
        if (std::isalpha(c)) alpha_count++;
        else if (std::isdigit(c)) digit_count++;
        else if (std::ispunct(c)) punct_count++;
    }
    
    std::cout << "  Character counts - Alpha: " << alpha_count 
              << ", Digit: " << digit_count 
              << ", Punctuation: " << punct_count << std::endl;
    
    std::cout << "\nLocales and internationalization demonstration completed!" << std::endl;
    return 0;
}
