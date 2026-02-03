package concurrency.module04;

import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * CompletableFuture: chaining (thenApply, thenCompose), combining (thenCombine, allOf),
 * and exception handling (exceptionally, handle).
 */
public class CompletableFutureAdvanced {

    public static void main(String[] args) throws Exception {
        ExecutorService exec = Executors.newFixedThreadPool(4);

        // thenApply: sync transformation
        CompletableFuture<String> f1 = CompletableFuture.supplyAsync(() -> "hello", exec)
            .thenApply(s -> s + " world");
        System.out.println(f1.get());

        // thenCompose: chain async (avoid blocking get inside chain)
        CompletableFuture<String> f2 = CompletableFuture.supplyAsync(() -> "a", exec)
            .thenCompose(s -> CompletableFuture.supplyAsync(() -> s + "-async", exec));
        System.out.println(f2.get());

        // thenCombine: combine two futures
        CompletableFuture<Integer> fa = CompletableFuture.supplyAsync(() -> 10, exec);
        CompletableFuture<Integer> fb = CompletableFuture.supplyAsync(() -> 32, exec);
        CompletableFuture<Integer> combined = fa.thenCombine(fb, Integer::sum);
        System.out.println("Combined: " + combined.get());

        // allOf: wait for all (result is Void; collect manually)
        CompletableFuture<String> c1 = CompletableFuture.supplyAsync(() -> "1", exec);
        CompletableFuture<String> c2 = CompletableFuture.supplyAsync(() -> "2", exec);
        CompletableFuture<String> c3 = CompletableFuture.supplyAsync(() -> "3", exec);
        CompletableFuture<Void> all = CompletableFuture.allOf(c1, c2, c3);
        all.thenRun(() -> System.out.println("All done: " + List.of(c1.join(), c2.join(), c3.join()))).join();

        // Exception: handle maps failure to fallback value
        CompletableFuture<Integer> bad = CompletableFuture
            .<Integer>supplyAsync(() -> { throw new RuntimeException("fail"); }, exec)
            .handle((v, ex) -> ex != null ? -1 : v);
        System.out.println("After exception: " + bad.get());

        exec.shutdown();
    }
}
