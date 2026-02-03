// Lesson 6: Error Handling Examples

console.log("=== Error Handling Examples ===");

// Example 1: Basic Try-Catch-Finally
console.log("\n=== Basic Try-Catch-Finally ===");
function riskyOperation() {
    const random = Math.random();
    if (random < 0.5) {
        throw new Error("Random error occurred!");
    }
    return "Operation successful!";
}

try {
    console.log("Attempting risky operation...");
    let result = riskyOperation();
    console.log("Result:", result);
} catch (error) {
    console.log("Caught error:", error.message);
} finally {
    console.log("This always runs (cleanup code)");
}

// Example 2: Different Types of Errors
console.log("\n=== Different Types of Errors ===");

// TypeError
try {
    let obj = null;
    console.log(obj.property); // This will throw a TypeError
} catch (error) {
    console.log("TypeError caught:", error.name, "-", error.message);
}

// ReferenceError
try {
    console.log(undefinedVariable); // This will throw a ReferenceError
} catch (error) {
    console.log("ReferenceError caught:", error.name, "-", error.message);
}

// SyntaxError (this would be caught at parse time, not runtime)
try {
    eval("let x = ;"); // Invalid syntax
} catch (error) {
    console.log("SyntaxError caught:", error.name, "-", error.message);
}

// RangeError
try {
    let arr = new Array(-1); // This will throw a RangeError
} catch (error) {
    console.log("RangeError caught:", error.name, "-", error.message);
}

// Example 3: Custom Error Throwing
console.log("\n=== Custom Error Throwing ===");
function divide(a, b) {
    if (typeof a !== 'number' || typeof b !== 'number') {
        throw new Error("Both arguments must be numbers");
    }
    if (b === 0) {
        throw new Error("Cannot divide by zero!");
    }
    return a / b;
}

function safeDivide(a, b) {
    try {
        return divide(a, b);
    } catch (error) {
        console.log("Division error:", error.message);
        return null;
    }
}

console.log("Safe division examples:");
console.log("10 / 2 =", safeDivide(10, 2));
console.log("10 / 0 =", safeDivide(10, 0));
console.log("10 / 'abc' =", safeDivide(10, 'abc'));

// Example 4: Custom Error Classes
console.log("\n=== Custom Error Classes ===");
class ValidationError extends Error {
    constructor(message, field) {
        super(message);
        this.name = 'ValidationError';
        this.field = field;
    }
}

class NetworkError extends Error {
    constructor(message, statusCode) {
        super(message);
        this.name = 'NetworkError';
        this.statusCode = statusCode;
    }
}

class DatabaseError extends Error {
    constructor(message, operation) {
        super(message);
        this.name = 'DatabaseError';
        this.operation = operation;
    }
}

// Using custom error classes
function validateUser(user) {
    if (!user.name) {
        throw new ValidationError("Name is required", "name");
    }
    if (!user.email) {
        throw new ValidationError("Email is required", "email");
    }
    if (!user.email.includes('@')) {
        throw new ValidationError("Invalid email format", "email");
    }
    return true;
}

function simulateNetworkRequest() {
    const random = Math.random();
    if (random < 0.3) {
        throw new NetworkError("Connection timeout", 408);
    }
    if (random < 0.6) {
        throw new NetworkError("Server error", 500);
    }
    return "Request successful";
}

function simulateDatabaseOperation(operation) {
    const random = Math.random();
    if (random < 0.4) {
        throw new DatabaseError("Connection lost", operation);
    }
    return `${operation} completed successfully`;
}

// Testing custom error classes
console.log("Testing validation errors:");
try {
    validateUser({ name: "Alice" }); // Missing email
} catch (error) {
    if (error instanceof ValidationError) {
        console.log(`Validation error in field '${error.field}': ${error.message}`);
    }
}

try {
    validateUser({ name: "Bob", email: "invalid-email" }); // Invalid email
} catch (error) {
    if (error instanceof ValidationError) {
        console.log(`Validation error in field '${error.field}': ${error.message}`);
    }
}

console.log("\nTesting network errors:");
try {
    simulateNetworkRequest();
} catch (error) {
    if (error instanceof NetworkError) {
        console.log(`Network error (${error.statusCode}): ${error.message}`);
    }
}

console.log("\nTesting database errors:");
try {
    simulateDatabaseOperation("INSERT");
} catch (error) {
    if (error instanceof DatabaseError) {
        console.log(`Database error during ${error.operation}: ${error.message}`);
    }
}

// Example 5: Error Handling in Async Functions
console.log("\n=== Error Handling in Async Functions ===");
function simulateAsyncOperation(successRate = 0.7) {
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            if (Math.random() < successRate) {
                resolve("Async operation successful");
            } else {
                reject(new Error("Async operation failed"));
            }
        }, 1000);
    });
}

async function handleAsyncOperation() {
    try {
        console.log("Starting async operation...");
        let result = await simulateAsyncOperation(0.3); // 30% success rate
        console.log("Async result:", result);
    } catch (error) {
        console.log("Async error caught:", error.message);
    } finally {
        console.log("Async cleanup completed");
    }
}

// Run async example
handleAsyncOperation();

// Example 6: Multiple Catch Blocks (using if-else)
console.log("\n=== Multiple Error Types Handling ===");
function processData(data) {
    try {
        if (!data) {
            throw new ValidationError("Data is required", "data");
        }
        
        if (typeof data !== 'object') {
            throw new ValidationError("Data must be an object", "data");
        }
        
        if (!data.id) {
            throw new ValidationError("ID is required", "id");
        }
        
        // Simulate processing
        if (Math.random() < 0.3) {
            throw new NetworkError("Processing service unavailable", 503);
        }
        
        return `Processed data with ID: ${data.id}`;
        
    } catch (error) {
        if (error instanceof ValidationError) {
            console.log(`Validation failed: ${error.message} (field: ${error.field})`);
            return null;
        } else if (error instanceof NetworkError) {
            console.log(`Network issue: ${error.message} (status: ${error.statusCode})`);
            return null;
        } else {
            console.log(`Unexpected error: ${error.message}`);
            return null;
        }
    }
}

// Test multiple error types
console.log("Testing multiple error types:");
console.log("Valid data:", processData({ id: 123, name: "Test" }));
console.log("No data:", processData(null));
console.log("Invalid data type:", processData("not an object"));
console.log("Missing ID:", processData({ name: "Test" }));

// Example 7: Error Logging and Recovery
console.log("\n=== Error Logging and Recovery ===");
class ErrorLogger {
    static log(error, context = {}) {
        const timestamp = new Date().toISOString();
        console.log(`[${timestamp}] ERROR: ${error.name} - ${error.message}`);
        console.log(`Context:`, context);
        
        // In a real application, you might send this to a logging service
        // or save it to a file/database
    }
    
    static attemptRecovery(error, context = {}) {
        if (error instanceof NetworkError) {
            console.log("Attempting network recovery...");
            return "Retrying network request";
        } else if (error instanceof ValidationError) {
            console.log("Attempting validation recovery...");
            return "Using default values";
        } else {
            console.log("No recovery strategy available");
            return null;
        }
    }
}

function robustOperation(data) {
    try {
        return processData(data);
    } catch (error) {
        ErrorLogger.log(error, { operation: 'processData', data: data });
        const recovery = ErrorLogger.attemptRecovery(error, { data: data });
        return recovery;
    }
}

console.log("Testing error logging and recovery:");
console.log("Result:", robustOperation(null));

console.log("\n=== Error Handling Summary ===");
console.log("✓ Try-catch-finally blocks for error handling");
console.log("✓ Throwing custom errors with meaningful messages");
console.log("✓ Custom error classes for specific error types");
console.log("✓ Error handling in async functions");
console.log("✓ Multiple error type handling");
console.log("✓ Error logging and recovery strategies");
