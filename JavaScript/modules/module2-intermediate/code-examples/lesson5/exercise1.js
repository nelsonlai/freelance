// Exercise 1: Create a Car Class
// This exercise demonstrates basic class creation with properties and methods

console.log("=== Exercise 1: Car Class ===");

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
    
    getStatus() {
        return {
            info: this.getInfo(),
            speed: this.speed,
            isRunning: this.isRunning
        };
    }
}

// Testing the Car class
console.log("Creating a new car...");
let myCar = new Car("Toyota", "Camry", 2023);

console.log("Car info:", myCar.getInfo());
console.log("Initial status:", myCar.getStatus());

console.log("\nTesting car operations:");
console.log("Start:", myCar.start());
console.log("Accelerate:", myCar.accelerate());
console.log("Accelerate:", myCar.accelerate());
console.log("Brake:", myCar.brake());
console.log("Stop:", myCar.stop());

console.log("\nFinal status:", myCar.getStatus());

// Testing edge cases
console.log("\nTesting edge cases:");
console.log("Accelerate when stopped:", myCar.accelerate());
console.log("Start again:", myCar.start());
console.log("Brake when stopped:", myCar.brake());
console.log("Stop when already stopped:", myCar.stop());
