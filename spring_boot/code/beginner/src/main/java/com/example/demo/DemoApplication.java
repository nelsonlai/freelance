package com.example.demo;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

/**
 * Main entry point for the Spring Boot beginner demo application.
 * <p>
 * {@code @SpringBootApplication} is a convenience annotation that combines:
 * <ul>
 *   <li>{@code @SpringBootConfiguration} — marks this class as a configuration source (like {@code @Configuration})</li>
 *   <li>{@code @EnableAutoConfiguration} — enables Spring Boot's auto-configuration (e.g. embedded Tomcat, default MVC setup)</li>
 *   <li>{@code @ComponentScan} — scans this package and sub-packages for {@code @Component}, {@code @Service}, {@code @Controller}, etc.</li>
 * </ul>
 * The class that bears this annotation is both the application entry point and the root of component scanning.
 */
@SpringBootApplication
public class DemoApplication {

    /**
     * Starts the Spring Application Context and embedded web server.
     * Spring creates beans, wires dependencies, and listens on the configured port (default 8080).
     *
     * @param args command-line arguments (can override properties, e.g. --server.port=9090)
     */
    public static void main(String[] args) {
        SpringApplication.run(DemoApplication.class, args);
    }
}
