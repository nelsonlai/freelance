package concurrency.module07;

import org.apache.spark.SparkConf;
import org.apache.spark.api.java.JavaPairRDD;
import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.JavaSparkContext;
import scala.Tuple2;

import java.util.Arrays;
import java.util.List;

/**
 * Local SparkContext; RDD from collection; map, filter, reduceByKey.
 * Demonstrates concurrent processing of data across partitions (local = multiple threads).
 */
public class SparkRDDDemo {

    public static void main(String[] args) {
        SparkConf conf = new SparkConf()
                .setAppName("SparkRDDDemo")
                .setMaster("local[*]");  // use all cores locally

        try (JavaSparkContext sc = new JavaSparkContext(conf)) {
            // RDD from in-memory collection — partitioned and processed in parallel
            List<String> data = Arrays.asList(
                    "apple banana apple",
                    "banana cherry apple",
                    "cherry apple banana"
            );
            JavaRDD<String> lines = sc.parallelize(data, 2);  // 2 partitions for demo

            // Word count: flatMap -> mapToPair -> reduceByKey (classic concurrent big-data pattern)
            JavaPairRDD<String, Integer> wordCounts = lines
                    .flatMap(line -> Arrays.asList(line.split("\\s+")).iterator())
                    .mapToPair(word -> new Tuple2<>(word, 1))
                    .reduceByKey(Integer::sum);

            System.out.println("Word counts (processed in parallel across partitions):");
            wordCounts.collect().forEach(t -> System.out.println("  " + t._1 + " -> " + t._2));

            // Filter + map example
            JavaRDD<String> words = lines.flatMap(line -> Arrays.asList(line.split("\\s+")).iterator());
            long countApple = words.filter("apple"::equals).count();
            System.out.println("\nCount of 'apple': " + countApple);
        }
    }
}
