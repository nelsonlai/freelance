package concurrency.module03;

import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;

/**
 * Rate limiting using a {@link java.util.concurrent.Semaphore}: the number of
 * permits is the maximum number of concurrent operations. Acquire a permit
 * before running a task; release it when done (in finally so it's always released).
 *
 * <p>This implementation uses a fixed number of permits (no refill). For "N operations
 * per second" you would need a separate mechanism (e.g. refill thread or token bucket).
 */
public class SemaphoreRateLimit {

    private final Semaphore permits;
    private final int maxConcurrent;

    /**
     * Creates a rate limiter that allows at most maxConcurrent operations at once.
     *
     * @param maxConcurrent number of permits (max concurrent tasks)
     */
    public SemaphoreRateLimit(int maxConcurrent) {
        this.maxConcurrent = maxConcurrent;
        this.permits = new Semaphore(maxConcurrent);
    }

    /**
     * Runs the task if a permit is available (non-blocking). Acquires one permit,
     * runs the task, then releases in finally. If no permit is available, returns false
     * without running the task.
     *
     * @param task the runnable to run under the limit
     * @return true if the task was run, false if no permit was available
     */
    public boolean tryRun(Runnable task) {
        if (!permits.tryAcquire()) return false;
        try {
            task.run();
            return true;
        } finally {
            permits.release();
        }
    }

    /**
     * Acquires a permit (blocking if necessary), runs the task, then releases the permit.
     *
     * @param task the runnable to run
     * @throws InterruptedException if interrupted while waiting for a permit
     */
    public void run(Runnable task) throws InterruptedException {
        permits.acquire();
        try {
            task.run();
        } finally {
            permits.release();
        }
    }

    /**
     * Tries to acquire a permit within the given timeout. If acquired, runs the task
     * and returns true; otherwise returns false without running the task.
     *
     * @param task    the runnable to run
     * @param timeout maximum time to wait for a permit
     * @param unit    unit of timeout
     * @return true if the task was run, false if no permit within the timeout
     * @throws InterruptedException if interrupted while waiting
     */
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
