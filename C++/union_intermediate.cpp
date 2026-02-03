/*
 * UNION INTERMEDIATE EXAMPLES
 * 
 * This file demonstrates intermediate union concepts including tagged unions, memory management, and type safety:
 * - Advanced concepts and techniques
 * - Real-world applications and patterns
 * - Best practices and optimization
 * - Complex scenarios and edge cases
 * 
 * Learning Objectives:
 * - Master advanced UNION concepts
 * - Understand professional coding patterns
 * - Learn optimization techniques
 * - Apply knowledge in complex scenarios
 * - Develop problem-solving skills
 * 
 * Prerequisites:
 * - Solid understanding of basic UNION concepts
 * - Familiarity with intermediate C++ features
 * - Understanding of memory management
 * - Knowledge of STL containers and algorithms
 * 
 * Key Topics Covered:
 * - Advanced syntax and features
 * - Performance optimization
 * - Error handling and safety
 * - Modern C++ practices
 * - Real-world applications
 */

#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <memory>
using namespace std;

// Tagged union with constructors and destructors
struct VariantValue {
    enum Type { INT, FLOAT, STRING, BOOL } type;
    
    union {
        int intVal;
        float floatVal;
        string* stringVal;  // Pointer for complex types
        bool boolVal;
    } data;
    
    // Constructor
    VariantValue(int val) : type(INT) {
        data.intVal = val;
    }
    
    VariantValue(float val) : type(FLOAT) {
        data.floatVal = val;
    }
    
    VariantValue(const string& val) : type(STRING) {
        data.stringVal = new string(val);
    }
    
    VariantValue(bool val) : type(BOOL) {
        data.boolVal = val;
    }
    
    // Copy constructor
    VariantValue(const VariantValue& other) : type(other.type) {
        switch (type) {
            case INT:
                data.intVal = other.data.intVal;
                break;
            case FLOAT:
                data.floatVal = other.data.floatVal;
                break;
            case STRING:
                data.stringVal = new string(*other.data.stringVal);
                break;
            case BOOL:
                data.boolVal = other.data.boolVal;
                break;
        }
    }
    
    // Assignment operator
    VariantValue& operator=(const VariantValue& other) {
        if (this != &other) {
            // Clean up current data
            if (type == STRING && data.stringVal) {
                delete data.stringVal;
            }
            
            type = other.type;
            switch (type) {
                case INT:
                    data.intVal = other.data.intVal;
                    break;
                case FLOAT:
                    data.floatVal = other.data.floatVal;
                    break;
                case STRING:
                    data.stringVal = new string(*other.data.stringVal);
                    break;
                case BOOL:
                    data.boolVal = other.data.boolVal;
                    break;
            }
        }
        return *this;
    }
    
    // Destructor
    ~VariantValue() {
        if (type == STRING && data.stringVal) {
            delete data.stringVal;
        }
    }
    
    // Get value as string
    string toString() const {
        switch (type) {
            case INT:
                return to_string(data.intVal);
            case FLOAT:
                return to_string(data.floatVal);
            case STRING:
                return *data.stringVal;
            case BOOL:
                return data.boolVal ? "true" : "false";
            default:
                return "unknown";
        }
    }
    
    // Get type name
    string getTypeName() const {
        switch (type) {
            case INT: return "int";
            case FLOAT: return "float";
            case STRING: return "string";
            case BOOL: return "bool";
            default: return "unknown";
        }
    }
};

// Union for different number representations
union NumberUnion {
    int32_t int32;
    uint32_t uint32;
    float float32;
    char bytes[4];
    
    // Constructor
    NumberUnion(int32_t val) : int32(val) {}
    NumberUnion(float val) : float32(val) {}
    
    // Display all representations
    void displayAll() const {
        cout << "int32: " << int32 << endl;
        cout << "uint32: " << uint32 << endl;
        cout << "float32: " << float32 << endl;
        cout << "bytes: ";
        for (int i = 0; i < 4; i++) {
            cout << static_cast<int>(bytes[i]) << " ";
        }
        cout << endl;
    }
};

// Union for memory-efficient storage
struct FlexibleArray {
    enum Type { INT_ARRAY, FLOAT_ARRAY, CHAR_ARRAY } type;
    size_t size;
    
    union {
        int* intData;
        float* floatData;
        char* charData;
    } data;
    
    FlexibleArray(Type t, size_t s) : type(t), size(s) {
        switch (type) {
            case INT_ARRAY:
                data.intData = new int[size];
                break;
            case FLOAT_ARRAY:
                data.floatData = new float[size];
                break;
            case CHAR_ARRAY:
                data.charData = new char[size];
                break;
        }
    }
    
    ~FlexibleArray() {
        switch (type) {
            case INT_ARRAY:
                delete[] data.intData;
                break;
            case FLOAT_ARRAY:
                delete[] data.floatData;
                break;
            case CHAR_ARRAY:
                delete[] data.charData;
                break;
        }
    }
    
    void display() const {
        cout << "Array type: " << (type == INT_ARRAY ? "int" : 
                                  type == FLOAT_ARRAY ? "float" : "char") << endl;
        cout << "Size: " << size << endl;
        cout << "Data: ";
        
        switch (type) {
            case INT_ARRAY:
                for (size_t i = 0; i < size; i++) {
                    cout << data.intData[i] << " ";
                }
                break;
            case FLOAT_ARRAY:
                for (size_t i = 0; i < size; i++) {
                    cout << data.floatData[i] << " ";
                }
                break;
            case CHAR_ARRAY:
                for (size_t i = 0; i < size; i++) {
                    cout << data.charData[i] << " ";
                }
                break;
        }
        cout << endl;
    }
};

// Union for type punning (advanced)
union TypePunning {
    double d;
    uint64_t i;
    char bytes[8];
    
    TypePunning(double val) : d(val) {}
    TypePunning(uint64_t val) : i(val) {}
    
    void displayBits() const {
        cout << "Double: " << d << endl;
        cout << "Uint64: " << i << endl;
        cout << "Binary: ";
        for (int i = 7; i >= 0; i--) {
            for (int j = 7; j >= 0; j--) {
                cout << ((bytes[i] >> j) & 1);
            }
            cout << " ";
        }
        cout << endl;
    }
};

// Modern C++17 variant (alternative to unions)
using ModernVariant = variant<int, float, string, bool>;

void printVariant(const ModernVariant& v) {
    visit([](const auto& value) {
        cout << "Value: " << value << " (type: " << typeid(value).name() << ")" << endl;
    }, v);
}

int main() {
    cout << "=== UNION INTERMEDIATE EXAMPLES ===" << endl << endl;
    
    // Example 1: Tagged union with constructors/destructors
    cout << "1. Tagged Union with Constructors/Destructors:" << endl;
    {
        VariantValue val1(42);
        VariantValue val2(3.14f);
        VariantValue val3("Hello World");
        VariantValue val4(true);
        
        cout << "val1: " << val1.toString() << " (type: " << val1.getTypeName() << ")" << endl;
        cout << "val2: " << val2.toString() << " (type: " << val2.getTypeName() << ")" << endl;
        cout << "val3: " << val3.toString() << " (type: " << val3.getTypeName() << ")" << endl;
        cout << "val4: " << val4.toString() << " (type: " << val4.getTypeName() << ")" << endl;
        
        // Copy constructor
        VariantValue val5 = val3;
        cout << "val5 (copy of val3): " << val5.toString() << endl;
    }  // Destructors called here
    cout << endl;
    
    // Example 2: Number representation union
    cout << "2. Number Representation Union:" << endl;
    NumberUnion num1(42);
    cout << "Number 42 in different representations:" << endl;
    num1.displayAll();
    cout << endl;
    
    NumberUnion num2(3.14159f);
    cout << "Float 3.14159 in different representations:" << endl;
    num2.displayAll();
    cout << endl;
    
    // Example 3: Flexible array union
    cout << "3. Flexible Array Union:" << endl;
    FlexibleArray intArray(FlexibleArray::INT_ARRAY, 5);
    FlexibleArray floatArray(FlexibleArray::FLOAT_ARRAY, 3);
    FlexibleArray charArray(FlexibleArray::CHAR_ARRAY, 4);
    
    // Initialize int array
    for (size_t i = 0; i < 5; i++) {
        intArray.data.intData[i] = static_cast<int>(i * 10);
    }
    
    // Initialize float array
    for (size_t i = 0; i < 3; i++) {
        floatArray.data.floatData[i] = static_cast<float>(i * 1.5);
    }
    
    // Initialize char array
    charArray.data.charData[0] = 'A';
    charArray.data.charData[1] = 'B';
    charArray.data.charData[2] = 'C';
    charArray.data.charData[3] = 'D';
    
    intArray.display();
    floatArray.display();
    charArray.display();
    cout << endl;
    
    // Example 4: Type punning
    cout << "4. Type Punning:" << endl;
    TypePunning tp1(3.14159);
    cout << "Double 3.14159:" << endl;
    tp1.displayBits();
    cout << endl;
    
    TypePunning tp2(static_cast<uint64_t>(0x40490FDB));
    cout << "Uint64 0x40490FDB:" << endl;
    tp2.displayBits();
    cout << endl;
    
    // Example 5: Modern C++17 variant
    cout << "5. Modern C++17 Variant:" << endl;
    ModernVariant v1 = 42;
    ModernVariant v2 = 3.14f;
    ModernVariant v3 = string("Modern C++");
    ModernVariant v4 = true;
    
    printVariant(v1);
    printVariant(v2);
    printVariant(v3);
    printVariant(v4);
    cout << endl;
    
    // Example 6: Union with function pointers
    cout << "6. Union with Function Pointers:" << endl;
    union FunctionUnion {
        int (*intFunc)(int);
        float (*floatFunc)(float);
        void (*voidFunc)();
    };
    
    auto intSquare = [](int x) { return x * x; };
    auto floatSquare = [](float x) { return x * x; };
    auto printHello = []() { cout << "Hello from function pointer!" << endl; };
    
    FunctionUnion funcUnion;
    funcUnion.intFunc = intSquare;
    cout << "5 squared: " << funcUnion.intFunc(5) << endl;
    
    funcUnion.floatFunc = floatSquare;
    cout << "3.5 squared: " << funcUnion.floatFunc(3.5f) << endl;
    
    funcUnion.voidFunc = printHello;
    funcUnion.voidFunc();
    
    return 0;
}
