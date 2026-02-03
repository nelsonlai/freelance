package com.example.demo.exception;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.MethodArgumentNotValidException;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;

import java.util.HashMap;
import java.util.Map;

/**
 * Global exception handler for REST controllers.
 * <p>
 * {@code @RestControllerAdvice} applies to all controllers. When an exception is thrown,
 * Spring invokes the matching {@code @ExceptionHandler} method and returns its response.
 * This keeps controllers thin and centralizes error response format (e.g. JSON with "message" and "errors").
 */
@RestControllerAdvice
public class GlobalExceptionHandler {

    /**
     * Handles validation failures on {@code @Valid} request body (e.g. missing name, invalid price).
     * Returns 400 Bad Request with a map of field names to error messages.
     *
     * @param ex the exception thrown when Bean Validation fails
     * @return ResponseEntity with status 400 and body { "message": "Validation failed", "errors": { "field": "msg" } }
     */
    @ExceptionHandler(MethodArgumentNotValidException.class)
    public ResponseEntity<Map<String, Object>> handleValidation(MethodArgumentNotValidException ex) {
        Map<String, String> errors = new HashMap<>();
        ex.getBindingResult().getFieldErrors().forEach(err ->
            errors.put(err.getField(), err.getDefaultMessage()));
        return ResponseEntity
            .status(HttpStatus.BAD_REQUEST)
            .body(Map.of("message", "Validation failed", "errors", errors));
    }

    /**
     * Handles {@link ResourceNotFoundException} (e.g. product not found by ID).
     * Returns 404 Not Found with the exception message in the body.
     *
     * @param ex the exception
     * @return ResponseEntity with status 404 and body { "message": ex.getMessage() }
     */
    @ExceptionHandler(ResourceNotFoundException.class)
    public ResponseEntity<Map<String, String>> handleNotFound(ResourceNotFoundException ex) {
        return ResponseEntity
            .status(HttpStatus.NOT_FOUND)
            .body(Map.of("message", ex.getMessage()));
    }

    /**
     * Handles {@link DuplicateResourceException} (e.g. product name already exists).
     * Returns 409 Conflict with the exception message in the body.
     *
     * @param ex the exception
     * @return ResponseEntity with status 409 and body { "message": ex.getMessage() }
     */
    @ExceptionHandler(DuplicateResourceException.class)
    public ResponseEntity<Map<String, String>> handleDuplicate(DuplicateResourceException ex) {
        return ResponseEntity
            .status(HttpStatus.CONFLICT)
            .body(Map.of("message", ex.getMessage()));
    }
}
