# Lesson 1: Asynchronous JavaScript

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Understand synchronous vs asynchronous programming
- Use callbacks to handle asynchronous operations
- Work with Promises and their methods
- Use async/await for cleaner asynchronous code
- Handle errors in asynchronous operations
- Understand the event loop and execution order

## 📚 What is Asynchronous Programming?

**Asynchronous programming** allows JavaScript to perform multiple operations at the same time without blocking the main thread. This is crucial for web applications that need to fetch data, handle user interactions, and perform other operations simultaneously.

### Synchronous vs Asynchronous

```javascript
// Synchronous (blocking)
console.log("1");
console.log("2");
console.log("3");
// Output: 1, 2, 3

// Asynchronous (non-blocking)
console.log("1");
setTimeout(() => console.log("2"), 1000);
console.log("3");
// Output: 1, 3, 2 (after 1 second)
```

## 📞 Callbacks

**Callbacks** are functions passed as arguments to other functions, executed later when an operation completes.

### Basic Callback Example
```javascript
function fetchData(callback) {
    setTimeout(() => {
        const data = "Hello from server!";
        callback(data);
    }, 1000);
}

fetchData((result) => {
    console.log(result); // "Hello from server!" (after 1 second)
});
```

### Callback Hell Problem
```javascript
// This can become hard to read and maintain
getData((data) => {
    processData(data, (processed) => {
        saveData(processed, (saved) => {
            updateUI(saved, (updated) => {
                console.log("All done!");
            });
        });
    });
});
```

## 🔮 Promises

**Promises** provide a cleaner way to handle asynchronous operations.

### Creating Promises
```javascript
const myPromise = new Promise((resolve, reject) => {
    const success = true;
    
    if (success) {
        resolve("Operation successful!");
    } else {
        reject("Operation failed!");
    }
});
```

### Using Promises
```javascript
myPromise
    .then((result) => {     // API to get data - use fetch function
        console.log(result); // "Operation successful!"
    })
    .catch((error) => {
        console.log(error); // "Operation failed!"
    });
```

### Promise Methods
```javascript
// Promise.all - wait for all promises
Promise.all([promise1, promise2, promise3])
    .then((results) => {
        console.log("All completed:", results);
    })
    .catch((error) => {
        console.log("One failed:", error);
    });

// Promise.race - first to complete wins
Promise.race([promise1, promise2, promise3])
    .then((result) => {
        console.log("First completed, then 2nd and 3rd after.", result);
    });
```

## ⚡ Async/Await

**Async/await** provides a more readable way to work with Promises.

### Basic Async/Await
```javascript
async function fetchData() {
    try {
        const response = await fetch('https://api.example.com/data');
        const data = await response.json();
        return data;
    } catch (error) {
        console.log("Error:", error);
    }
}

// Usage
fetchData().then((data) => {
    console.log(data);
});
```

### Multiple Async Operations
```javascript
async function fetchMultipleData() {
    try {
        const [userData, postsData, commentsData] = await Promise.all([
            fetch('/api/user'),
            fetch('/api/posts'),
            fetch('/api/comments')
        ]);
        
        return {
            user: await userData.json(),
            posts: await postsData.json(),
            comments: await commentsData.json()
        };
    } catch (error) {
        console.log("Error fetching data:", error);
    }
}
```

## 🎯 Practice Exercises

### Exercise 1: Callback Function
Create a function that simulates fetching user data with a callback:

**Solution:**
```javascript
function fetchUserData(userId, callback) {
    setTimeout(() => {
        const user = {
            id: userId,
            name: "Alice",
            email: "alice@example.com"
        };
        callback(null, user);
    }, 1000);
}

fetchUserData(123, (error, user) => {
    if (error) {
        console.log("Error:", error);
    } else {
        console.log("User:", user);
    }
});
```

### Exercise 2: Promise-based Function
Convert the callback function to use Promises:

**Solution:**
```javascript
function fetchUserDataPromise(userId) {
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            const user = {
                id: userId,
                name: "Alice",
                email: "alice@example.com"
            };
            resolve(user);
        }, 1000);
    });
}

fetchUserDataPromise(123)
    .then((user) => {
        console.log("User:", user);
    })
    .catch((error) => {
        console.log("Error:", error);
    });
```

### Exercise 3: Async/Await Function
Convert the Promise function to use async/await:

**Solution:**
```javascript
async function getUserData(userId) {
    try {
        const user = await fetchUserDataPromise(userId);
        console.log("User:", user);
        return user;
    } catch (error) {
        console.log("Error:", error);
    }
}

getUserData(123);
```

## 🚨 Common Mistakes to Avoid

### 1. Forgetting to Handle Errors
```javascript
// Wrong
fetch('/api/data').then(data => console.log(data));

// Right
fetch('/api/data')
    .then(data => console.log(data))
    .catch(error => console.log('Error:', error));
```

### 2. Not Using await in async Functions
```javascript
// Wrong
async function getData() {
    return fetch('/api/data'); // Returns a Promise, not the data
}

// Right
async function getData() {
    const response = await fetch('/api/data');
    return response.json();
}
```

### 3. Blocking the Event Loop
```javascript
// Wrong - blocks the main thread
function heavyTask() {
    for (let i = 0; i < 1000000000; i++) {
        // Heavy computation
    }
}

// Right - use setTimeout to allow other operations
function heavyTask() {
    setTimeout(() => {
        // Heavy computation
    }, 0);
}
```

## 🎯 Key Takeaways

1. **Asynchronous programming** allows non-blocking operations
2. **Callbacks** are functions executed after operations complete
3. **Promises** provide cleaner error handling than callbacks
4. **Async/await** makes asynchronous code more readable
5. **Error handling** is crucial in asynchronous operations
6. **Event loop** manages the execution order

## 🚀 Next Steps

Excellent! You now understand asynchronous JavaScript. In the next lesson, we'll learn about:

- **Fetch API** - making HTTP requests
- **Handling responses** - parsing JSON and other formats
- **Error handling** - managing network failures

## 📚 Additional Resources

- [MDN Promises](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Promise)
- [MDN Async/Await](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Statements/async_function)
- [JavaScript.info Promises](https://javascript.info/promise-basics)

## 🎉 Congratulations!

You've mastered asynchronous JavaScript! You now understand:

- How asynchronous programming works
- When and how to use callbacks, Promises, and async/await
- How to handle errors in asynchronous operations
- The importance of non-blocking code

Practice with the exercises, and get ready for Lesson 2 where we'll learn about the Fetch API!

---

**Next Lesson**: [Lesson 2: Fetch API](./lesson2-fetch-api.md)
