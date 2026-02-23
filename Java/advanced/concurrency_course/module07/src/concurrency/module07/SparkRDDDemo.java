package concurrency.module07;

import org.apache.spark.SparkConf;
import org.apache.spark.api.java.JavaPairRDD;
import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.JavaSparkContext;
import scala.Tuple2;

import java.util.Arrays;
import java.util.List;

/**
 * Demonstrates Apache Spark RDD (Resilient Distributed Dataset) in local mode:
 * create an RDD from an in-memory collection, then apply transformations
 * (flatMap, mapToPair, filter) and actions (reduceByKey, count, collect).
 *
 * <p>In local mode, Spark uses multiple threads to process partitions in parallel;
 * the same code would run on a cluster with data distributed across machines.
 * Transformations are lazy; actions (e.g. collect, count) trigger execution.
 *
 * <p><b>Word count pattern:</b> flatMap (line → words) → mapToPair (word → (word, 1))
 * → reduceByKey (sum counts). This is the canonical example of concurrent big-data processing.
 */
public class SparkRDDDemo {

    /**
     * Builds a local Spark context, creates an RDD from a small list of lines,
     * runs word count and a filter/count example, then closes the context.
     *
     * @param args unused
     */
    public static void main(String[] args) {
        SparkConf conf = new SparkConf()
                .setAppName("SparkRDDDemo")
                .setMaster("local[*]");  // local mode, use all available cores

        try (JavaSparkContext sc = new JavaSparkContext(conf)) {
            // parallelize() distributes the collection into partitions; 2 partitions for demo
            List<String> data = Arrays.asList(
                    "apple banana apple",
                    "banana cherry apple",
                    "cherry apple banana"
            );
            JavaRDD<String> lines = sc.parallelize(data, 2);

            // Word count: flatMap (each line → words), mapToPair (word → (word,1)), reduceByKey (sum)
            JavaPairRDD<String, Integer> wordCounts = lines
                    .flatMap(line -> Arrays.asList(line.split("\\s+")).iterator())
                    .mapToPair(word -> new Tuple2<>(word, 1))
                    .reduceByKey(Integer::sum);

            System.out.println("Word counts (processed in parallel across partitions):");
            wordCounts.collect().forEach(t -> System.out.println("  " + t._1 + " -> " + t._2));

            // Another pattern: flatten to words, filter, then count (action)
            JavaRDD<String> words = lines.flatMap(line -> Arrays.asList(line.split("\\s+")).iterator());
            long countApple = words.filter("apple"::equals).count();
            System.out.println("\nCount of 'apple': " + countApple);
        }
    }
}
