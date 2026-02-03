package concurrency.module07;

import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

/**
 * Pure Java: parallel streams for "big" in-memory collection.
 * Contrast with Spark: same idea (partition → process in parallel → reduce), but single JVM only.
 * No Spark dependency — run with: javac -d out src/.../ParallelStreamsBigData.java && java -cp out concurrency.module07.ParallelStreamsBigData
 */
public class ParallelStreamsBigData {

    public static void main(String[] args) {
        // Simulate a large in-memory dataset (e.g. 100k "events")
        int size = 100_000;
        List<String> words = IntStream.range(0, size)
                .mapToObj(i -> randomWord())
                .collect(Collectors.toList());

        // Parallel "word count" using parallel stream + ConcurrentHashMap
        long start = System.nanoTime();
        Map<String, Long> counts = words.parallelStream()
                .collect(Collectors.groupingByConcurrent(w -> w, Collectors.counting()));
        long elapsed = (System.nanoTime() - start) / 1_000_000;
        System.out.println("Parallel stream word count: " + counts.size() + " distinct words in " + elapsed + " ms");

        // Top 5 by count
        counts.entrySet().parallelStream()
                .sorted(Map.Entry.<String, Long>comparingByValue().reversed())
                .limit(5)
                .forEach(e -> System.out.println("  " + e.getKey() + " -> " + e.getValue()));

        // Compare: sequential vs parallel sum over same data
        List<Integer> numbers = new ArrayList<>();
        for (int i = 0; i < 1_000_000; i++) numbers.add(i % 100);
        long seqSum = numbers.stream().mapToLong(Integer::longValue).sum();
        long parSum = numbers.parallelStream().mapToLong(Integer::longValue).sum();
        System.out.println("\nSequential sum: " + seqSum + ", Parallel sum: " + parSum + " (should match)");
    }

    private static final String[] SAMPLE = { "alpha", "beta", "gamma", "delta", "epsilon", "zeta", "eta", "theta" };

    private static String randomWord() {
        return SAMPLE[new Random().nextInt(SAMPLE.length)];
    }
}
