package concurrency.module07;

import org.apache.spark.SparkConf;
import org.apache.spark.api.java.JavaPairRDD;
import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.JavaSparkContext;
import scala.Tuple2;

import java.util.Arrays;

/**
 * Full word-count example with Spark RDD: split text into words, count by word,
 * then sort by word. Uses inline strings here; for real big data you would use
 * {@code sc.textFile("hdfs://path")} or {@code sc.textFile("file:///path")} to
 * read from storage (one partition per block/split by default).
 *
 * <p>Pipeline: flatMap (line → words) → mapToPair (word → (word, 1)) → reduceByKey
 * (sum) → sortByKey. reduceByKey causes a shuffle; sortByKey also shuffles. collect()
 * brings results to the driver.
 */
public class SparkWordCount {

    /**
     * Creates a local Spark context, builds an RDD from three lines of text,
     * runs word count (lowercased) and sortByKey, then prints the result.
     *
     * @param args unused
     */
    public static void main(String[] args) {
        SparkConf conf = new SparkConf()
                .setAppName("SparkWordCount")
                .setMaster("local[*]");

        try (JavaSparkContext sc = new JavaSparkContext(conf)) {
            // In production: JavaRDD<String> textRDD = sc.textFile("path/to/file");
            String[] lines = {
                    "Apache Spark is a unified engine for large-scale data analytics",
                    "Spark runs on Java and supports concurrent distributed processing",
                    "Spark processes data in parallel across many partitions and machines"
            };
            JavaRDD<String> textRDD = sc.parallelize(Arrays.asList(lines), 3);

            JavaPairRDD<String, Integer> counts = textRDD
                    .flatMap(line -> Arrays.asList(line.toLowerCase().split("\\s+")).iterator())
                    .mapToPair(word -> new Tuple2<>(word, 1))
                    .reduceByKey(Integer::sum)
                    .sortByKey();

            System.out.println("Word count (parallel over partitions):");
            counts.collect().forEach(t -> System.out.println("  " + t._1 + ": " + t._2));
        }
    }
}
