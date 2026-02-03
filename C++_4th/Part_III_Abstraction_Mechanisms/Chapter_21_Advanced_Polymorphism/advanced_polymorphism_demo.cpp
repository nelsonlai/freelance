#include <iostream>
#include <vector>
#include <memory>
#include <functional>
#include <typeinfo>
#include <chrono>

// Demonstrates advanced polymorphism concepts
int main() {
    std::cout << "Advanced Polymorphism Demonstration" << std::endl;
    std::cout << "====================================" << std::endl;
    
    // 1. Virtual Function Tables (VTables)
    std::cout << "\n1. VIRTUAL FUNCTION TABLES (VTABLES):" << std::endl;
    
    class Base {
    public:
        virtual void func1() { 
            std::cout << "Base::func1" << std::endl; 
        }
        virtual void func2() { 
            std::cout << "Base::func2" << std::endl; 
        }
        virtual void func3() { 
            std::cout << "Base::func3" << std::endl; 
        }
        virtual ~Base() { 
            std::cout << "Base destructor" << std::endl; 
        }
    };
    
    class Derived : public Base {
    public:
        void func1() override { 
            std::cout << "Derived::func1" << std::endl; 
        }
        void func2() override { 
            std::cout << "Derived::func2" << std::endl; 
        }
        virtual void func4() { 
            std::cout << "Derived::func4" << std::endl; 
        }
        ~Derived() override { 
            std::cout << "Derived destructor" << std::endl; 
        }
    };
    
    std::cout << "\nVTable behavior:" << std::endl;
    Base* base_ptr = new Derived();
    
    std::cout << "Calling virtual functions through base pointer:" << std::endl;
    base_ptr->func1();  // Calls Derived::func1
    base_ptr->func2();  // Calls Derived::func2
    base_ptr->func3();  // Calls Base::func3
    
    // Try to call func4 through base pointer (won't work)
    // base_ptr->func4(); // Error: func4 is not in Base
    
    // Dynamic cast to access func4
    if (auto* derived_ptr = dynamic_cast<Derived*>(base_ptr)) {
        derived_ptr->func4();
    }
    
    delete base_ptr;
    
    // 2. Polymorphic Containers
    std::cout << "\n2. POLYMORPHIC CONTAINERS:" << std::endl;
    
    class Shape {
    public:
        virtual ~Shape() = default;
        virtual void draw() const = 0;
        virtual double area() const = 0;
        virtual std::string getType() const = 0;
        virtual void move(double dx, double dy) = 0;
    };
    
    class Circle : public Shape {
    private:
        double x, y, radius;
    public:
        Circle(double x_pos, double y_pos, double r) : x(x_pos), y(y_pos), radius(r) {}
        void draw() const override { 
            std::cout << "Drawing circle at (" << x << ", " << y << ") with radius " << radius << std::endl; 
        }
        double area() const override { 
            return 3.14159 * radius * radius; 
        }
        std::string getType() const override { 
            return "Circle"; 
        }
        void move(double dx, double dy) override {
            x += dx; y += dy;
            std::cout << "Circle moved to (" << x << ", " << y << ")" << std::endl;
        }
    };
    
    class Rectangle : public Shape {
    private:
        double x, y, width, height;
    public:
        Rectangle(double x_pos, double y_pos, double w, double h) 
            : x(x_pos), y(y_pos), width(w), height(h) {}
        void draw() const override { 
            std::cout << "Drawing rectangle at (" << x << ", " << y << ") with size " << width << "x" << height << std::endl; 
        }
        double area() const override { 
            return width * height; 
        }
        std::string getType() const override { 
            return "Rectangle"; 
        }
        void move(double dx, double dy) override {
            x += dx; y += dy;
            std::cout << "Rectangle moved to (" << x << ", " << y << ")" << std::endl;
        }
    };
    
    class Triangle : public Shape {
    private:
        double x, y, base, height;
    public:
        Triangle(double x_pos, double y_pos, double b, double h) 
            : x(x_pos), y(y_pos), base(b), height(h) {}
        void draw() const override { 
            std::cout << "Drawing triangle at (" << x << ", " << y << ") with base " << base << " and height " << height << std::endl; 
        }
        double area() const override { 
            return 0.5 * base * height; 
        }
        std::string getType() const override { 
            return "Triangle"; 
        }
        void move(double dx, double dy) override {
            x += dx; y += dy;
            std::cout << "Triangle moved to (" << x << ", " << y << ")" << std::endl;
        }
    };
    
    std::cout << "\nPolymorphic container:" << std::endl;
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(0, 0, 5));
    shapes.push_back(std::make_unique<Rectangle>(10, 10, 4, 6));
    shapes.push_back(std::make_unique<Triangle>(20, 20, 3, 4));
    
    std::cout << "\nDrawing all shapes:" << std::endl;
    for (const auto& shape : shapes) {
        shape->draw();
        std::cout << "  Type: " << shape->getType() << std::endl;
        std::cout << "  Area: " << shape->area() << std::endl;
    }
    
    std::cout << "\nMoving all shapes:" << std::endl;
    for (auto& shape : shapes) {
        shape->move(1, 1);
    }
    
    // 3. Visitor Pattern
    std::cout << "\n3. VISITOR PATTERN:" << std::endl;
    
    class Visitor {
    public:
        virtual ~Visitor() = default;
        virtual void visitCircle(const Circle& circle) = 0;
        virtual void visitRectangle(const Rectangle& rectangle) = 0;
        virtual void visitTriangle(const Triangle& triangle) = 0;
    };
    
    class AreaCalculator : public Visitor {
    private:
        double total_area = 0.0;
    public:
        void visitCircle(const Circle& circle) override {
            total_area += circle.area();
            std::cout << "Added circle area: " << circle.area() << std::endl;
        }
        void visitRectangle(const Rectangle& rectangle) override {
            total_area += rectangle.area();
            std::cout << "Added rectangle area: " << rectangle.area() << std::endl;
        }
        void visitTriangle(const Triangle& triangle) override {
            total_area += triangle.area();
            std::cout << "Added triangle area: " << triangle.area() << std::endl;
        }
        double getTotalArea() const { return total_area; }
    };
    
    class ShapeInfoVisitor : public Visitor {
    public:
        void visitCircle(const Circle& circle) override {
            std::cout << "Circle info: radius = " << circle.area() / 3.14159 << std::endl;
        }
        void visitRectangle(const Rectangle& rectangle) override {
            std::cout << "Rectangle info: area = " << rectangle.area() << std::endl;
        }
        void visitTriangle(const Triangle& triangle) override {
            std::cout << "Triangle info: area = " << triangle.area() << std::endl;
        }
    };
    
    // Add accept method to Shape hierarchy
    class VisitableShape : public Shape {
    public:
        virtual void accept(Visitor& visitor) = 0;
    };
    
    class VisitableCircle : public VisitableShape {
    private:
        Circle circle;
    public:
        VisitableCircle(double x, double y, double r) : circle(x, y, r) {}
        void draw() const override { circle.draw(); }
        double area() const override { return circle.area(); }
        std::string getType() const override { return circle.getType(); }
        void move(double dx, double dy) override { circle.move(dx, dy); }
        void accept(Visitor& visitor) override { visitor.visitCircle(circle); }
    };
    
    class VisitableRectangle : public VisitableShape {
    private:
        Rectangle rectangle;
    public:
        VisitableRectangle(double x, double y, double w, double h) : rectangle(x, y, w, h) {}
        void draw() const override { rectangle.draw(); }
        double area() const override { return rectangle.area(); }
        std::string getType() const override { return rectangle.getType(); }
        void move(double dx, double dy) override { rectangle.move(dx, dy); }
        void accept(Visitor& visitor) override { visitor.visitRectangle(rectangle); }
    };
    
    class VisitableTriangle : public VisitableShape {
    private:
        Triangle triangle;
    public:
        VisitableTriangle(double x, double y, double b, double h) : triangle(x, y, b, h) {}
        void draw() const override { triangle.draw(); }
        double area() const override { return triangle.area(); }
        std::string getType() const override { return triangle.getType(); }
        void move(double dx, double dy) override { triangle.move(dx, dy); }
        void accept(Visitor& visitor) override { visitor.visitTriangle(triangle); }
    };
    
    std::cout << "\nVisitor pattern demonstration:" << std::endl;
    std::vector<std::unique_ptr<VisitableShape>> visitable_shapes;
    visitable_shapes.push_back(std::make_unique<VisitableCircle>(0, 0, 5));
    visitable_shapes.push_back(std::make_unique<VisitableRectangle>(10, 10, 4, 6));
    visitable_shapes.push_back(std::make_unique<VisitableTriangle>(20, 20, 3, 4));
    
    AreaCalculator area_calc;
    ShapeInfoVisitor info_visitor;
    
    std::cout << "\nCalculating total area:" << std::endl;
    for (auto& shape : visitable_shapes) {
        shape->accept(area_calc);
    }
    std::cout << "Total area: " << area_calc.getTotalArea() << std::endl;
    
    std::cout << "\nGathering shape info:" << std::endl;
    for (auto& shape : visitable_shapes) {
        shape->accept(info_visitor);
    }
    
    // 4. Type Erasure
    std::cout << "\n4. TYPE ERASURE:" << std::endl;
    
    class TypeErasure {
    private:
        class Concept {
        public:
            virtual ~Concept() = default;
            virtual void draw() const = 0;
            virtual double area() const = 0;
            virtual std::unique_ptr<Concept> clone() const = 0;
        };
        
        template<typename T>
        class Model : public Concept {
        private:
            T object;
        public:
            Model(T obj) : object(std::move(obj)) {}
            void draw() const override { object.draw(); }
            double area() const override { return object.area(); }
            std::unique_ptr<Concept> clone() const override {
                return std::make_unique<Model<T>>(object);
            }
        };
        
        std::unique_ptr<Concept> concept;
        
    public:
        template<typename T>
        TypeErasure(T object) : concept(std::make_unique<Model<T>>(std::move(object))) {}
        
        TypeErasure(const TypeErasure& other) : concept(other.concept->clone()) {}
        TypeErasure& operator=(const TypeErasure& other) {
            concept = other.concept->clone();
            return *this;
        }
        
        void draw() const { concept->draw(); }
        double area() const { return concept->area(); }
    };
    
    std::cout << "\nType erasure demonstration:" << std::endl;
    std::vector<TypeErasure> erased_shapes;
    erased_shapes.emplace_back(Circle(0, 0, 5));
    erased_shapes.emplace_back(Rectangle(10, 10, 4, 6));
    erased_shapes.emplace_back(Triangle(20, 20, 3, 4));
    
    for (const auto& shape : erased_shapes) {
        shape.draw();
        std::cout << "  Area: " << shape.area() << std::endl;
    }
    
    // 5. Polymorphic Function Objects
    std::cout << "\n5. POLYMORPHIC FUNCTION OBJECTS:" << std::endl;
    
    class PolymorphicFunction {
    private:
        class FunctionConcept {
        public:
            virtual ~FunctionConcept() = default;
            virtual double operator()(double x) const = 0;
            virtual std::unique_ptr<FunctionConcept> clone() const = 0;
        };
        
        template<typename F>
        class FunctionModel : public FunctionConcept {
        private:
            F function;
        public:
            FunctionModel(F f) : function(std::move(f)) {}
            double operator()(double x) const override { return function(x); }
            std::unique_ptr<FunctionConcept> clone() const override {
                return std::make_unique<FunctionModel<F>>(function);
            }
        };
        
        std::unique_ptr<FunctionConcept> concept;
        
    public:
        template<typename F>
        PolymorphicFunction(F f) : concept(std::make_unique<FunctionModel<F>>(std::move(f))) {}
        
        double operator()(double x) const { return (*concept)(x); }
    };
    
    std::cout << "\nPolymorphic function objects:" << std::endl;
    std::vector<PolymorphicFunction> functions;
    functions.emplace_back([](double x) { return x * x; });  // Square function
    functions.emplace_back([](double x) { return x * x * x; });  // Cube function
    functions.emplace_back([](double x) { return x + 1; });  // Linear function
    
    double x = 3.0;
    for (size_t i = 0; i < functions.size(); ++i) {
        double result = functions[i](x);
        std::cout << "Function " << i << "(" << x << ") = " << result << std::endl;
    }
    
    // 6. Performance Analysis
    std::cout << "\n6. PERFORMANCE ANALYSIS:" << std::endl;
    
    const int iterations = 1000000;
    
    // Non-virtual function calls
    auto start = std::chrono::high_resolution_clock::now();
    double sum = 0.0;
    for (int i = 0; i < iterations; ++i) {
        sum += static_cast<double>(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto non_virtual_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Non-virtual function calls time: " << non_virtual_time.count() << " microseconds" << std::endl;
    
    // Virtual function calls
    start = std::chrono::high_resolution_clock::now();
    sum = 0.0;
    std::unique_ptr<Shape> shape = std::make_unique<Circle>(0, 0, 5);
    for (int i = 0; i < iterations; ++i) {
        sum += shape->area();
    }
    end = std::chrono::high_resolution_clock::now();
    auto virtual_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "Virtual function calls time: " << virtual_time.count() << " microseconds" << std::endl;
    std::cout << "Virtual function overhead: " << (double)virtual_time.count() / non_virtual_time.count() << "x" << std::endl;
    
    // 7. Factory Pattern with Polymorphism
    std::cout << "\n7. FACTORY PATTERN WITH POLYMORPHISM:" << std::endl;
    
    class ShapeFactory {
    public:
        virtual ~ShapeFactory() = default;
        virtual std::unique_ptr<Shape> createShape() = 0;
        virtual std::string getShapeType() const = 0;
    };
    
    class CircleFactory : public ShapeFactory {
    public:
        std::unique_ptr<Shape> createShape() override {
            return std::make_unique<Circle>(0, 0, 5);
        }
        std::string getShapeType() const override {
            return "Circle";
        }
    };
    
    class RectangleFactory : public ShapeFactory {
    public:
        std::unique_ptr<Shape> createShape() override {
            return std::make_unique<Rectangle>(0, 0, 4, 6);
        }
        std::string getShapeType() const override {
            return "Rectangle";
        }
    };
    
    class TriangleFactory : public ShapeFactory {
    public:
        std::unique_ptr<Shape> createShape() override {
            return std::make_unique<Triangle>(0, 0, 3, 4);
        }
        std::string getShapeType() const override {
            return "Triangle";
        }
    };
    
    std::cout << "\nFactory pattern demonstration:" << std::endl;
    std::vector<std::unique_ptr<ShapeFactory>> factories;
    factories.push_back(std::make_unique<CircleFactory>());
    factories.push_back(std::make_unique<RectangleFactory>());
    factories.push_back(std::make_unique<TriangleFactory>());
    
    for (const auto& factory : factories) {
        auto shape = factory->createShape();
        std::cout << "Created " << factory->getShapeType() << " with area " << shape->area() << std::endl;
    }
    
    // 8. Strategy Pattern with Polymorphism
    std::cout << "\n8. STRATEGY PATTERN WITH POLYMORPHISM:" << std::endl;
    
    class DrawingStrategy {
    public:
        virtual ~DrawingStrategy() = default;
        virtual void draw(const Shape& shape) = 0;
    };
    
    class ConsoleDrawingStrategy : public DrawingStrategy {
    public:
        void draw(const Shape& shape) override {
            std::cout << "Console: ";
            shape.draw();
        }
    };
    
    class FileDrawingStrategy : public DrawingStrategy {
    public:
        void draw(const Shape& shape) override {
            std::cout << "File: Drawing " << shape.getType() << " to file" << std::endl;
        }
    };
    
    class NetworkDrawingStrategy : public DrawingStrategy {
    public:
        void draw(const Shape& shape) override {
            std::cout << "Network: Sending " << shape.getType() << " to remote server" << std::endl;
        }
    };
    
    class DrawingContext {
    private:
        std::unique_ptr<DrawingStrategy> strategy;
    public:
        void setStrategy(std::unique_ptr<DrawingStrategy> s) {
            strategy = std::move(s);
        }
        void drawShape(const Shape& shape) {
            if (strategy) {
                strategy->draw(shape);
            }
        }
    };
    
    std::cout << "\nStrategy pattern demonstration:" << std::endl;
    DrawingContext context;
    auto circle = std::make_unique<Circle>(0, 0, 5);
    
    context.setStrategy(std::make_unique<ConsoleDrawingStrategy>());
    context.drawShape(*circle);
    
    context.setStrategy(std::make_unique<FileDrawingStrategy>());
    context.drawShape(*circle);
    
    context.setStrategy(std::make_unique<NetworkDrawingStrategy>());
    context.drawShape(*circle);
    
    std::cout << "\nAdvanced polymorphism demonstration completed!" << std::endl;
    return 0;
}
