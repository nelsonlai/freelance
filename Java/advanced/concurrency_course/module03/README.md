# Module 3 — Java Concurrency Utilities in Depth (2 weeks)

---

## 1. Executor Framework & Thread Pool Design Principles

### 1.1 Why Executors?

- **Decoupling:** Submit tasks without managing threads directly (no `new Thread(...).start()` everywhere).
- **Reuse:** Thread pools reuse a fixed set of threads; avoid the cost of creating/destroying threads per task.
- **Backpressure and lifecycle:** Bounded queues and rejection policies; shutdown hooks.

### 1.2 Core Types

- **Executor:** `void execute(Runnable)` — fire-and-forget.
- **ExecutorService:** extends Executor; adds `submit(Callable)`, `invokeAll`, `invokeAny`, `shutdown()`, `awaitTermination()`, etc.
- **ScheduledExecutorService:** schedule once or at fixed rate/delay.

### 1.3 ThreadPoolExecutor (and factory methods)

- **Core pool size:** threads to keep alive (even if idle) unless allowCoreThreadTimeOut.
- **Maximum pool size:** cap on number of threads.
- **Work queue:** tasks waiting for a thread. Options:
  - **Unbounded** (e.g. `LinkedBlockingQueue`): max pool size rarely used; risk of unbounded growth.
  - **Bounded** (e.g. `ArrayBlockingQueue`): when full, new threads created up to max; then rejection.
- **RejectedExecutionHandler:** when queue is full and max threads reached — AbortPolicy (default), CallerRunsPolicy, DiscardPolicy, DiscardOldestPolicy, or custom.

**Design principles:**
- For CPU-bound: pool size ≈ number of cores (or cores + 1).
- For I/O-bound: larger pool or separate pools so blocking doesn’t starve CPU.
- Prefer bounded queues and explicit rejection policy in production.

### 1.4 Factory methods (Executors)

- `newCachedThreadPool()`: unbounded thread count; short-lived tasks. Risk: burst can create many threads.
- `newFixedThreadPool(n)`: fixed size, unbounded queue. Good for stable load; queue can grow.
- `newSingleThreadExecutor()`: one thread, ordered execution.
- `newScheduledThreadPool(n)`: for scheduled tasks.

---

## 2. BlockingQueue Internals

- **Blocking:** `take()` blocks until an element is available; `put(e)` blocks until space is available (for bounded queues).
- **Implementations:**
  - **ArrayBlockingQueue:** bounded, array-based, one lock (or two for take/put), fair option.
  - **LinkedBlockingQueue:** optional capacity; often two locks (take vs put) for better throughput.
  - **SynchronousQueue:** no storage; put blocks until a take; “handoff” pattern.
  - **PriorityBlockingQueue:** heap-based priority; unbounded.
  - **DelayQueue:** elements taken when delay expires.

**Exchange relevance:** Order queues, task queues, and producer-consumer pipelines often use BlockingQueue.

---

## 3. Semaphore, CountDownLatch, Phaser

### 3.1 Semaphore

- **Permits:** acquire() / release(); number of permits limits concurrency. Binary semaphore (1 permit) ≈ lock (but can release from another thread — not reentrant by default).
- **Use:** limit concurrent access (e.g. DB connections, rate limiting), resource pools.

### 3.2 CountDownLatch

- **One-shot:** count down from N to 0; await() blocks until count is 0. All awaiters released at once.
- **Use:** “start gate” (one thread counts down when ready) or “finish line” (N workers each count down when done; main awaits).

### 3.3 Phaser

- **Multi-phase barrier:** parties register; arrive() / arriveAndAwaitAdvance() for each phase; dynamic registration.
- **Use:** multi-stage pipelines where each stage must complete before the next (e.g. batch processing).

---

## 4. Rate Limiting Strategies (Exchange-Critical)

- **Token bucket:** refill tokens at a rate; consume one per request; reject when empty.
- **Sliding window / leaky bucket:** smooth or cap burst.
- **Per-user / per-API key limits:** prevent one client from starving others.
- **Implementation:** often a Semaphore + refill thread, or a custom limiter with timestamps and atomic state.

---

## 5. Hands-On

- **Transaction throttling system:** cap concurrent transactions (e.g. Semaphore); optional per-user limits; measure throughput and rejection rate.
- **Custom thread pool:** implement a minimal pool with a BlockingQueue and a fixed set of worker threads; compare with ThreadPoolExecutor.
- **Avoiding Executor misuse:** unbounded queue + fixed pool leading to OOM; silent swallow in rejection handler; not shutting down the pool.

---

## 6. Code in This Module

| Class | Purpose |
|-------|--------|
| `ExecutorBasics` | submit vs execute; Future; shutdown/awaitTermination. |
| `BlockingQueueDemo` | Producer-consumer with ArrayBlockingQueue; take/put blocking. |
| `SemaphoreRateLimit` | Semaphore-based rate limiter; N permits, refill or fixed. |
| `CountDownLatchDemo` | Start gate and “all workers done” usage. |
| `PhaserDemo` | Multi-phase parallel steps with Phaser. |
| `TransactionThrottling` | Throttle concurrent transactions; optional per-user limit; metrics. |
| `CustomThreadPool` | Minimal thread pool with BlockingQueue and worker threads. |
