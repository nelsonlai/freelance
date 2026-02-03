package concurrency.module02;

import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

/**
 * ReadWriteLock: multiple readers or single writer. Good when reads dominate.
 * This demo uses a shared value; many threads read, one occasionally writes.
 */
public class ReadWriteLockDemo {

    private final ReadWriteLock rwl = new ReentrantReadWriteLock();
    private volatile long value = 0;

    public long read() {
        rwl.readLock().lock();
        try {
            return value;
        } finally {
            rwl.readLock().unlock();
        }
    }

    public void write(long v) {
        rwl.writeLock().lock();
        try {
            value = v;
        } finally {
            rwl.writeLock().unlock();
        }
    }

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
