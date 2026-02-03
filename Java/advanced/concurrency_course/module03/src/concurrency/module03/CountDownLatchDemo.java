package concurrency.module03;

import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;

/**
 * CountDownLatch: one-shot barrier. countDown() decrements; await() blocks until 0.
 * - Start gate: one thread counts down when "ready"; workers await then proceed.
 * - Finish gate: N workers each countDown when done; main awaits then continues.
 */
public class CountDownLatchDemo {

    public static void main(String[] args) throws InterruptedException {
        int workers = 3;
        CountDownLatch startGate = new CountDownLatch(1);
        CountDownLatch doneGate = new CountDownLatch(workers);

        for (int i = 0; i < workers; i++) {
            int id = i;
            new Thread(() -> {
                try {
                    startGate.await();
                    System.out.println("Worker " + id + " started");
                    Thread.sleep(100);
                } catch (InterruptedException e) { Thread.currentThread().interrupt(); } finally {
                    doneGate.countDown();
                }
            }).start();
        }

        System.out.println("Main: releasing start gate");
        startGate.countDown();
        doneGate.await(5, TimeUnit.SECONDS);
        System.out.println("Main: all workers done");
    }
}
