package com.example.demo.controller;

import com.example.demo.dto.ProductCreateRequest;
import com.example.demo.dto.ProductUpdateRequest;
import com.example.demo.entity.Product;
import com.example.demo.service.ProductService;
import jakarta.validation.Valid;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.support.ServletUriComponentsBuilder;

import java.net.URI;
import java.util.List;

/**
 * REST controller for product CRUD operations.
 * <p>
 * All endpoints are under {@code /api/products}. Requires authentication (HTTP Basic) except where
 * security config permits. Uses {@code @Valid} so that request bodies are validated (Bean Validation);
 * validation errors are handled by {@link com.example.demo.exception.GlobalExceptionHandler}.
 */
@RestController
@RequestMapping("/api/products")
public class ProductController {

    private final ProductService productService;

    public ProductController(ProductService productService) {
        this.productService = productService;
    }

    /**
     * GET /api/products — list all products, optionally filtered by name.
     * Query param {@code name} (optional): if present, only products whose name contains this string (case-insensitive).
     *
     * @param name optional search string for product name
     * @return list of products (possibly empty)
     */
    @GetMapping
    public List<Product> list(
            @RequestParam(required = false, defaultValue = "") String name) {
        if (name.isBlank()) {
            return productService.findAll();
        }
        return productService.findByNameContaining(name);
    }

    /**
     * GET /api/products/{id} — get a single product by ID.
     *
     * @param id product ID (path variable)
     * @return 200 OK with product body, or 404 Not Found if not found
     */
    @GetMapping("/{id}")
    public ResponseEntity<Product> getById(@PathVariable Long id) {
        return productService.findById(id)
            .map(ResponseEntity::ok)
            .orElse(ResponseEntity.notFound().build());
    }

    /**
     * POST /api/products — create a new product.
     * Request body is validated; duplicate name returns 409 Conflict.
     *
     * @param request JSON body (name, price, stock)
     * @return 201 Created with product body and Location header pointing to the new resource
     */
    @PostMapping
    public ResponseEntity<Product> create(@RequestBody @Valid ProductCreateRequest request) {
        Product created = productService.create(request);
        URI location = ServletUriComponentsBuilder
            .fromCurrentRequest()
            .path("/{id}")
            .buildAndExpand(created.getId())
            .toUri();
        return ResponseEntity.status(HttpStatus.CREATED).location(location).body(created);
    }

    /**
     * PUT /api/products/{id} — full update of an existing product.
     *
     * @param id      product ID (path variable)
     * @param request JSON body (name, price, stock)
     * @return 200 OK with updated product, or 404 Not Found if product does not exist
     */
    @PutMapping("/{id}")
    public ResponseEntity<Product> update(
            @PathVariable Long id,
            @RequestBody @Valid ProductUpdateRequest request) {
        return productService.findById(id)
            .map(existing -> ResponseEntity.ok(productService.update(id, request)))
            .orElse(ResponseEntity.notFound().build());
    }

    /**
     * DELETE /api/products/{id} — delete a product.
     *
     * @param id product ID (path variable)
     * @return 204 No Content on success, or 404 Not Found if product does not exist
     */
    @DeleteMapping("/{id}")
    public ResponseEntity<Void> delete(@PathVariable Long id) {
        return productService.findById(id)
            .map(p -> {
                productService.deleteById(id);
                return ResponseEntity.noContent().<Void>build();
            })
            .orElse(ResponseEntity.notFound().build());
    }
}
