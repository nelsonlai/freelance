package concurrency.module02;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.atomic.AtomicLong;

/**
 * High-concurrency account balance: three implementations —
 * synchronized, ReentrantLock, and lock-free (AtomicLong).
 * Simple benchmark: many threads credit/debit repeatedly.
 */
public class AccountBalance {

    interface Account {
        void credit(long amount);
        void debit(long amount);
        long getBalance();
    }

    static class SynchronizedAccount implements Account {
        private long balance = 0;
        @Override
        public synchronized void credit(long amount) { balance += amount; }
        @Override
        public synchronized void debit(long amount)  { balance -= amount; }
        @Override
        public synchronized long getBalance()       { return balance; }
    }

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

    static class LockFreeAccount implements Account {
        private final AtomicLong balance = new AtomicLong(0);
        @Override
        public void credit(long amount) { balance.addAndGet(amount); }
        @Override
        public void debit(long amount)  { balance.addAndGet(-amount); }
        @Override
        public long getBalance()        { return balance.get(); }
    }

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
