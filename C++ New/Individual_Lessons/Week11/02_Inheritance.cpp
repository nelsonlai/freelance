/*
 * Lesson 11.2: Inheritance
 * 
 * This file demonstrates base and derived class relationships,
 * virtual functions, polymorphism, abstract classes, and inheritance patterns.
 */

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <cmath>

// Example 1: Basic Inheritance - Animal Hierarchy
class Animal {
protected:
    std::string name_;
    int age_;
    double weight_;
    
public:
    Animal(const std::string& name, int age, double weight = 0.0)
        : name_(name), age_(age), weight_(weight) {}
    
    virtual ~Animal() = default;
    
    // Virtual functions for polymorphism
    virtual void makeSound() const {
        std::cout << name_ << " makes a generic animal sound" << std::endl;
    }
    
    virtual void move() const {
        std::cout << name_ << " moves in a generic way" << std::endl;
    }
    
    virtual void eat() const {
        std::cout << name_ << " is eating" << std::endl;
    }
    
    virtual void sleep() const {
        std::cout << name_ << " is sleeping" << std::endl;
    }
    
    virtual void displayInfo() const {
        std::cout << "Animal: " << name_ << ", Age: " << age_ 
                  << ", Weight: " << weight_ << " kg" << std::endl;
    }
    
    // Non-virtual function
    void breathe() const {
        std::cout << name_ << " is breathing" << std::endl;
    }
    
    // Getters
    const std::string& getName() const { return name_; }
    int getAge() const { return age_; }
    double getWeight() const { return weight_; }
    
    // Setters
    void setWeight(double weight) { weight_ = weight; }
};

// Derived class - Dog
class Dog : public Animal {
private:
    std::string breed_;
    bool is_trained_;
    
public:
    Dog(const std::string& name, int age, double weight, 
        const std::string& breed, bool trained = false)
        : Animal(name, age, weight), breed_(breed), is_trained_(trained) {}
    
    // Override virtual functions
    void makeSound() const override {
        std::cout << name_ << " barks: Woof! Woof!" << std::endl;
    }
    
    void move() const override {
        std::cout << name_ << " runs on four legs" << std::endl;
    }
    
    void eat() const override {
        std::cout << name_ << " eats dog food" << std::endl;
    }
    
    void displayInfo() const override {
        Animal::displayInfo();
        std::cout << "Breed: " << breed_ << ", Trained: " 
                  << (is_trained_ ? "Yes" : "No") << std::endl;
    }
    
    // Dog-specific methods
    void fetch() const {
        std::cout << name_ << " is fetching the ball" << std::endl;
    }
    
    void sit() const {
        if (is_trained_) {
            std::cout << name_ << " sits on command" << std::endl;
        } else {
            std::cout << name_ << " needs more training" << std::endl;
        }
    }
    
    void wagTail() const {
        std::cout << name_ << " is wagging its tail happily" << std::endl;
    }
    
    // Getters
    const std::string& getBreed() const { return breed_; }
    bool isTrained() const { return is_trained_; }
    
    // Setters
    void setTrained(bool trained) { is_trained_ = trained; }
};

// Derived class - Cat
class Cat : public Animal {
private:
    std::string color_;
    bool is_indoor_;
    
public:
    Cat(const std::string& name, int age, double weight,
        const std::string& color, bool indoor = true)
        : Animal(name, age, weight), color_(color), is_indoor_(indoor) {}
    
    // Override virtual functions
    void makeSound() const override {
        std::cout << name_ << " meows: Meow! Meow!" << std::endl;
    }
    
    void move() const override {
        std::cout << name_ << " moves gracefully on four legs" << std::endl;
    }
    
    void eat() const override {
        std::cout << name_ << " eats cat food" << std::endl;
    }
    
    void displayInfo() const override {
        Animal::displayInfo();
        std::cout << "Color: " << color_ << ", Indoor: " 
                  << (is_indoor_ ? "Yes" : "No") << std::endl;
    }
    
    // Cat-specific methods
    void purr() const {
        std::cout << name_ << " is purring contentedly" << std::endl;
    }
    
    void climb() const {
        std::cout << name_ << " is climbing" << std::endl;
    }
    
    void hunt() const {
        if (is_indoor_) {
            std::cout << name_ << " hunts toy mice" << std::endl;
        } else {
            std::cout << name_ << " hunts real mice" << std::endl;
        }
    }
    
    // Getters
    const std::string& getColor() const { return color_; }
    bool isIndoor() const { return is_indoor_; }
    
    // Setters
    void setIndoor(bool indoor) { is_indoor_ = indoor; }
};

// Example 2: Abstract Base Class - Shape
class Shape {
protected:
    double area_;
    double perimeter_;
    
public:
    Shape() : area_(0.0), perimeter_(0.0) {}
    virtual ~Shape() = default;
    
    // Pure virtual functions (makes class abstract)
    virtual double calculateArea() = 0;
    virtual double calculatePerimeter() = 0;
    
    // Virtual function with default implementation
    virtual void display() const {
        std::cout << "Shape - Area: " << area_ << ", Perimeter: " << perimeter_ << std::endl;
    }
    
    // Non-virtual function
    void printInfo() const {
        std::cout << "Area: " << area_ << ", Perimeter: " << perimeter_ << std::endl;
    }
    
    // Getters
    double getArea() const { return area_; }
    double getPerimeter() const { return perimeter_; }
};

// Concrete derived class - Circle
class Circle : public Shape {
private:
    double radius_;
    
public:
    Circle(double radius) : radius_(radius) {
        area_ = calculateArea();
        perimeter_ = calculatePerimeter();
    }
    
    double calculateArea() override {
        return 3.14159 * radius_ * radius_;
    }
    
    double calculatePerimeter() override {
        return 2 * 3.14159 * radius_;
    }
    
    void display() const override {
        std::cout << "Circle (radius: " << radius_ << ") - Area: " 
                  << area_ << ", Perimeter: " << perimeter_ << std::endl;
    }
    
    double getRadius() const { return radius_; }
};

// Concrete derived class - Rectangle
class Rectangle : public Shape {
private:
    double width_, height_;
    
public:
    Rectangle(double width, double height) : width_(width), height_(height) {
        area_ = calculateArea();
        perimeter_ = calculatePerimeter();
    }
    
    double calculateArea() override {
        return width_ * height_;
    }
    
    double calculatePerimeter() override {
        return 2 * (width_ + height_);
    }
    
    void display() const override {
        std::cout << "Rectangle (" << width_ << "x" << height_ 
                  << ") - Area: " << area_ << ", Perimeter: " << perimeter_ << std::endl;
    }
    
    double getWidth() const { return width_; }
    double getHeight() const { return height_; }
};

// Concrete derived class - Triangle
class Triangle : public Shape {
private:
    double base_, height_, side1_, side2_;
    
public:
    Triangle(double base, double height, double side1, double side2)
        : base_(base), height_(height), side1_(side1), side2_(side2) {
        area_ = calculateArea();
        perimeter_ = calculatePerimeter();
    }
    
    double calculateArea() override {
        return 0.5 * base_ * height_;
    }
    
    double calculatePerimeter() override {
        return base_ + side1_ + side2_;
    }
    
    void display() const override {
        std::cout << "Triangle (base: " << base_ << ", height: " << height_ 
                  << ") - Area: " << area_ << ", Perimeter: " << perimeter_ << std::endl;
    }
    
    double getBase() const { return base_; }
    double getHeight() const { return height_; }
};

// Example 3: Multiple Inheritance - Flying and Swimming Animals
class Flyable {
public:
    virtual ~Flyable() = default;
    virtual void fly() const = 0;
    virtual double getMaxAltitude() const = 0;
};

class Swimmable {
public:
    virtual ~Swimmable() = default;
    virtual void swim() const = 0;
    virtual double getMaxDepth() const = 0;
};

class Duck : public Animal, public Flyable, public Swimmable {
private:
    double max_altitude_;
    double max_depth_;
    
public:
    Duck(const std::string& name, int age, double weight, 
         double altitude, double depth)
        : Animal(name, age, weight), max_altitude_(altitude), max_depth_(depth) {}
    
    // Animal virtual functions
    void makeSound() const override {
        std::cout << name_ << " quacks: Quack! Quack!" << std::endl;
    }
    
    void move() const override {
        std::cout << name_ << " waddles on land" << std::endl;
    }
    
    void displayInfo() const override {
        Animal::displayInfo();
        std::cout << "Max Altitude: " << max_altitude_ << "m, Max Depth: " 
                  << max_depth_ << "m" << std::endl;
    }
    
    // Flyable interface
    void fly() const override {
        std::cout << name_ << " is flying up to " << max_altitude_ << " meters" << std::endl;
    }
    
    double getMaxAltitude() const override {
        return max_altitude_;
    }
    
    // Swimmable interface
    void swim() const override {
        std::cout << name_ << " is swimming up to " << max_depth_ << " meters deep" << std::endl;
    }
    
    double getMaxDepth() const override {
        return max_depth_;
    }
};

// Example 4: Virtual Inheritance - Diamond Problem Solution
class Vehicle {
protected:
    std::string brand_;
    int year_;
    
public:
    Vehicle(const std::string& brand, int year) : brand_(brand), year_(year) {}
    virtual ~Vehicle() = default;
    
    virtual void start() const {
        std::cout << brand_ << " vehicle is starting" << std::endl;
    }
    
    virtual void stop() const {
        std::cout << brand_ << " vehicle is stopping" << std::endl;
    }
    
    const std::string& getBrand() const { return brand_; }
    int getYear() const { return year_; }
};

class Motorized : virtual public Vehicle {
protected:
    double engine_power_;
    
public:
    Motorized(const std::string& brand, int year, double power)
        : Vehicle(brand, year), engine_power_(power) {}
    
    void start() const override {
        std::cout << brand_ << " motorized vehicle (power: " 
                  << engine_power_ << " HP) is starting" << std::endl;
    }
    
    double getEnginePower() const { return engine_power_; }
};

class Electric : virtual public Vehicle {
protected:
    double battery_capacity_;
    
public:
    Electric(const std::string& brand, int year, double capacity)
        : Vehicle(brand, year), battery_capacity_(capacity) {}
    
    void start() const override {
        std::cout << brand_ << " electric vehicle (battery: " 
                  << battery_capacity_ << " kWh) is starting" << std::endl;
    }
    
    double getBatteryCapacity() const { return battery_capacity_; }
};

class HybridCar : public Motorized, public Electric {
public:
    HybridCar(const std::string& brand, int year, double power, double capacity)
        : Vehicle(brand, year),  // Virtual base constructor
          Motorized(brand, year, power),
          Electric(brand, year, capacity) {}
    
    void start() const override {
        std::cout << brand_ << " hybrid car (power: " << engine_power_ 
                  << " HP, battery: " << battery_capacity_ << " kWh) is starting" << std::endl;
    }
    
    void displayInfo() const {
        std::cout << year_ << " " << brand_ << " Hybrid Car" << std::endl;
        std::cout << "Engine Power: " << engine_power_ << " HP" << std::endl;
        std::cout << "Battery Capacity: " << battery_capacity_ << " kWh" << std::endl;
    }
};

// Function to demonstrate basic inheritance
void demonstrateBasicInheritance() {
    std::cout << "=== Basic Inheritance Demonstration ===" << std::endl;
    
    Dog dog("Buddy", 3, 25.5, "Golden Retriever", true);
    Cat cat("Whiskers", 2, 4.2, "Orange", true);
    
    std::cout << "\nAnimal information:" << std::endl;
    dog.displayInfo();
    cat.displayInfo();
    
    std::cout << "\nAnimal behaviors:" << std::endl;
    dog.makeSound();
    dog.move();
    dog.eat();
    dog.sleep();
    dog.breathe();
    
    cat.makeSound();
    cat.move();
    cat.eat();
    cat.sleep();
    cat.breathe();
    
    std::cout << "\nSpecies-specific behaviors:" << std::endl;
    dog.fetch();
    dog.sit();
    dog.wagTail();
    
    cat.purr();
    cat.climb();
    cat.hunt();
}

// Function to demonstrate polymorphism
void demonstratePolymorphism() {
    std::cout << "\n=== Polymorphism Demonstration ===" << std::endl;
    
    // Using base class pointers
    std::vector<std::unique_ptr<Animal>> animals;
    animals.push_back(std::make_unique<Dog>("Rex", 5, 30.0, "German Shepherd", true));
    animals.push_back(std::make_unique<Cat>("Fluffy", 4, 3.8, "Black", false));
    animals.push_back(std::make_unique<Duck>("Donald", 2, 1.5, 100.0, 5.0));
    
    std::cout << "\nPolymorphic behavior:" << std::endl;
    for (const auto& animal : animals) {
        std::cout << "\n--- " << animal->getName() << " ---" << std::endl;
        animal->makeSound();
        animal->move();
        animal->eat();
        animal->displayInfo();
        
        // Dynamic casting to access derived class methods
        if (auto* dog = dynamic_cast<Dog*>(animal.get())) {
            dog->fetch();
        } else if (auto* cat = dynamic_cast<Cat*>(animal.get())) {
            cat->purr();
        } else if (auto* duck = dynamic_cast<Duck*>(animal.get())) {
            duck->fly();
            duck->swim();
        }
    }
}

// Function to demonstrate abstract classes
void demonstrateAbstractClasses() {
    std::cout << "\n=== Abstract Classes Demonstration ===" << std::endl;
    
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5.0));
    shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0));
    shapes.push_back(std::make_unique<Triangle>(3.0, 4.0, 5.0, 6.0));
    
    std::cout << "\nShape information:" << std::endl;
    for (const auto& shape : shapes) {
        shape->display();
        shape->printInfo();
        std::cout << std::endl;
    }
    
    // Calculate total area
    double total_area = 0.0;
    for (const auto& shape : shapes) {
        total_area += shape->getArea();
    }
    std::cout << "Total area of all shapes: " << total_area << std::endl;
}

// Function to demonstrate multiple inheritance
void demonstrateMultipleInheritance() {
    std::cout << "\n=== Multiple Inheritance Demonstration ===" << std::endl;
    
    Duck duck("Daffy", 3, 2.0, 50.0, 3.0);
    
    std::cout << "Duck information:" << std::endl;
    duck.displayInfo();
    
    std::cout << "\nDuck behaviors:" << std::endl;
    duck.makeSound();
    duck.move();
    duck.eat();
    duck.fly();
    duck.swim();
    
    // Using interface pointers
    Flyable* flyable = &duck;
    Swimmable* swimmable = &duck;
    
    std::cout << "\nUsing interface pointers:" << std::endl;
    flyable->fly();
    std::cout << "Max altitude: " << flyable->getMaxAltitude() << " meters" << std::endl;
    
    swimmable->swim();
    std::cout << "Max depth: " << swimmable->getMaxDepth() << " meters" << std::endl;
}

// Function to demonstrate virtual inheritance
void demonstrateVirtualInheritance() {
    std::cout << "\n=== Virtual Inheritance Demonstration ===" std::endl;
    
    HybridCar hybrid("Toyota", 2023, 150.0, 8.8);
    
    std::cout << "Hybrid car information:" << std::endl;
    hybrid.displayInfo();
    
    std::cout << "\nHybrid car behaviors:" << std::endl;
    hybrid.start();
    hybrid.stop();
    
    // Using base class pointers
    Vehicle* vehicle = &hybrid;
    Motorized* motorized = &hybrid;
    Electric* electric = &hybrid;
    
    std::cout << "\nUsing base class pointers:" << std::endl;
    vehicle->start();
    motorized->start();
    electric->start();
    
    std::cout << "\nAccessing inherited members:" << std::endl;
    std::cout << "Brand: " << vehicle->getBrand() << std::endl;
    std::cout << "Year: " << vehicle->getYear() << std::endl;
    std::cout << "Engine Power: " << motorized->getEnginePower() << " HP" << std::endl;
    std::cout << "Battery Capacity: " << electric->getBatteryCapacity() << " kWh" << std::endl;
}

// Function to demonstrate access specifiers
void demonstrateAccessSpecifiers() {
    std::cout << "\n=== Access Specifiers Demonstration ===" << std::endl;
    
    Dog dog("Max", 4, 28.0, "Labrador", false);
    
    std::cout << "Public access:" << std::endl;
    std::cout << "Name: " << dog.getName() << std::endl;
    std::cout << "Age: " << dog.getAge() << std::endl;
    std::cout << "Breed: " << dog.getBreed() << std::endl;
    
    std::cout << "\nProtected access (through public methods):" << std::endl;
    dog.displayInfo();  // Accesses protected members through public methods
    
    std::cout << "\nPrivate access (through public methods):" << std::endl;
    std::cout << "Is trained: " << (dog.isTrained() ? "Yes" : "No") << std::endl;
    
    std::cout << "\nModifying private members through public methods:" << std::endl;
    dog.setTrained(true);
    std::cout << "After training: " << (dog.isTrained() ? "Yes" : "No") << std::endl;
    dog.sit();
}

// Function to demonstrate constructor and destructor order
void demonstrateConstructorDestructorOrder() {
    std::cout << "\n=== Constructor/Destructor Order Demonstration ===" << std::endl;
    
    std::cout << "Creating Dog object:" << std::endl;
    Dog dog("Luna", 2, 22.0, "Border Collie", true);
    
    std::cout << "\nCreating Cat object:" << std::endl;
    Cat cat("Mittens", 1, 3.5, "White", true);
    
    std::cout << "\nObjects will be destroyed when leaving scope..." << std::endl;
}

int main() {
    std::cout << "=== Inheritance Demonstration ===" << std::endl;
    std::cout << "This program demonstrates base and derived class relationships,\n"
              << "virtual functions, polymorphism, abstract classes, and inheritance patterns.\n" << std::endl;
    
    // Demonstrate various inheritance concepts
    demonstrateBasicInheritance();
    demonstratePolymorphism();
    demonstrateAbstractClasses();
    demonstrateMultipleInheritance();
    demonstrateVirtualInheritance();
    demonstrateAccessSpecifiers();
    demonstrateConstructorDestructorOrder();
    
    std::cout << "\n=== Key Takeaways ===" << std::endl;
    std::cout << "1. Inheritance creates 'is-a' relationships between classes" << std::endl;
    std::cout << "2. Virtual functions enable polymorphic behavior" << std::endl;
    std::cout << "3. Abstract classes define interfaces for derived classes" << std::endl;
    std::cout << "4. Multiple inheritance allows classes to inherit from multiple bases" << std::endl;
    std::cout << "5. Virtual inheritance solves the diamond problem" << std::endl;
    std::cout << "6. Access specifiers control member visibility in inheritance" << std::endl;
    std::cout << "7. Constructors and destructors are called in specific order" << std::endl;
    std::cout << "8. Dynamic casting enables safe downcasting" << std::endl;
    
    std::cout << "\nProgram completed successfully!" << std::endl;
    return 0;
}

/*
 * Compilation Instructions:
 * 
 * Using GCC:
 * g++ -std=c++17 -Wall -Wextra -O2 -o inheritance 02_Inheritance.cpp
 * 
 * Using Clang:
 * clang++ -std=c++17 -Wall -Wextra -O2 -o inheritance 02_Inheritance.cpp
 * 
 * Using MSVC (Visual Studio):
 * cl /std:c++17 /EHsc /O2 02_Inheritance.cpp
 * 
 * Running:
 * ./inheritance (Linux/macOS)
 * inheritance.exe (Windows)
 * 
 * Note: This lesson requires C++11 or later for smart pointers and some features.
 * C++17 is recommended for best inheritance support.
 * 
 * Inheritance Notes:
 * - Use public inheritance for 'is-a' relationships
 * - Make destructors virtual in base classes
 * - Use override keyword for clarity
 * - Prefer composition over inheritance when possible
 * - Use abstract classes to define interfaces
 * - Handle multiple inheritance carefully
 * - Use virtual inheritance to solve diamond problem
 * - Access specifiers control member visibility
 */"""
