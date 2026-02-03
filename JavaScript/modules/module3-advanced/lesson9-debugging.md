# Lesson 9: Debugging Tools

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Use Chrome DevTools effectively
- Set breakpoints and step through code
- Inspect variables and call stack
- Use the network inspector
- Debug asynchronous code
- Profile application performance

## 📚 Chrome DevTools

### Console Tab
```javascript
// Basic logging
console.log('Debug message');
console.error('Error message');
console.warn('Warning message');
console.info('Info message');

// Grouping logs
console.group('User Data');
console.log('Name:', 'Alice');
console.log('Age:', 30);
console.groupEnd();

// Table display
const users = [
    { name: 'Alice', age: 30 },
    { name: 'Bob', age: 25 }
];
console.table(users);
```

### Sources Tab
```javascript
// Setting breakpoints
function calculateTotal(items) {
    let total = 0; // Set breakpoint here
    
    for (let item of items) {
        total += item.price; // Set breakpoint here
    }
    
    return total; // Set breakpoint here
}

// Debugging with debugger statement
function processData(data) {
    debugger; // Execution will pause here
    const processed = data.map(item => item * 2);
    return processed;
}
```

### Network Tab
```javascript
// Monitor API calls
async function fetchUserData() {
    try {
        const response = await fetch('/api/users');
        const data = await response.json();
        return data;
    } catch (error) {
        console.error('Fetch error:', error);
    }
}
```

## 🎯 Practice Exercises

### Exercise 1: Debugging Practice
Create code with intentional bugs to practice debugging:

**Solution:**
```javascript
// Buggy code for debugging practice
function calculateAverage(numbers) {
    let sum = 0;
    
    for (let i = 0; i <= numbers.length; i++) { // Bug: should be < not <=
        sum += numbers[i];
    }
    
    return sum / numbers.length; // Bug: division by zero possible
}

// Fixed version
function calculateAverageFixed(numbers) {
    if (numbers.length === 0) {
        return 0;
    }
    
    let sum = 0;
    
    for (let i = 0; i < numbers.length; i++) {
        sum += numbers[i];
    }
    
    return sum / numbers.length;
}

// Test cases
console.log('Buggy:', calculateAverage([1, 2, 3, 4, 5])); // NaN
console.log('Fixed:', calculateAverageFixed([1, 2, 3, 4, 5])); // 3
```

## 🎯 Key Takeaways

1. **Console logging** helps track program flow
2. **Breakpoints** pause execution for inspection
3. **Network tab** monitors API requests
4. **Sources tab** provides debugging controls
5. **Performance tab** identifies bottlenecks

---

**Next Lesson**: [Lesson 10: Mini Project - Weather App](./lesson10-mini-project.md)
