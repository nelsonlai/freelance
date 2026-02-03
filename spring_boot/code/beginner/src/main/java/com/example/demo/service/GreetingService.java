package com.example.demo.service;

import org.springframework.stereotype.Service;

/**
 * Service that generates greeting messages.
 * <p>
 * {@code @Service} is a stereotype of {@code @Component}; Spring registers this class as a bean
 * and injects it wherever needed (e.g. into {@link com.example.demo.controller.HelloController}).
 * Business logic that does not handle HTTP directly belongs in a service layer.
 */
@Service
public class GreetingService {

    /**
     * Builds a greeting string for the given name.
     *
     * @param name the name to include in the greeting (e.g. "Student")
     * @return greeting in the form "Hello, &lt;name&gt;!"
     */
    public String greet(String name) {
        return "Hello, " + name + "!";
    }
}
