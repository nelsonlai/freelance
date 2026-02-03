# Module 12: Microservices Patterns with Spring Boot

**Level:** Advanced  
**Time:** ~75 minutes

---

## Learning Objectives

- Understand microservices in the context of Spring Boot
- Use Spring Cloud (optional) for service discovery and config
- Implement inter-service communication (HTTP client, resilience)
- Apply API gateway and observability concepts at a high level

---

## 12.1 Microservices in Short

- **Monolith:** One deployable application containing all features.
- **Microservices:** Many small services, each owning a bounded context, deployed and scaled independently.

Spring Boot is well-suited for implementing each service: stand-alone JARs, embedded server, and a rich ecosystem (Spring Cloud, Spring Cloud Netflix, etc.).

---

## 12.2 Building a Single Service (Recap)

Each microservice is typically:

- A Spring Boot application
- Owns its own data (database per service)
- Exposes REST (or gRPC) API
- Configured via environment and profiles
- Monitored via Actuator (health, metrics)

---

## 12.3 Inter-Service Communication

### HTTP Client (RestClient / RestTemplate / WebClient)

**RestClient (Spring 6.1+):**

```java
@Service
public class OrderService {

    private final RestClient orderClient;

    public OrderService(RestClient.Builder builder) {
        this.orderClient = builder
            .baseUrl("http://order-service:8080")
            .build();
    }

    public Order getOrder(Long id) {
        return orderClient.get()
            .uri("/api/orders/{id}", id)
            .retrieve()
            .body(Order.class);
    }
}
```

**WebClient (reactive, non-blocking):**

```java
@Service
public class OrderService {

    private final WebClient webClient;

    public OrderService(WebClient.Builder builder) {
        this.webClient = builder
            .baseUrl("http://order-service:8080")
            .build();
    }

    public Mono<Order> getOrder(Long id) {
        return webClient.get()
            .uri("/api/orders/{id}", id)
            .retrieve()
            .bodyToMono(Order.class);
    }
}
```

Base URL should come from configuration (e.g. `app.order-service.url`) or service discovery.

---

## 12.4 Resilience: Retry and Circuit Breaker

Failures and latency in other services should not bring down your service.

- **Retry:** Retry failed HTTP calls with backoff (e.g. Spring Retry, or resilience4j).
- **Circuit breaker:** After N failures, stop calling the downstream service for a period, then try again (e.g. Resilience4j, Spring Cloud Circuit Breaker).

**Resilience4j (conceptual):**

```java
@CircuitBreaker(name = "orderService", fallbackMethod = "getOrderFallback")
public Order getOrder(Long id) {
    return orderClient.get()
        .uri("/api/orders/{id}", id)
        .retrieve()
        .body(Order.class);
}

public Order getOrderFallback(Long id, Exception ex) {
    return Order.unknown(id);
}
```

Implementation details (dependency, configuration, and exact annotations) depend on the version of Spring Boot and the resilience library you use.

---

## 12.5 Service Discovery (Conceptual)

In a dynamic environment, service instances come and go. **Service discovery** lets clients find instances by name (e.g. “order-service”) instead of hard-coding URLs.

- **Client-side discovery:** Client asks a registry (e.g. Consul, Eureka) for instances and then calls one.
- **Server-side discovery:** A load balancer or API gateway resolves the service name; the client only calls the gateway.

Spring Cloud provides integration with Eureka, Consul, and others. You register your app with the discovery server and optionally use a client (e.g. `DiscoveryClient`) or a load-balanced `RestTemplate`/`WebClient` to resolve service names.

---

## 12.6 Centralized Configuration (Conceptual)

Spring Cloud Config provides a central server that serves configuration (e.g. from Git) to applications. Each application can have a profile-specific config (e.g. `myapp-prod.yml`). This is optional; many teams use environment variables and Kubernetes ConfigMaps instead.

---

## 12.7 API Gateway (Conceptual)

An **API Gateway** sits in front of multiple services and provides:

- Single entry point (e.g. `https://api.example.com`)
- Routing (e.g. `/orders/*` → order-service)
- Auth, rate limiting, logging

Spring Cloud Gateway is a reactive gateway built on Spring WebFlux. Each backend service remains a Spring Boot app; the gateway is another Spring Boot app that routes and optionally enforces security.

---

## 12.8 Observability

- **Logging:** Structured logs (e.g. JSON); correlate by trace id.
- **Metrics:** Actuator + Micrometer; export to Prometheus/Grafana.
- **Tracing:** Distributed tracing (e.g. Sleuth/Micrometer Tracing, Zipkin) to follow a request across services.

---

## 12.9 Summary

- **Microservices** = many small Spring Boot apps, each with its own API and data.
- **Communication:** HTTP via RestClient/WebClient; base URL from config or discovery.
- **Resilience:** Retry and circuit breaker for downstream calls.
- **Discovery:** Optional; use a registry (Eureka, Consul) or Kubernetes DNS.
- **Config:** Centralized (e.g. Spring Cloud Config) or env/Kubernetes.
- **Gateway:** Optional; Spring Cloud Gateway for routing and cross-cutting concerns.
- **Observability:** Logs, metrics, and tracing for production.

---

## Exercises

1. Create a second Spring Boot service “Product Service” that exposes GET /api/products. Call it from the first service via RestClient with base URL from application.properties.
2. Add a simple retry (e.g. Spring Retry or manual loop) when the Product Service call fails.
3. (Optional) Add Spring Cloud Config or use environment variables for the Product Service URL and verify the client uses it.
