package com.example.demo.dto;

import jakarta.validation.constraints.DecimalMin;
import jakarta.validation.constraints.Min;
import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.NotNull;
import jakarta.validation.constraints.Size;

import java.math.BigDecimal;

/**
 * Request DTO for updating an existing product (PUT /api/products/{id}).
 * <p>
 * Same validation rules as {@link ProductCreateRequest}; used for full replacement of product fields.
 * Bean Validation runs when the controller parameter is annotated with {@code @Valid}.
 */
public class ProductUpdateRequest {

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

    public String getName() { return name; }
    public void setName(String name) { this.name = name; }
    public BigDecimal getPrice() { return price; }
    public void setPrice(BigDecimal price) { this.price = price; }
    public int getStock() { return stock; }
    public void setStock(int stock) { this.stock = stock; }
}
