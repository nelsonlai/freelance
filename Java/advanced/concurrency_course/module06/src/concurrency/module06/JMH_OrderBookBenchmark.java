package concurrency.module06;

import org.openjdk.jmh.annotations.*;
import org.openjdk.jmh.infra.Blackhole;
import java.util.concurrent.TimeUnit;

/**
 * JMH (Java Microbenchmark Harness) benchmark for {@link OrderBook} operations.
 * Measures throughput of add+cancel and bestBid/bestAsk. Requires JMH dependencies.
 *
 * <p><b>Maven dependencies (pom.xml):</b>
 * <pre>
 * &lt;dependency&gt;
 *   &lt;groupId&gt;org.openjdk.jmh&lt;/groupId&gt;
 *   &lt;artifactId&gt;jmh-core&lt;/artifactId&gt;
 *   &lt;version&gt;1.36&lt;/version&gt;
 * &lt;/dependency&gt;
 * &lt;dependency&gt;
 *   &lt;groupId&gt;org.openjdk.jmh&lt;/groupId&gt;
 *   &lt;artifactId&gt;jmh-generator-annprocess&lt;/artifactId&gt;
 *   &lt;version&gt;1.36&lt;/version&gt;
 * &lt;/dependency&gt;
 * </pre>
 *
 * <p><b>Run:</b> mvn clean install && java -jar target/benchmarks.jar (with jmh-maven-plugin),
 * or use the IDE JMH plugin.
 */
@State(Scope.Thread)
@BenchmarkMode(Mode.Throughput)
@OutputTimeUnit(TimeUnit.MILLISECONDS)
@Fork(1)
@Warmup(iterations = 2)
@Measurement(iterations = 3)
public class JMH_OrderBookBenchmark {

    private OrderBook book;

    /** Runs once per thread before benchmarks; populates the book with 100 levels each side. */
    @Setup
    public void setup() {
        book = new OrderBook("BTC-USD");
        for (int i = 0; i < 100; i++) {
            book.addOrder(true, 100 - i * 0.01, 10, "u" + i);
            book.addOrder(false, 101 + i * 0.01, 10, "u" + i);
        }
    }

    /** Benchmark: one addOrder followed by cancelOrder. Blackhole consumes return values so JIT doesn't optimize away. */
    @Benchmark
    public void addAndCancel(Blackhole bh) {
        long id = book.addOrder(true, 99.5, 1, "bench");
        bh.consume(book.cancelOrder(id));
    }

    /** Benchmark: bestBid and bestAsk. Measures read path throughput. */
    @Benchmark
    public void bestBidAsk(Blackhole bh) {
        bh.consume(book.bestBid());
        bh.consume(book.bestAsk());
    }
}
