import java.util.*;

class MyCalendarTwo {
    private List<int[]> events;
    private List<int[]> overlaps;

    public MyCalendarTwo() {
        events = new ArrayList<>();
        overlaps = new ArrayList<>();
    }
    
    public boolean book(int startTime, int endTime) {
        for (int[] overlap : overlaps) {
            if (overlap[0] < endTime && startTime < overlap[1]) {
                return false;
            }
        }
        
        for (int[] event : events) {
            if (event[0] < endTime && startTime < event[1]) {
                overlaps.add(new int[]{Math.max(event[0], startTime), Math.min(event[1], endTime)});
            }
        }
        
        events.add(new int[]{startTime, endTime});
        return true;
    }
}
