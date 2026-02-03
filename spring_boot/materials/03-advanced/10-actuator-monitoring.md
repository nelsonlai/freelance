# Module 10: Actuator & Monitoring

**Level:** Advanced  
**Time:** ~60 minutes

---

## Learning Objectives

- Add Spring Boot Actuator and expose endpoints
- Use health, info, metrics, and env endpoints
- Secure actuator endpoints and customize health
- Understand production monitoring practices

---

## 10.1 Dependencies

**Maven:**

```xml
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-actuator</artifactId>
</dependency>
```

**Gradle:**

```groovy
implementation 'org.springframework.boot:spring-boot-starter-actuator'
```

By default, only **/actuator/health** is exposed over HTTP (and often only a simple status). You configure which endpoints are exposed and whether they show details.

---

## 10.2 Exposing Endpoints

**application.properties / application.yml:**

```properties
# Expose health and info over HTTP (default for 3.x: health only)
management.endpoints.web.exposure.include=health,info,metrics,env

# Show full health details (e.g. DB status)
management.endpoint.health.show-details=when-authorized
# Or for dev: management.endpoint.health.show-details=always
```

- **management.endpoints.web.exposure.include** — comma-separated list: health, info, metrics, env, beans, configprops, etc.
- **management.endpoint.health.show-details** — `never`, `when-authorized`, `always`.

**Common endpoints:**

| Endpoint | Purpose |
|----------|---------|
| /actuator/health | Application and dependency health (DB, disk, etc.) |
| /actuator/info | Custom app info (version, git, etc.) |
| /actuator/metrics | Metrics (JVM, HTTP, custom) |
| /actuator/env | Environment and configuration properties |
| /actuator/beans | All Spring beans (sensitive; restrict in prod) |

---

## 10.3 Health Indicator

**GET /actuator/health** returns status (UP/DOWN) and, when details are shown, sub-components (e.g. db, diskSpace).

Custom health indicator:

```java
package com.example.demo.actuator;

import org.springframework.boot.actuate.health.Health;
import org.springframework.boot.actuate.health.HealthIndicator;
import org.springframework.stereotype.Component;

@Component
public class CustomHealthIndicator implements HealthIndicator {

    @Override
    public Health health() {
        // Check something (e.g. external API, cache)
        boolean ok = checkSomething();
        if (ok) {
            return Health.up().withDetail("custom", "OK").build();
        }
        return Health.down().withDetail("custom", "Failed").build();
    }

    private boolean checkSomething() {
        return true;
    }
}
```

---

## 10.4 Info Endpoint

**GET /actuator/info** — add custom info via properties or an `InfoContributor`:

**application.properties:**

```properties
info.app.name=My API
info.app.version=1.0.0
info.app.description=Demo API for teaching
```

**Java (dynamic info):**

```java
package com.example.demo.actuator;

import org.springframework.boot.actuate.info.Info;
import org.springframework.boot.actuate.info.InfoContributor;
import org.springframework.stereotype.Component;

import java.util.Map;

@Component
public class CustomInfoContributor implements InfoContributor {

    @Override
    public void contribute(Info.Builder builder) {
        builder.withDetail("custom", Map.of(
            "author", "Training Team",
            "environment", System.getenv().getOrDefault("ENV", "dev")
        ));
    }
}
```

---

## 10.5 Metrics

**GET /actuator/metrics** lists metric names.  
**GET /actuator/metrics/jvm.memory.used** (example) returns the metric value.

**Custom metric:**

```java
package com.example.demo.actuator;

import io.micrometer.core.instrument.Counter;
import io.micrometer.core.instrument.MeterRegistry;
import org.springframework.stereotype.Component;

@Component
public class OrderMetrics {

    private final Counter orderCreatedCounter;

    public OrderMetrics(MeterRegistry registry) {
        this.orderCreatedCounter = Counter.builder("orders.created")
            .description("Total orders created")
            .register(registry);
    }

    public void recordOrderCreated() {
        orderCreatedCounter.increment();
    }
}
```

Inject `OrderMetrics` in your service and call `recordOrderCreated()` when an order is created. Then check **GET /actuator/metrics/orders.created**.

---

## 10.6 Securing Actuator in Production

- **Expose only what you need:** e.g. `health` and `info` for a load balancer; restrict `env`, `beans`, `configprops`.
- **Restrict by role:** Use Spring Security so only admins can access sensitive endpoints:

```java
requestMatchers("/actuator/**").hasRole("ACTUATOR_ADMIN")
```

- **Change base path:** `management.endpoints.web.base-path=/manage` so actuator is under `/manage` (optional).
- **Show health details:** Use `when-authorized` and protect `/actuator/health` if you expose details.

---

## 10.7 Summary

- **Actuator** — production-ready health, info, metrics, and env.
- **Exposure** — `management.endpoints.web.exposure.include`; restrict in production.
- **Health** — built-in indicators + custom `HealthIndicator`.
- **Info** — `info.*` properties + `InfoContributor`.
- **Metrics** — Micrometer; use `MeterRegistry` for custom metrics.
- **Security** — limit exposed endpoints and secure with Spring Security.

---

## Exercises

1. Add actuator, expose health and info, and call /actuator/health and /actuator/info.
2. Add a custom health indicator that checks a simple condition (e.g. a flag or time).
3. Add a counter metric that increments on each request to a specific endpoint and verify it in /actuator/metrics.
