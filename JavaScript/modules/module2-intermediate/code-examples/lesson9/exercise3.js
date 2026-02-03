// Exercise 3: JSON Schema Validation System
// This exercise demonstrates advanced JSON handling with schema validation

console.log("=== Exercise 3: JSON Schema Validation System ===");

// LocalStorage simulator for Node.js
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

// JSON Schema validator
class JSONSchemaValidator {
    constructor() {
        this.schemas = {};
    }
    
    // Register a schema
    registerSchema(name, schema) {
        this.schemas[name] = schema;
        console.log(`Schema registered: ${name}`);
    }
    
    // Validate data against schema
    validate(data, schemaName) {
        const schema = this.schemas[schemaName];
        if (!schema) {
            throw new Error(`Schema '${schemaName}' not found`);
        }
        
        const errors = this.validateValue(data, schema, 'root');
        
        return {
            valid: errors.length === 0,
            errors: errors
        };
    }
    
    // Recursive validation
    validateValue(value, schema, path) {
        const errors = [];
        
        // Required field validation
        if (schema.required && schema.type === 'object') {
            schema.required.forEach(field => {
                if (!(field in value)) {
                    errors.push({
                        path: `${path}.${field}`,
                        message: `Required field '${field}' is missing`,
                        type: 'required'
                    });
                }
            });
        }
        
        // Type validation
        if (schema.type) {
            const typeError = this.validateType(value, schema.type, path);
            if (typeError) {
                errors.push(typeError);
            }
        }
        
        // Additional validations based on type
        if (schema.type === 'string') {
            errors.push(...this.validateString(value, schema, path));
        } else if (schema.type === 'number') {
            errors.push(...this.validateNumber(value, schema, path));
        } else if (schema.type === 'array') {
            errors.push(...this.validateArray(value, schema, path));
        } else if (schema.type === 'object') {
            errors.push(...this.validateObject(value, schema, path));
        }
        
        return errors;
    }
    
    validateType(value, expectedType, path) {
        const actualType = this.getType(value);
        
        if (actualType !== expectedType) {
            return {
                path,
                message: `Expected ${expectedType}, got ${actualType}`,
                type: 'type_mismatch',
                expected: expectedType,
                actual: actualType
            };
        }
        
        return null;
    }
    
    getType(value) {
        if (value === null) return 'null';
        if (Array.isArray(value)) return 'array';
        return typeof value;
    }
    
    validateString(value, schema, path) {
        const errors = [];
        
        if (schema.minLength && value.length < schema.minLength) {
            errors.push({
                path,
                message: `String length ${value.length} is less than minimum ${schema.minLength}`,
                type: 'min_length'
            });
        }
        
        if (schema.maxLength && value.length > schema.maxLength) {
            errors.push({
                path,
                message: `String length ${value.length} exceeds maximum ${schema.maxLength}`,
                type: 'max_length'
            });
        }
        
        if (schema.pattern && !schema.pattern.test(value)) {
            errors.push({
                path,
                message: `String does not match pattern ${schema.pattern}`,
                type: 'pattern'
            });
        }
        
        if (schema.enum && !schema.enum.includes(value)) {
            errors.push({
                path,
                message: `Value '${value}' is not in allowed values: ${schema.enum.join(', ')}`,
                type: 'enum'
            });
        }
        
        return errors;
    }
    
    validateNumber(value, schema, path) {
        const errors = [];
        
        if (schema.minimum !== undefined && value < schema.minimum) {
            errors.push({
                path,
                message: `Value ${value} is less than minimum ${schema.minimum}`,
                type: 'minimum'
            });
        }
        
        if (schema.maximum !== undefined && value > schema.maximum) {
            errors.push({
                path,
                message: `Value ${value} exceeds maximum ${schema.maximum}`,
                type: 'maximum'
            });
        }
        
        return errors;
    }
    
    validateArray(value, schema, path) {
        const errors = [];
        
        if (schema.minItems && value.length < schema.minItems) {
            errors.push({
                path,
                message: `Array length ${value.length} is less than minimum ${schema.minItems}`,
                type: 'min_items'
            });
        }
        
        if (schema.maxItems && value.length > schema.maxItems) {
            errors.push({
                path,
                message: `Array length ${value.length} exceeds maximum ${schema.maxItems}`,
                type: 'max_items'
            });
        }
        
        if (schema.items) {
            value.forEach((item, index) => {
                errors.push(...this.validateValue(item, schema.items, `${path}[${index}]`));
            });
        }
        
        return errors;
    }
    
    validateObject(value, schema, path) {
        const errors = [];
        
        if (schema.properties) {
            for (const [key, propSchema] of Object.entries(schema.properties)) {
                if (key in value) {
                    errors.push(...this.validateValue(value[key], propSchema, `${path}.${key}`));
                }
            }
        }
        
        if (schema.additionalProperties === false) {
            const allowedKeys = Object.keys(schema.properties || {});
            for (const key of Object.keys(value)) {
                if (!allowedKeys.includes(key)) {
                    errors.push({
                        path: `${path}.${key}`,
                        message: `Additional property '${key}' is not allowed`,
                        type: 'additional_property'
                    });
                }
            }
        }
        
        return errors;
    }
}

// Data manager with schema validation
class SchemaValidatedDataManager {
    constructor(storage = new LocalStorageSimulator()) {
        this.storage = storage;
        this.validator = new JSONSchemaValidator();
        this.prefix = 'validated_';
    }
    
    // Register schema
    registerSchema(name, schema) {
        this.validator.registerSchema(name, schema);
    }
    
    // Save data with validation
    save(key, data, schemaName) {
        const validation = this.validator.validate(data, schemaName);
        
        if (!validation.valid) {
            console.error(`Validation failed for ${key}:`, validation.errors);
            return { success: false, errors: validation.errors };
        }
        
        const fullKey = `${this.prefix}${key}`;
        const jsonString = JSON.stringify(data);
        this.storage.setItem(fullKey, jsonString);
        
        console.log(`✓ Data saved and validated: ${key}`);
        return { success: true };
    }
    
    // Load data
    load(key) {
        const fullKey = `${this.prefix}${key}`;
        const storedData = this.storage.getItem(fullKey);
        
        if (storedData === null) {
            return null;
        }
        
        try {
            return JSON.parse(storedData);
        } catch (error) {
            console.error(`Error parsing data for ${key}:`, error);
            return null;
        }
    }
    
    // Validate existing data
    validateExisting(key, schemaName) {
        const data = this.load(key);
        if (data === null) {
            return { valid: false, errors: [{ message: 'Data not found', type: 'not_found' }] };
        }
        
        return this.validator.validate(data, schemaName);
    }
}

// Test the JSON schema validation system
console.log("Testing JSON schema validation system...");

const dataManager = new SchemaValidatedDataManager();

// Define schemas
const userSchema = {
    type: 'object',
    required: ['id', 'name', 'email'],
    properties: {
        id: { type: 'number', minimum: 1 },
        name: { type: 'string', minLength: 2, maxLength: 50 },
        email: { type: 'string', pattern: /^[^\s@]+@[^\s@]+\.[^\s@]+$/ },
        age: { type: 'number', minimum: 0, maximum: 150 },
        role: { type: 'string', enum: ['user', 'admin', 'moderator'] }
    },
    additionalProperties: false
};

const todoSchema = {
    type: 'object',
    required: ['id', 'text', 'completed'],
    properties: {
        id: { type: 'number', minimum: 1 },
        text: { type: 'string', minLength: 1, maxLength: 500 },
        completed: { type: 'boolean' },
        priority: { type: 'string', enum: ['low', 'medium', 'high'] },
        tags: { type: 'array', minItems: 0, maxItems: 10, items: { type: 'string' } }
    }
};

const todoListSchema = {
    type: 'object',
    required: ['todos'],
    properties: {
        todos: { type: 'array', items: todoSchema },
        metadata: {
            type: 'object',
            properties: {
                total: { type: 'number', minimum: 0 },
                completed: { type: 'number', minimum: 0 }
            }
        }
    }
};

// Register schemas
dataManager.registerSchema('user', userSchema);
dataManager.registerSchema('todo', todoSchema);
dataManager.registerSchema('todoList', todoListSchema);

// Test 1: Valid data
console.log("\n=== Test 1: Valid Data ===");

const validUser = {
    id: 1,
    name: 'Alice Johnson',
    email: 'alice@example.com',
    age: 30,
    role: 'user'
};

const result1 = dataManager.save('user1', validUser, 'user');
console.log('Save result:', result1);

// Test 2: Invalid data
console.log("\n=== Test 2: Invalid Data ===");

const invalidUser = {
    id: 0, // Invalid: minimum is 1
    name: 'A', // Invalid: minLength is 2
    email: 'invalid-email', // Invalid: doesn't match pattern
    age: 200, // Invalid: maximum is 150
    role: 'invalid-role', // Invalid: not in enum
    extraField: 'not allowed' // Invalid: additionalProperties is false
};

const result2 = dataManager.save('user2', invalidUser, 'user');
console.log('Save result:', result2);

// Test 3: Todo list validation
console.log("\n=== Test 3: Todo List Validation ===");

const validTodoList = {
    todos: [
        { id: 1, text: 'Learn JavaScript', completed: false, priority: 'high', tags: ['learning'] },
        { id: 2, text: 'Build a project', completed: true, priority: 'medium', tags: ['project', 'coding'] }
    ],
    metadata: {
        total: 2,
        completed: 1
    }
};

const result3 = dataManager.save('todoList1', validTodoList, 'todoList');
console.log('Save result:', result3);

// Test 4: Partial validation
console.log("\n=== Test 4: Partial Validation ===");

const partialUser = {
    id: 2,
    name: 'Bob Smith'
    // Missing required email field
};

const result4 = dataManager.save('user3', partialUser, 'user');
console.log('Save result:', result4);

// Test 5: Validate existing data
console.log("\n=== Test 5: Validate Existing Data ===");

const validationResult = dataManager.validateExisting('user1', 'user');
console.log('Validation result:', validationResult);

// Test 6: Schema evolution
console.log("\n=== Test 6: Schema Evolution ===");

// Update schema to be more strict
const strictUserSchema = {
    ...userSchema,
    properties: {
        ...userSchema.properties,
        name: { ...userSchema.properties.name, minLength: 5 }, // Increased minimum
        email: { ...userSchema.properties.email, pattern: /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/ } // Stricter pattern
    }
};

dataManager.registerSchema('strictUser', strictUserSchema);

const existingUser = dataManager.load('user1');
const strictValidation = dataManager.validator.validate(existingUser, 'strictUser');
console.log('Strict validation:', strictValidation);

// Test 7: Complex nested validation
console.log("\n=== Test 7: Complex Nested Validation ===");

const complexSchema = {
    type: 'object',
    required: ['users', 'settings'],
    properties: {
        users: {
            type: 'array',
            minItems: 1,
            items: userSchema
        },
        settings: {
            type: 'object',
            properties: {
                theme: { type: 'string', enum: ['light', 'dark'] },
                notifications: { type: 'boolean' },
                maxUsers: { type: 'number', minimum: 1, maximum: 1000 }
            }
        }
    }
};

dataManager.registerSchema('complex', complexSchema);

const complexData = {
    users: [validUser],
    settings: {
        theme: 'dark',
        notifications: true,
        maxUsers: 100
    }
};

const complexResult = dataManager.save('complexData', complexData, 'complex');
console.log('Complex save result:', complexResult);

console.log("\n=== JSON Schema Validation System Summary ===");
console.log("✓ Comprehensive JSON schema validation");
console.log("✓ Type checking and constraint validation");
console.log("✓ String, number, array, and object validation");
console.log("✓ Required fields and additional properties control");
console.log("✓ Pattern matching and enum validation");
console.log("✓ Nested object and array validation");
console.log("✓ Schema evolution and versioning");
console.log("✓ Integration with data persistence layer");
