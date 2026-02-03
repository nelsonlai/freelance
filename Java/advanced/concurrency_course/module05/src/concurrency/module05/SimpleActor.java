package concurrency.module05;

import java.util.concurrent.*;

/**
 * Minimal in-process "actor": has a mailbox (BlockingQueue) and a single thread
 * that processes messages sequentially. No shared mutable state with other actors.
 */
public class SimpleActor {

    public interface Message {}

    private final BlockingQueue<Message> mailbox = new LinkedBlockingQueue<>();
    private final Thread worker;
    private volatile boolean running = true;

    public SimpleActor(java.util.function.Consumer<Message> handler) {
        worker = new Thread(() -> {
            while (running) {
                try {
                    Message msg = mailbox.poll(100, TimeUnit.MILLISECONDS);
                    if (msg != null) handler.accept(msg);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    break;
                }
            }
        });
        worker.start();
    }

    public void send(Message msg) {
        mailbox.offer(msg);
    }

    public void stop() {
        running = false;
        worker.interrupt();
    }

    public static void main(String[] args) throws InterruptedException {
        SimpleActor actor = new SimpleActor(msg -> System.out.println("Received: " + msg));
        actor.send(new Message() { @Override public String toString() { return "Hello"; } });
        actor.send(new Message() { @Override public String toString() { return "World"; } });
        Thread.sleep(500);
        actor.stop();
    }
}
