package com.example.demo.repository;

import com.example.demo.entity.Product;
import org.springframework.data.jpa.repository.JpaRepository;

import java.math.BigDecimal;
import java.util.List;

/**
 * Spring Data JPA repository for {@link com.example.demo.entity.Product}.
 * <p>
 * Extending {@link JpaRepository} provides standard CRUD methods (findById, save, delete, etc.)
 * without implementation. Method names follow the "derived query" convention: Spring generates
 * the query from the method name (e.g. findByNameContainingIgnoreCase → WHERE LOWER(name) LIKE %?%).
 */
public interface ProductRepository extends JpaRepository<Product, Long> {

    /**
     * Find all products whose name contains the given string (case-insensitive).
     * Generated query: WHERE LOWER(name) LIKE LOWER('%' || ?1 || '%')
     *
     * @param name the substring to search for (e.g. "laptop")
     * @return list of matching products
     */
    List<Product> findByNameContainingIgnoreCase(String name);

    /**
     * Find all products with price between min and max (inclusive).
     * Generated query: WHERE price BETWEEN ?1 AND ?2
     *
     * @param min minimum price
     * @param max maximum price
     * @return list of matching products
     */
    List<Product> findByPriceBetween(BigDecimal min, BigDecimal max);

    /**
     * Check whether a product with the given name already exists.
     * Generated query: SELECT COUNT(*) > 0 WHERE name = ?1
     *
     * @param name product name
     * @return true if a product with this name exists
     */
    boolean existsByName(String name);
}
