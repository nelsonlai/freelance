package concurrency.module02;

import java.util.concurrent.atomic.AtomicReference;
import java.util.concurrent.atomic.AtomicStampedReference;

/**
 * ABA problem: value changes from A -> B -> A; a thread that only checks
 * "is it A?" can wrongly assume nothing changed. Fix: use version/stamp
 * (AtomicStampedReference).
 */
public class ABADemo {

    static class Box {
        final String id;
        Box(String id) { this.id = id; }
    }

    public static void main(String[] args) throws InterruptedException {
        AtomicReference<Box> ref = new AtomicReference<>(new Box("A"));

        Thread t1 = new Thread(() -> {
            Box a = ref.get();
            try { Thread.sleep(50); } catch (InterruptedException e) { Thread.currentThread().interrupt(); }
            // We still have reference to original "A"; meanwhile another thread may have changed A->B->A
            boolean ok = ref.compareAndSet(a, new Box("C"));
            System.out.println("Thread 1 CAS(a->C): " + ok);
        });

        Thread t2 = new Thread(() -> {
            Box a = ref.get();
            ref.compareAndSet(a, new Box("B"));
            ref.compareAndSet(ref.get(), a);  // B -> A (same reference as original A)
        });

        t1.start();
        t2.start();
        t1.join();
        t2.join();
        System.out.println("Ref after ABA: " + ref.get().id);  // Can be "C" even though "A" was replaced and restored

        // --- Fix with AtomicStampedReference ---
        AtomicStampedReference<Box> stamped = new AtomicStampedReference<>(new Box("A"), 0);
        int[] hold = new int[1];

        Thread t3 = new Thread(() -> {
            Box a = stamped.getReference();
            int stamp = stamped.getStamp();
            try { Thread.sleep(50); } catch (InterruptedException e) { Thread.currentThread().interrupt(); }
            boolean ok = stamped.compareAndSet(a, new Box("C"), stamp, stamp + 1);
            System.out.println("Thread 3 CAS(a->C) with stamp: " + ok);
        });

        Thread t4 = new Thread(() -> {
            Box a = stamped.getReference();
            int s = stamped.getStamp();
            stamped.compareAndSet(a, new Box("B"), s, s + 1);
            Box b = stamped.getReference();
            int s2 = stamped.getStamp();
            stamped.compareAndSet(b, a, s2, s2 + 1);  // B -> A, but stamp is now different
        });

        t3.start();
        t4.start();
        t3.join();
        t4.join();
        System.out.println("Stamped ref after ABA: " + stamped.getReference().id + ", stamp=" + stamped.getStamp());
    }
}
