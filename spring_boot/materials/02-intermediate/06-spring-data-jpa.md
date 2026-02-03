# Module 6: Spring Data JPA

**Level:** Intermediate  
**Time:** ~90 minutes

---

## Learning Objectives

- Define JPA entities and map them to tables
- Create Spring Data JPA repositories (interfaces)
- Use derived query methods and @Query
- Understand transactions and basic best practices

---

## 6.1 Dependencies

Add to `pom.xml` (Maven) or `build.gradle` (Gradle):

**Maven:**

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-data-jpa</artifactId>
</dependency>
<dependency>
    <groupId>com.h2database</groupId>
    <artifactId>h2</artifactId>
    <scope>runtime</scope>
</dependency>
```

**Gradle:**

```groovy
implementation 'org.springframework.boot:spring-boot-starter-data-jpa'
runtimeOnly 'com.h2database:h2'
```

H2 is an in-memory DB for development; replace with PostgreSQL/MySQL for production.

---

## 6.2 Entity

An **entity** is a Java class mapped to a database table:

```java
package com.example.demo.entity;

import jakarta.persistence.*;

@Entity
@Table(name = "products")
public class Product {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @Column(nullable = false, length = 255)
    private String name;

    @Column(nullable = false, precision = 19, scale = 2)
    private java.math.BigDecimal price;

    private int stock;

    @Column(name = "created_at", updatable = false)
    private java.time.Instant createdAt;

    @PrePersist
    protected void onCreate() {
        createdAt = java.time.Instant.now();
    }

    // Default constructor (required by JPA)
    public Product() {}

    // Getters and setters
    public Long getId() { return id; }
    public void setId(Long id) { this.id = id; }
    public String getName() { return name; }
    public void setName(String name) { this.name = name; }
    public java.math.BigDecimal getPrice() { return price; }
    public void setPrice(java.math.BigDecimal price) { this.price = price; }
    public int getStock() { return stock; }
    public void setStock(int stock) { this.stock = stock; }
    public java.time.Instant getCreatedAt() { return createdAt; }
    public void setCreatedAt(java.time.Instant createdAt) { this.createdAt = createdAt; }
}
```

- **@Entity** — JPA entity
- **@Table** — table name (optional; default = class name)
- **@Id** — primary key
- **@GeneratedValue** — auto-generated ID (e.g. IDENTITY for MySQL/Postgres)
- **@Column** — column mapping
- **@PrePersist** — set `createdAt` before first persist

---

## 6.3 Repository Interface

Spring Data JPA provides implementations for interfaces that extend `JpaRepository`:

```java
package com.example.demo.repository;

import com.example.demo.entity.Product;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface ProductRepository extends JpaRepository<Product, Long> {

    List<Product> findByNameContainingIgnoreCase(String name);

    List<Product> findByPriceBetween(java.math.BigDecimal min, java.math.BigDecimal max);

    boolean existsByName(String name);
}
```

You do **not** implement this interface; Spring generates the implementation at runtime.

- **JpaRepository<Product, Long>** — entity type and ID type
- **findByNameContainingIgnoreCase** — derived query: `WHERE LOWER(name) LIKE %name%`
- **findByPriceBetween** — `WHERE price BETWEEN min AND max`
- **existsByName** — `SELECT COUNT(*) > 0 WHERE name = ?`

---

## 6.4 Derived Query Methods (Naming Conventions)

| Method name pattern | Generated query (concept) |
|---------------------|---------------------------|
| `findByName(String name)` | `WHERE name = ?` |
| `findByNameAndPrice(String name, BigDecimal price)` | `WHERE name = ? AND price = ?` |
| `findByNameOrDescription(...)` | `WHERE name = ? OR description = ?` |
| `findByOrderByCreatedAtDesc()` | `ORDER BY created_at DESC` |
| `findTop10By...()` | `LIMIT 10` |
| `countByName(String name)` | `SELECT COUNT(*) WHERE name = ?` |
| `existsByEmail(String email)` | `SELECT COUNT(*) > 0 WHERE email = ?` |

[Spring Data JPA Reference — Query methods](https://docs.spring.io/spring-data/jpa/docs/current/reference/html/#jpa.query-methods.query-creation)

---

## 6.5 @Query for Custom JPQL or SQL

```java
public interface ProductRepository extends JpaRepository<Product, Long> {

    @Query("SELECT p FROM Product p WHERE p.name LIKE %:keyword% OR p.description LIKE %:keyword%")
    List<Product> searchByKeyword(@Param("keyword") String keyword);

    @Query(value = "SELECT * FROM products WHERE price > :minPrice", nativeQuery = true)
    List<Product> findByPriceGreaterThan(@Param("minPrice") java.math.BigDecimal minPrice);
}
```

- **JPQL** — entity-based (default); use `:param` and `@Param`.
- **nativeQuery = true** — raw SQL; use with care (table/column names).

---

## 6.6 Service Layer and Transactions

Keep controllers thin; put business logic in a service and use `@Transactional` for write operations:

```java
@Service
public class ProductService {

    private final ProductRepository productRepository;

    public ProductService(ProductRepository productRepository) {
        this.productRepository = productRepository;
    }

    @Transactional(readOnly = true)
    public Optional<Product> findById(Long id) {
        return productRepository.findById(id);
    }

    @Transactional
    public Product create(ProductCreateRequest request) {
        if (productRepository.existsByName(request.getName())) {
            throw new DuplicateResourceException("Product name already exists");
        }
        Product product = new Product();
        product.setName(request.getName());
        product.setPrice(request.getPrice());
        product.setStock(request.getStock());
        return productRepository.save(product);
    }

    @Transactional
    public Product update(Long id, ProductUpdateRequest request) {
        Product product = productRepository.findById(id)
            .orElseThrow(() -> new ResourceNotFoundException("Product not found: " + id));
        product.setName(request.getName());
        product.setPrice(request.getPrice());
        product.setStock(request.getStock());
        return productRepository.save(product);
    }

    @Transactional
    public void deleteById(Long id) {
        if (!productRepository.existsById(id)) {
            throw new ResourceNotFoundException("Product not found: " + id);
        }
        productRepository.deleteById(id);
    }
}
```

- **@Transactional** — one transaction per method; rollback on unchecked exception.
- **@Transactional(readOnly = true)** — hint for read-only optimizations.

---

## 6.7 Configuration (application.properties)

```properties
# H2 (development)
spring.datasource.url=jdbc:h2:mem:testdb
spring.datasource.driver-class-name=org.h2.Driver
spring.datasource.username=sa
spring.datasource.password=
spring.h2.console.enabled=true
spring.jpa.hibernate.ddl-auto=create-drop
spring.jpa.show-sql=true

# PostgreSQL (production example)
# spring.datasource.url=jdbc:postgresql://localhost:5432/mydb
# spring.datasource.username=user
# spring.datasource.password=pass
# spring.jpa.hibernate.ddl-auto=validate
```

- **ddl-auto:** `create-drop` (dev), `update` (dev), `validate` (prod), `none`.

---

## 6.8 Summary

- **Entity:** `@Entity`, `@Table`, `@Id`, `@GeneratedValue`, `@Column`.
- **Repository:** Extend `JpaRepository<Entity, IdType>`; use derived methods or `@Query`.
- **Service:** Business logic and `@Transactional` for writes.
- **Config:** Datasource and JPA/Hibernate in `application.properties`.

---

## Exercises

1. Create an entity `Order` with id, customerName, total, createdAt and a repository with `findByCustomerName`.
2. Add a service that creates an order and a REST endpoint POST /api/orders.
3. Use `@Query` to find orders with total greater than a given value.
