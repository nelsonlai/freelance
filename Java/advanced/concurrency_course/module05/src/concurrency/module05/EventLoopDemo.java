package concurrency.module05;

import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicBoolean;

/**
 * Single-thread event loop: poll task queue and "I/O" completion queue;
 * run handlers without blocking the loop (simulated async).
 */
public class EventLoopDemo {

    private final BlockingQueue<Runnable> taskQueue = new LinkedBlockingQueue<>();
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

    public void runOnLoop(Runnable r) {
        taskQueue.offer(r);
    }

    /** Simulate async I/O: run "io" in a separate thread, then enqueue completion on loop. */
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
