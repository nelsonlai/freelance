package concurrency.module02;

/**
 * False sharing: two counters on the same cache line (e.g. 64 bytes) are
 * written by different threads -> cache line bounces. Padding (or @Contended)
 * puts them on different lines to reduce contention.
 *
 * This is a simplified demo structure; on real hardware you may need many
 * iterations and specific JVM flags to see the effect clearly. Use JMH for
 * serious measurement.
 */
public class FalseSharingDemo {

    // Unpadded: likely on same cache line
    static class Unpadded {
        volatile long a;
        volatile long b;
    }

    // Padded: put ~56 bytes between a and b so they tend to be on different cache lines
    static class Padded {
        volatile long a;
        long p1, p2, p3, p4, p5, p6, p7;  // 7 * 8 = 56 bytes
        volatile long b;
    }

    public static void main(String[] args) throws InterruptedException {
        Unpadded u = new Unpadded();
        Padded p = new Padded();

        int iterations = 10_000_000;

        long start = System.nanoTime();
        Thread ua = new Thread(() -> { for (int i = 0; i < iterations; i++) u.a++; });
        Thread ub = new Thread(() -> { for (int i = 0; i < iterations; i++) u.b++; });
        ua.start();
        ub.start();
        ua.join();
        ub.join();
        long unpaddedTime = (System.nanoTime() - start) / 1_000_000;

        start = System.nanoTime();
        Thread pa = new Thread(() -> { for (int i = 0; i < iterations; i++) p.a++; });
        Thread pb = new Thread(() -> { for (int i = 0; i < iterations; i++) p.b++; });
        pa.start();
        pb.start();
        pa.join();
        pb.join();
        long paddedTime = (System.nanoTime() - start) / 1_000_000;

        System.out.println("Unpadded (ms): " + unpaddedTime + ", Padded (ms): " + paddedTime);
        System.out.println("(Run multiple times; padding often wins when false sharing is significant.)");
    }
}
