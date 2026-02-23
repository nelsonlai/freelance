package concurrency.module01;

/**
 * Illustrates that the JVM and CPU may reorder instructions when there is no
 * happens-before relationship between threads.
 *
 * <p><b>What is reordering?</b> The compiler and processor are allowed to reorder
 * independent operations for performance. In program order the writer does
 * {@code data = 1;} then {@code ready = true;}. From another thread's perspective,
 * {@code ready = true} can become visible <i>before</i> {@code data = 1} because
 * there is no volatile or lock to enforce ordering.
 *
 * <p><b>Result:</b> The reader may see {@code ready == true} but {@code data == 0}.
 * We run many trials to increase the chance of observing this on various JVMs/CPUs.
 *
 * <p><b>Fix:</b> Make {@code ready} volatile so the write to ready happens-before
 * the read of ready, and program order in the writer ensures data=1 is visible first.
 *
 * @see VolatileFix for the same pattern with volatile
 */
public class ReorderingDemo {

    /** Shared data written by writer, read by reader. Not volatile — no ordering guarantee. */
    private int data = 0;

    /** Signal from writer to reader. Not volatile — reader may see this before data is updated. */
    private boolean ready = false;

    /**
     * Writer thread: sets data then ready. The JMM allows these two writes to be
     * reordered or made visible to other threads in any order (no happens-before).
     */
    public void writer() {
        data = 1;
        ready = true;
    }

    /**
     * Reader thread: if it sees ready==true, it reads data. Due to reordering,
     * data may still be 0 (the read of ready may be "moved before" the write to data
     * in the writer, from the reader's perspective).
     */
    public void reader() {
        if (ready) {
            int r = data;  // Might be 0 due to reordering
            if (r == 0) {
                System.out.println("Reordering observed: ready=true but data=0");
            }
        }
    }

    /**
     * Runs many trials; each trial runs one writer and one reader. We count how
     * many times we observe ready==true and data==0 (either in reader or after join).
     *
     * @param args unused
     * @throws InterruptedException if any thread is interrupted during join()
     */
    public static void main(String[] args) throws InterruptedException {
        int trials = 100_000;
        int reorders = 0;

        for (int t = 0; t < trials; t++) {
            ReorderingDemo demo = new ReorderingDemo();

            Thread w = new Thread(demo::writer);
            Thread r = new Thread(demo::reader);

            r.start();
            w.start();
            r.join();
            w.join();

            // Post-join check: if reader saw ready but not data, we might still have
            // ready true and data 0 in main's view (depending on timing)
            if (demo.ready && demo.data == 0) {
                reorders++;
            }
        }

        System.out.println("Trials: " + trials + ", reordering observed (ready && data==0): " + reorders);
    }
}
