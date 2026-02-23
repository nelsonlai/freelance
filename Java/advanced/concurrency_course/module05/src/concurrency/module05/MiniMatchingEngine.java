package concurrency.module05;

import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicLong;
import java.util.function.Consumer;

/**
 * Mini matching engine for a single trading pair: many threads can submit orders
 * via a {@link BlockingQueue}; a single consumer thread runs the matching loop
 * and updates an in-memory order book. Ordering and consistency are guaranteed
 * because only one thread touches the book.
 *
 * <p>Matching: buy orders match against best (lowest) ask; sell orders against
 * best (highest) bid. Filled quantity is reported via a callback; unfilled
 * remainder is added to the book.
 */
public class MiniMatchingEngine {

    /** Immutable order: id, side (buy/sell), limit price, quantity, user. */
    public static final class Order {
        final long id;
        final boolean buy;
        final double price;
        final int quantity;
        final String userId;

        Order(long id, boolean buy, double price, int quantity, String userId) {
            this.id = id;
            this.buy = buy;
            this.price = price;
            this.quantity = quantity;
            this.userId = userId;
        }
    }

    /**
     * Order book: bids (price → quantity) descending, asks ascending.
     * add() adds resting quantity; match() matches an incoming order against
     * the opposite side, then adds any remainder to the book.
     */
    static class Book {
        final TreeMap<Double, AtomicInteger> bids = new TreeMap<>(Collections.reverseOrder());
        final TreeMap<Double, AtomicInteger> asks = new TreeMap<>();

        void add(boolean buy, double price, int qty) {
            TreeMap<Double, AtomicInteger> side = buy ? bids : asks;
            side.computeIfAbsent(price, p -> new AtomicInteger(0)).addAndGet(qty);
        }

        /**
         * Matches the order against the opposite side: for a buy, walk asks from
         * lowest; for a sell, walk bids from highest. Fill until price no longer
         * crosses or quantity exhausted. Call onFill for each fill; add remainder to book.
         */
        void match(Order order, Consumer<String> onFill) {
            TreeMap<Double, AtomicInteger> opposite = order.buy ? asks : bids;
            Iterator<Map.Entry<Double, AtomicInteger>> it = opposite.entrySet().iterator();
            int remaining = order.quantity;
            while (it.hasNext() && remaining > 0) {
                Map.Entry<Double, AtomicInteger> e = it.next();
                double price = e.getKey();
                if (order.buy && price > order.price) break;
                if (!order.buy && price < order.price) break;
                int available = e.getValue().get();
                int fill = Math.min(remaining, available);
                if (fill > 0) {
                    e.getValue().addAndGet(-fill);
                    remaining -= fill;
                    onFill.accept("FILL orderId=" + order.id + " price=" + price + " qty=" + fill);
                }
                if (e.getValue().get() <= 0) it.remove();
            }
            if (remaining > 0) add(order.buy, order.price, remaining);
        }
    }

    private final BlockingQueue<Order> orderQueue = new LinkedBlockingQueue<>();
    private final Book book = new Book();
    private final AtomicLong orderIdGen = new AtomicLong(0);
    private volatile boolean running = true;
    private final Thread matcherThread;

    public MiniMatchingEngine() {
        matcherThread = new Thread(() -> {
            while (running) {
                try {
                    Order order = orderQueue.poll(100, TimeUnit.MILLISECONDS);
                    if (order != null) {
                        book.match(order, System.out::println);
                    }
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    break;
                }
            }
        });
        matcherThread.start();
    }

    /**
     * Submits an order to the matching engine. Returns immediately with an order id;
     * matching happens asynchronously on the matcher thread.
     *
     * @return the assigned order id
     */
    public long submit(boolean buy, double price, int quantity, String userId) {
        long id = orderIdGen.incrementAndGet();
        orderQueue.offer(new Order(id, buy, price, quantity, userId));
        return id;
    }

    public void stop() {
        running = false;
        matcherThread.interrupt();
    }

    public static void main(String[] args) throws InterruptedException {
        MiniMatchingEngine engine = new MiniMatchingEngine();
        engine.submit(true, 100.0, 10, "u1");
        engine.submit(false, 100.0, 5, "u2");
        engine.submit(false, 99.0, 10, "u3");
        Thread.sleep(500);
        engine.stop();
    }
}
