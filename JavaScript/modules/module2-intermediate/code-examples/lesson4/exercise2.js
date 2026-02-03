// Exercise 2: Import and Use Utilities
// This demonstrates how to import and use utility functions from modules

console.log("=== Exercise 2: Import and Use Utilities ===");

// In a real project, you would import like this:
// import validateEmail, { formatCurrency, formatDate, formatTime, capitalize, truncate, generateId } from './utils.js';

// For this example, we'll simulate the imported functions
// (In practice, these would come from the utils.js module)

// Simulated imports (these would be actual imports in a real project)
function formatCurrency(amount) {
    return `$${amount.toFixed(2)}`;
}

function formatDate(date) {
    return date.toLocaleDateString();
}

function formatTime(date) {
    return date.toLocaleTimeString();
}

function capitalize(str) {
    return str.charAt(0).toUpperCase() + str.slice(1).toLowerCase();
}

function truncate(str, maxLength) {
    if (str.length <= maxLength) return str;
    return str.substring(0, maxLength) + '...';
}

function generateId() {
    return Date.now().toString(36) + Math.random().toString(36).substr(2);
}

function validateEmail(email) {
    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    return emailRegex.test(email);
}

// Main application code using the imported utilities
console.log("Using imported utility functions:");

// Example 1: E-commerce product display
const product = {
    name: "JavaScript Programming Book",
    price: 29.99,
    description: "A comprehensive guide to JavaScript programming for beginners and advanced developers",
    createdAt: new Date()
};

console.log("\n=== Product Display ===");
console.log("Product:", capitalize(product.name));
console.log("Price:", formatCurrency(product.price));
console.log("Added:", formatDate(product.createdAt));
console.log("Description:", truncate(product.description, 50));

// Example 2: User registration
const userData = {
    name: "john doe",
    email: "john@example.com",
    id: generateId()
};

console.log("\n=== User Registration ===");
console.log("Name:", capitalize(userData.name));
console.log("Email:", userData.email);
console.log("Email valid:", validateEmail(userData.email));
console.log("User ID:", userData.id);

// Example 3: Order processing
const order = {
    id: generateId(),
    items: [
        { name: "Book", price: 29.99 },
        { name: "Pen", price: 2.50 },
        { name: "Notebook", price: 5.99 }
    ],
    orderDate: new Date()
};

console.log("\n=== Order Processing ===");
console.log("Order ID:", order.id);
console.log("Order Date:", formatDate(order.orderDate));
console.log("Order Time:", formatTime(order.orderDate));

let total = 0;
order.items.forEach((item, index) => {
    console.log(`Item ${index + 1}: ${capitalize(item.name)} - ${formatCurrency(item.price)}`);
    total += item.price;
});

console.log("Total:", formatCurrency(total));

// Example 4: Email validation
const emails = [
    "user@example.com",
    "test.email@domain.co.uk",
    "invalid-email",
    "another@test.org",
    "not-an-email"
];

console.log("\n=== Email Validation ===");
emails.forEach(email => {
    console.log(`${email}: ${validateEmail(email) ? 'Valid' : 'Invalid'}`);
});

console.log("\n=== Import Examples ===");
console.log("In a real project, you would import these utilities like:");
console.log("import validateEmail, { formatCurrency, formatDate, capitalize } from './utils.js';");
console.log("import { generateId, truncate } from './utils.js';");
console.log("import * as utils from './utils.js'; // Import all as utils object");
