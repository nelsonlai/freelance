// Exercise 2: Custom Error Classes
// This exercise demonstrates creating and using custom error classes

console.log("=== Exercise 2: Custom Error Classes ===");

// Custom error classes
class ValidationError extends Error {
    constructor(message, field, value) {
        super(message);
        this.name = 'ValidationError';
        this.field = field;
        this.value = value;
        this.timestamp = new Date().toISOString();
    }
    
    getDetails() {
        return {
            name: this.name,
            message: this.message,
            field: this.field,
            value: this.value,
            timestamp: this.timestamp
        };
    }
}

class AuthenticationError extends Error {
    constructor(message, code = 'AUTH_FAILED') {
        super(message);
        this.name = 'AuthenticationError';
        this.code = code;
        this.timestamp = new Date().toISOString();
    }
    
    getDetails() {
        return {
            name: this.name,
            message: this.message,
            code: this.code,
            timestamp: this.timestamp
        };
    }
}

class DatabaseError extends Error {
    constructor(message, operation, table = null) {
        super(message);
        this.name = 'DatabaseError';
        this.operation = operation;
        this.table = table;
        this.timestamp = new Date().toISOString();
    }
    
    getDetails() {
        return {
            name: this.name,
            message: this.message,
            operation: this.operation,
            table: this.table,
            timestamp: this.timestamp
        };
    }
}

class NetworkError extends Error {
    constructor(message, statusCode, url = null) {
        super(message);
        this.name = 'NetworkError';
        this.statusCode = statusCode;
        this.url = url;
        this.timestamp = new Date().toISOString();
    }
    
    getDetails() {
        return {
            name: this.name,
            message: this.message,
            statusCode: this.statusCode,
            url: this.url,
            timestamp: this.timestamp
        };
    }
}

// User validation function using custom errors
function validateUser(user) {
    const errors = [];
    
    try {
        // Check if user object exists
        if (!user || typeof user !== 'object') {
            throw new ValidationError("User data is required", "user", user);
        }
        
        // Validate username
        if (!user.username) {
            throw new ValidationError("Username is required", "username", user.username);
        }
        
        if (typeof user.username !== 'string') {
            throw new ValidationError("Username must be a string", "username", user.username);
        }
        
        if (user.username.length < 3) {
            throw new ValidationError("Username must be at least 3 characters", "username", user.username);
        }
        
        // Validate email
        if (!user.email) {
            throw new ValidationError("Email is required", "email", user.email);
        }
        
        const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
        if (!emailRegex.test(user.email)) {
            throw new ValidationError("Invalid email format", "email", user.email);
        }
        
        // Validate age
        if (user.age !== undefined) {
            if (typeof user.age !== 'number') {
                throw new ValidationError("Age must be a number", "age", user.age);
            }
            
            if (user.age < 0 || user.age > 150) {
                throw new ValidationError("Age must be between 0 and 150", "age", user.age);
            }
        }
        
        return { success: true, user: user };
        
    } catch (error) {
        if (error instanceof ValidationError) {
            return { success: false, error: error };
        } else {
            // Re-throw unexpected errors
            throw error;
        }
    }
}

// Authentication function using custom errors
function authenticateUser(username, password) {
    try {
        // Simulate authentication logic
        if (!username || !password) {
            throw new AuthenticationError("Username and password are required", "MISSING_CREDENTIALS");
        }
        
        // Simulate checking credentials
        const validUsers = {
            'admin': 'admin123',
            'user': 'password123',
            'test': 'test123'
        };
        
        if (!validUsers[username]) {
            throw new AuthenticationError("User not found", "USER_NOT_FOUND");
        }
        
        if (validUsers[username] !== password) {
            throw new AuthenticationError("Invalid password", "INVALID_PASSWORD");
        }
        
        return { success: true, token: `token_${username}_${Date.now()}` };
        
    } catch (error) {
        if (error instanceof AuthenticationError) {
            return { success: false, error: error };
        } else {
            throw error;
        }
    }
}

// Database operation function using custom errors
function performDatabaseOperation(operation, data) {
    try {
        // Simulate database operations
        const operations = ['INSERT', 'UPDATE', 'DELETE', 'SELECT'];
        
        if (!operations.includes(operation)) {
            throw new DatabaseError(`Invalid operation: ${operation}`, operation);
        }
        
        if (!data) {
            throw new DatabaseError("Data is required for database operation", operation);
        }
        
        // Simulate random database failures
        if (Math.random() < 0.3) {
            throw new DatabaseError("Database connection lost", operation, data.table || 'unknown');
        }
        
        return { success: true, result: `${operation} operation completed successfully` };
        
    } catch (error) {
        if (error instanceof DatabaseError) {
            return { success: false, error: error };
        } else {
            throw error;
        }
    }
}

// Network request function using custom errors
function makeNetworkRequest(url, method = 'GET') {
    try {
        if (!url) {
            throw new NetworkError("URL is required", 400);
        }
        
        // Simulate network request
        const random = Math.random();
        
        if (random < 0.2) {
            throw new NetworkError("Connection timeout", 408, url);
        } else if (random < 0.4) {
            throw new NetworkError("Server error", 500, url);
        } else if (random < 0.6) {
            throw new NetworkError("Not found", 404, url);
        }
        
        return { success: true, data: `Response from ${url}` };
        
    } catch (error) {
        if (error instanceof NetworkError) {
            return { success: false, error: error };
        } else {
            throw error;
        }
    }
}

// Test the custom error classes
console.log("=== Testing Custom Error Classes ===");

// Test validation errors
console.log("\n1. Testing Validation Errors:");
const invalidUsers = [
    null,
    { username: "ab" }, // Too short
    { username: "validuser", email: "invalid-email" }, // Invalid email
    { username: 123, email: "test@example.com" }, // Invalid username type
    { username: "validuser", email: "test@example.com", age: -5 } // Invalid age
];

invalidUsers.forEach((user, index) => {
    console.log(`\nTest ${index + 1}:`, user);
    const result = validateUser(user);
    if (!result.success) {
        console.log("Validation failed:", result.error.getDetails());
    } else {
        console.log("Validation passed");
    }
});

// Test authentication errors
console.log("\n2. Testing Authentication Errors:");
const authTests = [
    { username: "admin", password: "admin123" }, // Valid
    { username: "admin", password: "wrong" }, // Wrong password
    { username: "nonexistent", password: "password" }, // User not found
    { username: "", password: "password" } // Missing username
];

authTests.forEach((test, index) => {
    console.log(`\nAuth Test ${index + 1}:`, test);
    const result = authenticateUser(test.username, test.password);
    if (!result.success) {
        console.log("Authentication failed:", result.error.getDetails());
    } else {
        console.log("Authentication successful:", result.token);
    }
});

// Test database errors
console.log("\n3. Testing Database Errors:");
const dbTests = [
    { operation: "INSERT", data: { table: "users", name: "John" } },
    { operation: "INVALID", data: { table: "users" } },
    { operation: "UPDATE", data: null }
];

dbTests.forEach((test, index) => {
    console.log(`\nDB Test ${index + 1}:`, test);
    const result = performDatabaseOperation(test.operation, test.data);
    if (!result.success) {
        console.log("Database operation failed:", result.error.getDetails());
    } else {
        console.log("Database operation successful:", result.result);
    }
});

// Test network errors
console.log("\n4. Testing Network Errors:");
const networkTests = [
    "https://api.example.com/users",
    "https://api.example.com/posts",
    "" // Empty URL
];

networkTests.forEach((url, index) => {
    console.log(`\nNetwork Test ${index + 1}: ${url || 'Empty URL'}`);
    const result = makeNetworkRequest(url);
    if (!result.success) {
        console.log("Network request failed:", result.error.getDetails());
    } else {
        console.log("Network request successful:", result.data);
    }
});

console.log("\n=== Custom Error Classes Summary ===");
console.log("✓ Created custom error classes with additional properties");
console.log("✓ Implemented getDetails() method for error information");
console.log("✓ Used custom errors in validation, authentication, database, and network operations");
console.log("✓ Demonstrated proper error handling and user feedback");
