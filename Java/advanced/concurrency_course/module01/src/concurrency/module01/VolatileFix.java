package concurrency.module01;

/**
 * Same pattern as VisibilityBug, but 'ready' is volatile. This establishes
 * happens-before: the write to ready is visible to the read of ready, and
 * the write to value happens-before the write to ready in program order,
 * so the read of value after seeing ready=true should see 42.
 *
 * Shows that volatile fixes visibility but NOT compound operations: see
 * volatileCounter — two threads doing count++ still lose updates.
 */
public class VolatileFix {

    private static volatile boolean ready = false;
    private static int value = 0;

    // Volatile ensures visibility of each read/write, but count++ is read-modify-write.
    private static volatile int volatileCounter = 0;

    public static void main(String[] args) throws InterruptedException {
        // --- Visibility fix ---
        Thread writer = new Thread(() -> {
            value = 42;
            ready = true;
        }, "writer");
        Thread reader = new Thread(() -> {
            while (!ready) { /* spin */ }
            System.out.println("value = " + value);  // Should always be 42
        }, "reader");

        reader.start();
        writer.start();
        reader.join();
        writer.join();

        // --- Volatile does NOT make count++ atomic ---
        int iterations = 100_000;
        Thread a = new Thread(() -> {
            for (int i = 0; i < iterations; i++) volatileCounter++;
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
