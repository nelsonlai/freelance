# Lesson 3: APIs & REST Concepts

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Understand what APIs are and how they work
- Learn REST principles and HTTP methods
- Build query parameters for API requests
- Understand API endpoints and URL structure
- Handle API responses and error codes
- Design API-friendly applications

## 📚 What is an API?

**API (Application Programming Interface)** is a way for different software applications to communicate with each other.

### REST Principles
- **Representational State Transfer**
- **Stateless** - each request is independent
- **Resource-based** - everything is a resource
- **HTTP methods** - GET, POST, PUT, DELETE

### HTTP Methods
```javascript
// GET - Retrieve data
fetch('/api/users')

// POST - Create new data
fetch('/api/users', { method: 'POST', body: data })

// PUT - Update existing data
fetch('/api/users/1', { method: 'PUT', body: data })

// DELETE - Remove data
fetch('/api/users/1', { method: 'DELETE' })
```

## 🔗 Building Query Parameters

```javascript
function buildQueryString(params) {
    const queryString = new URLSearchParams(params).toString();
    return queryString;
}

// Usage
const params = {    // https://example.com/xyz?page=1&limit=10&search=javascript
    page: 1,
    limit: 10,
    search: 'javascript'
};

const queryString = buildQueryString(params);
// const querySting = new URLSearchParams(params).toString();
const url = `https://api.example.com/posts?${queryString}`;
```

## 🎯 Practice Exercises

### Exercise 1: API Endpoint Builder
Create a function that builds API endpoints:

**Solution:**
```javascript
function buildApiEndpoint(baseUrl, resource, id = null, queryParams = {}) {
    let endpoint = `${baseUrl}/${resource}`;
    
    if (id) {
        endpoint += `/${id}`;
    }
    
    if (Object.keys(queryParams).length > 0) {
        const queryString = new URLSearchParams(queryParams).toString();
        endpoint += `?${queryString}`;
    }
    
    return endpoint;
}

// Usage
const baseUrl = 'https://api.example.com';
console.log(buildApiEndpoint(baseUrl, 'users')); // https://api.example.com/users
console.log(buildApiEndpoint(baseUrl, 'users', 1)); // https://api.example.com/users/1
console.log(buildApiEndpoint(baseUrl, 'posts', null, { page: 1, limit: 10 }));
```

## 🎯 Key Takeaways

1. **APIs** enable communication between applications
2. **REST** follows specific design principles
3. **HTTP methods** have specific purposes
4. **Query parameters** filter and paginate data
5. **Error codes** indicate request status

---

**Next Lesson**: [Lesson 4: DOM Advanced](./lesson4-dom-advanced.md)
