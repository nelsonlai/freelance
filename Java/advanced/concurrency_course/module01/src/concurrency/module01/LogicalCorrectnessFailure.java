package concurrency.module01;

/**
 * Demonstrates how "logically correct" code can still fail under the Java Memory Model (JMM).
 *
 * <p><b>Concepts illustrated:</b>
 * <ul>
 *   <li><b>Double-checked locking (DCL) bug:</b> Without volatile on the reference and/or
 *       the "initialized" flag, the JVM is allowed to reorder the writer's operations. The
 *       reader may see {@code initialized == true} and {@code ref != null} before the
 *       writes to the Holder's fields are visible — a "half-constructed" object.</li>
 *   <li><b>Happens-before:</b> There is no synchronization (no volatile, no lock) between
 *       the writer and reader, so the JMM does not guarantee that the write to {@code value}
 *       is visible when the reader sees {@code initialized == true}.</li>
 * </ul>
 *
 * <p><b>Fix in production:</b> Use volatile for both the reference and the flag, or use
 * a properly synchronized lazy holder (e.g. static inner class) or {@code AtomicReference}.
 *
 * @see VolatileFix for how volatile establishes happens-before and fixes visibility
 */
public class LogicalCorrectnessFailure {

    /**
     * Shared reference to a Holder. Not volatile — other threads may see this reference
     * published before the fields of the Holder are visible (reordering).
     */
    private static Holder ref = null;

    /**
     * Flag indicating initialization is complete. Not volatile — no happens-before
     * between writer and reader; reader may see true while still seeing stale ref/value.
     */
    private static boolean initialized = false;

    /**
     * Simple holder for a single int. Used to demonstrate that the reader can observe
     * the object reference (ref != null) but with default/uninitialized field value (0).
     */
    static class Holder {
        int value;
    }

    /**
     * Runs many trials: each trial has a writer thread that constructs a Holder and sets
     * ref + initialized, and a reader that spins until initialized then checks ref.value.
     * We count how often the reader (or post-join check) sees value != 42.
     *
     * @param args unused
     * @throws InterruptedException if any thread is interrupted during join()
     */
    public static void main(String[] args) throws InterruptedException {
        int reorders = 0;
        int trials = 500_000;

        for (int t = 0; t < trials; t++) {
            ref = null;
            initialized = false;

            Thread writer = new Thread(() -> {
                Holder h = new Holder();
                h.value = 42;
                // JMM allows reordering: another thread might see ref != null and
                // initialized == true before h.value = 42 is visible.
                ref = h;
                initialized = true;
            });

            Thread reader = new Thread(() -> {
                while (!initialized) { /* spin until writer signals */ }
                Holder r = ref;
                if (r != null && r.value != 42) {
                    // Observed half-constructed object: we saw ref and initialized
                    // but not the write to value (still 0).
                    System.out.println("Half-constructed object observed: value=" + r.value);
                }
            });

            reader.start();
            writer.start();
            reader.join();
            writer.join();

            // After both threads finish, check if we ever observed inconsistent state
            if (ref != null && ref.value != 42) reorders++;
        }

        System.out.println("Trials: " + trials + ", half-constructed observations: " + reorders);
    }
}
