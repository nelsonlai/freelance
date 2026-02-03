// Exercise 2: Create a SportsCar Class
// This exercise demonstrates inheritance by extending the Car class

console.log("=== Exercise 2: SportsCar Class (Inheritance) ===");

// First, we need the base Car class
class Car {
    constructor(brand, model, year) {
        this.brand = brand;
        this.model = model;
        this.year = year;
        this.speed = 0;
        this.isRunning = false;
    }
    
    start() {
        if (!this.isRunning) {
            this.isRunning = true;
            return `The ${this.getInfo()} has been started`;
        }
        return "The car is already running";
    }
    
    stop() {
        if (this.isRunning) {
            this.isRunning = false;
            this.speed = 0;
            return `The ${this.getInfo()} has been stopped`;
        }
        return "The car is already stopped";
    }
    
    accelerate() {
        if (this.isRunning) {
            this.speed += 10;
            return `Speed is now ${this.speed} mph`;
        }
        return "Start the car first";
    }
    
    brake() {
        if (this.speed > 0) {
            this.speed -= 10;
            if (this.speed < 0) this.speed = 0;
            return `Speed is now ${this.speed} mph`;
        }
        return "Car is already stopped";
    }
    
    getInfo() {
        return `${this.year} ${this.brand} ${this.model}`;
    }
}

// SportsCar class extending Car
class SportsCar extends Car {
    constructor(brand, model, year, topSpeed) {
        super(brand, model, year); // Call parent constructor
        this.topSpeed = topSpeed;
        this.turboMode = false;
    }
    
    // Override accelerate method for faster acceleration
    accelerate() {
        if (this.isRunning) {
            const acceleration = this.turboMode ? 25 : 20;
            this.speed += acceleration;
            
            // Prevent exceeding top speed
            if (this.speed > this.topSpeed) {
                this.speed = this.topSpeed;
            }
            
            return `Sports car speed is now ${this.speed} mph`;
        }
        return "Start the car first";
    }
    
    // New method specific to SportsCar
    enableTurbo() {
        this.turboMode = true;
        return `Turbo mode enabled for ${this.getInfo()}`;
    }
    
    disableTurbo() {
        this.turboMode = false;
        return `Turbo mode disabled for ${this.getInfo()}`;
    }
    
    getTopSpeed() {
        return `Top speed: ${this.topSpeed} mph`;
    }
    
    // Override getInfo to include sports car specific info
    getInfo() {
        return `${this.year} ${this.brand} ${this.model} (Sports Car)`;
    }
    
    getStatus() {
        return {
            ...super.getStatus ? super.getStatus() : {},
            info: this.getInfo(),
            speed: this.speed,
            isRunning: this.isRunning,
            topSpeed: this.topSpeed,
            turboMode: this.turboMode
        };
    }
}

// Testing the SportsCar class
console.log("Creating a sports car...");
let sportsCar = new SportsCar("Ferrari", "488 GTB", 2023, 205);

console.log("Sports car info:", sportsCar.getInfo());
console.log("Top speed:", sportsCar.getTopSpeed());

console.log("\nTesting sports car operations:");
console.log("Start:", sportsCar.start());
console.log("Accelerate:", sportsCar.accelerate());
console.log("Accelerate:", sportsCar.accelerate());
console.log("Enable turbo:", sportsCar.enableTurbo());
console.log("Accelerate with turbo:", sportsCar.accelerate());
console.log("Accelerate with turbo:", sportsCar.accelerate());
console.log("Disable turbo:", sportsCar.disableTurbo());
console.log("Brake:", sportsCar.brake());
console.log("Stop:", sportsCar.stop());

// Testing inheritance - SportsCar should have all Car methods
console.log("\nTesting inheritance:");
console.log("Sports car can use parent methods:");
console.log("Start:", sportsCar.start());
console.log("Accelerate:", sportsCar.accelerate());
console.log("Brake:", sportsCar.brake());
console.log("Stop:", sportsCar.stop());

// Comparing regular car vs sports car
console.log("\n=== Comparison: Regular Car vs Sports Car ===");
let regularCar = new Car("Honda", "Civic", 2023);
let anotherSportsCar = new SportsCar("Porsche", "911", 2023, 191);

console.log("Regular car:", regularCar.getInfo());
console.log("Sports car:", anotherSportsCar.getInfo());

console.log("\nBoth cars starting and accelerating:");
console.log("Regular car start:", regularCar.start());
console.log("Sports car start:", anotherSportsCar.start());

console.log("Regular car accelerate:", regularCar.accelerate());
console.log("Sports car accelerate:", anotherSportsCar.accelerate());

console.log("Regular car accelerate:", regularCar.accelerate());
console.log("Sports car accelerate:", anotherSportsCar.accelerate());

console.log("\nSports car turbo boost:");
console.log("Enable turbo:", anotherSportsCar.enableTurbo());
console.log("Sports car accelerate:", anotherSportsCar.accelerate());
console.log("Sports car accelerate:", anotherSportsCar.accelerate());
