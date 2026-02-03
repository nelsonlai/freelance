# Module 8: Configuration & Profiles

**Level:** Intermediate  
**Time:** ~60 minutes

---

## Learning Objectives

- Use `application.properties` and `application.yml`
- Activate profiles (dev, test, prod) and profile-specific files
- Inject configuration with `@Value` and `@ConfigurationProperties`
- Understand externalized configuration and precedence

---

## 8.1 application.properties vs application.yml

Both live in `src/main/resources`. Spring Boot loads them automatically.

**application.properties:**

```properties
server.port=8080
spring.application.name=myapp
app.api.version=1.0
app.feature.enabled=true
```

**application.yml** (equivalent):

```yaml
server:
  port: 8080
spring:
  application:
    name: myapp
app:
  api:
    version: "1.0"
  feature:
    enabled: true
```

YAML is hierarchical and often easier to read; properties are flat. You can mix both; properties override YAML for the same key.

---

## 8.2 @Value

Inject a single property:

```java
@Component
public class ApiInfo {
    @Value("${app.api.version:1.0}")
    private String version;

    @Value("${app.feature.enabled:false}")
    private boolean featureEnabled;

    public String getVersion() { return version; }
    public boolean isFeatureEnabled() { return featureEnabled; }
}
```

- **${property.name}** — required; fails if missing.
- **${property.name:default}** — use default if missing.

---

## 8.3 @ConfigurationProperties

Bind a group of properties to a typed bean:

**application.yml:**

```yaml
app:
  api:
    version: "1.0"
    title: "My API"
  feature:
    enabled: true
  limits:
    maxPageSize: 100
```

**Java:**

```java
package com.example.demo.config;

import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.stereotype.Component;

@Component
@ConfigurationProperties(prefix = "app")
public class AppProperties {

    private Api api = new Api();
    private Feature feature = new Feature();
    private Limits limits = new Limits();

    public static class Api {
        private String version = "1.0";
        private String title = "My API";
        // getters and setters
        public String getVersion() { return version; }
        public void setVersion(String version) { this.version = version; }
        public String getTitle() { return title; }
        public void setTitle(String title) { this.title = title; }
    }

    public static class Feature {
        private boolean enabled = false;
        public boolean isEnabled() { return enabled; }
        public void setEnabled(boolean enabled) { this.enabled = enabled; }
    }

    public static class Limits {
        private int maxPageSize = 50;
        public int getMaxPageSize() { return maxPageSize; }
        public void setMaxPageSize(int maxPageSize) { this.maxPageSize = maxPageSize; }
    }

    public Api getApi() { return api; }
    public void setApi(Api api) { this.api = api; }
    public Feature getFeature() { return feature; }
    public void setFeature(Feature feature) { this.feature = feature; }
    public Limits getLimits() { return limits; }
    public void setLimits(Limits limits) { this.limits = limits; }
}
```

Use `AppProperties` by injecting it; supports validation (`@Validated` + `@NotNull`, etc.) and IDE completion when using the spring-boot-configuration-processor dependency.

---

## 8.4 Profiles

Profiles let you switch configuration per environment (dev, test, prod).

**Activate a profile:**

- **application.properties:** `spring.profiles.active=dev`
- **Environment variable:** `SPRING_PROFILES_ACTIVE=prod`
- **Command line:** `--spring.profiles.active=prod`
- **IDE:** Run configuration → Active profiles: `dev`

**Profile-specific files:**

- `application.properties` — base
- `application-dev.properties` — when profile `dev` is active
- `application-prod.properties` — when profile `prod` is active

Spring loads `application.properties` first, then `application-{profile}.properties`; profile-specific overrides base.

**YAML:** You can also use a single file with profile blocks:

```yaml
server:
  port: 8080
---
spring:
  config:
    activate:
      on-profile: dev
server:
  port: 8081
logging:
  level:
    root: DEBUG
---
spring:
  config:
    activate:
      on-profile: prod
server:
  port: 8080
logging:
  level:
    root: WARN
```

---

## 8.5 Externalized Configuration (Precedence)

Spring Boot loads configuration in this order (higher overrides lower):

1. Command-line arguments
2. Environment variables
3. `application-{profile}.properties` / `.yml` (e.g. in current directory or classpath)
4. `application.properties` / `.yml` (current directory or classpath)
5. Defaults in code

So you can override `server.port` with `SERVER_PORT` or `--server.port` without changing the file. Good for 12-factor apps and containers.

---

## 8.6 Sensitive Data

- **Never** commit secrets to Git. Use environment variables or a secret manager.
- **Spring:** Use env vars (e.g. `SPRING_DATASOURCE_PASSWORD`) or place a local `application-local.properties` (gitignored) that overrides defaults.

---

## 8.7 Summary

- **application.properties / application.yml** — base configuration; profile-specific files override.
- **@Value** — inject a single property with optional default.
- **@ConfigurationProperties** — bind a prefix to a bean; good for structured config.
- **Profiles** — `spring.profiles.active` and `application-{profile}.properties`.
- **Precedence** — command line and env vars override files.

---

## Exercises

1. Create `application-dev.properties` and `application-prod.properties` with different `server.port` and `logging.level.root`; run with each profile.
2. Define an `app.greeting` property and inject it with `@Value` in a controller.
3. Create a `@ConfigurationProperties(prefix = "app.mail")` class and use it in a service (e.g. to read smtp host and port).
