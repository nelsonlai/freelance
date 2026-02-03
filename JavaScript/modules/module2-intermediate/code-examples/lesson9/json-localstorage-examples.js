// Lesson 9: JSON and LocalStorage Examples
// Note: These examples work in both Node.js and browser environments

console.log("=== JSON and LocalStorage Examples ===");

// Example 1: JSON Basics
console.log("\n=== Example 1: JSON Basics ===");

// JavaScript object
let person = {
    name: "Alice",
    age: 30,
    city: "New York",
    hobbies: ["reading", "swimming", "coding"],
    isStudent: false,
    address: {
        street: "123 Main St",
        zipCode: "10001"
    }
};

console.log("Original JavaScript object:");
console.log(person);

// Convert to JSON string
let jsonString = JSON.stringify(person);
console.log("\nJSON string:");
console.log(jsonString);

// Convert back to JavaScript object
let parsedPerson = JSON.parse(jsonString);
console.log("\nParsed back to JavaScript object:");
console.log(parsedPerson);

// Example 2: JSON with Different Data Types
console.log("\n=== Example 2: JSON with Different Data Types ===");

let complexData = {
    string: "Hello World",
    number: 42,
    boolean: true,
    nullValue: null,
    undefinedValue: undefined, // Will be omitted in JSON
    array: [1, 2, 3, "four", true],
    object: {
        nested: "value",
        deep: {
            level: 3
        }
    },
    date: new Date(), // Will be converted to string
    function: function() { return "test"; } // Will be omitted in JSON
};

console.log("Complex data before JSON:");
console.log(complexData);

let complexJson = JSON.stringify(complexData);
console.log("\nComplex data as JSON:");
console.log(complexJson);

let parsedComplex = JSON.parse(complexJson);
console.log("\nParsed complex data:");
console.log(parsedComplex);

// Example 3: JSON with Custom Replacer and Reviver
console.log("\n=== Example 3: JSON with Custom Replacer and Reviver ===");

let dataWithFunctions = {
    name: "John",
    age: 25,
    greet: function() { return "Hello!"; },
    secret: "password123"
};

// Custom replacer function
function replacer(key, value) {
    if (typeof value === 'function') {
        return value.toString(); // Convert function to string
    }
    if (key === 'secret') {
        return '***'; // Hide secret values
    }
    return value;
}

let jsonWithReplacer = JSON.stringify(dataWithFunctions, replacer, 2);
console.log("JSON with custom replacer:");
console.log(jsonWithReplacer);

// Custom reviver function
function reviver(key, value) {
    if (typeof value === 'string' && value.startsWith('function')) {
        return eval('(' + value + ')'); // Convert string back to function
    }
    return value;
}

let parsedWithReviver = JSON.parse(jsonWithReplacer, reviver);
console.log("\nParsed with custom reviver:");
console.log(parsedWithReviver);

// Example 4: LocalStorage Simulation (Node.js compatible)
console.log("\n=== Example 4: LocalStorage Simulation ===");

// Simulate localStorage for Node.js
class LocalStorageSimulator {
    constructor() {
        this.store = {};
    }
    
    setItem(key, value) {
        this.store[key] = String(value);
        console.log(`localStorage.setItem('${key}', '${value}')`);
    }
    
    getItem(key) {
        const value = this.store[key];
        console.log(`localStorage.getItem('${key}') = ${value}`);
        return value;
    }
    
    removeItem(key) {
        delete this.store[key];
        console.log(`localStorage.removeItem('${key}')`);
    }
    
    clear() {
        this.store = {};
        console.log("localStorage.clear()");
    }
    
    get length() {
        return Object.keys(this.store).length;
    }
    
    key(index) {
        const keys = Object.keys(this.store);
        return keys[index];
    }
}

// Use localStorage simulator
const localStorage = new LocalStorageSimulator();

// Store JSON data in localStorage
let userData = {
    id: 1,
    name: "Alice",
    email: "alice@example.com",
    preferences: {
        theme: "dark",
        language: "en"
    }
};

console.log("Storing user data in localStorage:");
localStorage.setItem('user', JSON.stringify(userData));
localStorage.setItem('settings', JSON.stringify({ notifications: true }));

// Retrieve and parse data from localStorage
console.log("\nRetrieving data from localStorage:");
let storedUser = localStorage.getItem('user');
let parsedUser = JSON.parse(storedUser);
console.log("Retrieved user:", parsedUser);

let storedSettings = localStorage.getItem('settings');
let parsedSettings = JSON.parse(storedSettings);
console.log("Retrieved settings:", parsedSettings);

// Example 5: LocalStorage Utilities
console.log("\n=== Example 5: LocalStorage Utilities ===");

class StorageManager {
    constructor(storage = localStorage) {
        this.storage = storage;
    }
    
    save(key, data) {
        try {
            const jsonString = JSON.stringify(data);
            this.storage.setItem(key, jsonString);
            return true;
        } catch (error) {
            console.error("Error saving to storage:", error);
            return false;
        }
    }
    
    load(key) {
        try {
            const jsonString = this.storage.getItem(key);
            if (jsonString === null) {
                return null;
            }
            return JSON.parse(jsonString);
        } catch (error) {
            console.error("Error loading from storage:", error);
            return null;
        }
    }
    
    remove(key) {
        this.storage.removeItem(key);
    }
    
    clear() {
        this.storage.clear();
    }
    
    exists(key) {
        return this.storage.getItem(key) !== null;
    }
    
    getAllKeys() {
        const keys = [];
        for (let i = 0; i < this.storage.length; i++) {
            keys.push(this.storage.key(i));
        }
        return keys;
    }
}

// Use StorageManager
const storageManager = new StorageManager();

console.log("Using StorageManager:");
storageManager.save('todoList', [
    { id: 1, text: 'Learn JavaScript', completed: false },
    { id: 2, text: 'Build a project', completed: true },
    { id: 3, text: 'Deploy to production', completed: false }
]);

storageManager.save('userProfile', {
    name: 'Bob',
    avatar: 'avatar.jpg',
    lastLogin: new Date().toISOString()
});

console.log("\nRetrieved todo list:", storageManager.load('todoList'));
console.log("Retrieved user profile:", storageManager.load('userProfile'));
console.log("All keys:", storageManager.getAllKeys());
console.log("'todoList' exists:", storageManager.exists('todoList'));

// Example 6: Error Handling with JSON
console.log("\n=== Example 6: Error Handling with JSON ===");

function safeJsonParse(jsonString) {
    try {
        return JSON.parse(jsonString);
    } catch (error) {
        console.error("JSON parse error:", error.message);
        return null;
    }
}

function safeJsonStringify(obj) {
    try {
        return JSON.stringify(obj);
    } catch (error) {
        console.error("JSON stringify error:", error.message);
        return null;
    }
}

// Test error handling
let invalidJson = '{"name": "Alice", "age": 30,}'; // Trailing comma
let parsed = safeJsonParse(invalidJson);
console.log("Parsed invalid JSON:", parsed);

let circularObj = { name: "Alice" };
circularObj.self = circularObj; // Circular reference
let stringified = safeJsonStringify(circularObj);
console.log("Stringified circular object:", stringified);

// Example 7: Data Validation with JSON
console.log("\n=== Example 7: Data Validation with JSON ===");

function validateUserData(data) {
    const required = ['name', 'email', 'age'];
    const missing = required.filter(field => !data[field]);
    
    if (missing.length > 0) {
        throw new Error(`Missing required fields: ${missing.join(', ')}`);
    }
    
    if (typeof data.age !== 'number' || data.age < 0) {
        throw new Error('Age must be a positive number');
    }
    
    if (!data.email.includes('@')) {
        throw new Error('Invalid email format');
    }
    
    return true;
}

function saveUserSafely(userData) {
    try {
        validateUserData(userData);
        const jsonString = JSON.stringify(userData);
        localStorage.setItem('user', jsonString);
        console.log("User saved successfully");
        return true;
    } catch (error) {
        console.error("Validation error:", error.message);
        return false;
    }
}

// Test validation
console.log("Testing user validation:");
saveUserSafely({ name: "Alice", email: "alice@example.com", age: 30 });
saveUserSafely({ name: "Bob", email: "invalid-email", age: 25 });
saveUserSafely({ name: "Charlie", age: 35 }); // Missing email

// Example 8: Batch Operations
console.log("\n=== Example 8: Batch Operations ===");

class BatchStorageManager extends StorageManager {
    constructor(storage = localStorage) {
        super(storage);
        this.batch = {};
    }
    
    batchSave(key, data) {
        this.batch[key] = data;
    }
    
    commitBatch() {
        const results = {};
        for (const [key, data] of Object.entries(this.batch)) {
            results[key] = this.save(key, data);
        }
        this.batch = {};
        return results;
    }
    
    rollbackBatch() {
        this.batch = {};
        console.log("Batch rolled back");
    }
}

// Use batch operations
const batchManager = new BatchStorageManager();

console.log("Batch operations:");
batchManager.batchSave('user1', { name: 'Alice', age: 30 });
batchManager.batchSave('user2', { name: 'Bob', age: 25 });
batchManager.batchSave('user3', { name: 'Charlie', age: 35 });

console.log("Committing batch:");
const results = batchManager.commitBatch();
console.log("Batch results:", results);

console.log("\n=== JSON and LocalStorage Summary ===");
console.log("✓ JSON.stringify() and JSON.parse()");
console.log("✓ Custom replacer and reviver functions");
console.log("✓ LocalStorage operations (setItem, getItem, removeItem)");
console.log("✓ Storage utility classes");
console.log("✓ Error handling with JSON operations");
console.log("✓ Data validation before storage");
console.log("✓ Batch storage operations");
console.log("✓ Cross-environment compatibility");
