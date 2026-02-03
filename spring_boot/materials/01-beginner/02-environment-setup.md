# Module 2: Environment Setup

**Level:** Beginner  
**Time:** ~60 minutes

---

## Learning Objectives

- Install JDK 17+ and verify the installation
- Choose and set up a build tool (Maven or Gradle)
- Use Spring Initializr to generate a project
- Run the generated app from IDE and command line

---

## 2.1 Java Development Kit (JDK)

### Requirement

- **Spring Boot 3.x:** Java 17 minimum
- **Spring Boot 4.x:** Java 17+ (supports up to Java 25)

### Install JDK

**Option A: Eclipse Temurin (recommended)**

- Download: [adoptium.net](https://adoptium.net/)
- Choose JDK 17 or 21 LTS

**Option B: Oracle JDK**

- Download from [Oracle Java](https://www.oracle.com/java/technologies/downloads/)

**Option C: SDKMAN (macOS/Linux)**

```bash
sdk install java 21.0.1-tem
sdk use java 21.0.1-tem
```

### Verify

```bash
java -version
javac -version
```

You should see version 17 or higher.

---

## 2.2 Build Tools

Spring Boot works with **Maven** or **Gradle**. You only need one.

### Maven

- **Install:** [maven.apache.org](https://maven.apache.org/download.cgi) or use the wrapper (`mvnw`) included by Initializr
- **Verify:** `mvn -v`

### Gradle

- **Install:** [gradle.org](https://gradle.org/install/) or use the wrapper (`gradlew`) from Initializr
- **Verify:** `./gradlew --version` or `gradle --version`

**Tip:** Prefer the **wrapper** (`mvnw`/`gradlew`) so students use the same version without installing Maven/Gradle globally.

---

## 2.3 Spring Initializr

[start.spring.io](https://start.spring.io) generates a ready-to-run Spring Boot project.

### Steps

1. Open **https://start.spring.io**
2. **Project:** Maven or Gradle
3. **Language:** Java (or Kotlin)
4. **Spring Boot:** Latest 3.x (e.g. 3.2.x) or 4.x
5. **Metadata:**
   - Group: `com.example` (or your domain)
   - Artifact: `demo`
   - Name / Description: optional
   - Package name: usually same as Group
6. **Packaging:** Jar
7. **Java:** 17 or 21
8. **Dependencies:** Add:
   - **Spring Web** — for REST/MVC (we use this in the first app)
9. Click **Generate** and download the ZIP

### What You Get

- `pom.xml` (Maven) or `build.gradle` (Gradle)
- `src/main/java` — main application and packages
- `src/main/resources` — `application.properties`, static, templates
- `src/test/java` — test skeleton
- Wrapper scripts: `mvnw`/`mvnw.cmd` or `gradlew`/`gradlew.bat`

---

## 2.4 IDE Setup

### IntelliJ IDEA

- **File → New → Project from Existing Sources** and select the project folder, or open the `pom.xml` / `build.gradle`
- JDK: **Project Structure → Project → SDK** = 17 or 21
- Run: open the main class (with `@SpringBootApplication`) and click Run

### Eclipse (with Spring Tools)

- Install **Spring Tools 4** from the Eclipse Marketplace
- **File → Import → Maven/Gradle → Existing Project**
- Right-click project → **Run As → Spring Boot App**

### VS Code

- Install **Extension Pack for Java** and **Spring Boot Extension Pack**
- Open folder; run from the main class or use the Spring Boot dashboard

---

## 2.5 Run the Application

### From IDE

- Open the class that has `@SpringBootApplication` and `main(String[] args)`
- Run that class (e.g. green play button)

### From Command Line

**Maven:**

```bash
./mvnw spring-boot:run
```

**Gradle:**

```bash
./gradlew bootRun
```

### Build a JAR and Run

**Maven:**

```bash
./mvnw clean package
java -jar target/demo-0.0.1-SNAPSHOT.jar
```

**Gradle:**

```bash
./gradlew clean bootJar
java -jar build/libs/demo-0.0.1-SNAPSHOT.jar
```

Then open **http://localhost:8080**. The template project may show a Whitelabel error page until you add a controller — that’s expected.

---

## 2.6 Troubleshooting

| Issue | Check |
|-------|--------|
| `java: command not found` | JDK not installed or not on PATH |
| Wrong Java version | `JAVA_HOME` and `java -version` |
| Port 8080 in use | Change `server.port` in `application.properties` or stop the other process |
| Maven/Gradle not found | Use wrapper: `./mvnw` or `./gradlew` |

---

## Summary

- Install JDK 17+ and a build tool (or use wrappers).
- Use Spring Initializr to create a project with **Spring Web**.
- Run with IDE or `./mvnw spring-boot:run` / `./gradlew bootRun`.
- Build a JAR with `package` / `bootJar` and run it with `java -jar`.

---

## Exercises

1. Generate a project from start.spring.io with **Spring Web** and run it; confirm it starts on port 8080.
2. Change the server port to 9090 via `application.properties` and run again.
3. Build the JAR and run it from the command line without the IDE.
