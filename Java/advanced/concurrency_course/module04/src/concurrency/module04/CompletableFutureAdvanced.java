package concurrency.module04;

import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * Advanced {@link java.util.concurrent.CompletableFuture} usage: chaining, combining,
 * and exception handling.
 *
 * <p><b>Chaining:</b>
 * <ul>
 *   <li><b>thenApply:</b> Synchronous transformation (T → U). Runs in the same thread
 *       that completed the previous stage (or default executor). Use when the step is quick.</li>
 *   <li><b>thenCompose:</b> Chain another async operation (T → CompletableFuture&lt;U&gt;).
 *       Use when the next step returns a Future; avoids nested CompletableFuture.</li>
 * </ul>
 * <p><b>Combining:</b> thenCombine (two futures → one result); allOf (wait for all, result Void).
 * <p><b>Exception:</b> handle(BiFunction) receives (result, throwable) and returns a new value.
 */
public class CompletableFutureAdvanced {

    /**
     * Demonstrates thenApply (sync), thenCompose (async chain), thenCombine, allOf,
     * and handle for exception recovery.
     *
     * @param args unused
     * @throws Exception from get() if not using handle/exceptionally
     */
    public static void main(String[] args) throws Exception {
        ExecutorService exec = Executors.newFixedThreadPool(4);

        // thenApply: sync transformation; runs when previous stage completes
        CompletableFuture<String> f1 = CompletableFuture.supplyAsync(() -> "hello", exec)
            .thenApply(s -> s + " world");
        System.out.println(f1.get());

        // thenCompose: next step returns CompletableFuture; flattens to one future
        CompletableFuture<String> f2 = CompletableFuture.supplyAsync(() -> "a", exec)
            .thenCompose(s -> CompletableFuture.supplyAsync(() -> s + "-async", exec));
        System.out.println(f2.get());

        // thenCombine: when both fa and fb complete, combine their results with the bifunction
        CompletableFuture<Integer> fa = CompletableFuture.supplyAsync(() -> 10, exec);
        CompletableFuture<Integer> fb = CompletableFuture.supplyAsync(() -> 32, exec);
        CompletableFuture<Integer> combined = fa.thenCombine(fb, Integer::sum);
        System.out.println("Combined: " + combined.get());

        // allOf: one future that completes when all of c1,c2,c3 complete; result is Void
        CompletableFuture<String> c1 = CompletableFuture.supplyAsync(() -> "1", exec);
        CompletableFuture<String> c2 = CompletableFuture.supplyAsync(() -> "2", exec);
        CompletableFuture<String> c3 = CompletableFuture.supplyAsync(() -> "3", exec);
        CompletableFuture<Void> all = CompletableFuture.allOf(c1, c2, c3);
        all.thenRun(() -> System.out.println("All done: " + List.of(c1.join(), c2.join(), c3.join()))).join();

        // handle: on exception, (v, ex) has ex non-null; return fallback value so chain continues
        CompletableFuture<Integer> bad = CompletableFuture
            .<Integer>supplyAsync(() -> { throw new RuntimeException("fail"); }, exec)
            .handle((v, ex) -> ex != null ? -1 : v);
        System.out.println("After exception: " + bad.get());

        exec.shutdown();
    }
}
