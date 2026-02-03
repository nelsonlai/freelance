# Module 1 — Threads, JVM Memory Model & Visibility (2 weeks)

> Most engineers know how to *use* threads, but not how they actually work under the hood.

---

## 1. JVM Memory Model & Happens-Before Rules

### 1.1 What is the JVM Memory Model (JMM)?

The **Java Memory Model** is a formal specification (JLS §17) that defines:
- How threads interact through **shared memory**.
- When a write by one thread is **visible** to another.
- What **reorderings** compilers and CPUs are allowed to do.

Without the JMM, "obviously correct" code could fail in subtle ways on multicore machines.

### 1.2 Main Memory vs Working Memory (Conceptual)

- **Main memory**: shared heap (objects, static fields). All threads "see" it in principle.
- **Working memory**: conceptual per-thread cache of what that thread has read or written. The JVM may keep variables in registers or CPU caches and only flush to main memory under specific rules.

A thread is not required to see another thread's write immediately unless the JMM defines a **happens-before** relationship between the write and the read.

### 1.3 Happens-Before Rules (Essential)

**Happens-before** is a partial order. If A *happens-before* B:
- All visible effects of A are visible to any thread that observes B.
- No reordering can make A appear after B from any thread's perspective.

Key rules:

1. **Program order**: Within a single thread, actions in program order happen-before each other.
2. **Monitor lock (synchronized)**:
   - Unlock on monitor M *happens-before* every subsequent lock on M.
   - So: writes before `unlock` are visible to the next thread that `lock`s.
3. **Volatile**:
   - A write to volatile V *happens-before* every subsequent read of V (by any thread).
   - Volatile reads/writes are not reordered with each other (and have additional ordering guarantees).
4. **Thread start**: `Thread.start()` *happens-before* any action in the started thread.
5. **Thread termination**: Any action in a thread *happens-before* `Thread.join()` returns in the joining thread.

**Takeaway:** If two threads communicate only through non-volatile, non-synchronized variables, there is no happens-before between them → **visibility bugs** are allowed.

---

## 2. Stack vs Heap vs Metaspace

### 2.1 Stack (per thread)

- **Stores:** local variables, method parameters, return addresses, partial results.
- **Lifecycle:** frame pushed on method call, popped on return.
- **Not shared:** each thread has its own stack. No visibility issues for true locals.

### 2.2 Heap

- **Stores:** object instances, arrays (the objects themselves).
- **Shared:** all threads access the same heap. Hence races and visibility matter.
- **GC:** managed by the garbage collector.

### 2.3 Metaspace (Java 8+)

- **Stores:** class metadata (class structures, method metadata, constant pool, etc.).
- **Replaces:** old "PermGen". Not for your object data.
- **Shared:** loaded classes are shared; visibility of class state still follows JMM for static fields (they live in the heap/metaspace boundary as far as values go—static field *values* are in heap).

**Rule of thumb:** If it's shared across threads (object fields, static variables), it's on the heap and you must think about visibility and synchronization.

---

## 3. Instruction Reordering & CPU Cache Behavior

### 3.1 Why Reordering Exists

- **Compiler:** may reorder instructions for optimization (e.g. move independent reads earlier).
- **CPU:** out-of-order execution, store buffers, cache hierarchies.

The JMM allows reordering as long as **within-thread** semantics (as-if-serial) and **happens-before** rules are respected. So from another thread's perspective, your program can look reordered.

### 3.2 Example: Reordering Breaking "Logical" Correctness

```text
Thread 1:                    Thread 2:
  a = 1;                       while (!ready);
  ready = true;                print(a);
```

Logically you might expect Thread 2 to always print `1`. But:
- Without synchronization, `ready` and `a` have no happens-before.
- Compiler/CPU might reorder so `ready = true` is visible to Thread 2 before `a = 1`. Then Thread 2 could print `0`.

Making `ready` volatile (or using a lock) establishes happens-before and prevents this.

### 3.3 CPU Caches

- Each core has its own cache (L1/L2, sometimes L3 shared).
- A write may sit in a store buffer or cache before being visible to other cores.
- **Cache coherency** (e.g. MESI) eventually propagates changes, but the **when** is constrained only by the JMM (volatile, synchronized, etc.), not by "immediate" visibility.

So: "I wrote it, so the other thread will see it" is **false** unless you use the right primitives.

---

## 4. Why `volatile` Is Not a Silver Bullet

### 4.1 What `volatile` Gives You

- **Visibility:** a write to a volatile variable is visible to subsequent reads by any thread (happens-before).
- **No reordering:** the JMM forbids reordering of volatile accesses with other volatile accesses, and restricts reordering of surrounding non-volatile accesses (e.g. a volatile write cannot be reordered with a prior read/write; a volatile read cannot be reordered with a subsequent read/write). So you get a "barrier" effect.

### 4.2 What `volatile` Does *Not* Give You

- **Atomicity of compound actions:** e.g. `count++` is read-modify-write. Two threads can both read the same value, both increment, both write → lost updates. Volatile only makes each read/write visible; it does not make the whole `count++` atomic.
- **Mutual exclusion:** no locking. So no "only one thread in this block at a time."

**When volatile is enough:** a single writer, other threads only read (e.g. a shutdown flag, or a reference published once). For read-modify-write or multi-writer shared state, use atomics or locks.

---

## 5. Hands-On Objectives

- **Reproduce visibility bugs:** run the examples that show stale reads (e.g. shared flags/counters without volatile or locks).
- **Debug non-obvious failures:** use the examples where "logically correct" code fails under concurrency (reordering, visibility).
- **Understand volatile:** see that volatile fixes visibility but not compound updates; compare with synchronized/atomic.

---

## 6. Code in This Module

| Class | Purpose |
|-------|--------|
| `VisibilityBug` | Shared flag/counter without synchronization; demonstrates stale visibility. |
| `VolatileFix` | Same scenario with `volatile`; correct visibility, still not atomic for count++. |
| `ReorderingDemo` | Illustrates how reordering can make "ready" visible before "data". |
| `LogicalCorrectnessFailure` | "Logically correct" double-check or flag usage that can fail under JMM. |

Run the `main` methods and vary thread count / loop iterations to see failures (you may need to run many times or add stress loops).
