package concurrency.module06;

import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;
import java.util.function.Consumer;

/**
 * Idempotent processor: ensures each key (e.g. client order ID or idempotency key)
 * is processed at most once. Duplicate keys are skipped without running the handler.
 * Suitable when messages or requests can be delivered at least once and you need
 * to avoid double execution (e.g. double credit).
 *
 * <p>Uses {@link ConcurrentHashMap#newKeySet()} for thread-safe add/contains.
 * For very high throughput or bounded memory, consider a cache with TTL or a
 * bloom filter plus periodic cleanup.
 *
 * @param <K> type of the idempotency key
 */
public class IdempotentProcessor<K> {

    /** Set of keys already processed. add() is atomic; first add wins. */
    private final Set<K> processed = ConcurrentHashMap.newKeySet();
    private final Consumer<K> handler;

    public IdempotentProcessor(Consumer<K> handler) {
        this.handler = handler;
    }

    /**
     * If the key has not been seen before, adds it, runs the handler, and returns true.
     * If the key was already processed, returns false without running the handler.
     *
     * @param key the idempotency key (e.g. order id)
     * @return true if the handler was run, false if duplicate
     */
    public boolean processOnce(K key) {
        if (processed.add(key)) {
            handler.accept(key);
            return true;
        }
        return false;
    }

    /** Returns true if this key has already been processed. */
    public boolean alreadyProcessed(K key) {
        return processed.contains(key);
    }

    public static void main(String[] args) {
        IdempotentProcessor<String> p = new IdempotentProcessor<>(k -> System.out.println("Processed: " + k));
        System.out.println(p.processOnce("order-1"));
        System.out.println(p.processOnce("order-1"));
        System.out.println(p.processOnce("order-2"));
    }
}
