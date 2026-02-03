# Module 7 — Using Spark to Concurrently Process Big Data (2 weeks)

> Scale beyond a single JVM: distribute work across a cluster with Apache Spark.

---

## 1. Why Spark for Big Data Concurrency?

### 1.1 Beyond Single-Machine Concurrency

- **Threads and Executors** (Modules 1–5) give concurrency on one machine; **Spark** distributes work across many machines (or many cores in local mode).
- **Big data:** datasets that don’t fit in memory or would take too long on a single core. Spark partitions data and runs the same logic on each partition in parallel.
- **Unified engine:** batch (RDD, DataFrame), streaming (DStream, Structured Streaming), and SQL — one API and execution model.

### 1.2 Core Ideas

- **Resilient Distributed Dataset (RDD):** immutable, partitioned collection; transformations are lazy, actions trigger execution.
- **Directed Acyclic Graph (DAG):** Spark builds a DAG of stages; scheduler runs stages with maximum parallelism (e.g. one task per partition).
- **Fault tolerance:** lineage (how RDDs were built) allows recomputation of lost partitions without replicating raw data.

---

## 2. Spark Architecture (High Level)

- **Driver:** runs your `main()`; builds DAG, submits jobs to the cluster.
- **Executors:** run tasks (one per partition); store RDD partitions in memory or disk; report back to driver.
- **Cluster Manager:** YARN, Mesos, Kubernetes, or standalone — allocates resources and launches executors.
- **Local mode:** driver and executors run in one JVM; ideal for learning and small data.

**Concurrency in Spark:** Many tasks run concurrently across executors (and within an executor, multiple threads). Partition count and cluster size drive parallelism.

---

## 3. RDD Basics (Java API)

### 3.1 Creating RDDs

- **From collection:** `JavaSparkContext.parallelize(List)` — useful for demos; data lives in driver and is distributed.
- **From file:** `sc.textFile(path)` — one partition per HDFS block (or file split); each partition processed in parallel.

### 3.2 Transformations (Lazy) vs Actions (Eager)

- **Transformations:** `map`, `filter`, `flatMap`, `groupByKey`, `reduceByKey`, `join`, etc. Return RDD; no work until an action.
- **Actions:** `count`, `collect`, `reduce`, `foreach`, `saveAsTextFile`. Trigger execution and return a result or write output.

### 3.3 Key Transformations for Concurrent Processing

- **map / flatMap:** one-to-one or one-to-many per element; runs in parallel over partitions.
- **filter:** drop elements; partition-wise.
- **reduceByKey / aggregateByKey:** shuffle by key; then reduce per key in parallel. Critical for “big data” aggregations.
- **repartition(n)** / **coalesce(n):** change partition count; repartition triggers shuffle; use to tune parallelism.

**Design:** More partitions → more tasks → more concurrency (up to cluster capacity). Too many partitions → overhead; too few → underutilized cores.

---

## 4. DataFrame / Dataset API (Structured)

- **DataFrame:** distributed collection of rows with named columns (like a table). Built on the same engine as RDDs but with Catalyst optimizer.
- **Operations:** `select`, `filter`, `groupBy`, `agg`, `join` — expressed in terms of columns; Spark optimizes execution (predicate pushdown, join strategies).
- **Concurrency:** Same as RDDs — operations are executed as stages with many tasks; partition count and cluster size define parallelism.

---

## 5. Tuning Concurrency and Throughput

- **Partition count:** For RDDs/DataFrames, rule of thumb: at least 2–4× number of cores (or total executor cores in cluster). Adjust with `repartition`/`coalesce`.
- **Shuffle:** `groupByKey`, `reduceByKey`, `join` cause shuffle (network I/O). Minimize shuffle or increase parallelism for shuffle (e.g. `spark.sql.shuffle.partitions`).
- **Memory:** Executor memory and storage fraction; avoid OOM by not collecting huge RDDs to the driver — use `take`, `foreach`, or write to storage.
- **Local vs cluster:** This module’s demos use local mode; same APIs scale to a cluster by changing master and deploying with spark-submit.

---

## 6. Hands-On

- **Word count (RDD):** `textFile` → `flatMap(split)` → `mapToPair(word -> (word, 1))` → `reduceByKey(+)` → `collect` or `saveAsTextFile`. Observe parallelism in logs.
- **DataFrame aggregation:** Load CSV or in-memory data; `groupBy` + `agg`; compare with single-threaded Java aggregation on a small dataset.
- **Partitioning and repartition:** Create RDD with few partitions; repartition; run a CPU-heavy map; measure time vs partition count (local mode).

---

## 7. Code in This Module

| Class | Purpose |
|-------|--------|
| `SparkRDDDemo` | Local SparkContext; RDD from collection; map, filter, reduceByKey; word-count style. |
| `SparkDataFrameDemo` | SparkSession; DataFrame from in-memory data; select, filter, groupBy, agg. |
| `SparkWordCount` | Full word-count from text (or inline); shows parallel text processing. |
| `ParallelStreamsBigData` | Pure Java: parallel streams for “big” in-memory collection; contrast with Spark. |

---

## 8. Running the Code

This module uses **Apache Spark** and is built with **Maven**.

**From `concurrency_course` (or project root):**

```bash
cd module07
mvn compile exec:java -Dexec.mainClass="concurrency.module07.SparkRDDDemo"
mvn compile exec:java -Dexec.mainClass="concurrency.module07.SparkDataFrameDemo"
mvn compile exec:java -Dexec.mainClass="concurrency.module07.SparkWordCount"
```

For `ParallelStreamsBigData` (no Spark):

```bash
javac -d ../../out src/concurrency/module07/ParallelStreamsBigData.java
java -cp ../../out concurrency.module07.ParallelStreamsBigData
```

(Or add `module07` to your IDE and run the main classes.)

**Requirements:** Java 11+; Maven 3.6+; for Spark demos, Maven will pull `spark-core` and `spark-sql`.
