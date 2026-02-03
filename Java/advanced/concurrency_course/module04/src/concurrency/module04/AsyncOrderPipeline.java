package concurrency.module04;

import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * Async order processing pipeline: validate -> enrich -> persist -> notify.
 * Each stage returns CompletableFuture; errors propagated and handled.
 */
public class AsyncOrderPipeline {

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

    CompletableFuture<Order> validate(Order order) {
        return CompletableFuture.supplyAsync(() -> {
            order.valid = order.amount > 0 && order.userId != null;
            return order;
        }, exec);
    }

    CompletableFuture<Order> enrich(Order order) {
        return CompletableFuture.supplyAsync(() -> {
            // Simulate lookup
            return order;
        }, exec);
    }

    CompletableFuture<Order> persist(Order order) {
        return CompletableFuture.supplyAsync(() -> {
            // Simulate DB write
            return order;
        }, exec);
    }

    CompletableFuture<Void> notify(Order order) {
        return CompletableFuture.runAsync(() -> {
            System.out.println("Notified for order " + order.id);
        }, exec);
    }

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
