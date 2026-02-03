package concurrency.module04;

import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/**
 * Benchmark: N simulated I/O calls in sequence (sync) vs in parallel (async with CompletableFuture).
 * Measures total time to show async wins when work is parallelizable.
 */
public class SyncVsAsyncLatency {

    static void simulateIO(long ms) {
        try {
            Thread.sleep(ms);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    public static void main(String[] args) throws Exception {
        int n = 5;
        long ioMs = 100;
        ExecutorService exec = Executors.newFixedThreadPool(n);

        // Sync: one after another
        long syncStart = System.nanoTime();
        for (int i = 0; i < n; i++) simulateIO(ioMs);
        long syncTime = (System.nanoTime() - syncStart) / 1_000_000;
        System.out.println("Sync " + n + " x " + ioMs + " ms: " + syncTime + " ms");

        // Async: all in parallel
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
