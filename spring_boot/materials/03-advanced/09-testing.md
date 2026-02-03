# Module 9: Testing

**Level:** Advanced  
**Time:** ~90 minutes

---

## Learning Objectives

- Write unit tests with JUnit 5 and Mockito
- Test REST controllers with MockMvc
- Run integration tests with @SpringBootTest and Testcontainers (conceptual)
- Use test slices (@WebMvcTest, @DataJpaTest) for focused tests

---

## 9.1 Dependencies

Spring Boot starters include **JUnit 5** and **Mockito**. For MockMvc you need `spring-boot-starter-web` (and usually `spring-boot-starter-test`, which brings AssertJ, Hamcrest, Mockito, and JSON path).

**Maven (spring-boot-starter-test):**

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-test</artifactId>
    <scope>test</scope>
</dependency>
```

**Gradle:** Same; scope `testImplementation`.

---

## 9.2 Unit Testing a Service (Mockito)

**Service:**

```java
@Service
public class ProductService {
    private final ProductRepository productRepository;

    public ProductService(ProductRepository productRepository) {
        this.productRepository = productRepository;
    }

    public Optional<Product> findById(Long id) {
        return productRepository.findById(id);
    }

    public Product create(ProductCreateRequest request) {
        if (productRepository.existsByName(request.getName())) {
            throw new DuplicateResourceException("Name exists");
        }
        Product product = new Product();
        product.setName(request.getName());
        product.setPrice(request.getPrice());
        product.setStock(request.getStock());
        return productRepository.save(product);
    }
}
```

**Test:**

```java
package com.example.demo.service;

import com.example.demo.dto.ProductCreateRequest;
import com.example.demo.entity.Product;
import com.example.demo.exception.DuplicateResourceException;
import com.example.demo.repository.ProductRepository;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;

import java.math.BigDecimal;
import java.util.Optional;

import static org.assertj.core.api.Assertions.assertThat;
import static org.assertj.core.api.Assertions.assertThatThrownBy;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.*;

@ExtendWith(MockitoExtension.class)
class ProductServiceTest {

    @Mock
    private ProductRepository productRepository;

    @InjectMocks
    private ProductService productService;

    @Test
    void findById_whenExists_returnsProduct() {
        Product product = new Product();
        product.setId(1L);
        product.setName("Laptop");
        product.setPrice(new BigDecimal("999.99"));
        when(productRepository.findById(1L)).thenReturn(Optional.of(product));

        Optional<Product> result = productService.findById(1L);

        assertThat(result).isPresent();
        assertThat(result.get().getName()).isEqualTo("Laptop");
        verify(productRepository).findById(1L);
    }

    @Test
    void findById_whenNotExists_returnsEmpty() {
        when(productRepository.findById(999L)).thenReturn(Optional.empty());

        Optional<Product> result = productService.findById(999L);

        assertThat(result).isEmpty();
    }

    @Test
    void create_whenNameExists_throwsDuplicateResourceException() {
        ProductCreateRequest request = new ProductCreateRequest("Laptop", new BigDecimal("999"), 10);
        when(productRepository.existsByName("Laptop")).thenReturn(true);

        assertThatThrownBy(() -> productService.create(request))
            .isInstanceOf(DuplicateResourceException.class)
            .hasMessageContaining("Name exists");

        verify(productRepository, never()).save(any());
    }

    @Test
    void create_whenNameUnique_savesAndReturnsProduct() {
        ProductCreateRequest request = new ProductCreateRequest("Laptop", new BigDecimal("999"), 10);
        when(productRepository.existsByName("Laptop")).thenReturn(false);
        Product saved = new Product();
        saved.setId(1L);
        saved.setName("Laptop");
        saved.setPrice(new BigDecimal("999"));
        saved.setStock(10);
        when(productRepository.save(any(Product.class))).thenReturn(saved);

        Product result = productService.create(request);

        assertThat(result.getId()).isEqualTo(1L);
        assertThat(result.getName()).isEqualTo("Laptop");
        verify(productRepository).save(any(Product.class));
    }
}
```

- **@ExtendWith(MockitoExtension.class)** — enables Mockito for JUnit 5.
- **@Mock** — mock dependency.
- **@InjectMocks** — creates the subject and injects mocks.
- **when(...).thenReturn(...)** — stub behavior.
- **verify(...)** — assert calls.
- **assertThatThrownBy** — assert exceptions (AssertJ).

---

## 9.3 Testing REST Controllers with MockMvc

**Controller:**

```java
@RestController
@RequestMapping("/api/products")
public class ProductController {
    private final ProductService productService;

    public ProductController(ProductService productService) {
        this.productService = productService;
    }

    @GetMapping("/{id}")
    public ResponseEntity<Product> getById(@PathVariable Long id) {
        return productService.findById(id)
            .map(ResponseEntity::ok)
            .orElse(ResponseEntity.notFound().build());
    }

    @PostMapping
    public ResponseEntity<Product> create(@RequestBody @Valid ProductCreateRequest request) {
        Product created = productService.create(request);
        return ResponseEntity.status(HttpStatus.CREATED).body(created);
    }
}
```

**Test (slice: only web layer):**

```java
package com.example.demo.controller;

import com.example.demo.dto.ProductCreateRequest;
import com.example.demo.entity.Product;
import com.example.demo.service.ProductService;
import com.fasterxml.jackson.databind.ObjectMapper;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.WebMvcTest;
import org.springframework.boot.test.mock.mockito.MockBean;
import org.springframework.http.MediaType;
import org.springframework.test.web.servlet.MockMvc;

import java.math.BigDecimal;
import java.util.Optional;

import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.when;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;

@WebMvcTest(ProductController.class)
class ProductControllerTest {

    @Autowired
    private MockMvc mockMvc;

    @Autowired
    private ObjectMapper objectMapper;

    @MockBean
    private ProductService productService;

    @Test
    void getById_whenExists_returns200AndProduct() throws Exception {
        Product product = new Product();
        product.setId(1L);
        product.setName("Laptop");
        product.setPrice(new BigDecimal("999.99"));
        when(productService.findById(1L)).thenReturn(Optional.of(product));

        mockMvc.perform(get("/api/products/1"))
            .andExpect(status().isOk())
            .andExpect(jsonPath("$.id").value(1))
            .andExpect(jsonPath("$.name").value("Laptop"))
            .andExpect(jsonPath("$.price").value(999.99));
    }

    @Test
    void getById_whenNotExists_returns404() throws Exception {
        when(productService.findById(999L)).thenReturn(Optional.empty());

        mockMvc.perform(get("/api/products/999"))
            .andExpect(status().isNotFound());
    }

    @Test
    void create_returns201AndBody() throws Exception {
        ProductCreateRequest request = new ProductCreateRequest("Laptop", new BigDecimal("999"), 10);
        Product created = new Product();
        created.setId(1L);
        created.setName("Laptop");
        created.setPrice(new BigDecimal("999"));
        created.setStock(10);
        when(productService.create(any(ProductCreateRequest.class))).thenReturn(created);

        mockMvc.perform(post("/api/products")
                .contentType(MediaType.APPLICATION_JSON)
                .content(objectMapper.writeValueAsString(request)))
            .andExpect(status().isCreated())
            .andExpect(jsonPath("$.id").value(1))
            .andExpect(jsonPath("$.name").value("Laptop"));
    }
}
```

- **@WebMvcTest(ProductController.class)** — loads only the web layer and the specified controller; other beans must be mocked with **@MockBean**.
- **MockMvc** — perform requests and assert status/JSON without starting the full server.
- **jsonPath** — assert JSON fields (JsonPath).

---

## 9.4 Integration Test with @SpringBootTest

Full application context and real HTTP (optional):

```java
@SpringBootTest(webEnvironment = SpringBootTest.WebEnvironment.RANDOM_PORT)
@AutoConfigureMockMvc
class ProductControllerIntegrationTest {

    @Autowired
    private MockMvc mockMvc;

    @Autowired
    private ProductRepository productRepository;

    @BeforeEach
    void setUp() {
        productRepository.deleteAll();
    }

    @Test
    void createThenGet_returnsCreatedProduct() throws Exception {
        String body = "{\"name\":\"Laptop\",\"price\":999.99,\"stock\":10}";
        mockMvc.perform(post("/api/products")
                .contentType(MediaType.APPLICATION_JSON)
                .content(body))
            .andExpect(status().isCreated())
            .andExpect(jsonPath("$.name").value("Laptop"));

        Long id = productRepository.findAll().get(0).getId();
        mockMvc.perform(get("/api/products/" + id))
            .andExpect(status().isOk())
            .andExpect(jsonPath("$.name").value("Laptop"));
    }
}
```

- **@SpringBootTest** — loads full context; **RANDOM_PORT** starts the real server on a random port.
- **@AutoConfigureMockMvc** — adds MockMvc; you can also use **TestRestTemplate** with the real port.
- Use an in-memory DB (H2) or Testcontainers for integration tests so the DB is isolated.

---

## 9.5 Test Slices Summary

| Annotation | What it loads | Use case |
|------------|----------------|----------|
| **@WebMvcTest(Controller.class)** | Web layer + one controller | Controller tests with mocked services |
| **@DataJpaTest** | JPA + one repository | Repository tests with in-memory DB |
| **@SpringBootTest** | Full context | Integration tests |

---

## 9.6 Summary

- **Unit tests:** Mock dependencies with Mockito; test service logic.
- **Controller tests:** @WebMvcTest + MockMvc + @MockBean for services.
- **Integration tests:** @SpringBootTest + MockMvc or TestRestTemplate; use in-memory DB or Testcontainers.
- **Slices:** @WebMvcTest, @DataJpaTest for faster, focused tests.

---

## Exercises

1. Add unit tests for a service method that updates a product (happy path and not-found).
2. Add a MockMvc test for PUT /api/products/{id} that expects 200 and updated JSON.
3. Write one @DataJpaTest for a repository method (e.g. findByNameContainingIgnoreCase).
