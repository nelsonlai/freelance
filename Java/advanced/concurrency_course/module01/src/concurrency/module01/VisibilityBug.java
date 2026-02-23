package concurrency.module01;

/**
 * Demonstrates a classic visibility bug when shared variables are accessed by
 * multiple threads without a happens-before relationship.
 *
 * <p><b>Visibility:</b> Without volatile or synchronization, the JVM does not
 * guarantee that a write by one thread is ever visible to another. The reader
 * may keep a stale value of {@code ready} in a register or cache and never
 * exit the loop, or it may see {@code ready == true} but still see {@code value == 0}.
 *
 * <p><b>Possible outcomes:</b>
 * <ul>
 *   <li>Reader never sees {@code ready == true} → infinite loop (join times out).</li>
 *   <li>Reader sees {@code ready == true} but {@code value} still 0 → prints "value = 0".</li>
 *   <li>Everything visible correctly → prints "value = 42" (correct but not guaranteed).</li>
 * </ul>
 *
 * <p>Behavior can vary with JVM, CPU, and -Xint. That's the point: without
 * synchronization, behavior is undefined per the JMM.
 *
 * @see VolatileFix for the corrected version using volatile
 */
public class VisibilityBug {

    /**
     * Signal from writer to reader. Not volatile — no happens-before between
     * writer and reader; reader may never see the update (infinite loop) or
     * see it in an order that makes value still 0.
     */
    private static boolean ready = false;

    /**
     * Value written by writer, read by reader. Not volatile — may be reordered
     * with ready or never flushed to main memory from writer's view.
     */
    private static int value = 0;

    /**
     * Starts writer and reader. Writer sets value then ready; reader spins on
     * ready then prints value. We join with a timeout; if reader is still alive,
     * we report the visibility bug (reader never saw ready=true).
     *
     * @param args unused
     * @throws InterruptedException if interrupted during join
     */
    public static void main(String[] args) throws InterruptedException {
        Thread writer = new Thread(() -> {
            value = 42;       // May be reordered with ready = true
            ready = true;     // Reader may see true before seeing value = 42
        }, "writer");

        Thread reader = new Thread(() -> {
            while (!ready) {
                // Busy spin. The JVM may "hoist" the read of ready out of the loop
                // (only read once), effectively making this an infinite loop if the
                // initial read saw false.
            }
            System.out.println("value = " + value);  // Might print 0 if reordered
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
