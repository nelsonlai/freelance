# Lesson 2: Default Parameters & Optional Chaining

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Use default parameters in functions
- Implement optional chaining for safe property access
- Use nullish coalescing operator
- Handle undefined/null values gracefully
- Write more robust and defensive code

## 📚 Default Parameters

### Basic Default Parameters
```javascript
// Old way
function greet(name) {
    name = name || 'Guest';
    return `Hello, ${name}!`;
}

// New way with default parameters
function greet(name = 'Guest') {
    return `Hello, ${name}!`;
}

// Multiple default parameters
function createUser(name = 'Anonymous', age = 18, isActive = true) {
    return { name, age, isActive };
}
```

### Default Parameters with Expressions
```javascript
function createId(prefix = 'user', timestamp = Date.now()) {
    return `${prefix}_${timestamp}`;
}

function calculateTotal(items = [], taxRate = 0.1) {
    const subtotal = items.reduce((sum, item) => sum + item.price, 0);
    return subtotal * (1 + taxRate);
}
```

## 🔗 Optional Chaining

### Safe Property Access
```javascript
const user = {
    name: 'Alice',
    address: {
        street: '123 Main St',
        city: 'New York'
    }
};

// Old way - verbose and error-prone
let city = null;
if (user && user.address && user.address.city) {
    city = user.address.city;
}

// New way with optional chaining
const city = user?.address?.city;
const street = user?.address?.street;
const country = user?.address?.country; // undefined, no error
```

### Optional Chaining with Methods
```javascript
const user = {
    name: 'Alice',
    getProfile() {
        return { bio: 'Software developer' };
    }
};

// Safe method calls
const bio = user?.getProfile?.()?.bio;
const nonExistent = user?.getData?.()?.info; // undefined, no error
```

### Optional Chaining with Arrays
```javascript
const users = [
    { name: 'Alice', hobbies: ['reading', 'coding'] },
    { name: 'Bob', hobbies: null }
];

// Safe array access
const firstHobby = users?.[0]?.hobbies?.[0]; // 'reading'
const secondHobby = users?.[1]?.hobbies?.[0]; // undefined, no error
```

## ❓ Nullish Coalescing

### Handling Null/Undefined Values
```javascript
// Old way
const username = user.name || 'Guest';
const count = items.length || 0;

// Problem: falsy values (0, '', false) are replaced
const score = user.score || 0; // If score is 0, it becomes 0

// New way with nullish coalescing
const username = user.name ?? 'Guest';
const count = items.length ?? 0;
const score = user.score ?? 0; // Only replaces null/undefined, not 0
```

### Combining with Optional Chaining
```javascript
const user = {
    name: 'Alice',
    preferences: {
        theme: 'dark',
        notifications: false
    }
};

// Safe access with fallbacks
const theme = user?.preferences?.theme ?? 'light';
const notifications = user?.preferences?.notifications ?? true;
const language = user?.preferences?.language ?? 'en';
```

## 🎯 Practice Exercises

### Exercise 1: API Response Handler
Create a function that safely processes API responses:

**Solution:**
```javascript
function processApiResponse(response) {
    const data = response?.data ?? {};
    const users = data?.users ?? [];
    const total = data?.pagination?.total ?? 0;
    
    return {
        users: users.map(user => ({
            id: user?.id ?? 'unknown',
            name: user?.name ?? 'Anonymous',
            email: user?.email ?? 'no-email@example.com',
            isActive: user?.status === 'active'
        })),
        total,
        hasMore: data?.pagination?.hasMore ?? false
    };
}

// Usage
const apiResponse = {
    data: {
        users: [
            { id: 1, name: 'Alice', email: 'alice@example.com', status: 'active' },
            { id: 2, name: 'Bob', status: 'inactive' }
        ],
        pagination: { total: 2, hasMore: false }
    }
};

console.log(processApiResponse(apiResponse));
```

### Exercise 2: Configuration Builder
Create a configuration object with safe defaults:

**Solution:**
```javascript
function createConfig(options = {}) {
    return {
        apiUrl: options?.api?.url ?? 'https://api.example.com',
        timeout: options?.api?.timeout ?? 5000,
        retries: options?.api?.retries ?? 3,
        features: {
            darkMode: options?.features?.darkMode ?? false,
            notifications: options?.features?.notifications ?? true,
            analytics: options?.features?.analytics ?? false
        },
        user: {
            theme: options?.user?.theme ?? 'light',
            language: options?.user?.language ?? 'en',
            timezone: options?.user?.timezone ?? 'UTC'
        }
    };
}

// Usage
const config1 = createConfig();
const config2 = createConfig({
    api: { url: 'https://custom-api.com', timeout: 10000 },
    features: { darkMode: true },
    user: { theme: 'dark', language: 'es' }
});

console.log(config1);
console.log(config2);
```

## 🎯 Key Takeaways

1. **Default parameters** provide fallback values
2. **Optional chaining** prevents property access errors
3. **Nullish coalescing** handles null/undefined specifically
4. **Combine features** for robust error handling
5. **Defensive programming** makes code more reliable

## 🚀 Next Steps

Excellent! You now understand default parameters and optional chaining. In the next lesson, we'll learn about:

- **Advanced Promise patterns** - Promise.allSettled, Promise.any
- **Async/await best practices** - error handling, parallel execution
- **Promise composition** - chaining and combining promises

---

**Next Lesson**: [Lesson 3: Promises & Async/Await Patterns](./lesson3-promises-async.md)
