#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <typeinfo>

// Demonstrates advanced inheritance concepts
int main() {
    std::cout << "Advanced Inheritance Demonstration" << std::endl;
    std::cout << "=================================" << std::endl;
    
    // 1. Virtual Inheritance - Diamond Problem
    std::cout << "\n1. VIRTUAL INHERITANCE - DIAMOND PROBLEM:" << std::endl;
    
    class Animal {
    protected:
        std::string name;
        int age;
    public:
        Animal(const std::string& n, int a) : name(n), age(a) {
            std::cout << "Animal constructor: " << name << std::endl;
        }
        virtual ~Animal() {
            std::cout << "Animal destructor: " << name << std::endl;
        }
        virtual void makeSound() = 0;
        virtual void eat() = 0;
        virtual void sleep() {
            std::cout << name << " is sleeping" << std::endl;
        }
        std::string getName() const { return name; }
        int getAge() const { return age; }
    };
    
    class Mammal : public virtual Animal {
    public:
        Mammal(const std::string& n, int a) : Animal(n, a) {
            std::cout << "Mammal constructor: " << n << std::endl;
        }
        virtual ~Mammal() {
            std::cout << "Mammal destructor: " << name << std::endl;
        }
        void breathe() {
            std::cout << name << " breathes with lungs" << std::endl;
        }
        virtual void giveBirth() {
            std::cout << name << " gives birth to live young" << std::endl;
        }
    };
    
    class WingedAnimal : public virtual Animal {
    public:
        WingedAnimal(const std::string& n, int a) : Animal(n, a) {
            std::cout << "WingedAnimal constructor: " << n << std::endl;
        }
        virtual ~WingedAnimal() {
            std::cout << "WingedAnimal destructor: " << name << std::endl;
        }
        void fly() {
            std::cout << name << " can fly" << std::endl;
        }
        virtual void migrate() {
            std::cout << name << " migrates seasonally" << std::endl;
        }
    };
    
    class Bat : public Mammal, public WingedAnimal {
    public:
        Bat(const std::string& n, int a) : Animal(n, a), Mammal(n, a), WingedAnimal(n, a) {
            std::cout << "Bat constructor: " << n << std::endl;
        }
        virtual ~Bat() {
            std::cout << "Bat destructor: " << name << std::endl;
        }
        void makeSound() override {
            std::cout << name << " makes ultrasonic sounds" << std::endl;
        }
        void eat() override {
            std::cout << name << " eats insects and fruit" << std::endl;
        }
        void giveBirth() override {
            std::cout << name << " gives birth to a single pup" << std::endl;
        }
        void migrate() override {
            std::cout << name << " migrates to warmer climates" << std::endl;
        }
    };
    
    std::cout << "\nCreating a bat:" << std::endl;
    Bat bat("Vampire Bat", 3);
    
    std::cout << "\nBat behaviors:" << std::endl;
    bat.makeSound();
    bat.eat();
    bat.sleep();
    bat.breathe();
    bat.fly();
    bat.giveBirth();
    bat.migrate();
    
    std::cout << "\nBat information:" << std::endl;
    std::cout << "Name: " << bat.getName() << std::endl;
    std::cout << "Age: " << bat.getAge() << std::endl;
    
    // 2. Abstract Base Classes
    std::cout << "\n2. ABSTRACT BASE CLASSES:" << std::endl;
    
    class Shape {
    public:
        virtual ~Shape() = default;
        virtual double area() const = 0;
        virtual double perimeter() const = 0;
        virtual void draw() const = 0;
        virtual std::string getType() const = 0;
        
        // Non-pure virtual function
        virtual void displayInfo() const {
            std::cout << "Shape: " << getType() << std::endl;
            std::cout << "Area: " << area() << std::endl;
            std::cout << "Perimeter: " << perimeter() << std::endl;
        }
    };
    
    class Circle : public Shape {
    private:
        double radius;
    public:
        Circle(double r) : radius(r) {
            if (radius <= 0) throw std::invalid_argument("Radius must be positive");
        }
        double area() const override { return 3.14159 * radius * radius; }
        double perimeter() const override { return 2 * 3.14159 * radius; }
        void draw() const override { 
            std::cout << "Drawing a circle with radius " << radius << std::endl; 
        }
        std::string getType() const override { return "Circle"; }
    };
    
    class Rectangle : public Shape {
    private:
        double width, height;
    public:
        Rectangle(double w, double h) : width(w), height(h) {
            if (width <= 0 || height <= 0) 
                throw std::invalid_argument("Dimensions must be positive");
        }
        double area() const override { return width * height; }
        double perimeter() const override { return 2 * (width + height); }
        void draw() const override { 
            std::cout << "Drawing a rectangle " << width << "x" << height << std::endl; 
        }
        std::string getType() const override { return "Rectangle"; }
    };
    
    class Triangle : public Shape {
    private:
        double base, height;
    public:
        Triangle(double b, double h) : base(b), height(h) {
            if (base <= 0 || height <= 0) 
                throw std::invalid_argument("Dimensions must be positive");
        }
        double area() const override { return 0.5 * base * height; }
        double perimeter() const override { 
            // Simplified - assuming right triangle
            double hypotenuse = sqrt(base * base + height * height);
            return base + height + hypotenuse;
        }
        void draw() const override { 
            std::cout << "Drawing a triangle with base " << base << " and height " << height << std::endl; 
        }
        std::string getType() const override { return "Triangle"; }
    };
    
    std::cout << "\nCreating shapes:" << std::endl;
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5.0));
    shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0));
    shapes.push_back(std::make_unique<Triangle>(3.0, 4.0));
    
    std::cout << "\nShape information:" << std::endl;
    for (const auto& shape : shapes) {
        shape->displayInfo();
        shape->draw();
        std::cout << std::endl;
    }
    
    // 3. Multiple Inheritance
    std::cout << "\n3. MULTIPLE INHERITANCE:" << std::endl;
    
    class Drawable {
    public:
        virtual ~Drawable() = default;
        virtual void draw() const = 0;
        virtual std::string getColor() const { return "default"; }
    };
    
    class Movable {
    public:
        virtual ~Movable() = default;
        virtual void move() = 0;
        virtual double getSpeed() const { return 0.0; }
    };
    
    class GameObject : public Drawable, public Movable {
    private:
        std::string name;
        std::string color;
        double speed;
        double x, y;
    public:
        GameObject(const std::string& n, const std::string& c, double s, double x_pos, double y_pos)
            : name(n), color(c), speed(s), x(x_pos), y(y_pos) {}
        
        // Drawable interface
        void draw() const override {
            std::cout << "Drawing " << name << " at (" << x << ", " << y << ") in " << color << std::endl;
        }
        std::string getColor() const override { return color; }
        
        // Movable interface
        void move() override {
            x += speed;
            y += speed;
            std::cout << name << " moved to (" << x << ", " << y << ")" << std::endl;
        }
        double getSpeed() const override { return speed; }
        
        // GameObject specific methods
        std::string getName() const { return name; }
        void setPosition(double x_pos, double y_pos) { x = x_pos; y = y_pos; }
        std::pair<double, double> getPosition() const { return {x, y}; }
    };
    
    GameObject player("Player", "blue", 1.5, 0.0, 0.0);
    GameObject enemy("Enemy", "red", 1.0, 10.0, 10.0);
    
    std::cout << "\nGame objects:" << std::endl;
    player.draw();
    player.move();
    std::cout << "Player speed: " << player.getSpeed() << std::endl;
    
    enemy.draw();
    enemy.move();
    std::cout << "Enemy speed: " << enemy.getSpeed() << std::endl;
    
    // 4. Runtime Type Information (RTTI)
    std::cout << "\n4. RUNTIME TYPE INFORMATION (RTTI):" << std::endl;
    
    std::cout << "\nType information:" << std::endl;
    std::cout << "Circle type: " << typeid(Circle).name() << std::endl;
    std::cout << "Rectangle type: " << typeid(Rectangle).name() << std::endl;
    std::cout << "Triangle type: " << typeid(Triangle).name() << std::endl;
    
    std::cout << "\nRuntime type checking:" << std::endl;
    for (const auto& shape : shapes) {
        std::cout << "Shape type: " << typeid(*shape).name() << std::endl;
        
        // Dynamic casting
        if (auto* circle = dynamic_cast<Circle*>(shape.get())) {
            std::cout << "  This is a circle!" << std::endl;
        } else if (auto* rectangle = dynamic_cast<Rectangle*>(shape.get())) {
            std::cout << "  This is a rectangle!" << std::endl;
        } else if (auto* triangle = dynamic_cast<Triangle*>(shape.get())) {
            std::cout << "  This is a triangle!" << std::endl;
        }
    }
    
    // 5. Virtual Function Tables and Performance
    std::cout << "\n5. VIRTUAL FUNCTION TABLES:" << std::endl;
    
    class Base {
    public:
        virtual void func1() { std::cout << "Base::func1" << std::endl; }
        virtual void func2() { std::cout << "Base::func2" << std::endl; }
        virtual ~Base() = default;
    };
    
    class Derived : public Base {
    public:
        void func1() override { std::cout << "Derived::func1" << std::endl; }
        void func2() override { std::cout << "Derived::func2" << std::endl; }
        virtual void func3() { std::cout << "Derived::func3" << std::endl; }
    };
    
    Base* base_ptr = new Derived();
    base_ptr->func1();
    base_ptr->func2();
    
    // Try to call func3 through base pointer (won't work)
    // base_ptr->func3(); // Error: func3 is not in Base
    
    // Dynamic cast to access func3
    if (auto* derived_ptr = dynamic_cast<Derived*>(base_ptr)) {
        derived_ptr->func3();
    }
    
    delete base_ptr;
    
    // 6. Interface Segregation
    std::cout << "\n6. INTERFACE SEGREGATION:" << std::endl;
    
    class IReadable {
    public:
        virtual ~IReadable() = default;
        virtual void read() = 0;
    };
    
    class IWritable {
    public:
        virtual ~IWritable() = default;
        virtual void write() = 0;
    };
    
    class IExecutable {
    public:
        virtual ~IExecutable() = default;
        virtual void execute() = 0;
    };
    
    class File : public IReadable, public IWritable {
    private:
        std::string filename;
    public:
        File(const std::string& name) : filename(name) {}
        void read() override {
            std::cout << "Reading file: " << filename << std::endl;
        }
        void write() override {
            std::cout << "Writing to file: " << filename << std::endl;
        }
    };
    
    class Program : public IReadable, public IExecutable {
    private:
        std::string program_name;
    public:
        Program(const std::string& name) : program_name(name) {}
        void read() override {
            std::cout << "Reading program: " << program_name << std::endl;
        }
        void execute() override {
            std::cout << "Executing program: " << program_name << std::endl;
        }
    };
    
    File file("data.txt");
    Program program("my_program.exe");
    
    std::cout << "\nFile operations:" << std::endl;
    file.read();
    file.write();
    
    std::cout << "\nProgram operations:" << std::endl;
    program.read();
    program.execute();
    
    // 7. Covariant Return Types
    std::cout << "\n7. COVARIANT RETURN TYPES:" << std::endl;
    
    class AnimalFactory {
    public:
        virtual Animal* create() = 0;
        virtual ~AnimalFactory() = default;
    };
    
    class BatFactory : public AnimalFactory {
    public:
        Bat* create() override {  // Covariant return type
            return new Bat("Factory Bat", 1);
        }
    };
    
    BatFactory factory;
    Bat* bat_from_factory = factory.create();
    std::cout << "Created bat from factory: " << bat_from_factory->getName() << std::endl;
    delete bat_from_factory;
    
    // 8. Virtual Destructors
    std::cout << "\n8. VIRTUAL DESTRUCTORS:" << std::endl;
    
    class BaseWithVirtualDestructor {
    public:
        virtual ~BaseWithVirtualDestructor() {
            std::cout << "BaseWithVirtualDestructor destructor" << std::endl;
        }
    };
    
    class DerivedWithVirtualDestructor : public BaseWithVirtualDestructor {
    public:
        ~DerivedWithVirtualDestructor() override {
            std::cout << "DerivedWithVirtualDestructor destructor" << std::endl;
        }
    };
    
    std::cout << "\nTesting virtual destructors:" << std::endl;
    BaseWithVirtualDestructor* base_with_virtual = new DerivedWithVirtualDestructor();
    delete base_with_virtual;  // This will call both destructors
    
    std::cout << "\nAdvanced inheritance demonstration completed!" << std::endl;
    return 0;
}
