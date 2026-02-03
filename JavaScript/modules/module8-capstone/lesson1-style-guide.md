# Lesson 1: JavaScript Style Guide & Best Practices

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Follow JavaScript style guides and conventions
- Write clean, readable, and maintainable code
- Use ESLint for code linting
- Implement consistent naming conventions
- Follow best practices for functions and variables
- Use modern JavaScript patterns effectively

## 📚 Style Guide Essentials

### Naming Conventions
```javascript
// Variables and functions - camelCase
const userName = 'john_doe';
const getUserData = () => {};

// Constants - UPPER_SNAKE_CASE
const API_BASE_URL = 'https://api.example.com';
const MAX_RETRY_ATTEMPTS = 3;

// Classes - PascalCase
class UserManager {}
class ApiClient {}

// Private properties - underscore prefix
class User {
    constructor(name) {
        this.name = name;
        this._internalId = Date.now();
    }
}
```

### Code Organization
```javascript
// Import order: external libraries, internal modules, relative imports
import React from 'react';
import { useState, useEffect } from 'react';
import axios from 'axios';

import { apiClient } from './utils/api';
import { formatDate } from './utils/helpers';

import UserCard from './components/UserCard';
import './styles/App.css';

// Function organization
function App() {
    // 1. State declarations
    const [users, setUsers] = useState([]);
    const [loading, setLoading] = useState(false);
    
    // 2. Effect hooks
    useEffect(() => {
        fetchUsers();
    }, []);
    
    // 3. Event handlers
    const handleUserSelect = (user) => {
        setSelectedUser(user);
    };
    
    // 4. Helper functions
    const fetchUsers = async () => {
        setLoading(true);
        try {
            const response = await apiClient.get('/users');
            setUsers(response.data);
        } catch (error) {
            console.error('Error fetching users:', error);
        } finally {
            setLoading(false);
        }
    };
    
    // 5. Render
    return (
        <div className="app">
            {loading ? <div>Loading...</div> : <UserList users={users} />}
        </div>
    );
}
```

## 🎯 Practice Exercises

### Exercise 1: Code Refactoring
Refactor poorly written code following best practices:

**Solution:**
```javascript
// Before (poor code)
function processData(d) {
    let r = [];
    for (let i = 0; i < d.length; i++) {
        if (d[i].active) {
            r.push({
                id: d[i].id,
                name: d[i].name.toUpperCase(),
                email: d[i].email.toLowerCase()
            });
        }
    }
    return r;
}

// After (clean code)
function processActiveUsers(users) {
    return users
        .filter(user => user.active)
        .map(user => ({
            id: user.id,
            name: user.name.toUpperCase(),
            email: user.email.toLowerCase()
        }));
}

// Before (poor code)
const x = 10;
const y = 20;
const z = x + y;

// After (clean code)
const WIDTH = 10;
const HEIGHT = 20;
const AREA = WIDTH * HEIGHT;
```

### Exercise 2: ESLint Configuration
Create a comprehensive ESLint configuration:

**Solution:**
```javascript
// .eslintrc.js
module.exports = {
    env: {
        browser: true,
        es2021: true,
        node: true,
        jest: true
    },
    extends: [
        'eslint:recommended',
        '@typescript-eslint/recommended',
        'react/recommended',
        'react-hooks/recommended'
    ],
    parser: '@typescript-eslint/parser',
    parserOptions: {
        ecmaFeatures: {
            jsx: true
        },
        ecmaVersion: 12,
        sourceType: 'module'
    },
    plugins: [
        'react',
        'react-hooks',
        '@typescript-eslint'
    ],
    rules: {
        // Code quality
        'no-console': 'warn',
        'no-debugger': 'error',
        'no-unused-vars': 'error',
        'no-var': 'error',
        'prefer-const': 'error',
        
        // Style
        'indent': ['error', 4],
        'quotes': ['error', 'single'],
        'semi': ['error', 'always'],
        'comma-dangle': ['error', 'never'],
        
        // React specific
        'react/prop-types': 'off',
        'react/react-in-jsx-scope': 'off',
        'react-hooks/rules-of-hooks': 'error',
        'react-hooks/exhaustive-deps': 'warn'
    },
    settings: {
        react: {
            version: 'detect'
        }
    }
};
```

## 🎯 Key Takeaways

1. **Consistent naming** improves code readability
2. **Code organization** follows logical structure
3. **ESLint** enforces coding standards
4. **Comments** explain why, not what
5. **Modern patterns** use ES6+ features

---

**Next Lesson**: [Lesson 2: Testing with Jest](./lesson2-testing.md)
