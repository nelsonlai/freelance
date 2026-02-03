package concurrency.module06;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.atomic.AtomicLong;

/**
 * Conceptual pipeline: ingest queue -> matching (single consumer) -> fill queue.
 * Demonstrates separation: matching, risk, settlement are separate stages.
 */
public class ExchangePipeline {

    static class IncomingOrder {
        final long id;
        final boolean buy;
        final double price;
        final int quantity;
        final String userId;

        IncomingOrder(long id, boolean buy, double price, int quantity, String userId) {
            this.id = id;
            this.buy = buy;
            this.price = price;
            this.quantity = quantity;
            this.userId = userId;
        }
    }

    static class Fill {
        final long orderId;
        final double price;
        final int quantity;

        Fill(long orderId, double price, int quantity) {
            this.orderId = orderId;
            this.price = price;
            this.quantity = quantity;
        }
    }

    private final BlockingQueue<IncomingOrder> ingestQueue = new LinkedBlockingQueue<>();
    private final BlockingQueue<Fill> fillQueue = new LinkedBlockingQueue<>();
    private final OrderBook book;
    private final AtomicLong orderIdGen = new AtomicLong(0);
    private volatile boolean running = true;
    private final Thread matchingThread;

    public ExchangePipeline(String symbol) {
        this.book = new OrderBook(symbol);
        matchingThread = new Thread(() -> {
            while (running) {
                try {
                    IncomingOrder in = ingestQueue.poll(100, java.util.concurrent.TimeUnit.MILLISECONDS);
                    if (in != null) {
                        OrderBook.Order order = new OrderBook.Order(in.id, in.buy, in.price, in.quantity, in.userId);
                        for (double[] f : book.match(order)) {
                            fillQueue.offer(new Fill(in.id, f[0], (int) f[1]));
                        }
                    }
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    break;
                }
            }
        });
        matchingThread.start();
    }

    public long submitOrder(boolean buy, double price, int quantity, String userId) {
        long id = orderIdGen.incrementAndGet();
        ingestQueue.offer(new IncomingOrder(id, buy, price, quantity, userId));
        return id;
    }

    public BlockingQueue<Fill> getFillQueue() {
        return fillQueue;
    }

    public void stop() {
        running = false;
        matchingThread.interrupt();
    }
}
