package concurrency.module02;

import java.util.concurrent.locks.StampedLock;

/**
 * Demonstrates {@link java.util.concurrent.locks.StampedLock} and <b>optimistic reading</b>.
 *
 * <p>StampedLock has three modes: write lock (exclusive), read lock (shared), and
 * optimistic read. With optimistic read we do <i>not</i> hold a lock while reading;
 * we get a stamp, read the fields, then call {@code validate(stamp)}. If no write
 * occurred in between, the read was consistent. If validate fails, we retry with a
 * full read lock. This can improve throughput when writes are rare.
 *
 * <p>Coordinates (x, y) are updated under write lock; distance is computed with
 * optimistic read and fallback to read lock if needed.
 */
public class StampedLockDemo {

    private final StampedLock sl = new StampedLock();
    private double x;
    private double y;

    /**
     * Updates x and y under the write lock. Must pair with unlockWrite(stamp).
     */
    public void move(double dx, double dy) {
        long stamp = sl.writeLock();
        try {
            x += dx;
            y += dy;
        } finally {
            sl.unlockWrite(stamp);
        }
    }

    /**
     * Optimistic read: acquire a stamp (no lock held), read x and y, then validate.
     * If validate returns true, no write occurred — use the read values. If false,
     * retry with a full read lock to get a consistent snapshot.
     *
     * @return distance from origin sqrt(x^2 + y^2)
     */
    public double distanceFromOrigin() {
        long stamp = sl.tryOptimisticRead();
        double cx = x;
        double cy = y;
        if (!sl.validate(stamp)) {
            // A write happened after we took the stamp; re-read under read lock
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
