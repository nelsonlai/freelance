package concurrency.module07;

import org.apache.spark.sql.Dataset;
import org.apache.spark.sql.Row;
import org.apache.spark.sql.RowFactory;
import org.apache.spark.sql.SparkSession;
import org.apache.spark.sql.types.DataTypes;
import org.apache.spark.sql.types.Metadata;
import org.apache.spark.sql.types.StructField;
import org.apache.spark.sql.types.StructType;

import java.util.Arrays;
import java.util.List;

import static org.apache.spark.sql.functions.*;

/**
 * SparkSession; DataFrame from in-memory data; select, filter, groupBy, agg.
 * Shows structured concurrent processing with Catalyst optimization.
 */
public class SparkDataFrameDemo {

    public static void main(String[] args) {
        SparkSession spark = SparkSession.builder()
                .appName("SparkDataFrameDemo")
                .master("local[*]")
                .getOrCreate();

        try {
            // Schema for simple "sales" data: product, amount, region
            StructType schema = new StructType(new StructField[]{
                    new StructField("product", DataTypes.StringType, false, Metadata.empty()),
                    new StructField("amount", DataTypes.IntegerType, false, Metadata.empty()),
                    new StructField("region", DataTypes.StringType, false, Metadata.empty())
            });

            List<Row> rows = Arrays.asList(
                    RowFactory.create("A", 100, "North"),
                    RowFactory.create("B", 150, "South"),
                    RowFactory.create("A", 200, "South"),
                    RowFactory.create("B", 80, "North"),
                    RowFactory.create("A", 90, "North")
            );

            Dataset<Row> df = spark.createDataFrame(rows, schema);

            System.out.println("DataFrame (distributed, partition-level parallelism):");
            df.show();

            System.out.println("Filter amount >= 100:");
            df.filter(col("amount").geq(100)).show();

            System.out.println("Aggregation by product (runs in parallel across partitions):");
            df.groupBy("product")
                    .agg(sum("amount").as("total"), count("*").as("count"))
                    .show();

            System.out.println("Aggregation by region:");
            df.groupBy("region")
                    .agg(sum("amount").as("total"))
                    .show();
        } finally {
            spark.stop();
        }
    }
}
