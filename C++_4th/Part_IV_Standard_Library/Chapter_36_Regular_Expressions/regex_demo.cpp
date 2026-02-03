#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <fstream>

// Demonstrates regular expressions
int main() {
    std::cout << "Regular Expressions Demonstration" << std::endl;
    std::cout << "=================================" << std::endl;
    
    // 1. Basic regex patterns
    std::cout << "\n1. BASIC REGEX PATTERNS:" << std::endl;
    
    std::string text = "The quick brown fox jumps over the lazy dog. The fox is clever.";
    
    // Find all words
    std::regex word_pattern(R"(\b\w+\b)");
    std::sregex_iterator word_begin(text.begin(), text.end(), word_pattern);
    std::sregex_iterator word_end;
    
    std::cout << "All words: ";
    for (auto it = word_begin; it != word_end; ++it) {
        std::cout << it->str() << " ";
    }
    std::cout << std::endl;
    
    // Find 4-letter words
    std::regex four_letter_pattern(R"(\b\w{4}\b)");
    std::sregex_iterator four_letter_begin(text.begin(), text.end(), four_letter_pattern);
    std::sregex_iterator four_letter_end;
    
    std::cout << "4-letter words: ";
    for (auto it = four_letter_begin; it != four_letter_end; ++it) {
        std::cout << it->str() << " ";
    }
    std::cout << std::endl;
    
    // Find words starting with 't' or 'T'
    std::regex t_words_pattern(R"(\b[tT]\w+\b)");
    std::sregex_iterator t_words_begin(text.begin(), text.end(), t_words_pattern);
    std::sregex_iterator t_words_end;
    
    std::cout << "Words starting with 't' or 'T': ";
    for (auto it = t_words_begin; it != t_words_end; ++it) {
        std::cout << it->str() << " ";
    }
    std::cout << std::endl;
    
    // 2. Email validation
    std::cout << "\n2. EMAIL VALIDATION:" << std::endl;
    
    std::regex email_pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    
    std::vector<std::string> emails = {
        "user@example.com",
        "test.email@domain.org",
        "invalid.email",
        "bad@email@domain.com",
        "user+tag@example.co.uk",
        "user123@test-domain.com"
    };
    
    for (const auto& email : emails) {
        bool is_valid = std::regex_match(email, email_pattern);
        std::cout << email << " is " << (is_valid ? "valid" : "invalid") << std::endl;
    }
    
    // 3. Phone number validation
    std::cout << "\n3. PHONE NUMBER VALIDATION:" << std::endl;
    
    std::regex phone_pattern(R"(\+?1?[-.\s]?\(?([0-9]{3})\)?[-.\s]?([0-9]{3})[-.\s]?([0-9]{4}))");
    
    std::vector<std::string> phone_numbers = {
        "123-456-7890",
        "(123) 456-7890",
        "123.456.7890",
        "123 456 7890",
        "+1 123 456 7890",
        "1234567890",
        "invalid phone"
    };
    
    for (const auto& phone : phone_numbers) {
        bool is_valid = std::regex_match(phone, phone_pattern);
        std::cout << phone << " is " << (is_valid ? "valid" : "invalid") << std::endl;
    }
    
    // 4. String replacement
    std::cout << "\n4. STRING REPLACEMENT:" << std::endl;
    
    std::string original_text = "The cat sat on the mat. The cat was happy.";
    std::regex cat_pattern(R"(\bcat\b)");
    
    // Replace first occurrence
    std::string replaced_text = std::regex_replace(original_text, cat_pattern, "dog", std::regex_constants::format_first_only);
    std::cout << "Original: " << original_text << std::endl;
    std::cout << "First replacement: " << replaced_text << std::endl;
    
    // Replace all occurrences
    std::string all_replaced_text = std::regex_replace(original_text, cat_pattern, "dog");
    std::cout << "All replacements: " << all_replaced_text << std::endl;
    
    // 5. Data extraction
    std::cout << "\n5. DATA EXTRACTION:" << std::endl;
    
    std::string log_entry = "2023-12-07 14:30:25 ERROR: Database connection failed";
    std::regex log_pattern(R"((\d{4}-\d{2}-\d{2}) (\d{2}:\d{2}:\d{2}) (\w+): (.+))");
    
    std::smatch matches;
    if (std::regex_search(log_entry, matches, log_pattern)) {
        std::cout << "Date: " << matches[1] << std::endl;
        std::cout << "Time: " << matches[2] << std::endl;
        std::cout << "Level: " << matches[3] << std::endl;
        std::cout << "Message: " << matches[4] << std::endl;
    }
    
    // 6. URL parsing
    std::cout << "\n6. URL PARSING:" << std::endl;
    
    std::regex url_pattern(R"((https?://)?([^/]+)(/.*)?)");
    
    std::vector<std::string> urls = {
        "https://www.example.com/path/to/page",
        "http://example.com",
        "www.example.com/path",
        "example.com"
    };
    
    for (const auto& url : urls) {
        std::smatch url_matches;
        if (std::regex_search(url, url_matches, url_pattern)) {
            std::cout << "URL: " << url << std::endl;
            std::cout << "  Protocol: " << (url_matches[1].str().empty() ? "none" : url_matches[1].str()) << std::endl;
            std::cout << "  Domain: " << url_matches[2] << std::endl;
            std::cout << "  Path: " << (url_matches[3].str().empty() ? "/" : url_matches[3].str()) << std::endl;
        }
    }
    
    // 7. HTML tag extraction
    std::cout << "\n7. HTML TAG EXTRACTION:" << std::endl;
    
    std::string html = "<html><head><title>Test Page</title></head><body><h1>Welcome</h1><p>This is a test.</p></body></html>";
    std::regex tag_pattern(R"(<(\w+)[^>]*>(.*?)</\1>)");
    
    std::sregex_iterator tag_begin(html.begin(), html.end(), tag_pattern);
    std::sregex_iterator tag_end;
    
    std::cout << "HTML tags:" << std::endl;
    for (auto it = tag_begin; it != tag_end; ++it) {
        std::cout << "  Tag: " << (*it)[1] << ", Content: " << (*it)[2] << std::endl;
    }
    
    // 8. Credit card number validation
    std::cout << "\n8. CREDIT CARD NUMBER VALIDATION:" << std::endl;
    
    std::regex credit_card_pattern(R"(\b\d{4}[\s-]?\d{4}[\s-]?\d{4}[\s-]?\d{4}\b)");
    
    std::vector<std::string> card_numbers = {
        "1234-5678-9012-3456",
        "1234 5678 9012 3456",
        "1234567890123456",
        "1234-5678-9012-345",
        "1234-5678-9012-34567"
    };
    
    for (const auto& card : card_numbers) {
        bool is_valid = std::regex_match(card, credit_card_pattern);
        std::cout << card << " is " << (is_valid ? "valid" : "invalid") << std::endl;
    }
    
    // 9. Password strength validation
    std::cout << "\n9. PASSWORD STRENGTH VALIDATION:" << std::endl;
    
    std::regex weak_password(R"(^.{1,7}$)");
    std::regex medium_password(R"(^(?=.*[a-z])(?=.*[A-Z])(?=.*\d).{8,}$)");
    std::regex strong_password(R"(^(?=.*[a-z])(?=.*[A-Z])(?=.*\d)(?=.*[@$!%*?&]).{8,}$)");
    
    std::vector<std::string> passwords = {
        "password",
        "Password1",
        "Password123",
        "Password123!",
        "P@ssw0rd"
    };
    
    for (const auto& password : passwords) {
        std::string strength;
        if (std::regex_match(password, strong_password)) {
            strength = "strong";
        } else if (std::regex_match(password, medium_password)) {
            strength = "medium";
        } else if (std::regex_match(password, weak_password)) {
            strength = "weak";
        } else {
            strength = "invalid";
        }
        std::cout << password << " is " << strength << std::endl;
    }
    
    // 10. Regex performance comparison
    std::cout << "\n10. REGEX PERFORMANCE COMPARISON:" << std::endl;
    
    std::string large_text = "The quick brown fox jumps over the lazy dog. ";
    // Repeat the text many times
    for (int i = 0; i < 1000; ++i) {
        large_text += "The quick brown fox jumps over the lazy dog. ";
    }
    
    // Pre-compiled regex
    std::regex precompiled_pattern(R"(\b\w{4}\b)");
    
    auto start = std::chrono::high_resolution_clock::now();
    
    std::sregex_iterator perf_begin(large_text.begin(), large_text.end(), precompiled_pattern);
    std::sregex_iterator perf_end;
    
    int count = 0;
    for (auto it = perf_begin; it != perf_end; ++it) {
        count++;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Found " << count << " matches in " << duration.count() << " microseconds" << std::endl;
    
    // 11. Regex flags demonstration
    std::cout << "\n11. REGEX FLAGS DEMONSTRATION:" << std::endl;
    
    std::string case_text = "The Quick Brown Fox JUMPS over the LAZY dog.";
    
    // Case sensitive (default)
    std::regex case_sensitive(R"(\bquick\b)");
    std::cout << "Case sensitive search for 'quick': " << std::boolalpha << std::regex_search(case_text, case_sensitive) << std::endl;
    
    // Case insensitive
    std::regex case_insensitive(R"(\bquick\b)", std::regex_constants::icase);
    std::cout << "Case insensitive search for 'quick': " << std::boolalpha << std::regex_search(case_text, case_insensitive) << std::endl;
    
    // 12. Complex pattern matching
    std::cout << "\n12. COMPLEX PATTERN MATCHING:" << std::endl;
    
    std::string complex_text = "Contact us at support@company.com or call +1-555-123-4567 or visit https://www.company.com/contact";
    
    // Extract email, phone, and URL
    std::regex email_extract(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    std::regex phone_extract(R"(\+?1?[-.\s]?\(?([0-9]{3})\)?[-.\s]?([0-9]{3})[-.\s]?([0-9]{4}))");
    std::regex url_extract(R"(https?://[^\s]+)");
    
    std::cout << "Extracted information:" << std::endl;
    
    std::smatch email_match;
    if (std::regex_search(complex_text, email_match, email_extract)) {
        std::cout << "  Email: " << email_match.str() << std::endl;
    }
    
    std::smatch phone_match;
    if (std::regex_search(complex_text, phone_match, phone_extract)) {
        std::cout << "  Phone: " << phone_match.str() << std::endl;
    }
    
    std::smatch url_match;
    if (std::regex_search(complex_text, url_match, url_extract)) {
        std::cout << "  URL: " << url_match.str() << std::endl;
    }
    
    std::cout << "\nRegular expressions demonstration completed!" << std::endl;
    return 0;
}
