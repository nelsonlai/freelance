import java.util.*;

class MyCalendar {
    private List<int[]> events;

    public MyCalendar() {
        events = new ArrayList<>();
    }
    
    public boolean book(int startTime, int endTime) {
        for (int[] event : events) {
            if (event[0] < endTime && startTime < event[1]) {
                return false;
            }
        }
        events.add(new int[]{startTime, endTime});
        return true;
    }
}
