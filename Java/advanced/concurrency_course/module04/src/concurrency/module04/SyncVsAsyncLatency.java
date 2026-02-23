package concurrency.module04;

import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/**
 * Simple benchmark: N simulated I/O operations (each sleeps ioMs) done either
 * sequentially (sync) or in parallel (async with CompletableFuture).
 *
 * <p>Sync total time ≈ N * ioMs. Async total time ≈ ioMs (all run concurrently).
 * Use this pattern when you have multiple independent I/O calls (e.g. HTTP, DB)
 * that can be issued in parallel to reduce latency.
 */
public class SyncVsAsyncLatency {

    /**
     * Simulates an I/O call by sleeping for the given number of milliseconds.
     * In real code this would be a network or disk call.
     */
    static void simulateIO(long ms) {
        try {
            Thread.sleep(ms);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    /**
     * Runs N simulated I/O calls first in sequence, then in parallel. Prints
     * elapsed time for each; parallel should be roughly ioMs, sequence N*ioMs.
     *
     * @param args unused
     * @throws Exception not thrown in this demo
     */
    public static void main(String[] args) throws Exception {
        int n = 5;
        long ioMs = 100;
        ExecutorService exec = Executors.newFixedThreadPool(n);

        // Sync: one after another; total time = n * ioMs
        long syncStart = System.nanoTime();
        for (int i = 0; i < n; i++) simulateIO(ioMs);
        long syncTime = (System.nanoTime() - syncStart) / 1_000_000;
        System.out.println("Sync " + n + " x " + ioMs + " ms: " + syncTime + " ms");

        // Async: start all N tasks; allOf().join() waits until every one completes
        long asyncStart = System.nanoTime();
        CompletableFuture<?>[] futures = new CompletableFuture[n];
        for (int i = 0; i < n; i++) {
            futures[i] = CompletableFuture.runAsync(() -> simulateIO(ioMs), exec);
        }
        CompletableFuture.allOf(futures).join();
        long asyncTime = (System.nanoTime() - asyncStart) / 1_000_000;
        System.out.println("Async " + n + " x " + ioMs + " ms (parallel): " + asyncTime + " ms");

        exec.shutdown();
        exec.awaitTermination(5, TimeUnit.SECONDS);
    }
}
