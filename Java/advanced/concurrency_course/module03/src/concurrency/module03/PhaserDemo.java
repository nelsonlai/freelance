package concurrency.module03;

import java.util.concurrent.Phaser;

/**
 * Phaser: multi-phase barrier. Parties register; arriveAndAwaitAdvance() at each phase.
 * Good for multi-stage pipelines where every party must finish phase N before phase N+1.
 */
public class PhaserDemo {

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
