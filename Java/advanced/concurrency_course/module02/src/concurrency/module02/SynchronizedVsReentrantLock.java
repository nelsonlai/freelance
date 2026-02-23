package concurrency.module02;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * Compares {@code synchronized} and {@link java.util.concurrent.locks.ReentrantLock}
 * for the same critical section (incrementing a counter).
 *
 * <p><b>ReentrantLock advantages:</b> tryLock (non-blocking or with timeout), fairness
 * option, multiple condition queues, and lock status queries. synchronized is simpler
 * and sufficient when you don't need those features.
 *
 * <p>Also demonstrates tryLock: one thread repeatedly tries to acquire the lock
 * without blocking; when it gets the lock it increments and returns true.
 */
public class SynchronizedVsReentrantLock {

    private int counterSync = 0;
    private int counterLock = 0;
    /** Monitor used for synchronized blocks; could use this instead of a separate object. */
    private final Object monitor = new Object();
    private final Lock lock = new ReentrantLock();

    /** Increment under the monitor lock; only one thread at a time. */
    public void incrementSync() {
        synchronized (monitor) {
            counterSync++;
        }
    }

    /** Read under the same monitor so we see a consistent value. */
    public int getCounterSync() {
        synchronized (monitor) {
            return counterSync;
        }
    }

    /** Increment under ReentrantLock. Unlock in finally so we never leave the lock held. */
    public void incrementLock() {
        lock.lock();
        try {
            counterLock++;
        } finally {
            lock.unlock();
        }
    }

    /** Read under the same lock for consistency. */
    public int getCounterLock() {
        lock.lock();
        try {
            return counterLock;
        } finally {
            lock.unlock();
        }
    }

    /**
     * Tries to acquire the lock without blocking. If acquired, increments and returns true;
     * otherwise returns false immediately. This is not possible with synchronized.
     *
     * @return true if the lock was acquired and increment was performed, false if lock was busy
     */
    public boolean tryIncrementLock() {
        if (lock.tryLock()) {
            try {
                counterLock++;
                return true;
            } finally {
                lock.unlock();
            }
        }
        return false;
    }

    public static void main(String[] args) throws InterruptedException {
        SynchronizedVsReentrantLock demo = new SynchronizedVsReentrantLock();
        int n = 500_000;

        // Benchmark synchronized: two threads each increment n times
        Thread s1 = new Thread(() -> { for (int i = 0; i < n; i++) demo.incrementSync(); });
        Thread s2 = new Thread(() -> { for (int i = 0; i < n; i++) demo.incrementSync(); });
        s1.start();
        s2.start();
        s1.join();
        s2.join();
        System.out.println("synchronized counter: " + demo.getCounterSync() + " (expected " + (2 * n) + ")");

        // Same with ReentrantLock
        Thread l1 = new Thread(() -> { for (int i = 0; i < n; i++) demo.incrementLock(); });
        Thread l2 = new Thread(() -> { for (int i = 0; i < n; i++) demo.incrementLock(); });
        l1.start();
        l2.start();
        l1.join();
        l2.join();
        System.out.println("ReentrantLock counter: " + demo.getCounterLock() + " (expected " + (2 * n) + ")");

        // tryLock: one thread keeps trying until it has performed n increments
        demo.counterLock = 0;
        Thread tryT = new Thread(() -> {
            int done = 0;
            while (done < n) {
                if (demo.tryIncrementLock()) done++;
            }
        });
        tryT.start();
        tryT.join();
        System.out.println("tryLock counter: " + demo.getCounterLock());
    }
}
