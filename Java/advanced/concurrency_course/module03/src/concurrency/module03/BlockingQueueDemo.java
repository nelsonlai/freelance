package concurrency.module03;

import java.util.concurrent.*;

/**
 * Producer-consumer pattern using {@link java.util.concurrent.BlockingQueue}.
 *
 * <p><b>BlockingQueue:</b> put(item) blocks when the queue is full (bounded);
 * take() blocks when the queue is empty. This provides natural backpressure:
 * a fast producer is slowed down when the consumer can't keep up (queue full).
 *
 * <p>Here we use {@link java.util.concurrent.ArrayBlockingQueue} with capacity 10.
 * One thread produces 20 integers (put); the other consumes 20 (take). When the
 * queue is full, put blocks until the consumer takes an item; when empty, take
 * blocks until the producer puts one.
 */
public class BlockingQueueDemo {

    /**
     * Starts one producer and one consumer sharing a bounded queue of capacity 10.
     * Producer puts 0..19; consumer takes 20 items. put/take handle blocking and
     * interrupt response.
     *
     * @param args unused
     * @throws InterruptedException if interrupted during join
     */
    public static void main(String[] args) throws InterruptedException {
        BlockingQueue<Integer> queue = new ArrayBlockingQueue<>(10);

        Thread producer = new Thread(() -> {
            try {
                for (int i = 0; i < 20; i++) {
                    queue.put(i);  // Blocks if queue is full
                    System.out.println("Produced " + i);
                }
            } catch (InterruptedException e) { Thread.currentThread().interrupt(); }
        });

        Thread consumer = new Thread(() -> {
            try {
                for (int i = 0; i < 20; i++) {
                    int v = queue.take();  // Blocks if queue is empty
                    System.out.println("Consumed " + v);
                }
            } catch (InterruptedException e) { Thread.currentThread().interrupt(); }
        });

        consumer.start();
        producer.start();
        producer.join();
        consumer.join();
    }
}
