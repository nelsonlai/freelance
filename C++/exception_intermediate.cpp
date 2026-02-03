/*
 * EXCEPTION HANDLING INTERMEDIATE EXAMPLES
 * 
 * This file demonstrates intermediate exception handling concepts:
 * - Custom exception classes
 * - Exception hierarchies
 * - Exception specifications (noexcept)
 * - Stack unwinding
 * - RAII and exception safety
 * - Exception in constructors and destructors
 * - std::exception_ptr
 * - Nested exceptions
 * - Exception-safe containers
 * 
 * Learning Objectives:
 * - Create custom exception classes
 * - Understand stack unwinding mechanism
 * - Master noexcept specification
 * - Write exception-safe code with RAII
 * - Handle exceptions in special member functions
 * - Use advanced exception features
 * 
 * Prerequisites:
 * - Completed exception_beginner.cpp
 * - Understanding of C++ classes and inheritance
 * - Familiarity with destructors
 * - Understanding of RAII concept
 * 
 * Key Topics Covered:
 * - Custom exceptions
 * - Exception hierarchies
 * - noexcept specification
 * - Stack unwinding
 * - RAII pattern
 * - Exception safety guarantees
 */

#include <iostream>
#include <string>
#include <stdexcept>
#include <memory>
#include <vector>
#include <exception>
#include <sstream>
using namespace std;

// ==============================================================================
// SECTION 1: CUSTOM EXCEPTION CLASSES
// ==============================================================================
/*
 * CUSTOM EXCEPTION CLASSES:
 * 
 * Why create custom exceptions?
 * - Provide domain-specific error information
 * - Include additional error context
 * - Enable specific exception handling
 * - Better error reporting
 * 
 * Best practices:
 * - Inherit from std::exception or its derivatives
 * - Override what() method
 * - Make copy constructor noexcept
 * - Include relevant error information
 */

// Simple custom exception
class MathError : public exception {
private:
    string message;
    
public:
    MathError(const string& msg) : message(msg) {}
    
    // Override what() method
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Custom exception with error code
class DatabaseError : public runtime_error {
private:
    int errorCode;
    string query;
    
public:
    DatabaseError(const string& msg, int code, const string& q)
        : runtime_error(msg), errorCode(code), query(q) {}
    
    int getErrorCode() const { return errorCode; }
    string getQuery() const { return query; }
};

// Custom exception with detailed information
class FileError : public runtime_error {
private:
    string filename;
    int lineNumber;
    
public:
    FileError(const string& msg, const string& fname, int line = 0)
        : runtime_error(msg), filename(fname), lineNumber(line) {}
    
    string getFilename() const { return filename; }
    int getLineNumber() const { return lineNumber; }
    
    string getFullMessage() const {
        ostringstream oss;
        oss << what() << " (File: " << filename;
        if (lineNumber > 0) {
            oss << ", Line: " << lineNumber;
        }
        oss << ")";
        return oss.str();
    }
};

void customExceptionClasses() {
    cout << "=== CUSTOM EXCEPTION CLASSES ===" << endl << endl;
    
    // Example 1: Simple custom exception
    cout << "1. Simple Custom Exception:" << endl;
    try {
        throw MathError("Invalid mathematical operation");
    } catch (MathError& e) {
        cout << "   Caught MathError: " << e.what() << endl;
    }
    cout << endl;
    
    // Example 2: Exception with error code
    cout << "2. Exception with Error Code:" << endl;
    try {
        throw DatabaseError("Connection failed", 1045, "SELECT * FROM users");
    } catch (DatabaseError& e) {
        cout << "   Error: " << e.what() << endl;
        cout << "   Code: " << e.getErrorCode() << endl;
        cout << "   Query: " << e.getQuery() << endl;
    }
    cout << endl;
    
    // Example 3: Exception with detailed information
    cout << "3. Detailed File Exception:" << endl;
    try {
        throw FileError("Failed to parse configuration", "config.txt", 42);
    } catch (FileError& e) {
        cout << "   " << e.getFullMessage() << endl;
    }
    cout << endl;
}

// ==============================================================================
// SECTION 2: EXCEPTION HIERARCHIES
// ==============================================================================
/*
 * EXCEPTION HIERARCHIES:
 * 
 * Creating a hierarchy allows:
 * - Catch general or specific exceptions
 * - Group related errors
 * - Polymorphic exception handling
 * 
 * Design principles:
 * - Base class for general category
 * - Derived classes for specific errors
 * - Use public inheritance
 * - Override what() appropriately
 */

// Base exception for network errors
class NetworkError : public runtime_error {
public:
    NetworkError(const string& msg) : runtime_error(msg) {}
};

// Specific network errors
class ConnectionError : public NetworkError {
private:
    string host;
    int port;
    
public:
    ConnectionError(const string& h, int p)
        : NetworkError("Connection failed"), host(h), port(p) {}
    
    string getHost() const { return host; }
    int getPort() const { return port; }
};

class TimeoutError : public NetworkError {
private:
    int timeoutSeconds;
    
public:
    TimeoutError(int timeout)
        : NetworkError("Operation timed out"), timeoutSeconds(timeout) {}
    
    int getTimeout() const { return timeoutSeconds; }
};

class ProtocolError : public NetworkError {
private:
    string expectedProtocol;
    string receivedProtocol;
    
public:
    ProtocolError(const string& expected, const string& received)
        : NetworkError("Protocol mismatch"),
          expectedProtocol(expected), receivedProtocol(received) {}
    
    string getExpected() const { return expectedProtocol; }
    string getReceived() const { return receivedProtocol; }
};

void simulateNetworkOperation(int operation) {
    switch (operation) {
        case 1:
            throw ConnectionError("example.com", 80);
        case 2:
            throw TimeoutError(30);
        case 3:
            throw ProtocolError("HTTP/1.1", "HTTP/0.9");
    }
}

void exceptionHierarchies() {
    cout << "=== EXCEPTION HIERARCHIES ===" << endl << endl;
    
    // Example 1: Catching specific exceptions
    cout << "1. Catching Specific Exceptions:" << endl;
    for (int i = 1; i <= 3; i++) {
        try {
            simulateNetworkOperation(i);
        } catch (ConnectionError& e) {
            cout << "   Connection to " << e.getHost() << ":" 
                 << e.getPort() << " failed" << endl;
        } catch (TimeoutError& e) {
            cout << "   Timeout after " << e.getTimeout() << " seconds" << endl;
        } catch (ProtocolError& e) {
            cout << "   Expected " << e.getExpected() 
                 << ", got " << e.getReceived() << endl;
        }
    }
    cout << endl;
    
    // Example 2: Catching base class (polymorphic)
    cout << "2. Catching Base Class (Polymorphic):" << endl;
    for (int i = 1; i <= 3; i++) {
        try {
            simulateNetworkOperation(i);
        } catch (NetworkError& e) {
            cout << "   Network error: " << e.what() << endl;
        }
    }
    cout << endl;
}

// ==============================================================================
// SECTION 3: NOEXCEPT SPECIFICATION
// ==============================================================================
/*
 * NOEXCEPT SPECIFICATION (C++11):
 * 
 * Syntax: returnType functionName() noexcept;
 * 
 * Indicates that a function doesn't throw exceptions.
 * 
 * Benefits:
 * - Enables compiler optimizations
 * - Documents function guarantees
 * - Allows move operations in containers
 * - Required for certain standard library optimizations
 * 
 * If noexcept function throws: std::terminate() is called
 * 
 * Use for:
 * - Destructors (implicitly noexcept)
 * - Move constructors/operators
 * - Swap functions
 * - Simple getters
 */

class NoexceptDemo {
private:
    int value;
    
public:
    // Constructor (can throw)
    NoexceptDemo(int v) : value(v) {
        if (v < 0) {
            throw invalid_argument("Value must be non-negative");
        }
    }
    
    // Destructor (implicitly noexcept)
    ~NoexceptDemo() {
        // Should never throw!
    }
    
    // Getter (noexcept - simple operation)
    int getValue() const noexcept {
        return value;
    }
    
    // Setter (can throw)
    void setValue(int v) {
        if (v < 0) {
            throw invalid_argument("Value must be non-negative");
        }
        value = v;
    }
    
    // Move constructor (should be noexcept)
    NoexceptDemo(NoexceptDemo&& other) noexcept : value(other.value) {
        other.value = 0;
    }
    
    // Move assignment (should be noexcept)
    NoexceptDemo& operator=(NoexceptDemo&& other) noexcept {
        value = other.value;
        other.value = 0;
        return *this;
    }
    
    // Swap (should be noexcept)
    void swap(NoexceptDemo& other) noexcept {
        int temp = value;
        value = other.value;
        other.value = temp;
    }
};

// Conditional noexcept
template<typename T>
void swapValues(T& a, T& b) noexcept(noexcept(T(std::move(a)))) {
    T temp = std::move(a);
    a = std::move(b);
    b = std::move(temp);
}

void noexceptSpecification() {
    cout << "=== NOEXCEPT SPECIFICATION ===" << endl << endl;
    
    cout << "1. Noexcept Functions:" << endl;
    NoexceptDemo obj1(10);
    cout << "   getValue() (noexcept): " << obj1.getValue() << endl;
    cout << endl;
    
    cout << "2. Functions That Can Throw:" << endl;
    try {
        NoexceptDemo obj2(-5);  // Constructor can throw
    } catch (invalid_argument& e) {
        cout << "   Constructor threw: " << e.what() << endl;
    }
    cout << endl;
    
    cout << "3. Move Operations (noexcept):" << endl;
    NoexceptDemo obj3(20);
    NoexceptDemo obj4 = std::move(obj3);
    cout << "   Moved successfully (noexcept guarantee)" << endl;
    cout << endl;
    
    cout << "Why noexcept matters:" << endl;
    cout << "   ✓ Enables compiler optimizations" << endl;
    cout << "   ✓ Allows efficient move in containers" << endl;
    cout << "   ✓ Documents function guarantees" << endl;
    cout << "   ✓ Required for destructors" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 4: STACK UNWINDING
// ==============================================================================
/*
 * STACK UNWINDING:
 * 
 * When an exception is thrown:
 * 1. Program searches for matching catch block
 * 2. Destroys local objects in reverse order of creation
 * 3. Moves up the call stack
 * 4. Repeats until catch block found or main() exited
 * 
 * Important:
 * - Destructors are called during unwinding
 * - This is why destructors shouldn't throw
 * - RAII objects clean up automatically
 */

class ResourceTracker {
private:
    string name;
    
public:
    ResourceTracker(const string& n) : name(n) {
        cout << "   [" << name << "] Acquired" << endl;
    }
    
    ~ResourceTracker() {
        cout << "   [" << name << "] Released" << endl;
    }
};

void level3() {
    ResourceTracker r3("Level3-Resource");
    cout << "   Level3: About to throw" << endl;
    throw runtime_error("Error from level 3");
    cout << "   Level3: This won't execute" << endl;
}

void level2() {
    ResourceTracker r2("Level2-Resource");
    cout << "   Level2: Calling level3" << endl;
    level3();
    cout << "   Level2: This won't execute" << endl;
}

void level1() {
    ResourceTracker r1("Level1-Resource");
    cout << "   Level1: Calling level2" << endl;
    level2();
    cout << "   Level1: This won't execute" << endl;
}

void stackUnwinding() {
    cout << "=== STACK UNWINDING ===" << endl << endl;
    
    cout << "Demonstrating stack unwinding:" << endl;
    try {
        level1();
    } catch (runtime_error& e) {
        cout << "   Caught: " << e.what() << endl;
    }
    cout << endl;
    
    cout << "Notice:" << endl;
    cout << "   - Resources released in reverse order (LIFO)" << endl;
    cout << "   - Destructors called automatically" << endl;
    cout << "   - Stack unwound until catch block found" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 5: RAII AND EXCEPTION SAFETY
// ==============================================================================
/*
 * RAII (Resource Acquisition Is Initialization):
 * 
 * Pattern where resource lifetime is tied to object lifetime:
 * - Acquire resource in constructor
 * - Release resource in destructor
 * 
 * Benefits with exceptions:
 * - Automatic cleanup during stack unwinding
 * - Exception-safe by design
 * - No manual cleanup needed
 * 
 * Examples: unique_ptr, lock_guard, fstream, etc.
 */

class FileHandle {
private:
    string filename;
    bool isOpen;
    
public:
    FileHandle(const string& fname) : filename(fname), isOpen(false) {
        cout << "   Opening file: " << filename << endl;
        isOpen = true;
        // Simulate file opening
    }
    
    ~FileHandle() {
        if (isOpen) {
            cout << "   Closing file: " << filename << endl;
            isOpen = false;
        }
    }
    
    void write(const string& data) {
        if (!isOpen) {
            throw runtime_error("File not open");
        }
        cout << "   Writing: " << data << endl;
    }
    
    // Prevent copying
    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;
};

class DatabaseConnection {
private:
    string connectionString;
    bool connected;
    
public:
    DatabaseConnection(const string& connStr)
        : connectionString(connStr), connected(false) {
        cout << "   Connecting to database..." << endl;
        connected = true;
    }
    
    ~DatabaseConnection() {
        if (connected) {
            cout << "   Disconnecting from database..." << endl;
            connected = false;
        }
    }
    
    void query(const string& sql) {
        if (!connected) {
            throw runtime_error("Not connected");
        }
        cout << "   Executing: " << sql << endl;
    }
    
    // Prevent copying
    DatabaseConnection(const DatabaseConnection&) = delete;
    DatabaseConnection& operator=(const DatabaseConnection&) = delete;
};

void raiiAndExceptionSafety() {
    cout << "=== RAII AND EXCEPTION SAFETY ===" << endl << endl;
    
    // Example 1: Exception-safe file handling
    cout << "1. RAII File Handling:" << endl;
    try {
        FileHandle file("data.txt");
        file.write("Some data");
        throw runtime_error("Simulated error");
        file.write("This won't execute");
    } catch (runtime_error& e) {
        cout << "   Error: " << e.what() << endl;
    }
    cout << "   (File automatically closed)" << endl;
    cout << endl;
    
    // Example 2: Multiple RAII objects
    cout << "2. Multiple RAII Resources:" << endl;
    try {
        FileHandle file("log.txt");
        DatabaseConnection db("localhost:5432");
        
        file.write("Starting operation");
        db.query("SELECT * FROM users");
        
        throw runtime_error("Operation failed");
    } catch (runtime_error& e) {
        cout << "   Error: " << e.what() << endl;
    }
    cout << "   (All resources automatically cleaned up)" << endl;
    cout << endl;
    
    // Example 3: Using smart pointers (RAII)
    cout << "3. Smart Pointer RAII:" << endl;
    try {
        auto ptr = make_unique<int[]>(1000);
        cout << "   Memory allocated" << endl;
        throw runtime_error("Error!");
    } catch (runtime_error& e) {
        cout << "   Error: " << e.what() << endl;
    }
    cout << "   (Memory automatically freed)" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 6: EXCEPTIONS IN CONSTRUCTORS
// ==============================================================================
/*
 * EXCEPTIONS IN CONSTRUCTORS:
 * 
 * Constructors can and should throw exceptions:
 * - No return value to indicate error
 * - Exception is the proper way to signal failure
 * - Object is not created if constructor throws
 * 
 * Important:
 * - Destructor won't be called if constructor throws
 * - Clean up any acquired resources before throwing
 * - Use RAII for member objects (they're cleaned up automatically)
 */

class SafeResource {
private:
    int* data;
    size_t size;
    
public:
    SafeResource(size_t s) : data(nullptr), size(s) {
        cout << "   Constructor: Allocating " << size << " integers" << endl;
        
        if (size == 0) {
            throw invalid_argument("Size must be positive");
        }
        
        if (size > 1000000) {
            throw invalid_argument("Size too large");
        }
        
        data = new int[size];
        cout << "   Constructor: Allocation successful" << endl;
    }
    
    ~SafeResource() {
        cout << "   Destructor: Cleaning up" << endl;
        delete[] data;
    }
    
    // Prevent copying for simplicity
    SafeResource(const SafeResource&) = delete;
    SafeResource& operator=(const SafeResource&) = delete;
};

class CompositeResource {
private:
    unique_ptr<int[]> buffer1;  // RAII - automatic cleanup
    unique_ptr<int[]> buffer2;  // RAII - automatic cleanup
    
public:
    CompositeResource(size_t size1, size_t size2) {
        cout << "   Allocating buffer1" << endl;
        buffer1 = make_unique<int[]>(size1);
        
        cout << "   Allocating buffer2" << endl;
        buffer2 = make_unique<int[]>(size2);
        
        if (size1 > 100) {
            // buffer1 automatically cleaned up!
            throw runtime_error("Size1 too large");
        }
        
        cout << "   Constructor completed successfully" << endl;
    }
    
    ~CompositeResource() {
        cout << "   Destructor called" << endl;
        // Smart pointers clean up automatically
    }
};

void exceptionsInConstructors() {
    cout << "=== EXCEPTIONS IN CONSTRUCTORS ===" << endl << endl;
    
    // Example 1: Constructor throws
    cout << "1. Constructor Exception:" << endl;
    try {
        SafeResource res(0);  // Invalid size
    } catch (invalid_argument& e) {
        cout << "   Caught: " << e.what() << endl;
    }
    cout << endl;
    
    // Example 2: Successful construction
    cout << "2. Successful Construction:" << endl;
    try {
        SafeResource res(100);
        cout << "   Object created successfully" << endl;
    } catch (invalid_argument& e) {
        cout << "   Caught: " << e.what() << endl;
    }
    cout << endl;
    
    // Example 3: RAII members clean up automatically
    cout << "3. RAII Members Auto-Cleanup:" << endl;
    try {
        CompositeResource res(200, 50);  // Will throw
    } catch (runtime_error& e) {
        cout << "   Caught: " << e.what() << endl;
        cout << "   (RAII members automatically cleaned up)" << endl;
    }
    cout << endl;
}

// ==============================================================================
// SECTION 7: EXCEPTIONS IN DESTRUCTORS (DON'T!)
// ==============================================================================
/*
 * EXCEPTIONS IN DESTRUCTORS:
 * 
 * NEVER throw exceptions from destructors!
 * 
 * Why?
 * - Destructors called during stack unwinding
 * - If destructor throws during unwinding, std::terminate() called
 * - Program crashes
 * 
 * Rules:
 * - Destructors are implicitly noexcept
 * - Catch and handle all exceptions in destructors
 * - Log errors but don't throw
 */

class BadDestructor {
public:
    ~BadDestructor() {
        // NEVER DO THIS!
        // throw runtime_error("Error in destructor");
        cout << "   BadDestructor: Cleaned up safely" << endl;
    }
};

class GoodDestructor {
public:
    ~GoodDestructor() {
        try {
            // Some operation that might throw
            // if (someCondition) throw runtime_error("Error");
        } catch (...) {
            // Catch ALL exceptions in destructor
            cout << "   GoodDestructor: Caught exception, logged it" << endl;
            // Log the error, but DON'T rethrow
        }
        cout << "   GoodDestructor: Cleaned up safely" << endl;
    }
};

void exceptionsInDestructors() {
    cout << "=== EXCEPTIONS IN DESTRUCTORS ===" << endl << endl;
    
    cout << "Why destructors shouldn't throw:" << endl;
    cout << "   - Called during stack unwinding" << endl;
    cout << "   - Double exception = std::terminate()" << endl;
    cout << "   - Program crash" << endl;
    cout << endl;
    
    cout << "Demonstrating safe destructor:" << endl;
    try {
        GoodDestructor obj;
        throw runtime_error("Some error");
    } catch (runtime_error& e) {
        cout << "   Caught: " << e.what() << endl;
    }
    cout << "   (Destructor handled its own errors internally)" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 8: EXCEPTION SAFETY GUARANTEES
// ==============================================================================
/*
 * EXCEPTION SAFETY GUARANTEES:
 * 
 * 1. No-throw (no-fail) guarantee:
 *    - Function never throws
 *    - Mark with noexcept
 *    - Example: destructors, swap
 * 
 * 2. Strong guarantee (commit-or-rollback):
 *    - Operation completes successfully, or
 *    - State unchanged (as if operation never happened)
 *    - Example: vector::push_back (when possible)
 * 
 * 3. Basic guarantee:
 *    - No resource leaks
 *    - Object in valid state (may be modified)
 *    - Example: most operations
 * 
 * 4. No guarantee:
 *    - Resources may leak
 *    - Object in invalid state
 *    - DON'T DO THIS!
 */

class StrongGuaranteeVector {
private:
    vector<int> data;
    
public:
    // Strong guarantee: succeeds or no change
    void push_back_strong(int value) {
        vector<int> temp = data;  // Copy
        temp.push_back(value);     // Modify copy
        data = std::move(temp);    // Commit (no-throw move)
        // If push_back throws, original data unchanged
    }
    
    // Basic guarantee: no leak, but state may change
    void push_back_basic(int value) {
        data.push_back(value);
        // If this throws, some internal state may have changed
        // But no resources leaked
    }
    
    size_t size() const noexcept {
        return data.size();
    }
    
    void display() const {
        cout << "   Vector: ";
        for (int val : data) {
            cout << val << " ";
        }
        cout << endl;
    }
};

void exceptionSafetyGuarantees() {
    cout << "=== EXCEPTION SAFETY GUARANTEES ===" << endl << endl;
    
    cout << "1. No-throw Guarantee:" << endl;
    StrongGuaranteeVector vec;
    size_t s = vec.size();  // noexcept - will never throw
    cout << "   Size: " << s << " (noexcept operation)" << endl;
    cout << endl;
    
    cout << "2. Strong Guarantee:" << endl;
    vec.push_back_strong(10);
    vec.push_back_strong(20);
    cout << "   After strong push_back:" << endl;
    vec.display();
    cout << "   (If push_back threw, vector would be unchanged)" << endl;
    cout << endl;
    
    cout << "Exception Safety Levels:" << endl;
    cout << "   1. No-throw:  Never throws (noexcept)" << endl;
    cout << "   2. Strong:    Success or no change" << endl;
    cout << "   3. Basic:     No leaks, valid state" << endl;
    cout << "   4. None:      Avoid at all costs!" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 9: NESTED EXCEPTIONS (C++11)
// ==============================================================================
/*
 * NESTED EXCEPTIONS:
 * 
 * Allows capturing context while rethrowing:
 * - Catch exception at one level
 * - Add context
 * - Throw new exception with nested original
 * 
 * Functions:
 * - throw_with_nested() - throws with nested exception
 * - rethrow_if_nested() - rethrows nested exception
 * - nested_ptr() - gets nested exception
 */

void lowLevelFunction() {
    throw runtime_error("Low-level database error");
}

void midLevelFunction() {
    try {
        lowLevelFunction();
    } catch (const exception& e) {
        // Add context and rethrow with nested exception
        throw_with_nested(runtime_error("Mid-level: Failed to query database"));
    }
}

void printNestedException(const exception& e, int level = 0) {
    string indent(level * 2, ' ');
    cout << indent << "Exception: " << e.what() << endl;
    
    try {
        rethrow_if_nested(e);
    } catch (const exception& nested) {
        printNestedException(nested, level + 1);
    }
}

void nestedExceptions() {
    cout << "=== NESTED EXCEPTIONS ===" << endl << endl;
    
    cout << "Demonstrating nested exceptions:" << endl;
    try {
        midLevelFunction();
    } catch (const exception& e) {
        cout << "Caught exception chain:" << endl;
        printNestedException(e);
    }
    cout << endl;
    
    cout << "Benefits:" << endl;
    cout << "   ✓ Preserves original error" << endl;
    cout << "   ✓ Adds contextual information" << endl;
    cout << "   ✓ Full error trace available" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 10: BEST PRACTICES SUMMARY
// ==============================================================================

void bestPracticesSummary() {
    cout << "=== BEST PRACTICES SUMMARY ===" << endl << endl;
    
    cout << "Custom Exceptions:" << endl;
    cout << "   ✓ Inherit from std::exception" << endl;
    cout << "   ✓ Override what() as noexcept" << endl;
    cout << "   ✓ Include relevant context" << endl;
    cout << endl;
    
    cout << "Exception Safety:" << endl;
    cout << "   ✓ Use RAII for all resources" << endl;
    cout << "   ✓ Prefer strong guarantee when possible" << endl;
    cout << "   ✓ Ensure at least basic guarantee" << endl;
    cout << "   ✓ Mark non-throwing functions noexcept" << endl;
    cout << endl;
    
    cout << "Destructors:" << endl;
    cout << "   ✓ NEVER throw from destructors" << endl;
    cout << "   ✓ Catch all exceptions internally" << endl;
    cout << "   ✓ Destructors are implicitly noexcept" << endl;
    cout << endl;
    
    cout << "Constructors:" << endl;
    cout << "   ✓ CAN and SHOULD throw on failure" << endl;
    cout << "   ✓ Use RAII for member resources" << endl;
    cout << "   ✓ Clean up before throwing" << endl;
    cout << endl;
    
    cout << "General:" << endl;
    cout << "   ✓ Throw by value, catch by reference" << endl;
    cout << "   ✓ Use exception hierarchies" << endl;
    cout << "   ✓ Provide meaningful error messages" << endl;
    cout << "   ✓ Document exception guarantees" << endl;
    cout << endl;
}

// ==============================================================================
// MAIN FUNCTION - RUNS ALL EXAMPLES
// ==============================================================================

int main() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║    EXCEPTION HANDLING INTERMEDIATE TUTORIAL - C++          ║" << endl;
    cout << "║                                                            ║" << endl;
    cout << "║  Master advanced exception handling techniques             ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    cout << "\n";
    
    customExceptionClasses();
    exceptionHierarchies();
    noexceptSpecification();
    stackUnwinding();
    raiiAndExceptionSafety();
    exceptionsInConstructors();
    exceptionsInDestructors();
    exceptionSafetyGuarantees();
    nestedExceptions();
    bestPracticesSummary();
    
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║  End of Exception Handling Intermediate Tutorial           ║" << endl;
    cout << "║  Next: Move on to exception_advanced.cpp                   ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    
    return 0;
}

