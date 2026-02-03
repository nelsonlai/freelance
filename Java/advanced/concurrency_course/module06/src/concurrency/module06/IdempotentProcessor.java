package concurrency.module06;

import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;
import java.util.function.Consumer;

/**
 * Idempotent processor: process each key (e.g. client order ID) at most once.
 * Duplicate keys are skipped. Suitable for at-least-once delivery with idempotent handling.
 */
public class IdempotentProcessor<K> {

    private final Set<K> processed = ConcurrentHashMap.newKeySet();
    private final Consumer<K> handler;

    public IdempotentProcessor(Consumer<K> handler) {
        this.handler = handler;
    }

    /** Process only if key was not seen before. Returns true if processed, false if duplicate. */
    public boolean processOnce(K key) {
        if (processed.add(key)) {
            handler.accept(key);
            return true;
        }
        return false;
    }

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
