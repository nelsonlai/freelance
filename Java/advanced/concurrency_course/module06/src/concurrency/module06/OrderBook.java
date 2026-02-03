package concurrency.module06;

import java.util.*;
import java.util.concurrent.atomic.AtomicLong;

/**
 * In-memory order book for one instrument: bids and asks (price-time priority).
 * Single-threaded use only (e.g. from one matching thread). Not thread-safe.
 */
public class OrderBook {

    private final String symbol;
    private final TreeMap<Double, List<Order>> bids = new TreeMap<>(Comparator.reverseOrder());
    private final TreeMap<Double, List<Order>> asks = new TreeMap<>();
    private final Map<Long, Order> byId = new HashMap<>();
    private final AtomicLong idGen = new AtomicLong(0);

    public static class Order {
        final long id;
        final boolean buy;
        final double price;
        int quantity;
        final String userId;

        Order(long id, boolean buy, double price, int quantity, String userId) {
            this.id = id;
            this.buy = buy;
            this.price = price;
            this.quantity = quantity;
            this.userId = userId;
        }
    }

    public OrderBook(String symbol) {
        this.symbol = symbol;
    }

    public long addOrder(boolean buy, double price, int quantity, String userId) {
        long id = idGen.incrementAndGet();
        Order order = new Order(id, buy, price, quantity, userId);
        byId.put(id, order);
        TreeMap<Double, List<Order>> side = buy ? bids : asks;
        side.computeIfAbsent(price, p -> new ArrayList<>()).add(order);
        return id;
    }

    public boolean cancelOrder(long orderId) {
        Order order = byId.remove(orderId);
        if (order == null) return false;
        TreeMap<Double, List<Order>> side = order.buy ? bids : asks;
        List<Order> level = side.get(order.price);
        if (level != null) {
            level.remove(order);
            if (level.isEmpty()) side.remove(order.price);
        }
        return true;
    }

    /** Match incoming order against book; return list of fills (price, qty). */
    public List<double[]> match(Order incoming) {
        List<double[]> fills = new ArrayList<>();
        TreeMap<Double, List<Order>> opposite = incoming.buy ? asks : bids;
        int remaining = incoming.quantity;
        Iterator<Map.Entry<Double, List<Order>>> levelIt = opposite.entrySet().iterator();
        while (levelIt.hasNext() && remaining > 0) {
            Map.Entry<Double, List<Order>> levelEntry = levelIt.next();
            double price = levelEntry.getKey();
            if (incoming.buy && price > incoming.price) break;
            if (!incoming.buy && price < incoming.price) break;
            List<Order> level = levelEntry.getValue();
            Iterator<Order> orderIt = level.iterator();
            while (orderIt.hasNext() && remaining > 0) {
                Order resting = orderIt.next();
                int fillQty = Math.min(remaining, resting.quantity);
                if (fillQty > 0) {
                    fills.add(new double[] { price, fillQty });
                    remaining -= fillQty;
                    resting.quantity -= fillQty;
                    if (resting.quantity <= 0) {
                        orderIt.remove();
                        byId.remove(resting.id);
                    }
                }
            }
            if (level.isEmpty()) levelIt.remove();
        }
        if (remaining > 0) addOrder(incoming.buy, incoming.price, remaining, incoming.userId);
        return fills;
    }

    public OptionalDouble bestBid() {
        return bids.isEmpty() ? OptionalDouble.empty() : OptionalDouble.of(bids.firstKey());
    }

    public OptionalDouble bestAsk() {
        return asks.isEmpty() ? OptionalDouble.empty() : OptionalDouble.of(asks.firstKey());
    }

    public static void main(String[] args) {
        OrderBook book = new OrderBook("BTC-USD");
        book.addOrder(true, 100, 10, "u1");
        book.addOrder(false, 101, 5, "u2");
        Order in = new Order(0, true, 101, 3, "u3");
        List<double[]> fills = book.match(in);
        fills.forEach(f -> System.out.println("Fill: price=" + f[0] + " qty=" + f[1]));
    }
}
