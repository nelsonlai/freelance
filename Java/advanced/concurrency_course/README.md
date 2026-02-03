# Java Concurrency for Exchange Systems — Course Index

A 6-module, ~12–14 week course on threads, JVM memory model, locks, concurrency utilities, async/reactive patterns, and exchange-style system design.

## Structure

| Module | Topic | Duration | Path |
|--------|--------|----------|------|
| 1 | Threads, JVM Memory Model & Visibility | 2 weeks | [module01/](module01/) |
| 2 | Locks, Synchronization & Lock-Free Design | 2 weeks | [module02/](module02/) |
| 3 | Java Concurrency Utilities in Depth | 2 weeks | [module03/](module03/) |
| 4 | Asynchronous Programming & Reactive Thinking | 2 weeks | [module04/](module04/) |
| 5 | Concurrency Models Used in Exchanges | 2 weeks | [module05/](module05/) |
| 6 | Real-World Exchange System Design | 2–3 weeks | [module06/](module06/) |

## How to Use

- **Teaching materials:** Each module has a `README.md` with theory and key points.
- **Code:** Java sources live under `moduleNN/src/concurrency/moduleNN/`. From the `concurrency_course` directory:

  **Compile one module (e.g. module01):**
  ```bash
  mkdir -p out
  javac -d out module01/src/concurrency/module01/*.java
  ```

  **Run a main class:**
  ```bash
  java -cp out concurrency.module01.VisibilityBug
  java -cp out concurrency.module01.VolatileFix
  ```

  Repeat for other modules: replace `module01` with `module02` … `module06`. Module 6’s `JMH_OrderBookBenchmark` requires the JMH library; use `SimpleOrderBookBenchmark` for a plain-Java benchmark.

- **Hands-on:** Each module README lists exercises and the table of classes with their purpose.

## Prerequisites

- Java 11+ (17+ recommended for modern APIs).
- Basic familiarity with threads and `synchronized` (e.g. from `advanced/Concurrency.java`).
