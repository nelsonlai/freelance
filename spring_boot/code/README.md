# Spring Boot Code Examples

Working code for the [Spring Boot Teaching Materials](../materials/README.md).

## Projects

| Folder | Level | Corresponding Modules |
|--------|--------|------------------------|
| **beginner** | Beginner | 1–4 (Intro, Setup, First App, Core Concepts) |
| **intermediate** | Intermediate | 5–8 (REST, JPA, Security, Configuration) |
| **advanced** | Advanced | 9–12 (Testing, Actuator, Production, Microservices) |

## Running the Code

Each project uses **Maven**. To run without installing Maven globally:

1. **Option A:** Generate a new project from [start.spring.io](https://start.spring.io) (same dependencies as in each `pom.xml`), then copy the `src` and `pom.xml` from the corresponding folder (beginner, intermediate, or advanced). The generated project includes the Maven wrapper (`mvnw`).

2. **Option B:** If Maven is installed, generate the wrapper from the project directory:
   ```bash
   mvn wrapper:wrapper
   ```
   Then run:
   ```bash
   ./mvnw spring-boot:run
   ```

3. **Option C:** With Maven installed, run directly:
   ```bash
   mvn spring-boot:run
   ```

## Quick Start

```bash
cd beginner
./mvnw spring-boot:run   # or: mvn spring-boot:run
# Open http://localhost:8080/hello
```

See each project’s **README.md** for endpoints and details.
