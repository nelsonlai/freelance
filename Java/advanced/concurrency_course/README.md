# Java Concurrency for Exchange Systems — Course Index

A 7-module, ~14–16 week course on threads, JVM memory model, locks, concurrency utilities, async/reactive patterns, exchange-style system design, and concurrent big data with Spark.

## Structure

| Module | Topic | Duration | Path |
|--------|--------|----------|------|
| 1 | Threads, JVM Memory Model & Visibility | 2 weeks | [module01/](module01/) |
| 2 | Locks, Synchronization & Lock-Free Design | 2 weeks | [module02/](module02/) |
| 3 | Java Concurrency Utilities in Depth | 2 weeks | [module03/](module03/) |
| 4 | Asynchronous Programming & Reactive Thinking | 2 weeks | [module04/](module04/) |
| 5 | Concurrency Models Used in Exchanges | 2 weeks | [module05/](module05/) |
| 6 | Real-World Exchange System Design | 2–3 weeks | [module06/](module06/) |
| 7 | Using Spark to Concurrently Process Big Data | 2 weeks | [module07/](module07/) |

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

  Repeat for other modules: replace `module01` with `module02` … `module06`. Module 6’s `JMH_OrderBookBenchmark` requires the JMH library; use `SimpleOrderBookBenchmark` for a plain-Java benchmark. **Module 7** (Spark big data) uses Maven: run from `module07/` with `mvn compile exec:java -Dexec.mainClass="concurrency.module07.SparkRDDDemo"` (or other main classes); see [module07/README.md](module07/README.md).

- **Hands-on:** Each module README lists exercises and the table of classes with their purpose.

## Prerequisites

- Java 11+ (17+ recommended for modern APIs).
- Basic familiarity with threads and `synchronized` (e.g. from `advanced/Concurrency.java`).
