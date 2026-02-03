/*
 * OBJECT-ORIENTED PROGRAMMING (OOP) ADVANCED EXAMPLES
 * 
 * This file demonstrates advanced OOP concepts in C++:
 * - Multiple inheritance and virtual inheritance
 * - Diamond problem and its solution
 * - Move semantics (Rule of Five)
 * - RAII and smart pointers
 * - Design patterns (Factory, Singleton, Observer, Strategy)
 * - SOLID principles
 * - Template classes and generic programming
 * - Type traits and SFINAE
 * - CRTP (Curiously Recurring Template Pattern)
 * - Mixins and policy-based design
 * 
 * Learning Objectives:
 * - Master advanced inheritance techniques
 * - Implement design patterns
 * - Apply SOLID principles
 * - Use modern C++ features
 * - Write production-quality code
 * 
 * Prerequisites:
 * - Completed oop_beginner.cpp and oop_intermediate.cpp
 * - Understanding of templates
 * - Familiarity with smart pointers
 * - Knowledge of move semantics
 * 
 * Key Topics Covered:
 * - Virtual inheritance
 * - Rule of Five
 * - Design patterns
 * - SOLID principles
 * - Advanced templates
 * - Modern C++ techniques
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <algorithm>
#include <map>
using namespace std;

// ==============================================================================
// SECTION 1: MULTIPLE INHERITANCE AND DIAMOND PROBLEM
// ==============================================================================
/*
 * MULTIPLE INHERITANCE:
 * 
 * Class inherits from multiple base classes.
 * 
 * Syntax: class Derived : public Base1, public Base2 { };
 * 
 * DIAMOND PROBLEM:
 * Ambiguity when a class inherits from two classes that have a common base.
 * 
 * Solution: VIRTUAL INHERITANCE
 */

// Diamond problem example
class Device {
protected:
    string name;
    
public:
    Device(string n) : name(n) {
        cout << "   Device constructor: " << name << endl;
    }
    
    virtual void powerOn() {
        cout << "   Device powered on: " << name << endl;
    }
};

// Without virtual inheritance (BAD - creates diamond problem)
class Scanner : public Device {
public:
    Scanner(string n) : Device(n) {
        cout << "   Scanner constructor" << endl;
    }
    
    void scan() {
        cout << "   Scanning document..." << endl;
    }
};

class Printer : public Device {
public:
    Printer(string n) : Device(n) {
        cout << "   Printer constructor" << endl;
    }
    
    void print() {
        cout << "   Printing document..." << endl;
    }
};

// This would cause ambiguity
// class PrinterScanner : public Scanner, public Printer { };

// WITH VIRTUAL INHERITANCE (GOOD - solves diamond problem)
class VirtualScanner : public virtual Device {
public:
    VirtualScanner(string n) : Device(n) {
        cout << "   VirtualScanner constructor" << endl;
    }
    
    void scan() {
        cout << "   Scanning document..." << endl;
    }
};

class VirtualPrinter : public virtual Device {
public:
    VirtualPrinter(string n) : Device(n) {
        cout << "   VirtualPrinter constructor" << endl;
    }
    
    void print() {
        cout << "   Printing document..." << endl;
    }
};

class MultiFunction : public VirtualScanner, public VirtualPrinter {
public:
    MultiFunction(string n) 
        : Device(n), VirtualScanner(n), VirtualPrinter(n) {
        cout << "   MultiFunction constructor" << endl;
    }
    
    void displayInfo() {
        cout << "   Multi-function device: " << name << endl;
        powerOn();  // No ambiguity!
        scan();
        print();
    }
};

void multipleInheritanceAndDiamond() {
    cout << "=== MULTIPLE INHERITANCE AND DIAMOND PROBLEM ===" << endl << endl;
    
    cout << "1. Creating Multi-Function Device:" << endl;
    MultiFunction device("HP OfficeJet");
    cout << endl;
    
    cout << "2. Using Multi-Function Device:" << endl;
    device.displayInfo();
    cout << endl;
    
    cout << "Virtual Inheritance:" << endl;
    cout << "   ✓ Solves diamond problem" << endl;
    cout << "   ✓ Only one instance of base class" << endl;
    cout << "   ✓ No ambiguity in member access" << endl;
    cout << "   ✓ Most derived class initializes virtual base" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 2: RULE OF FIVE (C++11)
// ==============================================================================
/*
 * RULE OF FIVE:
 * 
 * If a class requires a user-defined:
 * 1. Destructor
 * 2. Copy constructor
 * 3. Copy assignment operator
 * 4. Move constructor (C++11)
 * 5. Move assignment operator (C++11)
 * 
 * Then it likely needs all five (or explicitly delete them).
 * 
 * Move semantics enables efficient transfer of resources.
 */

class Buffer {
private:
    int* data;
    size_t size;
    
public:
    // Constructor
    Buffer(size_t s) : size(s), data(new int[s]) {
        cout << "   Constructor: Buffer of size " << size << endl;
        for (size_t i = 0; i < size; i++) {
            data[i] = 0;
        }
    }
    
    // Destructor
    ~Buffer() {
        delete[] data;
        cout << "   Destructor: Buffer freed" << endl;
    }
    
    // Copy constructor (deep copy)
    Buffer(const Buffer& other) : size(other.size), data(new int[other.size]) {
        cout << "   Copy constructor (expensive)" << endl;
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }
    
    // Copy assignment operator
    Buffer& operator=(const Buffer& other) {
        cout << "   Copy assignment (expensive)" << endl;
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            for (size_t i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    // Move constructor (cheap!)
    Buffer(Buffer&& other) noexcept : size(other.size), data(other.data) {
        cout << "   Move constructor (cheap!)" << endl;
        other.data = nullptr;
        other.size = 0;
    }
    
    // Move assignment operator (cheap!)
    Buffer& operator=(Buffer&& other) noexcept {
        cout << "   Move assignment (cheap!)" << endl;
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = other.data;
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }
    
    void set(size_t index, int value) {
        if (index < size) data[index] = value;
    }
    
    size_t getSize() const { return size; }
};

Buffer createBuffer(size_t size) {
    return Buffer(size);  // Move semantics used
}

void ruleOfFive() {
    cout << "=== RULE OF FIVE ===" << endl << endl;
    
    cout << "1. Copy Semantics (expensive):" << endl;
    Buffer buf1(1000);
    Buffer buf2 = buf1;  // Copy constructor
    cout << endl;
    
    cout << "2. Move Semantics (cheap):" << endl;
    Buffer buf3 = createBuffer(1000);  // Move constructor
    Buffer buf4(500);
    buf4 = createBuffer(1000);  // Move assignment
    cout << endl;
    
    cout << "3. Explicit Move:" << endl;
    Buffer buf5(2000);
    Buffer buf6 = std::move(buf5);  // Explicit move
    cout << "   buf5 size after move: " << buf5.getSize() << endl;
    cout << "   buf6 size after move: " << buf6.getSize() << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 3: FACTORY PATTERN
// ==============================================================================
/*
 * FACTORY PATTERN:
 * 
 * Creational pattern that provides an interface for creating objects.
 * Encapsulates object creation logic.
 * 
 * Benefits:
 * - Decouples client from concrete classes
 * - Centralized object creation
 * - Easy to add new types
 * - Follows Open/Closed Principle
 */

// Product hierarchy
class Shape {
public:
    virtual void draw() const = 0;
    virtual double area() const = 0;
    virtual ~Shape() {}
};

class CircleShape : public Shape {
private:
    double radius;
    
public:
    CircleShape(double r) : radius(r) {}
    
    void draw() const override {
        cout << "   Drawing circle (radius: " << radius << ")" << endl;
    }
    
    double area() const override {
        return 3.14159 * radius * radius;
    }
};

class RectangleShape : public Shape {
private:
    double width, height;
    
public:
    RectangleShape(double w, double h) : width(w), height(h) {}
    
    void draw() const override {
        cout << "   Drawing rectangle (" << width << " x " << height << ")" << endl;
    }
    
    double area() const override {
        return width * height;
    }
};

class TriangleShape : public Shape {
private:
    double base, height;
    
public:
    TriangleShape(double b, double h) : base(b), height(h) {}
    
    void draw() const override {
        cout << "   Drawing triangle (base: " << base 
             << ", height: " << height << ")" << endl;
    }
    
    double area() const override {
        return 0.5 * base * height;
    }
};

// Factory class
class ShapeFactory {
public:
    enum ShapeType { CIRCLE, RECTANGLE, TRIANGLE };
    
    static unique_ptr<Shape> createShape(ShapeType type, double param1, double param2 = 0) {
        switch (type) {
            case CIRCLE:
                return make_unique<CircleShape>(param1);
            case RECTANGLE:
                return make_unique<RectangleShape>(param1, param2);
            case TRIANGLE:
                return make_unique<TriangleShape>(param1, param2);
            default:
                return nullptr;
        }
    }
};

void factoryPattern() {
    cout << "=== FACTORY PATTERN ===" << endl << endl;
    
    cout << "1. Creating Shapes Using Factory:" << endl;
    auto circle = ShapeFactory::createShape(ShapeFactory::CIRCLE, 5.0);
    auto rectangle = ShapeFactory::createShape(ShapeFactory::RECTANGLE, 4.0, 6.0);
    auto triangle = ShapeFactory::createShape(ShapeFactory::TRIANGLE, 3.0, 4.0);
    cout << endl;
    
    cout << "2. Using Created Shapes:" << endl;
    vector<unique_ptr<Shape>> shapes;
    shapes.push_back(move(circle));
    shapes.push_back(move(rectangle));
    shapes.push_back(move(triangle));
    
    for (const auto& shape : shapes) {
        shape->draw();
        cout << "   Area: " << shape->area() << endl;
    }
    cout << endl;
    
    cout << "Benefits:" << endl;
    cout << "   ✓ Centralized creation logic" << endl;
    cout << "   ✓ Easy to add new types" << endl;
    cout << "   ✓ Client doesn't know concrete classes" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 4: SINGLETON PATTERN
// ==============================================================================
/*
 * SINGLETON PATTERN:
 * 
 * Ensures only one instance of a class exists.
 * Provides global access point.
 * 
 * Thread-safe implementation using Meyer's Singleton.
 */

class Logger {
private:
    // Private constructor
    Logger() {
        cout << "   Logger instance created" << endl;
    }
    
    // Delete copy constructor and assignment
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
public:
    // Get singleton instance (thread-safe in C++11)
    static Logger& getInstance() {
        static Logger instance;  // Created only once
        return instance;
    }
    
    void log(const string& message) {
        cout << "   [LOG] " << message << endl;
    }
    
    void error(const string& message) {
        cout << "   [ERROR] " << message << endl;
    }
};

void singletonPattern() {
    cout << "=== SINGLETON PATTERN ===" << endl << endl;
    
    cout << "1. Getting Singleton Instance:" << endl;
    Logger& logger1 = Logger::getInstance();
    Logger& logger2 = Logger::getInstance();
    cout << "   logger1 address: " << &logger1 << endl;
    cout << "   logger2 address: " << &logger2 << endl;
    cout << "   (Same instance!)" << endl;
    cout << endl;
    
    cout << "2. Using Singleton:" << endl;
    logger1.log("Application started");
    logger2.error("An error occurred");
    cout << endl;
    
    cout << "Characteristics:" << endl;
    cout << "   ✓ Only one instance exists" << endl;
    cout << "   ✓ Global access point" << endl;
    cout << "   ✓ Thread-safe (C++11)" << endl;
    cout << "   ✗ Can make testing difficult" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 5: OBSERVER PATTERN
// ==============================================================================
/*
 * OBSERVER PATTERN:
 * 
 * Defines one-to-many dependency between objects.
 * When one object changes state, all dependents are notified.
 * 
 * Also known as: Publish-Subscribe pattern
 */

// Observer interface
class Observer {
public:
    virtual void update(const string& message) = 0;
    virtual ~Observer() {}
};

// Concrete observers
class EmailNotifier : public Observer {
private:
    string email;
    
public:
    EmailNotifier(string e) : email(e) {}
    
    void update(const string& message) override {
        cout << "   Email to " << email << ": " << message << endl;
    }
};

class SMSNotifier : public Observer {
private:
    string phone;
    
public:
    SMSNotifier(string p) : phone(p) {}
    
    void update(const string& message) override {
        cout << "   SMS to " << phone << ": " << message << endl;
    }
};

// Subject (Observable)
class NewsPublisher {
private:
    vector<Observer*> observers;
    string latestNews;
    
public:
    void attach(Observer* observer) {
        observers.push_back(observer);
        cout << "   Observer attached" << endl;
    }
    
    void detach(Observer* observer) {
        observers.erase(
            remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
        cout << "   Observer detached" << endl;
    }
    
    void setNews(const string& news) {
        latestNews = news;
        notify();
    }
    
    void notify() {
        cout << "   Notifying all observers..." << endl;
        for (auto observer : observers) {
            observer->update(latestNews);
        }
    }
};

void observerPattern() {
    cout << "=== OBSERVER PATTERN ===" << endl << endl;
    
    cout << "1. Setting Up Observers:" << endl;
    NewsPublisher publisher;
    EmailNotifier email("user@example.com");
    SMSNotifier sms("+1234567890");
    
    publisher.attach(&email);
    publisher.attach(&sms);
    cout << endl;
    
    cout << "2. Publishing News:" << endl;
    publisher.setNews("Breaking: New C++ standard released!");
    cout << endl;
    
    cout << "3. Detaching Observer:" << endl;
    publisher.detach(&sms);
    publisher.setNews("Update: Conference scheduled for next month");
    cout << endl;
    
    cout << "Benefits:" << endl;
    cout << "   ✓ Loose coupling between subject and observers" << endl;
    cout << "   ✓ Dynamic relationships" << endl;
    cout << "   ✓ Broadcast communication" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 6: STRATEGY PATTERN
// ==============================================================================
/*
 * STRATEGY PATTERN:
 * 
 * Defines family of algorithms, encapsulates each one,
 * and makes them interchangeable.
 * 
 * Algorithm varies independently from clients that use it.
 */

// Strategy interface
class SortStrategy {
public:
    virtual void sort(vector<int>& data) const = 0;
    virtual string getName() const = 0;
    virtual ~SortStrategy() {}
};

// Concrete strategies
class BubbleSort : public SortStrategy {
public:
    void sort(vector<int>& data) const override {
        size_t n = data.size();
        for (size_t i = 0; i < n - 1; i++) {
            for (size_t j = 0; j < n - i - 1; j++) {
                if (data[j] > data[j + 1]) {
                    swap(data[j], data[j + 1]);
                }
            }
        }
    }
    
    string getName() const override {
        return "Bubble Sort";
    }
};

class QuickSortStrategy : public SortStrategy {
private:
    void quickSort(vector<int>& data, int low, int high) const {
        if (low < high) {
            int pivot = data[high];
            int i = low - 1;
            
            for (int j = low; j < high; j++) {
                if (data[j] < pivot) {
                    i++;
                    swap(data[i], data[j]);
                }
            }
            swap(data[i + 1], data[high]);
            int pi = i + 1;
            
            quickSort(data, low, pi - 1);
            quickSort(data, pi + 1, high);
        }
    }
    
public:
    void sort(vector<int>& data) const override {
        if (!data.empty()) {
            quickSort(const_cast<vector<int>&>(data), 0, data.size() - 1);
        }
    }
    
    string getName() const override {
        return "Quick Sort";
    }
};

// Context class
class DataSorter {
private:
    unique_ptr<SortStrategy> strategy;
    
public:
    void setStrategy(unique_ptr<SortStrategy> s) {
        strategy = move(s);
    }
    
    void sort(vector<int>& data) {
        if (strategy) {
            cout << "   Using " << strategy->getName() << endl;
            strategy->sort(data);
        }
    }
};

void strategyPattern() {
    cout << "=== STRATEGY PATTERN ===" << endl << endl;
    
    vector<int> data1 = {64, 34, 25, 12, 22, 11, 90};
    vector<int> data2 = {64, 34, 25, 12, 22, 11, 90};
    
    DataSorter sorter;
    
    cout << "1. Using Bubble Sort Strategy:" << endl;
    sorter.setStrategy(make_unique<BubbleSort>());
    sorter.sort(data1);
    cout << "   Sorted: ";
    for (int val : data1) cout << val << " ";
    cout << endl << endl;
    
    cout << "2. Changing to Quick Sort Strategy:" << endl;
    sorter.setStrategy(make_unique<QuickSortStrategy>());
    sorter.sort(data2);
    cout << "   Sorted: ";
    for (int val : data2) cout << val << " ";
    cout << endl << endl;
    
    cout << "Benefits:" << endl;
    cout << "   ✓ Algorithms interchangeable at runtime" << endl;
    cout << "   ✓ Eliminates conditional statements" << endl;
    cout << "   ✓ Easy to add new strategies" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 7: SOLID PRINCIPLES
// ==============================================================================
/*
 * SOLID PRINCIPLES:
 * 
 * S - Single Responsibility Principle
 * O - Open/Closed Principle
 * L - Liskov Substitution Principle
 * I - Interface Segregation Principle
 * D - Dependency Inversion Principle
 */

// S - Single Responsibility Principle
class User {
private:
    string username;
    string email;
    
public:
    User(string u, string e) : username(u), email(e) {}
    string getUsername() const { return username; }
    string getEmail() const { return email; }
};

class UserRepository {
public:
    void save(const User& user) {
        cout << "   Saving user: " << user.getUsername() << endl;
    }
};

class EmailService {
public:
    void sendEmail(const User& user, const string& message) {
        cout << "   Sending email to " << user.getEmail() 
             << ": " << message << endl;
    }
};

// L - Liskov Substitution Principle
class Bird {
public:
    virtual void eat() {
        cout << "   Bird eating" << endl;
    }
    virtual ~Bird() {}
};

class FlyingBird : public Bird {
public:
    virtual void fly() {
        cout << "   Bird flying" << endl;
    }
};

class Sparrow : public FlyingBird {
public:
    void fly() override {
        cout << "   Sparrow flying" << endl;
    }
};

class Penguin : public Bird {
    // Penguin can't fly, so doesn't inherit from FlyingBird
public:
    void swim() {
        cout << "   Penguin swimming" << endl;
    }
};

// D - Dependency Inversion Principle
class IDatabase {
public:
    virtual void save(const string& data) = 0;
    virtual ~IDatabase() {}
};

class MySQLDatabase : public IDatabase {
public:
    void save(const string& data) override {
        cout << "   Saving to MySQL: " << data << endl;
    }
};

class MongoDatabase : public IDatabase {
public:
    void save(const string& data) override {
        cout << "   Saving to MongoDB: " << data << endl;
    }
};

class UserService {
private:
    IDatabase* database;  // Depend on abstraction, not concrete class
    
public:
    UserService(IDatabase* db) : database(db) {}
    
    void createUser(const string& userData) {
        cout << "   Creating user..." << endl;
        database->save(userData);
    }
};

void solidPrinciples() {
    cout << "=== SOLID PRINCIPLES ===" << endl << endl;
    
    cout << "1. Single Responsibility Principle:" << endl;
    User user("john_doe", "john@example.com");
    UserRepository repo;
    EmailService emailService;
    
    repo.save(user);
    emailService.sendEmail(user, "Welcome!");
    cout << "   (Each class has one responsibility)" << endl;
    cout << endl;
    
    cout << "2. Liskov Substitution Principle:" << endl;
    Bird* bird1 = new Sparrow();
    Bird* bird2 = new Penguin();
    
    bird1->eat();
    // Can safely call fly on FlyingBird*, but not on Bird*
    dynamic_cast<FlyingBird*>(bird1)->fly();
    
    bird2->eat();
    dynamic_cast<Penguin*>(bird2)->swim();
    
    delete bird1;
    delete bird2;
    cout << endl;
    
    cout << "3. Dependency Inversion Principle:" << endl;
    MySQLDatabase mysql;
    MongoDatabase mongo;
    
    UserService service1(&mysql);
    service1.createUser("User data 1");
    
    UserService service2(&mongo);
    service2.createUser("User data 2");
    cout << "   (Service depends on abstraction, not concrete DB)" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 8: CRTP (CURIOUSLY RECURRING TEMPLATE PATTERN)
// ==============================================================================
/*
 * CRTP:
 * 
 * Pattern where a class inherits from a template instantiated with itself.
 * 
 * class Derived : public Base<Derived> { };
 * 
 * Benefits:
 * - Static polymorphism (compile-time)
 * - No vtable overhead
 * - Can add functionality to derived classes
 */

template<typename Derived>
class Counter {
private:
    static int count;
    
protected:
    Counter() {
        ++count;
    }
    
    ~Counter() {
        --count;
    }
    
public:
    static int getCount() {
        return count;
    }
};

template<typename Derived>
int Counter<Derived>::count = 0;

class Dog : public Counter<Dog> {
public:
    void bark() { cout << "   Woof!" << endl; }
};

class Cat : public Counter<Cat> {
public:
    void meow() { cout << "   Meow!" << endl; }
};

void crtpPattern() {
    cout << "=== CRTP (Curiously Recurring Template Pattern) ===" << endl << endl;
    
    cout << "1. Creating Objects:" << endl;
    Dog d1, d2, d3;
    Cat c1, c2;
    
    cout << "   Dogs created: " << Dog::getCount() << endl;
    cout << "   Cats created: " << Cat::getCount() << endl;
    cout << endl;
    
    {
        Dog d4;
        cout << "   Dogs after creating d4: " << Dog::getCount() << endl;
    }
    cout << "   Dogs after d4 destroyed: " << Dog::getCount() << endl;
    cout << endl;
    
    cout << "Benefits:" << endl;
    cout << "   ✓ Static polymorphism (no vtable)" << endl;
    cout << "   ✓ Zero overhead" << endl;
    cout << "   ✓ Compile-time type safety" << endl;
    cout << "   ✓ Each type has its own counter" << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 9: TEMPLATE CLASS DESIGN
// ==============================================================================
/*
 * Template classes enable generic programming.
 */

template<typename T>
class Stack {
private:
    vector<T> elements;
    
public:
    void push(const T& element) {
        elements.push_back(element);
    }
    
    void pop() {
        if (!elements.empty()) {
            elements.pop_back();
        }
    }
    
    T& top() {
        if (elements.empty()) {
            throw runtime_error("Stack is empty");
        }
        return elements.back();
    }
    
    bool empty() const {
        return elements.empty();
    }
    
    size_t size() const {
        return elements.size();
    }
};

void templateClassDesign() {
    cout << "=== TEMPLATE CLASS DESIGN ===" << endl << endl;
    
    cout << "1. Stack of Integers:" << endl;
    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    
    cout << "   Top: " << intStack.top() << endl;
    cout << "   Size: " << intStack.size() << endl;
    intStack.pop();
    cout << "   After pop, top: " << intStack.top() << endl;
    cout << endl;
    
    cout << "2. Stack of Strings:" << endl;
    Stack<string> stringStack;
    stringStack.push("Hello");
    stringStack.push("World");
    
    cout << "   Top: " << stringStack.top() << endl;
    cout << "   Size: " << stringStack.size() << endl;
    cout << endl;
}

// ==============================================================================
// SECTION 10: BEST PRACTICES
// ==============================================================================

void bestPractices() {
    cout << "=== OOP ADVANCED BEST PRACTICES ===" << endl << endl;
    
    cout << "Design Patterns:" << endl;
    cout << "   ✓ Use patterns to solve common problems" << endl;
    cout << "   ✓ Don't force patterns where not needed" << endl;
    cout << "   ✓ Understand trade-offs of each pattern" << endl;
    cout << "   ✓ Combine patterns when appropriate" << endl;
    cout << endl;
    
    cout << "SOLID Principles:" << endl;
    cout << "   ✓ Single Responsibility - one reason to change" << endl;
    cout << "   ✓ Open/Closed - open for extension, closed for modification" << endl;
    cout << "   ✓ Liskov Substitution - subtypes must be substitutable" << endl;
    cout << "   ✓ Interface Segregation - many specific interfaces" << endl;
    cout << "   ✓ Dependency Inversion - depend on abstractions" << endl;
    cout << endl;
    
    cout << "Modern C++:" << endl;
    cout << "   ✓ Use smart pointers (unique_ptr, shared_ptr)" << endl;
    cout << "   ✓ Follow Rule of Five (or Rule of Zero)" << endl;
    cout << "   ✓ Use move semantics for efficiency" << endl;
    cout << "   ✓ Prefer noexcept for move operations" << endl;
    cout << "   ✓ Use RAII for resource management" << endl;
    cout << endl;
    
    cout << "Templates:" << endl;
    cout << "   ✓ Use templates for generic programming" << endl;
    cout << "   ✓ Consider CRTP for static polymorphism" << endl;
    cout << "   ✓ Provide clear error messages" << endl;
    cout << "   ✓ Document template requirements" << endl;
    cout << endl;
    
    cout << "General:" << endl;
    cout << "   ✓ Prefer composition over inheritance" << endl;
    cout << "   ✓ Program to interfaces, not implementations" << endl;
    cout << "   ✓ Keep inheritance hierarchies shallow" << endl;
    cout << "   ✓ Use virtual inheritance to solve diamond problem" << endl;
    cout << "   ✓ Make destructors virtual in polymorphic base classes" << endl;
    cout << "   ✓ Write testable, maintainable code" << endl;
    cout << endl;
}

// ==============================================================================
// MAIN FUNCTION - RUNS ALL EXAMPLES
// ==============================================================================

int main() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║          OOP ADVANCED TUTORIAL - C++                       ║" << endl;
    cout << "║                                                            ║" << endl;
    cout << "║  Master advanced OOP techniques and design patterns        ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    cout << "\n";
    
    multipleInheritanceAndDiamond();
    ruleOfFive();
    factoryPattern();
    singletonPattern();
    observerPattern();
    strategyPattern();
    solidPrinciples();
    crtpPattern();
    templateClassDesign();
    bestPractices();
    
    cout << "╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║  End of OOP Advanced Tutorial                              ║" << endl;
    cout << "║                                                            ║" << endl;
    cout << "║  You now have mastery of Object-Oriented Programming!      ║" << endl;
    cout << "║  Apply these concepts to build robust applications.        ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;
    
    return 0;
}

