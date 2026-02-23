package concurrency.module05;

import java.util.concurrent.*;
import java.util.function.Consumer;

/**
 * Minimal in-process "actor": a mailbox ({@link BlockingQueue}) and a single
 * thread that processes messages one at a time. No shared mutable state with
 * other actors — communication is only via sending messages; all state is
 * local to the actor and updated sequentially in the handler.
 *
 * <p>Contrast with thread-per-request: one thread serves all messages, so you
 * avoid thread explosion and need no locks for the actor's state.
 */
public class SimpleActor {

    /** Marker for messages; in a real actor you'd have multiple message types. */
    public interface Message {}

    private final BlockingQueue<Message> mailbox = new LinkedBlockingQueue<>();
    private final Thread worker;
    private volatile boolean running = true;

    /**
     * Creates the actor and starts its worker thread. The handler is invoked
     * for each message in order; it should not block for long (or use a
     * separate pool for heavy work and send results back as messages).
     *
     * @param handler called for each message on the actor's thread
     */
    public SimpleActor(Consumer<Message> handler) {
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

    /** Sends a message to the actor. Non-blocking; the message is queued. */
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
