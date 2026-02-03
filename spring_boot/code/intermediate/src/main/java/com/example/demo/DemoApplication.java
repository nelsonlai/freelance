package com.example.demo;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

/**
 * Main entry point for the Spring Boot intermediate demo application.
 * <p>
 * This application demonstrates REST APIs, Spring Data JPA, Spring Security, and configuration.
 * {@code @SpringBootApplication} enables component scanning, auto-configuration, and marks this class as configuration.
 */
@SpringBootApplication
public class DemoApplication {

    /**
     * Starts the Spring Application Context and embedded web server.
     *
     * @param args command-line arguments (e.g. --server.port=9090)
     */
    public static void main(String[] args) {
        SpringApplication.run(DemoApplication.class, args);
    }
}
