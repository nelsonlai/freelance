# Lesson 1: Scope and Hoisting

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Understand global vs local scope
- Explain lexical scope and scope chain
- Understand hoisting behavior with `var`, `let`, and `const`
- Identify scope-related bugs and avoid them
- Write code that follows best practices for scope

## 📚 What is Scope?

**Scope** determines where variables can be accessed in your code. Think of it like the "visibility" of variables - some variables can be seen everywhere, others only in specific places.

### Types of Scope

1. **Global Scope** - Variables accessible everywhere
2. **Local Scope** - Variables accessible only in specific areas
3. **Block Scope** - Variables accessible only within `{}` blocks

## 🌍 Global vs Local Scope

### Global Scope
Variables declared outside any function or block are in global scope:

```javascript
let globalVariable = "I'm global!";

function myFunction() {
    console.log(globalVariable); // Can access global variable
}

console.log(globalVariable); // Can access global variable
```

### Local Scope
Variables declared inside a function are in local scope:

```javascript
function myFunction() {
    let localVariable = "I'm local!";
    console.log(localVariable); // Can access local variable
}

// console.log(localVariable); // Error! Cannot access local variable
```

## 🔗 Lexical Scope

**Lexical scope** means that inner functions can access variables from outer functions:

```javascript
function outerFunction() {
    let outerVariable = "I'm in outer function";
    
    function innerFunction() {
        console.log(outerVariable); // Can access outer variable
        let innerVariable = "I'm in inner function";
    }
    
    // console.log(innerVariable); // Error! Cannot access inner variable
}
```

## ⬆️ Hoisting

**Hoisting** is JavaScript's behavior of moving declarations to the top of their scope before execution.

### Hoisting with `var`

```javascript
console.log(x); // undefined (not an error!)
var x = 5;
console.log(x); // 5
```

This is equivalent to:
```javascript
var x; // Declaration is hoisted
console.log(x); // undefined
x = 5; // Assignment happens here
console.log(x); // 5
```

### Hoisting with `let` and `const`

```javascript
// console.log(y); // Error! Cannot access before declaration
let y = 10;
console.log(y); // 10

// console.log(z); // Error! Cannot access before declaration
const z = 15;
console.log(z); // 15
```

### Function Hoisting

```javascript
sayHello(); // "Hello!" (works!)

function sayHello() {
    console.log("Hello!");
}
```

But function expressions are not hoisted:
```javascript
// sayGoodbye(); // Error! Cannot access before declaration

const sayGoodbye = function() {
    console.log("Goodbye!");
};
```

## 🎯 Practice Exercises

### Exercise 1: Scope Understanding
Predict what will be logged and explain why:

**Solution:**
```javascript
let globalVar = "global";

function testScope() {
    let localVar = "local";
    console.log("Inside function - global:", globalVar);
    console.log("Inside function - local:", localVar);
}

testScope();
console.log("Outside function - global:", globalVar);
// console.log("Outside function - local:", localVar); // Error!
```

### Exercise 2: Hoisting Behavior
Predict the output and explain the hoisting:

**Solution:**
```javascript
console.log("1. var before:", typeof hoistedVar); // undefined
console.log("2. let before:", typeof hoistedLet); // ReferenceError

var hoistedVar = "I'm hoisted!";
let hoistedLet = "I'm not hoisted!";

console.log("3. var after:", hoistedVar); // "I'm hoisted!"
console.log("4. let after:", hoistedLet); // "I'm not hoisted!"
```

### Exercise 3: Scope Chain
Create nested functions and demonstrate scope chain:

**Solution:**
```javascript
let globalVar = "global";

function outerFunction() {
    let outerVar = "outer";
    
    function innerFunction() {
        let innerVar = "inner";
        console.log("Inner can see:", globalVar, outerVar, innerVar);
        
        function deepestFunction() {
            console.log("Deepest can see:", globalVar, outerVar, innerVar);
        }
        
        deepestFunction();
    }
    
    innerFunction();
    console.log("Outer can see:", globalVar, outerVar);
}

outerFunction();
```

## 🚨 Common Scope Mistakes

### 1. Accidental Global Variables
```javascript
function badFunction() {
    // Missing let/const - creates global variable!
    badVariable = "I'm global!";
}

badFunction();
console.log(badVariable); // Works, but bad practice!
```

### 2. Variable Shadowing
```javascript
let name = "Alice";

function greet() {
    let name = "Bob"; // Shadows the outer name
    console.log("Hello, " + name); // "Hello, Bob"
}

greet();
console.log(name); // "Alice"
```

### 3. Loop Variable Issues
```javascript
// Problem with var in loops
for (var i = 0; i < 3; i++) {
    setTimeout(() => console.log(i), 100); // Logs 3, 3, 3
}

// Solution with let
for (let j = 0; j < 3; j++) {
    setTimeout(() => console.log(j), 100); // Logs 0, 1, 2
}
```

## 🎯 Key Takeaways

1. **Scope** determines where variables can be accessed
2. **Global scope** - accessible everywhere
3. **Local scope** - accessible only within function/block
4. **Lexical scope** - inner functions can access outer variables
5. **Hoisting** - declarations move to top of scope
6. **`var`** is hoisted but initialized as `undefined`
7. **`let`/`const`** are hoisted but not initialized (temporal dead zone)
8. **Always use `let`/`const`** instead of `var`

## 🚀 Next Steps

Great! You now understand scope and hoisting. In the next lesson, we'll learn about:

- **Destructuring** - extracting values from arrays and objects
- **Spread operator** - expanding arrays and objects
- **Rest operator** - collecting remaining elements

## 📚 Additional Resources

- [MDN Scope](https://developer.mozilla.org/en-US/docs/Glossary/Scope)
- [MDN Hoisting](https://developer.mozilla.org/en-US/docs/Glossary/Hoisting)
- [JavaScript.info Scope](https://javascript.info/closure)

## 🎉 Congratulations!

You've mastered JavaScript scope and hoisting! You now understand:

- How variables are accessed in different scopes
- Why hoisting happens and how it affects your code
- How to avoid common scope-related bugs
- Best practices for variable declaration

Practice with the exercises, and get ready for Lesson 2 where we'll learn about destructuring and spread/rest operators!

---

**Next Lesson**: [Lesson 2: Destructuring & Spread/Rest](./lesson2-destructuring-spread.md)
