# Lesson 2: Variables and Data Types

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Understand what variables are and why we use them
- Declare variables using `var`, `let`, and `const`
- Identify and work with different data types
- Convert between different data types
- Use the `typeof` operator to check data types

## 📚 What are Variables?

A **variable** is like a labeled box that stores information. You can put something in the box, look at what's inside, or change what's in the box.

Think of it like this:
- **Variable name** = the label on the box
- **Value** = what's inside the box

```javascript
let age = 25;        // age is the variable name, 25 is the value
let name = "Alice";  // name is the variable name, "Alice" is the value
```

## 🔧 Declaring Variables

JavaScript has three ways to declare variables:

### 1. `var` (Old way - still works but not recommended)
```javascript
var age = 25;
var name = "Alice";
```

### 2. `let` (Modern way - can be changed)
```javascript
let age = 25;
let name = "Alice";

// You can change the value later
age = 26;  // Now age is 26
```

### 3. `const` (Constant - cannot be changed)
```javascript
const pi = 3.14159;
const company = "Google";

// This would cause an error:
// pi = 3.14;  // Error! Cannot change const
```

### When to Use Each:

- **`const`**: Use for values that never change (like mathematical constants, company names)
- **`let`**: Use for values that might change (like user age, current score)
- **`var`**: Avoid in modern JavaScript (use `let` instead)

## 📊 Data Types

JavaScript has several data types. Let's learn the most important ones:

### 1. Numbers
```javascript
let age = 25;           // Integer (whole number)
let price = 19.99;      // Float (decimal number)
let temperature = -5;   // Negative number
let bigNumber = 1000000; // Large number
```

### 2. Strings (Text)
```javascript
let name = "Alice";           // Double quotes
let city = 'New York';        // Single quotes
let message = `Hello ${name}`; // Template literal (backticks)
```

### 3. Booleans (True/False)
```javascript
let isStudent = true;
let isWorking = false;
let hasLicense = true;
```

### 4. Undefined
```javascript
let x;  // x is undefined (no value assigned)
console.log(x);  // undefined
```

### 5. Null
```javascript
let emptyBox = null;  // Explicitly empty
console.log(emptyBox);  // null
```

## 🔍 Checking Data Types with `typeof`

The `typeof` operator tells you what type of data something is:

```javascript
console.log(typeof 42);           // "number"
console.log(typeof "Hello");       // "string"
console.log(typeof true);         // "boolean"
console.log(typeof undefined);    // "undefined"
console.log(typeof null);         // "object" (this is a JavaScript quirk!)
```

## 🔄 Type Conversion

Sometimes you need to change one data type to another:

### Converting to String
```javascript
let age = 25;
let ageString = String(age);        // "25"
let ageString2 = age.toString();    // "25"
let ageString3 = age + "";          // "25" (concatenation trick)
```

### Converting to Number
```javascript
let ageString = "25";
let age = Number(ageString);        // 25
let age2 = parseInt(ageString);    // 25 (for integers)
let age3 = parseFloat("25.5");     // 25.5 (for decimals)
```

### Converting to Boolean
```javascript
let text = "Hello";
let isTrue = Boolean(text);        // true
let isEmpty = Boolean("");         // false
let isZero = Boolean(0);           // false
```

## 🎯 Practice Exercises

### Exercise 1: Variable Declaration
Create variables for:
- Your name (string)
- Your age (number)
- Whether you're a student (boolean)
- Your favorite number (number)

**Solution:**
```javascript
const name = "Alice";
let age = 25;
const isStudent = true;
let favoriteNumber = 42;

console.log("Name:", name);
console.log("Age:", age);
console.log("Is student:", isStudent);
console.log("Favorite number:", favoriteNumber);
```

### Exercise 2: Type Checking
Create different variables and check their types:

**Solution:**
```javascript
let name = "Bob";
let age = 30;
let isMarried = false;
let salary = 50000.50;

console.log("Name type:", typeof name);      // "string"
console.log("Age type:", typeof age);        // "number"
console.log("Married type:", typeof isMarried); // "boolean"
console.log("Salary type:", typeof salary);  // "number"
```

### Exercise 3: Type Conversion
Convert between different types:

**Solution:**
```javascript
let age = 25;
let ageString = String(age);
console.log("Age as string:", ageString, typeof ageString);

let score = "95";
let scoreNumber = Number(score);
console.log("Score as number:", scoreNumber, typeof scoreNumber);

let isActive = "true";
let isActiveBoolean = Boolean(isActive);
console.log("Active as boolean:", isActiveBoolean, typeof isActiveBoolean);
```

## 🚨 Common Mistakes to Avoid

### 1. Forgetting to declare variables
```javascript
// Wrong
age = 25;  // This creates a global variable (bad!)

// Right
let age = 25;  // Properly declared
```

### 2. Using `var` instead of `let`
```javascript
// Old way (avoid)
var age = 25;

// Modern way (preferred)
let age = 25;
```

### 3. Trying to change a `const`
```javascript
const pi = 3.14159;
pi = 3.14;  // Error! Cannot change const
```

### 4. Confusing `null` and `undefined`
```javascript
let x;           // undefined (no value assigned)
let y = null;    // null (explicitly empty)
```

## 🎯 Key Takeaways

1. **Variables** store information with a name
2. **`let`** for values that can change, **`const`** for values that don't
3. **Data types**: number, string, boolean, undefined, null
4. **`typeof`** tells you what type something is
5. **Type conversion** changes one type to another
6. **Always declare variables** with `let` or `const`

## 🚀 Next Steps

Great job! You now understand variables and data types. In the next lesson, we'll learn about:

- **Operators** - how to do math and comparisons
- **Operator precedence** - which operations happen first
- **Short-circuit evaluation** - smart logical operations

## 📚 Additional Resources

- [MDN Variables](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Grammar_and_types#Declarations)
- [JavaScript Data Types](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Data_structures)

## 🎉 Congratulations!

You've learned the building blocks of JavaScript programming! You can now:

- Store information in variables
- Work with different data types
- Convert between types
- Check what type something is

Practice with the exercises, and get ready for Lesson 3 where we'll learn about operators!

---

**Next Lesson**: [Lesson 3: Operators](./lesson3-operators.md)
