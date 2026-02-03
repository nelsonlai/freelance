/*
 * Lesson 6.3: References
 * 
 * This file demonstrates reference declaration, initialization,
 * reference vs pointer differences, and const references.
 */

#include <iostream>
#include <string>
#include <vector>

// Function to demonstrate basic references
void demonstrateBasicReferences() {
    std::cout << "=== Basic References Demonstration ===" << std::endl;
    
    int x = 42;
    int& ref = x;  // Reference to x
    
    std::cout << "Variable x: " << x << std::endl;
    std::cout << "Reference ref: " << ref << std::endl;
    std::cout << "Address of x: " << &x << std::endl;
    std::cout << "Address of ref: " << &ref << std::endl;
    
    // Modify through reference
    ref = 100;
    std::cout << "
After ref = 100:" << std::endl;
    std::cout << "Variable x: " << x << std::endl;
    std::cout << "Reference ref: " << ref << std::endl;
    
    // Multiple references to same variable
    int& ref2 = x;
    int& ref3 = x;
    
    std::cout << "
Multiple references to same variable:" << std::endl;
    std::cout << "ref2: " << ref2 << std::endl;
    std::cout << "ref3: " << ref3 << std::endl;
    
    // All references have same address
    std::cout << "All references point to same address: " << &ref << std::endl;
}

// Function to demonstrate reference vs pointer
void demonstrateReferenceVsPointer() {
    std::cout << "
=== Reference vs Pointer ===" << std::endl;
    
    int x = 42;
    int& ref = x;
    int* ptr = &x;
    
    std::cout << "Variable x: " << x << std::endl;
    std::cout << "Reference ref: " << ref << std::endl;
    std::cout << "Pointer *ptr: " << *ptr << std::endl;
    
    std::cout << "
Address comparisons:" << std::endl;
    std::cout << "&x: " << &x << std::endl;
    std::cout << "&ref: " << &ref << std::endl;
    std::cout << "ptr: " << ptr << std::endl;
    
    // Modification through reference
    ref = 100;
    std::cout << "
After ref = 100:" << std::endl;
    std::cout << "x: " << x << ", ref: " << ref << ", *ptr: " << *ptr << std::endl;
    
    // Modification through pointer
    *ptr = 200;
    std::cout << "
After *ptr = 200:" << std::endl;
    std::cout << "x: " << x << ", ref: " << ref << ", *ptr: " << *ptr << std::endl;
    
    // Pointer can be reassigned, reference cannot
    int y = 300;
    ptr = &y;  // OK: pointer can be reassigned
    std::cout << "
After ptr = &y:" << std::endl;
    std::cout << "x: " << x << ", ref: " << ref << ", *ptr: " << *ptr << std::endl;
    
    // ref = y;  // This would modify x, not reassign ref
}

// Function to demonstrate const references
void demonstrateConstReferences() {
    std::cout << "
=== Const References ===" << std::endl;
    
    int x = 42;
    const int& const_ref = x;
    
    std::cout << "Variable x: " << x << std::endl;
    std::cout << "Const reference: " << const_ref << std::endl;
    
    // Can modify original variable
    x = 100;
    std::cout << "
After x = 100:" << std::endl;
    std::cout << "x: " << x << ", const_ref: " << const_ref << std::endl;
    
    // Cannot modify through const reference
    // const_ref = 200;  // Error: cannot modify through const reference
    
    // Const reference to temporary
    const int& temp_ref = 42;
    std::cout << "
Const reference to temporary: " << temp_ref << std::endl;
    
    // Const reference to expression
    const int& expr_ref = x + 10;
    std::cout << "Const reference to expression: " << expr_ref << std::endl;
}

// Function to demonstrate reference parameters
void demonstrateReferenceParameters() {
    std::cout << "
=== Reference Parameters ===" << std::endl;
    
    // Function with reference parameter
    auto modifyValue = [](int& param) {
        param *= 2;
        std::cout << "Inside function: param = " << param << std::endl;
    };
    
    // Function with const reference parameter
    auto readValue = [](const int& param) {
        std::cout << "Inside function: param = " << param << std::endl;
        // param = 100;  // Error: cannot modify through const reference
    };
    
    int value = 50;
    std::cout << "Original value: " << value << std::endl;
    
    modifyValue(value);
    std::cout << "After modifyValue: " << value << std::endl;
    
    readValue(value);
    std::cout << "After readValue: " << value << std::endl;
}

// Function to demonstrate reference return values
void demonstrateReferenceReturn() {
    std::cout << "
=== Reference Return Values ===" << std::endl;
    
    // Safe: return reference to static variable
    auto& getStaticValue = []() -> int& {
        static int value = 42;
        return value;
    };
    
    int& ref = getStaticValue();
    std::cout << "Reference to static value: " << ref << std::endl;
    
    // Modify through returned reference
    ref = 100;
    std::cout << "After modification: " << getStaticValue() << std::endl;
    
    // Dangerous: return reference to local variable (don't do this!)
    auto& getLocalValue = []() -> int& {
        int local = 42;  // Local variable
        return local;    // DANGEROUS: local will be destroyed!
    };
    
    // This would be undefined behavior:
    // int& dangerous_ref = getLocalValue();
    // std::cout << dangerous_ref << std::endl;  // Undefined behavior!
    
    std::cout << "Note: Returning reference to local variable is dangerous!" << std::endl;
}

// Function to demonstrate references with containers
void demonstrateReferencesWithContainers() {
    std::cout << "
=== References with Containers ===" << std::endl;
    
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    
    // Reference to container element
    int& first_element = numbers[0];
    std::cout << "First element: " << first_element << std::endl;
    
    // Modify through reference
    first_element = 100;
    std::cout << "After modification: " << numbers[0] << std::endl;
    
    // Range-based for loop with references
    std::cout << "
Range-based for loop with references:" << std::endl;
    for (int& element : numbers) {
        element *= 2;  // Modify each element
    }
    
    std::cout << "After doubling all elements:" << std::endl;
    for (const int& element : numbers) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    
    // Const references in range-based for loop
    std::cout << "
Const references in range-based for loop:" << std::endl;
    for (const int& element : numbers) {
        std::cout << element << " ";  // Read-only access
    }
    std::cout << std::endl;
}

// Function to demonstrate references with strings
void demonstrateReferencesWithStrings() {
    std::cout << "
=== References with Strings ===" << std::endl;
    
    std::string text = "Hello, World!";
    
    // Reference to string
    std::string& text_ref = text;
    std::cout << "Original text: " << text << std::endl;
    std::cout << "Reference: " << text_ref << std::endl;
    
    // Modify through reference
    text_ref += " How are you?";
    std::cout << "After modification: " << text << std::endl;
    
    // Const reference to string
    const std::string& const_text_ref = text;
    std::cout << "Const reference: " << const_text_ref << std::endl;
    
    // Function with const reference parameter
    auto printString = [](const std::string& str) {
        std::cout << "String length: " << str.length() << std::endl;
        std::cout << "String content: " << str << std::endl;
    };
    
    printString(text);
}

// Function to demonstrate reference safety
void demonstrateReferenceSafety() {
    std::cout << "
=== Reference Safety ===" << std::endl;
    
    // Safe: reference to valid object
    int x = 42;
    int& safe_ref = x;
    std::cout << "Safe reference: " << safe_ref << std::endl;
    
    // Safe: const reference to temporary
    const int& temp_ref = 100;
    std::cout << "Const reference to temporary: " << temp_ref << std::endl;
    
    // Safe: reference to static variable
    static int static_var = 200;
    int& static_ref = static_var;
    std::cout << "Reference to static variable: " << static_ref << std::endl;
    
    // Dangerous: reference to local variable in function
    auto dangerousFunction = []() -> int& {
        int local = 300;
        return local;  // DANGEROUS: local will be destroyed!
    };
    
    std::cout << "
Warning: Returning reference to local variable is dangerous!" << std::endl;
    std::cout << "The local variable will be destroyed when the function returns." << std::endl;
    std::cout << "Accessing the returned reference will cause undefined behavior." << std::endl;
}

// Function to demonstrate reference initialization
void demonstrateReferenceInitialization() {
    std::cout << "
=== Reference Initialization ===" << std::endl;
    
    int x = 42;
    
    // Valid reference initialization
    int& ref1 = x;
    std::cout << "ref1: " << ref1 << std::endl;
    
    // Reference to reference (same as reference to original)
    int& ref2 = ref1;
    std::cout << "ref2: " << ref2 << std::endl;
    
    // Const reference to non-const variable
    const int& const_ref = x;
    std::cout << "const_ref: " << const_ref << std::endl;
    
    // Const reference to temporary
    const int& temp_ref = 42;
    std::cout << "temp_ref: " << temp_ref << std::endl;
    
    // Const reference to expression
    const int& expr_ref = x + 10;
    std::cout << "expr_ref: " << expr_ref << std::endl;
    
    std::cout << "
Invalid reference initialization (commented out):" << std::endl;
    std::cout << "// int& bad_ref;        // Error: must be initialized" << std::endl;
    std::cout << "// int& null_ref = nullptr;  // Error: no null references" << std::endl;
}

int main() {
    std::cout << "=== References Demonstration ===" << std::endl;
    std::cout << "This program demonstrates reference declaration, initialization,
"
              << "reference vs pointer differences, and const references.
" << std::endl;
    
    // Demonstrate various reference concepts
    demonstrateBasicReferences();
    demonstrateReferenceVsPointer();
    demonstrateConstReferences();
    demonstrateReferenceParameters();
    demonstrateReferenceReturn();
    demonstrateReferencesWithContainers();
    demonstrateReferencesWithStrings();
    demonstrateReferenceSafety();
    demonstrateReferenceInitialization();
    
    std::cout << "
=== Key Takeaways ===" << std::endl;
    std::cout << "1. References are aliases for existing variables" << std::endl;
    std::cout << "2. References must be initialized and cannot be reassigned" << std::endl;
    std::cout << "3. References cannot be null and don't support arithmetic" << std::endl;
    std::cout << "4. Const references prevent modification and work with temporaries" << std::endl;
    std::cout << "5. Reference parameters avoid copying and enable modification" << std::endl;
    std::cout << "6. References provide direct access without dereferencing" << std::endl;
    std::cout << "7. Be careful with reference lifetime to avoid dangling references" << std::endl;
    
    std::cout << "
Program completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o references 03_References.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o references 03_References.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 03_References.cpp
 * 
 * Running:
 * ./references (Linux/macOS)
 * references.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for lambdas.
 * C++17 is recommended for best reference support.
 * 
 * Reference Notes:
 * - References must be initialized
 * - References cannot be reassigned
 * - References cannot be null
 * - Use const references for read-only access
 * - Be careful with reference lifetime
 * - References provide performance benefits over copying
 */