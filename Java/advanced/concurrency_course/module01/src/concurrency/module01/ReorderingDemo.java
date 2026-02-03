package concurrency.module01;

/**
 * Illustrates instruction reordering: from another thread's perspective,
 * "ready = true" can become visible before "data = 1" if there is no
 * happens-before between them. We run many trials to increase chance
 * of observing the reordering (data still 0 when ready is seen true).
 */
public class ReorderingDemo {

    private int data = 0;
    private boolean ready = false;

    public void writer() {
        data = 1;
        ready = true;
    }

    public void reader() {
        if (ready) {
            int r = data;  // Might be 0 due to reordering
            if (r == 0) {
                System.out.println("Reordering observed: ready=true but data=0");
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        int trials = 100_000;
        int reorders = 0;

        for (int t = 0; t < trials; t++) {
            ReorderingDemo demo = new ReorderingDemo();

            Thread w = new Thread(demo::writer);
            Thread r = new Thread(() -> {
                demo.reader();
            });

            r.start();
            w.start();
            r.join();
            w.join();

            // Check after the fact (reader might have seen ready=true and data=0)
            if (demo.ready && demo.data == 0) {
                reorders++;
            }
        }

        System.out.println("Trials: " + trials + ", reordering observed (ready && data==0): " + reorders);
    }
}
