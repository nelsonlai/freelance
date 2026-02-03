package com.example.demo.exception;

/**
 * Thrown when creating or updating a resource would violate a uniqueness constraint
 * (e.g. product name already exists).
 * <p>
 * Handled by {@link GlobalExceptionHandler} to return HTTP 409 Conflict with a JSON body
 * containing the exception message.
 */
public class DuplicateResourceException extends RuntimeException {

    /**
     * @param message human-readable message (e.g. "Product name already exists")
     */
    public DuplicateResourceException(String message) {
        super(message);
    }
}
