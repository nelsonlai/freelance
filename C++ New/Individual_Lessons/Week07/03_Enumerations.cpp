/*
 * Lesson 7.3: Enumerations
 * 
 * This file demonstrates enum declaration, usage,
 * scoped enumerations, and enum operations.
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>

// Traditional enum
enum Color {
    RED,
    GREEN,
    BLUE
};

// Enum with custom values
enum Status {
    PENDING = 10,
    RUNNING = 20,
    COMPLETED = 30,
    FAILED = 40
};

// Scoped enumeration (enum class)
enum class Priority {
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3,
    CRITICAL = 4
};

// Scoped enumeration with custom underlying type
enum class Direction : uint8_t {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
};

// Enum class for file permissions
enum class FilePermission {
    READ = 1,
    WRITE = 2,
    EXECUTE = 4
};

// Function to demonstrate basic enums
void demonstrateBasicEnums() {
    std::cout << "=== Basic Enums Demonstration ===" << std::endl;
    
    // Traditional enum usage
    Color color = GREEN;
    std::cout << "Color: " << color << std::endl;
    
    // Enum with custom values
    Status status = RUNNING;
    std::cout << "Status: " << status << std::endl;
    
    // Switch statement with enum
    switch (status) {
        case PENDING:
            std::cout << "Task is pending" << std::endl;
            break;
        case RUNNING:
            std::cout << "Task is running" << std::endl;
            break;
        case COMPLETED:
            std::cout << "Task is completed" << std::endl;
            break;
        case FAILED:
            std::cout << "Task failed" << std::endl;
            break;
    }
    
    // Enum size
    std::cout << "Size of Color enum: " << sizeof(Color) << " bytes" << std::endl;
    std::cout << "Size of Status enum: " << sizeof(Status) << " bytes" << std::endl;
}

// Function to demonstrate scoped enumerations
void demonstrateScopedEnums() {
    std::cout << "\n=== Scoped Enums (enum class) ===" << std::endl;
    
    Priority priority = Priority::HIGH;
    std::cout << "Priority value: " << static_cast<int>(priority) << std::endl;
    
    // Switch statement with scoped enum
    switch (priority) {
        case Priority::LOW:
            std::cout << "Low priority task" << std::endl;
            break;
        case Priority::MEDIUM:
            std::cout << "Medium priority task" << std::endl;
            break;
        case Priority::HIGH:
            std::cout << "High priority task" << std::endl;
            break;
        case Priority::CRITICAL:
            std::cout << "Critical priority task" << std::endl;
            break;
    }
    
    // Enum class size
    std::cout << "Size of Priority enum class: " << sizeof(Priority) << " bytes" << std::endl;
    std::cout << "Size of Direction enum class: " << sizeof(Direction) << " bytes" << std::endl;
    
    // Direction enum usage
    Direction dir = Direction::NORTH;
    std::cout << "Direction: " << static_cast<int>(dir) << std::endl;
}

// Function to demonstrate enum conversions
void demonstrateEnumConversions() {
    std::cout << "\n=== Enum Conversions ===" << std::endl;
    
    // Convert enum to int
    Priority priority = Priority::CRITICAL;
    int priorityValue = static_cast<int>(priority);
    std::cout << "Priority as int: " << priorityValue << std::endl;
    
    // Convert int to enum
    int value = 2;
    Priority convertedPriority = static_cast<Priority>(value);
    std::cout << "Int " << value << " as Priority: " << static_cast<int>(convertedPriority) << std::endl;
    
    // Direction conversions
    Direction dir = Direction::EAST;
    uint8_t dirValue = static_cast<uint8_t>(dir);
    std::cout << "Direction as uint8_t: " << (int)dirValue << std::endl;
    
    // Convert back from uint8_t
    uint8_t newValue = 3;
    Direction newDir = static_cast<Direction>(newValue);
    std::cout << "uint8_t " << (int)newValue << " as Direction: " << static_cast<int>(newDir) << std::endl;
}

// Function to demonstrate enum operations
void demonstrateEnumOperations() {
    std::cout << "\n=== Enum Operations ===" << std::endl;
    
    // Direction operations
    Direction currentDir = Direction::NORTH;
    std::cout << "Current direction: " << static_cast<int>(currentDir) << std::endl;
    
    // Turn right
    Direction rightDir = static_cast<Direction>((static_cast<int>(currentDir) + 1) % 4);
    std::cout << "Turn right: " << static_cast<int>(rightDir) << std::endl;
    
    // Turn left
    Direction leftDir = static_cast<Direction>((static_cast<int>(currentDir) + 3) % 4);
    std::cout << "Turn left: " << static_cast<int>(leftDir) << std::endl;
    
    // Turn around
    Direction oppositeDir = static_cast<Direction>((static_cast<int>(currentDir) + 2) % 4);
    std::cout << "Turn around: " << static_cast<int>(oppositeDir) << std::endl;
    
    // File permission operations
    FilePermission perm1 = FilePermission::READ;
    FilePermission perm2 = FilePermission::WRITE;
    
    // Combine permissions (bitwise OR)
    FilePermission combinedPerm = static_cast<FilePermission>(
        static_cast<int>(perm1) | static_cast<int>(perm2)
    );
    std::cout << "Combined permission: " << static_cast<int>(combinedPerm) << std::endl;
    
    // Check if permission is set (bitwise AND)
    bool hasRead = (static_cast<int>(combinedPerm) & static_cast<int>(FilePermission::READ)) != 0;
    bool hasWrite = (static_cast<int>(combinedPerm) & static_cast<int>(FilePermission::WRITE)) != 0;
    bool hasExecute = (static_cast<int>(combinedPerm) & static_cast<int>(FilePermission::EXECUTE)) != 0;
    
    std::cout << "Has READ: " << (hasRead ? "Yes" : "No") << std::endl;
    std::cout << "Has WRITE: " << (hasWrite ? "Yes" : "No") << std::endl;
    std::cout << "Has EXECUTE: " << (hasExecute ? "Yes" : "No") << std::endl;
}

// Function to demonstrate enum iteration
void demonstrateEnumIteration() {
    std::cout << "\n=== Enum Iteration ===" << std::endl;
    
    // Array of enum values
    Priority priorities[] = {Priority::LOW, Priority::MEDIUM, Priority::HIGH, Priority::CRITICAL};
    
    std::cout << "All priorities:" << std::endl;
    for (auto priority : priorities) {
        std::cout << "Priority: " << static_cast<int>(priority) << std::endl;
    }
    
    // Direction iteration
    Direction directions[] = {Direction::NORTH, Direction::EAST, Direction::SOUTH, Direction::WEST};
    const char* directionNames[] = {"North", "East", "South", "West"};
    
    std::cout << "\nAll directions:" << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout << directionNames[i] << ": " << static_cast<int>(directions[i]) << std::endl;
    }
}

// Function to demonstrate enum with functions
void demonstrateEnumWithFunctions() {
    std::cout << "\n=== Enum with Functions ===" << std::endl;
    
    // Function that takes enum parameter
    auto getPriorityString = [](Priority priority) -> std::string {
        switch (priority) {
            case Priority::LOW: return "Low";
            case Priority::MEDIUM: return "Medium";
            case Priority::HIGH: return "High";
            case Priority::CRITICAL: return "Critical";
            default: return "Unknown";
        }
    };
    
    // Function that returns enum
    auto getNextPriority = [](Priority current) -> Priority {
        int currentValue = static_cast<int>(current);
        if (currentValue < static_cast<int>(Priority::CRITICAL)) {
            return static_cast<Priority>(currentValue + 1);
        }
        return Priority::LOW;  // Wrap around
    };
    
    Priority priority = Priority::MEDIUM;
    std::cout << "Current priority: " << getPriorityString(priority) << std::endl;
    
    Priority nextPriority = getNextPriority(priority);
    std::cout << "Next priority: " << getPriorityString(nextPriority) << std::endl;
    
    // Function with enum class
    auto getDirectionName = [](Direction dir) -> std::string {
        switch (dir) {
            case Direction::NORTH: return "North";
            case Direction::EAST: return "East";
            case Direction::SOUTH: return "South";
            case Direction::WEST: return "West";
            default: return "Unknown";
        }
    };
    
    Direction dir = Direction::SOUTH;
    std::cout << "Direction: " << getDirectionName(dir) << std::endl;
}

// Function to demonstrate enum class vs traditional enum
void demonstrateEnumClassVsTraditional() {
    std::cout << "\n=== Enum Class vs Traditional Enum ===" << std::endl;
    
    // Traditional enum
    enum OldColor { RED, GREEN, BLUE };
    enum OldTrafficLight { RED, YELLOW, GREEN };  // This would cause redefinition error
    
    std::cout << "Traditional enum size: " << sizeof(OldColor) << " bytes" << std::endl;
    
    // Enum class (scoped)
    enum class NewColor { RED, GREEN, BLUE };
    enum class NewTrafficLight { RED, YELLOW, GREEN };  // No conflict
    
    std::cout << "Enum class size: " << sizeof(NewColor) << " bytes" << std::endl;
    
    // Usage differences
    OldColor oldColor = RED;  // No scope needed
    NewColor newColor = NewColor::RED;  // Scope required
    
    std::cout << "Traditional enum: " << oldColor << std::endl;
    std::cout << "Enum class: " << static_cast<int>(newColor) << std::endl;
    
    // Implicit conversion differences
    int oldValue = oldColor;  // Implicit conversion allowed
    // int newValue = newColor;  // Error: implicit conversion not allowed
    int newValue = static_cast<int>(newColor);  // Explicit conversion required
    
    std::cout << "Traditional enum as int: " << oldValue << std::endl;
    std::cout << "Enum class as int: " << newValue << std::endl;
}

// Function to demonstrate enum with underlying type
void demonstrateEnumUnderlyingType() {
    std::cout << "\n=== Enum Underlying Type ===" << std::endl;
    
    // Enum with explicit underlying type
    enum class SmallEnum : uint8_t {
        VALUE1 = 1,
        VALUE2 = 2,
        VALUE3 = 3
    };
    
    enum class LargeEnum : uint64_t {
        VALUE1 = 1,
        VALUE2 = 2,
        VALUE3 = 3
    };
    
    std::cout << "Size of SmallEnum (uint8_t): " << sizeof(SmallEnum) << " bytes" << std::endl;
    std::cout << "Size of LargeEnum (uint64_t): " << sizeof(LargeEnum) << " bytes" << std::endl;
    
    // Usage
    SmallEnum small = SmallEnum::VALUE2;
    LargeEnum large = LargeEnum::VALUE3;
    
    std::cout << "SmallEnum value: " << static_cast<uint8_t>(small) << std::endl;
    std::cout << "LargeEnum value: " << static_cast<uint64_t>(large) << std::endl;
}

// Function to demonstrate enum with bitwise operations
void demonstrateEnumBitwiseOperations() {
    std::cout << "\n=== Enum Bitwise Operations ===" << std::endl;
    
    // Enum for flags
    enum class Flags : uint32_t {
        NONE = 0,
        FLAG1 = 1 << 0,  // 1
        FLAG2 = 1 << 1,  // 2
        FLAG3 = 1 << 2,  // 4
        FLAG4 = 1 << 3,  // 8
        ALL = FLAG1 | FLAG2 | FLAG3 | FLAG4
    };
    
    // Set flags
    Flags flags = static_cast<Flags>(
        static_cast<uint32_t>(Flags::FLAG1) | static_cast<uint32_t>(Flags::FLAG3)
    );
    
    std::cout << "Flags value: " << static_cast<uint32_t>(flags) << std::endl;
    
    // Check flags
    bool hasFlag1 = (static_cast<uint32_t>(flags) & static_cast<uint32_t>(Flags::FLAG1)) != 0;
    bool hasFlag2 = (static_cast<uint32_t>(flags) & static_cast<uint32_t>(Flags::FLAG2)) != 0;
    bool hasFlag3 = (static_cast<uint32_t>(flags) & static_cast<uint32_t>(Flags::FLAG3)) != 0;
    bool hasFlag4 = (static_cast<uint32_t>(flags) & static_cast<uint32_t>(Flags::FLAG4)) != 0;
    
    std::cout << "Has FLAG1: " << (hasFlag1 ? "Yes" : "No") << std::endl;
    std::cout << "Has FLAG2: " << (hasFlag2 ? "Yes" : "No") << std::endl;
    std::cout << "Has FLAG3: " << (hasFlag3 ? "Yes" : "No") << std::endl;
    std::cout << "Has FLAG4: " << (hasFlag4 ? "Yes" : "No") << std::endl;
    
    // Clear flag
    flags = static_cast<Flags>(
        static_cast<uint32_t>(flags) & ~static_cast<uint32_t>(Flags::FLAG1)
    );
    std::cout << "\nAfter clearing FLAG1: " << static_cast<uint32_t>(flags) << std::endl;
    
    // Set all flags
    flags = Flags::ALL;
    std::cout << "All flags set: " << static_cast<uint32_t>(flags) << std::endl;
}

// Function to demonstrate enum with containers
void demonstrateEnumWithContainers() {
    std::cout << "\n=== Enum with Containers ===" << std::endl;
    
    // Vector of enums
    std::vector<Priority> priorities = {
        Priority::LOW, Priority::MEDIUM, Priority::HIGH, Priority::CRITICAL
    };
    
    std::cout << "Priorities in vector:" << std::endl;
    for (const auto& priority : priorities) {
        std::cout << "Priority: " << static_cast<int>(priority) << std::endl;
    }
    
    // Map with enum as key
    std::map<Priority, std::string> priorityNames = {
        {Priority::LOW, "Low Priority"},
        {Priority::MEDIUM, "Medium Priority"},
        {Priority::HIGH, "High Priority"},
        {Priority::CRITICAL, "Critical Priority"}
    };
    
    std::cout << "\nPriority names:" << std::endl;
    for (const auto& pair : priorityNames) {
        std::cout << static_cast<int>(pair.first) << ": " << pair.second << std::endl;
    }
    
    // Array of enum values
    Direction directions[4] = {Direction::NORTH, Direction::EAST, Direction::SOUTH, Direction::WEST};
    const char* directionNames[4] = {"North", "East", "South", "West"};
    
    std::cout << "\nDirections:" << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout << directionNames[i] << ": " << static_cast<int>(directions[i]) << std::endl;
    }
}

int main() {
    std::cout << "=== Enumerations Demonstration ===" << std::endl;
    std::cout << "This program demonstrates enum declaration, usage,\n"
              << "scoped enumerations, and enum operations.\n" << std::endl;
    
    // Demonstrate various enum concepts
    demonstrateBasicEnums();
    demonstrateScopedEnums();
    demonstrateEnumConversions();
    demonstrateEnumOperations();
    demonstrateEnumIteration();
    demonstrateEnumWithFunctions();
    demonstrateEnumClassVsTraditional();
    demonstrateEnumUnderlyingType();
    demonstrateEnumBitwiseOperations();
    demonstrateEnumWithContainers();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Enums provide named constants for better readability" << std::endl;
    std::cout << "2. Enum class provides scoping and type safety" << std::endl;
    std::cout << "3. Explicit conversions are required for enum class" << std::endl;
    std::cout << "4. Enums can have custom underlying types" << std::endl;
    std::cout << "5. Enums support bitwise operations for flags" << std::endl;
    std::cout << "6. Enums work well with containers and algorithms" << std::endl;
    std::cout << "7. Prefer enum class over traditional enum for new code" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o enumerations 03_Enumerations.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o enumerations 03_Enumerations.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 03_Enumerations.cpp
 * 
 * Running:
 * ./enumerations (Linux/macOS)
 * enumerations.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for enum class.
 * C++17 is recommended for best enum support.
 * 
 * Enum Notes:
 * - Use enum class for type safety
 * - Explicit conversions are required
 * - Enums can have custom underlying types
 * - Bitwise operations work with enums
 * - Enums are useful for state machines
 * - Prefer enum class over traditional enum
 */"""