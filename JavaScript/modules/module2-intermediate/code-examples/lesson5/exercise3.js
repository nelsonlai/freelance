// Exercise 3: Advanced OOP Concepts
// This exercise demonstrates advanced object-oriented programming concepts

console.log("=== Exercise 3: Advanced OOP Concepts ===");

// Example 1: Abstract-like behavior with base class
console.log("\n=== Abstract-like Base Class ===");
class Shape {
    constructor(name) {
        this.name = name;
    }
    
    // This method should be overridden by subclasses
    calculateArea() {
        throw new Error("calculateArea() must be implemented by subclass");
    }
    
    // This method should be overridden by subclasses
    calculatePerimeter() {
        throw new Error("calculatePerimeter() must be implemented by subclass");
    }
    
    getInfo() {
        return `${this.name} - Area: ${this.calculateArea()}, Perimeter: ${this.calculatePerimeter()}`;
    }
}

// Rectangle class extending Shape
class Rectangle extends Shape {
    constructor(width, height) {
        super("Rectangle");
        this.width = width;
        this.height = height;
    }
    
    calculateArea() {
        return this.width * this.height;
    }
    
    calculatePerimeter() {
        return 2 * (this.width + this.height);
    }
}

// Circle class extending Shape
class Circle extends Shape {
    constructor(radius) {
        super("Circle");
        this.radius = radius;
    }
    
    calculateArea() {
        return Math.PI * this.radius * this.radius;
    }
    
    calculatePerimeter() {
        return 2 * Math.PI * this.radius;
    }
}

// Testing Shape inheritance
console.log("Creating shapes...");
let rectangle = new Rectangle(5, 3);
let circle = new Circle(4);

console.log("Rectangle info:", rectangle.getInfo());
console.log("Circle info:", circle.getInfo());

// Example 2: Composition over inheritance
console.log("\n=== Composition Example ===");
class Engine {
    constructor(type, horsepower) {
        this.type = type;
        this.horsepower = horsepower;
        this.isRunning = false;
    }
    
    start() {
        this.isRunning = true;
        return `${this.type} engine started (${this.horsepower} HP)`;
    }
    
    stop() {
        this.isRunning = false;
        return `${this.type} engine stopped`;
    }
    
    getStatus() {
        return `${this.type} engine - ${this.horsepower} HP - ${this.isRunning ? 'Running' : 'Stopped'}`;
    }
}

class Wheel {
    constructor(size, brand) {
        this.size = size;
        this.brand = brand;
    }
    
    rotate() {
        return `Wheel rotating (${this.size}" ${this.brand})`;
    }
    
    getInfo() {
        return `${this.size}" ${this.brand} wheel`;
    }
}

class Vehicle {
    constructor(brand, model, engine, wheels) {
        this.brand = brand;
        this.model = model;
        this.engine = engine; // Composition
        this.wheels = wheels; // Composition
        this.speed = 0;
    }
    
    start() {
        return `${this.brand} ${this.model}: ${this.engine.start()}`;
    }
    
    stop() {
        this.speed = 0;
        return `${this.brand} ${this.model}: ${this.engine.stop()}`;
    }
    
    accelerate() {
        if (this.engine.isRunning) {
            this.speed += 10;
            return `${this.brand} ${this.model} accelerating to ${this.speed} mph`;
        }
        return "Start the vehicle first";
    }
    
    getVehicleInfo() {
        return `${this.brand} ${this.model} with ${this.engine.getStatus()}`;
    }
    
    getWheelInfo() {
        return this.wheels.map(wheel => wheel.getInfo()).join(', ');
    }
}

// Creating vehicles using composition
let v8Engine = new Engine("V8", 400);
let wheels = [
    new Wheel(18, "Michelin"),
    new Wheel(18, "Michelin"),
    new Wheel(18, "Michelin"),
    new Wheel(18, "Michelin")
];

let vehicle = new Vehicle("Ford", "Mustang", v8Engine, wheels);

console.log("Vehicle info:", vehicle.getVehicleInfo());
console.log("Wheels:", vehicle.getWheelInfo());
console.log("Start:", vehicle.start());
console.log("Accelerate:", vehicle.accelerate());
console.log("Accelerate:", vehicle.accelerate());
console.log("Stop:", vehicle.stop());

// Example 3: Polymorphism
console.log("\n=== Polymorphism Example ===");
class Animal {
    constructor(name) {
        this.name = name;
    }
    
    makeSound() {
        return `${this.name} makes a sound`;
    }
    
    move() {
        return `${this.name} moves`;
    }
}

class Dog extends Animal {
    makeSound() {
        return `${this.name} barks: Woof! Woof!`;
    }
    
    move() {
        return `${this.name} runs`;
    }
}

class Bird extends Animal {
    makeSound() {
        return `${this.name} chirps: Tweet! Tweet!`;
    }
    
    move() {
        return `${this.name} flies`;
    }
}

class Fish extends Animal {
    makeSound() {
        return `${this.name} bubbles silently`;
    }
    
    move() {
        return `${this.name} swims`;
    }
}

// Polymorphism in action
let animals = [
    new Dog("Buddy"),
    new Bird("Tweety"),
    new Fish("Nemo"),
    new Animal("Generic Animal")
];

console.log("Polymorphism demonstration:");
animals.forEach(animal => {
    console.log(`${animal.name}: ${animal.makeSound()}`);
    console.log(`${animal.name}: ${animal.move()}`);
    console.log("---");
});

// Example 4: Encapsulation with private-like properties
console.log("\n=== Encapsulation Example ===");
class BankAccount {
    constructor(accountNumber, ownerName, initialBalance = 0) {
        this.accountNumber = accountNumber;
        this.ownerName = ownerName;
        this._balance = initialBalance; // Convention: underscore indicates "private"
        this._transactions = [];
    }
    
    // Getter for balance (read-only access)
    get balance() {
        return this._balance;
    }
    
    // Getter for transactions (read-only access)
    get transactions() {
        return [...this._transactions]; // Return copy to prevent external modification
    }
    
    deposit(amount) {
        if (amount > 0) {
            this._balance += amount;
            this._transactions.push({
                type: 'deposit',
                amount: amount,
                date: new Date(),
                balance: this._balance
            });
            return `Deposited $${amount}. New balance: $${this._balance}`;
        }
        return "Invalid deposit amount";
    }
    
    withdraw(amount) {
        if (amount > 0 && amount <= this._balance) {
            this._balance -= amount;
            this._transactions.push({
                type: 'withdrawal',
                amount: amount,
                date: new Date(),
                balance: this._balance
            });
            return `Withdrew $${amount}. New balance: $${this._balance}`;
        }
        return "Insufficient funds or invalid amount";
    }
    
    getAccountSummary() {
        return `Account ${this.accountNumber} (${this.ownerName}): $${this._balance}`;
    }
}

// Testing encapsulation
let account = new BankAccount("ACC001", "Alice Johnson", 1000);
console.log("Account summary:", account.getAccountSummary());
console.log("Balance (getter):", account.balance);
console.log("Deposit:", account.deposit(500));
console.log("Withdraw:", account.withdraw(200));
console.log("Transactions:", account.transactions.length);
console.log("Final balance:", account.balance);

// Try to access "private" properties (this will work but is not recommended)
console.log("Direct access to _balance:", account._balance); // Not recommended
console.log("Direct access to _transactions:", account._transactions.length); // Not recommended

console.log("\n=== Advanced OOP Concepts Summary ===");
console.log("✓ Abstract-like behavior with base classes");
console.log("✓ Composition over inheritance");
console.log("✓ Polymorphism with method overriding");
console.log("✓ Encapsulation with private-like properties");
console.log("✓ Getters for controlled access to properties");
console.log("✓ Error handling in abstract methods");
