# Module 6 — Real-World Exchange System Design (2–3 weeks)

---

## 1. Order Lifecycle Management

- **States:** Created → Validated → Accepted → PartiallyFilled → Filled / Cancelled / Rejected.
- **Transitions:** Strict state machine; idempotent by client order ID where applicable.
- **Persistence:** Persist at accept and at every fill/cancel so recovery is possible.
- **Concurrency:** Single writer (matching engine thread) updates state; readers (APIs, risk) see snapshots or event stream.

---

## 2. Separation of Matching, Risk Control, and Settlement

- **Matching:** Single-threaded or lock-free order book; input queue of orders; output stream of fills and book updates.
- **Risk control:** Pre-trade checks (balance, position limits, rate limits); can be in the hot path (sync) or async with reject/cancel flow.
- **Settlement:** Post-trade; update balances, positions; can be eventually consistent with at-least-once delivery and idempotent handlers.

---

## 3. Idempotency and Duplicate Handling

- **Client order ID:** Client sends unique ID; exchange deduplicates. Re-submit with same ID → same outcome (accept once, same fills).
- **Idempotent handlers:** Settlement and downstream consumers use keys (e.g. trade ID + account) to apply updates once.
- **At-least-once delivery:** Message queues may redeliver; design so processing twice is safe (idempotency or dedup store).

---

## 4. Exactly-Once vs At-Least-Once Semantics

- **At-least-once:** Producer retries; consumer may see same message twice. Use idempotent processing.
- **Exactly-once:** Harder; usually “exactly-once processing” via idempotency + dedup, or transactional outbox and consumer transaction.
- **Exchange:** Matching often “effectively once” (single consumer, single queue); settlement often at-least-once with idempotent application.

---

## 5. Capstone: High-Concurrency Order Book

- **Design:** Lock-free or single-writer order book; multiple producers (gateways) enqueue to one queue; one matching thread; output to risk/settlement via queues.
- **Load testing:** JMH for throughput/latency of book operations; integration tests with many concurrent order submissions.
- **GC and latency:** Reduce allocations in hot path; consider off-heap for critical structures; tune GC (e.g. G1, ZGC) for low pause times.

---

## 6. Code in This Module

| Class | Purpose |
|-------|--------|
| `OrderLifecycle` | Order state enum and transitions; example state machine. |
| `OrderBook` | In-memory order book (bids/asks); add/cancel/match; single-threaded use. |
| `ExchangePipeline` | Placeholder pipeline: ingest queue → matching → fill queue; separation of concerns. |
| `IdempotentProcessor` | Dedup by key (e.g. client order ID); process once. |
| `JMH_OrderBookBenchmark` | JMH benchmark skeleton (requires JMH dependency). |
| `SimpleOrderBookBenchmark` | Plain Java throughput benchmark (no JMH). |
