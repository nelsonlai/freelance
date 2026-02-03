# Module 4 — Asynchronous Programming & Reactive Thinking (2 weeks)

> Async-first thinking is essential for Web3 and exchange systems.

---

## 1. CompletableFuture (Advanced Usage & Pitfalls)

### 1.1 What It Is

- **CompletableFuture\<T>:** A future that you can complete explicitly (`complete(value)`, `completeExceptionally(throwable)`) and compose with callbacks or further async stages.
- **Non-blocking:** Use `thenApply`, `thenCompose`, `thenCombine`, `allOf`, `anyOf`, etc., instead of blocking on `get()`.

### 1.2 Creating a CompletableFuture

- `CompletableFuture.supplyAsync(Supplier)` — run in ForkJoinPool.commonPool() (or provided Executor).
- `CompletableFuture.runAsync(Runnable)`.
- `new CompletableFuture<>()` then `complete(value)` from another thread.

### 1.3 Chaining and Combining

- **thenApply:** transform result (sync function).
- **thenCompose:** chain another async operation (returns CompletableFuture).
- **thenCombine / thenAcceptBoth:** combine two futures.
- **allOf(futures):** one future that completes when all complete (result is void; gather results manually).
- **anyOf(futures):** completes with first result.

### 1.4 Pitfalls

- **Blocking in async chain:** Avoid `get()` inside `thenApply`; use `thenCompose` with an async call instead.
- **Default executor:** supplyAsync uses commonPool(); for many or blocking tasks, pass a dedicated Executor.
- **Exception handling:** use `handle`, `exceptionally`, or `whenComplete` so failures don’t get lost.
- **Completing once:** only the first `complete`/`completeExceptionally` wins; later ones are ignored.

---

## 2. Asynchronous Error Handling

- **exceptionally(Function):** map throwable to a fallback value.
- **handle(BiFunction):** receive result or throwable; return new value (or throw).
- **whenComplete(BiConsumer):** side effect; doesn’t change result. Good for logging.
- **CompletableFuture.completedExceptionally(throwable):** start a chain in failed state.

**Best practice:** Ensure every async pipeline has a terminal handler (e.g. `whenComplete` or `handle`) so exceptions are not swallowed.

---

## 3. Backpressure Fundamentals

- **Definition:** When a fast producer feeds a slow consumer, the consumer signals “slow down” (backpressure) so the system doesn’t buffer unboundedly or OOM.
- **Reactive Streams:** Subscription with `request(n)` — consumer requests n items; publisher sends at most n until next request.
- **In CompletableFuture:** No built-in backpressure; you coordinate with bounded queues, semaphores, or reactive libraries (Reactor, RxJava) that implement backpressure.

---

## 4. Introduction to Reactive Streams Concepts

- **Publisher:** produces a stream of items (and completion/error).
- **Subscriber:** consumes with `onNext`, `onComplete`, `onError`; signals demand via `Subscription.request(n)`.
- **Subscription:** links publisher and subscriber; `request(n)` is backpressure.
- **Processor:** both subscriber and publisher (transform in the middle).

Java 9+ `java.util.concurrent.Flow` defines the interfaces; implementations (Reactor, RxJava) provide the machinery.

---

## 5. Hands-On

- **Async order processing pipeline:** stages: validate → enrich → persist → notify; each stage returns CompletableFuture; chain with thenCompose; handle errors.
- **Sync vs async latency benchmarking:** same workload done synchronously vs async (e.g. multiple I/O calls); measure end-to-end latency and throughput.
- **Failure propagation in async flows:** one stage fails; ensure exception propagates and alternative path (e.g. retry or fallback) is clear.

---

## 6. Code in This Module

| Class | Purpose |
|-------|--------|
| `CompletableFutureAdvanced` | Chaining, thenCompose, thenCombine, allOf; exception handling. |
| `AsyncErrorHandling` | exceptionally, handle, whenComplete; propagation. |
| `AsyncOrderPipeline` | Validate → enrich → persist → notify with CF; error handling. |
| `SyncVsAsyncLatency` | Benchmark: N I/O-like calls in sequence vs in parallel with CF. |
