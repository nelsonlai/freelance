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
import org.springframework.security.test.context.support.WithMockUser;
import org.springframework.test.web.servlet.MockMvc;

import java.math.BigDecimal;
import java.util.Optional;

import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.when;
import static org.springframework.security.test.web.servlet.request.SecurityMockMvcRequestPostProcessors.httpBasic;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;

/**
 * Controller (slice) tests for {@link ProductController}.
 * <p>
 * {@code @WebMvcTest(ProductController.class)} loads only the web layer and the specified controller;
 * no full application context. Dependencies (e.g. {@link ProductService}) must be mocked with
 * {@code @MockBean}. We use {@link MockMvc} to perform HTTP requests and assert status and JSON
 * without starting the real server. For authenticated endpoints we use {@code @WithMockUser} or
 * {@code .with(httpBasic("user", "password"))}.
 */
@WebMvcTest(ProductController.class)
class ProductControllerTest {

    /** MockMvc: perform GET/POST/etc. and assert response status and body (e.g. jsonPath). */
    @Autowired
    private MockMvc mockMvc;

    /** ObjectMapper for serializing request body to JSON (e.g. in POST). */
    @Autowired
    private ObjectMapper objectMapper;

    /** Mock service; controller is real, service is mocked so we control behavior. */
    @MockBean
    private ProductService productService;

    /**
     * GET /api/products/1 when product exists returns 200 OK and product JSON.
     * We stub productService.findById(1L) to return a product and assert status, id, name, price in response.
     * {@code @WithMockUser} provides a fake authenticated user so the request is allowed.
     */
    @Test
    @WithMockUser
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

    /**
     * GET /api/products/999 when product does not exist returns 404 Not Found.
     * We stub productService.findById(999L) to return Optional.empty().
     */
    @Test
    @WithMockUser
    void getById_whenNotExists_returns404() throws Exception {
        when(productService.findById(999L)).thenReturn(Optional.empty());

        mockMvc.perform(get("/api/products/999"))
            .andExpect(status().isNotFound());
    }

    /**
     * POST /api/products with HTTP Basic auth returns 201 Created, Location header, and product body.
     * We use .with(httpBasic("user", "password")) to simulate HTTP Basic; stub productService.create
     * to return the created product; assert status 201, Location header contains /api/products/1,
     * and response JSON has id and name.
     */
    @Test
    void create_withHttpBasic_returns201AndBody() throws Exception {
        ProductCreateRequest request = new ProductCreateRequest("Laptop", new BigDecimal("999"), 10);
        Product created = new Product();
        created.setId(1L);
        created.setName("Laptop");
        created.setPrice(new BigDecimal("999"));
        created.setStock(10);
        when(productService.create(any(ProductCreateRequest.class))).thenReturn(created);

        mockMvc.perform(post("/api/products")
                .with(httpBasic("user", "password"))
                .contentType(MediaType.APPLICATION_JSON)
                .content(objectMapper.writeValueAsString(request)))
            .andExpect(status().isCreated())
            .andExpect(header().string("Location", org.hamcrest.Matchers.containsString("/api/products/1")))
            .andExpect(jsonPath("$.id").value(1))
            .andExpect(jsonPath("$.name").value("Laptop"));
    }
}
