# Lesson 9: Error Handling in Express

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Implement comprehensive error handling
- Create custom error classes
- Use error handling middleware
- Handle different types of errors
- Implement logging and monitoring
- Create user-friendly error responses

## 📚 Error Handling Patterns

### Custom Error Classes
```javascript
class AppError extends Error {
    constructor(message, statusCode) {
        super(message);
        this.statusCode = statusCode;
        this.isOperational = true;
        Error.captureStackTrace(this, this.constructor);
    }
}

class ValidationError extends AppError {
    constructor(message) {
        super(message, 400);
    }
}
```

### Error Handling Middleware
```javascript
function errorHandler(err, req, res, next) {
    let error = { ...err };
    error.message = err.message;
    
    // Mongoose bad ObjectId
    if (err.name === 'CastError') {
        const message = 'Resource not found';
        error = new AppError(message, 404);
    }
    
    // Mongoose duplicate key
    if (err.code === 11000) {
        const message = 'Duplicate field value entered';
        error = new AppError(message, 400);
    }
    
    // Mongoose validation error
    if (err.name === 'ValidationError') {
        const message = Object.values(err.errors).map(val => val.message);
        error = new AppError(message, 400);
    }
    
    res.status(error.statusCode || 500).json({
        success: false,
        error: error.message || 'Server Error'
    });
}
```

## 🎯 Practice Exercises

### Exercise 1: Complete Error Handling System
Create a comprehensive error handling system:

**Solution:**
```javascript
const express = require('express');
const mongoose = require('mongoose');

const app = express();
app.use(express.json());

// Custom Error Classes
class AppError extends Error {
    constructor(message, statusCode) {
        super(message);
        this.statusCode = statusCode;
        this.isOperational = true;
        Error.captureStackTrace(this, this.constructor);
    }
}

class ValidationError extends AppError {
    constructor(message) {
        super(message, 400);
    }
}

class NotFoundError extends AppError {
    constructor(resource) {
        super(`${resource} not found`, 404);
    }
}

// Error Handling Middleware
function errorHandler(err, req, res, next) {
    let error = { ...err };
    error.message = err.message;
    
    // Log error
    console.error(err);
    
    // Mongoose bad ObjectId
    if (err.name === 'CastError') {
        const message = 'Resource not found';
        error = new AppError(message, 404);
    }
    
    // Mongoose duplicate key
    if (err.code === 11000) {
        const message = 'Duplicate field value entered';
        error = new AppError(message, 400);
    }
    
    // Mongoose validation error
    if (err.name === 'ValidationError') {
        const message = Object.values(err.errors).map(val => val.message);
        error = new AppError(message, 400);
    }
    
    // JWT errors
    if (err.name === 'JsonWebTokenError') {
        const message = 'Invalid token';
        error = new AppError(message, 401);
    }
    
    if (err.name === 'TokenExpiredError') {
        const message = 'Token expired';
        error = new AppError(message, 401);
    }
    
    res.status(error.statusCode || 500).json({
        success: false,
        error: error.message || 'Server Error',
        ...(process.env.NODE_ENV === 'development' && { stack: err.stack })
    });
}

// Async Error Handler
function asyncHandler(fn) {
    return (req, res, next) => {
        Promise.resolve(fn(req, res, next)).catch(next);
    };
}

// Example route with error handling
app.get('/api/users/:id', asyncHandler(async (req, res, next) => {
    const user = await User.findById(req.params.id);
    
    if (!user) {
        return next(new NotFoundError('User'));
    }
    
    res.json({
        success: true,
        data: user
    });
}));

// Global error handler (must be last)
app.use(errorHandler);

app.listen(3000, () => {
    console.log('Server running on http://localhost:3000');
});
```

## 🎯 Key Takeaways

1. **Custom error classes** provide specific error types
2. **Error middleware** handles all errors centrally
3. **Async error handling** catches promise rejections
4. **Error logging** helps with debugging
5. **User-friendly messages** improve experience

---

**Next Lesson**: [Lesson 10: Mini Project - Simple Blog API](./lesson10-mini-project.md)
