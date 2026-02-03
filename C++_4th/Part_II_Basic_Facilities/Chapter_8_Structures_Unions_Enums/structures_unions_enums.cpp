#include <iostream>
#include <string>
#include <cmath>

// Demonstrates structures, unions, and enumerations in C++
int main() {
    std::cout << "Structures, Unions, and Enumerations Demonstration" << std::endl;
    std::cout << "=================================================" << std::endl;
    
    // 1. Basic structures
    std::cout << "\n1. BASIC STRUCTURES:" << std::endl;
    
    struct Point {
        double x, y;
        
        Point(double x = 0, double y = 0) : x(x), y(y) {}
        
        void display() const {
            std::cout << "Point(" << x << ", " << y << ")" << std::endl;
        }
        
        double distance_from_origin() const {
            return std::sqrt(x * x + y * y);
        }
        
        Point operator+(const Point& other) const {
            return Point(x + other.x, y + other.y);
        }
    };
    
    Point p1(3.0, 4.0);
    Point p2(1.0, 2.0);
    
    std::cout << "Point 1: ";
    p1.display();
    std::cout << "Distance from origin: " << p1.distance_from_origin() << std::endl;
    
    Point p3 = p1 + p2;
    std::cout << "Point 1 + Point 2: ";
    p3.display();
    
    // 2. Structure with different data types
    std::cout << "\n2. STRUCTURE WITH DIFFERENT DATA TYPES:" << std::endl;
    
    struct Person {
        std::string name;
        int age;
        double height;
        bool is_student;
        
        Person(const std::string& name, int age, double height, bool is_student)
            : name(name), age(age), height(height), is_student(is_student) {}
        
        void display_info() const {
            std::cout << "Name: " << name << ", Age: " << age 
                      << ", Height: " << height << ", Student: " 
                      << std::boolalpha << is_student << std::endl;
        }
        
        bool is_adult() const {
            return age >= 18;
        }
    };
    
    Person person1("Alice", 25, 5.6, true);
    Person person2("Bob", 17, 5.8, true);
    
    person1.display_info();
    std::cout << "Is adult: " << std::boolalpha << person1.is_adult() << std::endl;
    
    person2.display_info();
    std::cout << "Is adult: " << std::boolalpha << person2.is_adult() << std::endl;
    
    // 3. Traditional enumerations
    std::cout << "\n3. TRADITIONAL ENUMERATIONS:" << std::endl;
    
    enum Color {
        RED,
        GREEN,
        BLUE,
        YELLOW,
        PURPLE
    };
    
    Color color = GREEN;
    std::cout << "Color: " << color << std::endl;  // Implicit conversion to int
    
    // Switch statement with enum
    switch (color) {
        case RED:
            std::cout << "Color is red" << std::endl;
            break;
        case GREEN:
            std::cout << "Color is green" << std::endl;
            break;
        case BLUE:
            std::cout << "Color is blue" << std::endl;
            break;
        default:
            std::cout << "Other color" << std::endl;
            break;
    }
    
    // 4. Scoped enumerations (enum class)
    std::cout << "\n4. SCOPED ENUMERATIONS (ENUM CLASS):" << std::endl;
    
    enum class Size {
        SMALL,
        MEDIUM,
        LARGE,
        EXTRA_LARGE
    };
    
    enum class Status : unsigned char {
        PENDING = 0,
        ACTIVE = 1,
        COMPLETED = 2,
        CANCELLED = 3
    };
    
    Size size = Size::MEDIUM;
    Status status = Status::ACTIVE;
    
    // Type-safe comparison
    if (size == Size::MEDIUM) {
        std::cout << "Size is medium" << std::endl;
    }
    
    std::cout << "Status value: " << static_cast<int>(status) << std::endl;
    
    // 5. Unions
    std::cout << "\n5. UNIONS:" << std::endl;
    
    union Number {
        int integer;
        double floating_point;
        char character;
        
        Number(int value) : integer(value) {}
        Number(double value) : floating_point(value) {}
        Number(char value) : character(value) {}
    };
    
    Number num1(42);
    Number num2(3.14);
    Number num3('A');
    
    std::cout << "Integer: " << num1.integer << std::endl;
    std::cout << "Float: " << num2.floating_point << std::endl;
    std::cout << "Character: " << num3.character << std::endl;
    
    std::cout << "Size of union: " << sizeof(Number) << " bytes" << std::endl;
    
    // 6. Tagged union (type-safe union)
    std::cout << "\n6. TAGGED UNION (TYPE-SAFE UNION):" << std::endl;
    
    enum class ValueType {
        INTEGER,
        FLOATING_POINT,
        CHARACTER
    };
    
    struct TaggedNumber {
        ValueType type;
        union {
            int integer;
            double floating_point;
            char character;
        } value;
        
        TaggedNumber(int val) : type(ValueType::INTEGER) { value.integer = val; }
        TaggedNumber(double val) : type(ValueType::FLOATING_POINT) { value.floating_point = val; }
        TaggedNumber(char val) : type(ValueType::CHARACTER) { value.character = val; }
        
        void display() const {
            switch (type) {
                case ValueType::INTEGER:
                    std::cout << "Integer: " << value.integer << std::endl;
                    break;
                case ValueType::FLOATING_POINT:
                    std::cout << "Float: " << value.floating_point << std::endl;
                    break;
                case ValueType::CHARACTER:
                    std::cout << "Character: " << value.character << std::endl;
                    break;
            }
        }
    };
    
    TaggedNumber tagged1(42);
    TaggedNumber tagged2(3.14);
    TaggedNumber tagged3('Z');
    
    tagged1.display();
    tagged2.display();
    tagged3.display();
    
    // 7. Memory layout and alignment
    std::cout << "\n7. MEMORY LAYOUT AND ALIGNMENT:" << std::endl;
    
    struct AlignedStruct {
        char c;      // 1 byte
        int i;       // 4 bytes
        double d;    // 8 bytes
    };
    
    struct PackedStruct {
        char c;      // 1 byte
        int i;       // 4 bytes
        double d;    // 8 bytes
    } __attribute__((packed));
    
    std::cout << "Size of AlignedStruct: " << sizeof(AlignedStruct) << " bytes" << std::endl;
    std::cout << "Size of PackedStruct: " << sizeof(PackedStruct) << " bytes" << std::endl;
    std::cout << "Alignment of AlignedStruct: " << alignof(AlignedStruct) << " bytes" << std::endl;
    std::cout << "Alignment of PackedStruct: " << alignof(PackedStruct) << " bytes" << std::endl;
    
    // 8. Bit fields
    std::cout << "\n8. BIT FIELDS:" << std::endl;
    
    struct BitFieldStruct {
        unsigned int flag1 : 1;    // 1 bit
        unsigned int flag2 : 1;    // 1 bit
        unsigned int value : 6;    // 6 bits
        unsigned int padding : 24; // 24 bits
    };
    
    BitFieldStruct bit_field;
    bit_field.flag1 = 1;
    bit_field.flag2 = 0;
    bit_field.value = 42;
    
    std::cout << "Flag1: " << bit_field.flag1 << std::endl;
    std::cout << "Flag2: " << bit_field.flag2 << std::endl;
    std::cout << "Value: " << bit_field.value << std::endl;
    std::cout << "Size of BitFieldStruct: " << sizeof(BitFieldStruct) << " bytes" << std::endl;
    
    // 9. Anonymous structures and unions
    std::cout << "\n9. ANONYMOUS STRUCTURES AND UNIONS:" << std::endl;
    
    struct AnonymousExample {
        int type;
        union {
            int integer;
            double floating_point;
            char character;
        };  // Anonymous union
        
        AnonymousExample(int t, int val) : type(t), integer(val) {}
        AnonymousExample(int t, double val) : type(t), floating_point(val) {}
        AnonymousExample(int t, char val) : type(t), character(val) {}
    };
    
    AnonymousExample anon1(1, 42);
    AnonymousExample anon2(2, 3.14);
    AnonymousExample anon3(3, 'X');
    
    std::cout << "Type: " << anon1.type << ", Value: " << anon1.integer << std::endl;
    std::cout << "Type: " << anon2.type << ", Value: " << anon2.floating_point << std::endl;
    std::cout << "Type: " << anon3.type << ", Value: " << anon3.character << std::endl;
    
    // 10. Forward declarations
    std::cout << "\n10. FORWARD DECLARATIONS:" << std::endl;
    
    enum class ForwardEnum : int;  // Forward declaration
    
    enum class ForwardEnum : int {
        VALUE1,
        VALUE2,
        VALUE3
    };
    
    ForwardEnum forward_val = ForwardEnum::VALUE2;
    std::cout << "Forward enum value: " << static_cast<int>(forward_val) << std::endl;
    
    std::cout << "\nStructures, unions, and enumerations demonstration completed!" << std::endl;
    return 0;
}
