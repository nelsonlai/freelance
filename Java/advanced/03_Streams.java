/**
 * ADVANCED LEVEL - Lesson 3: Streams API (Java 8+)
 * 
 * This lesson covers:
 * - Creating streams
 * - Intermediate operations (filter, map, sorted, distinct, etc.)
 * - Terminal operations (forEach, collect, reduce, etc.)
 * - Parallel streams
 * - Optional class
 */

import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class StreamsExample {
    public static void main(String[] args) {
        System.out.println("=== CREATING STREAMS ===");
        
        // From Collection
        List<String> list = Arrays.asList("apple", "banana", "cherry", "date");
        Stream<String> stream1 = list.stream();
        
        // From Array
        String[] array = {"one", "two", "three"};
        Stream<String> stream2 = Arrays.stream(array);
        
        // Using Stream.of()
        Stream<String> stream3 = Stream.of("x", "y", "z");
        
        // Using Stream.generate()
        Stream<Integer> infiniteStream = Stream.generate(() -> 1).limit(5);
        System.out.println("Generated stream: " + infiniteStream.collect(Collectors.toList()));
        
        // Using Stream.iterate()
        Stream<Integer> iterateStream = Stream.iterate(0, n -> n + 2).limit(5);
        System.out.println("Iterate stream: " + iterateStream.collect(Collectors.toList()));
        
        System.out.println("\n=== INTERMEDIATE OPERATIONS ===");
        
        List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
        
        // Filter - Keep elements matching predicate
        List<Integer> evens = numbers.stream()
            .filter(n -> n % 2 == 0)
            .collect(Collectors.toList());
        System.out.println("Even numbers: " + evens);
        
        // Map - Transform each element
        List<Integer> squared = numbers.stream()
            .map(n -> n * n)
            .collect(Collectors.toList());
        System.out.println("Squared: " + squared);
        
        // Distinct - Remove duplicates
        List<Integer> withDuplicates = Arrays.asList(1, 2, 2, 3, 3, 3, 4);
        List<Integer> unique = withDuplicates.stream()
            .distinct()
            .collect(Collectors.toList());
        System.out.println("Unique: " + unique);
        
        // Sorted - Sort elements
        List<Integer> unsorted = Arrays.asList(5, 2, 8, 1, 9, 3);
        List<Integer> sorted = unsorted.stream()
            .sorted()
            .collect(Collectors.toList());
        System.out.println("Sorted: " + sorted);
        
        // Limit - Take first n elements
        List<Integer> first5 = numbers.stream()
            .limit(5)
            .collect(Collectors.toList());
        System.out.println("First 5: " + first5);
        
        // Skip - Skip first n elements
        List<Integer> skip5 = numbers.stream()
            .skip(5)
            .collect(Collectors.toList());
        System.out.println("Skip first 5: " + skip5);
        
        // FlatMap - Flatten nested structures
        List<List<Integer>> nested = Arrays.asList(
            Arrays.asList(1, 2, 3),
            Arrays.asList(4, 5),
            Arrays.asList(6, 7, 8)
        );
        List<Integer> flattened = nested.stream()
            .flatMap(List::stream)
            .collect(Collectors.toList());
        System.out.println("Flattened: " + flattened);
        
        System.out.println("\n=== TERMINAL OPERATIONS ===");
        
        // ForEach - Perform action on each element
        System.out.print("ForEach: ");
        numbers.stream()
            .filter(n -> n > 5)
            .forEach(n -> System.out.print(n + " "));
        System.out.println();
        
        // Collect - Collect into collection
        List<String> fruits = Arrays.asList("apple", "banana", "cherry", "date");
        List<String> filtered = fruits.stream()
            .filter(f -> f.length() > 5)
            .collect(Collectors.toList());
        System.out.println("Fruits with length > 5: " + filtered);
        
        // Collect to Set
        Set<Integer> numberSet = numbers.stream()
            .collect(Collectors.toSet());
        System.out.println("As Set: " + numberSet);
        
        // Collect to Map
        Map<String, Integer> fruitLengths = fruits.stream()
            .collect(Collectors.toMap(
                fruit -> fruit,
                String::length
            ));
        System.out.println("Fruit lengths map: " + fruitLengths);
        
        // Reduce - Combine elements
        int sum = numbers.stream()
            .reduce(0, Integer::sum);
        System.out.println("Sum: " + sum);
        
        int product = numbers.stream()
            .limit(5)
            .reduce(1, (a, b) -> a * b);
        System.out.println("Product of first 5: " + product);
        
        // Count
        long count = numbers.stream()
            .filter(n -> n % 2 == 0)
            .count();
        System.out.println("Count of even numbers: " + count);
        
        // AnyMatch, AllMatch, NoneMatch
        boolean hasEven = numbers.stream().anyMatch(n -> n % 2 == 0);
        boolean allPositive = numbers.stream().allMatch(n -> n > 0);
        boolean noneNegative = numbers.stream().noneMatch(n -> n < 0);
        System.out.println("Has even: " + hasEven);
        System.out.println("All positive: " + allPositive);
        System.out.println("None negative: " + noneNegative);
        
        // FindFirst, FindAny
        Optional<Integer> firstEven = numbers.stream()
            .filter(n -> n % 2 == 0)
            .findFirst();
        System.out.println("First even: " + firstEven.orElse(-1));
        
        // Min, Max
        Optional<Integer> min = numbers.stream().min(Integer::compare);
        Optional<Integer> max = numbers.stream().max(Integer::compare);
        System.out.println("Min: " + min.orElse(-1));
        System.out.println("Max: " + max.orElse(-1));
        
        System.out.println("\n=== CHAINING OPERATIONS ===");
        
        List<String> result = fruits.stream()
            .filter(f -> f.length() > 4)
            .map(String::toUpperCase)
            .sorted()
            .collect(Collectors.toList());
        System.out.println("Filtered, uppercased, sorted: " + result);
        
        // Complex example
        int sumOfSquaredEvens = numbers.stream()
            .filter(n -> n % 2 == 0)
            .map(n -> n * n)
            .reduce(0, Integer::sum);
        System.out.println("Sum of squared evens: " + sumOfSquaredEvens);
        
        System.out.println("\n=== OPTIONAL CLASS ===");
        
        Optional<String> optional = Optional.of("Hello");
        System.out.println("Optional value: " + optional.get());
        System.out.println("Is present: " + optional.isPresent());
        
        Optional<String> empty = Optional.empty();
        System.out.println("Empty optional: " + empty.orElse("Default"));
        
        Optional<String> nullable = Optional.ofNullable(null);
        System.out.println("Nullable optional: " + nullable.orElse("Default"));
        
        // Optional with map
        Optional<String> upper = optional.map(String::toUpperCase);
        System.out.println("Uppercased: " + upper.get());
        
        System.out.println("\n=== PARALLEL STREAMS ===");
        
        List<Integer> largeList = new ArrayList<>();
        for (int i = 0; i < 1000000; i++) {
            largeList.add(i);
        }
        
        long start = System.currentTimeMillis();
        long sequentialSum = largeList.stream()
            .mapToLong(Integer::longValue)
            .sum();
        long sequentialTime = System.currentTimeMillis() - start;
        
        start = System.currentTimeMillis();
        long parallelSum = largeList.parallelStream()
            .mapToLong(Integer::longValue)
            .sum();
        long parallelTime = System.currentTimeMillis() - start;
        
        System.out.println("Sequential sum: " + sequentialSum + " (Time: " + sequentialTime + "ms)");
        System.out.println("Parallel sum: " + parallelSum + " (Time: " + parallelTime + "ms)");
        
        System.out.println("\n=== GROUPING AND PARTITIONING ===");
        
        List<String> words = Arrays.asList("apple", "banana", "apricot", "cherry", "date");
        
        // Grouping by first letter
        Map<Character, List<String>> grouped = words.stream()
            .collect(Collectors.groupingBy(s -> s.charAt(0)));
        System.out.println("Grouped by first letter: " + grouped);
        
        // Partitioning by condition
        Map<Boolean, List<String>> partitioned = words.stream()
            .collect(Collectors.partitioningBy(s -> s.length() > 5));
        System.out.println("Partitioned by length > 5: " + partitioned);
    }
}

