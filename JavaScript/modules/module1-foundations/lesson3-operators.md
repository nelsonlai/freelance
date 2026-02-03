# Lesson 3: Operators

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Use arithmetic operators for calculations
- Apply assignment operators to store results
- Compare values with comparison operators
- Combine conditions with logical operators
- Use the ternary operator for conditional expressions
- Understand operator precedence and short-circuit evaluation

## 📚 What are Operators?

**Operators** are symbols that perform operations on values (called operands). Think of them as mathematical symbols that tell JavaScript what to do with numbers, text, or other data.

## 🔢 Arithmetic Operators

These operators perform mathematical calculations:

```javascript
let a = 10;
let b = 3;

console.log(a + b);  // 13 (addition)
console.log(a - b);  // 7 (subtraction)
console.log(a * b);  // 30 (multiplication)
console.log(a / b);  // 3.333... (division)
console.log(a % b);  // 1 (remainder/modulo)
console.log(a ** b); // 1000 (exponentiation)
```

### Examples:
```javascript
let price = 19.99;
let tax = 0.08;
let total = price + (price * tax);
console.log("Total:", total);  // 21.5892

let items = 5;
let itemsPerBox = 3;
let fullBoxes = Math.floor(items / itemsPerBox);  // 1
let remainingItems = items % itemsPerBox;         // 2
console.log("Full boxes:", fullBoxes);
console.log("Remaining items:", remainingItems);
```

## 📝 Assignment Operators

These operators assign values to variables:

```javascript
let x = 10;

x += 5;   // Same as x = x + 5;  → x is now 15
x -= 3;   // Same as x = x - 3;  → x is now 12
x *= 2;   // Same as x = x * 2;  → x is now 24
x /= 4;   // Same as x = x / 4;  → x is now 6
x %= 5;   // Same as x = x % 5;  → x is now 1
```

### Examples:
```javascript
let score = 0;
score += 10;  // Add 10 points
score += 5;   // Add 5 more points
console.log("Total score:", score);  // 15

let count = 100;
count -= 25;  // Subtract 25
count *= 2;   // Double it
console.log("Final count:", count);  // 150
```

## ⚖️ Comparison Operators

These operators compare two values and return `true` or `false`:

```javascript
let a = 10;
let b = 5;

console.log(a > b);   // true (greater than)
console.log(a < b);   // false (less than)
console.log(a >= b);  // true (greater than or equal)
console.log(a <= b);  // false (less than or equal)
console.log(a == b);  // false (equal to)
console.log(a != b);  // true (not equal to)
console.log(a === b); // false (strictly equal to)
console.log(a !== b); // true (strictly not equal to)
```

### Strict vs Loose Equality:

```javascript
let num = 5;
let str = "5";

console.log(num == str);   // true (loose equality - converts types)
console.log(num === str);  // false (strict equality - checks type too)
console.log(num != str);   // false (loose inequality)
console.log(num !== str);  // true (strict inequality)
```

**Always use `===` and `!==` for comparisons!**

## 🧠 Logical Operators

These operators combine boolean values:

### AND (`&&`) - Both must be true
```javascript
let age = 25;
let hasLicense = true;

if (age >= 18 && hasLicense) {
    console.log("Can drive!");
}
```

### OR (`||`) - At least one must be true
```javascript
let isStudent = true;
let isSenior = false;

if (isStudent || isSenior) {
    console.log("Gets discount!");
}
```

### NOT (`!`) - Reverses true/false
```javascript
let isLoggedIn = false;

if (!isLoggedIn) {
    console.log("Please log in");
}
```

## ❓ Ternary Operator

A shorthand way to write if-else statements:

```javascript
// Syntax: condition ? valueIfTrue : valueIfFalse

let age = 20;
let status = age >= 18 ? "adult" : "minor";
console.log(status);  // "adult"

let score = 85;
let grade = score >= 90 ? "A" : score >= 80 ? "B" : "C";
console.log(grade);  // "B"
```

## 🎯 Operator Precedence

JavaScript follows rules about which operations happen first:

```javascript
let result = 2 + 3 * 4;  // 14 (not 20!)
// Multiplication happens first: 3 * 4 = 12, then 2 + 12 = 14

let result2 = (2 + 3) * 4;  // 20
// Parentheses force addition first: 2 + 3 = 5, then 5 * 4 = 20
```

### Order of Operations (PEMDAS):
1. **P**arentheses
2. **E**xponentiation (`**`)
3. **M**ultiplication (`*`) and **D**ivision (`/`)
4. **A**ddition (`+`) and **S**ubtraction (`-`)

## ⚡ Short-Circuit Evaluation

Logical operators can "short-circuit" - stop evaluating as soon as they know the answer:

```javascript
// AND short-circuits on first false
let x = false;
let y = true;
let result = x && y;  // false (stops at x, doesn't check y)

// OR short-circuits on first true
let a = true;
let b = false;
let result2 = a || b;  // true (stops at a, doesn't check b)
```

### Practical Example:
```javascript
let user = null;
let username = user && user.name;  // null (safe - won't crash)
console.log(username);

let defaultName = username || "Guest";  // "Guest"
console.log(defaultName);
```

## 🎯 Practice Exercises

### Exercise 1: Basic Calculations
Calculate the area and perimeter of a rectangle:

**Solution:**
```javascript
let length = 10;
let width = 5;

let area = length * width;
let perimeter = 2 * (length + width);

console.log("Area:", area);        // 50
console.log("Perimeter:", perimeter); // 30
```

### Exercise 2: Grade Calculator
Calculate a student's average and determine if they passed:

**Solution:**
```javascript
let math = 85;
let science = 92;
let english = 78;

let average = (math + science + english) / 3;
let passed = average >= 70;

console.log("Average:", average.toFixed(2));  // 85.00
console.log("Passed:", passed);              // true
```

### Exercise 3: Age Verification
Check if someone can vote and drive:

**Solution:**
```javascript
let age = 20;
let hasLicense = true;

let canVote = age >= 18;
let canDrive = age >= 16 && hasLicense;
let canDrink = age >= 21;

console.log("Can vote:", canVote);    // true
console.log("Can drive:", canDrive);  // true
console.log("Can drink:", canDrink);  // false
```

## 🚨 Common Mistakes to Avoid

### 1. Using `==` instead of `===`
```javascript
// Wrong
if (age == "18") { ... }

// Right
if (age === 18) { ... }
```

### 2. Forgetting operator precedence
```javascript
// Wrong assumption
let result = 2 + 3 * 4;  // 14, not 20!

// Right with parentheses
let result = (2 + 3) * 4;  // 20
```

### 3. Confusing assignment with comparison
```javascript
// Wrong (assignment, not comparison)
if (x = 5) { ... }

// Right (comparison)
if (x === 5) { ... }
```

## 🎯 Key Takeaways

1. **Arithmetic operators** perform math calculations
2. **Assignment operators** store results in variables
3. **Comparison operators** compare values (use `===` and `!==`)
4. **Logical operators** combine conditions (`&&`, `||`, `!`)
5. **Ternary operator** is shorthand for if-else
6. **Operator precedence** determines order of operations
7. **Short-circuit evaluation** stops when answer is known

## 🚀 Next Steps

Excellent! You now understand how to perform calculations and comparisons. In the next lesson, we'll learn about:

- **String methods** - working with text
- **Number methods** - formatting and calculations
- **Math object** - advanced mathematical operations

## 📚 Additional Resources

- [MDN Operators](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Expressions_and_Operators)
- [JavaScript Operator Precedence](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/Operator_Precedence)

## 🎉 Congratulations!

You've mastered JavaScript operators! You can now:

- Perform mathematical calculations
- Compare values and make decisions
- Combine conditions logically
- Use shorthand operators efficiently

Practice with the exercises, and get ready for Lesson 4 where we'll learn about string and number methods!

---

**Next Lesson**: [Lesson 4: String and Number Methods](./lesson4-string-number-methods.md)
