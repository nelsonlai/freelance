/**
 * MEDIUM LEVEL - Lesson 4: Interfaces
 * 
 * This lesson covers:
 * - Interface definition
 * - Implementing interfaces
 * - Multiple interface implementation
 * - Default methods in interfaces
 * - Static methods in interfaces
 * - Functional interfaces
 * - Interface inheritance
 */

// ========== BASIC INTERFACE ==========

interface Drawable {
    // Abstract method (implicitly public and abstract)
    void draw();
    
    // Default method (Java 8+)
    default void drawWithColor(String color) {
        System.out.println("Drawing with color: " + color);
        draw();
    }
    
    // Static method (Java 8+)
    static void printInfo() {
        System.out.println("This is a Drawable interface");
    }
}

// ========== INTERFACE WITH MULTIPLE METHODS ==========

interface Resizable {
    void resize(double factor);
    void resize(int width, int height);
}


// ========== INTERFACE INHERITANCE ==========

interface Shape extends Drawable {
    double getArea();
    double getPerimeter();
}

// ========== CLASSES IMPLEMENTING INTERFACES ==========

class Circle implements Drawable {      // Interface can be implemented by a class
    private double radius;
    
    public Circle(double radius) {
        this.radius = radius;
    }
    
    @Override
    public void draw() {
        System.out.println("Drawing a circle with radius " + radius);
    }
}

class Rectangle implements Drawable, Resizable {
    private double width;
    private double height;
    
    public Rectangle(double width, double height) {
        this.width = width;
        this.height = height;
    }
    
    @Override
    public void draw() {
        System.out.println("Drawing a rectangle " + width + "x" + height);
    }
    
    @Override
    public void resize(double factor) {
        width *= factor;
        height *= factor;
        System.out.println("Resized by factor " + factor + ": " + width + "x" + height);
    }
    
    @Override
    public void resize(int width, int height) {
        this.width = width;
        this.height = height;
        System.out.println("Resized to: " + width + "x" + height);
    }
}

class Square implements Shape {
    private double side;
    
    public Square(double side) {
        this.side = side;
    }
    
    @Override
    public void draw() {        // From Drawable interface
        System.out.println("Drawing a square with side " + side);
    }
    
    @Override
    public double getArea() {   // From Shape interface
        return side * side;
    }
    
    @Override
    public double getPerimeter() {  // From Shape interface
        return 4 * side;
    }
}

// ========== FUNCTIONAL INTERFACE (Single Abstract Method) ==========

@FunctionalInterface    // This annotation indicates that the interface is a functional interface, can have only one abstract method
interface Calculator {
    int calculate(int a, int b);
}
// ========== MAIN CLASS ==========

public class Interfaces {
    public static void main(String[] args) {
        System.out.println("=== Basic Interface Implementation ===");
        
        Drawable circle = new Circle(5.0);
        circle.draw();
        circle.drawWithColor("Red");  // Using default method
        
        System.out.println("\n=== Multiple Interface Implementation ===");
        Rectangle rect = new Rectangle(4.0, 6.0);
        rect.draw();
        rect.resize(1.5);  // Resize by factor
        rect.resize(8, 12);  // Resize to specific dimensions
        
        System.out.println("\n=== Interface Inheritance ===");
        Square square = new Square(5.0);
        square.draw();  // From Drawable interface
        System.out.println("Area: " + square.getArea());
        System.out.println("Perimeter: " + square.getPerimeter());
        
        System.out.println("\n=== Static Methods in Interfaces ===");
        Drawable.printInfo();  // Call static method
        
        System.out.println("\n=== Functional Interfaces ===");
        
        // Using lambda expressions with functional interfaces
        Calculator add = (a, b) -> a + b;
        Calculator multiply = (a, b) -> a * b;
        Calculator subtract = (a, b) -> a - b;
        
        System.out.println("10 + 5 = " + add.calculate(10, 5));
        System.out.println("10 * 5 = " + multiply.calculate(10, 5));
        System.out.println("10 - 5 = " + subtract.calculate(10, 5));
        
        // Anonymous inner class implementation
        Calculator divide = new Calculator() {
            @Override
            public int calculate(int a, int b) {
                return b != 0 ? a / b : 0;
            }
        };
        System.out.println("10 / 5 = " + divide.calculate(10, 5));
        
        System.out.println("\n=== Polymorphism with Interfaces ===");
        Drawable[] drawables = {
            new Circle(3.0),
            new Rectangle(2.0, 4.0),
            new Square(5.0)
        };
        
        for (Drawable d : drawables) {
            d.draw();
        }
        
        System.out.println("\n=== Using Interface as Type ===");
        processDrawable(new Circle(7.0));
        processDrawable(new Rectangle(3.0, 5.0));
    }
    
    // Method accepting interface type (polymorphism)
    public static void processDrawable(Drawable drawable) {
        System.out.println("Processing drawable object...");
        drawable.draw();
    }
}

