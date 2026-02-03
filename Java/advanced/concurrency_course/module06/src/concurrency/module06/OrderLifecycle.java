package concurrency.module06;

import java.util.EnumSet;
import java.util.Set;

/**
 * Order lifecycle: states and allowed transitions. Single-threaded state machine
 * (transitions should be done by matching engine thread only).
 */
public class OrderLifecycle {

    public enum State {
        CREATED,
        VALIDATED,
        ACCEPTED,
        PARTIALLY_FILLED,
        FILLED,
        CANCELLED,
        REJECTED
    }

    private static final Set<State> TERMINAL = EnumSet.of(State.FILLED, State.CANCELLED, State.REJECTED);

    private static final Set<State> CAN_ACCEPT = EnumSet.of(State.CREATED, State.VALIDATED);
    private static final Set<State> CAN_FILL = EnumSet.of(State.ACCEPTED, State.PARTIALLY_FILLED);
    private static final Set<State> CAN_CANCEL = EnumSet.of(State.CREATED, State.VALIDATED, State.ACCEPTED, State.PARTIALLY_FILLED);

    public static boolean canTransition(State from, State to) {
        if (TERMINAL.contains(from)) return false;
        switch (to) {
            case VALIDATED: return from == State.CREATED;
            case ACCEPTED: return CAN_ACCEPT.contains(from);
            case PARTIALLY_FILLED: case FILLED: return CAN_FILL.contains(from);
            case CANCELLED: case REJECTED: return CAN_CANCEL.contains(from) || from == State.CREATED;
            default: return false;
        }
    }

    public static boolean isTerminal(State state) {
        return TERMINAL.contains(state);
    }

    public static void main(String[] args) {
        System.out.println("CREATED -> ACCEPTED: " + canTransition(State.CREATED, State.ACCEPTED));
        System.out.println("FILLED -> CANCELLED: " + canTransition(State.FILLED, State.CANCELLED));
    }
}
