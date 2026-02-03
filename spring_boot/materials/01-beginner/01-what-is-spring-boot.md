# Module 1: What is Spring Boot?

**Level:** Beginner  
**Time:** ~45 minutes

---

## Learning Objectives

- Explain what Spring Boot is and why it exists
- Distinguish Spring Framework from Spring Boot
- List key features and benefits
- Understand “convention over configuration”

---

## 1.1 The Problem Spring Boot Solves

### Before Spring Boot (Traditional Java EE / Spring)

- **Heavy configuration:** XML or Java config for every component
- **Dependency hell:** Choosing and aligning library versions manually
- **Deployment:** Building WARs, configuring application servers (Tomcat, JBoss)
- **Boilerplate:** Repetitive setup for every new project

### After Spring Boot

- **Minimal config:** Sensible defaults; override only when needed
- **Managed dependencies:** Starters bring in compatible versions
- **Embedded server:** Run as a standalone JAR with embedded Tomcat/Jetty/Undertow
- **Fast start:** Create a runnable app in minutes

---

## 1.2 Spring Framework vs Spring Boot

| Aspect | Spring Framework | Spring Boot |
|--------|------------------|-------------|
| **What it is** | Core container + modules (MVC, Data, Security, etc.) | Opinionated layer on top of Spring |
| **Configuration** | You wire beans and decide versions | Auto-configuration + starters |
| **Server** | You deploy to an external server | Embedded server (e.g. Tomcat) in the JAR |
| **Goal** | Flexibility and power | “Just run” production-ready apps |

**Summary:** Spring Boot is not a replacement for Spring; it is a way to use Spring with less configuration and faster development.

---

## 1.3 Key Features of Spring Boot

1. **Stand-alone applications**  
   Single JAR you run with `java -jar app.jar`.

2. **Embedded web server**  
   Tomcat, Jetty, or Undertow inside your app — no separate install.

3. **Starter dependencies**  
   One dependency (e.g. `spring-boot-starter-web`) pulls in a coherent set of libraries.

4. **Auto-configuration**  
   Spring configures beans based on classpath and properties (e.g. if H2 is on classpath, a DataSource can be auto-configured).

5. **Production-ready features**  
   Health checks, metrics, externalized configuration (Actuator, `application.properties`).

6. **No code generation, no XML required**  
   Pure Java (or Kotlin) and optional properties/YAML.

---

## 1.4 Convention Over Configuration

Spring Boot prefers **conventions**:

- **Port:** 8080 by default
- **Context path:** `/` by default
- **Static resources:** `src/main/resources/static`
- **Config:** `application.properties` or `application.yml`
- **Main class:** Class with `public static void main` and `@SpringBootApplication`

You *can* override everything; you only configure what differs from the convention.

---

## 1.5 What You Build With Spring Boot

- REST and MVC web applications
- Microservices
- Batch jobs (Spring Batch)
- Event-driven apps (Spring Kafka, AMQP)
- Data access (JPA, MongoDB, Redis, etc.)
- Secure APIs (Spring Security)

---

## 1.6 Summary

- **Spring Boot** = Spring + opinionated defaults + embedded server + starters + auto-configuration.
- It reduces setup time and lets you focus on business logic.
- It targets stand-alone, production-grade applications that you can “just run.”

---

## Exercises

1. In one paragraph, explain to a colleague why a team might choose Spring Boot over plain Spring.
2. List three “conventions” Spring Boot uses that you could override in configuration.
3. Name two types of applications (e.g. REST API, batch) that you could build with Spring Boot.
