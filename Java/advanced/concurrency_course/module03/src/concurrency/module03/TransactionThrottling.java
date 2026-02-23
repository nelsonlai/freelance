package concurrency.module03;

import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicLong;

/**
 * Transaction throttling: limit the number of concurrent "transactions" using
 * a {@link java.util.concurrent.Semaphore}. When the limit is reached, new
 * submissions can be rejected (tryAcquire) or block (acquire).
 *
 * <p>Tracks metrics: how many were accepted (permit acquired), rejected (tryAcquire
 * failed), and completed (permit released after run). Useful for exchange-style
 * systems that must cap concurrent orders or requests.
 */
public class TransactionThrottling {

    private final Semaphore permit;
    private final AtomicLong accepted = new AtomicLong(0);
    private final AtomicLong rejected = new AtomicLong(0);
    private final AtomicLong completed = new AtomicLong(0);

    /**
     * Creates a throttler that allows at most maxConcurrent transactions at once.
     *
     * @param maxConcurrent maximum number of concurrent transactions
     */
    public TransactionThrottling(int maxConcurrent) {
        this.permit = new Semaphore(maxConcurrent);
    }

    /**
     * Tries to run the transaction if a permit is available. If not, increments
     * rejected count and returns false. If yes, increments accepted, runs the
     * transaction, then in finally increments completed and releases the permit.
     *
     * @param transaction the runnable representing the transaction
     * @return true if the transaction was run, false if rejected (no permit)
     */
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

    /**
     * Acquires a permit (blocking), runs the transaction, then releases the permit
     * and increments completed. Use when you want to wait rather than reject.
     *
     * @param transaction the runnable representing the transaction
     * @throws InterruptedException if interrupted while waiting for a permit
     */
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

    /**
     * Submits 20 "transactions" (each just sleeps 100ms) to a pool of 10 threads,
     * with a throttle of 2 concurrent. Some will be rejected. Prints accepted,
     * rejected, and completed counts.
     */
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
