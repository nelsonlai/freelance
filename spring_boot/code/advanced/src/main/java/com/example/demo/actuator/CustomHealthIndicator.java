package com.example.demo.actuator;

import org.springframework.boot.actuate.health.Health;
import org.springframework.boot.actuate.health.HealthIndicator;
import org.springframework.stereotype.Component;

/**
 * Custom Spring Boot Actuator health indicator.
 * <p>
 * Implementations of {@link HealthIndicator} are automatically picked up by Actuator and
 * included in the /actuator/health response under a key derived from the bean name
 * (e.g. "customHealthIndicator" → "custom" when using the default naming).
 * Use this to report health of external dependencies (e.g. a cache, another service) or
 * application-specific checks. Here we use a trivial check for demonstration.
 */
@Component
public class CustomHealthIndicator implements HealthIndicator {

    /**
     * Returns the health status. If the check passes, return {@link Health#up()} with optional details;
     * otherwise return {@link Health#down()} so the overall /actuator/health can report DOWN.
     *
     * @return Health with status UP or DOWN and optional detail "custom"
     */
    @Override
    public Health health() {
        boolean ok = checkCustomCondition();
        if (ok) {
            return Health.up().withDetail("custom", "OK").build();
        }
        return Health.down().withDetail("custom", "Failed").build();
    }

    /**
     * Placeholder for a real check (e.g. ping an external service, verify a flag).
     * In production you might check connectivity to a cache, message broker, or another API.
     *
     * @return true if the custom condition is satisfied
     */
    private boolean checkCustomCondition() {
        return true;
    }
}
