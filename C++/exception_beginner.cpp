/*
 * EXCEPTION HANDLING BEGINNER EXAMPLES
 * 
 * This file demonstrates basic exception handling concepts:
 * - What are exceptions and why do we need them?
 * - Basic try-catch blocks
 * - Standard exception types
 * - throw keyword
 * - Multiple catch blocks
 * - Exception propagation
 * - Exception safety basics
 * - Common error handling patterns
 * 
 * Learning Objectives:
 * - Understand what exceptions are and when to use them
 * - Learn basic try-catch-throw syntax
 * - Handle different types of exceptions
 * - Write exception-safe code
 * - Follow exception handling best practices
 * 
 * Prerequisites:
 * - Basic understanding of C++ syntax
 * - Familiarity with functions
 * - Understanding of control flow
 * 
 * Key Topics Covered:
 * - Exception basics
 * - Standard exception types
 * - Try-catch blocks
 * - Throwing exceptions
 * - Exception handling best practices
 */

#include <iostream>
#include <string>
#include <stdexcept>  // For standard exception types
#include <vector>
using namespace std;

// ==============================================================================
// SECTION 1: WHAT ARE EXCEPTIONS?
// ==============================================================================
/*
 * EXCEPTIONS:
 * 
 * An exception is a problem that arises during program execution.
 * Instead of crashing, C++ allows you to "catch" and handle these problems.
 * 
 * Traditional error handling (return codes):
 * - Function returns special value (-1, nullptr, etc.) to indicate error
 * - Caller must check return value
 * - Easy to forget to check
 * - Can't return error from constructor
 * 
 * Exception handling:
 * - Separates error handling from normal code
 * - Can't be ignored (program stops if not caught)
 * - Works with constructors
 * - Provides detailed error information
 * 
 * When to use exceptions:
 * ✓ Error conditions that are exceptional (not common)
 * ✓ Errors that can't be handled locally
 * ✓ Constructor failures
 * ✓ Deep call stacks where error needs to propagate up
 * 
 * When NOT to use exceptions:
 * ✗ Normal control flow
 * ✗ Expected conditions (like end of file)
 * ✗ Performance-critical code (exceptions have overhead)
 */

void whatAreExceptions() {
    cout << "=== WHAT ARE EXCEPTIONS? ===" << endl << endl;
    
    cout << "Without exceptions (old way):" << endl;
    cout << "   int result = divide(10, 0);" << endl;
    cout << "   if (result == -1) {  // Must remember to check!" << endl;
    cout << "       // Handle error" << endl;
    cout << "   }" << endl;
    cout << endl;
    
    cout << "With exceptions (modern way):" << endl;
    cout << "   try {" << endl;
    cout << "       int result = divide(10, 0);" << endl;
    cout << "   } catch (exception& e) {" << endl;
    cout << "       // Error automatically caught" << endl;
    cout << "   }" << endl;
    cout << endl;
    
    cout << "Benefits:" << endl;
    cout << "   ✓ Cleaner code (error handling separate)" << endl;
    cout << "   ✓ Can't be ignored" << endl;
    cout << "   ✓ Provides detailed error information" << endl;
    cout << "   ✓ Works with constructors" << endl;
    cout << "   ✓ Propagates up call stack automatically" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 2: BASIC TRY-CATCH SYNTAX
// ==============================================================================
/*
 * TRY-CATCH BLOCKS:
 * 
 * Syntax:
 *   try {
 *       // Code that might throw an exception
 *   } catch (ExceptionType& e) {
 *       // Handle the exception
 *   }
 * 
 * - try: Contains code that might throw an exception
 * - catch: Handles the exception if thrown
 * - throw: Throws an exception
 * 
 * Flow:
 * 1. Code in try block executes
 * 2. If exception thrown, jump to matching catch block
 * 3. Execute catch block code
 * 4. Continue after try-catch
 * 5. If no exception, skip catch block
 */

void basicTryCatchSyntax() {
    cout << "=== BASIC TRY-CATCH SYNTAX ===" << endl << endl;
    
    // Example 1: Simple try-catch
    cout << "1. Simple Try-Catch:" << endl;
    try {
        cout << "   Inside try block" << endl;
        throw runtime_error("Something went wrong!");  // Throw exception
        cout << "   This line never executes" << endl;
    } catch (runtime_error& e) {
        cout << "   Caught exception: " << e.what() << endl;
    }
    cout << "   Program continues normally" << endl;
    cout << endl;
    
    // Example 2: No exception thrown
    cout << "2. No Exception Thrown:" << endl;
    try {
        cout << "   Code executes normally" << endl;
        int x = 10;
        int y = 0;
        int z = x / y;
        cout << "   No exception thrown" << endl;
    } catch (runtime_error& e) {
        cout << "   This won't execute" << endl;
    }
    cout << "   Program continues" << endl;
    cout << endl;
    
    // Example 3: Exception with integer
    cout << "3. Throwing Different Types:" << endl;
    try {
        throw 42;  // Can throw any type
    } catch (int value) {
        cout << "   Caught integer: " << value << endl;
    }
    cout << endl;
    
    // Example 4: Exception with string
    try {
        throw string("Error message");
    } catch (string& msg) {
        cout << "   Caught string: " << msg << endl;
    }
    cout << endl;
}

// ==============================================================================
// SECTION 3: STANDARD EXCEPTION TYPES
// ==============================================================================
/*
 * STANDARD EXCEPTION HIERARCHY:
 * 
 * C++ provides a hierarchy of standard exception types:
 * 
 * exception (base class)
 * ├── logic_error
 * │   ├── invalid_argument
 * │   ├── domain_error
 * │   ├── length_error
 * │   ├── out_of_range
 * │   └── future_error
 * ├── runtime_error
 * │   ├── range_error
 * │   ├── overflow_error
 * │   ├── underflow_error
 * │   └── system_error
 * ├── bad_alloc (memory allocation failure)
 * ├── bad_cast (dynamic_cast failure)
 * └── bad_typeid (typeid on null pointer)
 * 
 * All have what() method that returns error message.
 */

void standardExceptionTypes() {
    cout << "=== STANDARD EXCEPTION TYPES ===" << endl << endl;
    
    // 1. runtime_error - General runtime error
    cout << "1. runtime_error:" << endl;
    try {
        throw runtime_error("General runtime error");
    } catch (runtime_error& e) {
        cout << "   Caught: " << e.what() << endl;
    }
    cout << endl;
    
    // 2. logic_error - Programming logic error
    cout << "2. logic_error:" << endl;
    try {
        throw logic_error("Logic error in program");
    } catch (logic_error& e) {
        cout << "   Caught: " << e.what() << endl;
    }
    cout << endl;
    
    // 3. invalid_argument - Invalid function argument
    cout << "3. invalid_argument:" << endl;
    try {
        throw invalid_argument("Invalid argument passed");
    } catch (invalid_argument& e) {
        cout << "   Caught: " << e.what() << endl;
    }
    cout << endl;
    
    // 4. out_of_range - Index out of range
    cout << "4. out_of_range:" << endl;
    try {
        vector<int> vec = {1, 2, 3};
        int value = vec.at(10);  // Will throw out_of_range
    } catch (out_of_range& e) {
        cout << "   Caught: " << e.what() << endl;
    }
    cout << endl;
    
    // 5. overflow_error - Arithmetic overflow
    cout << "5. overflow_error:" << endl;
    try {
        throw overflow_error("Arithmetic overflow occurred");
    } catch (overflow_error& e) {
        cout << "   Caught: " << e.what() << endl;
    }
    cout << endl;
    
    // 6. bad_alloc - Memory allocation failure
    cout << "6. bad_alloc (simulated):" << endl;
    try {
        // In real code: int* huge = new int[999999999999];
        throw bad_alloc();
    } catch (bad_alloc& e) {
        cout << "   Caught: Memory allocation failed" << endl;
    }
    cout << endl;
}

// ==============================================================================
// SECTION 4: THROWING EXCEPTIONS
// ==============================================================================
/*
 * THROWING EXCEPTIONS:
 * 
 * Syntax: throw exceptionObject;
 * 
 * You can throw:
 * - Standard exception objects
 * - Custom exception objects
 * - Built-in types (int, string, etc.)
 * 
 * Best practice: Throw by value, catch by reference
 * - throw SomeException("message");  (by value)
 * - catch (SomeException& e)         (by reference)
 * 
 * Why catch by reference?
 * - Avoids copying (more efficient)
 * - Preserves polymorphism
 * - Prevents object slicing
 */

// Function that throws exception
double divide(double numerator, double denominator) {
    if (denominator == 0) {
        throw invalid_argument("Division by zero!");
    }
    return numerator / denominator;
}

// Function that validates age
void setAge(int age) {
    if (age < 0) {
        throw invalid_argument("Age cannot be negative");
    }
    if (age > 150) {
        throw invalid_argument("Age is unrealistic");
    }
    cout << "   Age set to: " << age << endl;
}

// Function that checks array index
int getElement(const vector<int>& vec, size_t index) {
    if (index >= vec.size()) {
        throw out_of_range("Index out of bounds");
    }
    return vec[index];
}

void throwingExceptions() {
    cout << "=== THROWING EXCEPTIONS ===" << endl << endl;
    
    // Example 1: Division by zero
    cout << "1. Division Function:" << endl;
    try {
        double result = divide(10, 2);
        cout << "   10 / 2 = " << result << endl;
        
        result = divide(10, 0);  // This will throw
        cout << "   This won't print" << endl;
    } catch (invalid_argument& e) {
        cout << "   Error: " << e.what() << endl;
    }
    cout << endl;
    
    // Example 2: Age validation
    cout << "2. Age Validation:" << endl;
    try {
        setAge(25);
        setAge(-5);  // This will throw
    } catch (invalid_argument& e) {
        cout << "   Error: " << e.what() << endl;
    }
    cout << endl;
    
    // Example 3: Array bounds checking
    cout << "3. Array Bounds Checking:" << endl;
    vector<int> numbers = {10, 20, 30, 40, 50};
    try {
        cout << "   Element at index 2: " << getElement(numbers, 2) << endl;
        cout << "   Element at index 10: " << getElement(numbers, 10) << endl;
    } catch (out_of_range& e) {
        cout << "   Error: " << e.what() << endl;
    }
    cout << endl;
}

// ==============================================================================
// SECTION 5: MULTIPLE CATCH BLOCKS
// ==============================================================================
/*
 * MULTIPLE CATCH BLOCKS:
 * 
 * You can have multiple catch blocks to handle different exception types.
 * 
 * Syntax:
 *   try {
 *       // code
 *   } catch (Type1& e) {
 *       // handle Type1
 *   } catch (Type2& e) {
 *       // handle Type2
 *   } catch (...) {
 *       // catch all others
 *   }
 * 
 * Important:
 * - Catch blocks are checked in order
 * - More specific exceptions should come first
 * - catch(...) catches ANY exception (use as last resort)
 */

void performOperation(int operation) {
    if (operation == 1) {
        throw invalid_argument("Invalid argument error");
    } else if (operation == 2) {
        throw out_of_range("Out of range error");
    } else if (operation == 3) {
        throw runtime_error("Runtime error");
    } else if (operation == 4) {
        throw 42;  // Throwing an int
    }
}

void multipleCatchBlocks() {
    cout << "=== MULTIPLE CATCH BLOCKS ===" << endl << endl;
    
    // Try each operation
    for (int i = 1; i <= 5; i++) {
        cout << "Operation " << i << ":" << endl;
        try {
            performOperation(i);
            cout << "   No exception" << endl;
        } catch (invalid_argument& e) {
            cout << "   Caught invalid_argument: " << e.what() << endl;
        } catch (out_of_range& e) {
            cout << "   Caught out_of_range: " << e.what() << endl;
        } catch (runtime_error& e) {
            cout << "   Caught runtime_error: " << e.what() << endl;
        } catch (int value) {
            cout << "   Caught integer: " << value << endl;
        } catch (...) {
            cout << "   Caught unknown exception" << endl;
        }
        cout << endl;
    }
}

// ==============================================================================
// SECTION 6: CATCH-ALL HANDLER
// ==============================================================================
/*
 * CATCH-ALL HANDLER: catch(...)
 * 
 * Catches ANY type of exception.
 * 
 * Use cases:
 * - Cleanup operations
 * - Logging unknown errors
 * - Safety net at top level
 * 
 * Limitations:
 * - Can't access exception information
 * - Can't determine what was thrown
 * 
 * Best practice: Use specific catches first, catch-all last
 */

void catchAllHandler() {
    cout << "=== CATCH-ALL HANDLER ===" << endl << endl;
    
    // Example 1: Catching specific and general
    cout << "1. Specific + Catch-All:" << endl;
    try {
        throw string("Unknown error type");
    } catch (runtime_error& e) {
        cout << "   Caught runtime_error" << endl;
    } catch (logic_error& e) {
        cout << "   Caught logic_error" << endl;
    } catch (...) {
        cout << "   Caught unknown exception (catch-all)" << endl;
    }
    cout << endl;
    
    // Example 2: Catch-all for cleanup
    cout << "2. Cleanup with Catch-All:" << endl;
    int* ptr = nullptr;
    try {
        ptr = new int[100];
        cout << "   Memory allocated" << endl;
        throw runtime_error("Something went wrong");
    } catch (runtime_error& e) {
        cout << "   Error: " << e.what() << endl;
        delete[] ptr;  // Cleanup
        cout << "   Memory freed" << endl;
    } catch (...) {
        cout << "   Unknown error occurred" << endl;
        delete[] ptr;  // Cleanup for any other exception
    }
    cout << endl;
}

// ==============================================================================
// SECTION 7: EXCEPTION PROPAGATION
// ==============================================================================
/*
 * EXCEPTION PROPAGATION:
 * 
 * If an exception is not caught in a function, it propagates up
 * the call stack until it finds a matching catch block.
 * 
 * Flow:
 * 1. Exception thrown in function C
 * 2. No catch in C, propagate to B
 * 3. No catch in B, propagate to A
 * 4. Catch in A handles it
 * 
 * If never caught: Program terminates (calls std::terminate())
 */

void functionC() {
    cout << "   functionC: Throwing exception" << endl;
    throw runtime_error("Error from functionC");
}

void functionB() {
    cout << "   functionB: Calling functionC" << endl;
    functionC();  // Exception propagates from here
    cout << "   functionB: This won't execute" << endl;
}

void functionA() {
    cout << "   functionA: Calling functionB" << endl;
    try {
        functionB();
    } catch (runtime_error& e) {
        cout << "   functionA: Caught exception: " << e.what() << endl;
    }
    cout << "   functionA: Continuing execution" << endl;
}

void exceptionPropagation() {
    cout << "=== EXCEPTION PROPAGATION ===" << endl << endl;
    
    cout << "Call stack: A -> B -> C" << endl;
    cout << "Exception thrown in C, caught in A" << endl;
    cout << endl;
    functionA();
    cout << endl;
}

// ==============================================================================
// SECTION 8: RETHROWING EXCEPTIONS
// ==============================================================================
/*
 * RETHROWING EXCEPTIONS:
 * 
 * Sometimes you want to:
 * 1. Catch an exception
 * 2. Do some cleanup or logging
 * 3. Rethrow it for higher level to handle
 * 
 * Syntax: throw; (without argument)
 * 
 * This rethrows the currently caught exception.
 */

void processData(int value) {
    if (value < 0) {
        throw invalid_argument("Value must be non-negative");
    }
    cout << "   Processing value: " << value << endl;
}

void intermediateFunction(int value) {
    try {
        processData(value);
    } catch (invalid_argument& e) {
        cout << "   intermediateFunction: Caught exception" << endl;
        cout << "   intermediateFunction: Doing cleanup..." << endl;
        throw;  // Rethrow the exception
    }
}

void rethrowingExceptions() {
    cout << "=== RETHROWING EXCEPTIONS ===" << endl << endl;
    
    try {
        intermediateFunction(-5);
    } catch (invalid_argument& e) {
        cout << "   Main: Caught rethrown exception: " << e.what() << endl;
    }
    cout << endl;
}

// ==============================================================================
// SECTION 9: EXCEPTION SAFETY BASICS
// ==============================================================================
/*
 * EXCEPTION SAFETY LEVELS:
 * 
 * 1. No-throw guarantee: Function never throws exceptions
 * 2. Strong guarantee: Operation succeeds or has no effect (atomic)
 * 3. Basic guarantee: No resource leaks, object in valid state
 * 4. No guarantee: Anything can happen (BAD!)
 * 
 * Best practices:
 * - Clean up resources in catch blocks
 * - Use RAII (Resource Acquisition Is Initialization)
 * - Prefer smart pointers over raw pointers
 * - Be aware of what can throw
 */

void exceptionSafetyBasics() {
    cout << "=== EXCEPTION SAFETY BASICS ===" << endl << endl;
    
    // Example 1: Resource leak (BAD!)
    cout << "1. Resource Leak Example (DON'T DO THIS):" << endl;
    try {
        int* data = new int[100];
        cout << "   Memory allocated" << endl;
        // throw runtime_error("Error!");  // Memory leaked!
        delete[] data;
        cout << "   Memory freed" << endl;
    } catch (runtime_error& e) {
        cout << "   Error: " << e.what() << endl;
        // data is not accessible here - MEMORY LEAK!
    }
    cout << endl;
    
    // Example 2: Exception-safe (GOOD!)
    cout << "2. Exception-Safe Example (DO THIS):" << endl;
    int* data = nullptr;
    try {
        data = new int[100];
        cout << "   Memory allocated" << endl;
        throw runtime_error("Error!");
    } catch (runtime_error& e) {
        cout << "   Error: " << e.what() << endl;
        delete[] data;  // Cleanup in catch block
        cout << "   Memory freed (no leak!)" << endl;
    }
    cout << endl;
}

// ==============================================================================
// SECTION 10: WHEN TO USE EXCEPTIONS
// ==============================================================================
/*
 * WHEN TO USE EXCEPTIONS:
 * 
 * ✓ Good use cases:
 * - Error conditions that are truly exceptional
 * - Errors that can't be handled locally
 * - Constructor failures (can't return error code)
 * - Errors in deeply nested calls
 * - Separating error handling from normal logic
 * 
 * ✗ Bad use cases:
 * - Normal control flow (if-else is better)
 * - Expected conditions (like EOF)
 * - Performance-critical paths
 * - Simple validation (return bool is better)
 * - Very frequent errors
 */

void whenToUseExceptions() {
    cout << "=== WHEN TO USE EXCEPTIONS ===" << endl << endl;
    
    cout << "GOOD Use Cases:" << endl;
    cout << "   ✓ File not found (unexpected)" << endl;
    cout << "   ✓ Network connection failed" << endl;
    cout << "   ✓ Memory allocation failed" << endl;
    cout << "   ✓ Invalid configuration data" << endl;
    cout << "   ✓ Constructor initialization failure" << endl;
    cout << endl;
    
    cout << "BAD Use Cases:" << endl;
    cout << "   ✗ User input validation (use return codes)" << endl;
    cout << "   ✗ End of file reached (expected)" << endl;
    cout << "   ✗ Item not in cache (common)" << endl;
    cout << "   ✗ Control flow in loops" << endl;
    cout << "   ✗ Performance-critical code" << endl;
    cout << endl;
    
    cout << "Remember:" << endl;
    cout << "   - Exceptions are for EXCEPTIONAL situations" << endl;
    cout << "   - They have performance overhead" << endl;
    cout << "   - Use them wisely, not as primary control flow" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 11: PRACTICAL EXAMPLES
// ==============================================================================
/*
 * PRACTICAL EXAMPLES:
 * 
 * Real-world scenarios where exception handling is useful.
 */

// Example: Safe array access
class SafeArray {
private:
    int* data;
    size_t size;
    
public:
    SafeArray(size_t s) : size(s), data(new int[s]) {
        for (size_t i = 0; i < size; i++) {
            data[i] = 0;
        }
    }
    
    ~SafeArray() {
        delete[] data;
    }
    
    int& at(size_t index) {
        if (index >= size) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }
    
    size_t getSize() const { return size; }
};

// Example: Calculator with exception handling
double calculator(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                throw invalid_argument("Division by zero");
            }
            return a / b;
        default:
            throw invalid_argument("Invalid operator");
    }
}

void practicalExamples() {
    cout << "=== PRACTICAL EXAMPLES ===" << endl << endl;
    
    // Example 1: Safe array
    cout << "1. Safe Array Class:" << endl;
    SafeArray arr(5);
    try {
        arr.at(2) = 100;
        cout << "   Set arr[2] = 100" << endl;
        cout << "   arr[2] = " << arr.at(2) << endl;
        
        arr.at(10) = 200;  // This will throw
    } catch (out_of_range& e) {
        cout << "   Error: " << e.what() << endl;
    }
    cout << endl;
    
    // Example 2: Calculator
    cout << "2. Calculator with Exception Handling:" << endl;
    try {
        cout << "   10 + 5 = " << calculator(10, 5, '+') << endl;
        cout << "   10 / 2 = " << calculator(10, 2, '/') << endl;
        cout << "   10 / 0 = " << calculator(10, 0, '/') << endl;
    } catch (invalid_argument& e) {
        cout << "   Error: " << e.what() << endl;
    }
    cout << endl;
}

// ==============================================================================
// SECTION 12: BEST PRACTICES SUMMARY
// ==============================================================================
/*
 * EXCEPTION HANDLING BEST PRACTICES:
 * 
 * 1. Throw by value, catch by reference
 * 2. Use standard exception types when possible
 * 3. Provide meaningful error messages
 * 4. Catch specific exceptions first
 * 5. Use catch-all (...) only as last resort
 * 6. Don't throw in destructors
 * 7. Clean up resources in catch blocks
 * 8. Document what exceptions functions can throw
 * 9. Use exceptions for exceptional cases only
 * 10. Prefer RAII over manual cleanup
 */

void bestPracticesSummary() {
    cout << "=== EXCEPTION HANDLING BEST PRACTICES ===" << endl << endl;
    
    cout << "DO:" << endl;
    cout << "   ✓ throw by value: throw runtime_error(\"msg\");" << endl;
    cout << "   ✓ catch by reference: catch (exception& e)" << endl;
    cout << "   ✓ Use standard exceptions when appropriate" << endl;
    cout << "   ✓ Provide clear error messages" << endl;
    cout << "   ✓ Clean up resources" << endl;
    cout << "   ✓ Document exceptions in comments" << endl;
    cout << endl;
    
    cout << "DON'T:" << endl;
    cout << "   ✗ catch by value (causes slicing)" << endl;
    cout << "   ✗ Use exceptions for control flow" << endl;
    cout << "   ✗ Throw in destructors" << endl;
    cout << "   ✗ Catch and ignore without good reason" << endl;
    cout << "   ✗ Throw built-in types (int, char, etc.)" << endl;
    cout << "   ✗ Let resources leak" << endl;
    cout << endl;
    
    cout << "Remember:" << endl;
    cout << "   - Exceptions are for EXCEPTIONAL situations" << endl;
    cout << "   - They separate error handling from normal code" << endl;
    cout << "   - They can't be ignored (unlike return codes)" << endl;
    cout << "   - They provide clear error information" << endl;
    cout << endl;
}

// ==============================================================================
// MAIN FUNCTION - RUNS ALL EXAMPLES
// ==============================================================================

int main() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║      EXCEPTION HANDLING BEGINNER TUTORIAL - C++            ║" << endl;
    cout << "║                                                            ║" << endl;
    cout << "║  Learn exception handling fundamentals step by step       ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    cout << "\n";
    
    whatAreExceptions();
    basicTryCatchSyntax();
    standardExceptionTypes();
    throwingExceptions();
    multipleCatchBlocks();
    catchAllHandler();
    exceptionPropagation();
    rethrowingExceptions();
    exceptionSafetyBasics();
    whenToUseExceptions();
    practicalExamples();
    bestPracticesSummary();
    
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║  End of Exception Handling Beginner Tutorial               ║" << endl;
    cout << "║  Next: Move on to exception_intermediate.cpp               ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    
    return 0;
}

