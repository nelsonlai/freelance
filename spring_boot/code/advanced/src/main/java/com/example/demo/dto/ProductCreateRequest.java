package com.example.demo.dto;

import jakarta.validation.constraints.DecimalMin;
import jakarta.validation.constraints.Min;
import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.NotNull;
import jakarta.validation.constraints.Size;

import java.math.BigDecimal;

/**
 * Request DTO for creating a new product (POST /api/products).
 * <p>
 * Bean Validation (JSR 380) annotations are checked when the controller method has {@code @Valid}.
 * If validation fails, Spring throws {@link org.springframework.web.bind.MethodArgumentNotValidException},
 * which can be handled by {@link com.example.demo.exception.GlobalExceptionHandler}.
 */
public class ProductCreateRequest {

    /** Product name; must be non-blank and at most 255 characters. */
    @NotBlank(message = "Name is required")
    @Size(max = 255)
    private String name;

    /** Price; required and must be at least 0.01. */
    @NotNull
    @DecimalMin("0.01")
    private BigDecimal price;

    /** Stock quantity; must be non-negative. */
    @Min(0)
    private int stock;

    /** No-argument constructor; used by Jackson for JSON deserialization. */
    public ProductCreateRequest() {}

    /**
     * All-args constructor for tests or manual construction.
     *
     * @param name  product name
     * @param price price
     * @param stock stock quantity
     */
    public ProductCreateRequest(String name, BigDecimal price, int stock) {
        this.name = name;
        this.price = price;
        this.stock = stock;
    }

    public String getName() { return name; }
    public void setName(String name) { this.name = name; }
    public BigDecimal getPrice() { return price; }
    public void setPrice(BigDecimal price) { this.price = price; }
    public int getStock() { return stock; }
    public void setStock(int stock) { this.stock = stock; }
}
