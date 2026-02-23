package concurrency.module02;

import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

/**
 * Demonstrates {@link java.util.concurrent.locks.ReadWriteLock}: allows multiple
 * readers to hold the lock concurrently, or a single writer (exclusive).
 * Good when reads dominate and writes are infrequent — readers don't block each other.
 *
 * <p>This demo: one writer thread updates a long value occasionally; many reader
 * threads repeatedly read it. We measure total time for all operations.
 */
public class ReadWriteLockDemo {

    private final ReadWriteLock rwl = new ReentrantReadWriteLock();
    private volatile long value = 0;

    /**
     * Acquires the read lock so multiple threads can read concurrently.
     * Must unlock in finally so the lock is always released.
     */
    public long read() {
        rwl.readLock().lock();
        try {
            return value;
        } finally {
            rwl.readLock().unlock();
        }
    }

    /**
     * Acquires the write lock (exclusive); blocks until no readers or writers.
     * Updates the shared value then releases the lock.
     */
    public void write(long v) {
        rwl.writeLock().lock();
        try {
            value = v;
        } finally {
            rwl.writeLock().unlock();
        }
    }

    /**
     * Runs one writer (100 writes with small sleep) and many readers (each doing
     * many reads). Measures total elapsed time to show read-heavy workload with ReadWriteLock.
     *
     * @param args unused
     * @throws InterruptedException if interrupted during join
     */
    public static void main(String[] args) throws InterruptedException {
        ReadWriteLockDemo demo = new ReadWriteLockDemo();
        int readers = 10;
        int readIterations = 100_000;

        Thread writer = new Thread(() -> {
            for (int i = 0; i < 100; i++) {
                demo.write(i);
                try { Thread.sleep(1); } catch (InterruptedException e) { Thread.currentThread().interrupt(); }
            }
        });

        Thread[] readerThreads = new Thread[readers];
        for (int r = 0; r < readers; r++) {
            readerThreads[r] = new Thread(() -> {
                long sum = 0;
                for (int i = 0; i < readIterations; i++) {
                    sum += demo.read();
                }
            });
        }

        long start = System.nanoTime();
        writer.start();
        for (Thread t : readerThreads) t.start();
        writer.join();
        for (Thread t : readerThreads) t.join();
        long elapsed = (System.nanoTime() - start) / 1_000_000;
        System.out.println("ReadWriteLock: " + readers + " readers x " + readIterations + " reads + 1 writer, " + elapsed + " ms");
    }
}
