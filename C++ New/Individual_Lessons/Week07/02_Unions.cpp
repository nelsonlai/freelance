/*
 * Lesson 7.2: Unions
 * 
 * This file demonstrates union declaration, usage,
 * memory layout, and tagged unions.
 */

#include <iostream>
#include <string>
#include <array>
#include <variant>

// Basic union example
union Number {
    int integer;
    double floating;
    char character;
};

// Tagged union for safety
struct TaggedNumber {
    enum Type { INTEGER, FLOATING, CHARACTER } type;
    union {
        int integer;
        double floating;
        char character;
    } value;
    
    // Constructor for integer
    TaggedNumber(int val) : type(INTEGER) {
        value.integer = val;
    }
    
    // Constructor for floating
    TaggedNumber(double val) : type(FLOATING) {
        value.floating = val;
    }
    
    // Constructor for character
    TaggedNumber(char val) : type(CHARACTER) {
        value.character = val;
    }
    
    // Display function
    void display() const {
        switch (type) {
            case INTEGER:
                std::cout << "Integer: " << value.integer << std::endl;
                break;
            case FLOATING:
                std::cout << "Floating: " << value.floating << std::endl;
                break;
            case CHARACTER:
                std::cout << "Character: " << value.character << std::endl;
                break;
        }
    }
};

// Union for network data
union NetworkData {
    struct {
        uint16_t type;
        uint16_t length;
        uint32_t data;
    } header;
    
    char raw_data[8];
    
    void display() const {
        std::cout << "Header - Type: " << header.type 
                  << ", Length: " << header.length 
                  << ", Data: " << header.data << std::endl;
    }
};

// Union for graphics color
union Color {
    struct {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t alpha;
    } rgba;
    
    uint32_t packed;
    
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
        rgba.red = r;
        rgba.green = g;
        rgba.blue = b;
        rgba.alpha = a;
    }
    
    void display() const {
        std::cout << "RGBA: (" << (int)rgba.red << ", " << (int)rgba.green 
                  << ", " << (int)rgba.blue << ", " << (int)rgba.alpha << ")" << std::endl;
        std::cout << "Packed: 0x" << std::hex << packed << std::dec << std::endl;
    }
};

// Function to demonstrate basic unions
void demonstrateBasicUnions() {
    std::cout << "=== Basic Unions Demonstration ===" << std::endl;
    
    union Number num;
    
    std::cout << "Union size: " << sizeof(union Number) << " bytes" << std::endl;
    std::cout << "Size of int: " << sizeof(int) << " bytes" << std::endl;
    std::cout << "Size of double: " << sizeof(double) << " bytes" << std::endl;
    std::cout << "Size of char: " << sizeof(char) << " bytes" << std::endl;
    
    // Use integer member
    num.integer = 42;
    std::cout << "\nUsing integer member:" << std::endl;
    std::cout << "Integer: " << num.integer << std::endl;
    std::cout << "Floating (garbage): " << num.floating << std::endl;
    std::cout << "Character (garbage): " << (int)num.character << std::endl;
    
    // Use floating member (overwrites integer)
    num.floating = 3.14159;
    std::cout << "\nUsing floating member:" << std::endl;
    std::cout << "Integer (garbage): " << num.integer << std::endl;
    std::cout << "Floating: " << num.floating << std::endl;
    std::cout << "Character (garbage): " << (int)num.character << std::endl;
    
    // Use character member (overwrites floating)
    num.character = 'A';
    std::cout << "\nUsing character member:" << std::endl;
    std::cout << "Integer (garbage): " << num.integer << std::endl;
    std::cout << "Floating (garbage): " << num.floating << std::endl;
    std::cout << "Character: " << num.character << std::endl;
}

// Function to demonstrate tagged unions
void demonstrateTaggedUnions() {
    std::cout << "\n=== Tagged Unions Demonstration ===" << std::endl;
    
    TaggedNumber num1(42);
    TaggedNumber num2(3.14159);
    TaggedNumber num3('X');
    
    std::cout << "TaggedNumber 1:" << std::endl;
    num1.display();
    
    std::cout << "\nTaggedNumber 2:" << std::endl;
    num2.display();
    
    std::cout << "\nTaggedNumber 3:" << std::endl;
    num3.display();
    
    // Safe access using tag
    std::cout << "\nSafe access:" << std::endl;
    if (num1.type == TaggedNumber::INTEGER) {
        std::cout << "num1 is an integer: " << num1.value.integer << std::endl;
    }
    
    if (num2.type == TaggedNumber::FLOATING) {
        std::cout << "num2 is a floating: " << num2.value.floating << std::endl;
    }
    
    if (num3.type == TaggedNumber::CHARACTER) {
        std::cout << "num3 is a character: " << num3.value.character << std::endl;
    }
}

// Function to demonstrate union memory layout
void demonstrateUnionMemoryLayout() {
    std::cout << "\n=== Union Memory Layout ===" << std::endl;
    
    union MemoryTest {
        struct {
            char a;
            char b;
            char c;
            char d;
        } chars;
        int integer;
    };
    
    MemoryTest test;
    test.chars.a = 'A';
    test.chars.b = 'B';
    test.chars.c = 'C';
    test.chars.d = 'D';
    
    std::cout << "Union size: " << sizeof(MemoryTest) << " bytes" << std::endl;
    std::cout << "Chars: " << test.chars.a << test.chars.b 
              << test.chars.c << test.chars.d << std::endl;
    std::cout << "Integer: " << test.integer << std::endl;
    
    // Show memory addresses
    std::cout << "\nMemory addresses:" << std::endl;
    std::cout << "&test: " << &test << std::endl;
    std::cout << "&test.chars: " << &test.chars << std::endl;
    std::cout << "&test.integer: " << &test.integer << std::endl;
    std::cout << "&test.chars.a: " << (void*)&test.chars.a << std::endl;
}

// Function to demonstrate network data union
void demonstrateNetworkData() {
    std::cout << "\n=== Network Data Union ===" << std::endl;
    
    NetworkData packet;
    
    // Set header data
    packet.header.type = 0x1234;
    packet.header.length = 0x5678;
    packet.header.data = 0x9ABCDEF0;
    
    std::cout << "Network packet:" << std::endl;
    packet.display();
    
    // Show raw data
    std::cout << "\nRaw data bytes:" << std::endl;
    for (int i = 0; i < 8; ++i) {
        std::cout << "Byte " << i << ": 0x" << std::hex 
                  << (unsigned char)packet.raw_data[i] << std::dec << std::endl;
    }
}

// Function to demonstrate color union
void demonstrateColorUnion() {
    std::cout << "\n=== Color Union ===" << std::endl;
    
    Color red(255, 0, 0, 255);
    Color green(0, 255, 0, 255);
    Color blue(0, 0, 255, 255);
    Color white(255, 255, 255, 255);
    
    std::cout << "Red color:" << std::endl;
    red.display();
    
    std::cout << "\nGreen color:" << std::endl;
    green.display();
    
    std::cout << "\nBlue color:" << std::endl;
    blue.display();
    
    std::cout << "\nWhite color:" << std::endl;
    white.display();
}

// Function to demonstrate union vs structure
void demonstrateUnionVsStructure() {
    std::cout << "\n=== Union vs Structure ===" << std::endl;
    
    // Structure
    struct Point {
        int x, y;
    };
    
    // Union
    union Number {
        int integer;
        double floating;
    };
    
    std::cout << "Structure Point size: " << sizeof(Point) << " bytes" << std::endl;
    std::cout << "Union Number size: " << sizeof(Number) << " bytes" << std::endl;
    
    // Structure usage
    Point p = {10, 20};
    std::cout << "\nStructure Point: x=" << p.x << ", y=" << p.y << std::endl;
    
    // Union usage
    Number n;
    n.integer = 42;
    std::cout << "Union Number (integer): " << n.integer << std::endl;
    n.floating = 3.14;
    std::cout << "Union Number (floating): " << n.floating << std::endl;
}

// Function to demonstrate anonymous unions
void demonstrateAnonymousUnions() {
    std::cout << "\n=== Anonymous Unions ===" << std::endl;
    
    struct Container {
        enum Type { INTEGER, FLOATING, CHARACTER } type;
        union {  // Anonymous union
            int i;
            double d;
            char c;
        };
        
        Container(int val) : type(INTEGER), i(val) {}
        Container(double val) : type(FLOATING), d(val) {}
        Container(char val) : type(CHARACTER), c(val) {}
        
        void display() const {
            switch (type) {
                case INTEGER:
                    std::cout << "Integer: " << i << std::endl;
                    break;
                case FLOATING:
                    std::cout << "Floating: " << d << std::endl;
                    break;
                case CHARACTER:
                    std::cout << "Character: " << c << std::endl;
                    break;
            }
        }
    };
    
    Container c1(42);
    Container c2(3.14159);
    Container c3('Z');
    
    std::cout << "Container 1:" << std::endl;
    c1.display();
    
    std::cout << "\nContainer 2:" << std::endl;
    c2.display();
    
    std::cout << "\nContainer 3:" << std::endl;
    c3.display();
}

// Function to demonstrate union safety issues
void demonstrateUnionSafety() {
    std::cout << "\n=== Union Safety Issues ===" << std::endl;
    
    union UnsafeUnion {
        int integer;
        double floating;
    };
    
    UnsafeUnion u;
    
    // This is unsafe - accessing inactive member
    u.integer = 42;
    std::cout << "Integer: " << u.integer << std::endl;
    u.floating = 3.14;
    std::cout << "Floating: " << u.floating << std::endl;
    std::cout << "Integer (now garbage): " << u.integer << std::endl;
    
    std::cout << "\nWarning: Accessing inactive union members causes undefined behavior!" << std::endl;
    std::cout << "Always use tagged unions or std::variant for safety." << std::endl;
}

// Function to demonstrate modern alternatives
void demonstrateModernAlternatives() {
    std::cout << "\n=== Modern Alternatives (std::variant) ===" << std::endl;
    
    // Using std::variant (C++17)
    std::variant<int, double, std::string> var;
    
    var = 42;
    std::cout << "Variant holds int: " << std::get<int>(var) << std::endl;
    
    var = 3.14159;
    std::cout << "Variant holds double: " << std::get<double>(var) << std::endl;
    
    var = std::string("Hello");
    std::cout << "Variant holds string: " << std::get<std::string>(var) << std::endl;
    
    // Safe access with std::visit
    std::visit([](auto&& value) {
        using T = std::decay_t<decltype(value)>;
        if constexpr (std::is_same_v<T, int>) {
            std::cout << "Visiting int: " << value << std::endl;
        } else if constexpr (std::is_same_v<T, double>) {
            std::cout << "Visiting double: " << value << std::endl;
        } else if constexpr (std::is_same_v<T, std::string>) {
            std::cout << "Visiting string: " << value << std::endl;
        }
    }, var);
    
    std::cout << "\nstd::variant is type-safe and doesn't have undefined behavior!" << std::endl;
}

int main() {
    std::cout << "=== Unions Demonstration ===" << std::endl;
    std::cout << "This program demonstrates union declaration, usage,\n"
              << "memory layout, and tagged unions.\n" << std::endl;
    
    // Demonstrate various union concepts
    demonstrateBasicUnions();
    demonstrateTaggedUnions();
    demonstrateUnionMemoryLayout();
    demonstrateNetworkData();
    demonstrateColorUnion();
    demonstrateUnionVsStructure();
    demonstrateAnonymousUnions();
    demonstrateUnionSafety();
    demonstrateModernAlternatives();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Unions share memory between members" << std::endl;
    std::cout << "2. Union size equals the size of its largest member" << std::endl;
    std::cout << "3. Only one union member can be active at a time" << std::endl;
    std::cout << "4. Tagged unions provide safety by tracking active member" << std::endl;
    std::cout << "5. Accessing inactive members causes undefined behavior" << std::endl;
    std::cout << "6. Unions are useful for memory efficiency" << std::endl;
    std::cout << "7. Consider std::variant as a modern, safe alternative" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o unions 02_Unions.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o unions 02_Unions.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 02_Unions.cpp
 * 
 * Running:
 * ./unions (Linux/macOS)
 * unions.exe (Windows)
 * 
 * Note: This lesson requires C++17 for std::variant.
 * C++11 is sufficient for basic union functionality.
 * 
 * Union Notes:
 * - Unions share memory between members
 * - Only one member can be active at a time
 * - Use tagged unions for safety
 * - Consider std::variant for modern C++
 * - Be careful with member lifetime
 * - Unions are useful for memory efficiency
 */"""