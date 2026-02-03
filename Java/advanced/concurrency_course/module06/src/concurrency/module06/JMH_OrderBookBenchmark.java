package concurrency.module06;

import org.openjdk.jmh.annotations.*;
import org.openjdk.jmh.infra.Blackhole;
import java.util.concurrent.TimeUnit;

/**
 * JMH benchmark skeleton for OrderBook operations. Add JMH dependencies to run:
 *
 * Add to pom.xml (Maven):
 *   <dependency>
 *     <groupId>org.openjdk.jmh</groupId>
 *     <artifactId>jmh-core</artifactId>
 *     <version>1.36</version>
 *   </dependency>
 *   <dependency>
 *     <groupId>org.openjdk.jmh</groupId>
 *     <artifactId>jmh-generator-annprocess</artifactId>
 *     <version>1.36</version>
 *   </dependency>
 *
 * Run: mvn clean install && java -jar target/benchmarks.jar (with jmh-maven-plugin)
 * Or use IDE JMH plugin.
 */
@State(Scope.Thread)
@BenchmarkMode(Mode.Throughput)
@OutputTimeUnit(TimeUnit.MILLISECONDS)
@Fork(1)
@Warmup(iterations = 2)
@Measurement(iterations = 3)
public class JMH_OrderBookBenchmark {

    private OrderBook book;

    @Setup
    public void setup() {
        book = new OrderBook("BTC-USD");
        for (int i = 0; i < 100; i++) {
            book.addOrder(true, 100 - i * 0.01, 10, "u" + i);
            book.addOrder(false, 101 + i * 0.01, 10, "u" + i);
        }
    }

    @Benchmark
    public void addAndCancel(Blackhole bh) {
        long id = book.addOrder(true, 99.5, 1, "bench");
        bh.consume(book.cancelOrder(id));
    }

    @Benchmark
    public void bestBidAsk(Blackhole bh) {
        bh.consume(book.bestBid());
        bh.consume(book.bestAsk());
    }
}
