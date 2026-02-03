/**
 * ADVANCED LEVEL - Lesson 5: Concurrency
 * 
 * This lesson covers:
 * - Thread creation and management
 * - Synchronization
 * - Thread pools (ExecutorService)
 * - Future and CompletableFuture
 * - Concurrent collections
 * - Atomic classes
 */

import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.ReentrantLock;

// ========== THREAD CREATION ==========

class MyThread extends Thread {
    private String name;
    
    public MyThread(String name) {
        this.name = name;
    }
    
    @Override
    public void run() {
        for (int i = 0; i < 5; i++) {
            System.out.println(name + " - Count: " + i);
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                System.out.println(name + " interrupted");
                return;
            }
        }
    }
}

class MyRunnable implements Runnable {
    private String name;
    
    public MyRunnable(String name) {
        this.name = name;
    }
    
    @Override
    public void run() {
        for (int i = 0; i < 5; i++) {
            System.out.println(name + " - Count: " + i);
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                System.out.println(name + " interrupted");
                return;
            }
        }
    }
}

// ========== SYNCHRONIZATION ==========

class Counter {
    private int count = 0;
    
    // Synchronized method
    public synchronized void increment() {
        count++;
    }
    
    public synchronized int getCount() {
        return count;
    }
}

class SynchronizedCounter {
    private int count = 0;
    private final Object lock = new Object();
    
    public void increment() {
        synchronized (lock) {
            count++;
        }
    }
    
    public int getCount() {
        synchronized (lock) {
            return count;
        }
    }
}

class LockCounter {
    private int count = 0;
    private final ReentrantLock lock = new ReentrantLock();
    
    public void increment() {
        lock.lock();
        try {
            count++;
        } finally {
            lock.unlock();
        }
    }
    
    public int getCount() {
        lock.lock();
        try {
            return count;
        } finally {
            lock.unlock();
        }
    }
}

// ========== ATOMIC OPERATIONS ==========

class AtomicCounter {
    private AtomicInteger count = new AtomicInteger(0);
    
    public void increment() {
        count.incrementAndGet();
    }
    
    public int getCount() {
        return count.get();
    }
}

// ========== MAIN CLASS ==========

public class Concurrency {
    public static void main(String[] args) throws InterruptedException, ExecutionException {
        System.out.println("=== THREAD CREATION ===");
        
        // Method 1: Extending Thread
        MyThread thread1 = new MyThread("Thread-1");
        MyThread thread2 = new MyThread("Thread-2");
        
        thread1.start();
        thread2.start();
        
        thread1.join();  // Wait for thread to complete
        thread2.join();
        
        System.out.println("\n=== RUNNABLE INTERFACE ===");
        
        // Method 2: Implementing Runnable
        Thread runnableThread1 = new Thread(new MyRunnable("Runnable-1"));
        Thread runnableThread2 = new Thread(new MyRunnable("Runnable-2"));
        
        runnableThread1.start();
        runnableThread2.start();
        
        runnableThread1.join();
        runnableThread2.join();
        
        // Method 3: Lambda expression
        Thread lambdaThread = new Thread(() -> {
            for (int i = 0; i < 5; i++) {
                System.out.println("Lambda Thread - Count: " + i);
                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    return;
                }
            }
        });
        
        lambdaThread.start();
        lambdaThread.join();
        
        System.out.println("\n=== SYNCHRONIZATION ===");
        
        Counter counter = new Counter();
        Thread[] threads = new Thread[5];
        
        for (int i = 0; i < 5; i++) {
            threads[i] = new Thread(() -> {
                for (int j = 0; j < 1000; j++) {
                    counter.increment();
                }
            });
            threads[i].start();
        }
        
        for (Thread t : threads) {
            t.join();
        }
        
        System.out.println("Final count (synchronized): " + counter.getCount());
        
        System.out.println("\n=== THREAD POOLS ===");
        
        // ExecutorService
        ExecutorService executor = Executors.newFixedThreadPool(3);
        
        for (int i = 0; i < 5; i++) {
            final int taskId = i;
            executor.submit(() -> {
                System.out.println("Task " + taskId + " executed by " + Thread.currentThread().getName());
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            });
        }
        
        executor.shutdown();
        executor.awaitTermination(10, TimeUnit.SECONDS);
        
        System.out.println("\n=== FUTURE ===");
        
        ExecutorService executorService = Executors.newSingleThreadExecutor();
        
        Future<Integer> future = executorService.submit(() -> {
            Thread.sleep(2000);
            return 42;
        });
        
        System.out.println("Task submitted, doing other work...");
        
        try {
            Integer result = future.get(3, TimeUnit.SECONDS);
            System.out.println("Future result: " + result);
        } catch (TimeoutException e) {
            System.out.println("Task timed out");
        }
        
        executorService.shutdown();
        
        System.out.println("\n=== COMPLETABLEFUTURE ===");
        
        CompletableFuture<String> completableFuture = CompletableFuture.supplyAsync(() -> {
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
            return "Hello";
        });
        
        CompletableFuture<String> future2 = completableFuture.thenApply(s -> s + " World");
        
        future2.thenAccept(result -> System.out.println("CompletableFuture result: " + result));
        
        Thread.sleep(2000);
        
        System.out.println("\n=== ATOMIC CLASSES ===");
        
        AtomicCounter atomicCounter = new AtomicCounter();
        Thread[] atomicThreads = new Thread[5];
        
        for (int i = 0; i < 5; i++) {
            atomicThreads[i] = new Thread(() -> {
                for (int j = 0; j < 1000; j++) {
                    atomicCounter.increment();
                }
            });
            atomicThreads[i].start();
        }
        
        for (Thread t : atomicThreads) {
            t.join();
        }
        
        System.out.println("Final count (atomic): " + atomicCounter.getCount());
        
        System.out.println("\n=== CONCURRENT COLLECTIONS ===");
        
        // ConcurrentHashMap - Thread-safe HashMap
        ConcurrentHashMap<String, Integer> concurrentMap = new ConcurrentHashMap<>();
        concurrentMap.put("One", 1);
        concurrentMap.put("Two", 2);
        concurrentMap.put("Three", 3);
        System.out.println("ConcurrentHashMap: " + concurrentMap);
        
        // BlockingQueue
        BlockingQueue<String> queue = new LinkedBlockingQueue<>();
        queue.offer("Item1");
        queue.offer("Item2");
        queue.offer("Item3");
        System.out.println("BlockingQueue: " + queue);
        
        // CopyOnWriteArrayList - Thread-safe ArrayList
        CopyOnWriteArrayList<String> list = new CopyOnWriteArrayList<>();
        list.add("A");
        list.add("B");
        list.add("C");
        System.out.println("CopyOnWriteArrayList: " + list);
        
        System.out.println("\n=== THREAD STATES ===");
        Thread stateThread = new Thread(() -> {
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        });
        
        System.out.println("New: " + stateThread.getState());
        stateThread.start();
        System.out.println("Started: " + stateThread.getState());
        stateThread.join();
        System.out.println("Terminated: " + stateThread.getState());
    }
}

