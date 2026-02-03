package concurrency.module03;

import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicLong;

/**
 * Transaction throttling: cap concurrent transactions with a Semaphore.
 * Tracks accepted vs rejected and total completed for simple metrics.
 */
public class TransactionThrottling {

    private final Semaphore permit;
    private final AtomicLong accepted = new AtomicLong(0);
    private final AtomicLong rejected = new AtomicLong(0);
    private final AtomicLong completed = new AtomicLong(0);

    public TransactionThrottling(int maxConcurrent) {
        this.permit = new Semaphore(maxConcurrent);
    }

    public boolean submitTransaction(Runnable transaction) {
        if (!permit.tryAcquire()) {
            rejected.incrementAndGet();
            return false;
        }
        accepted.incrementAndGet();
        try {
            transaction.run();
            return true;
        } finally {
            completed.incrementAndGet();
            permit.release();
        }
    }

    public void submitTransactionBlocking(Runnable transaction) throws InterruptedException {
        permit.acquire();
        try {
            transaction.run();
        } finally {
            completed.incrementAndGet();
            permit.release();
        }
    }

    public long getAccepted() { return accepted.get(); }
    public long getRejected() { return rejected.get(); }
    public long getCompleted() { return completed.get(); }

    public static void main(String[] args) throws InterruptedException {
        TransactionThrottling throttle = new TransactionThrottling(2);
        ExecutorService exec = Executors.newFixedThreadPool(10);

        for (int i = 0; i < 20; i++) {
            int id = i;
            exec.execute(() -> {
                boolean ok = throttle.submitTransaction(() -> {
                    try { Thread.sleep(100); } catch (InterruptedException e) { Thread.currentThread().interrupt(); }
                });
                if (!ok) System.out.println("Transaction " + id + " rejected");
            });
        }

        exec.shutdown();
        exec.awaitTermination(10, TimeUnit.SECONDS);
        System.out.println("Accepted: " + throttle.getAccepted() + ", Rejected: " + throttle.getRejected() + ", Completed: " + throttle.getCompleted());
    }
}
