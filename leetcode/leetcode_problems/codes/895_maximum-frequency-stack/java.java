import java.util.*;

class FreqStack {
    private Map<Integer, Integer> freq;
    private Map<Integer, Stack<Integer>> group;
    private int maxFreq;

    public FreqStack() {
        freq = new HashMap<>();
        group = new HashMap<>();
        maxFreq = 0;
    }

    public void push(int val) {
        freq.put(val, freq.getOrDefault(val, 0) + 1);
        int f = freq.get(val);
        maxFreq = Math.max(maxFreq, f);
        group.computeIfAbsent(f, k -> new Stack<>()).push(val);
    }

    public int pop() {
        int x = group.get(maxFreq).pop();
        freq.put(x, freq.get(x) - 1);
        if (group.get(maxFreq).isEmpty()) {
            maxFreq--;
        }
        return x;
    }
}
