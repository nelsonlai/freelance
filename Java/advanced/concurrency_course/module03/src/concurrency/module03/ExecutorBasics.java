package concurrency.module03;

import java.util.concurrent.*;

/**
 * Executor basics: execute vs submit; Future; shutdown and awaitTermination.
 * Demonstrates correct shutdown to avoid leaving threads running.
 */
public class ExecutorBasics {

    public static void main(String[] args) throws InterruptedException, ExecutionException {
        ExecutorService executor = Executors.newFixedThreadPool(2);

        // execute: fire-and-forget
        executor.execute(() -> System.out.println("Task 1 " + Thread.currentThread().getName()));

        // submit: returns Future
        Future<Integer> f = executor.submit(() -> {
            Thread.sleep(200);
            return 42;
        });
        System.out.println("Future get: " + f.get());

        // invokeAll: wait for all
        java.util.List<Callable<Integer>> tasks = java.util.Arrays.asList(() -> 1, () -> 2, () -> 3);
        java.util.List<Future<Integer>> futures = executor.invokeAll(tasks);
        for (Future<Integer> fu : futures) {
            System.out.println("invokeAll result: " + fu.get());
        }

        executor.shutdown();
        if (!executor.awaitTermination(5, TimeUnit.SECONDS)) {
            executor.shutdownNow();
        }
    }
}
