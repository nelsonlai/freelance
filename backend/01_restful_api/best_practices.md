# RESTful API Best Practices

Practical guidelines for designing and implementing production-quality REST APIs.

---

## 1. Use JSON

- Use **JSON** for request and response bodies (`Content-Type: application/json`).
- Keep keys consistent (e.g. camelCase or snake_case) across the API.
- Avoid exposing internal IDs or implementation details when not needed.

---

## 2. Version Your API

- **Path versioning**: `/v1/users`, `/v2/users` — simple and clear.
- **Header versioning**: `Accept: application/vnd.api.v1+json` — keeps URLs stable.
- When introducing breaking changes, add a new version and deprecate the old one with clear communication.

---

## 3. Consistent Error Responses

Use a single error format so clients can parse errors reliably.

**Example:**

```json
{
  "error": {
    "code": "VALIDATION_ERROR",
    "message": "Invalid input",
    "details": [
      { "field": "email", "message": "Must be a valid email address" }
    ]
  }
}
```

- Include an HTTP status code and a machine-readable `code` when useful.
- Don’t leak stack traces or internal paths in production.

---

## 4. Pagination for Lists

- Never return unbounded lists (e.g. "all users").
- Support at least: `page` + `limit`, or `offset` + `limit`, or cursor-based pagination.
- Include metadata: `totalItems`, `totalPages`, `currentPage` (or next cursor).

---

## 5. Security

- **HTTPS only** in production.
- **Authentication**: Prefer tokens (e.g. JWT) in `Authorization` header; avoid putting secrets in query params.
- **Authorization**: Enforce per-resource (e.g. user can only access their own data).
- **Rate limiting**: Per IP or per user to prevent abuse and DDoS.
- **Input validation**: Validate and sanitize all inputs; reject invalid data with 400.

---

## 6. Idempotency (Where It Matters)

- **GET, PUT, DELETE** should be idempotent: same request → same outcome.
- For **POST** (e.g. payments), support idempotency keys: `Idempotency-Key: <uuid>` and return the same result for the same key.

---

## 7. HATEOAS (Optional)

Hypermedia links in responses can describe available actions (e.g. `next`, `prev`, `self`). Useful for discoverability; not required for most internal or partner APIs.

---

## 8. Documentation

- Maintain **OpenAPI (Swagger)** or similar spec.
- Document every endpoint: method, path, parameters, body schema, response codes, example payloads.
- Many frameworks auto-generate docs from code (FastAPI, Nest.js).

---

## 9. Health and Readiness

- **Health**: `GET /health` — is the process up? (200 OK).
- **Readiness**: `GET /ready` — can the server accept traffic? (e.g. DB and dependencies available). Use for load balancers and Kubernetes.

---

## 10. Logging and Observability

- Log request ID, method, path, status, duration; avoid logging full bodies (PII).
- Use structured logs (JSON) for easier querying.
- Metrics: request count, latency, error rate per endpoint.

---

*See [01_restful_api/README.md](README.md) for core REST concepts.*
