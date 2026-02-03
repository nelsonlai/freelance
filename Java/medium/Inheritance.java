/**
 * MEDIUM LEVEL - Lesson 2: Inheritance
 * 
 * This lesson covers:
 * - Class inheritance (extends keyword)
 * - Method overriding
 * - super keyword
 * - Constructor chaining
 * - Access modifiers in inheritance
 * - instanceof operator
 */

// ========== PARENT CLASS (BASE CLASS) ==========

class Animal {
    protected String name;
    protected int age;
    
    public Animal(String name, int age) {
        this.name = name;
        this.age = age;
        System.out.println("Animal constructor called");
    }
    
    public void eat() {
        System.out.println(name + " is eating");
    }
    
    public void sleep() {
        System.out.println(name + " is sleeping");
    }
    
    public void makeSound() {
        System.out.println(name + " makes a sound");
    }
    
    public void displayInfo() {
        System.out.println("Animal: " + name + ", Age: " + age);
    }
    
    // Method that can be overridden
    public String getType() {
        return "Unknown Animal";
    }
}

// ========== CHILD CLASS 1 ==========

class Dog extends Animal {
    private String breed;
    
    public Dog(String name, int age, String breed) {
        super(name, age);  // Call parent constructor
        this.breed = breed;
        System.out.println("Dog constructor called");
    }
    
    // Method overriding
    @Override
    public void makeSound() {
        System.out.println(name + " barks: Woof! Woof!");
    }
    
    @Override
    public String getType() {
        return "Dog";
    }
    
    // Additional method specific to Dog
    public void fetch() {
        System.out.println(name + " is fetching the ball");
    }
    
    @Override
    public void displayInfo() {
        super.displayInfo();  // Call parent method
        System.out.println("Breed: " + breed);
    }
}

// ========== CHILD CLASS 2 ==========

class Cat extends Animal {
    private boolean isIndoor;
    
    public Cat(String name, int age, boolean isIndoor) {
        super(name, age);
        this.isIndoor = isIndoor;
        System.out.println("Cat constructor called");
    }
    
    @Override
    public void makeSound() {
        System.out.println(name + " meows: Meow! Meow!");
    }
    
    @Override
    public String getType() {
        return "Cat";
    }
    
    // Additional method specific to Cat
    public void climb() {
        System.out.println(name + " is climbing");
    }
    
    @Override
    public void displayInfo() {
        super.displayInfo();
        System.out.println("Indoor cat: " + isIndoor);
    }
}

// ========== MULTI-LEVEL INHERITANCE ========== 

class Puppy extends Dog {   // Puppy extends Dog, which extends Animal
    private boolean isTrained;
    
    public Puppy(String name, int age, String breed, boolean isTrained) {
        super(name, age, breed);
        this.isTrained = isTrained;
        System.out.println("Puppy constructor called");
    }
    
    @Override
    public void makeSound() {
        System.out.println(name + " yelps: Yip! Yip!");
    }
    
    @Override
    public String getType() {
        return "Puppy";
    }
    
    public void play() {
        System.out.println(name + " is playing");
    }
}

// ========== MAIN CLASS ==========

public class Inheritance {
    public static void main(String[] args) {
        System.out.println("=== Creating Animal Objects ===");
        
        // Creating parent class object
        Animal animal = new Animal("Generic Animal", 5);
        animal.eat();
        animal.sleep();
        animal.makeSound();
        System.out.println();
        
        System.out.println("=== Creating Dog Object ===");
        Dog dog = new Dog("Buddy", 3, "Golden Retriever");
        dog.eat();        // Inherited from Animal
        dog.sleep();      // Inherited from Animal
        dog.makeSound();  // Overridden method
        dog.fetch();      // Dog-specific method
        dog.displayInfo();
        System.out.println("Type: " + dog.getType());
        System.out.println();
        
        System.out.println("=== Creating Cat Object ===");
        Cat cat = new Cat("Whiskers", 2, true);
        cat.eat();
        cat.sleep();
        cat.makeSound();  // Overridden method
        cat.climb();      // Cat-specific method
        cat.displayInfo();
        System.out.println("Type: " + cat.getType());
        System.out.println();
        
        System.out.println("=== Multi-level Inheritance ===");
        Puppy puppy = new Puppy("Max", 1, "Labrador", false);
        puppy.eat();      // Inherited from Animal
        puppy.makeSound(); // Overridden in Puppy
        puppy.fetch();    // Inherited from Dog
        puppy.play();     // Puppy-specific method
        puppy.displayInfo();
        System.out.println();
        
        System.out.println("=== Polymorphism with Inheritance ===");
        // Parent reference can point to child objects
        Animal animal1 = new Dog("Rex", 4, "German Shepherd");
        Animal animal2 = new Cat("Fluffy", 3, false);
        
        animal1.makeSound();  // Calls Dog's makeSound()
        animal2.makeSound();  // Calls Cat's makeSound()
        System.out.println();
        
        System.out.println("=== instanceof Operator ===");
        System.out.println("animal1 is Animal: " + (animal1 instanceof Animal));
        System.out.println("animal1 is Dog: " + (animal1 instanceof Dog));
        System.out.println("animal1 is Cat: " + (animal1 instanceof Cat));
        System.out.println("dog is Animal: " + (dog instanceof Animal));
        System.out.println("puppy is Dog: " + (puppy instanceof Dog));
        System.out.println("puppy is Animal: " + (puppy instanceof Animal));
        System.out.println();
        
        System.out.println("=== Array of Animals (Polymorphism) ===");
        Animal[] animals = {    // Array of Animal references, variable name is animals
            new Dog("Spot", 5, "Dalmatian"),
            new Cat("Mittens", 4, true),
            new Puppy("Tiny", 1, "Beagle", true)
        };
        
        for (Animal a : animals) {
            System.out.println("Type: " + a.getType());
            a.makeSound();
        }
    }
}

