package concurrency.module04;

import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * Demonstrates error handling in async pipelines using {@link java.util.concurrent.CompletableFuture}.
 *
 * <p><b>Key methods:</b>
 * <ul>
 *   <li><b>whenComplete(BiConsumer):</b> Called when the stage completes (success or failure).
 *       Receives (result, throwable). Does not change the result; use for logging/side effects.</li>
 *   <li><b>exceptionally(Function):</b> Only called on failure. Maps the throwable to a fallback
 *       value so the pipeline continues with that value instead of propagating the exception.</li>
 *   <li><b>handle(BiFunction):</b> Called for both success and failure. Receives (result, throwable);
 *       returns a new value. Use to convert failure to a default value (e.g. 0 or null).</li>
 * </ul>
 * Best practice: ensure every async chain has a terminal handler so exceptions are not swallowed.
 */
public class AsyncErrorHandling {

    /**
     * First chain: supplyAsync may throw; whenComplete logs result or error;
     * exceptionally provides fallback -1; thenAccept prints final value.
     * Second chain: middle stage throws; handle maps failure to 0 so join() returns 0.
     *
     * @param args unused
     */
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

        // When a stage throws, handle receives (null, throwable) and can return a fallback
        CompletableFuture<Integer> chain = CompletableFuture.supplyAsync(() -> 1, exec)
            .thenApply(n -> { throw new RuntimeException("stage2"); })
            .handle((v, t) -> t != null ? Integer.valueOf(0) : (Integer) v);
        System.out.println("Chain after handle: " + chain.join());

        exec.shutdown();
    }
}
