#include "parser.h"
#include <iostream>
#include <string>
#include <vector>

using namespace text_parser;

// Demonstrates the Text Parser Project
int main() {
    std::cout << "Text Parser Project Demonstration" << std::endl;
    std::cout << "=================================" << std::endl;
    
    try {
        // Create parser instance
        TextParser parser;
        
        // Configure parser
        parser.set_case_sensitive(true);
        parser.set_skip_comments(true);
        parser.set_skip_whitespace(true);
        
        // Test input strings
        std::vector<std::string> test_inputs = {
            "int x = 42;",
            "if (x > 0) { return x; }",
            "for (int i = 0; i < 10; ++i) { std::cout << i << std::endl; }",
            "std::string name = \"Hello, World!\";",
            "double result = calculate(3.14, 2.71);",
            "// This is a comment\nint value = 100;",
            "class MyClass {\npublic:\n    void method();\n};"
        };
        
        // Parse each test input
        for (size_t i = 0; i < test_inputs.size(); ++i) {
            std::cout << "\n" << (i + 1) << ". Parsing: \"" << test_inputs[i] << "\"" << std::endl;
            std::cout << "----------------------------------------" << std::endl;
            
            try {
                parser.parse_string(test_inputs[i]);
                
                // Print tokens
                parser.print_tokens();
                
                // Print any errors or warnings
                if (parser.has_errors()) {
                    std::cout << "\nErrors:" << std::endl;
                    parser.print_errors();
                }
                
                if (parser.has_warnings()) {
                    std::cout << "\nWarnings:" << std::endl;
                    parser.print_warnings();
                }
                
            } catch (const ParserException& e) {
                std::cout << "Parser error: " << e.what() << std::endl;
                if (e.get_line() > 0) {
                    std::cout << "At line " << e.get_line() << ", column " << e.get_column() << std::endl;
                }
            } catch (const std::exception& e) {
                std::cout << "Unexpected error: " << e.what() << std::endl;
            }
            
            // Clear parser for next iteration
            parser.clear();
        }
        
        // Test with more complex input
        std::cout << "\n\nComplex Input Test:" << std::endl;
        std::cout << "===================" << std::endl;
        
        std::string complex_input = R"(
#include <iostream>
#include <string>

class Calculator {
private:
    double value;
    
public:
    Calculator(double initial = 0) : value(initial) {}
    
    double add(double x) {
        value += x;
        return value;
    }
    
    double multiply(double x) {
        value *= x;
        return value;
    }
    
    double get_value() const {
        return value;
    }
};

int main() {
    Calculator calc(10.0);
    double result = calc.add(5.0).multiply(2.0);
    std::cout << "Result: " << result << std::endl;
    return 0;
}
)";
        
        std::cout << "Parsing complex C++ code..." << std::endl;
        parser.parse_string(complex_input);
        
        // Print summary
        std::cout << "\nParsing Summary:" << std::endl;
        std::cout << "================" << std::endl;
        std::cout << "Total tokens: " << parser.get_tokens().size() << std::endl;
        std::cout << "Errors: " << parser.get_errors().size() << std::endl;
        std::cout << "Warnings: " << parser.get_warnings().size() << std::endl;
        
        // Print first 20 tokens as sample
        std::cout << "\nFirst 20 tokens:" << std::endl;
        const auto& tokens = parser.get_tokens();
        for (size_t i = 0; i < std::min(tokens.size(), size_t(20)); ++i) {
            if (tokens[i].get_type() != TokenType::EOF_TOKEN) {
                std::cout << "  " << tokens[i].to_string() << std::endl;
            }
        }
        
        if (tokens.size() > 20) {
            std::cout << "  ... and " << (tokens.size() - 20) << " more tokens" << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cout << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\nText Parser Project demonstration completed successfully!" << std::endl;
    return 0;
}
