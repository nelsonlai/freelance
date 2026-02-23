package concurrency.module02;

/**
 * Demonstrates <b>false sharing</b>: when two variables used by different threads
 * lie on the same CPU cache line (typically 64 bytes), writes by one thread
 * invalidate the line for the other, causing cache line "bounces" and slower execution.
 *
 * <p><b>Fix:</b> Pad the fields so {@code a} and {@code b} sit on different cache lines
 * (e.g. ~56 bytes of padding between them). Alternatively use {@code @Contended} (JDK 8+)
 * with -XX:-RestrictContended for non-JDK classes.
 *
 * <p>This is a simplified demo; results depend on layout and JVM. For serious
 * measurement use JMH and multiple runs.
 */
public class FalseSharingDemo {

    /**
     * Two volatile longs with no padding. On a 64-byte cache line, both a and b
     * often share the same line; two threads each updating one still cause invalidations.
     */
    static class Unpadded {
        volatile long a;
        volatile long b;
    }

    /**
     * Same two longs but with 7 long fields (7*8=56 bytes) between them so a and b
     * tend to fall on different cache lines. Reduces false sharing.
     */
    static class Padded {
        volatile long a;
        long p1, p2, p3, p4, p5, p6, p7;  // padding to push b to another cache line
        volatile long b;
    }

    /**
     * Runs two threads on Unpadded (each updating one counter), then the same on Padded.
     * Prints elapsed time for each; padded is often faster when false sharing matters.
     *
     * @param args unused
     * @throws InterruptedException if interrupted during join
     */
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
