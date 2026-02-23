package concurrency.module03;

import java.util.concurrent.Phaser;

/**
 * Demonstrates {@link java.util.concurrent.Phaser}: a reusable barrier for
 * multi-phase coordination. Parties register with the phaser; at each phase
 * they call arriveAndAwaitAdvance() and block until all registered parties
 * have arrived, then the phase number advances.
 *
 * <p>Use case: multi-stage pipelines (e.g. batch processing) where every worker
 * must finish phase N before any proceed to phase N+1. Unlike CountDownLatch,
 * Phaser supports dynamic registration and multiple phases.
 *
 * <p>Here we use a "main" party (register 1) so that we can deregister it and
 * allow the worker threads to run; each worker goes through 3 phases then deregisters.
 */
public class PhaserDemo {

    /**
     * Registers 3 worker threads with a Phaser(1) (one party = main). Each worker
     * runs phase 0, arriveAndAwaitAdvance(), phase 1, arriveAndAwaitAdvance(),
     * phase 2, then arriveAndDeregister(). Main deregisters so the registered
     * count matches the 3 workers.
     *
     * @param args unused
     */
    public static void main(String[] args) {
        int parties = 3;
        Phaser phaser = new Phaser(1);

        for (int i = 0; i < parties; i++) {
            int id = i;
            phaser.register();
            new Thread(() -> {
                System.out.println("Phase 0: worker " + id);
                phaser.arriveAndAwaitAdvance();
                System.out.println("Phase 1: worker " + id);
                phaser.arriveAndAwaitAdvance();
                System.out.println("Phase 2: worker " + id + " done");
                phaser.arriveAndDeregister();
            }).start();
        }

        phaser.arriveAndDeregister();
    }
}
