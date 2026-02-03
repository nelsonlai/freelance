/*
 * UNION BEGINNER EXAMPLES
 * 
 * This file demonstrates basic union concepts in C++:
 * - Basic union declaration and usage
 * - Memory sharing between union members
 * - Union size and memory layout
 * - Tagged unions for type safety
 * - Different data type representations
 * 
 * Learning Objectives:
 * - Understand what unions are and how they work
 * - Learn about memory sharing in unions
 * - Master union size calculation
 * - Understand tagged unions for type safety
 * - Learn when and why to use unions
 * 
 * Prerequisites:
 * - Basic C++ knowledge
 * - Understanding of data types and memory
 * - Familiarity with structs and enums
 */

#include <iostream>  // For input/output operations (cout, endl)
#include <string>    // For string data type
using namespace std; // Using standard namespace (for beginners)

/*
 * BASIC UNION DECLARATION
 * 
 * A union is a special data type that allows different data types to be stored
 * in the same memory location. All members share the same memory space.
 * 
 * Key Points:
 * - All members share the same memory location
 * - Only one member can be active at a time
 * - Union size equals the size of the largest member
 * - Changing one member affects all other members
 * - Useful for memory optimization and type punning
 */
union Number {
    int integer;    // 4 bytes (typically)
    float decimal;  // 4 bytes (typically)
    char character; // 1 byte
    // Total union size = 4 bytes (size of largest member)
};

/*
 * UNION FOR DIFFERENT DATA REPRESENTATIONS
 * 
 * This union demonstrates how different data types can share memory.
 * It's useful when you need to interpret the same memory in different ways.
 * 
 * Key Points:
 * - All members occupy the same memory space
 * - Accessing inactive members results in undefined behavior
 * - Useful for data conversion and type punning
 * - Memory layout depends on system architecture
 */
union Data {
    int intValue;     // 4 bytes - integer representation
    float floatValue; // 4 bytes - floating-point representation
    double doubleValue; // 8 bytes - double precision representation
    char charValue;   // 1 byte - character representation
    // Total union size = 8 bytes (size of double)
};

/*
 * TAGGED UNION (DISCRIMINATED UNION)
 * 
 * A tagged union combines a union with a tag (enum) to keep track of
 * which member is currently active. This provides type safety.
 * 
 * Key Points:
 * - The tag indicates which union member is active
 * - Prevents undefined behavior from accessing inactive members
 * - More memory overhead but much safer
 * - Common pattern in systems programming
 */
struct Value {
    // Tag to indicate which union member is active
    enum Type { INT, FLOAT, CHAR } type;
    
    // Union containing the actual data
    union {
        int intVal;     // Integer value when type == INT
        float floatVal; // Float value when type == FLOAT
        char charVal;   // Character value when type == CHAR
    } data;
};

/*
 * HELPER FUNCTION: PRINT UNION DATA BASED ON TYPE
 * 
 * This function safely accesses union data by checking the tag first.
 * This prevents undefined behavior from accessing inactive members.
 * 
 * @param v The Value struct containing the tagged union
 */
void printValue(const Value& v) {
    switch (v.type) {
        case Value::INT:    // If the active member is int
            cout << "Integer value: " << v.data.intVal << endl;
            break;
        case Value::FLOAT:  // If the active member is float
            cout << "Float value: " << v.data.floatVal << endl;
            break;
        case Value::CHAR:   // If the active member is char
            cout << "Character value: " << v.data.charVal << endl;
            break;
    }
}

/*
 * MAIN FUNCTION
 * 
 * This function demonstrates various ways to use unions in C++.
 * It shows memory sharing, size calculation, type safety with tagged unions,
 * and practical applications of unions.
 */
int main() {
    // Display program header
    cout << "=== UNION BEGINNER EXAMPLES ===" << endl << endl;
    
    /*
     * EXAMPLE 1: BASIC UNION USAGE
     * 
     * This demonstrates the fundamental concept of unions:
     * - All members share the same memory location
     * - Only one member can be active at a time
     * - Changing one member affects all others
     * - Accessing inactive members gives undefined behavior
     */
    cout << "1. Basic Union Usage:" << endl;
    
    // Create a Number union instance
    Number num;
    
    // Store an integer value in the union
    num.integer = 42;
    cout << "Stored integer: " << num.integer << endl;
    
    // Access the same memory as different types
    // WARNING: This is undefined behavior! We're accessing inactive members
    cout << "Same memory as float: " << num.decimal << endl;
    cout << "Same memory as char: " << (int)num.character << endl;
    cout << endl;
    
    // Now store a float value in the union
    num.decimal = 3.14f;
    cout << "Stored float: " << num.decimal << endl;
    
    // Access the same memory as different types
    // WARNING: This is undefined behavior! We're accessing inactive members
    cout << "Same memory as integer: " << num.integer << endl;
    cout << "Same memory as char: " << (int)num.character << endl;
    cout << endl;
    
    /*
     * EXAMPLE 2: UNION SIZE DEMONSTRATION
     * 
     * This demonstrates how union size is calculated:
     * - Union size equals the size of the largest member
     * - All members share the same memory space
     * - This is different from structs where members are stored sequentially
     */
    cout << "2. Union Size Demonstration:" << endl;
    
    // Display the size of our Number union
    cout << "Size of Number union: " << sizeof(Number) << " bytes" << endl;
    
    // Display sizes of individual data types
    cout << "Size of int: " << sizeof(int) << " bytes" << endl;
    cout << "Size of float: " << sizeof(float) << " bytes" << endl;
    cout << "Size of char: " << sizeof(char) << " bytes" << endl;
    
    // Explain the union size rule
    cout << "Union size = size of largest member" << endl;
    cout << endl;
    
    /*
     * EXAMPLE 3: TAGGED UNION USAGE (TYPE SAFE)
     * 
     * This demonstrates how to use unions safely with tags:
     * - The tag indicates which member is active
     * - We check the tag before accessing members
     * - This prevents undefined behavior
     * - More memory overhead but much safer
     */
    cout << "3. Tagged Union Usage:" << endl;
    
    // Create a Value struct with integer data
    Value val1;
    val1.type = Value::INT;        // Set the tag to indicate integer is active
    val1.data.intVal = 100;        // Store integer value
    printValue(val1);              // Safely print the value
    
    // Create a Value struct with float data
    Value val2;
    val2.type = Value::FLOAT;      // Set the tag to indicate float is active
    val2.data.floatVal = 2.718f;   // Store float value (e, Euler's number)
    printValue(val2);              // Safely print the value
    
    // Create a Value struct with character data
    Value val3;
    val3.type = Value::CHAR;       // Set the tag to indicate char is active
    val3.data.charVal = 'A';       // Store character value
    printValue(val3);              // Safely print the value
    cout << endl;
    
    /*
     * EXAMPLE 4: UNION WITH DIFFERENT DATA TYPES
     * 
     * This demonstrates how unions can be used to interpret
     * the same memory in different ways:
     * - Useful for data conversion
     * - Can be used for type punning (with caution)
     * - Shows how different types view the same memory
     */
    cout << "4. Union with Different Data Types:" << endl;
    
    // Create a Data union instance
    Data data;
    
    // Store an integer value
    data.intValue = 12345;
    cout << "As integer: " << data.intValue << endl;
    
    // Interpret the same memory as different types
    // WARNING: This is undefined behavior! We're accessing inactive members
    cout << "As float: " << data.floatValue << endl;
    cout << "As double: " << data.doubleValue << endl;
    cout << "As char: " << (int)data.charValue << endl;
    cout << endl;
    
    // Now store a float value
    data.floatValue = 3.14159f;
    cout << "As integer: " << data.intValue << endl;
    cout << "As float: " << data.floatValue << endl;
    cout << "As double: " << data.doubleValue << endl;
    cout << "As char: " << (int)data.charValue << endl;
    cout << endl;
    
    /*
     * EXAMPLE 5: MEMORY SHARING DEMONSTRATION
     * 
     * This demonstrates how unions share memory by showing
     * how the same memory can be interpreted as different data types:
     * - We store a multi-byte integer
     * - We extract individual bytes as characters
     * - This shows the byte-level memory layout
     */
    cout << "5. Memory Sharing Demonstration:" << endl;
    
    // Create a Number union for testing
    Number test;
    
    // Store a multi-byte integer (0x41424344 = 'ABCD' in ASCII)
    test.integer = 0x41424344;
    
    cout << "Stored as integer: " << test.integer << endl;
    cout << "As characters: ";
    
    // Extract individual bytes and convert to characters
    // This shows how the same memory is interpreted differently
    cout << (char)(test.integer & 0xFF) << " ";           // First byte (D)
    cout << (char)((test.integer >> 8) & 0xFF) << " ";    // Second byte (C)
    cout << (char)((test.integer >> 16) & 0xFF) << " ";   // Third byte (B)
    cout << (char)((test.integer >> 24) & 0xFF) << endl;  // Fourth byte (A)
    
    // Return 0 to indicate successful program execution
    return 0;
}
