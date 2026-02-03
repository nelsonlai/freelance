# RESTful API Best Practices & Examples

This guide provides practical examples and advanced concepts for building high-quality REST APIs.

## 1. JSON (JavaScript Object Notation)
JSON is the standard format for REST APIs. It is lightweight and easy for both humans and machines to read.

**Example Response:**
```json
{
  "id": 1,
  "title": "Introduction to REST",
  "author": {
    "id": 42,
    "name": "Jane Smith"
  },
  "tags": ["api", "web", "rest"]
}
```

## 2. Versioning your API
Always version your API to avoid breaking changes for your users.
- **Path versioning (Recommended)**: `https://api.example.com/v1/products`
- **Header versioning**: `Accept: application/vnd.example.v1+json`

## 3. Error Handling
Always return a consistent error object.
```json
{
  "error": "Resource Not Found",
  "message": "The book with ID 999 does not exist in our database.",
  "code": 404
}
```

## 4. Pagination
For endpoints that return lists, never return thousands of items at once. Use pagination.
- `GET /products?page=2&limit=20`
- Response should include metadata:
```json
{
  "data": [...],
  "meta": {
    "current_page": 2,
    "total_pages": 50,
    "total_items": 1000
  }
}
```

## 5. Security
- **HTTPS**: Always use encryption.
- **Authentication**: Use JWT (JSON Web Tokens) or API Keys.
- **Rate Limiting**: Prevent abuse by limiting requests per minute per user.

## 6. Documentation
A REST API is only as good as its documentation.
- Use **OpenAPI (Swagger)** for interactive docs (FastAPI does this automatically!).
- Provide clear examples for every endpoint.
