# Module 4: Core Concepts — IoC, DI, and Auto-Configuration

**Level:** Beginner  
**Time:** ~75 minutes

---

## Learning Objectives

- Explain Inversion of Control (IoC) and the Spring container
- Use Dependency Injection (DI) via constructor injection
- Understand stereotypes: `@Component`, `@Service`, `@Controller`, `@Repository`
- Describe how auto-configuration works at a high level

---

## 4.1 Inversion of Control (IoC)

### Traditional Flow

Your code creates and configures dependencies:

```java
public class OrderService {
    private final EmailSender emailSender = new EmailSender();
    private final PaymentGateway gateway = new PaymentGateway();

    public void placeOrder(Order order) {
        // ...
        emailSender.send(...);
        gateway.charge(...);
    }
}
```

Problems: tight coupling, hard to test (can’t replace `EmailSender`), creation logic scattered.

### IoC Flow

A **container** (Spring) creates and injects dependencies. Your code *receives* them:

```java
@Service
public class OrderService {
    private final EmailSender emailSender;
    private final PaymentGateway gateway;

    public OrderService(EmailSender emailSender, PaymentGateway gateway) {
        this.emailSender = emailSender;
        this.gateway = gateway;
    }

    public void placeOrder(Order order) {
        // ...
        emailSender.send(...);
        gateway.charge(...);
    }
}
```

Control of *what* is created and *when* is “inverted” to the container. Your classes stay focused on behavior.

---

## 4.2 The Spring Container (ApplicationContext)

- Spring’s **IoC container** is the `ApplicationContext`.
- It **creates** objects (beans), **wires** dependencies, and **manages** their lifecycle.
- Beans are registered by:
  - Component scanning (`@Component` and related annotations)
  - Configuration classes (`@Configuration` + `@Bean`)

Spring Boot starts the context when you run the main class; it scans your packages and loads auto-configuration.

---

## 4.3 Dependency Injection (DI)

**Dependency Injection** = the container provides (“injects”) dependencies into your class.

### Constructor injection (recommended)

```java
@Service
public class OrderService {
    private final OrderRepository orderRepository;

    public OrderService(OrderRepository orderRepository) {
        this.orderRepository = orderRepository;
    }
}
```

- Dependencies are `final` and set once.
- Clear and test-friendly (you pass mocks in tests).

### Setter injection (optional dependencies)

```java
@Autowired
public void setNotifier(OrderNotifier notifier) {
    this.notifier = notifier;
}
```

Use when the dependency is optional or might change. Prefer constructor injection for required dependencies.

### Field injection (avoid in new code)

```java
@Autowired
private OrderRepository orderRepository;
```

Discouraged: harder to test and to see required dependencies.

---

## 4.4 Stereotype Annotations (Component Scanning)

Spring discovers classes that are annotated with:

| Annotation | Meaning | Typical use |
|------------|---------|-------------|
| `@Component` | Generic bean | Any Spring-managed component |
| `@Service` | Business logic | Service layer |
| `@Repository` | Data access | DAOs, JPA repositories |
| `@Controller` | Web MVC controller | Pages, redirects |
| `@RestController` | REST API | REST controllers (Controller + ResponseBody) |

All of these are **stereotypes** of `@Component`; they are scanned and registered as beans.

Example:

```java
@Service
public class GreetingService {
    public String greet(String name) {
        return "Hello, " + name + "!";
    }
}
```

```java
@RestController
public class GreetingController {
    private final GreetingService greetingService;

    public GreetingController(GreetingService greetingService) {
        this.greetingService = greetingService;
    }

    @GetMapping("/greet")
    public String greet(@RequestParam String name) {
        return greetingService.greet(name);
    }
}
```

Spring creates `GreetingService` and `GreetingController` and injects `GreetingService` into the controller.

---

## 4.5 @Configuration and @Bean

When you need to define beans explicitly (e.g. third-party classes, or custom configuration):

```java
@Configuration
public class AppConfig {

    @Bean
    public Clock clock() {
        return Clock.systemDefaultZone();
    }

    @Bean
    public MyService myService(Clock clock) {
        return new MyService(clock);
    }
}
```

- `@Configuration` — class that defines beans.
- `@Bean` — method return value is registered as a bean; method parameters are injected.

---

## 4.6 Auto-Configuration (High Level)

Spring Boot’s **auto-configuration** adds beans based on:

- **Classpath:** e.g. if `spring-boot-starter-web` is present, MVC and embedded Tomcat are configured.
- **Existing beans:** e.g. if no `DataSource` bean is defined but H2 is on classpath, a DataSource can be created.
- **Properties:** e.g. `server.port` changes the embedded server port.

Conditional annotations (e.g. `@ConditionalOnClass`, `@ConditionalOnMissingBean`) drive this. You don’t need to write those yourself; the important idea is: “Spring Boot configures things for you by default; you override when needed.”

---

## 4.7 Summary

- **IoC:** The container controls creation and wiring of objects.
- **DI:** Dependencies are injected (prefer constructor injection).
- **Stereotypes:** `@Component`, `@Service`, `@Repository`, `@Controller`, `@RestController` make classes into beans.
- **@Configuration + @Bean:** For explicit bean definitions.
- **Auto-configuration:** Spring Boot configures beans based on classpath and configuration.

---

## Exercises

1. Create a `CalculatorService` with a method `add(int a, int b)` and inject it into a REST controller that exposes `/add?a=1&b=2`.
2. Define a `@Bean` that returns a `String` (e.g. app name) and inject it into a controller.
3. Explain in one sentence why constructor injection is preferred over field injection for required dependencies.
