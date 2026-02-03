/**
 * MEDIUM LEVEL - Lesson 3: Polymorphism
 * 
 * This lesson covers:
 * - Runtime polymorphism (method overriding)
 * - Compile-time polymorphism (method overloading)
 * - Dynamic method dispatch
 * - Virtual method invocation
 * - Upcasting and downcasting
 */

// ========== BASE CLASS ==========
// Encapsulation
// Inheritance
// Polymorphism
// Abstraction class

class Shape {
    protected String name;
    
    public Shape(String name) {  // Shape constructor
        this.name = name;
    }
    
    // Method to be overridden (polymorphic method)
    public double calculateArea() {
        return 0.0;
    }
    
    public double calculatePerimeter() {
        return 0.0;
    }
    
    public void displayInfo() {
        System.out.println("Shape: " + name);
        System.out.println("Area: " + calculateArea());
        System.out.println("Perimeter: " + calculatePerimeter());
    }
}

// ========== DERIVED CLASSES ==========

class Circle extends Shape {    // Circle is extended from Shape class. Shape is the parent class of Circle.
    private double radius;
    
    public Circle(double radius) {  // Circle constructor
        super("Circle");  // Call Shape (parent class)constructor
        this.radius = radius;  // Initialize radius
    }
    
    @Override
    public double calculateArea() {
        return Math.PI * radius * radius;
    }
    
    @Override
    public double calculatePerimeter() {
        return 2 * Math.PI * radius;
    }
}

class Rectangle extends Shape {
    private double width;
    private double height;
    
    public Rectangle(double width, double height) {     // Rectangle constructor
        super("Rectangle");
        this.width = width;
        this.height = height;
    }
    
    @Override
    public double calculateArea() {
        return width * height;
    }
    
    @Override
    public double calculatePerimeter() {
        return 2 * (width + height);
    }
}

class Triangle extends Shape {
    private double base;
    private double height;
    private double side1, side2;
    
    public Triangle(double base, double height, double side1, double side2) {
        super("Triangle");
        this.base = base;
        this.height = height;
        this.side1 = side1;
        this.side2 = side2;
    }
    
    @Override
    public double calculateArea() {
        return 0.5 * base * height;
    }
    
    @Override
    public double calculatePerimeter() {
        return base + side1 + side2;
    }
}

// ========== CLASS DEMONSTRATING METHOD OVERLOADING (COMPILE-TIME POLYMORPHISM) ==========

class Calculator {
    // Method overloading - same method name, different parameters
    public int add(int a, int b) {
        return a + b;
    }
    
    public double add(double a, double b) {
        return a + b;
    }
    
    public int add(int a, int b, int c) {
        return a + b + c;
    }
    
    public String add(String a, String b) {
        return a + b;  // String concatenation
    }
    
    public int add(int... numbers) {    // variables arguments
        int sum = 0;
        for (int num : numbers) {
            sum += num;
        }
        return sum;
    }
}

// ========== MAIN CLASS ==========

public class Polymorphism {
    public static void main(String[] args) {
        System.out.println("=== Runtime Polymorphism (Method Overriding) ===");
        
        // Parent reference pointing to child objects
        Shape shape1 = new Circle(5.0);
        Shape shape2 = new Rectangle(4.0, 6.0);
        Shape shape3 = new Triangle(3.0, 4.0, 3.0, 5.0);
        
        // Dynamic method dispatch - calls the overridden method at runtime
        System.out.println("\n--- Circle ---");
        shape1.displayInfo();
        
        System.out.println("\n--- Rectangle ---");
        shape2.displayInfo();
        
        System.out.println("\n--- Triangle ---");
        shape3.displayInfo();
        
        // Array of shapes (polymorphism in action)
        System.out.println("\n=== Array of Shapes ===");
        Shape[] shapes = {
            new Circle(3.0),
            new Rectangle(2.0, 4.0),
            new Triangle(3.0, 4.0, 3.0, 5.0),
            new Circle(7.0)
        };
        
        double totalArea = 0;
        double totalPerimeter = 0;
        for (Shape shape : shapes) {
            totalArea += shape.calculateArea();  // Calls appropriate method
            totalPerimeter += shape.calculatePerimeter();
        }
        System.out.println("Total area of all shapes: " + totalArea);
        System.out.println("Total perimeter of all shapes: " + totalPerimeter);
        System.out.println("\n=== Compile-time Polymorphism (Method Overloading) ===");

        // Create an instance of the Calculator class
        Calculator calc = new Calculator();
        
        System.out.println("add(5, 3) = " + calc.add(5, 3));
        System.out.println("add(5.5, 3.2) = " + calc.add(5.5, 3.2));
        System.out.println("add(1, 2, 3) = " + calc.add(1, 2, 3));
        System.out.println("add(\"Hello\", \" World\") = " + calc.add("Hello", " World"));
        System.out.println("add(1, 2, 3, 4, 5) = " + calc.add(1, 2, 3, 4, 5));
        System.out.println("add(2, 7, 11, 23, 13, 23, 45, 8) = " + calc.add(2, 7, 11, 23, 13, 23, 45, 8));
        
        System.out.println("\n=== Upcasting and Downcasting ===");
        
        // Upcasting (implicit) - Child to Parent
        Shape shape = new Circle(10.0);     // shape is a reference of type Shape pointing to a Circle object
        
        // Downcasting (explicit) - Parent to Child
        if (shape instanceof Circle) {
            Circle circle = (Circle) shape;  // Explicit cast
            System.out.println("Downcast successful. Circle created.");
        }
        
        // Safe downcasting with instanceof check
        Shape unknownShape = new Rectangle(5.0, 5.0);
        if (unknownShape instanceof Circle) {
            Circle c = (Circle) unknownShape;
            System.out.println("This is a circle");
        } else if (unknownShape instanceof Rectangle) {
            Rectangle r = (Rectangle) unknownShape;
            System.out.println("This is a rectangle");
        }
        
        System.out.println("\n=== Polymorphic Method Calls ===");
        printShapeInfo(new Circle(5.0));
        printShapeInfo(new Rectangle(4.0, 6.0));
        printShapeInfo(new Triangle(3.0, 4.0, 3.0, 5.0));
    }
    
    // Method that accepts any Shape (polymorphism)
    public static void printShapeInfo(Shape shape) {
        System.out.println("--- " + shape.name + " ---");
        System.out.println("Area: " + shape.calculateArea());
        System.out.println("Perimeter: " + shape.calculatePerimeter());
    }
}

