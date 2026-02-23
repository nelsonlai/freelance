# Full Stack Development & RESTful API

## Comprehensive Teaching Materials

---

## Table of Contents

1. [Introduction to Full Stack Development](#1-introduction-to-full-stack-development)
2. [Client-Server Architecture](#2-client-server-architecture)
3. [Understanding RESTful APIs](#3-understanding-restful-apis)
4. [HTTP Fundamentals](#4-http-fundamentals)
5. [REST API Design Principles](#5-rest-api-design-principles)
6. [Request &amp; Response Patterns](#6-request--response-patterns)
7. [Authentication &amp; Security](#7-authentication--security)
8. [Best Practices &amp; Common Patterns](#8-best-practices--common-patterns)
9. [Deployment &amp; DevOps Overview](#9-deployment--devops-overview)

---

## 1. Introduction to Full Stack Development

### 1.1 What is Full Stack?

**Full stack development** refers to building and maintaining both the **frontend** (client-facing) and **backend** (server-side) portions of a web application, plus the infrastructure that connects them.

A full stack developer works across all layers:

| Layer                   | Responsibility                                       | Common Technologies                                                   |
| ----------------------- | ---------------------------------------------------- | --------------------------------------------------------------------- |
| **Frontend**      | User interface, user experience, client-side logic   | HTML5, CSS, JavaScript, React, Vue, Angular                           |
| **Backend**       | Business logic, API, authentication, data processing | Node.js, Python (Flask/Django), Ruby on Rails, Java (Spring Boot), Go |
| **Database**      | Data persistence, queries, relationships             | PostgreSQL, MongoDB, MySQL, SQLite                                    |
| **DevOps/Deploy** | Hosting, CI/CD, monitoring                           | AWS, Vercel, Netlify, Docker, GitHub Actions                          |

### 1.2 Why Full Stack?

- **End-to-end understanding** — See how data flows from database to user
- **Flexibility** — Work on any part of the system
- **Career value** — Broad, in-demand skill set
- **Rapid prototyping** — Build complete products independently or in small teams

### 1.3 The Full Stack Flow

```
User Action → Frontend → HTTP Request → Backend API → Database
                ↑                                              │
                └────────── HTTP Response ←── JSON/HTML ←──────┘
```

---

## 2. Client-Server Architecture

### 2.1 Core Concept

The web operates on a **client-server model**:

- **Client** — Browser or app that requests resources (HTML, JSON, images)
- **Server** — Machine that hosts the application and responds to requests
- **Protocol** — HTTP/HTTPS defines how requests and responses are formatted

### 2.2 Request-Response Cycle

1. User performs an action (click, submit form, load page)
2. Client sends an HTTP request to the server
3. Server processes the request (query DB, run logic)
4. Server sends an HTTP response back
5. Client renders or uses the response

### 2.3 Stateless vs Stateful

| Model               | Description                                                | Example                                        |
| ------------------- | ---------------------------------------------------------- | ---------------------------------------------- |
| **Stateless** | Each request is independent; server does not store session | REST APIs, most modern backends                |
| **Stateful**  | Server tracks session/state between requests               | Traditional server-rendered apps with sessions |

REST APIs are typically **stateless**. Any session or user context is sent with each request (e.g., via tokens).

---

## 3. Understanding RESTful APIs

### 3.1 What is REST?

**REST** (Representational State Transfer) is an architectural style for designing networked applications. It uses HTTP as the communication protocol and treats everything as **resources** identified by **URLs**.

### 3.2 Key Principles of REST

1. **Stateless** — No client context stored on the server between requests
2. **Resource-based** — Everything is a resource (users, products, orders) with a unique URL
3. **HTTP verbs** — Use standard HTTP methods to indicate the action
4. **Representation** — Resources can be represented in different formats (JSON, XML, HTML)
5. **Uniform interface** — Consistent, predictable API design

### 3.3 Resources and URLs

Resources are nouns, not verbs. Use plural form for collections:

| Resource      | URL                      | Description          |
| ------------- | ------------------------ | -------------------- |
| Users         | `/api/users`           | Collection of users  |
| Single user   | `/api/users/42`        | User with ID 42      |
| Orders        | `/api/orders`          | Collection of orders |
| User's orders | `/api/users/42/orders` | Nested resource      |

### 3.4 HTTP Methods (Verbs)

| Method           | Action                | Idempotent* | Example                         |
| ---------------- | --------------------- | ----------- | ------------------------------- |
| **GET**    | Read/retrieve         | Yes         | Get list of users, get one user |
| **POST**   | Create                | No          | Create new user                 |
| **PUT**    | Replace (full update) | Yes         | Replace entire user resource    |
| **PATCH**  | Partial update        | Yes         | Update specific fields of user  |
| **DELETE** | Remove                | Yes         | Delete user                     |

*Idempotent: Multiple identical requests have the same effect as one request.

---

## 4. HTTP Fundamentals

### 4.1 HTTP Request Structure

```
METHOD /path?query=value HTTP/1.1
Host: api.example.com
Content-Type: application/json
Authorization: Bearer <token>

{ "body": "data" }
```

**Components:**

- **Request line** — Method, path, HTTP version
- **Headers** — Metadata (content type, auth, etc.)
- **Body** — Optional payload (typically for POST, PUT, PATCH)

### 4.2 HTTP Response Structure

```
HTTP/1.1 200 OK
Content-Type: application/json
Cache-Control: no-cache

{ "id": 1, "name": "John" }
```

**Components:**

- **Status line** — HTTP version, status code, status text
- **Headers** — Metadata
- **Body** — Response data

### 4.3 HTTP Status Codes

| Code Range    | Category     | Common Codes                                                        |
| ------------- | ------------ | ------------------------------------------------------------------- |
| **2xx** | Success      | 200 OK, 201 Created, 204 No Content                                 |
| **3xx** | Redirection  | 301 Moved Permanently, 302 Found, 304 Not Modified                  |
| **4xx** | Client Error | 400 Bad Request, 401 Unauthorized, 403 Forbidden, 404 Not Found     |
| **5xx** | Server Error | 500 Internal Server Error, 502 Bad Gateway, 503 Service Unavailable |

### 4.4 Common Status Codes Explained

| Code | Meaning               | When to Use                           |
| ---- | --------------------- | ------------------------------------- |
| 200  | OK                    | Successful GET, PUT, PATCH            |
| 201  | Created               | Successful POST (resource created)    |
| 204  | No Content            | Successful DELETE (nothing to return) |
| 400  | Bad Request           | Invalid input, malformed JSON         |
| 401  | Unauthorized          | Missing or invalid authentication     |
| 403  | Forbidden             | Authenticated but not allowed         |
| 404  | Not Found             | Resource does not exist               |
| 422  | Unprocessable Entity  | Validation failed                     |
| 500  | Internal Server Error | Unexpected server error               |

---

## 5. REST API Design Principles

### 5.1 Use Nouns, Not Verbs

| ❌ Avoid               | ✅ Prefer                |
| ---------------------- | ------------------------ |
| `/api/getUsers`      | `/api/users`           |
| `/api/createUser`    | `POST /api/users`      |
| `/api/deleteUser/42` | `DELETE /api/users/42` |

### 5.2 Use Plural for Collections

| ❌ Avoid           | ✅ Prefer           |
| ------------------ | ------------------- |
| `/api/user`      | `/api/users`      |
| `/api/product/1` | `/api/products/1` |

### 5.3 Nesting for Relationships

```
GET  /api/users/42/orders      → Orders belonging to user 42
GET  /api/users/42/orders/7    → Order 7 for user 42
POST /api/users/42/orders      → Create order for user 42
```

### 5.4 Use Query Parameters for Filtering & Pagination

```
GET /api/users?role=admin&page=2&limit=10
GET /api/products?sort=price&order=asc
GET /api/orders?status=pending
```

### 5.5 API Versioning

Include version in the path or header:

```
/api/v1/users
/api/v2/users
```

### 5.6 Consistent Response Format

**Success:**

```json
{
  "success": true,
  "data": { "id": 1, "name": "John" }
}
```

**Error:**

```json
{
  "success": false,
  "error": {
    "code": "VALIDATION_ERROR",
    "message": "Email is required",
    "details": { "field": "email" }
  }
}
```

---

## 6. Request & Response Patterns

### 6.1 GET — List Resources

**Request:**

```
GET /api/users HTTP/1.1
Host: api.example.com
Accept: application/json
```

**Response:**

```
HTTP/1.1 200 OK
Content-Type: application/json

{
  "data": [
    { "id": 1, "name": "Alice" },
    { "id": 2, "name": "Bob" }
  ],
  "meta": {
    "page": 1,
    "limit": 10,
    "total": 42
  }
}
```

### 6.2 GET — Single Resource

**Request:**

```
GET /api/users/1 HTTP/1.1
```

**Response:**

```
HTTP/1.1 200 OK
Content-Type: application/json

{
  "id": 1,
  "name": "Alice",
  "email": "alice@example.com",
  "createdAt": "2025-01-15T10:00:00Z"
}
```

### 6.3 POST — Create Resource

**Request:**

```
POST /api/users HTTP/1.1
Content-Type: application/json

{
  "name": "Charlie",
  "email": "charlie@example.com"
}
```

**Response:**

```
HTTP/1.1 201 Created
Content-Type: application/json
Location: /api/users/3

{
  "id": 3,
  "name": "Charlie",
  "email": "charlie@example.com",
  "createdAt": "2025-02-04T12:00:00Z"
}
```

### 6.4 PUT/PATCH — Update Resource

**Request (PATCH):**

```
PATCH /api/users/1 HTTP/1.1
Content-Type: application/json

{
  "name": "Alice Updated"
}
```

**Response:**

```
HTTP/1.1 200 OK
Content-Type: application/json

{
  "id": 1,
  "name": "Alice Updated",
  "email": "alice@example.com"
}
```

### 6.5 DELETE — Remove Resource

**Request:**

```
DELETE /api/users/1 HTTP/1.1
```

**Response:**

```
HTTP/1.1 204 No Content
```

---

## 7. Authentication & Security

### 7.1 Common Authentication Methods

| Method                       | Description                       | Use Case                           |
| ---------------------------- | --------------------------------- | ---------------------------------- |
| **API Key**            | Secret key in header or query     | Server-to-server, simple apps      |
| **Bearer Token (JWT)** | Token in `Authorization` header | Single-page apps, mobile apps      |
| **Session Cookie**     | Cookie-based session              | Traditional web apps               |
| **OAuth 2.0**          | Delegated authorization           | Third-party login (Google, GitHub) |

### 7.2 JWT (JSON Web Token) Flow

1. Client sends credentials (username/password) to login endpoint
2. Server validates and returns a JWT
3. Client stores JWT and sends it in `Authorization: Bearer <token>` for subsequent requests
4. Server validates JWT on each request

### 7.3 Security Best Practices

- Use **HTTPS** for all API traffic
- Never expose secrets in URLs or client code
- Validate and sanitize all input
- Implement rate limiting to prevent abuse
- Use CORS correctly to control allowed origins

---

## 8. Best Practices & Common Patterns

### 8.1 Pagination

For large collections, always paginate:

```
GET /api/users?page=1&limit=20
GET /api/users?cursor=abc123&limit=20  (cursor-based)
```

### 8.2 Filtering & Sorting

```
GET /api/products?category=electronics&minPrice=100&sort=createdAt&order=desc
```

### 8.3 Error Handling

Return consistent error format with appropriate status codes. Include:

- Error code
- Human-readable message
- Optional: field-level validation details

### 8.4 Documentation

- Use **OpenAPI (Swagger)** or similar for API documentation
- Document all endpoints, parameters, and response formats
- Provide examples for each endpoint

### 8.5 CORS (Cross-Origin Resource Sharing)

When frontend and backend are on different domains, configure CORS headers on the server to allow specific origins.

---

## 9. Deployment & DevOps Overview

### 9.1 Typical Deployment Stack

```
[Git Repository] → [CI/CD Pipeline] → [Build] → [Deploy to Host]
       │                    │
       │                    └── Run tests, build artifacts
       │
       └── Push triggers pipeline
```

### 9.2 Common Hosting Options

| Type                 | Examples                         | Best For                             |
| -------------------- | -------------------------------- | ------------------------------------ |
| **PaaS**       | Vercel, Netlify, Heroku, Railway | Quick deploy, managed infrastructure |
| **VPS**        | DigitalOcean, Linode, AWS EC2    | Full control, custom setup           |
| **Serverless** | AWS Lambda, Vercel Functions     | Event-driven, auto-scaling           |
| **Container**  | Docker + Kubernetes, AWS ECS     | Microservices, complex apps          |

### 9.3 Environment Variables

Never hardcode secrets. Use environment variables for:

- Database URLs
- API keys
- JWT secrets
- Third-party service credentials

---

## Summary

| Concept              | Key Takeaway                            |
| -------------------- | --------------------------------------- |
| **Full Stack** | Frontend + Backend + Database + DevOps  |
| **REST**       | Resource-based, HTTP methods, stateless |
| **HTTP**       | Methods, status codes, headers, body    |
| **API Design** | Nouns, plural, versioning, consistency  |
| **Security**   | HTTPS, auth (JWT), validation, CORS     |

---

## Further Reading

- [REST API Tutorial](https://restfulapi.net/)
- [MDN HTTP Guide](https://developer.mozilla.org/en-US/docs/Web/HTTP)
- [OpenAPI Specification](https://swagger.io/specification/)
