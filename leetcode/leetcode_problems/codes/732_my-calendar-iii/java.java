import java.util.*;

class MyCalendarThree {
    private TreeMap<Integer, Integer> delta;

    public MyCalendarThree() {
        delta = new TreeMap<>();
    }
    
    public int book(int startTime, int endTime) {
        delta.put(startTime, delta.getOrDefault(startTime, 0) + 1);
        delta.put(endTime, delta.getOrDefault(endTime, 0) - 1);
        
        int active = 0;
        int maxActive = 0;
        for (int count : delta.values()) {
            active += count;
            maxActive = Math.max(maxActive, active);
        }
        
        return maxActive;
    }
}
