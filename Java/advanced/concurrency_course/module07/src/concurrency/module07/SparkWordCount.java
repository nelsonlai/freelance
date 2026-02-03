package concurrency.module07;

import org.apache.spark.SparkConf;
import org.apache.spark.api.java.JavaPairRDD;
import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.JavaSparkContext;
import scala.Tuple2;

import java.util.Arrays;

/**
 * Full word-count style: parallel text processing with Spark RDD.
 * Uses inline text; in production you would use sc.textFile("path/to/file") for big data.
 */
public class SparkWordCount {

    public static void main(String[] args) {
        SparkConf conf = new SparkConf()
                .setAppName("SparkWordCount")
                .setMaster("local[*]");

        try (JavaSparkContext sc = new JavaSparkContext(conf)) {
            // Simulate "big" text as multiple lines (in real use: sc.textFile("hdfs://...") or "file://...")
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
