# Spring Boot Teaching Materials — Beginner to Expert

Comprehensive, classroom-ready materials for teaching [Spring Boot](https://spring.io/projects/spring-boot) from absolute beginners to advanced practitioners. Includes written modules and runnable code.

---

## What’s Inside

- **[materials/](materials/)** — 12 modules (markdown) from “What is Spring Boot?” through Testing, Actuator, Production, and Microservices.
- **[code/](code/)** — Three runnable Spring Boot projects: **beginner**, **intermediate**, and **advanced**, aligned with the modules.

---

## Curriculum at a Glance

| Level | Modules | Topics |
|-------|---------|--------|
| **Beginner** | 1–4 | What is Spring Boot, environment setup, first application, IoC/DI and core concepts |
| **Intermediate** | 5–8 | REST APIs, Spring Data JPA, Spring Security, configuration and profiles |
| **Advanced** | 9–12 | Testing (unit, MockMvc), Actuator and monitoring, production deployment, microservices patterns |

---

## How to Use

1. **Teach in order** — Follow modules 1–12 for a full course.
2. **Run the code** — Use the projects in `code/beginner`, `code/intermediate`, and `code/advanced` (see [code/README.md](code/README.md) for how to run them).
3. **Exercises** — Each module ends with exercises; use them for labs or homework.

---

## Prerequisites

- **Java 17+** (Spring Boot 3.x). Spring Boot 4.x supports Java 17+ and newer JDKs.
- Basic Java (classes, interfaces, collections). Maven or Gradle is helpful but not required (wrapper can be used).

---

## Quick Links

- [Materials overview and learning path](materials/README.md)
- [Code examples and how to run them](code/README.md)
- [Spring Boot official site](https://spring.io/projects/spring-boot)
- [Spring Initializr](https://start.spring.io) — bootstrap new projects
- [Spring Guides](https://spring.io/guides)

---

## Repository Layout

```
spring_boot/
├── README.md                 ← You are here
├── materials/
│   ├── README.md             ← Curriculum and learning path
│   ├── 01-beginner/          ← Modules 1–4
│   ├── 02-intermediate/      ← Modules 5–8
│   └── 03-advanced/          ← Modules 9–12
└── code/
    ├── README.md             ← How to run the code
    ├── beginner/             ← First app, IoC/DI
    ├── intermediate/         ← REST, JPA, Security, Config
    └── advanced/             ← Tests, Actuator, Docker, prod profile
```

These materials are for educational use. Spring Boot is under the Apache License 2.0.
