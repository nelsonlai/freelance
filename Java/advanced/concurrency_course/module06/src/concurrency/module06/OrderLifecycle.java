package concurrency.module06;

import java.util.EnumSet;
import java.util.Set;

/**
 * Order lifecycle: states and allowed transitions for an exchange order.
 * Modelled as a state machine; transitions should be performed only by the
 * matching engine (or gateway) thread to avoid races.
 *
 * <p>Typical flow: CREATED → VALIDATED → ACCEPTED → (PARTIALLY_FILLED)* → FILLED,
 * or CREATED/VALIDATED/ACCEPTED/PARTIALLY_FILLED → CANCELLED/REJECTED.
 */
public class OrderLifecycle {

    /** Order states. Terminal states: FILLED, CANCELLED, REJECTED. */
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

    /**
     * Returns true if transitioning from {@code from} to {@code to} is allowed.
     * No transitions out of terminal states; other rules encode valid flows.
     *
     * @param from current state
     * @param to   next state
     * @return true if the transition is valid
     */
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

    /** Returns true if the state is FILLED, CANCELLED, or REJECTED (no further transitions). */
    public static boolean isTerminal(State state) {
        return TERMINAL.contains(state);
    }

    public static void main(String[] args) {
        System.out.println("CREATED -> ACCEPTED: " + canTransition(State.CREATED, State.ACCEPTED));
        System.out.println("FILLED -> CANCELLED: " + canTransition(State.FILLED, State.CANCELLED));
    }
}
