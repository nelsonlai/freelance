# Module 1: RESTful API Fundamentals

REST (Representational State Transfer) is the dominant architectural style for web APIs. This module covers concepts you need before building backends with any framework.

---

## 1. What is REST?

REST is an **architectural style** for distributed systems. A **RESTful API** exposes resources over HTTP using standard methods and status codes so clients and servers can communicate in a uniform way.

- **Resource**: Any entity your API exposes (users, orders, products).
- **Representation**: Usually JSON (or XML). The "state" of a resource at a point in time.
- **Transfer**: Client and server exchange representations via HTTP.

---

## 2. Core Principles

### Client–Server Separation

- Client (browser, mobile app, another service) and server are independent.
- They only need to agree on the API contract (URLs, methods, payloads).
- Each can evolve and scale separately.

### Statelessness

- Each request must carry everything the server needs to understand and process it.
- The server does **not** store client session state between requests.
- Authentication is typically done per request (e.g. `Authorization: Bearer <token>`).

### Uniform Interface

- **Resource identification**: Resources are identified by URIs (e.g. `/users/42`).
- **Resource manipulation**: Standard HTTP methods (GET, POST, PUT, PATCH, DELETE).
- **Self-descriptive messages**: Headers like `Content-Type: application/json` describe the body.

---

## 3. HTTP Methods (Verbs)

| Method   | Typical use | Description                    | Idempotent? |
|----------|-------------|--------------------------------|-------------|
| **GET**  | Read        | Retrieve one or many resources | Yes         |
| **POST** | Create      | Create a new resource         | No          |
| **PUT**  | Replace     | Replace entire resource       | Yes         |
| **PATCH**| Partial update | Update part of a resource  | No*         |
| **DELETE** | Delete   | Remove a resource              | Yes         |

*Idempotent*: repeating the same request has the same effect as doing it once (e.g. GET, PUT, DELETE).

### Examples

- `GET /users` — list users  
- `GET /users/1` — get user with id 1  
- `POST /users` — create user (body: `{ "name": "Alice", "email": "alice@example.com" }`)  
- `PUT /users/1` — replace user 1 with the body  
- `PATCH /users/1` — partially update user 1  
- `DELETE /users/1` — delete user 1  

---

## 4. HTTP Status Codes

Use status codes so clients can handle success and errors consistently.

### 2xx Success

- **200 OK** — Request succeeded (e.g. GET, PUT, PATCH).
- **201 Created** — Resource created (e.g. after POST); often include `Location` header.
- **204 No Content** — Success with no body (e.g. after DELETE).

### 4xx Client Errors

- **400 Bad Request** — Invalid input or malformed request.
- **401 Unauthorized** — Not authenticated (e.g. missing or invalid token).
- **403 Forbidden** — Authenticated but not allowed to perform this action.
- **404 Not Found** — Resource does not exist.
- **409 Conflict** — Conflict with current state (e.g. duplicate key).

### 5xx Server Errors

- **500 Internal Server Error** — Unexpected server failure.
- **502 Bad Gateway** / **503 Service Unavailable** — Proxy or server temporarily unavailable.

---

## 5. Resource Naming Conventions

- **Use nouns, not verbs**  
  - Good: `GET /books`  
  - Avoid: `GET /getBooks`

- **Use plurals for collections**  
  - Good: `/users`, `/users/123`  
  - Avoid: `/user`, `/user/123` for the collection/item pattern

- **Use hierarchy for relationships**  
  - `GET /users/5/orders` — orders belonging to user 5  
  - `GET /orders/10/items` — items in order 10  

- **Use query parameters for filtering, sorting, pagination**  
  - `GET /products?category=electronics&sort=price&order=asc`  
  - `GET /products?page=2&limit=20`  

---

## 6. Request/Response Anatomy

### Typical request

- **Method + URL**: `POST https://api.example.com/v1/users`
- **Headers**:  
  - `Content-Type: application/json`  
  - `Authorization: Bearer <token>`  
  - `Accept: application/json`
- **Body**: `{"name": "Jane", "email": "jane@example.com"}`

### Typical success response (201)

- **Headers**: `Content-Type: application/json`, optionally `Location: /v1/users/42`
- **Body**: `{"id": 42, "name": "Jane", "email": "jane@example.com"}`

### Typical error response (4xx/5xx)

Return a consistent error shape, e.g.:

```json
{
  "error": {
    "code": "NOT_FOUND",
    "message": "User with id 999 does not exist."
  }
}
```

---

## 7. API Versioning

Avoid breaking existing clients when you change the API.

- **URL path (common)**: `https://api.example.com/v1/users`, `https://api.example.com/v2/users`
- **Header**: `Accept: application/vnd.example.v1+json`

---

## 8. Pagination

For list endpoints, don’t return unbounded lists.

- **Query**: `?page=2&limit=20` or `?offset=20&limit=20` or `?cursor=abc123`
- **Response** often includes metadata:

```json
{
  "data": [ ... ],
  "meta": {
    "currentPage": 2,
    "totalPages": 10,
    "totalItems": 200
  }
}
```

---

## 9. Security Basics

- Use **HTTPS** in production.
- **Authentication**: JWT, API keys, or OAuth — include in headers, not in URLs.
- **Authorization**: Check permissions per endpoint (e.g. user can only edit own resource).
- **Rate limiting**: Limit requests per client/IP to reduce abuse.
- **Input validation**: Validate and sanitize all inputs; return 400 for invalid data.

---

## 10. Documentation

- Describe every endpoint: method, path, query/body parameters, responses, errors.
- **OpenAPI (Swagger)** is widely used; many frameworks (e.g. FastAPI, Nest.js) can generate it from code.
- Provide example requests and responses.

---

## Next Steps

- **Python**: [02_python_fastapi](../02_python_fastapi/) or [03_python_flask](../03_python_flask/)
- **Node**: [04_nodejs](../04_nodejs/) or [05_nestjs](../05_nestjs/)

See also: [Best practices](best_practices.md) and the REST section in `../python_backend/curriculum/rest_api/`.
