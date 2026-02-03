// Exercise 1: Create a Utility Module
// This demonstrates how to create a module with utility functions

// In a real project, this would be in utils.js
console.log("=== Exercise 1: Utility Module ===");

// Named exports
function formatCurrency(amount) {
    return `$${amount.toFixed(2)}`;
}

function formatDate(date) {
    return date.toLocaleDateString();
}

function formatTime(date) {
    return date.toLocaleTimeString();
}

function formatDateTime(date) {
    return `${formatDate(date)} ${formatTime(date)}`;
}

// Default export
function validateEmail(email) {
    const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
    return emailRegex.test(email);
}

// Additional utility functions
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

// In a real module file, these would be exported like:
// export function formatCurrency(amount) { ... }
// export function formatDate(date) { ... }
// export function formatTime(date) { ... }
// export function formatDateTime(date) { ... }
// export function capitalize(str) { ... }
// export function truncate(str, maxLength) { ... }
// export function generateId() { ... }
// export default function validateEmail(email) { ... }

// Test the utility functions
console.log("Testing utility functions:");
console.log("formatCurrency(19.99):", formatCurrency(19.99));
console.log("formatCurrency(0):", formatCurrency(0));
console.log("formatCurrency(1234.567):", formatCurrency(1234.567));

const now = new Date();
console.log("formatDate(now):", formatDate(now));
console.log("formatTime(now):", formatTime(now));
console.log("formatDateTime(now):", formatDateTime(now));

console.log("validateEmail('user@example.com'):", validateEmail('user@example.com'));
console.log("validateEmail('invalid-email'):", validateEmail('invalid-email'));

console.log("capitalize('hello world'):", capitalize('hello world'));
console.log("capitalize('JAVASCRIPT'):", capitalize('JAVASCRIPT'));

console.log("truncate('This is a long string', 10):", truncate('This is a long string', 10));
console.log("truncate('Short', 10):", truncate('Short', 10));

console.log("generateId():", generateId());
console.log("generateId():", generateId());
