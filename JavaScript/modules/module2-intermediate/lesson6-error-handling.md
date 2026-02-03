# Lesson 6: Error Handling

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Use `try`, `catch`, and `finally` blocks
- Throw custom errors
- Handle different types of errors
- Create custom error classes
- Write robust error handling code

## 📚 Error Handling Basics

### Try-Catch-Finally
```javascript
try {
    // Code that might throw an error
    let result = riskyOperation();
    console.log(result);
} catch (error) {
    // Handle the error
    console.log("An error occurred:", error.message);
} finally {
    // Always runs
    console.log("Cleanup code here");
}
```

### Throwing Errors
```javascript
function divide(a, b) {
    if (b === 0) {
        throw new Error("Cannot divide by zero!");
    }
    return a / b;
}

try {
    let result = divide(10, 0);
} catch (error) {
    console.log(error.message); // "Cannot divide by zero!"
}
```

## 🎯 Practice Exercises

### Exercise 1: Safe Division Function
Create a function that safely divides two numbers:

**Solution:**
```javascript
function safeDivide(a, b) {
    try {
        if (typeof a !== 'number' || typeof b !== 'number') {
            throw new Error("Both arguments must be numbers");
        }
        if (b === 0) {
            throw new Error("Cannot divide by zero");
        }
        return a / b;
    } catch (error) {
        console.log("Error:", error.message);
        return null;
    }
}

console.log(safeDivide(10, 2)); // 5
console.log(safeDivide(10, 0)); // null
console.log(safeDivide("10", 2)); // null
```

## 🎯 Key Takeaways

1. **Try-catch** handles errors gracefully
2. **Throw** creates custom errors
3. **Finally** always executes
4. **Error handling** prevents crashes

---

**Next Lesson**: [Lesson 7: DOM Manipulation Basics](./lesson7-dom-basics.md)
