package concurrency.module05;

import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicBoolean;

/**
 * Single-thread event loop: one thread repeatedly polls a task queue and an
 * "I/O completion" queue, running handlers one at a time. No handler blocks
 * the loop; I/O is simulated by running work in another thread and enqueueing
 * a completion callback to be run on the loop.
 *
 * <p>Used in Node.js, Netty, and many exchange/gateway designs: all application
 * logic runs on one thread, so no locks are needed for shared state; I/O is
 * delegated and results are processed when completions arrive.
 */
public class EventLoopDemo {

    /** Pending tasks to run on the loop (e.g. timers or enqueued work). */
    private final BlockingQueue<Runnable> taskQueue = new LinkedBlockingQueue<>();
    /** Callbacks to run when "I/O" completes; submitted by submitIO. */
    private final BlockingQueue<Runnable> ioCompletions = new LinkedBlockingQueue<>();
    private final AtomicBoolean running = new AtomicBoolean(true);
    private final Thread loopThread;

    public EventLoopDemo() {
        loopThread = new Thread(() -> {
            while (running.get()) {
                try {
                    Runnable task = taskQueue.poll();
                    if (task != null) {
                        task.run();
                        continue;
                    }
                    // Block briefly for I/O completions so we don't busy-spin
                    Runnable io = ioCompletions.poll(10, TimeUnit.MILLISECONDS);
                    if (io != null) io.run();
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    break;
                }
            }
        });
        loopThread.start();
    }

    /** Schedules a task to run on the event loop thread. Non-blocking. */
    public void runOnLoop(Runnable r) {
        taskQueue.offer(r);
    }

    /**
     * Submits I/O work to run in a separate thread. When the I/O finishes,
     * onComplete is enqueued to the loop so it runs on the loop thread (no
     * shared-state races with other handlers).
     *
     * @param io        the blocking I/O work (e.g. socket read)
     * @param onComplete callback to run on the loop when io finishes
     */
    public void submitIO(Runnable io, Runnable onComplete) {
        Executors.newSingleThreadExecutor().execute(() -> {
            io.run();
            ioCompletions.offer(onComplete);
        });
    }

    public void stop() {
        running.set(false);
        loopThread.interrupt();
    }

    public static void main(String[] args) throws InterruptedException {
        EventLoopDemo loop = new EventLoopDemo();
        loop.runOnLoop(() -> System.out.println("Task 1"));
        loop.submitIO(() -> {
            try { Thread.sleep(50); } catch (InterruptedException e) { Thread.currentThread().interrupt(); }
        }, () -> System.out.println("IO complete"));
        Thread.sleep(200);
        loop.stop();
    }
}
