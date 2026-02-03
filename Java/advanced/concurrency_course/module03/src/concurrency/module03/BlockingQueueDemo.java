package concurrency.module03;

import java.util.concurrent.*;

/**
 * Producer-consumer with ArrayBlockingQueue. Producers put items;
 * consumers take (block until available). Bounded queue provides backpressure.
 */
public class BlockingQueueDemo {

    public static void main(String[] args) throws InterruptedException {
        BlockingQueue<Integer> queue = new ArrayBlockingQueue<>(10);

        Thread producer = new Thread(() -> {
            try {
                for (int i = 0; i < 20; i++) {
                    queue.put(i);
                    System.out.println("Produced " + i);
                }
            } catch (InterruptedException e) { Thread.currentThread().interrupt(); }
        });

        Thread consumer = new Thread(() -> {
            try {
                for (int i = 0; i < 20; i++) {
                    int v = queue.take();
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
