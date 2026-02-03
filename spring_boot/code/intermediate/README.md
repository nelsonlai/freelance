# Spring Boot Intermediate Code

Corresponds to **Modules 5–8** (REST APIs, Spring Data JPA, Spring Security, Configuration).

## Run

```bash
./mvnw spring-boot:run
```

## Endpoints

- **GET /api/public/health** — no auth
- **GET /api/products** — list (auth: user/password or admin/admin)
- **GET /api/products/{id}** — get one
- **POST /api/products** — create (JSON body)
- **PUT /api/products/{id}** — update
- **DELETE /api/products/{id}** — delete

## Auth (HTTP Basic)

- User: `user` / `password` (USER)
- Admin: `admin` / `admin` (USER, ADMIN)

Example with curl:

```bash
curl -u user:password http://localhost:8080/api/products
curl -u user:password -X POST -H "Content-Type: application/json" -d '{"name":"Laptop","price":999.99,"stock":10}' http://localhost:8080/api/products
```

## Structure

- **entity/Product.java** — JPA entity
- **repository/ProductRepository.java** — Spring Data JPA
- **service/ProductService.java** — transactions, business logic
- **controller/ProductController.java** — REST CRUD, validation
- **exception/GlobalExceptionHandler.java** — validation and not-found handling
- **config/SecurityConfig.java** — SecurityFilterChain, in-memory users
