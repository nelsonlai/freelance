package concurrency.module01;

/**
 * Demonstrates a classic visibility bug: one thread updates a shared flag/counter,
 * another thread reads it without any happens-before relationship. The reading
 * thread may never see the update (stale read from cache/register) or see
 * partial reorderings.
 *
 * Run repeatedly; on many systems the reader may stall (infinite loop) or see
 * stale values. Adding -Xint (interpreted mode) or running on a different
 * core layout can change behavior — that's the point: without synchronization,
 * behavior is undefined from the JMM perspective.
 */
public class VisibilityBug {

    // No volatile — no happens-before between writer and reader.
    private static boolean ready = false;
    private static int value = 0;

    public static void main(String[] args) throws InterruptedException {
        Thread writer = new Thread(() -> {
            value = 42;       // May be reordered with ready = true
            ready = true;     // Reader may see true before seeing value = 42
        }, "writer");

        Thread reader = new Thread(() -> {
            while (!ready) {
                // Busy spin — may never see ready=true due to visibility
                // On some JVMs/CPUs this may be optimized to an infinite loop (hoisting read).
            }
            System.out.println("value = " + value);  // Might print 0
        }, "reader");

        reader.start();
        writer.start();

        reader.join(5000);
        writer.join(2000);

        if (reader.isAlive()) {
            System.out.println("Reader still running after 5s — visibility bug: never saw ready=true.");
        }
    }
}
