package concurrency.module05;

import java.util.concurrent.atomic.AtomicInteger;

/**
 * Simulates the "thread-per-request" model: each incoming request is handled
 * by a new thread. Demonstrates that the number of threads grows with the
 * number of concurrent requests.
 *
 * <p><b>Why it doesn't scale:</b> Threads have non-trivial memory (stack) and
 * context-switch cost. Under high load you can run out of threads or CPU. Real
 * servers use a thread pool (fixed number of threads) or an event loop / async
 * I/O so that many requests are multiplexed onto fewer threads.
 *
 * @see EventLoopDemo for a single-thread event loop
 * @see concurrency.module03.ExecutorBasics for thread pools
 */
public class ThreadPerRequestDemo {

    /** Approximate count of threads that have run (each request increments once). */
    private static final AtomicInteger threadCount = new AtomicInteger(0);

    /**
     * Simulates request handling (e.g. I/O or computation). Here just sleeps.
     *
     * @param requestId id of the request (for logging)
     */
    static void handleRequest(int requestId) {
        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    /**
     * Starts one thread per "request"; each thread runs handleRequest then exits.
     * Prints total threads used to show linear growth with request count.
     *
     * @param args unused
     * @throws InterruptedException if interrupted during join
     */
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
