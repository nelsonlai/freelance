package com.example.demo;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

/**
 * Main entry point for the Spring Boot advanced demo application.
 * <p>
 * This application extends the intermediate demo with Actuator (health, info, metrics),
 * unit and controller tests, production profile, and Docker support.
 */
@SpringBootApplication
public class DemoApplication {

    /**
     * Starts the Spring Application Context and embedded web server.
     *
     * @param args command-line arguments (e.g. --spring.profiles.active=prod)
     */
    public static void main(String[] args) {
        SpringApplication.run(DemoApplication.class, args);
    }
}
