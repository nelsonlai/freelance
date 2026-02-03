package concurrency.module05;

import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicLong;

/**
 * Mini matching engine: single trading pair; multiple producers enqueue orders
 * to one BlockingQueue; single consumer thread runs the matching loop and
 * applies orders to an in-memory book. Guaranteed ordering and consistency
 * by single-threaded consumer.
 */
public class MiniMatchingEngine {

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

    static class Book {
        final TreeMap<Double, AtomicInteger> bids = new TreeMap<>(Collections.reverseOrder());
        final TreeMap<Double, AtomicInteger> asks = new TreeMap<>();

        void add(boolean buy, double price, int qty) {
            TreeMap<Double, AtomicInteger> side = buy ? bids : asks;
            side.computeIfAbsent(price, p -> new AtomicInteger(0)).addAndGet(qty);
        }

        void match(Order order, java.util.function.Consumer<String> onFill) {
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
