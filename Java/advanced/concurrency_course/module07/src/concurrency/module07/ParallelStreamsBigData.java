package concurrency.module07;

import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

/**
 * Pure Java parallel streams for "big" in-memory collections: no Spark dependency.
 * Demonstrates the same idea as Spark — partition data, process in parallel, reduce —
 * but within a single JVM using the ForkJoin common pool.
 *
 * <p><b>Contrast with Spark:</b> Spark distributes across machines and handles
 * fault tolerance; parallel streams are limited to one JVM and available cores.
 * Use parallel streams when data fits in memory and single-machine parallelism
 * is enough.
 *
 * <p>Run without Spark: javac -d out src/.../ParallelStreamsBigData.java && java -cp out concurrency.module07.ParallelStreamsBigData
 */
public class ParallelStreamsBigData {

    /** Sample words for generating random "events". */
    private static final String[] SAMPLE = { "alpha", "beta", "gamma", "delta", "epsilon", "zeta", "eta", "theta" };

    private static String randomWord() {
        return SAMPLE[new Random().nextInt(SAMPLE.length)];
    }

    /**
     * (1) Builds a list of 100k random words, then runs a parallel "word count"
     * using groupingByConcurrent so the map is thread-safe during reduction.
     * (2) Finds top 5 words by count using a parallel stream. (3) Compares
     * sequential vs parallel sum on 1M integers to show both give the same result.
     *
     * @param args unused
     */
    public static void main(String[] args) {
        int size = 100_000;
        List<String> words = IntStream.range(0, size)
                .mapToObj(i -> randomWord())
                .collect(Collectors.toList());

        long start = System.nanoTime();
        Map<String, Long> counts = words.parallelStream()
                .collect(Collectors.groupingByConcurrent(w -> w, Collectors.counting()));
        long elapsed = (System.nanoTime() - start) / 1_000_000;
        System.out.println("Parallel stream word count: " + counts.size() + " distinct words in " + elapsed + " ms");

        counts.entrySet().parallelStream()
                .sorted(Map.Entry.<String, Long>comparingByValue().reversed())
                .limit(5)
                .forEach(e -> System.out.println("  " + e.getKey() + " -> " + e.getValue()));

        List<Integer> numbers = new ArrayList<>();
        for (int i = 0; i < 1_000_000; i++) numbers.add(i % 100);
        long seqSum = numbers.stream().mapToLong(Integer::longValue).sum();
        long parSum = numbers.parallelStream().mapToLong(Integer::longValue).sum();
        System.out.println("\nSequential sum: " + seqSum + ", Parallel sum: " + parSum + " (should match)");
    }
}
