// Exercise 3: Robust Error Handling System
// This exercise demonstrates a comprehensive error handling system

console.log("=== Exercise 3: Robust Error Handling System ===");

// Error types and codes
const ERROR_TYPES = {
    VALIDATION: 'VALIDATION',
    AUTHENTICATION: 'AUTHENTICATION',
    AUTHORIZATION: 'AUTHORIZATION',
    NETWORK: 'NETWORK',
    DATABASE: 'DATABASE',
    BUSINESS_LOGIC: 'BUSINESS_LOGIC',
    SYSTEM: 'SYSTEM'
};

const ERROR_CODES = {
    // Validation codes
    REQUIRED_FIELD: 'REQUIRED_FIELD',
    INVALID_FORMAT: 'INVALID_FORMAT',
    OUT_OF_RANGE: 'OUT_OF_RANGE',
    
    // Authentication codes
    INVALID_CREDENTIALS: 'INVALID_CREDENTIALS',
    TOKEN_EXPIRED: 'TOKEN_EXPIRED',
    USER_NOT_FOUND: 'USER_NOT_FOUND',
    
    // Network codes
    CONNECTION_TIMEOUT: 'CONNECTION_TIMEOUT',
    SERVER_ERROR: 'SERVER_ERROR',
    NOT_FOUND: 'NOT_FOUND',
    
    // Database codes
    CONNECTION_FAILED: 'CONNECTION_FAILED',
    QUERY_FAILED: 'QUERY_FAILED',
    CONSTRAINT_VIOLATION: 'CONSTRAINT_VIOLATION'
};

// Base error class
class AppError extends Error {
    constructor(message, type, code, details = {}) {
        super(message);
        this.name = 'AppError';
        this.type = type;
        this.code = code;
        this.details = details;
        this.timestamp = new Date().toISOString();
        this.stack = this.stack;
    }
    
    toJSON() {
        return {
            name: this.name,
            message: this.message,
            type: this.type,
            code: this.code,
            details: this.details,
            timestamp: this.timestamp
        };
    }
}

// Specific error classes
class ValidationError extends AppError {
    constructor(message, field, value, code = ERROR_CODES.REQUIRED_FIELD) {
        super(message, ERROR_TYPES.VALIDATION, code, { field, value });
        this.name = 'ValidationError';
    }
}

class AuthenticationError extends AppError {
    constructor(message, code = ERROR_CODES.INVALID_CREDENTIALS) {
        super(message, ERROR_TYPES.AUTHENTICATION, code);
        this.name = 'AuthenticationError';
    }
}

class NetworkError extends AppError {
    constructor(message, statusCode, url, code = ERROR_CODES.SERVER_ERROR) {
        super(message, ERROR_TYPES.NETWORK, code, { statusCode, url });
        this.name = 'NetworkError';
    }
}

class DatabaseError extends AppError {
    constructor(message, operation, table, code = ERROR_CODES.QUERY_FAILED) {
        super(message, ERROR_TYPES.DATABASE, code, { operation, table });
        this.name = 'DatabaseError';
    }
}

// Error handler class
class ErrorHandler {
    static handle(error, context = {}) {
        const errorInfo = {
            error: error.toJSON ? error.toJSON() : {
                name: error.name,
                message: error.message,
                stack: error.stack
            },
            context: context,
            timestamp: new Date().toISOString()
        };
        
        // Log error
        this.logError(errorInfo);
        
        // Determine user-friendly message
        const userMessage = this.getUserMessage(error);
        
        // Determine if error should be reported
        const shouldReport = this.shouldReportError(error);
        
        return {
            success: false,
            error: userMessage,
            details: shouldReport ? errorInfo : null,
            code: error.code || 'UNKNOWN_ERROR'
        };
    }
    
    static logError(errorInfo) {
        console.log(`[ERROR LOG] ${errorInfo.timestamp}`);
        console.log(`Type: ${errorInfo.error.type || 'Unknown'}`);
        console.log(`Message: ${errorInfo.error.message}`);
        console.log(`Context:`, errorInfo.context);
        console.log('---');
        
        // In a real application, you would send this to a logging service
        // or save it to a file/database
    }
    
    static getUserMessage(error) {
        if (error instanceof ValidationError) {
            return `Please check your input: ${error.message}`;
        } else if (error instanceof AuthenticationError) {
            return "Authentication failed. Please check your credentials.";
        } else if (error instanceof NetworkError) {
            return "Network error occurred. Please try again later.";
        } else if (error instanceof DatabaseError) {
            return "Database error occurred. Please contact support.";
        } else {
            return "An unexpected error occurred. Please try again.";
        }
    }
    
    static shouldReportError(error) {
        // Don't report user input validation errors
        if (error instanceof ValidationError) {
            return false;
        }
        
        // Report system errors
        if (error instanceof DatabaseError || error instanceof NetworkError) {
            return true;
        }
        
        // Report unexpected errors
        if (!(error instanceof AppError)) {
            return true;
        }
        
        return false;
    }
}

// Retry mechanism
class RetryHandler {
    static async retry(operation, maxRetries = 3, delay = 1000) {
        let lastError;
        
        for (let attempt = 1; attempt <= maxRetries; attempt++) {
            try {
                console.log(`Attempt ${attempt}/${maxRetries}`);
                return await operation();
            } catch (error) {
                lastError = error;
                
                // Don't retry validation or authentication errors
                if (error instanceof ValidationError || error instanceof AuthenticationError) {
                    throw error;
                }
                
                if (attempt < maxRetries) {
                    console.log(`Attempt ${attempt} failed, retrying in ${delay}ms...`);
                    await this.delay(delay);
                    delay *= 2; // Exponential backoff
                }
            }
        }
        
        throw lastError;
    }
    
    static delay(ms) {
        return new Promise(resolve => setTimeout(resolve, ms));
    }
}

// Example application functions with error handling
class UserService {
    static async createUser(userData) {
        try {
            // Validate user data
            this.validateUserData(userData);
            
            // Simulate database operation
            const user = await this.saveUserToDatabase(userData);
            
            return { success: true, user: user };
            
        } catch (error) {
            return ErrorHandler.handle(error, { operation: 'createUser', userData });
        }
    }
    
    static validateUserData(userData) {
        if (!userData) {
            throw new ValidationError("User data is required", "userData", userData);
        }
        
        if (!userData.email) {
            throw new ValidationError("Email is required", "email", userData.email);
        }
        
        const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
        if (!emailRegex.test(userData.email)) {
            throw new ValidationError("Invalid email format", "email", userData.email, ERROR_CODES.INVALID_FORMAT);
        }
        
        if (!userData.username) {
            throw new ValidationError("Username is required", "username", userData.username);
        }
        
        if (userData.username.length < 3) {
            throw new ValidationError("Username must be at least 3 characters", "username", userData.username, ERROR_CODES.OUT_OF_RANGE);
        }
    }
    
    static async saveUserToDatabase(userData) {
        // Simulate database operation with potential failures
        return new Promise((resolve, reject) => {
            setTimeout(() => {
                const random = Math.random();
                
                if (random < 0.3) {
                    reject(new DatabaseError("Database connection failed", "INSERT", "users", ERROR_CODES.CONNECTION_FAILED));
                } else if (random < 0.5) {
                    reject(new DatabaseError("Username already exists", "INSERT", "users", ERROR_CODES.CONSTRAINT_VIOLATION));
                } else {
                    resolve({
                        id: Date.now(),
                        ...userData,
                        createdAt: new Date().toISOString()
                    });
                }
            }, 500);
        });
    }
}

class ApiService {
    static async fetchUserData(userId) {
        try {
            const userData = await RetryHandler.retry(async () => {
                return await this.makeApiRequest(`/api/users/${userId}`);
            });
            
            return { success: true, data: userData };
            
        } catch (error) {
            return ErrorHandler.handle(error, { operation: 'fetchUserData', userId });
        }
    }
    
    static async makeApiRequest(url) {
        // Simulate API request with potential failures
        return new Promise((resolve, reject) => {
            setTimeout(() => {
                const random = Math.random();
                
                if (random < 0.2) {
                    reject(new NetworkError("Connection timeout", 408, url, ERROR_CODES.CONNECTION_TIMEOUT));
                } else if (random < 0.4) {
                    reject(new NetworkError("Server error", 500, url, ERROR_CODES.SERVER_ERROR));
                } else if (random < 0.6) {
                    reject(new NetworkError("Not found", 404, url, ERROR_CODES.NOT_FOUND));
                } else {
                    resolve({ id: 123, name: "John Doe", email: "john@example.com" });
                }
            }, 1000);
        });
    }
}

// Test the robust error handling system
console.log("=== Testing Robust Error Handling System ===");

async function runTests() {
    // Test 1: User creation with validation errors
    console.log("\n1. Testing User Creation with Validation Errors:");
    
    const invalidUsers = [
        null,
        { email: "invalid-email" },
        { email: "test@example.com" }, // Missing username
        { email: "test@example.com", username: "ab" } // Username too short
    ];
    
    for (let i = 0; i < invalidUsers.length; i++) {
        console.log(`\nTest ${i + 1}:`, invalidUsers[i]);
        const result = await UserService.createUser(invalidUsers[i]);
        console.log("Result:", result);
    }
    
    // Test 2: User creation with database errors
    console.log("\n2. Testing User Creation with Database Errors:");
    
    const validUser = { email: "test@example.com", username: "testuser" };
    
    for (let i = 0; i < 3; i++) {
        console.log(`\nAttempt ${i + 1}:`);
        const result = await UserService.createUser(validUser);
        console.log("Result:", result);
    }
    
    // Test 3: API requests with retry mechanism
    console.log("\n3. Testing API Requests with Retry Mechanism:");
    
    for (let i = 0; i < 3; i++) {
        console.log(`\nAPI Test ${i + 1}:`);
        const result = await ApiService.fetchUserData(123);
        console.log("Result:", result);
    }
}

// Run the tests
runTests().then(() => {
    console.log("\n=== Robust Error Handling System Summary ===");
    console.log("✓ Comprehensive error classification system");
    console.log("✓ Centralized error handling and logging");
    console.log("✓ User-friendly error messages");
    console.log("✓ Retry mechanism with exponential backoff");
    console.log("✓ Error reporting based on error type");
    console.log("✓ Context-aware error handling");
}).catch(error => {
    console.error("Test execution failed:", error);
});
