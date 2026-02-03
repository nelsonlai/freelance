package concurrency.module01;

/**
 * "Logically correct" code that can still fail under the JMM:
 * - Double-checked locking without volatile (famous DCL bug).
 * - Or a shared "initialized" flag used without proper synchronization,
 *   so one thread sees the flag true but not the associated writes.
 *
 * This class demonstrates a simplified "lazy init" where the reader
 * can see the object reference as non-null but still see uninitialized
 * fields (half-constructed object) due to reordering.
 */
public class LogicalCorrectnessFailure {

    // Simulates a lazy-initialized object: writer sets ref and then initializes fields.
    private static Holder ref = null;
    private static boolean initialized = false;

    static class Holder {
        int value;
    }

    public static void main(String[] args) throws InterruptedException {
        int reorders = 0;
        int trials = 500_000;

        for (int t = 0; t < trials; t++) {
            ref = null;
            initialized = false;

            Thread writer = new Thread(() -> {
                Holder h = new Holder();
                h.value = 42;
                ref = h;           // Another thread might see ref != null
                initialized = true; // before h.value is visible (reordering).
            });

            Thread reader = new Thread(() -> {
                while (!initialized) { /* spin */ }
                Holder r = ref;
                if (r != null && r.value != 42) {
                    // Saw ref and initialized but not the write to value
                    System.out.println("Half-constructed object observed: value=" + r.value);
                }
            });

            reader.start();
            writer.start();
            reader.join();
            writer.join();

            if (ref != null && ref.value != 42) reorders++;
        }

        System.out.println("Trials: " + trials + ", half-constructed observations: " + reorders);
    }
}
