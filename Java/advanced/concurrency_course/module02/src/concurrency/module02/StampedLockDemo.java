package concurrency.module02;

import java.util.concurrent.locks.StampedLock;

/**
 * StampedLock: optimistic read — no lock held during read; validate at the end.
 * If validation fails, retry with full read lock.
 */
public class StampedLockDemo {

    private final StampedLock sl = new StampedLock();
    private double x;
    private double y;

    public void move(double dx, double dy) {
        long stamp = sl.writeLock();
        try {
            x += dx;
            y += dy;
        } finally {
            sl.unlockWrite(stamp);
        }
    }

    /** Optimistic read: no lock held; must validate. */
    public double distanceFromOrigin() {
        long stamp = sl.tryOptimisticRead();
        double cx = x;
        double cy = y;
        if (!sl.validate(stamp)) {
            stamp = sl.readLock();
            try {
                cx = x;
                cy = y;
            } finally {
                sl.unlockRead(stamp);
            }
        }
        return Math.sqrt(cx * cx + cy * cy);
    }

    public static void main(String[] args) throws InterruptedException {
        StampedLockDemo demo = new StampedLockDemo();
        demo.move(3, 4);
        System.out.println("Distance: " + demo.distanceFromOrigin() + " (expected 5.0)");

        Thread writer = new Thread(() -> { for (int i = 0; i < 1000; i++) demo.move(0.01, 0.01); });
        Thread reader = new Thread(() -> { for (int i = 0; i < 1000; i++) demo.distanceFromOrigin(); });
        writer.start();
        reader.start();
        writer.join();
        reader.join();
        System.out.println("After concurrent moves/reads, distance: " + demo.distanceFromOrigin());
    }
}
