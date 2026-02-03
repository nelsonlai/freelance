package concurrency.module03;

import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;

/**
 * Rate limiting using a Semaphore: N permits = max N concurrent operations.
 * Optional: refill permits periodically for "per second" style limits (here we use fixed permits for simplicity).
 */
public class SemaphoreRateLimit {

    private final Semaphore permits;
    private final int maxConcurrent;

    public SemaphoreRateLimit(int maxConcurrent) {
        this.maxConcurrent = maxConcurrent;
        this.permits = new Semaphore(maxConcurrent);
    }

    /** Run task if a permit is available; otherwise returns false. */
    public boolean tryRun(Runnable task) {
        if (!permits.tryAcquire()) return false;
        try {
            task.run();
            return true;
        } finally {
            permits.release();
        }
    }

    /** Run task, blocking until a permit is available. */
    public void run(Runnable task) throws InterruptedException {
        permits.acquire();
        try {
            task.run();
        } finally {
            permits.release();
        }
    }

    public boolean tryRunWithTimeout(Runnable task, long timeout, TimeUnit unit) throws InterruptedException {
        if (!permits.tryAcquire(timeout, unit)) return false;
        try {
            task.run();
            return true;
        } finally {
            permits.release();
        }
    }

    public static void main(String[] args) throws InterruptedException {
        SemaphoreRateLimit limiter = new SemaphoreRateLimit(2);
        for (int i = 0; i < 5; i++) {
            int id = i;
            boolean ran = limiter.tryRun(() -> System.out.println("Task " + id + " running"));
            if (!ran) System.out.println("Task " + id + " rejected (no permit)");
        }
    }
}
