# Module 2 — Locks, Synchronization & Lock-Free Design (2 weeks)

> Real exchanges do **not** rely on naïve `synchronized` usage.

---

## 1. `synchronized` vs `ReentrantLock`

### 1.1 `synchronized`

- **Syntax:** `synchronized (object)` or `synchronized` method (locks on `this` or the class for `static`).
- **Reentrant:** same thread can acquire the same monitor again (e.g. recursive call).
- **No timeout:** blocking until the lock is acquired (except `wait`/`notify` for condition).
- **Unstructured:** lock is released when leaving the block/method; cannot hold across multiple methods easily.
- **Fairness:** no guaranteed fairness; JVM may favor barging threads.

**When to use:** Simple critical sections, coarse-grained locking, when you don’t need tryLock/timeouts or multiple condition queues.

### 1.2 `ReentrantLock`

- **Explicit:** `lock()`, `unlock()` — must call `unlock()` in `finally` to avoid deadlock on exception.
- **Reentrant:** same thread can lock multiple times; must unlock same number of times.
- **TryLock:** `tryLock()`, `tryLock(timeout)` — non-blocking or bounded wait.
- **Fairness:** `new ReentrantLock(true)` for (approximate) FIFO ordering.
- **Multiple conditions:** one lock can have multiple `Condition` instances (e.g. “not full”, “not empty” for a queue).

**When to use:** Need tryLock, fairness, or multiple condition queues; or when you want lock outside a single block (e.g. across methods).

### 1.3 Comparison

| Feature              | synchronized      | ReentrantLock        |
|----------------------|-------------------|------------------------|
| Try lock / timeout   | No                | Yes (tryLock)         |
| Fairness             | Not specified     | Optional (fair lock)  |
| Multiple conditions  | Single wait set   | Multiple Conditions   |
| Cross-method locking | Awkward          | Natural               |
| Syntax               | Built-in          | Explicit lock/unlock  |

---

## 2. ReadWriteLock & StampedLock

### 2.1 ReadWriteLock

- **Idea:** Many readers OR one writer. Good when reads dominate and critical section is “read-heavy”.
- **`ReentrantReadWriteLock`:** readLock() allows multiple readers; writeLock() is exclusive. Writers block readers and vice versa (implementation-dependent upgrade rules).
- **Pitfall:** If writers are frequent, readers can still contend; and **read lock is not reentrant with write lock** in the same thread by default — you can’t acquire write while holding read (must release read first, then take write, risking deadlock with other threads if not careful).

### 2.2 StampedLock (Java 8+)

- **Modes:** reading (optimistic or pessimistic), writing. **Optimistic read:** no lock held; after reading you validate with `validate(stamp)`; if validation fails, upgrade to full read lock.
- **No reentrancy:** not reentrant; misuse (e.g. taking a lock when already held) can deadlock.
- **No condition variables:** StampedLock does not support `Condition`; use other mechanisms for waiting.
- **Use case:** Very read-heavy, short critical sections; use optimistic reads when contention is low.

---

## 3. CAS Operations & ABA Problem

### 3.1 Compare-And-Swap (CAS)

- **Atomic operation:** “If current value == expected, set to new value; return whether it succeeded.”
- **In Java:** `AtomicInteger`, `AtomicLong`, `AtomicReference`, etc. expose `compareAndSet(expected, update)` and methods built on it (e.g. `incrementAndGet`).
- **Lock-free:** No mutex; threads retry on failure. Good for low contention and simple state.

### 3.2 ABA Problem

- **Scenario:** Thread 1 reads A, is preempted. Thread 2 changes A → B → A. Thread 1’s CAS sees “A” and succeeds, but the state has changed in between (e.g. list head was replaced and re-inserted).
- **Mitigation:** Use **versioned** or **tagged** references (e.g. AtomicStampedReference, or a version number that changes on every update). Then CAS checks both value and version.

---

## 4. False Sharing and Cache-Line Contention

### 4.1 Cache lines

- CPU caches load/store data in **cache lines** (e.g. 64 bytes). Two variables in the same line are in the same “unit” of cache.

### 4.2 False sharing

- **Definition:** Two threads modify **different** variables that happen to lie in the **same cache line**. Each write invalidates the line for the other core; they keep bouncing the line between caches → severe contention even though logically they don’t touch the same variable.
- **Solution:** **Padding** or **alignment** so hot variables used by different threads sit in different cache lines. Java: add unused fields (or use `@Contended` in JDK 8+ with `-XX:-RestrictContended` or in JDK internal packages) to separate them.

### 4.3 When it matters

- High-throughput counters or flags per thread (e.g. statistics, ring buffer sequence fields). Measure with benchmarks (e.g. JMH) before/after padding.

---

## 5. Hands-On

- **High-concurrency account balance:** Implement with synchronized, ReentrantLock, and lock-free (AtomicLong or CAS loop); compare correctness and performance.
- **Lock-based vs lock-free:** Same operations (e.g. debit/credit/read); benchmark under contention.
- **Performance benchmarking:** Use JMH or a simple harness; measure throughput and latency.

---

## 6. Code in This Module

| Class | Purpose |
|-------|--------|
| `SynchronizedVsReentrantLock` | Same counter/critical section with synchronized and ReentrantLock; tryLock example. |
| `ReadWriteLockDemo` | ReadWriteLock: many readers, occasional writer; throughput comparison idea. |
| `StampedLockDemo` | Optimistic read with StampedLock and validate. |
| `ABADemo` | ABA scenario with AtomicReference; AtomicStampedReference fix. |
| `FalseSharingDemo` | Two counters in same/different cache lines; optional @Contended. |
| `AccountBalance` | Account with synchronized, ReentrantLock, and lock-free (atomic) implementations; simple benchmark. |
