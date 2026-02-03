package com.example.demo.exception;

/**
 * Thrown when a requested resource (e.g. product by ID) does not exist.
 * <p>
 * Handled by {@link GlobalExceptionHandler} to return HTTP 404 Not Found with a JSON body
 * containing the exception message.
 */
public class ResourceNotFoundException extends RuntimeException {

    /**
     * @param message human-readable message (e.g. "Product not found: 123")
     */
    public ResourceNotFoundException(String message) {
        super(message);
    }
}
