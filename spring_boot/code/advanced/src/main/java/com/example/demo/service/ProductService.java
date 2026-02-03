package com.example.demo.service;

import com.example.demo.dto.ProductCreateRequest;
import com.example.demo.dto.ProductUpdateRequest;
import com.example.demo.entity.Product;
import com.example.demo.exception.DuplicateResourceException;
import com.example.demo.exception.ResourceNotFoundException;
import com.example.demo.repository.ProductRepository;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.Optional;

/**
 * Service layer for product business logic.
 * <p>
 * Delegates persistence to {@link ProductRepository}. Uses {@code @Transactional} so that
 * each method runs in a single transaction (rollback on unchecked exception). Read-only methods
 * use {@code readOnly = true} for optimization hints.
 */
@Service
public class ProductService {

    private final ProductRepository productRepository;

    public ProductService(ProductRepository productRepository) {
        this.productRepository = productRepository;
    }

    /**
     * Find a product by ID.
     *
     * @param id product ID
     * @return Optional containing the product if found, empty otherwise
     */
    @Transactional(readOnly = true)
    public Optional<Product> findById(Long id) {
        return productRepository.findById(id);
    }

    /**
     * Find all products.
     *
     * @return list of all products
     */
    @Transactional(readOnly = true)
    public List<Product> findAll() {
        return productRepository.findAll();
    }

    /**
     * Find products whose name contains the given string (case-insensitive).
     *
     * @param name substring to search for
     * @return list of matching products
     */
    @Transactional(readOnly = true)
    public List<Product> findByNameContaining(String name) {
        return productRepository.findByNameContainingIgnoreCase(name);
    }

    /**
     * Create a new product. Throws {@link DuplicateResourceException} if a product with the same name exists.
     *
     * @param request create request (name, price, stock)
     * @return the persisted product (with ID and createdAt set)
     */
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

    /**
     * Update an existing product. Throws {@link ResourceNotFoundException} if the product does not exist.
     *
     * @param id      product ID
     * @param request update request (name, price, stock)
     * @return the updated product
     */
    @Transactional
    public Product update(Long id, ProductUpdateRequest request) {
        Product product = productRepository.findById(id)
            .orElseThrow(() -> new ResourceNotFoundException("Product not found: " + id));
        product.setName(request.getName());
        product.setPrice(request.getPrice());
        product.setStock(request.getStock());
        return productRepository.save(product);
    }

    /**
     * Delete a product by ID. Throws {@link ResourceNotFoundException} if the product does not exist.
     *
     * @param id product ID
     */
    @Transactional
    public void deleteById(Long id) {
        if (!productRepository.existsById(id)) {
            throw new ResourceNotFoundException("Product not found: " + id);
        }
        productRepository.deleteById(id);
    }
}
