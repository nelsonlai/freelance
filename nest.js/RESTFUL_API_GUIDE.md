# 📘 Comprehensive RESTful API Guide

## Table of Contents

1. [Introduction to REST](#introduction-to-rest)
2. [REST Principles and Constraints](#rest-principles-and-constraints)
3. [HTTP Methods Deep Dive](#http-methods-deep-dive)
4. [HTTP Status Codes](#http-status-codes)
5. [Resource Naming Conventions](#resource-naming-conventions)
6. [Request and Response Formats](#request-and-response-formats)
7. [RESTful API Design Best Practices](#restful-api-design-best-practices)
8. [Common Patterns and Use Cases](#common-patterns-and-use-cases)
9. [Authentication and Authorization](#authentication-and-authorization)
10. [Error Handling](#error-handling)
11. [Versioning](#versioning)
12. [Pagination and Filtering](#pagination-and-filtering)
13. [Caching Strategies](#caching-strategies)
14. [Common Mistakes to Avoid](#common-mistakes-to-avoid)
15. [Real-World Examples](#real-world-examples)

---

## Introduction to REST

### What is REST?

**REST** stands for **Representational State Transfer**. It is an architectural style for designing networked applications, introduced by Roy Fielding in his 2000 doctoral dissertation.

### Key Concepts

1. **Stateless**: Each request from a client contains all the information needed to process the request
2. **Resource-Based**: Everything is a resource, identified by a URI
3. **Uniform Interface**: Standard HTTP methods are used
4. **Client-Server**: Clear separation between client and server
5. **Cacheable**: Responses can be cached
6. **Layered System**: Architecture can have multiple layers

### Why REST?

- **Simplicity**: Easy to understand and implement
- **Scalability**: Stateless nature allows horizontal scaling
- **Flexibility**: Works with any data format (JSON, XML, etc.)
- **Standard**: Uses standard HTTP methods and status codes
- **Language Agnostic**: Can be implemented in any programming language

---

## REST Principles and Constraints

### 1. Client-Server Architecture

**Principle**: Separation of concerns between client and server.

- **Client**: User interface, handles presentation
- **Server**: Data storage, business logic, handles requests

**Benefits**:
- Independent evolution of client and server
- Portability across multiple platforms
- Scalability improvements

### 2. Stateless Communication

**Principle**: Each request must contain all information needed to process it.

**What this means**:
- No server-side session storage
- Each request is independent
- Server doesn't remember previous requests

**Example**:
```http
# ❌ Bad: Stateless violation
GET /api/users/profile
Cookie: sessionId=abc123

# ✅ Good: Stateless
GET /api/users/profile
Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...
```

### 3. Cacheable Responses

**Principle**: Responses should be cacheable when possible.

**Benefits**:
- Reduces server load
- Improves performance
- Better user experience

**Implementation**:
```http
# Cache for 1 hour
Cache-Control: public, max-age=3600

# Don't cache
Cache-Control: no-cache, no-store, must-revalidate
```

### 4. Uniform Interface

**Principle**: Standard way of interacting with resources.

**Components**:
- **Resource Identification**: URIs identify resources
- **Resource Manipulation**: HTTP methods (GET, POST, PUT, DELETE)
- **Self-Descriptive Messages**: Headers and status codes
- **Hypermedia**: Links to related resources (HATEOAS)

### 5. Layered System

**Principle**: Architecture can have multiple layers (proxies, gateways, load balancers).

**Benefits**:
- Improved scalability
- Security layers
- Load balancing

### 6. Code on Demand (Optional)

**Principle**: Server can send executable code to client (JavaScript, applets).

**Note**: This is rarely used in modern REST APIs.

---

## HTTP Methods Deep Dive

### GET - Retrieve Resources

**Purpose**: Retrieve data from the server.

**Characteristics**:
- **Idempotent**: Yes (same request = same result)
- **Safe**: Yes (doesn't modify server state)
- **Cacheable**: Yes
- **Request Body**: Should not have one
- **Response Body**: Contains the requested resource

**When to Use**:
- Fetching a list of resources
- Fetching a single resource
- Searching/filtering resources

**Examples**:

```http
# Get all users
GET /api/users
Response: 200 OK
[
  { "id": 1, "name": "John", "email": "john@example.com" },
  { "id": 2, "name": "Jane", "email": "jane@example.com" }
]

# Get a specific user
GET /api/users/1
Response: 200 OK
{ "id": 1, "name": "John", "email": "john@example.com" }

# Get with query parameters
GET /api/users?page=1&limit=10&status=active
Response: 200 OK
{
  "data": [...],
  "pagination": { "page": 1, "limit": 10, "total": 100 }
}
```

**Best Practices**:
- Use query parameters for filtering, sorting, pagination
- Return appropriate status codes (200, 404)
- Support pagination for large datasets
- Use proper caching headers

### POST - Create Resources

**Purpose**: Create a new resource.

**Characteristics**:
- **Idempotent**: No (multiple requests = multiple resources)
- **Safe**: No (modifies server state)
- **Cacheable**: Only if freshness information is included
- **Request Body**: Required (resource data)
- **Response Body**: Usually contains created resource

**When to Use**:
- Creating a new resource
- Submitting forms
- Performing actions that create resources

**Examples**:

```http
# Create a new user
POST /api/users
Content-Type: application/json

{
  "name": "Alice",
  "email": "alice@example.com",
  "age": 30
}

Response: 201 Created
Location: /api/users/3
{
  "id": 3,
  "name": "Alice",
  "email": "alice@example.com",
  "age": 30,
  "createdAt": "2024-01-15T10:30:00Z"
}
```

**Best Practices**:
- Return 201 Created status code
- Include Location header with URI of created resource
- Return the created resource in response body
- Validate input data
- Handle duplicate creation attempts

### PUT - Update Entire Resource

**Purpose**: Replace an entire resource with new data.

**Characteristics**:
- **Idempotent**: Yes (same request = same result)
- **Safe**: No (modifies server state)
- **Cacheable**: No
- **Request Body**: Required (complete resource)
- **Response Body**: Usually contains updated resource

**When to Use**:
- Replacing an entire resource
- Updating all fields of a resource

**Examples**:

```http
# Update entire user
PUT /api/users/1
Content-Type: application/json

{
  "name": "John Updated",
  "email": "john.updated@example.com",
  "age": 31
}

Response: 200 OK
{
  "id": 1,
  "name": "John Updated",
  "email": "john.updated@example.com",
  "age": 31,
  "updatedAt": "2024-01-15T11:00:00Z"
}

# Or 204 No Content if not returning body
Response: 204 No Content
```

**Important Notes**:
- PUT replaces the entire resource
- Missing fields should be set to null/default
- If resource doesn't exist, you can create it (upsert behavior)

**Best Practices**:
- Return 200 OK or 204 No Content
- Include updated resource in response (if 200)
- Validate all required fields
- Handle non-existent resources (404 or create)

### PATCH - Partial Update

**Purpose**: Partially update a resource.

**Characteristics**:
- **Idempotent**: Should be (but not always)
- **Safe**: No (modifies server state)
- **Cacheable**: No
- **Request Body**: Required (only fields to update)
- **Response Body**: Usually contains updated resource

**When to Use**:
- Updating specific fields
- Partial modifications

**Examples**:

```http
# Update only the email
PATCH /api/users/1
Content-Type: application/json

{
  "email": "newemail@example.com"
}

Response: 200 OK
{
  "id": 1,
  "name": "John",
  "email": "newemail@example.com",
  "age": 30,
  "updatedAt": "2024-01-15T11:15:00Z"
}
```

**Best Practices**:
- Only update provided fields
- Return 200 OK with updated resource
- Validate updated fields
- Handle non-existent resources (404)

### DELETE - Remove Resources

**Purpose**: Delete a resource.

**Characteristics**:
- **Idempotent**: Yes (deleting twice = same result)
- **Safe**: No (modifies server state)
- **Cacheable**: No
- **Request Body**: Should not have one
- **Response Body**: Usually empty or confirmation

**When to Use**:
- Removing a resource
- Soft deletes (mark as deleted)

**Examples**:

```http
# Delete a user
DELETE /api/users/1

Response: 204 No Content

# Or with confirmation
Response: 200 OK
{
  "message": "User deleted successfully",
  "deletedId": 1
}
```

**Best Practices**:
- Return 204 No Content or 200 OK
- Handle non-existent resources (404 or 204)
- Consider soft deletes vs hard deletes
- Implement proper authorization

### OPTIONS - Preflight Request

**Purpose**: Get allowed HTTP methods and CORS information.

**Characteristics**:
- **Idempotent**: Yes
- **Safe**: Yes
- **Cacheable**: Yes
- **Request Body**: None
- **Response Body**: Usually empty

**When to Use**:
- CORS preflight requests
- Discovering allowed methods

**Examples**:

```http
# CORS preflight
OPTIONS /api/users
Origin: http://localhost:3000
Access-Control-Request-Method: POST
Access-Control-Request-Headers: Content-Type

Response: 204 No Content
Access-Control-Allow-Origin: http://localhost:3000
Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS
Access-Control-Allow-Headers: Content-Type, Authorization
Access-Control-Max-Age: 86400
```

**Best Practices**:
- Return appropriate CORS headers
- List all allowed methods
- Set Access-Control-Max-Age for caching
- Return 204 No Content

### HEAD - Get Headers Only

**Purpose**: Get response headers without body.

**Characteristics**:
- **Idempotent**: Yes
- **Safe**: Yes
- **Cacheable**: Yes
- **Request Body**: None
- **Response Body**: None (only headers)

**When to Use**:
- Check if resource exists
- Get metadata without downloading body
- Check last-modified date

**Examples**:

```http
HEAD /api/users/1

Response: 200 OK
Content-Type: application/json
Content-Length: 156
Last-Modified: Mon, 15 Jan 2024 10:30:00 GMT
ETag: "abc123"
```

---

## HTTP Status Codes

### 2xx Success

#### 200 OK
**Use**: Successful GET, PUT, PATCH requests.

```http
GET /api/users/1
Response: 200 OK
{ "id": 1, "name": "John" }
```

#### 201 Created
**Use**: Successful POST request that created a resource.

```http
POST /api/users
Response: 201 Created
Location: /api/users/2
{ "id": 2, "name": "Jane" }
```

#### 204 No Content
**Use**: Successful request with no response body (DELETE, PUT, PATCH).

```http
DELETE /api/users/1
Response: 204 No Content
```

### 3xx Redirection

#### 301 Moved Permanently
**Use**: Resource has permanently moved.

#### 302 Found (Temporary Redirect)
**Use**: Resource temporarily moved.

### 4xx Client Errors

#### 400 Bad Request
**Use**: Invalid request syntax or parameters.

```http
POST /api/users
{ "name": "" }  # Empty name

Response: 400 Bad Request
{
  "error": "Validation failed",
  "details": {
    "name": "Name cannot be empty"
  }
}
```

#### 401 Unauthorized
**Use**: Authentication required or failed.

```http
GET /api/users/profile
# No Authorization header

Response: 401 Unauthorized
{
  "error": "Authentication required"
}
```

#### 403 Forbidden
**Use**: Authenticated but not authorized.

```http
DELETE /api/admin/users/1
# User is authenticated but not admin

Response: 403 Forbidden
{
  "error": "Insufficient permissions"
}
```

#### 404 Not Found
**Use**: Resource not found.

```http
GET /api/users/999

Response: 404 Not Found
{
  "error": "User with ID 999 not found"
}
```

#### 409 Conflict
**Use**: Resource conflict (e.g., duplicate email).

```http
POST /api/users
{ "email": "existing@example.com" }

Response: 409 Conflict
{
  "error": "User with this email already exists"
}
```

#### 422 Unprocessable Entity
**Use**: Valid syntax but semantic errors.

```http
POST /api/users
{ "age": -5 }  # Invalid age

Response: 422 Unprocessable Entity
{
  "error": "Age must be positive"
}
```

### 5xx Server Errors

#### 500 Internal Server Error
**Use**: Generic server error.

```http
Response: 500 Internal Server Error
{
  "error": "Internal server error",
  "message": "An unexpected error occurred"
}
```

#### 502 Bad Gateway
**Use**: Invalid response from upstream server.

#### 503 Service Unavailable
**Use**: Server temporarily unavailable.

```http
Response: 503 Service Unavailable
Retry-After: 60
{
  "error": "Service temporarily unavailable",
  "retryAfter": 60
}
```

---

## Resource Naming Conventions

### Best Practices

1. **Use Nouns, Not Verbs**
   ```
   ✅ GET /api/users
   ❌ GET /api/getUsers
   ```

2. **Use Plural Nouns**
   ```
   ✅ GET /api/users
   ❌ GET /api/user
   ```

3. **Use Hierarchical Structure**
   ```
   ✅ GET /api/users/1/posts
   ✅ GET /api/users/1/posts/5/comments
   ```

4. **Use Hyphens for Multi-Word Resources**
   ```
   ✅ GET /api/user-profiles
   ❌ GET /api/userProfiles
   ```

5. **Use Lowercase**
   ```
   ✅ GET /api/users
   ❌ GET /api/Users
   ```

6. **Avoid File Extensions**
   ```
   ✅ GET /api/users
   ❌ GET /api/users.json
   ```

### Common Patterns

```
# Collection resources
GET    /api/users              # List all users
POST   /api/users              # Create user
GET    /api/users/1            # Get user 1
PUT    /api/users/1            # Update user 1
DELETE /api/users/1            # Delete user 1

# Sub-resources
GET    /api/users/1/posts      # Get posts by user 1
POST   /api/users/1/posts      # Create post for user 1

# Actions (use POST for non-CRUD operations)
POST   /api/users/1/activate  # Activate user
POST   /api/users/1/deactivate # Deactivate user
POST   /api/orders/1/cancel    # Cancel order

# Query parameters for filtering
GET    /api/users?status=active&role=admin
GET    /api/users?page=1&limit=10
GET    /api/users?sort=name&order=asc
```

---

## Request and Response Formats

### Request Headers

**Common Headers**:

```http
Content-Type: application/json
Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...
Accept: application/json
Accept-Language: en-US
If-None-Match: "abc123"
If-Modified-Since: Mon, 15 Jan 2024 10:30:00 GMT
```

### Request Body (JSON Example)

```json
{
  "name": "John Doe",
  "email": "john@example.com",
  "age": 30,
  "address": {
    "street": "123 Main St",
    "city": "New York",
    "zipCode": "10001"
  }
}
```

### Response Format

**Standard Success Response**:

```json
{
  "success": true,
  "data": {
    "id": 1,
    "name": "John Doe",
    "email": "john@example.com"
  },
  "message": "User retrieved successfully"
}
```

**Paginated Response**:

```json
{
  "success": true,
  "data": [
    { "id": 1, "name": "John" },
    { "id": 2, "name": "Jane" }
  ],
  "pagination": {
    "page": 1,
    "limit": 10,
    "total": 100,
    "totalPages": 10
  }
}
```

**Error Response**:

```json
{
  "success": false,
  "error": {
    "code": "VALIDATION_ERROR",
    "message": "Validation failed",
    "details": [
      {
        "field": "email",
        "message": "Email is required"
      }
    ]
  },
  "timestamp": "2024-01-15T10:30:00Z"
}
```

---

## RESTful API Design Best Practices

### 1. Use Proper HTTP Methods

```http
✅ GET    /api/users        # Retrieve
✅ POST   /api/users        # Create
✅ PUT    /api/users/1      # Update entire
✅ PATCH  /api/users/1      # Partial update
✅ DELETE /api/users/1      # Delete
```

### 2. Use Appropriate Status Codes

```http
✅ 200 OK           # Success
✅ 201 Created      # Resource created
✅ 204 No Content   # Success, no body
✅ 400 Bad Request  # Client error
✅ 401 Unauthorized # Auth required
✅ 404 Not Found    # Resource not found
✅ 500 Server Error # Server error
```

### 3. Consistent Response Format

```json
// Success
{
  "success": true,
  "data": {...}
}

// Error
{
  "success": false,
  "error": {...}
}
```

### 4. Use Query Parameters for Filtering

```http
GET /api/users?status=active&role=admin&page=1&limit=10
```

### 5. Implement Pagination

```json
{
  "data": [...],
  "pagination": {
    "page": 1,
    "limit": 10,
    "total": 100,
    "totalPages": 10,
    "hasNext": true,
    "hasPrev": false
  }
}
```

### 6. Version Your API

```http
GET /api/v1/users
GET /api/v2/users
```

### 7. Use HTTPS

Always use HTTPS in production for security.

### 8. Implement Rate Limiting

```http
X-RateLimit-Limit: 100
X-RateLimit-Remaining: 95
X-RateLimit-Reset: 1642248000
```

### 9. Provide Clear Error Messages

```json
{
  "error": {
    "code": "USER_NOT_FOUND",
    "message": "User with ID 123 not found",
    "details": "The requested user does not exist or has been deleted"
  }
}
```

### 10. Support Content Negotiation

```http
Accept: application/json
Accept: application/xml
```

---

## Common Patterns and Use Cases

### 1. CRUD Operations

```http
# Create
POST   /api/users
Body: { "name": "John", "email": "john@example.com" }

# Read
GET    /api/users
GET    /api/users/1

# Update
PUT    /api/users/1
Body: { "name": "John Updated", "email": "john@example.com" }

PATCH  /api/users/1
Body: { "name": "John Updated" }

# Delete
DELETE /api/users/1
```

### 2. Filtering and Searching

```http
# Filter by status
GET /api/users?status=active

# Search by name
GET /api/users?search=john

# Multiple filters
GET /api/users?status=active&role=admin&age_min=25&age_max=50
```

### 3. Sorting

```http
# Sort by name ascending
GET /api/users?sort=name&order=asc

# Sort by created date descending
GET /api/users?sort=createdAt&order=desc

# Multiple sort fields
GET /api/users?sort=name,createdAt&order=asc,desc
```

### 4. Pagination

```http
# Page-based
GET /api/users?page=1&limit=10

# Cursor-based
GET /api/users?cursor=abc123&limit=10
```

### 5. Nested Resources

```http
# Get user's posts
GET /api/users/1/posts

# Create post for user
POST /api/users/1/posts
Body: { "title": "My Post", "content": "..." }

# Get comments for a post
GET /api/users/1/posts/5/comments
```

### 6. Bulk Operations

```http
# Bulk create
POST /api/users/bulk
Body: [
  { "name": "User 1", "email": "user1@example.com" },
  { "name": "User 2", "email": "user2@example.com" }
]

# Bulk update
PUT /api/users/bulk
Body: {
  "ids": [1, 2, 3],
  "data": { "status": "inactive" }
}

# Bulk delete
DELETE /api/users/bulk
Body: { "ids": [1, 2, 3] }
```

---

## Authentication and Authorization

### Authentication Methods

#### 1. Bearer Token (JWT)

```http
GET /api/users/profile
Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...
```

#### 2. API Key

```http
GET /api/users
X-API-Key: your-api-key-here
```

#### 3. Basic Authentication

```http
GET /api/users
Authorization: Basic base64(username:password)
```

### Authorization Levels

```http
# Public endpoint
GET /api/public/posts

# Authenticated endpoint
GET /api/users/profile
Authorization: Bearer token

# Admin only endpoint
DELETE /api/admin/users/1
Authorization: Bearer admin-token
```

---

## Error Handling

### Standard Error Format

```json
{
  "success": false,
  "error": {
    "code": "ERROR_CODE",
    "message": "Human-readable message",
    "details": {
      "field": "Additional information"
    }
  },
  "timestamp": "2024-01-15T10:30:00Z",
  "path": "/api/users/999"
}
```

### Common Error Codes

- `VALIDATION_ERROR` - Input validation failed
- `NOT_FOUND` - Resource not found
- `UNAUTHORIZED` - Authentication required
- `FORBIDDEN` - Insufficient permissions
- `CONFLICT` - Resource conflict
- `RATE_LIMIT_EXCEEDED` - Too many requests
- `INTERNAL_ERROR` - Server error

### Error Response Examples

```http
# 400 Bad Request
{
  "success": false,
  "error": {
    "code": "VALIDATION_ERROR",
    "message": "Validation failed",
    "details": [
      {
        "field": "email",
        "message": "Email is required"
      },
      {
        "field": "age",
        "message": "Age must be a positive number"
      }
    ]
  }
}

# 404 Not Found
{
  "success": false,
  "error": {
    "code": "NOT_FOUND",
    "message": "User with ID 999 not found"
  }
}

# 401 Unauthorized
{
  "success": false,
  "error": {
    "code": "UNAUTHORIZED",
    "message": "Authentication required. Please provide a valid token."
  }
}
```

---

## Versioning

### URL Versioning (Recommended)

```http
GET /api/v1/users
GET /api/v2/users
```

### Header Versioning

```http
GET /api/users
Accept: application/vnd.api+json;version=2
```

### Query Parameter Versioning

```http
GET /api/users?version=2
```

### Best Practices

- Start with v1 from the beginning
- Maintain backward compatibility when possible
- Deprecate old versions gradually
- Document version changes

---

## Pagination and Filtering

### Page-Based Pagination

```http
GET /api/users?page=1&limit=10
```

**Response**:
```json
{
  "data": [...],
  "pagination": {
    "page": 1,
    "limit": 10,
    "total": 100,
    "totalPages": 10,
    "hasNext": true,
    "hasPrev": false
  }
}
```

### Cursor-Based Pagination

```http
GET /api/users?cursor=abc123&limit=10
```

**Response**:
```json
{
  "data": [...],
  "pagination": {
    "cursor": "def456",
    "limit": 10,
    "hasNext": true
  }
}
```

### Filtering

```http
# Single filter
GET /api/users?status=active

# Multiple filters
GET /api/users?status=active&role=admin&age_min=25

# Date range
GET /api/orders?start_date=2024-01-01&end_date=2024-01-31
```

### Sorting

```http
# Single field
GET /api/users?sort=name&order=asc

# Multiple fields
GET /api/users?sort=name,createdAt&order=asc,desc
```

---

## Caching Strategies

### HTTP Caching Headers

```http
# Cache for 1 hour
Cache-Control: public, max-age=3600

# Don't cache
Cache-Control: no-cache, no-store, must-revalidate

# Conditional requests
ETag: "abc123"
Last-Modified: Mon, 15 Jan 2024 10:30:00 GMT
```

### ETag Usage

```http
# First request
GET /api/users/1
ETag: "abc123"

# Conditional request
GET /api/users/1
If-None-Match: "abc123"
Response: 304 Not Modified
```

### Cache-Control Directives

- `public` - Can be cached by any cache
- `private` - Only browser can cache
- `no-cache` - Must revalidate before use
- `no-store` - Don't cache at all
- `max-age=3600` - Cache for 3600 seconds
- `must-revalidate` - Must check with server when expired

---

## Common Mistakes to Avoid

### 1. Using Wrong HTTP Methods

```http
❌ GET /api/users/create
✅ POST /api/users

❌ POST /api/users/1/delete
✅ DELETE /api/users/1
```

### 2. Not Using Proper Status Codes

```http
❌ POST /api/users → 200 OK (should be 201)
✅ POST /api/users → 201 Created

❌ DELETE /api/users/1 → 200 OK (should be 204)
✅ DELETE /api/users/1 → 204 No Content
```

### 3. Inconsistent Response Format

```http
❌ GET /api/users → { "users": [...] }
   GET /api/posts → { "data": [...] }

✅ GET /api/users → { "data": [...] }
   GET /api/posts → { "data": [...] }
```

### 4. Not Handling Errors Properly

```http
❌ GET /api/users/999 → 200 OK { "error": "Not found" }
✅ GET /api/users/999 → 404 Not Found { "error": "Not found" }
```

### 5. Exposing Internal Details

```http
❌ {
  "error": "Database connection failed at line 123 in UserService.java"
}

✅ {
  "error": "Internal server error. Please try again later."
}
```

### 6. Not Implementing Pagination

```http
❌ GET /api/users → Returns 10,000 records
✅ GET /api/users?page=1&limit=10 → Returns 10 records
```

### 7. Using Verbs in URLs

```http
❌ GET /api/getUsers
❌ POST /api/createUser
❌ DELETE /api/removeUser

✅ GET /api/users
✅ POST /api/users
✅ DELETE /api/users/1
```

### 8. Not Versioning APIs

```http
❌ GET /api/users (breaking changes affect all clients)
✅ GET /api/v1/users (safe to change v2)
```

---

## Real-World Examples

### Example 1: User Management API

```http
# Get all users with pagination
GET /api/v1/users?page=1&limit=10&status=active
Response: 200 OK
{
  "success": true,
  "data": [
    {
      "id": 1,
      "name": "John Doe",
      "email": "john@example.com",
      "status": "active",
      "createdAt": "2024-01-15T10:30:00Z"
    }
  ],
  "pagination": {
    "page": 1,
    "limit": 10,
    "total": 100,
    "totalPages": 10
  }
}

# Create user
POST /api/v1/users
Content-Type: application/json
{
  "name": "Jane Smith",
  "email": "jane@example.com",
  "password": "secure123"
}
Response: 201 Created
Location: /api/v1/users/2
{
  "success": true,
  "data": {
    "id": 2,
    "name": "Jane Smith",
    "email": "jane@example.com",
    "status": "active",
    "createdAt": "2024-01-15T11:00:00Z"
  }
}

# Update user
PATCH /api/v1/users/2
Content-Type: application/json
{
  "name": "Jane Doe"
}
Response: 200 OK
{
  "success": true,
  "data": {
    "id": 2,
    "name": "Jane Doe",
    "email": "jane@example.com",
    "updatedAt": "2024-01-15T11:15:00Z"
  }
}

# Delete user
DELETE /api/v1/users/2
Response: 204 No Content
```

### Example 2: E-Commerce API

```http
# Get products with filters
GET /api/v1/products?category=electronics&min_price=100&max_price=1000&sort=price&order=asc
Response: 200 OK
{
  "success": true,
  "data": [...],
  "filters": {
    "category": "electronics",
    "priceRange": { "min": 100, "max": 1000 }
  }
}

# Create order
POST /api/v1/orders
Authorization: Bearer token
Content-Type: application/json
{
  "items": [
    { "productId": 1, "quantity": 2 },
    { "productId": 3, "quantity": 1 }
  ],
  "shippingAddress": {
    "street": "123 Main St",
    "city": "New York",
    "zipCode": "10001"
  }
}
Response: 201 Created
{
  "success": true,
  "data": {
    "id": 123,
    "status": "pending",
    "total": 299.99,
    "createdAt": "2024-01-15T12:00:00Z"
  }
}

# Get user's orders
GET /api/v1/users/1/orders
Authorization: Bearer token
Response: 200 OK
{
  "success": true,
  "data": [...]
}
```

### Example 3: Blog API

```http
# Get posts with pagination
GET /api/v1/posts?page=1&limit=5&tags=javascript,nodejs
Response: 200 OK
{
  "success": true,
  "data": [...],
  "pagination": {...}
}

# Create post
POST /api/v1/posts
Authorization: Bearer token
Content-Type: application/json
{
  "title": "RESTful API Best Practices",
  "content": "...",
  "tags": ["api", "rest", "best-practices"],
  "published": false
}
Response: 201 Created
{
  "success": true,
  "data": {
    "id": 42,
    "title": "RESTful API Best Practices",
    "slug": "restful-api-best-practices",
    "author": { "id": 1, "name": "John Doe" },
    "createdAt": "2024-01-15T13:00:00Z"
  }
}

# Get post comments
GET /api/v1/posts/42/comments
Response: 200 OK
{
  "success": true,
  "data": [
    {
      "id": 1,
      "content": "Great article!",
      "author": { "id": 2, "name": "Jane Smith" },
      "createdAt": "2024-01-15T14:00:00Z"
    }
  ]
}
```

---

## Summary

### Key Takeaways

1. **REST is an architectural style**, not a protocol
2. **Use proper HTTP methods** for their intended purposes
3. **Return appropriate status codes** for different scenarios
4. **Follow naming conventions** (nouns, plural, lowercase)
5. **Implement proper error handling** with clear messages
6. **Version your APIs** from the start
7. **Use pagination** for large datasets
8. **Implement caching** where appropriate
9. **Keep responses consistent** across all endpoints
10. **Document your API** thoroughly

### REST Principles Checklist

- ✅ Client-Server architecture
- ✅ Stateless communication
- ✅ Cacheable responses
- ✅ Uniform interface
- ✅ Layered system
- ⚪ Code on demand (optional)

### HTTP Methods Summary

| Method | Idempotent | Safe | Use Case |
|--------|-----------|------|----------|
| GET | Yes | Yes | Retrieve resources |
| POST | No | No | Create resources |
| PUT | Yes | No | Replace entire resource |
| PATCH | Should be | No | Partial update |
| DELETE | Yes | No | Remove resource |
| OPTIONS | Yes | Yes | CORS preflight |
| HEAD | Yes | Yes | Get headers only |

---

## Additional Resources

- [REST API Tutorial](https://restfulapi.net/)
- [HTTP Status Codes](https://httpstatuses.com/)
- [JSON API Specification](https://jsonapi.org/)
- [OpenAPI Specification](https://swagger.io/specification/)
- [RESTful Web Services](https://www.ics.uci.edu/~fielding/pubs/dissertation/rest_arch_style.htm)

---

**Remember**: REST is about simplicity, consistency, and following web standards. Keep your APIs intuitive, well-documented, and easy to use!

