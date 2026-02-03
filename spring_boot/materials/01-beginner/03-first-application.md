# Module 3: Your First Application

**Level:** Beginner  
**Time:** ~60 minutes

---

## Learning Objectives

- Understand the default project structure
- Know the role of the main class and `@SpringBootApplication`
- Create a simple REST controller and return JSON
- Use `application.properties` for basic configuration

---

## 3.1 Project Structure

After generating from Spring Initializr you typically have:

```
demo/
├── src/
│   ├── main/
│   │   ├── java/
│   │   │   └── com/example/demo/
│   │   │       └── DemoApplication.java    ← Main class
│   │   └── resources/
│   │       ├── application.properties      ← Config
│   │       ├── static/                     ← CSS, JS, images
│   │       └── templates/                  ← View templates (if used)
│   └── test/
│       └── java/
│           └── com/example/demo/
│               └── DemoApplicationTests.java
├── pom.xml   (or build.gradle)
└── mvnw / gradlew (wrappers)
```

- **`src/main/java`** — application code
- **`src/main/resources`** — config, static files, templates
- **`src/test/java`** — tests

---

## 3.2 The Main Class

Example:

```java
package com.example.demo;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class DemoApplication {

    public static void main(String[] args) {
        SpringApplication.run(DemoApplication.class, args);
    }
}
```

### What `@SpringBootApplication` Does

It is a *composition* of three annotations:

1. **`@SpringBootConfiguration`** — marks this class as a configuration source (like `@Configuration`).
2. **`@EnableAutoConfiguration`** — enables Spring Boot auto-configuration (e.g. embedded server, default MVC config).
3. **`@ComponentScan`** — scans the package of this class and sub-packages for `@Component`, `@Service`, `@Controller`, etc.

So the class that has `@SpringBootApplication` is both the entry point and the root of component scanning.

---

## 3.3 Your First REST Controller

Create a new class in the same package (or a sub-package, e.g. `controller`):

```java
package com.example.demo.controller;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class HelloController {

    @GetMapping("/hello")
    public String hello() {
        return "Hello, Spring Boot!";
    }
}
```

- **`@RestController`** — combines `@Controller` and `@ResponseBody`: return values are written directly to the HTTP response (e.g. JSON or plain text).
- **`@GetMapping("/hello")** — maps HTTP GET requests for `/hello` to this method.

Run the application and open: **http://localhost:8080/hello**  
You should see: `Hello, Spring Boot!`

---

## 3.4 Returning JSON

Return an object; Spring (with Jackson on the classpath) serializes it to JSON:

```java
package com.example.demo.controller;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.Map;

@RestController
public class HelloController {

    @GetMapping("/hello")
    public String hello() {
        return "Hello, Spring Boot!";
    }

    @GetMapping("/info")
    public Map<String, Object> info() {
        return Map.of(
            "application", "Demo",
            "version", "1.0",
            "status", "running"
        );
    }
}
```

Request: **GET http://localhost:8080/info**  
Response (example): `{"application":"Demo","version":"1.0","status":"running"}`

---

## 3.5 Using a DTO (Data Transfer Object)

For a clearer API, use a dedicated class:

```java
package com.example.demo.dto;

public class AppInfo {
    private String application;
    private String version;
    private String status;

    public AppInfo(String application, String version, String status) {
        this.application = application;
        this.version = version;
        this.status = status;
    }

    // Getters and setters (required for JSON serialization)
    public String getApplication() { return application; }
    public void setApplication(String application) { this.application = application; }
    public String getVersion() { return version; }
    public void setVersion(String version) { this.version = version; }
    public String getStatus() { return status; }
    public void setStatus(String status) { this.status = status; }
}
```

Controller:

```java
@GetMapping("/info")
public AppInfo info() {
    return new AppInfo("Demo", "1.0", "running");
}
```

---

## 3.6 Configuration: application.properties

In `src/main/resources/application.properties` you can override defaults:

```properties
# Server
server.port=8080

# Application name (used in Actuator, logging)
spring.application.name=demo

# Custom property (we can inject this later)
app.welcome.message=Welcome to our API!
```

Change `server.port`, restart, and verify the app listens on the new port.

---

## 3.7 Summary

- **Main class:** `@SpringBootApplication` + `SpringApplication.run(...)`.
- **REST endpoint:** `@RestController` + `@GetMapping` (or other `@*Mapping`) methods.
- **JSON:** Return objects; Spring uses Jackson to serialize to JSON.
- **Config:** `application.properties` in `src/main/resources`.

---

## Exercises

1. Add a GET endpoint `/greet?name=YourName` that returns `"Hello, YourName!"`.
2. Create a small DTO (e.g. `Product` with id, name, price) and an endpoint that returns one product as JSON.
3. Move the welcome message to `application.properties` and inject it into a controller to return it from an endpoint.
