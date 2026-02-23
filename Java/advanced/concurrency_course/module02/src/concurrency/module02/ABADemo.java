package concurrency.module02;

import java.util.concurrent.atomic.AtomicReference;
import java.util.concurrent.atomic.AtomicStampedReference;

/**
 * Demonstrates the <b>ABA problem</b> in lock-free algorithms using compare-and-swap (CAS).
 *
 * <p><b>ABA:</b> The value goes A → B → A. A thread that read "A" and later does CAS(expected=A, new=C)
 * will succeed (because the reference is "A" again), even though the state <i>did</i> change in between.
 * In some algorithms (e.g. lock-free queues), this can break invariants.
 *
 * <p><b>Fix:</b> Use a version or stamp so we detect that "A" was modified. {@link AtomicStampedReference}
 * pairs a reference with an integer stamp; CAS must match both. When T2 does A→B→A, the stamp changes,
 * so T1's CAS(expectedRef=A, expectedStamp=0) fails.
 */
public class ABADemo {

    /** Simple box with an id; used as the reference type so we can have distinct A/B/C instances. */
    static class Box {
        final String id;
        Box(String id) { this.id = id; }
    }

    /**
     * Part 1: ABA with AtomicReference. T1 reads A, sleeps; T2 does A→B→A (same reference for A).
     * T1's CAS(a, C) then succeeds because ref is "A" again — but the history was A→B→A.
     * Part 2: Same scenario with AtomicStampedReference; T1's CAS fails because stamp changed.
     *
     * @param args unused
     * @throws InterruptedException if interrupted during join
     */
    public static void main(String[] args) throws InterruptedException {
        // ---------- Part 1: ABA with plain AtomicReference ----------
        AtomicReference<Box> ref = new AtomicReference<>(new Box("A"));

        Thread t1 = new Thread(() -> {
            Box a = ref.get();
            try { Thread.sleep(50); } catch (InterruptedException e) { Thread.currentThread().interrupt(); }
            // We still hold the original "A" reference; meanwhile T2 may have done A→B→A.
            // CAS succeeds because current ref equals our expected "a" (both are A).
            boolean ok = ref.compareAndSet(a, new Box("C"));
            System.out.println("Thread 1 CAS(a->C): " + ok);
        });

        Thread t2 = new Thread(() -> {
            Box a = ref.get();
            ref.compareAndSet(a, new Box("B"));
            ref.compareAndSet(ref.get(), a);  // B -> A (restore same reference as original A)
        });

        t1.start();
        t2.start();
        t1.join();
        t2.join();
        System.out.println("Ref after ABA: " + ref.get().id);

        // ---------- Part 2: Fix with AtomicStampedReference ----------
        AtomicStampedReference<Box> stamped = new AtomicStampedReference<>(new Box("A"), 0);

        Thread t3 = new Thread(() -> {
            Box a = stamped.getReference();
            int stamp = stamped.getStamp();
            try { Thread.sleep(50); } catch (InterruptedException e) { Thread.currentThread().interrupt(); }
            // CAS must match both reference and stamp. After T4 does A→B→A, stamp is 2, not 0.
            boolean ok = stamped.compareAndSet(a, new Box("C"), stamp, stamp + 1);
            System.out.println("Thread 3 CAS(a->C) with stamp: " + ok);
        });

        Thread t4 = new Thread(() -> {
            Box a = stamped.getReference();
            int s = stamped.getStamp();
            stamped.compareAndSet(a, new Box("B"), s, s + 1);
            Box b = stamped.getReference();
            int s2 = stamped.getStamp();
            stamped.compareAndSet(b, a, s2, s2 + 1);  // B -> A; stamp is now s2+1, so different from original
        });

        t3.start();
        t4.start();
        t3.join();
        t4.join();
        System.out.println("Stamped ref after ABA: " + stamped.getReference().id + ", stamp=" + stamped.getStamp());
    }
}
