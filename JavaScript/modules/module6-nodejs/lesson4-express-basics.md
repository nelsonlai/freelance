# Lesson 4: Express.js Basics

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Set up Express.js applications
- Create routes and handle HTTP methods
- Use middleware for request processing
- Serve static files
- Handle request parameters and body
- Implement basic error handling

## 📚 Express.js Setup

### Basic Express App
```javascript
const express = require('express');
const app = express();
const port = 3000;

app.get('/', (req, res) => {
    res.send('Hello World!');
});

app.listen(port, () => {
    console.log(`Server running on http://localhost:${port}`);
});
```

### Middleware
```javascript
// Built-in middleware
app.use(express.json());
app.use(express.urlencoded({ extended: true }));
app.use(express.static('public'));

// Custom middleware
app.use((req, res, next) => {
    console.log(`${req.method} ${req.path}`);
    next();
});
```

## 🎯 Practice Exercises

### Exercise 1: Express API Server
Create a basic Express API server:

**Solution:**
```javascript
const express = require('express');
const app = express();
const port = 3000;

// Middleware
app.use(express.json());
app.use(express.static('public'));

// Routes
app.get('/api/users', (req, res) => {
    res.json([
        { id: 1, name: 'Alice' },
        { id: 2, name: 'Bob' }
    ]);
});

app.post('/api/users', (req, res) => {
    const { name } = req.body;
    res.json({ id: Date.now(), name });
});

app.listen(port, () => {
    console.log(`Server running on http://localhost:${port}`);
});
```

## 🎯 Key Takeaways

1. **Express.js** simplifies web server creation
2. **Middleware** processes requests
3. **Routes** handle different endpoints
4. **Static files** can be served easily
5. **JSON parsing** handles request bodies

---

**Next Lesson**: [Lesson 5: Routing and REST API Design](./lesson5-routing-rest.md)
