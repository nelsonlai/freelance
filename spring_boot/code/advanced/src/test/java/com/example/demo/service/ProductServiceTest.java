package com.example.demo.service;

import com.example.demo.dto.ProductCreateRequest;
import com.example.demo.dto.ProductUpdateRequest;
import com.example.demo.entity.Product;
import com.example.demo.exception.DuplicateResourceException;
import com.example.demo.exception.ResourceNotFoundException;
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

/**
 * Unit tests for {@link ProductService}.
 * <p>
 * Uses JUnit 5 and Mockito. {@code @ExtendWith(MockitoExtension.class)} enables Mockito annotations.
 * {@code @Mock} creates a mock for {@link ProductRepository}; {@code @InjectMocks} creates a real
 * {@link ProductService} and injects the mock repository. We stub repository behavior with
 * {@code when(...).thenReturn(...)} and verify calls with {@code verify(...)}.
 */
@ExtendWith(MockitoExtension.class)
class ProductServiceTest {

    /** Mock repository; we control its behavior in each test. */
    @Mock
    private ProductRepository productRepository;

    /** Real ProductService with the mock repository injected. */
    @InjectMocks
    private ProductService productService;

    /**
     * When a product exists for the given ID, findById returns it.
     * We stub productRepository.findById(1L) to return an Optional of a product, then assert
     * that the service returns the same product and that findById was called once.
     */
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

    /**
     * When no product exists for the given ID, findById returns empty Optional.
     * We stub productRepository.findById(999L) to return Optional.empty().
     */
    @Test
    void findById_whenNotExists_returnsEmpty() {
        when(productRepository.findById(999L)).thenReturn(Optional.empty());

        Optional<Product> result = productService.findById(999L);

        assertThat(result).isEmpty();
    }

    /**
     * When creating a product with a name that already exists, create throws DuplicateResourceException.
     * We stub existsByName to return true and assert that save is never called.
     */
    @Test
    void create_whenNameExists_throwsDuplicateResourceException() {
        ProductCreateRequest request = new ProductCreateRequest("Laptop", new BigDecimal("999"), 10);
        when(productRepository.existsByName("Laptop")).thenReturn(true);

        assertThatThrownBy(() -> productService.create(request))
            .isInstanceOf(DuplicateResourceException.class)
            .hasMessageContaining("already exists");

        verify(productRepository, never()).save(any());
    }

    /**
     * When creating a product with a unique name, create saves and returns the product.
     * We stub existsByName to false and save to return a persisted product; then assert
     * the returned product and that save was called once.
     */
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

    /**
     * When updating a product that does not exist, update throws ResourceNotFoundException.
     * We stub findById to return Optional.empty() and assert the exception message contains the ID.
     */
    @Test
    void update_whenNotExists_throwsResourceNotFoundException() {
        ProductUpdateRequest request = new ProductUpdateRequest();
        request.setName("Laptop");
        request.setPrice(new BigDecimal("999"));
        request.setStock(10);
        when(productRepository.findById(999L)).thenReturn(Optional.empty());

        assertThatThrownBy(() -> productService.update(999L, request))
            .isInstanceOf(ResourceNotFoundException.class)
            .hasMessageContaining("999");
    }
}
