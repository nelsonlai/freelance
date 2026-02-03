# Lesson 4: Modules & Imports/Exports

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Understand what modules are and why they're important
- Export functions, variables, and objects from modules
- Import code from other modules
- Use default exports vs named exports
- Organize code across multiple files

## 📚 What are Modules?

**Modules** are separate files that contain related code. They allow you to:
- Split large programs into smaller, manageable pieces
- Reuse code across different files
- Keep code organized and maintainable

## 📤 Exporting from Modules

### Named Exports
```javascript
// math.js
export const PI = 3.14159;
export function add(a, b) {
    return a + b;
}
export function multiply(a, b) {
    return a * b;
}
```

### Default Export
```javascript
// calculator.js
export default function calculate(operation, a, b) {
    switch(operation) {
        case 'add': return a + b;
        case 'subtract': return a - b;
        case 'multiply': return a * b;
        case 'divide': return a / b;
        default: return 0;
    }
}
```

## 📥 Importing from Modules

### Named Imports
```javascript
// main.js
import { PI, add, multiply } from './math.js';

console.log(PI); // 3.14159
console.log(add(5, 3)); // 8
console.log(multiply(4, 6)); // 24
```

### Default Import
```javascript
// main.js
import calculate from './calculator.js';

console.log(calculate('add', 5, 3)); // 8
```

### Mixed Imports
```javascript
// main.js
import calculate, { PI } from './calculator.js';
import { add } from './math.js';
```

## 🎯 Practice Exercises

### Exercise 1: Create a Utility Module
Create a module with utility functions:

**Solution:**
```javascript
// utils.js
export function formatCurrency(amount) {
    return `$${amount.toFixed(2)}`;
}

export function formatDate(date) {
    return date.toLocaleDateString();
}

export default function validateEmail(email) {
    return email.includes('@');
}
```

### Exercise 2: Import and Use Utilities
Import and use the utility functions:

**Solution:**
```javascript
// main.js
import validateEmail, { formatCurrency, formatDate } from './utils.js';

let price = 19.99;
let date = new Date();
let email = "user@example.com";

console.log(formatCurrency(price)); // "$19.99"
console.log(formatDate(date)); // "12/25/2023"
console.log(validateEmail(email)); // true
```

## 🎯 Key Takeaways

1. **Modules** split code into separate files
2. **Named exports** use `export const/function`
3. **Default exports** use `export default`
4. **Named imports** use `import { }`
5. **Default imports** use `import name`

---

**Next Lesson**: [Lesson 5: Classes and OOP](./lesson5-classes-oop.md)
