package concurrency.module01;

/**
 * Same communication pattern as {@link VisibilityBug}, but {@code ready} is
 * declared volatile. This establishes a happens-before relationship so the
 * reader always sees the correct value.
 *
 * <p><b>Why volatile fixes visibility:</b> A write to a volatile variable
 * happens-before every subsequent read of that variable by any thread. In
 * program order, the writer does {@code value = 42;} before {@code ready = true}.
 * So the write to value happens-before the write to ready, and the read of
 * ready happens-after that write; therefore the read of value (after seeing
 * ready true) sees 42.
 *
 * <p><b>Volatile does NOT make compound operations atomic:</b> The second part
 * of this demo uses a volatile counter with {@code count++}. Each {@code count++}
 * is a read-modify-write (read, add 1, write). Two threads can interleave so
 * updates are lost. Use {@link java.util.concurrent.atomic.AtomicInteger} for
 * atomic increment.
 */
public class VolatileFix {

    /** Volatile ensures: write to ready is visible to reader; and program order gives value visible before ready. */
    private static volatile boolean ready = false;

    /** Written before ready in writer; read after ready in reader. Volatile on ready is enough for visibility. */
    private static int value = 0;

    /**
     * Volatile only guarantees visibility of each single read/write. The operation
     * volatileCounter++ is read-modify-write (not atomic), so two threads can
     * both read the same value, increment, and write back — losing one update.
     */
    private static volatile int volatileCounter = 0;

    /**
     * (1) Demonstrates visibility fix with volatile ready; (2) demonstrates that
     * volatile does not make count++ atomic — final count will be less than 2*iterations.
     *
     * @param args unused
     * @throws InterruptedException if any thread is interrupted during join()
     */
    public static void main(String[] args) throws InterruptedException {
        // --- Part 1: Visibility fix ---
        Thread writer = new Thread(() -> {
            value = 42;
            ready = true;  // Volatile write: all prior writes (value=42) are visible after this
        }, "writer");
        Thread reader = new Thread(() -> {
            while (!ready) { /* spin until volatile read sees true */ }
            System.out.println("value = " + value);  // Should always be 42
        }, "reader");

        reader.start();
        writer.start();
        reader.join();
        writer.join();

        // --- Part 2: Volatile does NOT make count++ atomic ---
        int iterations = 100_000;
        Thread a = new Thread(() -> {
            for (int i = 0; i < iterations; i++) volatileCounter++;  // read-modify-write
        });
        Thread b = new Thread(() -> {
            for (int i = 0; i < iterations; i++) volatileCounter++;
        });
        a.start();
        b.start();
        a.join();
        b.join();
        System.out.println("volatileCounter (expected " + (2 * iterations) + ") = " + volatileCounter);
    }
}
