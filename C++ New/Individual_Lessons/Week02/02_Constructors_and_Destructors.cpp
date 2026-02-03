/*
 * Lesson 2.2: Constructors and Destructors
 * 
 * This file demonstrates different types of constructors, destructors,
 * initialization lists, and RAII principles.
 */

#include <iostream>
#include <string>
#include <vector>

// Example 1: Basic constructor and destructor demonstration
class Person {
private:
    std::string name;
    int age;
    
public:
    // Default constructor
    Person() : name("Unknown"), age(0) {
        std::cout << "Default constructor called for " << name << std::endl;
    }
    
    // Parameterized constructor
    Person(const std::string& n, int a) : name(n), age(a) {
        std::cout << "Parameterized constructor called for " << name << std::endl;
    }
    
    // Copy constructor
    Person(const Person& other) : name(other.name), age(other.age) {
        std::cout << "Copy constructor called for " << name << std::endl;
    }
    
    // Destructor
    ~Person() {
        std::cout << "Destructor called for " << name << std::endl;
    }
    
    // Member functions
    void displayInfo() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
    
    void setName(const std::string& n) { name = n; }
    void setAge(int a) { age = a; }
    
    const std::string& getName() const { return name; }
    int getAge() const { return age; }
};

// Example 2: RAII demonstration with file management
class FileManager {
private:
    std::string filename;
    bool isOpen;
    
public:
    // Constructor opens file
    FileManager(const std::string& name) : filename(name), isOpen(true) {
        std::cout << "Opening file: " << filename << std::endl;
        // Simulate file opening
    }
    
    // Destructor closes file
    ~FileManager() {
        if (isOpen) {
            std::cout << "Closing file: " << filename << std::endl;
            isOpen = false;
        }
    }
    
    void writeData(const std::string& data) {
        if (isOpen) {
            std::cout << "Writing to " << filename << ": " << data << std::endl;
        } else {
            std::cout << "File is not open!" << std::endl;
        }
    }
    
    void closeFile() {
        if (isOpen) {
            std::cout << "Manually closing file: " << filename << std::endl;
            isOpen = false;
        }
    }
    
    const std::string& getFilename() const { return filename; }
    bool getIsOpen() const { return isOpen; }
};

// Example 3: Dynamic memory management with RAII
class DynamicArray {
private:
    int* data;
    size_t size;
    
public:
    // Constructor allocates memory
    DynamicArray(size_t s) : size(s) {
        data = new int[size];
        std::fill(data, data + size, 0);  // Initialize to zero
        std::cout << "Array created with " << size << " elements" << std::endl;
    }
    
    // Copy constructor - deep copy
    DynamicArray(const DynamicArray& other) : size(other.size) {
        data = new int[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        std::cout << "Array copied with " << size << " elements" << std::endl;
    }
    
    // Destructor frees memory
    ~DynamicArray() {
        delete[] data;
        std::cout << "Array destroyed" << std::endl;
    }
    
    // Assignment operator (for completeness)
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    // Member functions
    void setValue(size_t index, int value) {
        if (index < size) {
            data[index] = value;
        }
    }
    
    int getValue(size_t index) const {
        return (index < size) ? data[index] : -1;
    }
    
    size_t getSize() const { return size; }
    
    void display() const {
        std::cout << "Array contents: ";
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

// Example 4: Database connection simulation
class DatabaseConnection {
private:
    std::string connectionString;
    bool connected;
    int connectionId;
    
public:
    // Constructor establishes connection
    DatabaseConnection(const std::string& connStr) 
        : connectionString(connStr), connected(true), connectionId(12345) {
        std::cout << "Connected to database: " << connectionString 
                  << " (ID: " << connectionId << ")" << std::endl;
    }
    
    // Destructor closes connection
    ~DatabaseConnection() {
        if (connected) {
            std::cout << "Disconnecting from database: " << connectionString 
                      << " (ID: " << connectionId << ")" << std::endl;
            connected = false;
        }
    }
    
    // Copy constructor - new connection
    DatabaseConnection(const DatabaseConnection& other) 
        : connectionString(other.connectionString), connected(true), connectionId(67890) {
        std::cout << "New connection to database: " << connectionString 
                  << " (ID: " << connectionId << ")" << std::endl;
    }
    
    void executeQuery(const std::string& query) {
        if (connected) {
            std::cout << "Executing query: " << query << std::endl;
        } else {
            std::cout << "Not connected to database!" << std::endl;
        }
    }
    
    void disconnect() {
        if (connected) {
            std::cout << "Manually disconnecting from database: " << connectionString << std::endl;
            connected = false;
        }
    }
    
    bool isConnected() const { return connected; }
    const std::string& getConnectionString() const { return connectionString; }
    int getConnectionId() const { return connectionId; }
};

// Function to demonstrate object lifecycle
void demonstrateObjectLifecycle() {
    std::cout << "=== Object Lifecycle Demo ===" << std::endl;
    
    {
        std::cout << "\n--- Creating objects ---" << std::endl;
        Person p1;  // Default constructor
        p1.displayInfo();
        
        Person p2("Alice", 25);  // Parameterized constructor
        p2.displayInfo();
        
        Person p3 = p2;  // Copy constructor
        p3.displayInfo();
        
        std::cout << "\n--- Objects in use ---" << std::endl;
        p1.setName("Bob");
        p1.setAge(30);
        p1.displayInfo();
        
        std::cout << "\n--- Objects going out of scope ---" << std::endl;
    }  // Destructors called here when objects go out of scope
    
    std::cout << "All objects destroyed!" << std::endl;
}

// Function to demonstrate RAII with file management
void demonstrateRAIIWithFiles() {
    std::cout << "\n=== RAII File Management Demo ===" << std::endl;
    
    {
        FileManager file("data.txt");
        file.writeData("Hello, World!");
        file.writeData("This is RAII in action!");
        file.writeData("File will be closed automatically.");
        
        std::cout << "File is open: " << (file.getIsOpen() ? "Yes" : "No") << std::endl;
        
        // File automatically closed when file object goes out of scope
    }
    
    std::cout << "File management completed!" << std::endl;
}

// Function to demonstrate dynamic memory management
void demonstrateDynamicMemory() {
    std::cout << "\n=== Dynamic Memory Management Demo ===" << std::endl;
    
    {
        DynamicArray arr1(5);
        arr1.setValue(0, 10);
        arr1.setValue(1, 20);
        arr1.setValue(2, 30);
        arr1.display();
        
        std::cout << "\n--- Creating copy ---" << std::endl;
        DynamicArray arr2 = arr1;  // Copy constructor
        arr2.setValue(3, 40);
        arr2.setValue(4, 50);
        arr2.display();
        
        std::cout << "\n--- Modifying original ---" << std::endl;
        arr1.setValue(0, 100);
        arr1.display();
        arr2.display();  // Copy is independent
        
        // Arrays automatically destroyed when going out of scope
    }
    
    std::cout << "Memory management completed!" << std::endl;
}

// Function to demonstrate database connections
void demonstrateDatabaseConnections() {
    std::cout << "\n=== Database Connection Demo ===" << std::endl;
    
    {
        DatabaseConnection db1("localhost:3306/mydb");
        db1.executeQuery("SELECT * FROM users");
        db1.executeQuery("INSERT INTO users VALUES (1, 'John')");
        
        std::cout << "\n--- Creating copy connection ---" << std::endl;
        DatabaseConnection db2 = db1;  // New connection
        db2.executeQuery("SELECT * FROM orders");
        
        std::cout << "\n--- Manual disconnection ---" << std::endl;
        db1.disconnect();
        db1.executeQuery("This should fail");  // Should not work
        
        // Connections automatically closed when objects go out of scope
    }
    
    std::cout << "Database management completed!" << std::endl;
}

// Function to demonstrate constructor initialization lists
void demonstrateInitializationLists() {
    std::cout << "\n=== Initialization Lists Demo ===" << std::endl;
    
    class Rectangle {
    private:
        double width;
        double height;
        std::string name;
        
    public:
        // Constructor with initialization list
        Rectangle(double w, double h, const std::string& n) 
            : width(w), height(h), name(n) {
            std::cout << "Rectangle '" << name << "' created: " 
                      << width << " x " << height << std::endl;
        }
        
        // Default constructor with initialization list
        Rectangle() : width(1.0), height(1.0), name("Default") {
            std::cout << "Default rectangle created: " << width << " x " << height << std::endl;
        }
        
        double getArea() const { return width * height; }
        double getPerimeter() const { return 2 * (width + height); }
        
        ~Rectangle() {
            std::cout << "Rectangle '" << name << "' destroyed" << std::endl;
        }
    };
    
    Rectangle rect1(5.0, 3.0, "Rectangle 1");
    Rectangle rect2;  // Default constructor
    
    std::cout << "Area of " << rect1.getArea() << std::endl;
    std::cout << "Perimeter of " << rect1.getPerimeter() << std::endl;
}

int main() {
    std::cout << "=== C++ Constructors and Destructors Demo ===" << std::endl;
    std::cout << "This program demonstrates constructor types, destructors, and RAII.\n" << std::endl;
    
    // Demonstrate various concepts
    demonstrateObjectLifecycle();
    demonstrateRAIIWithFiles();
    demonstrateDynamicMemory();
    demonstrateDatabaseConnections();
    demonstrateInitializationLists();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Constructors initialize objects when they are created" << std::endl;
    std::cout << "2. Destructors clean up objects when they are destroyed" << std::endl;
    std::cout << "3. Initialization lists are more efficient than assignment" << std::endl;
    std::cout << "4. RAII ensures automatic resource management" << std::endl;
    std::cout << "5. Copy constructors create independent copies of objects" << std::endl;
    std::cout << "6. Objects are automatically destroyed when going out of scope" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -o constructors_destructors 02_Constructors_and_Destructors.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -o constructors_destructors 02_Constructors_and_Destructors.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc 02_Constructors_and_Destructors.cpp
 * 
 * Running:
 * ./constructors_destructors (Linux/macOS)
 * constructors_destructors.exe (Windows)
 */
