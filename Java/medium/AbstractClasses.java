/**
 * MEDIUM LEVEL - Lesson 5: Abstract Classes
 * 
 * This lesson covers:
 * - Abstract class definition
 * - Abstract methods
 * - Concrete methods in abstract classes
 * - Abstract class vs Interface
 * - When to use abstract classes
 */

// ========== ABSTRACT CLASS ==========

abstract class Animal {
    protected String name;
    protected int age;
    
    // Constructor
    public Animal(String name, int age) {
        this.name = name;
        this.age = age;
    }
    
    // Abstract method - must be implemented by subclasses
    public abstract void makeSound();
    
    // Abstract method
    public abstract void move();
    
    // Concrete method - can be used as-is or overridden
    public void eat() {
        System.out.println(name + " is eating");
    }
    
    // Concrete method
    public void sleep() {
        System.out.println(name + " is sleeping");
    }
    
    // Concrete method with implementation
    public void displayInfo() {
        System.out.println("Name: " + name);
        System.out.println("Age: " + age);
    }
    
    // Can have instance variables
    protected String habitat;
    
    public void setHabitat(String habitat) {
        this.habitat = habitat;
    }
    
    public String getHabitat() {
        return habitat;
    }
}

// private String habitat;  -- cannot be accessed outside the class
// protected String habitat;  -- can be accessed in subclasses
// public String habitat;   -- can be accessed anywhere

// ========== CONCRETE CLASS EXTENDING ABSTRACT CLASS ==========

class Dog extends Animal {
    private String breed;
    
    public Dog(String name, int age, String breed) {
        super(name, age);
        this.breed = breed;
    }
    
    // Must implement abstract methods
    @Override
    public void makeSound() {
        System.out.println(name + " barks: Woof! Woof!");
    }
    
    @Override
    public void move() {
        System.out.println(name + " runs on four legs");
    }
    
    // Can override concrete methods
    @Override
    public void displayInfo() {
        super.displayInfo();
        System.out.println("Breed: " + breed);
    }
    
    // Additional method specific to Dog
    public void fetch() {
        System.out.println(name + " is fetching");
    }
}

class Cat extends Animal {
    private boolean isIndoor;
    
    public Cat(String name, int age, boolean isIndoor) {
        super(name, age);
        this.isIndoor = isIndoor;
    }
    
    @Override
    public void makeSound() {
        System.out.println(name + " meows: Meow! Meow!");
    }
    
    @Override
    public void move() {
        System.out.println(name + " walks silently");
    }
    
    public void climb() {
        System.out.println(name + " is climbing");
    }
}

class Bird extends Animal {
    private boolean canFly;
    
    public Bird(String name, int age, boolean canFly) {
        super(name, age);
        this.canFly = canFly;
    }
    
    @Override
    public void makeSound() {
        System.out.println(name + " chirps: Tweet! Tweet!");
    }
    
    @Override
    public void move() {
        if (canFly) {
            System.out.println(name + " flies through the air");
        } else {
            System.out.println(name + " walks on the ground");
        }
    }
}

// ========== ANOTHER ABSTRACT CLASS EXAMPLE ==========

abstract class Vehicle {
    protected String brand;
    protected int year;
    
    public Vehicle(String brand, int year) {
        this.brand = brand;
        this.year = year;
    }
    
    // Abstract method
    public abstract void start();
    
    public abstract void stop();
    
    // Concrete method
    public void displayInfo() {
        System.out.println("Brand: " + brand + ", Year: " + year);
    }
    
    // Can have final methods (cannot be overridden)
    public final void honk() {
        System.out.println("Beep! Beep!");
    }
}

// abstract -- cannot be instantiated directly, must be extended and implement abstract methods
// final -- cannot be extended

class Car extends Vehicle {
    private int doors;
    
    public Car(String brand, int year, int doors) {
        super(brand, year);
        this.doors = doors;
    }
    
    @Override
    public void start() {
        System.out.println("Car engine started");
    }
    
    @Override
    public void stop() {
        System.out.println("Car engine stopped");
    }
    
    @Override
    public void displayInfo() {
        super.displayInfo();
        System.out.println("Doors: " + doors);
    }
}

// ========== MAIN CLASS ==========

public class AbstractClasses {
    public static void main(String[] args) {
        System.out.println("=== Abstract Classes ===");
        
        // Cannot instantiate abstract class directly
        // Animal animal = new Animal("Generic", 5);  // This would cause error
        
        System.out.println("\n=== Creating Concrete Subclasses ===");
        
        Dog dog = new Dog("Buddy", 3, "Golden Retriever");
        dog.makeSound();  // Implemented abstract method -- overridden
        dog.move();       // Implemented abstract method -- overridden
        dog.eat();        // Inherited concrete method -- can be used as-is parent
        dog.sleep();      // Inherited concrete method -- can be used as-is parent
        dog.displayInfo(); // Overridden concrete method
        dog.fetch();      // Dog-specific method
        
        System.out.println("\n--- Cat ---");
        Cat cat = new Cat("Whiskers", 2, true);
        cat.makeSound();    // Implemented abstract method -- overridden
        cat.move();         // Implemented abstract method -- overridden
        cat.eat();          // Inherited concrete method -- can be used as-is parent
        cat.climb();        // Cat-specific method
        
        System.out.println("\n--- Bird ---");
        Bird bird = new Bird("Tweety", 1, true);
        bird.makeSound();   // Implemented abstract method -- overridden
        bird.move();        // Implemented abstract method -- overridden
        bird.setHabitat("Forest");  // Bird-specific method
        System.out.println("Habitat: " + bird.getHabitat());
        
        System.out.println("\n=== Polymorphism with Abstract Classes ===");
        Animal[] animals = {    // Array of Animal references, variable name is animals
            new Dog("Rex", 4, "German Shepherd"),
            new Cat("Fluffy", 3, false),
            new Bird("Polly", 2, true)
        };
        
        for (Animal animal : animals) {
            System.out.println("\n--- Processing Animal ---");
            animal.displayInfo();
            animal.makeSound();
            animal.move();
        }
        
        System.out.println("\n=== Vehicle Example ===");
        Car car = new Car("Toyota", 2023, 4);
        car.displayInfo();
        car.start();
        car.honk();  // Final method, cannot be overridden
        car.stop();
        
        System.out.println("\n=== Abstract Class vs Interface ===");
        System.out.println("Abstract Class:");
        System.out.println("- Can have instance variables");
        System.out.println("- Can have constructors");
        System.out.println("- Can have both abstract and concrete methods");
        System.out.println("- Single inheritance (extends one class)");
        System.out.println("- Use when classes share common state/behavior");
        System.out.println();
        System.out.println("Interface:");
        System.out.println("- Cannot have instance variables (only constants)");
        System.out.println("- Cannot have constructors");
        System.out.println("- Methods are abstract by default (Java 8+ allows default/static)");
        System.out.println("- Multiple inheritance (implements multiple interfaces)");
        System.out.println("- Use when defining a contract/behavior");
    }
}

