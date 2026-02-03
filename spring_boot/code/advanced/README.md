# Spring Boot Advanced Code

Corresponds to **Modules 9–12** (Testing, Actuator, Production Deployment, Microservices patterns).

Extends the intermediate project with:

- **Actuator** — health, info, metrics
- **Custom health indicator** — `CustomHealthIndicator`
- **Unit tests** — `ProductServiceTest` (Mockito)
- **Controller tests** — `ProductControllerTest` (MockMvc, @WebMvcTest)
- **Production profile** — `application-prod.properties` (validate, WARN logging)
- **Dockerfile** — multi-stage build

## Run

```bash
./mvnw spring-boot:run
```

With production profile:

```bash
./mvnw spring-boot:run -Dspring-boot.run.profiles=prod
```

## Actuator Endpoints

- **GET /actuator/health** — health (no auth)
- **GET /actuator/info** — info (no auth)
- **GET /actuator/metrics** — metrics (auth: user/password)

## Tests

```bash
./mvnw test
```

## Build JAR and Run

```bash
./mvnw clean package -DskipTests
java -jar target/spring-boot-advanced-1.0.0-SNAPSHOT.jar
```

## Docker

```bash
# Copy Maven wrapper from intermediate or generate project with wrapper
cp -r ../intermediate/.mvn . 2>/dev/null || true
cp ../intermediate/mvnw . 2>/dev/null || true
chmod +x mvnw

docker build -t spring-boot-advanced:latest .
docker run -p 8080:8080 -e SPRING_PROFILES_ACTIVE=prod spring-boot-advanced:latest
```

Note: If `.mvn` and `mvnw` are missing, generate them with `mvn wrapper:wrapper` from the project root (with Maven installed) or copy from the intermediate project.
