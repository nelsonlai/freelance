package concurrency.module06;

/**
 * Simple throughput benchmark for {@link OrderBook} without JMH. Preloads the
 * book with orders, then measures: (1) add + cancel pairs, (2) bestBid/bestAsk
 * reads. Use for quick comparison; for rigorous measurement use
 * {@link JMH_OrderBookBenchmark} with JMH.
 */
public class SimpleOrderBookBenchmark {

    /**
     * Preloads the book with 500 bid and 500 ask levels, then runs two benchmarks:
     * add+cancel pairs and bestBid/bestAsk. Prints elapsed ms and ops/s for add+cancel.
     *
     * @param args unused
     */
    public static void main(String[] args) {
        OrderBook book = new OrderBook("BTC-USD");
        for (int i = 0; i < 500; i++) {
            book.addOrder(true, 100 - i * 0.01, 10, "u" + i);
            book.addOrder(false, 101 + i * 0.01, 10, "u" + i);
        }

        int ops = 1_000_000;
        long start = System.nanoTime();
        for (int i = 0; i < ops; i++) {
            long id = book.addOrder(true, 99.5, 1, "b");
            book.cancelOrder(id);
        }
        long elapsed = (System.nanoTime() - start) / 1_000_000;
        System.out.println("Add+cancel " + ops + " ops: " + elapsed + " ms, " + (ops * 1000L / Math.max(1, elapsed)) + " ops/s");

        start = System.nanoTime();
        for (int i = 0; i < ops; i++) {
            book.bestBid();
            book.bestAsk();
        }
        elapsed = (System.nanoTime() - start) / 1_000_000;
        System.out.println("BestBid/Ask " + ops + " ops: " + elapsed + " ms");
    }
}
