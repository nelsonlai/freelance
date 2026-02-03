# Lesson 3: Template Literals

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Create dynamic strings using template literals
- Embed variables and expressions in strings
- Write multi-line strings without concatenation
- Use template literals for complex string formatting
- Write cleaner, more readable string code

## 📚 What are Template Literals?

**Template literals** are a new way to create strings in JavaScript using backticks (`` ` ``) instead of quotes. They allow you to embed variables and expressions directly in strings.

### Basic Syntax
```javascript
// Old way with quotes
let name = "Alice";
let greeting = "Hello, " + name + "!";

// New way with template literals
let greeting = `Hello, ${name}!`;
```

## 🔤 String Interpolation

**String interpolation** allows you to embed variables and expressions inside strings:

```javascript
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
```

## 📝 Multi-line Strings

Template literals make multi-line strings much cleaner:

```javascript
// Old way (concatenation)
let oldMultiLine = "This is line 1\n" +
                   "This is line 2\n" +
                   "This is line 3";

// New way (template literals)
let newMultiLine = `This is line 1
This is line 2 
This is line 3`;
```

## 🎯 Practice Exercises

### Exercise 1: Basic Interpolation
Create a greeting message with user information:

**Solution:**
```javascript
let firstName = "Alice";
let lastName = "Smith";
let age = 30;

let greeting = `Hello, ${firstName} ${lastName}! You are ${age} years old.`;
console.log(greeting);
```

### Exercise 2: Multi-line Template
Create a formatted address using template literals:

**Solution:**
```javascript
let street = "123 Main St";
let city = "New York";
let state = "NY";
let zip = "10001";

let address = `${street}
${city}, ${state} ${zip}`;

console.log(address);
```

### Exercise 3: Dynamic Content
Create a product description with dynamic pricing:

**Solution:**
```javascript
let product = "Laptop";
let price = 999.99;
let discount = 0.15;
let finalPrice = price * (1 - discount);

let description = `Product: ${product}
Original Price: $${price}
Discount: ${discount * 100}%
Final Price: $${finalPrice.toFixed(2)}`;

console.log(description);
```

## 🎯 Key Takeaways

1. **Template literals** use backticks (`` ` ``) instead of quotes
2. **String interpolation** uses `${}` syntax
3. **Multi-line strings** are much cleaner with template literals
4. **Expressions** can be embedded directly in strings
5. **No concatenation** needed for complex strings

## 🚀 Next Steps

Great! You now understand template literals. In the next lesson, we'll learn about:

- **Modules** - splitting code across files
- **Import/Export** - sharing code between files
- **Module systems** - CommonJS vs ES6 modules

---

**Next Lesson**: [Lesson 4: Modules & Imports/Exports](./lesson4-modules.md)
