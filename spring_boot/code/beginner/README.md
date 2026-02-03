# Spring Boot Beginner Code

Corresponds to **Modules 1–4** (What is Spring Boot, Setup, First Application, Core Concepts).

## Run

```bash
./mvnw spring-boot:run
```

## Endpoints

- **GET http://localhost:8080/hello** — plain text
- **GET http://localhost:8080/info** — JSON (AppInfo)
- **GET http://localhost:8080/greet?name=Student** — uses GreetingService

## Structure

- `DemoApplication.java` — main class with `@SpringBootApplication`
- `controller/HelloController.java` — REST controller with `@RestController`, `@GetMapping`
- `dto/AppInfo.java` — DTO for JSON response
- `service/GreetingService.java` — service with constructor injection (DI)
