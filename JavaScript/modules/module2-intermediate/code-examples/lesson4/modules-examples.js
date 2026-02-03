// Lesson 4: Modules & Imports/Exports Examples

// Note: This file demonstrates module concepts
// In a real project, these would be separate files

console.log("=== Module Examples ===");
console.log("Note: These examples show how modules work");
console.log("In practice, each would be in separate .js files");

// Example 1: Named Exports (would be in math.js)
console.log("\n=== Named Exports Example ===");
const PI = 3.14159;

function add(a, b) {
    return a + b;
}

function multiply(a, b) {
    return a * b;
}

function subtract(a, b) {
    return a - b;
}

// In a real module file, these would be exported like:
// export const PI = 3.14159;
// export function add(a, b) { return a + b; }
// export function multiply(a, b) { return a * b; }

console.log("PI:", PI);
console.log("add(5, 3):", add(5, 3));
console.log("multiply(4, 6):", multiply(4, 6));
console.log("subtract(10, 4):", subtract(10, 4));

// Example 2: Default Export (would be in calculator.js)
console.log("\n=== Default Export Example ===");
function calculate(operation, a, b) {
    switch(operation) {
        case 'add': return a + b;
        case 'subtract': return a - b;
        case 'multiply': return a * b;
        case 'divide': return b !== 0 ? a / b : 'Error: Division by zero';
        default: return 0;
    }
}

// In a real module file, this would be exported like:
// export default function calculate(operation, a, b) { ... }

console.log("calculate('add', 5, 3):", calculate('add', 5, 3));
console.log("calculate('multiply', 4, 6):", calculate('multiply', 4, 6));
console.log("calculate('divide', 10, 2):", calculate('divide', 10, 2));

// Example 3: Utility Functions (would be in utils.js)
console.log("\n=== Utility Functions Example ===");
function formatCurrency(amount) {
    return `$${amount.toFixed(2)}`;
}

function formatDate(date) {
    return date.toLocaleDateString();
}

function validateEmail(email) {
    return email.includes('@') && email.includes('.');
}

function capitalize(str) {
    return str.charAt(0).toUpperCase() + str.slice(1).toLowerCase();
}

// In a real module file, these would be exported like:
// export function formatCurrency(amount) { ... }
// export function formatDate(date) { ... }
// export default function validateEmail(email) { ... }

console.log("formatCurrency(19.99):", formatCurrency(19.99));
console.log("formatDate(new Date()):", formatDate(new Date()));
console.log("validateEmail('user@example.com'):", validateEmail('user@example.com'));
console.log("capitalize('hello world'):", capitalize('hello world'));

// Example 4: Mixed Exports (would be in user.js)
console.log("\n=== Mixed Exports Example ===");
const DEFAULT_ROLE = 'user';

function createUser(name, email, role = DEFAULT_ROLE) {
    return {
        id: Date.now(),
        name,
        email,
        role,
        createdAt: new Date()
    };
}

function getUserInfo(user) {
    return `${user.name} (${user.email}) - ${user.role}`;
}

function isAdmin(user) {
    return user.role === 'admin';
}

// In a real module file, these would be exported like:
// export const DEFAULT_ROLE = 'user';
// export function createUser(name, email, role = DEFAULT_ROLE) { ... }
// export function getUserInfo(user) { ... }
// export default function isAdmin(user) { ... }

const user = createUser('Alice', 'alice@example.com', 'admin');
console.log("User created:", user);
console.log("User info:", getUserInfo(user));
console.log("Is admin:", isAdmin(user));

console.log("\n=== Module Import Examples ===");
console.log("In practice, you would import these like:");
console.log("import { PI, add, multiply } from './math.js';");
console.log("import calculate from './calculator.js';");
console.log("import validateEmail, { formatCurrency } from './utils.js';");
console.log("import isAdmin, { createUser, DEFAULT_ROLE } from './user.js';");
