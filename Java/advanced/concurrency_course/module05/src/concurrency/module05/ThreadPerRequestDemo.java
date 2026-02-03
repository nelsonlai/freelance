package concurrency.module05;

import java.util.concurrent.atomic.AtomicInteger;

/**
 * Simulates thread-per-request: each "request" gets a new thread.
 * Shows how thread count grows with concurrency (and why this doesn't scale).
 */
public class ThreadPerRequestDemo {

    private static final AtomicInteger threadCount = new AtomicInteger(0);

    static void handleRequest(int requestId) {
        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    public static void main(String[] args) throws InterruptedException {
        int requests = 50;
        Thread[] threads = new Thread[requests];
        for (int i = 0; i < requests; i++) {
            int id = i;
            threads[i] = new Thread(() -> {
                threadCount.incrementAndGet();
                handleRequest(id);
            });
            threads[i].start();
        }
        for (Thread t : threads) t.join();
        System.out.println("Total threads used for " + requests + " requests: " + threadCount.get());
    }
}
