package concurrency.module04;

import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * Async order processing pipeline: validate → enrich → persist → notify.
 * Each stage returns a {@link java.util.concurrent.CompletableFuture}; stages
 * are chained with thenCompose so the next stage runs when the previous completes.
 * Errors are caught by exceptionally at the end so the caller can join() without
 * handling exceptions (or they can handle on the returned future).
 *
 * <p>thenCompose is used (not thenApply) because each stage is async (returns
 * CompletableFuture). Using thenApply would nest CompletableFuture&lt;CompletableFuture&lt;T&gt;&gt;.
 */
public class AsyncOrderPipeline {

    /** Simple order DTO: id, amount, userId, and a validity flag set by validate. */
    static class Order {
        String id;
        double amount;
        String userId;
        boolean valid;

        Order(String id, double amount, String userId) {
            this.id = id;
            this.amount = amount;
            this.userId = userId;
        }
    }

    private final ExecutorService exec = Executors.newFixedThreadPool(4);

    /** Validates the order (amount > 0, userId non-null) and sets order.valid. */
    CompletableFuture<Order> validate(Order order) {
        return CompletableFuture.supplyAsync(() -> {
            order.valid = order.amount > 0 && order.userId != null;
            return order;
        }, exec);
    }

    /** Enriches the order (e.g. lookup user or product). Here just returns the same order. */
    CompletableFuture<Order> enrich(Order order) {
        return CompletableFuture.supplyAsync(() -> {
            return order;
        }, exec);
    }

    /** Persists the order (e.g. DB write). Here just returns the order. */
    CompletableFuture<Order> persist(Order order) {
        return CompletableFuture.supplyAsync(() -> {
            return order;
        }, exec);
    }

    /** Sends a notification (e.g. event or message). Returns Void. */
    CompletableFuture<Void> notify(Order order) {
        return CompletableFuture.runAsync(() -> {
            System.out.println("Notified for order " + order.id);
        }, exec);
    }

    /**
     * Runs the full pipeline: validate → enrich → persist → notify.
     * If validation fails (invalid order), we complete with failedFuture so
     * the chain fails and exceptionally runs. Otherwise each stage runs in sequence.
     *
     * @param order the order to process
     * @return a CompletableFuture that completes when the pipeline finishes (or fails)
     */
    public CompletableFuture<Void> processOrder(Order order) {
        return validate(order)
            .thenCompose(o -> o.valid ? enrich(o) : CompletableFuture.failedFuture(new IllegalArgumentException("Invalid order")))
            .thenCompose(this::persist)
            .thenCompose(this::notify)
            .exceptionally(t -> {
                System.err.println("Pipeline failed: " + t.getMessage());
                return null;
            });
    }

    public static void main(String[] args) {
        AsyncOrderPipeline pipeline = new AsyncOrderPipeline();
        Order order = new Order("ord-1", 100.0, "user-1");
        pipeline.processOrder(order).join();
        System.out.println("Done.");
    }
}
