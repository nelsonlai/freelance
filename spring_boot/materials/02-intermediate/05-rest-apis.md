# Module 5: Building REST APIs

**Level:** Intermediate  
**Time:** ~90 minutes

---

## Learning Objectives

- Map HTTP methods (GET, POST, PUT, PATCH, DELETE) to controller methods
- Use path variables, request parameters, and request bodies
- Handle validation and error responses
- Apply REST conventions (status codes, resource naming)

---

## 5.1 HTTP Methods and REST Conventions

| Method | Typical use | Idempotent? |
|--------|-------------|-------------|
| GET | Read resource(s) | Yes |
| POST | Create resource | No |
| PUT | Replace resource (full update) | Yes |
| PATCH | Partial update | Yes (semantically) |
| DELETE | Delete resource | Yes |

**REST conventions:** Use nouns for resources (e.g. `/users`, `/orders`), HTTP methods for actions.

---

## 5.2 Path Variables

Use `@PathVariable` for resource identifiers:

```java
@RestController
@RequestMapping("/api/products")
public class ProductController {

    @GetMapping("/{id}")
    public Product getById(@PathVariable Long id) {
        return productService.findById(id);
    }

    @DeleteMapping("/{id}")
    public void delete(@PathVariable Long id) {
        productService.deleteById(id);
    }
}
```

- **GET /api/products/1** → `id = 1`
- **DELETE /api/products/1** → `id = 1`

---

## 5.3 Request Parameters

Use `@RequestParam` for query parameters:

```java
@GetMapping
public List<Product> list(
    @RequestParam(required = false, defaultValue = "0") int page,
    @RequestParam(required = false, defaultValue = "20") int size,
    @RequestParam(required = false) String name
) {
    return productService.findAll(page, size, name);
}
```

Example: **GET /api/products?page=0&size=10&name=laptop**

---

## 5.4 Request Body and POST/PUT

Use `@RequestBody` for JSON (or other) request bodies:

```java
@PostMapping
public ResponseEntity<Product> create(@RequestBody @Valid ProductCreateRequest request) {
    Product created = productService.create(request);
    return ResponseEntity.status(HttpStatus.CREATED).body(created);
}

@PutMapping("/{id}")
public Product update(@PathVariable Long id, @RequestBody @Valid ProductUpdateRequest request) {
    return productService.update(id, request);
}
```

- **POST** → create; return **201 Created** and the new resource (or its location).
- **PUT** → full replace; return **200 OK** and the updated resource.

---

## 5.5 ResponseEntity

Use `ResponseEntity` to control status code and headers:

```java
@GetMapping("/{id}")
public ResponseEntity<Product> getById(@PathVariable Long id) {
    return productService.findById(id)
        .map(ResponseEntity::ok)
        .orElse(ResponseEntity.notFound().build());
}

@PostMapping
public ResponseEntity<Product> create(@RequestBody @Valid ProductCreateRequest request) {
    Product created = productService.create(request);
    URI location = ServletUriComponentsBuilder
        .fromCurrentRequest()
        .path("/{id}")
        .buildAndExpand(created.getId())
        .toUri();
    return ResponseEntity.created(location).body(created);
}
```

---

## 5.6 Validation with Bean Validation (JSR 380)

Add `spring-boot-starter-validation` (or it may come with `spring-boot-starter-web`). Use annotations on DTOs:

```java
public class ProductCreateRequest {
    @NotBlank(message = "Name is required")
    @Size(max = 255)
    private String name;

    @NotNull
    @DecimalMin("0.01")
    private BigDecimal price;

    @Min(0)
    private int stock;

    // getters and setters
}
```

Controller:

```java
@PostMapping
public ResponseEntity<Product> create(@RequestBody @Valid ProductCreateRequest request) {
    // If validation fails, MethodArgumentNotValidException is thrown
    // and can be handled by @ControllerAdvice
    Product created = productService.create(request);
    return ResponseEntity.status(HttpStatus.CREATED).body(created);
}
```

---

## 5.7 Global Exception Handling (@ControllerAdvice)

Handle validation and business exceptions in one place:

```java
@RestControllerAdvice
public class GlobalExceptionHandler {

    @ExceptionHandler(MethodArgumentNotValidException.class)
    public ResponseEntity<Map<String, Object>> handleValidation(
            MethodArgumentNotValidException ex) {
        Map<String, String> errors = new HashMap<>();
        ex.getBindingResult().getFieldErrors().forEach(err ->
            errors.put(err.getField(), err.getDefaultMessage()));
        return ResponseEntity
            .status(HttpStatus.BAD_REQUEST)
            .body(Map.of("message", "Validation failed", "errors", errors));
    }

    @ExceptionHandler(ResourceNotFoundException.class)
    public ResponseEntity<Map<String, String>> handleNotFound(ResourceNotFoundException ex) {
        return ResponseEntity
            .status(HttpStatus.NOT_FOUND)
            .body(Map.of("message", ex.getMessage()));
    }
}
```

---

## 5.8 Summary

- **Path variables:** `@PathVariable` for IDs in the path.
- **Query params:** `@RequestParam` for filters and pagination.
- **Request body:** `@RequestBody` + `@Valid` for POST/PUT.
- **Status codes:** Use `ResponseEntity` for 201, 404, etc.
- **Validation:** Bean Validation on DTOs; handle `MethodArgumentNotValidException` in `@RestControllerAdvice`.

---

## Exercises

1. Implement GET /api/products, POST /api/products, GET /api/products/{id}, PUT /api/products/{id}, DELETE /api/products/{id} with a simple in-memory service.
2. Add validation to the create/update DTOs and a global handler that returns a structured error JSON.
3. Return 404 when a product is not found and 201 with a Location header on create.
