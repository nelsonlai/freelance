package concurrency.module02;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * Compares synchronized and ReentrantLock for the same critical section.
 * Also demonstrates tryLock (non-blocking / timeout) which synchronized cannot do.
 */
public class SynchronizedVsReentrantLock {

    private int counterSync = 0;
    private int counterLock = 0;
    private final Object monitor = new Object();
    private final Lock lock = new ReentrantLock();

    public void incrementSync() {
        synchronized (monitor) {
            counterSync++;
        }
    }

    public int getCounterSync() {
        synchronized (monitor) {
            return counterSync;
        }
    }

    public void incrementLock() {
        lock.lock();
        try {
            counterLock++;
        } finally {
            lock.unlock();
        }
    }

    public int getCounterLock() {
        lock.lock();
        try {
            return counterLock;
        } finally {
            lock.unlock();
        }
    }

    /** Returns true if lock was acquired and increment performed. */
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

        Thread s1 = new Thread(() -> { for (int i = 0; i < n; i++) demo.incrementSync(); });
        Thread s2 = new Thread(() -> { for (int i = 0; i < n; i++) demo.incrementSync(); });
        s1.start();
        s2.start();
        s1.join();
        s2.join();
        System.out.println("synchronized counter: " + demo.getCounterSync() + " (expected " + (2 * n) + ")");

        Thread l1 = new Thread(() -> { for (int i = 0; i < n; i++) demo.incrementLock(); });
        Thread l2 = new Thread(() -> { for (int i = 0; i < n; i++) demo.incrementLock(); });
        l1.start();
        l2.start();
        l1.join();
        l2.join();
        System.out.println("ReentrantLock counter: " + demo.getCounterLock() + " (expected " + (2 * n) + ")");

        // tryLock: one thread spins until it gets the lock
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
