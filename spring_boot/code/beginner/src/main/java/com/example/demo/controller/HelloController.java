package com.example.demo.controller;

import com.example.demo.dto.AppInfo;
import com.example.demo.service.GreetingService;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

/**
 * REST controller for simple hello-world and info endpoints.
 * <p>
 * {@code @RestController} combines {@code @Controller} and {@code @ResponseBody}:
 * return values of handler methods are written directly to the HTTP response body
 * (e.g. as JSON when the return type is an object, thanks to Jackson on the classpath).
 * <p>
 * Spring injects {@link GreetingService} via constructor (dependency injection).
 */
@RestController
public class HelloController {

    /** Injected by Spring; used for the /greet endpoint. */
    private final GreetingService greetingService;

    /**
     * Constructor injection: Spring provides a {@link GreetingService} bean when creating this controller.
     * Prefer constructor injection for required dependencies (clear, testable, immutable).
     */
    public HelloController(GreetingService greetingService) {
        this.greetingService = greetingService;
    }

    /**
     * GET /hello — returns a plain text greeting.
     * Example: {@code GET http://localhost:8080/hello}
     *
     * @return fixed string "Hello, Spring Boot!"
     */
    @GetMapping("/hello")
    public String hello() {
        return "Hello, Spring Boot!";
    }

    /**
     * GET /info — returns application metadata as JSON.
     * Spring (Jackson) serializes the {@link AppInfo} object to JSON automatically.
     * Example: {@code GET http://localhost:8080/info}
     *
     * @return application info (name, version, status)
     */
    @GetMapping("/info")
    public AppInfo info() {
        return new AppInfo("Demo", "1.0", "running");
    }

    /**
     * GET /greet — returns a greeting for the given name (query parameter).
     * If "name" is omitted, defaults to "World" via {@code @RequestParam(defaultValue = "World")}.
     * Example: {@code GET http://localhost:8080/greet?name=Student}
     *
     * @param name the name to greet (optional; default "World")
     * @return greeting string, e.g. "Hello, Student!"
     */
    @GetMapping("/greet")
    public String greet(@RequestParam(defaultValue = "World") String name) {
        return greetingService.greet(name);
    }
}
