package concurrency.module04;

import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * Async error handling: exceptionally, handle, whenComplete.
 * Ensures failures are logged and optionally converted to fallback values.
 */
public class AsyncErrorHandling {

    public static void main(String[] args) {
        ExecutorService exec = Executors.newSingleThreadExecutor();

        CompletableFuture.supplyAsync(() -> {
            if (Math.random() > 0.5) throw new RuntimeException("simulated failure");
            return 42;
        }, exec)
            .whenComplete((v, t) -> {
                if (t != null) System.out.println("Error: " + t.getMessage());
                else System.out.println("Result: " + v);
            })
            .exceptionally(t -> {
                System.out.println("Fallback due to: " + t.getMessage());
                return -1;
            })
            .thenAccept(r -> System.out.println("Final value: " + r))
            .join();

        // Propagation: failure in middle stage -> fallback value (handle accepts Object from failed stage)
        CompletableFuture<Integer> chain = CompletableFuture.supplyAsync(() -> 1, exec)
            .thenApply(n -> { throw new RuntimeException("stage2"); })
            .handle((v, t) -> t != null ? Integer.valueOf(0) : (Integer) v);
        System.out.println("Chain after handle: " + chain.join());

        exec.shutdown();
    }
}
