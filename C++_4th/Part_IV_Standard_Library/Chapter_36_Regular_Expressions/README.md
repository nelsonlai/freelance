# Chapter 36: Regular Expressions

## 📘 Learning Objectives

After completing this chapter, you will:
- Master regular expression syntax and patterns
- Understand std::regex and related classes
- Learn about pattern matching and replacement
- Master regex performance optimization
- Understand common regex use cases

## 🎯 Key Concepts

### 1. Regular Expression Basics

- **Regex syntax**: Pattern syntax and metacharacters
- **Character classes**: Character set definitions
- **Quantifiers**: Repetition operators
- **Anchors**: Position assertions
- **Groups**: Capturing and non-capturing groups

### 2. std::regex Classes

- **std::regex**: Regular expression object
- **std::regex_match**: Exact string matching
- **std::regex_search**: Substring matching
- **std::regex_replace**: String replacement
- **std::smatch**: Match results

### 3. Pattern Matching

- **Match operations**: Different matching modes
- **Match results**: Accessing captured groups
- **Iterators**: Regex iterator usage
- **Flags**: Regex matching flags
- **Error handling**: Regex error handling

### 4. String Manipulation

- **Search and replace**: Pattern-based replacement
- **String validation**: Input validation with regex
- **Text processing**: Advanced text processing
- **Data extraction**: Extracting data from text
- **Format validation**: Format checking

### 5. Performance and Optimization

- **Regex compilation**: Compile-time vs runtime
- **Regex optimization**: Performance optimization
- **Memory usage**: Memory efficiency
- **Alternative approaches**: When not to use regex
- **Best practices**: Regex best practices

## 🧩 Practice Exercises

### Exercise 36.1: Basic Regex
Create basic regular expressions for common patterns.

### Exercise 36.2: Pattern Matching
Use regex for pattern matching and validation.

### Exercise 36.3: String Replacement
Perform string replacement with regex.

### Exercise 36.4: Data Extraction
Extract data from text using regex.

## 💻 Code Examples

### Basic Regex Usage
```cpp
#include <iostream>
#include <regex>
#include <string>

int main() {
    std::string text = "The quick brown fox jumps over the lazy dog";
    std::regex pattern(R"(\b\w{4}\b)");  // 4-letter words
    
    std::sregex_iterator begin(text.begin(), text.end(), pattern);
    std::sregex_iterator end;
    
    std::cout << "4-letter words: ";
    for (auto it = begin; it != end; ++it) {
        std::cout << it->str() << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
```

### Email Validation
```cpp
#include <iostream>
#include <regex>
#include <string>

bool is_valid_email(const std::string& email) {
    std::regex email_pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return std::regex_match(email, email_pattern);
}

int main() {
    std::vector<std::string> emails = {
        "user@example.com",
        "invalid.email",
        "test@domain.org",
        "bad@email@domain.com"
    };
    
    for (const auto& email : emails) {
        std::cout << email << " is " 
                  << (is_valid_email(email) ? "valid" : "invalid") 
                  << std::endl;
    }
    
    return 0;
}
```

## 🎓 Key Takeaways

1. **Master regex syntax** for effective pattern matching
2. **Use appropriate regex classes** for different operations
3. **Optimize regex performance** for large-scale applications
4. **Validate input** with regex patterns
5. **Extract data** efficiently from text

## 🔗 Next Steps

After mastering regular expressions, proceed to Chapter 37 to learn about memory management.

## 📚 Additional Resources

- C++ Reference: Regular Expressions
- C++ Core Guidelines: Regex
- Practice with complex regex patterns
