# Spring Boot Teaching Materials: Beginner to Expert

A comprehensive, classroom-ready curriculum for teaching [Spring Boot](https://spring.io/projects/spring-boot) from absolute beginners to advanced practitioners. Designed for instructors and self-learners.

---

## Curriculum Overview

| Level | Modules | Focus |
|-------|---------|--------|
| **Beginner** | 1–4 | What is Spring Boot, setup, first app, core concepts |
| **Intermediate** | 5–8 | REST APIs, Data (JPA), Security, Configuration |
| **Advanced** | 9–12 | Testing, Actuator, Production, Microservices |

**Prerequisites:** Basic Java (classes, interfaces, collections). Familiarity with Maven or Gradle is helpful but not required.

**Runtime:** Java 17+ (Spring Boot 3.x). Spring Boot 4.x uses Java 17+ and supports newer JDKs.

---

## Learning Path

```
BEGINNER
├── 01 What is Spring Boot?
├── 02 Environment Setup
├── 03 Your First Application
└── 04 Core Concepts (IoC, DI, Auto-configuration)

INTERMEDIATE
├── 05 Building REST APIs
├── 06 Spring Data JPA
├── 07 Spring Security
└── 08 Configuration & Profiles

ADVANCED
├── 09 Testing (Unit, Integration, MockMvc)
├── 10 Actuator & Monitoring
├── 11 Production Deployment
└── 12 Microservices Patterns
```

---

## How to Use These Materials

1. **In order:** Follow modules 1–12 for a full course.
2. **Code:** Each module references code in `/code/` — run and modify the examples.
3. **Exercises:** End-of-module exercises reinforce concepts.
4. **Slides/labs:** You can derive slides or lab sheets from the markdown.

---

## Directory Structure

```
materials/
├── README.md                 ← You are here
├── 01-beginner/
│   ├── 01-what-is-spring-boot.md
│   ├── 02-environment-setup.md
│   ├── 03-first-application.md
│   └── 04-core-concepts.md
├── 02-intermediate/
│   ├── 05-rest-apis.md
│   ├── 06-spring-data-jpa.md
│   ├── 07-spring-security.md
│   └── 08-configuration-profiles.md
└── 03-advanced/
    ├── 09-testing.md
    ├── 10-actuator-monitoring.md
    ├── 11-production-deployment.md
    └── 12-microservices-patterns.md

code/
├── beginner/                 ← First app, core concepts
├── intermediate/             ← REST, JPA, Security examples
└── advanced/                 ← Testing, Actuator, production
```

---

## Official Resources

- [Spring Boot Official Site](https://spring.io/projects/spring-boot)
- [Spring Boot Reference](https://docs.spring.io/spring-boot/docs/current/reference/html/)
- [Spring Guides](https://spring.io/guides)
- [Spring Initializr](https://start.spring.io) — bootstrap new projects

---

## License & Usage

These materials are for educational use. Spring Boot is under the Apache License 2.0.
