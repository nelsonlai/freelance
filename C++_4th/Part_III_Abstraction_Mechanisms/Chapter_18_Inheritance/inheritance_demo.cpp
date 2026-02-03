#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <typeinfo>

// Demonstrates C++ inheritance and polymorphism
int main() {
    std::cout << "C++ Inheritance and Polymorphism Demonstration" << std::endl;
    std::cout << "==============================================" << std::endl;
    
    // 1. Basic inheritance
    std::cout << "\n1. BASIC INHERITANCE:" << std::endl;
    
    class Shape {
    protected:
        std::string name;
        double area;
        
    public:
        Shape(const std::string& name) : name(name), area(0.0) {}
        
        virtual ~Shape() = default;
        
        virtual void calculate_area() = 0;  // Pure virtual function
        
        virtual void display() const {
            std::cout << "Shape: " << name << ", Area: " << area << std::endl;
        }
        
        const std::string& get_name() const { return name; }
        double get_area() const { return area; }
    };
    
    class Circle : public Shape {
    private:
        double radius;
        
    public:
        Circle(const std::string& name, double radius) 
            : Shape(name), radius(radius) {}
        
        void calculate_area() override {
            area = 3.14159 * radius * radius;
        }
        
        void display() const override {
            std::cout << "Circle: " << name << ", Radius: " << radius 
                      << ", Area: " << area << std::endl;
        }
        
        double get_radius() const { return radius; }
    };
    
    class Rectangle : public Shape {
    private:
        double width, height;
        
    public:
        Rectangle(const std::string& name, double width, double height)
            : Shape(name), width(width), height(height) {}
        
        void calculate_area() override {
            area = width * height;
        }
        
        void display() const override {
            std::cout << "Rectangle: " << name << ", Width: " << width 
                      << ", Height: " << height << ", Area: " << area << std::endl;
        }
        
        double get_width() const { return width; }
        double get_height() const { return height; }
    };
    
    Circle circle("Circle1", 5.0);
    Rectangle rectangle("Rectangle1", 4.0, 6.0);
    
    circle.calculate_area();
    rectangle.calculate_area();
    
    circle.display();
    rectangle.display();
    
    // 2. Polymorphism with virtual functions
    std::cout << "\n2. POLYMORPHISM WITH VIRTUAL FUNCTIONS:" << std::endl;
    
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>("Circle2", 3.0));
    shapes.push_back(std::make_unique<Rectangle>("Rectangle2", 5.0, 7.0));
    shapes.push_back(std::make_unique<Circle>("Circle3", 2.5));
    
    for (auto& shape : shapes) {
        shape->calculate_area();
        shape->display();
    }
    
    // 3. Abstract base class
    std::cout << "\n3. ABSTRACT BASE CLASS:" << std::endl;
    
    class Vehicle {
    protected:
        std::string brand;
        std::string model;
        int year;
        
    public:
        Vehicle(const std::string& brand, const std::string& model, int year)
            : brand(brand), model(model), year(year) {}
        
        virtual ~Vehicle() = default;
        
        virtual void start() = 0;  // Pure virtual function
        virtual void stop() = 0;   // Pure virtual function
        
        virtual void display_info() const {
            std::cout << "Vehicle: " << brand << " " << model << " (" << year << ")" << std::endl;
        }
        
        const std::string& get_brand() const { return brand; }
        const std::string& get_model() const { return model; }
        int get_year() const { return year; }
    };
    
    class Car : public Vehicle {
    private:
        int doors;
        
    public:
        Car(const std::string& brand, const std::string& model, int year, int doors)
            : Vehicle(brand, model, year), doors(doors) {}
        
        void start() override {
            std::cout << "Car engine started" << std::endl;
        }
        
        void stop() override {
            std::cout << "Car engine stopped" << std::endl;
        }
        
        void display_info() const override {
            Vehicle::display_info();
            std::cout << "Doors: " << doors << std::endl;
        }
    };
    
    class Motorcycle : public Vehicle {
    private:
        bool has_sidecar;
        
    public:
        Motorcycle(const std::string& brand, const std::string& model, int year, bool sidecar)
            : Vehicle(brand, model, year), has_sidecar(sidecar) {}
        
        void start() override {
            std::cout << "Motorcycle engine started" << std::endl;
        }
        
        void stop() override {
            std::cout << "Motorcycle engine stopped" << std::endl;
        }
        
        void display_info() const override {
            Vehicle::display_info();
            std::cout << "Has sidecar: " << std::boolalpha << has_sidecar << std::endl;
        }
    };
    
    Car car("Toyota", "Camry", 2023, 4);
    Motorcycle motorcycle("Honda", "CBR600", 2023, false);
    
    car.display_info();
    car.start();
    car.stop();
    
    motorcycle.display_info();
    motorcycle.start();
    motorcycle.stop();
    
    // 4. Multiple inheritance
    std::cout << "\n4. MULTIPLE INHERITANCE:" << std::endl;
    
    class Flyable {
    public:
        virtual void fly() = 0;
        virtual ~Flyable() = default;
    };
    
    class Swimmable {
    public:
        virtual void swim() = 0;
        virtual ~Swimmable() = default;
    };
    
    class Duck : public Animal, public Flyable, public Swimmable {
    private:
        std::string color;
        
    public:
        Duck(const std::string& name, int age, const std::string& color)
            : Animal(name, age), color(color) {}
        
        void make_sound() const override {
            std::cout << name << " quacks!" << std::endl;
        }
        
        void fly() override {
            std::cout << name << " is flying" << std::endl;
        }
        
        void swim() override {
            std::cout << name << " is swimming" << std::endl;
        }
        
        void display_info() const override {
            Animal::display_info();
            std::cout << "Color: " << color << std::endl;
        }
    };
    
    Duck duck("Donald", 2, "white");
    duck.display_info();
    duck.make_sound();
    duck.fly();
    duck.swim();
    
    // 5. Virtual inheritance
    std::cout << "\n5. VIRTUAL INHERITANCE:" << std::endl;
    
    class AnimalBase {
    protected:
        std::string species;
        
    public:
        AnimalBase(const std::string& species) : species(species) {
            std::cout << "AnimalBase constructor: " << species << std::endl;
        }
        
        virtual ~AnimalBase() = default;
        
        const std::string& get_species() const { return species; }
    };
    
    class Mammal : public virtual AnimalBase {
    public:
        Mammal(const std::string& species) : AnimalBase(species) {
            std::cout << "Mammal constructor" << std::endl;
        }
        
        virtual void give_birth() {
            std::cout << "Mammal gives birth" << std::endl;
        }
    };
    
    class Carnivore : public virtual AnimalBase {
    public:
        Carnivore(const std::string& species) : AnimalBase(species) {
            std::cout << "Carnivore constructor" << std::endl;
        }
        
        virtual void hunt() {
            std::cout << "Carnivore hunts" << std::endl;
        }
    };
    
    class Lion : public Mammal, public Carnivore {
    public:
        Lion() : AnimalBase("Lion"), Mammal("Lion"), Carnivore("Lion") {
            std::cout << "Lion constructor" << std::endl;
        }
        
        void give_birth() override {
            std::cout << "Lion gives birth to cubs" << std::endl;
        }
        
        void hunt() override {
            std::cout << "Lion hunts prey" << std::endl;
        }
    };
    
    Lion lion;
    std::cout << "Lion species: " << lion.get_species() << std::endl;
    lion.give_birth();
    lion.hunt();
    
    // 6. Access control in inheritance
    std::cout << "\n6. ACCESS CONTROL IN INHERITANCE:" << std::endl;
    
    class Base {
    public:
        int public_member;
    protected:
        int protected_member;
    private:
        int private_member;
        
    public:
        Base() : public_member(1), protected_member(2), private_member(3) {}
        
        void public_method() {
            std::cout << "Base public method" << std::endl;
        }
        
    protected:
        void protected_method() {
            std::cout << "Base protected method" << std::endl;
        }
        
    private:
        void private_method() {
            std::cout << "Base private method" << std::endl;
        }
    };
    
    class PublicDerived : public Base {
    public:
        void test_access() {
            public_member = 10;      // OK: public in derived
            protected_member = 20;   // OK: protected in derived
            // private_member = 30;  // Error: private not accessible
            
            public_method();         // OK: public in derived
            protected_method();      // OK: protected in derived
            // private_method();     // Error: private not accessible
        }
    };
    
    class ProtectedDerived : protected Base {
    public:
        void test_access() {
            public_member = 10;      // OK: public becomes protected
            protected_member = 20;   // OK: protected stays protected
            // private_member = 30;  // Error: private not accessible
            
            public_method();         // OK: public becomes protected
            protected_method();      // OK: protected stays protected
            // private_method();     // Error: private not accessible
        }
    };
    
    class PrivateDerived : private Base {
    public:
        void test_access() {
            public_member = 10;      // OK: public becomes private
            protected_member = 20;   // OK: protected becomes private
            // private_member = 30;  // Error: private not accessible
            
            public_method();         // OK: public becomes private
            protected_method();      // OK: protected becomes private
            // private_method();     // Error: private not accessible
        }
    };
    
    PublicDerived pub_derived;
    pub_derived.test_access();
    pub_derived.public_method();  // OK: public inheritance
    
    ProtectedDerived prot_derived;
    prot_derived.test_access();
    // prot_derived.public_method();  // Error: protected inheritance
    
    PrivateDerived priv_derived;
    priv_derived.test_access();
    // priv_derived.public_method();  // Error: private inheritance
    
    // 7. Virtual destructors
    std::cout << "\n7. VIRTUAL DESTRUCTORS:" << std::endl;
    
    class BaseWithVirtualDestructor {
    public:
        BaseWithVirtualDestructor() {
            std::cout << "BaseWithVirtualDestructor constructor" << std::endl;
        }
        
        virtual ~BaseWithVirtualDestructor() {
            std::cout << "BaseWithVirtualDestructor destructor" << std::endl;
        }
        
        virtual void display() const {
            std::cout << "BaseWithVirtualDestructor display" << std::endl;
        }
    };
    
    class DerivedWithVirtualDestructor : public BaseWithVirtualDestructor {
    private:
        int* data;
        
    public:
        DerivedWithVirtualDestructor() : data(new int(42)) {
            std::cout << "DerivedWithVirtualDestructor constructor" << std::endl;
        }
        
        ~DerivedWithVirtualDestructor() override {
            delete data;
            std::cout << "DerivedWithVirtualDestructor destructor" << std::endl;
        }
        
        void display() const override {
            std::cout << "DerivedWithVirtualDestructor display, data = " << *data << std::endl;
        }
    };
    
    {
        std::unique_ptr<BaseWithVirtualDestructor> ptr = 
            std::make_unique<DerivedWithVirtualDestructor>();
        ptr->display();
    }  // Virtual destructor called correctly
    
    // 8. Override and final keywords
    std::cout << "\n8. OVERRIDE AND FINAL KEYWORDS:" << std::endl;
    
    class BaseOverride {
    public:
        virtual void method1() {
            std::cout << "BaseOverride::method1" << std::endl;
        }
        
        virtual void method2() {
            std::cout << "BaseOverride::method2" << std::endl;
        }
        
        virtual void method3() final {
            std::cout << "BaseOverride::method3 (final)" << std::endl;
        }
    };
    
    class DerivedOverride : public BaseOverride {
    public:
        void method1() override {
            std::cout << "DerivedOverride::method1 (override)" << std::endl;
        }
        
        void method2() override final {
            std::cout << "DerivedOverride::method2 (override final)" << std::endl;
        }
        
        // void method3() override { }  // Error: cannot override final method
    };
    
    class FinalDerived final : public DerivedOverride {
    public:
        // void method2() override { }  // Error: cannot override final method
    };
    
    // class FurtherDerived : public FinalDerived { }  // Error: cannot inherit from final class
    
    DerivedOverride derived;
    derived.method1();
    derived.method2();
    derived.method3();
    
    // 9. Type information and dynamic casting
    std::cout << "\n9. TYPE INFORMATION AND DYNAMIC CASTING:" << std::endl;
    
    std::vector<std::unique_ptr<Shape>> shape_vector;
    shape_vector.push_back(std::make_unique<Circle>("Circle4", 4.0));
    shape_vector.push_back(std::make_unique<Rectangle>("Rectangle4", 3.0, 5.0));
    
    for (const auto& shape : shape_vector) {
        std::cout << "Type: " << typeid(*shape).name() << std::endl;
        
        // Dynamic casting
        if (auto* circle = dynamic_cast<Circle*>(shape.get())) {
            std::cout << "It's a circle with radius: " << circle->get_radius() << std::endl;
        } else if (auto* rectangle = dynamic_cast<Rectangle*>(shape.get())) {
            std::cout << "It's a rectangle with width: " << rectangle->get_width() 
                      << ", height: " << rectangle->get_height() << std::endl;
        }
    }
    
    // 10. Interface classes
    std::cout << "\n10. INTERFACE CLASSES:" << std::endl;
    
    class Drawable {
    public:
        virtual void draw() const = 0;
        virtual ~Drawable() = default;
    };
    
    class Movable {
    public:
        virtual void move(double x, double y) = 0;
        virtual ~Movable() = default;
    };
    
    class DrawableShape : public Shape, public Drawable, public Movable {
    private:
        double x, y;
        
    public:
        DrawableShape(const std::string& name, double x, double y) 
            : Shape(name), x(x), y(y) {}
        
        void calculate_area() override {
            area = 0.0;  // Default implementation
        }
        
        void draw() const override {
            std::cout << "Drawing " << name << " at (" << x << ", " << y << ")" << std::endl;
        }
        
        void move(double new_x, double new_y) override {
            x = new_x;
            y = new_y;
            std::cout << "Moved " << name << " to (" << x << ", " << y << ")" << std::endl;
        }
        
        double get_x() const { return x; }
        double get_y() const { return y; }
    };
    
    DrawableShape drawable_shape("DrawableShape1", 10, 20);
    drawable_shape.draw();
    drawable_shape.move(30, 40);
    drawable_shape.draw();
    
    std::cout << "\nInheritance and polymorphism demonstration completed!" << std::endl;
    return 0;
}
