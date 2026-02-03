/*
 * OBJECT-ORIENTED PROGRAMMING (OOP) BEGINNER EXAMPLES
 * 
 * This file demonstrates basic OOP concepts in C++:
 * - What is OOP and why use it?
 * - Classes and objects
 * - Data members and member functions
 * - Constructors and destructors
 * - Access specifiers (public, private, protected)
 * - Encapsulation
 * - The 'this' pointer
 * - Static members
 * - Const member functions
 * - Friend functions
 * 
 * Learning Objectives:
 * - Understand OOP fundamentals
 * - Create classes and objects
 * - Use constructors and destructors properly
 * - Implement encapsulation
 * - Work with member functions
 * 
 * Prerequisites:
 * - Basic C++ syntax knowledge
 * - Understanding of functions
 * - Familiarity with data types
 * 
 * Key Topics Covered:
 * - Class definition
 * - Object creation
 * - Constructors/destructors
 * - Access control
 * - Member functions
 * - Static members
 */

#include <iostream>
#include <string>
using namespace std;

// ==============================================================================
// SECTION 1: WHAT IS OOP?
// ==============================================================================
/*
 * OBJECT-ORIENTED PROGRAMMING (OOP):
 * 
 * A programming paradigm based on "objects" that contain:
 * - Data (attributes/properties)
 * - Code (methods/functions)
 * 
 * Four Pillars of OOP:
 * 1. ENCAPSULATION - Bundling data and methods together
 * 2. ABSTRACTION - Hiding complex implementation details
 * 3. INHERITANCE - Creating new classes from existing ones
 * 4. POLYMORPHISM - One interface, multiple implementations
 * 
 * Benefits:
 * ✓ Code reusability
 * ✓ Modularity
 * ✓ Data hiding and security
 * ✓ Easy maintenance
 * ✓ Real-world modeling
 * 
 * Procedural vs OOP:
 * Procedural: Functions + Data (separate)
 * OOP: Objects = Data + Functions (together)
 */

void whatIsOOP() {
    cout << "=== WHAT IS OOP? ===" << endl << endl;
    
    cout << "Four Pillars of OOP:" << endl;
    cout << "   1. Encapsulation - Bundle data and methods" << endl;
    cout << "   2. Abstraction - Hide complexity" << endl;
    cout << "   3. Inheritance - Reuse code" << endl;
    cout << "   4. Polymorphism - Flexible interfaces" << endl;
    cout << endl;
    
    cout << "Real-world analogy:" << endl;
    cout << "   A CAR is an object with:" << endl;
    cout << "   - Properties: color, speed, model" << endl;
    cout << "   - Methods: accelerate(), brake(), turn()" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 2: BASIC CLASS AND OBJECT
// ==============================================================================
/*
 * CLASS:
 * A blueprint/template for creating objects.
 * Defines properties (data members) and behaviors (member functions).
 * 
 * OBJECT:
 * An instance of a class.
 * Actual entity created from the class blueprint.
 * 
 * Syntax:
 * class ClassName {
 *     // members
 * };
 * 
 * Creating objects:
 * ClassName objectName;
 */

// Simple class example
class Dog {
public:
    // Data members (properties/attributes)
    string name;
    string breed;
    int age;
    
    // Member function (method/behavior)
    void bark() {
        cout << "   " << name << " says: Woof! Woof!" << endl;
    }
    
    void displayInfo() {
        cout << "   Name: " << name << endl;
        cout << "   Breed: " << breed << endl;
        cout << "   Age: " << age << " years" << endl;
    }
};

void basicClassAndObject() {
    cout << "=== BASIC CLASS AND OBJECT ===" << endl << endl;
    
    // Creating objects (instances of Dog class)
    cout << "1. Creating Objects:" << endl;
    Dog dog1;  // Object 1
    Dog dog2;  // Object 2
    
    // Setting properties for dog1
    dog1.name = "Buddy";
    dog1.breed = "Golden Retriever";
    dog1.age = 3;
    
    // Setting properties for dog2
    dog2.name = "Max";
    dog2.breed = "German Shepherd";
    dog2.age = 5;
    
    // Calling member functions
    cout << endl << "Dog 1:" << endl;
    dog1.displayInfo();
    dog1.bark();
    
    cout << endl << "Dog 2:" << endl;
    dog2.displayInfo();
    dog2.bark();
    cout << endl;
}

// ==============================================================================
// SECTION 3: ACCESS SPECIFIERS
// ==============================================================================
/*
 * ACCESS SPECIFIERS:
 * 
 * Control access to class members from outside the class.
 * 
 * 1. PUBLIC:
 *    - Accessible from anywhere
 *    - Can be accessed by objects directly
 * 
 * 2. PRIVATE:
 *    - Accessible only within the class
 *    - Default for class members
 *    - Implements data hiding
 * 
 * 3. PROTECTED:
 *    - Accessible within class and derived classes
 *    - Used in inheritance
 */

class BankAccount {
public:
    // Public members - accessible from outside
    string accountHolder;
    
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "   Deposited: $" << amount << endl;
        }
    }
    
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "   Withdrawn: $" << amount << endl;
        } else {
            cout << "   Insufficient funds!" << endl;
        }
    }
    
    double getBalance() const {
        return balance;
    }
    
private:
    // Private members - only accessible within class
    double balance = 0.0;
    string accountNumber = "ACC123456";
    
    // Private helper function
    void logTransaction(string type, double amount) {
        cout << "   [LOG] " << type << ": $" << amount << endl;
    }
};

void accessSpecifiers() {
    cout << "=== ACCESS SPECIFIERS ===" << endl << endl;
    
    BankAccount account;
    account.accountHolder = "John Doe";  // Public - OK
    
    // account.balance = 1000000;  // ERROR! Private member
    // account.accountNumber = "HACK";  // ERROR! Private member
    
    cout << "Using public methods to access private data:" << endl;
    account.deposit(1000);
    account.withdraw(200);
    cout << "   Balance: $" << account.getBalance() << endl;
    cout << endl;
    
    cout << "Why use private members?" << endl;
    cout << "   ✓ Data hiding (encapsulation)" << endl;
    cout << "   ✓ Validation and control" << endl;
    cout << "   ✓ Prevent unauthorized access" << endl;
    cout << "   ✓ Easy to maintain and modify" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 4: CONSTRUCTORS
// ==============================================================================
/*
 * CONSTRUCTOR:
 * 
 * Special member function that:
 * - Has same name as class
 * - No return type (not even void)
 * - Automatically called when object is created
 * - Used to initialize object
 * 
 * Types:
 * 1. Default constructor - no parameters
 * 2. Parameterized constructor - with parameters
 * 3. Copy constructor - creates copy of object
 */

class Student {
private:
    string name;
    int rollNumber;
    float gpa;
    
public:
    // Default constructor
    Student() {
        name = "Unknown";
        rollNumber = 0;
        gpa = 0.0;
        cout << "   Default constructor called" << endl;
    }
    
    // Parameterized constructor
    Student(string n, int roll, float g) {
        name = n;
        rollNumber = roll;
        gpa = g;
        cout << "   Parameterized constructor called for " << name << endl;
    }
    
    // Constructor with default parameters
    Student(string n, int roll = 0) {
        name = n;
        rollNumber = roll;
        gpa = 0.0;
        cout << "   Constructor with defaults called for " << name << endl;
    }
    
    void displayInfo() const {
        cout << "   Name: " << name << ", Roll: " << rollNumber 
             << ", GPA: " << gpa << endl;
    }
};

void constructors() {
    cout << "=== CONSTRUCTORS ===" << endl << endl;
    
    // Using default constructor
    cout << "1. Default Constructor:" << endl;
    Student student1;
    student1.displayInfo();
    cout << endl;
    
    // Using parameterized constructor
    cout << "2. Parameterized Constructor:" << endl;
    Student student2("Alice", 101, 3.8);
    student2.displayInfo();
    cout << endl;
    
    // Using constructor with defaults
    cout << "3. Constructor with Defaults:" << endl;
    Student student3("Bob", 102);
    student3.displayInfo();
    cout << endl;
}

// ==============================================================================
// SECTION 5: DESTRUCTORS
// ==============================================================================
/*
 * DESTRUCTOR:
 * 
 * Special member function that:
 * - Has same name as class with ~ prefix
 * - No return type and no parameters
 * - Automatically called when object is destroyed
 * - Used to clean up resources
 * - Only one destructor per class
 * 
 * When called:
 * - Object goes out of scope
 * - Program ends
 * - delete is called on pointer to object
 */

class Resource {
private:
    string resourceName;
    int* data;
    
public:
    // Constructor
    Resource(string name) : resourceName(name) {
        data = new int[100];  // Allocate memory
        cout << "   Constructor: Resource '" << resourceName << "' created" << endl;
    }
    
    // Destructor
    ~Resource() {
        delete[] data;  // Free memory
        cout << "   Destructor: Resource '" << resourceName << "' destroyed" << endl;
    }
    
    void useResource() {
        cout << "   Using resource: " << resourceName << endl;
    }
};

void destructors() {
    cout << "=== DESTRUCTORS ===" << endl << endl;
    
    cout << "Creating and destroying resources:" << endl;
    {
        Resource res1("File1");
        Resource res2("File2");
        res1.useResource();
        res2.useResource();
        // Destructors automatically called when exiting this scope
    }
    cout << "   (Scope exited, destructors called automatically)" << endl;
    cout << endl;
    
    cout << "Why destructors are important:" << endl;
    cout << "   ✓ Automatic cleanup" << endl;
    cout << "   ✓ Prevent memory leaks" << endl;
    cout << "   ✓ Close files/connections" << endl;
    cout << "   ✓ Release system resources" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 6: ENCAPSULATION
// ==============================================================================
/*
 * ENCAPSULATION:
 * 
 * Bundling data and methods that operate on data within a single unit (class).
 * Hiding internal details and providing public interface.
 * 
 * Implementation:
 * - Make data members private
 * - Provide public getter/setter methods
 * 
 * Benefits:
 * - Data protection
 * - Flexibility to change implementation
 * - Validation and control
 * - Loose coupling
 */

class Temperature {
private:
    double celsius;
    
    // Private helper method
    bool isValidTemperature(double temp) const {
        return temp >= -273.15;  // Absolute zero
    }
    
public:
    // Constructor
    Temperature(double temp = 0.0) {
        setCelsius(temp);
    }
    
    // Getter (accessor)
    double getCelsius() const {
        return celsius;
    }
    
    // Setter (mutator) with validation
    void setCelsius(double temp) {
        if (isValidTemperature(temp)) {
            celsius = temp;
        } else {
            celsius = -273.15;  // Set to absolute zero
            cout << "   Warning: Invalid temperature, set to absolute zero" << endl;
        }
    }
    
    // Convert to Fahrenheit
    double toFahrenheit() const {
        return (celsius * 9.0 / 5.0) + 32.0;
    }
    
    // Convert to Kelvin
    double toKelvin() const {
        return celsius + 273.15;
    }
    
    void display() const {
        cout << "   Temperature: " << celsius << "°C / "
             << toFahrenheit() << "°F / "
             << toKelvin() << "K" << endl;
    }
};

void encapsulation() {
    cout << "=== ENCAPSULATION ===" << endl << endl;
    
    cout << "1. Creating Temperature Object:" << endl;
    Temperature temp(25.0);
    temp.display();
    cout << endl;
    
    cout << "2. Using Setters with Validation:" << endl;
    temp.setCelsius(100.0);
    cout << "   Set to 100°C" << endl;
    temp.display();
    cout << endl;
    
    cout << "3. Invalid Temperature (below absolute zero):" << endl;
    temp.setCelsius(-300.0);  // Invalid!
    temp.display();
    cout << endl;
    
    cout << "Benefits of Encapsulation:" << endl;
    cout << "   ✓ Data validation (prevented invalid temperature)" << endl;
    cout << "   ✓ Controlled access through methods" << endl;
    cout << "   ✓ Can change internal representation without affecting users" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 7: THE 'THIS' POINTER
// ==============================================================================
/*
 * THE 'THIS' POINTER:
 * 
 * - Special pointer available in member functions
 * - Points to the object that called the function
 * - Automatically passed to member functions
 * 
 * Uses:
 * - Resolve naming conflicts
 * - Return current object
 * - Pass object to other functions
 * - Check self-assignment
 */

class Person {
private:
    string name;
    int age;
    
public:
    // Using 'this' to resolve naming conflict
    Person(string name, int age) {
        this->name = name;  // this->name is member, name is parameter
        this->age = age;
    }
    
    // Returning *this for method chaining
    Person& setName(string name) {
        this->name = name;
        return *this;  // Return reference to current object
    }
    
    Person& setAge(int age) {
        this->age = age;
        return *this;
    }
    
    void displayInfo() const {
        cout << "   Name: " << name << ", Age: " << age << endl;
    }
    
    // Comparing with another Person
    bool isOlderThan(const Person& other) const {
        return this->age > other.age;
    }
};

void thisPointer() {
    cout << "=== THE 'THIS' POINTER ===" << endl << endl;
    
    // Using 'this' in constructor
    cout << "1. Using 'this' to Resolve Name Conflicts:" << endl;
    Person person1("Alice", 25);
    person1.displayInfo();
    cout << endl;
    
    // Method chaining using 'this'
    cout << "2. Method Chaining (using return *this):" << endl;
    Person person2("Unknown", 0);
    person2.setName("Bob").setAge(30);  // Chaining!
    person2.displayInfo();
    cout << endl;
    
    // Using 'this' for comparison
    cout << "3. Using 'this' in Comparisons:" << endl;
    if (person2.isOlderThan(person1)) {
        cout << "   Bob is older than Alice" << endl;
    }
    cout << endl;
}

// ==============================================================================
// SECTION 8: STATIC MEMBERS
// ==============================================================================
/*
 * STATIC MEMBERS:
 * 
 * Static Data Members:
 * - Shared by ALL objects of the class
 * - Only one copy exists for entire class
 * - Must be initialized outside class
 * 
 * Static Member Functions:
 * - Can be called without creating object
 * - Can only access static members
 * - No 'this' pointer
 */

class Counter {
private:
    static int objectCount;  // Static data member (declaration)
    int id;
    
public:
    Counter() {
        id = ++objectCount;  // Increment shared counter
        cout << "   Object " << id << " created. Total objects: " 
             << objectCount << endl;
    }
    
    ~Counter() {
        objectCount--;
        cout << "   Object " << id << " destroyed. Total objects: " 
             << objectCount << endl;
    }
    
    // Static member function
    static int getObjectCount() {
        return objectCount;  // Can only access static members
    }
    
    int getId() const {
        return id;
    }
};

// Static member initialization (must be outside class)
int Counter::objectCount = 0;

void staticMembers() {
    cout << "=== STATIC MEMBERS ===" << endl << endl;
    
    // Call static function without object
    cout << "1. Initial Count (using static function):" << endl;
    cout << "   Object count: " << Counter::getObjectCount() << endl;
    cout << endl;
    
    // Create objects
    cout << "2. Creating Objects:" << endl;
    {
        Counter c1;
        Counter c2;
        Counter c3;
        cout << "   Total objects: " << Counter::getObjectCount() << endl;
    }
    
    cout << "3. After Scope Exit:" << endl;
    cout << "   Total objects: " << Counter::getObjectCount() << endl;
    cout << endl;
    
    cout << "Key Points:" << endl;
    cout << "   ✓ Static members shared by all objects" << endl;
    cout << "   ✓ Static functions can be called without object" << endl;
    cout << "   ✓ Static members initialized once" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 9: CONST MEMBER FUNCTIONS
// ==============================================================================
/*
 * CONST MEMBER FUNCTIONS:
 * 
 * - Marked with 'const' keyword after parameter list
 * - Guarantees function won't modify object
 * - Can be called on const objects
 * - Can only call other const functions
 * 
 * Syntax: returnType functionName() const { }
 * 
 * Good practice: Mark all functions that don't modify object as const
 */

class Rectangle {
private:
    double width;
    double height;
    
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    
    // Const member functions (don't modify object)
    double getWidth() const {
        return width;
    }
    
    double getHeight() const {
        return height;
    }
    
    double calculateArea() const {
        return width * height;
    }
    
    double calculatePerimeter() const {
        return 2 * (width + height);
    }
    
    void display() const {
        cout << "   Rectangle: " << width << " x " << height << endl;
        cout << "   Area: " << calculateArea() << endl;
        cout << "   Perimeter: " << calculatePerimeter() << endl;
    }
    
    // Non-const member function (modifies object)
    void setDimensions(double w, double h) {
        width = w;
        height = h;
    }
};

void printRectangle(const Rectangle& rect) {
    // Can only call const functions on const object
    cout << "   Width: " << rect.getWidth() << endl;
    cout << "   Height: " << rect.getHeight() << endl;
    cout << "   Area: " << rect.calculateArea() << endl;
}

void constMemberFunctions() {
    cout << "=== CONST MEMBER FUNCTIONS ===" << endl << endl;
    
    cout << "1. Using Const Member Functions:" << endl;
    Rectangle rect(5.0, 3.0);
    rect.display();
    cout << endl;
    
    cout << "2. Const Object Can Only Call Const Functions:" << endl;
    const Rectangle constRect(10.0, 4.0);
    // constRect.setDimensions(8.0, 6.0);  // ERROR! Non-const function
    cout << "   Area: " << constRect.calculateArea() << endl;  // OK - const function
    cout << endl;
    
    cout << "3. Passing to Function Taking Const Reference:" << endl;
    printRectangle(rect);
    cout << endl;
    
    cout << "Benefits:" << endl;
    cout << "   ✓ Compiler enforces const-correctness" << endl;
    cout << "   ✓ Documents function intent" << endl;
    cout << "   ✓ Enables optimization" << endl;
    cout << "   ✓ Works with const objects" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 10: FRIEND FUNCTIONS
// ==============================================================================
/*
 * FRIEND FUNCTIONS:
 * 
 * - Not member functions but can access private/protected members
 * - Declared in class with 'friend' keyword
 * - Defined outside class (like normal function)
 * 
 * Uses:
 * - Operator overloading
 * - Functions that need access to multiple classes
 * - Breaking encapsulation when necessary
 * 
 * Note: Use sparingly - breaks encapsulation!
 */

class Box {
private:
    double length;
    double width;
    double height;
    
public:
    Box(double l, double w, double h) : length(l), width(w), height(h) {}
    
    double getVolume() const {
        return length * width * height;
    }
    
    void display() const {
        cout << "   Box: " << length << " x " << width << " x " 
             << height << endl;
    }
    
    // Friend function declaration
    friend void compareBoxes(const Box& box1, const Box& box2);
    friend double getTotalVolume(const Box& box1, const Box& box2);
};

// Friend function definition (can access private members)
void compareBoxes(const Box& box1, const Box& box2) {
    // Can directly access private members
    cout << "   Box 1 dimensions: " << box1.length << " x " 
         << box1.width << " x " << box1.height << endl;
    cout << "   Box 2 dimensions: " << box2.length << " x " 
         << box2.width << " x " << box2.height << endl;
    
    if (box1.getVolume() > box2.getVolume()) {
        cout << "   Box 1 is larger" << endl;
    } else {
        cout << "   Box 2 is larger" << endl;
    }
}

double getTotalVolume(const Box& box1, const Box& box2) {
    return (box1.length * box1.width * box1.height) +
           (box2.length * box2.width * box2.height);
}

void friendFunctions() {
    cout << "=== FRIEND FUNCTIONS ===" << endl << endl;
    
    Box box1(3.0, 4.0, 5.0);
    Box box2(2.0, 3.0, 4.0);
    
    cout << "1. Displaying Boxes:" << endl;
    box1.display();
    box2.display();
    cout << endl;
    
    cout << "2. Using Friend Function to Compare:" << endl;
    compareBoxes(box1, box2);
    cout << endl;
    
    cout << "3. Using Friend Function to Calculate Total Volume:" << endl;
    cout << "   Total volume: " << getTotalVolume(box1, box2) << endl;
    cout << endl;
    
    cout << "Note on Friend Functions:" << endl;
    cout << "   ✓ Can access private members" << endl;
    cout << "   ✓ Not member functions" << endl;
    cout << "   ✗ Break encapsulation" << endl;
    cout << "   ✗ Use sparingly" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 11: PRACTICAL EXAMPLE - COMPLETE CLASS
// ==============================================================================
/*
 * Complete practical example demonstrating all concepts
 */

class BankAccountComplete {
private:
    static int nextAccountNumber;
    int accountNumber;
    string accountHolder;
    double balance;
    
    // Private helper
    bool isValidAmount(double amount) const {
        return amount > 0;
    }
    
public:
    // Constructor
    BankAccountComplete(string holder, double initialBalance = 0.0) 
        : accountHolder(holder) {
        accountNumber = nextAccountNumber++;
        balance = (initialBalance >= 0) ? initialBalance : 0.0;
        cout << "   Account " << accountNumber << " created for " 
             << accountHolder << endl;
    }
    
    // Destructor
    ~BankAccountComplete() {
        cout << "   Account " << accountNumber << " closed" << endl;
    }
    
    // Getters (const)
    int getAccountNumber() const { return accountNumber; }
    string getAccountHolder() const { return accountHolder; }
    double getBalance() const { return balance; }
    
    // Methods with validation
    bool deposit(double amount) {
        if (isValidAmount(amount)) {
            balance += amount;
            cout << "   Deposited $" << amount << " to account " 
                 << accountNumber << endl;
            return true;
        }
        return false;
    }
    
    bool withdraw(double amount) {
        if (isValidAmount(amount) && amount <= balance) {
            balance -= amount;
            cout << "   Withdrawn $" << amount << " from account " 
                 << accountNumber << endl;
            return true;
        }
        cout << "   Withdrawal failed!" << endl;
        return false;
    }
    
    void displayInfo() const {
        cout << "   Account #" << accountNumber << endl;
        cout << "   Holder: " << accountHolder << endl;
        cout << "   Balance: $" << balance << endl;
    }
    
    // Static function
    static int getTotalAccounts() {
        return nextAccountNumber - 1;
    }
};

int BankAccountComplete::nextAccountNumber = 1000;

void practicalExample() {
    cout << "=== PRACTICAL EXAMPLE - BANK ACCOUNT ===" << endl << endl;
    
    cout << "1. Creating Accounts:" << endl;
    BankAccountComplete acc1("Alice Smith", 1000.0);
    BankAccountComplete acc2("Bob Johnson", 500.0);
    cout << "   Total accounts: " << BankAccountComplete::getTotalAccounts() << endl;
    cout << endl;
    
    cout << "2. Account Operations:" << endl;
    acc1.deposit(500.0);
    acc1.withdraw(200.0);
    acc1.displayInfo();
    cout << endl;
    
    acc2.deposit(300.0);
    acc2.withdraw(1000.0);  // Will fail
    acc2.displayInfo();
    cout << endl;
}

// ==============================================================================
// SECTION 12: BEST PRACTICES
// ==============================================================================

void bestPractices() {
    cout << "=== OOP BEST PRACTICES ===" << endl << endl;
    
    cout << "Class Design:" << endl;
    cout << "   ✓ One class, one responsibility" << endl;
    cout << "   ✓ Make data members private" << endl;
    cout << "   ✓ Provide public interface through methods" << endl;
    cout << "   ✓ Use meaningful names" << endl;
    cout << endl;
    
    cout << "Constructors:" << endl;
    cout << "   ✓ Initialize all data members" << endl;
    cout << "   ✓ Use initialization lists" << endl;
    cout << "   ✓ Validate parameters" << endl;
    cout << "   ✓ Provide default constructor when needed" << endl;
    cout << endl;
    
    cout << "Member Functions:" << endl;
    cout << "   ✓ Mark const functions as const" << endl;
    cout << "   ✓ Keep functions focused and small" << endl;
    cout << "   ✓ Validate input in setters" << endl;
    cout << "   ✓ Return references for chaining" << endl;
    cout << endl;
    
    cout << "Encapsulation:" << endl;
    cout << "   ✓ Hide implementation details" << endl;
    cout << "   ✓ Provide controlled access" << endl;
    cout << "   ✓ Use getters/setters appropriately" << endl;
    cout << "   ✓ Keep data members private" << endl;
    cout << endl;
    
    cout << "General:" << endl;
    cout << "   ✓ Write destructors for resource cleanup" << endl;
    cout << "   ✓ Use static members for class-wide data" << endl;
    cout << "   ✓ Document public interface" << endl;
    cout << "   ✓ Follow naming conventions" << endl;
    cout << endl;
}

// ==============================================================================
// MAIN FUNCTION - RUNS ALL EXAMPLES
// ==============================================================================

int main() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║           OOP BEGINNER TUTORIAL - C++                      ║" << endl;
    cout << "║                                                            ║" << endl;
    cout << "║  Learn Object-Oriented Programming fundamentals            ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    cout << "\n";
    
    whatIsOOP();
    basicClassAndObject();
    accessSpecifiers();
    constructors();
    destructors();
    encapsulation();
    thisPointer();
    staticMembers();
    constMemberFunctions();
    friendFunctions();
    practicalExample();
    bestPractices();
    
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║  End of OOP Beginner Tutorial                              ║" << endl;
    cout << "║  Next: Move on to oop_intermediate.cpp                     ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    
    return 0;
}

