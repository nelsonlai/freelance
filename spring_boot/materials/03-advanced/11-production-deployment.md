# Module 11: Production Deployment

**Level:** Advanced  
**Time:** ~60 minutes

---

## Learning Objectives

- Build a production-ready executable JAR
- Configure for production (profiles, external config, logging)
- Understand containerization with Docker
- Apply basic production best practices (health, security, no default passwords)

---

## 11.1 Building the Executable JAR

Spring Boot packages the application and embedded server into a single “fat” JAR.

**Maven:**

```bash
./mvnw clean package -DskipTests
```

**Gradle:**

```bash
./gradlew clean bootJar
```

Output: **target/demo-0.0.1-SNAPSHOT.jar** (Maven) or **build/libs/demo-0.0.1-SNAPSHOT.jar** (Gradle).

**Run:**

```bash
java -jar target/demo-0.0.1-SNAPSHOT.jar
```

You can override config:

```bash
java -jar demo.jar --server.port=9090
java -jar demo.jar --spring.profiles.active=prod
```

---

## 11.2 Production Configuration

- **Profile:** Use `prod` (or `production`) profile: `--spring.profiles.active=prod` or `SPRING_PROFILES_ACTIVE=prod`.
- **Datasource:** Set via environment variables or external `application-prod.properties` (not in Git):
  - `SPRING_DATASOURCE_URL`, `SPRING_DATASOURCE_USERNAME`, `SPRING_DATASOURCE_PASSWORD`
- **JPA/Hibernate:** Use `spring.jpa.hibernate.ddl-auto=validate` or `none` in production (never `create-drop` or `update` in prod unless you have a controlled process).
- **Logging:** Reduce noise; use `logging.level.root=WARN` and set specific packages (e.g. your app) to INFO or DEBUG as needed.
- **Secrets:** Never commit passwords; use env vars or a secret manager (e.g. Kubernetes Secrets, AWS Secrets Manager).

---

## 11.3 Docker

**Dockerfile (multi-stage, small image):**

```dockerfile
# Build stage
FROM eclipse-temurin:21-jdk-alpine AS build
WORKDIR /app

COPY mvnw .
COPY .mvn .mvn
COPY pom.xml .
RUN ./mvnw dependency:go-offline -B

COPY src src
RUN ./mvnw package -DskipTests -B

# Run stage
FROM eclipse-temurin:21-jre-alpine
WORKDIR /app

RUN addgroup -S spring && adduser -S spring -G spring
USER spring:spring

COPY --from=build /app/target/*.jar app.jar

EXPOSE 8080
ENTRYPOINT ["java", "-jar", "app.jar"]
```

**Gradle variant:** Copy `build.gradle`, run `./gradlew bootJar`, then copy `build/libs/*.jar` into the run stage.

**Run locally:**

```bash
docker build -t demo:latest .
docker run -p 8080:8080 -e SPRING_PROFILES_ACTIVE=prod demo:latest
```

---

## 11.4 Health Check in Production

- Expose **/actuator/health** (and optionally **/actuator/info**).
- Use it for:
  - Load balancer / Kubernetes liveness and readiness probes
  - Orchestrator restarts when health is DOWN
- Prefer **when-authorized** for health details and protect actuator with Spring Security so only ops can see details.

---

## 11.5 Checklist (Summary)

- [ ] Build executable JAR with `package` / `bootJar`.
- [ ] Use a dedicated production profile and external config.
- [ ] Set datasource and all secrets via environment (or secret manager).
- [ ] Set `ddl-auto=validate` (or `none`) for JPA.
- [ ] No default passwords; disable or change default actuator/user accounts.
- [ ] Expose only needed actuator endpoints; secure them.
- [ ] Configure logging (level, format) for production.
- [ ] Run as non-root in Docker; use a specific user.
- [ ] Use health endpoint for orchestration (Kubernetes, ECS, etc.).

---

## Exercises

1. Build the JAR, run it with `--spring.profiles.active=prod`, and set the port via `--server.port=9090`.
2. Create `application-prod.properties` with `logging.level.root=WARN` and `spring.jpa.hibernate.ddl-auto=validate`; run with prod profile.
3. Write a Dockerfile for your app and run it with `docker run -p 8080:8080`.
