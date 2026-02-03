# Module 0: Understanding RESTful APIs

Before diving into code, it is essential to understand the architectural style that powers most of the modern web: **REST** (Representational State Transfer).

## 1. What is REST?
REST is an architectural style for providing standards between computer systems on the web, making it easier for systems to communicate with each other. A RESTful API is an interface that uses HTTP requests to GET, PUT, POST, and DELETE data.

## 2. Core Principles of REST

### A. Client-Server Separation
The client (frontend/mobile app) and the server (backend) are independent. They can be developed and scaled separately as long as they agree on the interface (the API).

### B. Statelessness
Each request from a client to a server must contain all the information necessary to understand and complete the request. The server does not store any "session" about the client.

### C. Uniform Interface
This is the heart of REST. It involves:
- **Resource Identification**: Using URIs (e.g., `/users/1`).
- **Resource Manipulation**: Using HTTP methods (GET, POST, etc.).
- **Self-descriptive messages**: Using Media Types (e.g., `application/json`).

## 3. HTTP Methods (The Verbs)

| Method | Action | Description | Idempotent? |
| :--- | :--- | :--- | :--- |
| **GET** | Read | Retrieve a resource or a list of resources. | Yes |
| **POST** | Create | Create a new resource. | No |
| **PUT** | Update | Replace an existing resource entirely. | Yes |
| **PATCH** | Update | Partially update an existing resource. | No |
| **DELETE** | Delete | Remove a resource. | Yes |

*Note: **Idempotent** means making the same request multiple times has the same effect as making it once.*

## 4. HTTP Status Codes

- **2xx (Success)**
    - `200 OK`: Request succeeded.
    - `201 Created`: Resource created (usually after POST).
    - `204 No Content`: Request succeeded, but no data returned (usually after DELETE).
- **4xx (Client Errors)**
    - `400 Bad Request`: Invalid input or syntax.
    - `401 Unauthorized`: Authentication required.
    - `403 Forbidden`: Authenticated but no permission.
    - `404 Not Found`: Resource does not exist.
- **5xx (Server Errors)**
    - `500 Internal Server Error`: Something went wrong on the server.

## 5. Resource Naming (Best Practices)

1.  **Use Nouns, Not Verbs**:
    - Good: `GET /books`
    - Bad: `GET /get-all-books`
2.  **Use Plurals**:
    - Good: `/users/123`
    - Bad: `/user/123`
3.  **Use Sub-resources for Relationships**:
    - `GET /authors/5/books` (Get all books by author #5)
4.  **Use Query Parameters for Filtering/Sorting**:
    - `GET /books?genre=fiction&sort=year`

## 6. Anatomy of a REST Request
- **Endpoint (URL)**: `https://api.example.com/v1/users`
- **Method**: `POST`
- **Headers**: `Content-Type: application/json`, `Authorization: Bearer <token>`
- **Body**: `{"name": "John Doe", "email": "john@example.com"}`
