# Module 5 — Concurrency Models Used in Exchanges (2 weeks)

> This module provides **major interview differentiation**.

---

## 1. Thread-per-Request (and Why It Fails at Scale)

- **Model:** Each incoming request gets a dedicated thread (e.g. classic servlet container). Thread handles the request end-to-end.
- **Problems at scale:**
  - **Thread count:** One thread per request; 10k concurrent requests → 10k threads. Thread stack (e.g. 1 MB) and context switching become expensive.
  - **Blocking I/O:** Thread blocks on DB, HTTP, or file I/O; that thread is not usable for other work. Throughput limited by thread count and blocking.
- **When it’s acceptable:** Low concurrency, simple deployments. Exchanges and high-throughput systems usually move to event-driven or actor models.

---

## 2. Actor Model (Used in Matching Engines)

- **Idea:** “Actors” are independent units of computation; they communicate only by **messages**. No shared mutable state; each actor processes its mailbox sequentially.
- **Benefits:** Natural isolation (no locks on shared state); location transparency; good for distributed systems. Fits matching engines: order book can be one actor (or a hierarchy); orders are messages.
- **In Java:** Akka (JVM); or a minimal in-process implementation: one thread per actor (or a shared pool) and a concurrent queue per mailbox.

---

## 3. Event Loop Architecture (Netty, Disruptor)

- **Event loop:** Single thread (or a small number of threads) runs a loop: poll events (I/O, timers, tasks) and dispatch handlers. No blocking in the loop; I/O is async (e.g. callbacks, futures).
- **Netty:** Network I/O with event loops and pipelines (handlers). Fits exchange gateways and microservices.
- **Disruptor:** Ring buffer + sequencers; single writer per sequence; wait-free or lock-free patterns. Used in ultra-low-latency trading; avoids locks and kernel syscalls where possible.

---

## 4. Message-Driven and Queue-Based Designs

- **Pattern:** Producers put messages (orders, events) into queues; consumers process from queues. Decouples producers and consumers; natural backpressure with bounded queues.
- **Exchange relevance:** Order ingestion → queue → matching engine; matching engine → queue → risk/settlement. Multiple producers, single consumer per queue for ordering guarantees.

---

## 5. Hands-On: Mini Matching Engine

- **Scope:** Single trading pair; multiple producers (order entry), single consumer (matching).
- **Guarantees:** Orders processed in a well-defined order (e.g. per queue); no shared mutable order book from multiple threads — one thread owns the book.
- **Design:** One thread runs the matching loop; it takes orders from a single queue (e.g. BlockingQueue), applies them to the book (in memory), and produces fills/trades. Producers only enqueue.

---

## 6. Code in This Module

| Class | Purpose |
|-------|--------|
| `ThreadPerRequestDemo` | Simulates thread-per-request; shows thread count growth. |
| `SimpleActor` | Minimal in-process “actor”: mailbox queue + single-thread processing. |
| `EventLoopDemo` | Single-thread event loop with a task queue and simulated I/O completion. |
| `MiniMatchingEngine` | Single queue, single consumer; order types (limit); in-memory book; produces fills. |
