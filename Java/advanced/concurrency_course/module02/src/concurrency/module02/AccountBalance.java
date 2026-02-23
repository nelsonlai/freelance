package concurrency.module02;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.atomic.AtomicLong;

/**
 * Compares three ways to implement a high-concurrency account balance:
 * <ul>
 *   <li><b>Synchronized:</b> Every method synchronized on the instance; simple but no tryLock/timeout.</li>
 *   <li><b>ReentrantLock:</b> Explicit lock/unlock in try/finally; same semantics, allows tryLock and fairness.</li>
 *   <li><b>Lock-free (AtomicLong):</b> No locks; credit/debit via addAndGet. Often faster under contention.</li>
 * </ul>
 * Each thread does many credit(1) and debit(1) pairs; net balance should remain 0. We measure total time.
 */
public class AccountBalance {

    /** Common interface for an account supporting credit, debit, and balance read. */
    interface Account {
        void credit(long amount);
        void debit(long amount);
        long getBalance();
    }

    /**
     * Account guarded by synchronized methods. Each method acquires the monitor on this;
     * only one thread can execute any of these at a time.
     */
    static class SynchronizedAccount implements Account {
        private long balance = 0;
        @Override
        public synchronized void credit(long amount) { balance += amount; }
        @Override
        public synchronized void debit(long amount)  { balance -= amount; }
        @Override
        public synchronized long getBalance()       { return balance; }
    }

    /**
     * Account guarded by ReentrantLock. Same mutual exclusion as synchronized, but we
     * must unlock in finally to avoid leaving the lock held on exception or early return.
     */
    static class ReentrantLockAccount implements Account {
        private long balance = 0;
        private final Lock lock = new ReentrantLock();
        @Override
        public void credit(long amount) {
            lock.lock();
            try { balance += amount; } finally { lock.unlock(); }
        }
        @Override
        public void debit(long amount) {
            lock.lock();
            try { balance -= amount; } finally { lock.unlock(); }
        }
        @Override
        public long getBalance() {
            lock.lock();
            try { return balance; } finally { lock.unlock(); }
        }
    }

    /**
     * Lock-free account using AtomicLong. addAndGet is a single atomic read-modify-write;
     * no blocking, so under high contention this often outperforms lock-based approaches.
     */
    static class LockFreeAccount implements Account {
        private final AtomicLong balance = new AtomicLong(0);
        @Override
        public void credit(long amount) { balance.addAndGet(amount); }
        @Override
        public void debit(long amount)  { balance.addAndGet(-amount); }
        @Override
        public long getBalance()        { return balance.get(); }
    }

    /**
     * Runs a simple benchmark: {@code threads} threads each performing {@code opsPerThread}
     * credit(1) and debit(1) pairs. Prints final balance (should be 0), elapsed ms, and total ops.
     */
    static void runBenchmark(Account acc, int threads, int opsPerThread) throws InterruptedException {
        Thread[] ts = new Thread[threads];
        long start = System.nanoTime();
        for (int i = 0; i < threads; i++) {
            ts[i] = new Thread(() -> {
                for (int j = 0; j < opsPerThread; j++) {
                    acc.credit(1);
                    acc.debit(1);
                }
            });
            ts[i].start();
        }
        for (Thread t : ts) t.join();
        long elapsed = (System.nanoTime() - start) / 1_000_000;
        System.out.println(acc.getClass().getSimpleName() + ": balance=" + acc.getBalance() + ", " + elapsed + " ms, " + (threads * opsPerThread * 2) + " ops");
    }

    public static void main(String[] args) throws InterruptedException {
        int threads = 4;
        int opsPerThread = 500_000;

        runBenchmark(new SynchronizedAccount(), threads, opsPerThread);
        runBenchmark(new ReentrantLockAccount(), threads, opsPerThread);
        runBenchmark(new LockFreeAccount(), threads, opsPerThread);
    }
}
