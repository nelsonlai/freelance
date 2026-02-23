package concurrency.module03;

import java.util.Arrays;
import java.util.List;
import java.util.concurrent.*;

/**
 * Core usage of {@link java.util.concurrent.ExecutorService}: execute (fire-and-forget),
 * submit (returns {@link Future}), and invokeAll (submit many and wait for all).
 *
 * <p>Also demonstrates correct shutdown: call shutdown() to stop accepting new tasks,
 * then awaitTermination() to wait for in-flight tasks. If the timeout elapses, shutdownNow()
 * interrupts workers so the JVM can exit.
 */
public class ExecutorBasics {

    /**
     * Creates a fixed thread pool of 2 threads, runs execute, submit, and invokeAll
     * examples, then shuts down and waits for termination (or forces shutdownNow).
     *
     * @param args unused
     * @throws InterruptedException if interrupted during get() or awaitTermination
     * @throws ExecutionException   if a submitted task throws
     */
    public static void main(String[] args) throws InterruptedException, ExecutionException {
        ExecutorService executor = Executors.newFixedThreadPool(2);

        // execute: fire-and-forget; no return value, no way to wait for completion
        executor.execute(() -> System.out.println("Task 1 " + Thread.currentThread().getName()));

        // submit(Callable): returns a Future; get() blocks until result is available
        Future<Integer> f = executor.submit(() -> {
            Thread.sleep(200);
            return 42;
        });
        System.out.println("Future get: " + f.get());

        // invokeAll: submit all tasks and block until every one has completed; returns list of Futures
        List<Callable<Integer>> tasks = Arrays.asList(() -> 1, () -> 2, () -> 3);
        List<Future<Integer>> futures = executor.invokeAll(tasks);
        for (Future<Integer> fu : futures) {
            System.out.println("invokeAll result: " + fu.get());
        }

        executor.shutdown();
        if (!executor.awaitTermination(5, TimeUnit.SECONDS)) {
            executor.shutdownNow();
        }
    }
}
