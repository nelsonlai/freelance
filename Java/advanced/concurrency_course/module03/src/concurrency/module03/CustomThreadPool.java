package concurrency.module03;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.atomic.AtomicBoolean;

/**
 * Minimal custom thread pool: fixed number of workers, shared BlockingQueue.
 * Workers take tasks and run them; shutdown stops accepting and drains queue.
 */
public class CustomThreadPool {

    private final BlockingQueue<Runnable> workQueue;
    private final Thread[] workers;
    private final AtomicBoolean shutdown = new AtomicBoolean(false);

    public CustomThreadPool(int nThreads) {
        this.workQueue = new LinkedBlockingQueue<>();
        this.workers = new Thread[nThreads];
        for (int i = 0; i < nThreads; i++) {
            workers[i] = new Thread(() -> {
                while (!shutdown.get() || !workQueue.isEmpty()) {
                    try {
                        Runnable task = workQueue.poll(100, java.util.concurrent.TimeUnit.MILLISECONDS);
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

    public void execute(Runnable task) {
        if (shutdown.get()) throw new IllegalStateException("Pool shut down");
        workQueue.offer(task);
    }

    public void shutdown() {
        shutdown.set(true);
    }

    public void awaitTermination(long timeout, java.util.concurrent.TimeUnit unit) throws InterruptedException {
        long deadline = System.nanoTime() + unit.toNanos(timeout);
        for (Thread w : workers) {
            long remaining = deadline - System.nanoTime();
            if (remaining <= 0) break;
            w.join(java.util.concurrent.TimeUnit.NANOSECONDS.toMillis(remaining));
        }
    }

    public static void main(String[] args) throws InterruptedException {
        CustomThreadPool pool = new CustomThreadPool(2);
        for (int i = 0; i < 5; i++) {
            int id = i;
            pool.execute(() -> System.out.println(Thread.currentThread().getName() + " runs task " + id));
        }
        pool.shutdown();
        pool.awaitTermination(5, java.util.concurrent.TimeUnit.SECONDS);
    }
}
