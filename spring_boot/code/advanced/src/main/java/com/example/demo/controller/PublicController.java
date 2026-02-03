package com.example.demo.controller;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.Map;

/**
 * Controller for public (unauthenticated) endpoints.
 * <p>
 * These paths are configured as {@code permitAll()} in {@link com.example.demo.config.SecurityConfig},
 * so no HTTP Basic or form login is required. Useful for health checks, status pages, or public info.
 */
@RestController
@RequestMapping("/api/public")
public class PublicController {

    /**
     * GET /api/public/health — simple health check (no auth).
     * Returns a minimal JSON body with status "UP". Can be used by load balancers or monitoring.
     *
     * @return map with key "status" and value "UP"
     */
    @GetMapping("/health")
    public Map<String, String> health() {
        return Map.of("status", "UP");
    }
}
