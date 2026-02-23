package concurrency.module03;

import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;

/**
 * Demonstrates {@link java.util.concurrent.CountDownLatch}: a one-shot barrier
 * that starts at a count N; countDown() decrements it; await() blocks until the
 * count reaches 0.
 *
 * <p><b>Two common patterns:</b>
 * <ul>
 *   <li><b>Start gate:</b> Latch(1). Workers call await(); main (or a coordinator)
 *       calls countDown() when "ready" so all workers start together.</li>
 *   <li><b>Finish gate:</b> Latch(N). Each of N workers does its work then countDown();
 *       main await()s until all are done.</li>
 * </ul>
 * This demo uses both: workers wait on a start gate, then main waits on a done gate.
 */
public class CountDownLatchDemo {

    /**
     * Creates 3 worker threads that await a start gate (count=1), then each does
     * a short sleep and countDown on a done gate (count=3). Main releases the
     * start gate, then await()s the done gate (with timeout).
     *
     * @param args unused
     * @throws InterruptedException if interrupted during await or join
     */
    public static void main(String[] args) throws InterruptedException {
        int workers = 3;
        CountDownLatch startGate = new CountDownLatch(1);
        CountDownLatch doneGate = new CountDownLatch(workers);

        for (int i = 0; i < workers; i++) {
            int id = i;
            new Thread(() -> {
                try {
                    startGate.await();  // Wait until main releases the start gate
                    System.out.println("Worker " + id + " started");
                    Thread.sleep(100);
                } catch (InterruptedException e) 
                    { Thread.currentThread().interrupt(); 

                } 
                finally {
                    doneGate.countDown();  // Signal this worker is done
                }
            }).start();
        }

        System.out.println("Main: releasing start gate");
        startGate.countDown();
        doneGate.await(5, TimeUnit.SECONDS);
        System.out.println("Main: all workers done");
    }
}
