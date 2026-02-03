// Exercise 3: Module Organization
// This demonstrates how to organize code across multiple modules

console.log("=== Exercise 3: Module Organization ===");

// This example shows how you might organize a simple application
// across multiple modules

// Module 1: Math utilities (would be in math.js)
console.log("\n=== Math Module ===");
const mathUtils = {
    add: (a, b) => a + b,
    subtract: (a, b) => a - b,
    multiply: (a, b) => a * b,
    divide: (a, b) => b !== 0 ? a / b : 'Error: Division by zero',
    power: (base, exponent) => Math.pow(base, exponent),
    square: (num) => num * num,
    cube: (num) => num * num * num,
    factorial: (n) => {
        if (n <= 1) return 1;
        return n * mathUtils.factorial(n - 1);
    }
};

// In a real module file, these would be exported like:
// export const add = (a, b) => a + b;
// export const subtract = (a, b) => a - b;
// export default mathUtils;

console.log("Math operations:");
console.log("add(5, 3):", mathUtils.add(5, 3));
console.log("multiply(4, 6):", mathUtils.multiply(4, 6));
console.log("power(2, 3):", mathUtils.power(2, 3));
console.log("factorial(5):", mathUtils.factorial(5));

// Module 2: String utilities (would be in string.js)
console.log("\n=== String Module ===");
const stringUtils = {
    capitalize: (str) => str.charAt(0).toUpperCase() + str.slice(1).toLowerCase(),
    reverse: (str) => str.split('').reverse().join(''),
    truncate: (str, maxLength) => str.length <= maxLength ? str : str.substring(0, maxLength) + '...',
    padLeft: (str, length, char = ' ') => str.padStart(length, char),
    padRight: (str, length, char = ' ') => str.padEnd(length, char),
    countWords: (str) => str.trim().split(/\s+/).length,
    removeSpaces: (str) => str.replace(/\s/g, '')
};

// In a real module file, these would be exported like:
// export const capitalize = (str) => { ... };
// export const reverse = (str) => { ... };
// export default stringUtils;

console.log("String operations:");
console.log("capitalize('hello world'):", stringUtils.capitalize('hello world'));
console.log("reverse('JavaScript'):", stringUtils.reverse('JavaScript'));
console.log("truncate('This is a long string', 10):", stringUtils.truncate('This is a long string', 10));
console.log("countWords('Hello world from JavaScript'):", stringUtils.countWords('Hello world from JavaScript'));

// Module 3: Date utilities (would be in date.js)
console.log("\n=== Date Module ===");
const dateUtils = {
    formatDate: (date) => date.toLocaleDateString(),
    formatTime: (date) => date.toLocaleTimeString(),
    formatDateTime: (date) => `${dateUtils.formatDate(date)} ${dateUtils.formatTime(date)}`,
    addDays: (date, days) => {
        const result = new Date(date);
        result.setDate(result.getDate() + days);
        return result;
    },
    daysBetween: (date1, date2) => {
        const diffTime = Math.abs(date2 - date1);
        return Math.ceil(diffTime / (1000 * 60 * 60 * 24));
    },
    isWeekend: (date) => {
        const day = date.getDay();
        return day === 0 || day === 6;
    },
    getAge: (birthDate) => {
        const today = new Date();
        const age = today.getFullYear() - birthDate.getFullYear();
        const monthDiff = today.getMonth() - birthDate.getMonth();
        return monthDiff < 0 || (monthDiff === 0 && today.getDate() < birthDate.getDate()) ? age - 1 : age;
    }
};

// In a real module file, these would be exported like:
// export const formatDate = (date) => { ... };
// export const addDays = (date, days) => { ... };
// export default dateUtils;

const today = new Date();
const birthday = new Date('1990-05-15');

console.log("Date operations:");
console.log("formatDate(today):", dateUtils.formatDate(today));
console.log("formatTime(today):", dateUtils.formatTime(today));
console.log("formatDateTime(today):", dateUtils.formatDateTime(today));
console.log("addDays(today, 7):", dateUtils.formatDate(dateUtils.addDays(today, 7)));
console.log("daysBetween(birthday, today):", dateUtils.daysBetween(birthday, today));
console.log("isWeekend(today):", dateUtils.isWeekend(today));
console.log("getAge(birthday):", dateUtils.getAge(birthday));

// Module 4: Validation utilities (would be in validation.js)
console.log("\n=== Validation Module ===");
const validationUtils = {
    isEmail: (email) => /^[^\s@]+@[^\s@]+\.[^\s@]+$/.test(email),
    isPhone: (phone) => /^[\+]?[1-9][\d]{0,15}$/.test(phone.replace(/[\s\-\(\)]/g, '')),
    isUrl: (url) => {
        try {
            new URL(url);
            return true;
        } catch {
            return false;
        }
    },
    isStrongPassword: (password) => {
        return password.length >= 8 && 
               /[A-Z]/.test(password) && 
               /[a-z]/.test(password) && 
               /\d/.test(password);
    },
    isNumeric: (str) => !isNaN(str) && !isNaN(parseFloat(str)),
    isAlpha: (str) => /^[a-zA-Z]+$/.test(str),
    isAlphaNumeric: (str) => /^[a-zA-Z0-9]+$/.test(str)
};

// In a real module file, these would be exported like:
// export const isEmail = (email) => { ... };
// export const isPhone = (phone) => { ... };
// export default validationUtils;

console.log("Validation operations:");
console.log("isEmail('user@example.com'):", validationUtils.isEmail('user@example.com'));
console.log("isEmail('invalid-email'):", validationUtils.isEmail('invalid-email'));
console.log("isPhone('+1-555-123-4567'):", validationUtils.isPhone('+1-555-123-4567'));
console.log("isUrl('https://example.com'):", validationUtils.isUrl('https://example.com'));
console.log("isStrongPassword('Password123'):", validationUtils.isStrongPassword('Password123'));
console.log("isNumeric('123'):", validationUtils.isNumeric('123'));
console.log("isAlpha('Hello'):", validationUtils.isAlpha('Hello'));

console.log("\n=== Module Import Examples ===");
console.log("In a real project, you would organize and import these like:");
console.log("import { add, multiply, factorial } from './math.js';");
console.log("import { capitalize, reverse, truncate } from './string.js';");
console.log("import { formatDate, addDays, getAge } from './date.js';");
console.log("import { isEmail, isPhone, isStrongPassword } from './validation.js';");
console.log("import * as utils from './utils.js'; // Import all utilities");
