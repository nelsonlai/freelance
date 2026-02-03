# Lesson 2: Testing with Jest

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Set up Jest testing framework
- Write unit tests for functions and components
- Use testing utilities and matchers
- Mock external dependencies
- Test asynchronous code
- Implement test-driven development

## 📚 Jest Testing Basics

### Basic Test Structure
```javascript
// math.js
function add(a, b) {
    return a + b;
}

function multiply(a, b) {
    return a * b;
}

module.exports = { add, multiply };

// math.test.js
const { add, multiply } = require('./math');

describe('Math functions', () => {
    test('adds two numbers correctly', () => {
        expect(add(2, 3)).toBe(5);
        expect(add(-1, 1)).toBe(0);
        expect(add(0, 0)).toBe(0);
    });
    
    test('multiplies two numbers correctly', () => {
        expect(multiply(2, 3)).toBe(6);
        expect(multiply(-2, 3)).toBe(-6);
        expect(multiply(0, 5)).toBe(0);
    });
});
```

### Testing React Components
```javascript
// UserCard.jsx
import React from 'react';

function UserCard({ user, onSelect }) {
    return (
        <div className="user-card" onClick={() => onSelect(user)}>
            <h3>{user.name}</h3>
            <p>{user.email}</p>
        </div>
    );
}

export default UserCard;

// UserCard.test.jsx
import React from 'react';
import { render, fireEvent } from '@testing-library/react';
import UserCard from './UserCard';

describe('UserCard', () => {
    const mockUser = {
        id: 1,
        name: 'John Doe',
        email: 'john@example.com'
    };
    
    test('renders user information', () => {
        const { getByText } = render(<UserCard user={mockUser} />);
        
        expect(getByText('John Doe')).toBeInTheDocument();
        expect(getByText('john@example.com')).toBeInTheDocument();
    });
    
    test('calls onSelect when clicked', () => {
        const mockOnSelect = jest.fn();
        const { getByText } = render(
            <UserCard user={mockUser} onSelect={mockOnSelect} />
        );
        
        fireEvent.click(getByText('John Doe'));
        expect(mockOnSelect).toHaveBeenCalledWith(mockUser);
    });
});
```

## 🎯 Practice Exercises

### Exercise 1: API Service Testing
Create comprehensive tests for an API service:

**Solution:**
```javascript
// apiService.js
class ApiService {
    constructor(baseURL) {
        this.baseURL = baseURL;
    }
    
    async get(endpoint) {
        const response = await fetch(`${this.baseURL}${endpoint}`);
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        return response.json();
    }
    
    async post(endpoint, data) {
        const response = await fetch(`${this.baseURL}${endpoint}`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(data)
        });
        
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        return response.json();
    }
}

module.exports = ApiService;

// apiService.test.js
const ApiService = require('./apiService');

// Mock fetch
global.fetch = jest.fn();

describe('ApiService', () => {
    let apiService;
    
    beforeEach(() => {
        apiService = new ApiService('https://api.example.com');
        fetch.mockClear();
    });
    
    describe('GET requests', () => {
        test('successfully fetches data', async () => {
            const mockData = { id: 1, name: 'Test' };
            fetch.mockResolvedValueOnce({
                ok: true,
                json: async () => mockData
            });
            
            const result = await apiService.get('/users/1');
            
            expect(fetch).toHaveBeenCalledWith('https://api.example.com/users/1');
            expect(result).toEqual(mockData);
        });
        
        test('handles HTTP errors', async () => {
            fetch.mockResolvedValueOnce({
                ok: false,
                status: 404
            });
            
            await expect(apiService.get('/users/999')).rejects.toThrow('HTTP error! status: 404');
        });
    });
    
    describe('POST requests', () => {
        test('successfully posts data', async () => {
            const mockData = { name: 'New User' };
            const mockResponse = { id: 2, ...mockData };
            
            fetch.mockResolvedValueOnce({
                ok: true,
                json: async () => mockResponse
            });
            
            const result = await apiService.post('/users', mockData);
            
            expect(fetch).toHaveBeenCalledWith('https://api.example.com/users', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json'
                },
                body: JSON.stringify(mockData)
            });
            expect(result).toEqual(mockResponse);
        });
    });
});
```

## 🎯 Key Takeaways

1. **Jest** provides comprehensive testing framework
2. **Unit tests** verify individual functions
3. **Component tests** verify UI behavior
4. **Mocking** isolates code under test
5. **Test-driven development** improves code quality

---

**Next Lesson**: [Lesson 3: Version Control (Git/GitHub)](./lesson3-git-github.md)
