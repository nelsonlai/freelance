/*
 * ENUM INTERMEDIATE EXAMPLES
 * 
 * This file demonstrates intermediate enum concepts including scoped enums, bitwise operations, and advanced usage patterns:
 * - Advanced concepts and techniques
 * - Real-world applications and patterns
 * - Best practices and optimization
 * - Complex scenarios and edge cases
 * 
 * Learning Objectives:
 * - Master advanced ENUM concepts
 * - Understand professional coding patterns
 * - Learn optimization techniques
 * - Apply knowledge in complex scenarios
 * - Develop problem-solving skills
 * 
 * Prerequisites:
 * - Solid understanding of basic ENUM concepts
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
#include <map>
using namespace std;

// Scoped enum (enum class) - C++11
enum class Color {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    PURPLE
};

// Enum with custom underlying type
enum class Priority : int {
    LOW = 1,
    MEDIUM = 5,
    HIGH = 10,
    CRITICAL = 20
};

// Enum with explicit values
enum class FilePermission : unsigned char {
    READ = 0x01,      // 00000001
    WRITE = 0x02,     // 00000010
    EXECUTE = 0x04,   // 00000100
    ALL = READ | WRITE | EXECUTE  // 00000111
};

// Enum for state machine
enum class State {
    IDLE,
    LOADING,
    PROCESSING,
    COMPLETED,
    ERROR
};

// Function to convert enum to string
string colorToString(Color c) {
    switch (c) {
        case Color::RED: return "Red";
        case Color::GREEN: return "Green";
        case Color::BLUE: return "Blue";
        case Color::YELLOW: return "Yellow";
        case Color::PURPLE: return "Purple";
        default: return "Unknown";
    }
}

// Function to convert priority to string
string priorityToString(Priority p) {
    switch (p) {
        case Priority::LOW: return "Low";
        case Priority::MEDIUM: return "Medium";
        case Priority::HIGH: return "High";
        case Priority::CRITICAL: return "Critical";
        default: return "Unknown";
    }
}

// Function to check file permissions
bool hasPermission(FilePermission permissions, FilePermission required) {
    return (static_cast<unsigned char>(permissions) & static_cast<unsigned char>(required)) != 0;
}

// Function to add permission
FilePermission addPermission(FilePermission current, FilePermission newPerm) {
    return static_cast<FilePermission>(
        static_cast<unsigned char>(current) | static_cast<unsigned char>(newPerm)
    );
}

// Function to remove permission
FilePermission removePermission(FilePermission current, FilePermission removePerm) {
    return static_cast<FilePermission>(
        static_cast<unsigned char>(current) & ~static_cast<unsigned char>(removePerm)
    );
}

// State machine class
class StateMachine {
private:
    State currentState;
    
public:
    StateMachine() : currentState(State::IDLE) {}
    
    State getCurrentState() const { return currentState; }
    
    void startLoading() {
        if (currentState == State::IDLE) {
            currentState = State::LOADING;
            cout << "State changed to LOADING" << endl;
        }
    }
    
    void startProcessing() {
        if (currentState == State::LOADING) {
            currentState = State::PROCESSING;
            cout << "State changed to PROCESSING" << endl;
        }
    }
    
    void complete() {
        if (currentState == State::PROCESSING) {
            currentState = State::COMPLETED;
            cout << "State changed to COMPLETED" << endl;
        }
    }
    
    void error() {
        currentState = State::ERROR;
        cout << "State changed to ERROR" << endl;
    }
    
    void reset() {
        currentState = State::IDLE;
        cout << "State reset to IDLE" << endl;
    }
};

// Template function for enum iteration
template<typename EnumType>
void printEnumValues() {
    cout << "Enum values:" << endl;
    // This is a simplified example - in practice, you'd need more sophisticated reflection
}

// Enum with associated data using struct
struct ColorInfo {
    Color color;
    string name;
    int red, green, blue;
    
    ColorInfo(Color c, const string& n, int r, int g, int b) 
        : color(c), name(n), red(r), green(g), blue(b) {}
};

int main() {
    cout << "=== ENUM INTERMEDIATE EXAMPLES ===" << endl << endl;
    
    // Example 1: Scoped enums (enum class)
    cout << "1. Scoped Enums (enum class):" << endl;
    Color favoriteColor = Color::BLUE;
    cout << "Favorite color: " << colorToString(favoriteColor) << endl;
    
    // Scoped enums require explicit scope resolution
    if (favoriteColor == Color::BLUE) {
        cout << "The color is indeed blue!" << endl;
    }
    cout << endl;
    
    // Example 2: Enums with custom underlying types
    cout << "2. Enums with Custom Underlying Types:" << endl;
    Priority taskPriority = Priority::HIGH;
    cout << "Task priority: " << priorityToString(taskPriority) << endl;
    cout << "Priority value: " << static_cast<int>(taskPriority) << endl;
    
    // Comparison with underlying type
    if (static_cast<int>(taskPriority) >= static_cast<int>(Priority::MEDIUM)) {
        cout << "This is a medium or high priority task" << endl;
    }
    cout << endl;
    
    // Example 3: Bitwise operations with enums
    cout << "3. Bitwise Operations with Enums:" << endl;
    FilePermission permissions = FilePermission::READ;
    cout << "Initial permissions: " << static_cast<int>(permissions) << endl;
    
    // Add write permission
    permissions = addPermission(permissions, FilePermission::WRITE);
    cout << "After adding WRITE: " << static_cast<int>(permissions) << endl;
    
    // Add execute permission
    permissions = addPermission(permissions, FilePermission::EXECUTE);
    cout << "After adding EXECUTE: " << static_cast<int>(permissions) << endl;
    
    // Check permissions
    if (hasPermission(permissions, FilePermission::READ)) {
        cout << "Has READ permission" << endl;
    }
    if (hasPermission(permissions, FilePermission::WRITE)) {
        cout << "Has WRITE permission" << endl;
    }
    if (hasPermission(permissions, FilePermission::EXECUTE)) {
        cout << "Has EXECUTE permission" << endl;
    }
    
    // Remove write permission
    permissions = removePermission(permissions, FilePermission::WRITE);
    cout << "After removing WRITE: " << static_cast<int>(permissions) << endl;
    cout << endl;
    
    // Example 4: State machine with enums
    cout << "4. State Machine with Enums:" << endl;
    StateMachine machine;
    
    cout << "Initial state: " << static_cast<int>(machine.getCurrentState()) << endl;
    machine.startLoading();
    machine.startProcessing();
    machine.complete();
    
    // Simulate error
    machine.reset();
    machine.startLoading();
    machine.error();
    cout << endl;
    
    // Example 5: Enum with associated data
    cout << "5. Enum with Associated Data:" << endl;
    vector<ColorInfo> colorDatabase = {
        {Color::RED, "Red", 255, 0, 0},
        {Color::GREEN, "Green", 0, 255, 0},
        {Color::BLUE, "Blue", 0, 0, 255},
        {Color::YELLOW, "Yellow", 255, 255, 0},
        {Color::PURPLE, "Purple", 128, 0, 128}
    };
    
    for (const auto& colorInfo : colorDatabase) {
        cout << colorInfo.name << ": RGB(" << colorInfo.red << ", " 
             << colorInfo.green << ", " << colorInfo.blue << ")" << endl;
    }
    cout << endl;
    
    // Example 6: Enum in containers
    cout << "6. Enum in Containers:" << endl;
    vector<Priority> taskPriorities = {Priority::LOW, Priority::HIGH, Priority::MEDIUM, Priority::CRITICAL};
    
    cout << "Task priorities: ";
    for (const auto& priority : taskPriorities) {
        cout << priorityToString(priority) << " ";
    }
    cout << endl;
    
    // Sort by priority value
    sort(taskPriorities.begin(), taskPriorities.end(), [](Priority a, Priority b) {
        return static_cast<int>(a) < static_cast<int>(b);
    });
    
    cout << "Sorted priorities: ";
    for (const auto& priority : taskPriorities) {
        cout << priorityToString(priority) << " ";
    }
    cout << endl;
    cout << endl;
    
    // Example 7: Enum with switch expressions (C++17 style)
    cout << "7. Enum with Switch Expressions:" << endl;
    auto getColorCode = [](Color c) -> string {
        switch (c) {
            case Color::RED: return "#FF0000";
            case Color::GREEN: return "#00FF00";
            case Color::BLUE: return "#0000FF";
            case Color::YELLOW: return "#FFFF00";
            case Color::PURPLE: return "#800080";
            default: return "#000000";
        }
    };
    
    cout << "Color codes:" << endl;
    for (const auto& colorInfo : colorDatabase) {
        cout << colorInfo.name << ": " << getColorCode(colorInfo.color) << endl;
    }
    
    return 0;
}
