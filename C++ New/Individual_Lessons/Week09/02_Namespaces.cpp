/*
 * Lesson 9.2: Namespaces
 * 
 * This file demonstrates namespace declaration, definition,
 * aliases, using declarations, and namespace organization.
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <chrono>

// Basic namespace example
namespace Math {
    const double PI = 3.14159;
    const double E = 2.71828;
    
    double circle_area(double radius) {
        return PI * radius * radius;
    }
    
    double circle_circumference(double radius) {
        return 2 * PI * radius;
    }
    
    double rectangle_area(double length, double width) {
        return length * width;
    }
    
    double triangle_area(double base, double height) {
        return 0.5 * base * height;
    }
}

// String utility namespace
namespace StringUtils {
    std::string to_upper(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }
    
    std::string to_lower(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }
    
    std::string reverse(const std::string& str) {
        std::string result = str;
        std::reverse(result.begin(), result.end());
        return result;
    }
    
    bool starts_with(const std::string& str, const std::string& prefix) {
        return str.size() >= prefix.size() && 
               str.substr(0, prefix.size()) == prefix;
    }
    
    bool ends_with(const std::string& str, const std::string& suffix) {
        return str.size() >= suffix.size() && 
               str.substr(str.size() - suffix.size()) == suffix;
    }
}

// Nested namespace example
namespace Library {
    namespace Core {
        class Base {
        private:
            int id_;
            std::string name_;
            
        public:
            Base(int id, const std::string& name) : id_(id), name_(name) {}
            
            int getId() const { return id_; }
            const std::string& getName() const { return name_; }
            
            virtual void display() const {
                std::cout << "Base: ID=" << id_ << ", Name=" << name_ << std::endl;
            }
            
            virtual ~Base() = default;
        };
    }
    
    namespace Graphics {
        class Window {
        private:
            int width_, height_;
            std::string title_;
            
        public:
            Window(int width, int height, const std::string& title) 
                : width_(width), height_(height), title_(title) {}
            
            void resize(int width, int height) {
                width_ = width;
                height_ = height;
            }
            
            void setTitle(const std::string& title) {
                title_ = title;
            }
            
            void display() const {
                std::cout << "Window: " << title_ << " (" << width_ << "x" << height_ << ")" << std::endl;
            }
        };
        
        class Color {
        private:
            int red_, green_, blue_;
            
        public:
            Color(int r, int g, int b) : red_(r), green_(g), blue_(b) {}
            
            void display() const {
                std::cout << "Color: RGB(" << red_ << ", " << green_ << ", " << blue_ << ")" << std::endl;
            }
        };
    }
    
    namespace Audio {
        class Sound {
        private:
            std::string filename_;
            double duration_;
            int volume_;
            
        public:
            Sound(const std::string& filename, double duration, int volume = 50) 
                : filename_(filename), duration_(duration), volume_(volume) {}
            
            void play() const {
                std::cout << "Playing: " << filename_ << " (Duration: " << duration_ << "s, Volume: " << volume_ << ")" << std::endl;
            }
            
            void setVolume(int volume) {
                volume_ = std::max(0, std::min(100, volume));
            }
        };
    }
}

// C++17 nested namespace syntax
namespace Library::Network {
    class Connection {
    private:
        std::string host_;
        int port_;
        bool connected_;
        
    public:
        Connection(const std::string& host, int port) 
            : host_(host), port_(port), connected_(false) {}
        
        bool connect() {
            connected_ = true;
            std::cout << "Connected to " << host_ << ":" << port_ << std::endl;
            return true;
        }
        
        void disconnect() {
            connected_ = false;
            std::cout << "Disconnected from " << host_ << ":" << port_ << std::endl;
        }
        
        bool isConnected() const { return connected_; }
    };
}

// Anonymous namespace for internal implementation
namespace {
    int internal_counter = 0;
    
    void increment_counter() {
        ++internal_counter;
    }
    
    int get_counter() {
        return internal_counter;
    }
    
    // Internal helper function
    bool is_valid_id(int id) {
        return id > 0;
    }
}

// Namespace with inline functions
namespace Utils {
    inline int max(int a, int b) {
        return (a > b) ? a : b;
    }
    
    inline int min(int a, int b) {
        return (a < b) ? a : b;
    }
    
    inline int clamp(int value, int min_val, int max_val) {
        return Utils::max(min_val, Utils::min(value, max_val));
    }
}

// Function to demonstrate basic namespaces
void demonstrateBasicNamespaces() {
    std::cout << "=== Basic Namespaces ===" << std::endl;
    
    // Using qualified names
    std::cout << "PI = " << Math::PI << std::endl;
    std::cout << "E = " << Math::E << std::endl;
    
    double radius = 5.0;
    std::cout << "Circle with radius " << radius << ":" << std::endl;
    std::cout << "  Area: " << Math::circle_area(radius) << std::endl;
    std::cout << "  Circumference: " << Math::circle_circumference(radius) << std::endl;
    
    // String utilities
    std::string text = "Hello World";
    std::cout << "\nString utilities for \"" << text << "\":" << std::endl;
    std::cout << "  Upper: " << StringUtils::to_upper(text) << std::endl;
    std::cout << "  Lower: " << StringUtils::to_lower(text) << std::endl;
    std::cout << "  Reverse: " << StringUtils::reverse(text) << std::endl;
    std::cout << "  Starts with 'Hello': " << (StringUtils::starts_with(text, "Hello") ? "Yes" : "No") << std::endl;
    std::cout << "  Ends with 'World': " << (StringUtils::ends_with(text, "World") ? "Yes" : "No") << std::endl;
}

// Function to demonstrate nested namespaces
void demonstrateNestedNamespaces() {
    std::cout << "\n=== Nested Namespaces ===" << std::endl;
    
    // Core namespace
    Library::Core::Base base(1, "TestBase");
    base.display();
    
    // Graphics namespace
    Library::Graphics::Window window(800, 600, "MyWindow");
    window.display();
    
    Library::Graphics::Color color(255, 128, 64);
    color.display();
    
    // Audio namespace
    Library::Audio::Sound sound("background_music.mp3", 120.5, 75);
    sound.play();
    
    // Network namespace (C++17 syntax)
    Library::Network::Connection connection("localhost", 8080);
    connection.connect();
    std::cout << "Connection status: " << (connection.isConnected() ? "Connected" : "Disconnected") << std::endl;
    connection.disconnect();
}

// Function to demonstrate namespace aliases
void demonstrateNamespaceAliases() {
    std::cout << "\n=== Namespace Aliases ===" << std::endl;
    
    // Create aliases for long namespace names
    namespace fs = std::filesystem;
    namespace chrono = std::chrono;
    
    // Use aliases
    fs::path current_path = fs::current_path();
    std::cout << "Current path: " << current_path << std::endl;
    
    auto now = chrono::system_clock::now();
    auto time_t = chrono::system_clock::to_time_t(now);
    std::cout << "Current time: " << std::ctime(&time_t);
    
    // Alias for custom namespace
    namespace MU = Math::Utils;  // Note: Math::Utils doesn't exist, this is for demonstration
    // namespace MU = Math;  // This would work
    namespace M = Math;
    
    std::cout << "Using Math alias: PI = " << M::PI << std::endl;
}

// Function to demonstrate using declarations
void demonstrateUsingDeclarations() {
    std::cout << "\n=== Using Declarations ===" << std::endl;
    
    // Selective using declarations
    using std::cout;
    using std::endl;
    using Math::PI;
    using StringUtils::to_upper;
    
    // Now we can use these without qualification
    cout << "PI = " << PI << endl;
    
    std::string text = "Hello World";
    cout << "Upper case: " << to_upper(text) << endl;
    
    // We still need to qualify other names
    cout << "Circle area: " << Math::circle_area(5.0) << endl;
    cout << "Lower case: " << StringUtils::to_lower(text) << endl;
}

// Function to demonstrate anonymous namespace
void demonstrateAnonymousNamespace() {
    std::cout << "\n=== Anonymous Namespace ===" << std::endl;
    
    // Access anonymous namespace functions
    std::cout << "Initial counter: " << get_counter() << std::endl;
    
    increment_counter();
    increment_counter();
    increment_counter();
    
    std::cout << "Counter after 3 increments: " << get_counter() << std::endl;
    
    // Test internal helper function
    std::cout << "ID 5 is valid: " << (is_valid_id(5) ? "Yes" : "No") << std::endl;
    std::cout << "ID -1 is valid: " << (is_valid_id(-1) ? "Yes" : "No") << std::endl;
    std::cout << "ID 0 is valid: " << (is_valid_id(0) ? "Yes" : "No") << std::endl;
}

// Function to demonstrate inline namespace functions
void demonstrateInlineNamespace() {
    std::cout << "\n=== Inline Namespace Functions ===" << std::endl;
    
    int a = 10, b = 20;
    
    std::cout << "max(" << a << ", " << b << ") = " << Utils::max(a, b) << std::endl;
    std::cout << "min(" << a << ", " << b << ") = " << Utils::min(a, b) << std::endl;
    
    int value = 15, min_val = 5, max_val = 25;
    std::cout << "clamp(" << value << ", " << min_val << ", " << max_val << ") = " 
              << Utils::clamp(value, min_val, max_val) << std::endl;
    
    value = 3;  // Below minimum
    std::cout << "clamp(" << value << ", " << min_val << ", " << max_val << ") = " 
              << Utils::clamp(value, min_val, max_val) << std::endl;
    
    value = 30;  // Above maximum
    std::cout << "clamp(" << value << ", " << min_val << ", " << max_val << ") = " 
              << Utils::clamp(value, min_val, max_val) << std::endl;
}

// Function to demonstrate namespace conflicts and resolution
void demonstrateNamespaceConflicts() {
    std::cout << "\n=== Namespace Conflicts and Resolution ===" << std::endl;
    
    // Create conflicting namespaces
    namespace A {
        void function() { std::cout << "A::function() called" << std::endl; }
        int value = 100;
    }
    
    namespace B {
        void function() { std::cout << "B::function() called" << std::endl; }
        int value = 200;
    }
    
    // Explicit namespace resolution
    A::function();
    B::function();
    std::cout << "A::value = " << A::value << std::endl;
    std::cout << "B::value = " << B::value << std::endl;
    
    // Using declarations for specific names
    using A::function;
    using B::value;
    
    function();  // Calls A::function
    std::cout << "B::value = " << value << std::endl;
    
    // This would cause ambiguity:
    // using A::value;
    // using B::value;
    // std::cout << value << std::endl;  // Error: ambiguous
}

// Function to demonstrate namespace organization patterns
void demonstrateNamespaceOrganization() {
    std::cout << "\n=== Namespace Organization Patterns ===" << std::endl;
    
    // Pattern 1: Feature-based organization
    namespace Database {
        namespace Connection {
            class Pool { /* ... */ };
            class Manager { /* ... */ };
        }
        
        namespace Query {
            class Builder { /* ... */ };
            class Executor { /* ... */ };
        }
        
        namespace Transaction {
            class Manager { /* ... */ };
            class Rollback { /* ... */ };
        }
    }
    
    // Pattern 2: Layer-based organization
    namespace Application {
        namespace Presentation {
            class View { /* ... */ };
            class Controller { /* ... */ };
        }
        
        namespace Business {
            class Service { /* ... */ };
            class Logic { /* ... */ };
        }
        
        namespace Data {
            class Repository { /* ... */ };
            class Entity { /* ... */ };
        }
    }
    
    std::cout << "Namespace organization patterns demonstrated" << std::endl;
    std::cout << "1. Feature-based: Database::Connection::Pool" << std::endl;
    std::cout << "2. Layer-based: Application::Business::Service" << std::endl;
}

// Function to demonstrate namespace best practices
void demonstrateNamespaceBestPractices() {
    std::cout << "\n=== Namespace Best Practices ===" << std::endl;
    
    std::cout << "Best practices for namespaces:" << std::endl;
    std::cout << "1. Use descriptive namespace names" << std::endl;
    std::cout << "2. Keep namespaces focused and cohesive" << std::endl;
    std::cout << "3. Avoid overly deep nesting" << std::endl;
    std::cout << "4. Use using declarations in implementation files, not headers" << std::endl;
    std::cout << "5. Be selective with using declarations" << std::endl;
    std::cout << "6. Use anonymous namespaces for internal implementation" << std::endl;
    std::cout << "7. Create namespace aliases for convenience" << std::endl;
    std::cout << "8. Document namespace purposes" << std::endl;
    
    // Example of good practice: selective using declarations
    using std::cout;
    using std::endl;
    using Math::PI;
    
    cout << "Example of selective using declarations:" << endl;
    cout << "PI = " << PI << endl;
    cout << "Circle area: " << Math::circle_area(3.0) << endl;  // Still qualified
}

int main() {
    std::cout << "=== Namespaces Demonstration ===" << std::endl;
    std::cout << "This program demonstrates namespace declaration, definition,\n"
              << "aliases, using declarations, and namespace organization.\n" << std::endl;
    
    // Demonstrate various namespace concepts
    demonstrateBasicNamespaces();
    demonstrateNestedNamespaces();
    demonstrateNamespaceAliases();
    demonstrateUsingDeclarations();
    demonstrateAnonymousNamespace();
    demonstrateInlineNamespace();
    demonstrateNamespaceConflicts();
    demonstrateNamespaceOrganization();
    demonstrateNamespaceBestPractices();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Namespaces organize code into logical groups" << std::endl;
    std::cout << "2. Namespaces prevent naming conflicts between libraries" << std::endl;
    std::cout << "3. Using declarations provide selective access to namespace members" << std::endl;
    std::cout << "4. Namespace aliases create convenient shortcuts for long names" << std::endl;
    std::cout << "5. Anonymous namespaces provide internal linkage" << std::endl;
    std::cout << "6. Nested namespaces allow hierarchical organization" << std::endl;
    std::cout << "7. C++17 provides concise nested namespace syntax" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o namespaces 02_Namespaces.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o namespaces 02_Namespaces.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 02_Namespaces.cpp
 * 
 * Running:
 * ./namespaces (Linux/macOS)
 * namespaces.exe (Windows)
 * 
 * Note: This lesson requires C++17 for nested namespace syntax.
 * C++11 is sufficient for basic namespace functionality.
 * 
 * Namespace Notes:
 * - Use descriptive namespace names
 * - Keep namespaces focused and cohesive
 * - Avoid using directives in headers
 * - Use selective using declarations
 * - Anonymous namespaces provide internal linkage
 * - Namespace aliases improve readability
 * - Organize code hierarchically with nested namespaces
 */"""
