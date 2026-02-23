package concurrency.module03;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;

/**
 * A minimal custom thread pool: a fixed number of worker threads and a shared
 * {@link BlockingQueue} of tasks. Workers repeatedly take a task from the queue
 * and run it. Shutdown sets a flag so no new tasks are accepted; workers drain
 * the queue then exit.
 *
 * <p>Compare with {@link java.util.concurrent.ThreadPoolExecutor}: production
 * code should use the JDK executor for rejection policies, lifecycle, and tuning.
 */
public class CustomThreadPool {

    /** Queue of pending tasks. Workers poll from here; execute() offers to here. */
    private final BlockingQueue<Runnable> workQueue;
    /** Fixed set of worker threads. */
    private final Thread[] workers;
    /** When true, execute() rejects and workers exit after draining the queue. */
    private final AtomicBoolean shutdown = new AtomicBoolean(false);

    /**
     * Creates nThreads worker threads. Each worker loops: poll a task (with timeout
     * so we can check shutdown), run it if non-null. Exits when shutdown is true
     * and the queue is empty.
     *
     * @param nThreads number of worker threads
     */
    public CustomThreadPool(int nThreads) {
        this.workQueue = new LinkedBlockingQueue<>();
        this.workers = new Thread[nThreads];
        for (int i = 0; i < nThreads; i++) {
            workers[i] = new Thread(() -> {
                while (!shutdown.get() || !workQueue.isEmpty()) {
                    try {
                        Runnable task = workQueue.poll(100, TimeUnit.MILLISECONDS);
                        if (task != null) task.run();
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                        break;
                    }
                }
            }, "worker-" + i);
            workers[i].start();
        }
    }

    /**
     * Submits a task to the queue. Throws if the pool is already shut down.
     *
     * @param task the runnable to execute
     * @throws IllegalStateException if shutdown() has been called
     */
    public void execute(Runnable task) {
        if (shutdown.get()) throw new IllegalStateException("Pool shut down");
        workQueue.offer(task);
    }

    /** Signals the pool to stop accepting new tasks; workers will drain the queue and exit. */
    public void shutdown() {
        shutdown.set(true);
    }

    /**
     * Waits for all worker threads to terminate, up to the given timeout.
     *
     * @param timeout maximum time to wait
     * @param unit    unit of timeout
     * @throws InterruptedException if interrupted while joining
     */
    public void awaitTermination(long timeout, TimeUnit unit) throws InterruptedException {
        long deadline = System.nanoTime() + unit.toNanos(timeout);
        for (Thread w : workers) {
            long remaining = deadline - System.nanoTime();
            if (remaining <= 0) break;
            w.join(TimeUnit.NANOSECONDS.toMillis(remaining));
        }
    }

    public static void main(String[] args) throws InterruptedException {
        CustomThreadPool pool = new CustomThreadPool(2);
        for (int i = 0; i < 5; i++) {
            int id = i;
            pool.execute(() -> System.out.println(Thread.currentThread().getName() + " runs task " + id));
        }
        pool.shutdown();
        // Error if add pool.execute() after shutdown()
        pool.awaitTermination(5, TimeUnit.SECONDS);
    }
}
