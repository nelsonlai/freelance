// Lesson 3: Template Literals Examples

console.log("=== Basic Template Literals ===");

let name = "Alice";
let age = 30;
let city = "New York";

// Simple interpolation
let message = `Hello, ${name}!`;
console.log(message); // "Hello, Alice!"

// Multiple variables
let info = `${name} is ${age} years old and lives in ${city}.`;
console.log(info); // "Alice is 30 years old and lives in New York."

// Expressions
let calculation = `The sum of 5 and 3 is ${5 + 3}.`;
console.log(calculation); // "The sum of 5 and 3 is 8."

console.log("\n=== Multi-line Strings ===");

// Old way (concatenation)
let oldMultiLine = "This is line 1\n" +
                   "This is line 2\n" +
                   "This is line 3";

// New way (template literals)
let newMultiLine = `This is line 1
This is line 2
This is line 3`;

console.log("Old way:");
console.log(oldMultiLine);
console.log("\nNew way:");
console.log(newMultiLine);

console.log("\n=== Complex Examples ===");

let product = "Laptop";
let price = 999.99;
let discount = 0.15;
let finalPrice = price * (1 - discount);

let description = `Product: ${product}
Original Price: $${price}
Discount: ${discount * 100}%
Final Price: $${finalPrice.toFixed(2)}`;

console.log(description);
