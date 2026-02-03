import java.util.*;

class Solution {
    public List<Interval> employeeFreeTime(List<List<Interval>> schedule) {
        List<Interval> intervals = new ArrayList<>();
        for (List<Interval> emp : schedule) {
            intervals.addAll(emp);
        }
        
        intervals.sort((a, b) -> a.start - b.start);
        List<Interval> merged = new ArrayList<>();
        
        for (Interval interval : intervals) {
            if (merged.isEmpty() || merged.get(merged.size() - 1).end < interval.start) {
                merged.add(interval);
            } else {
                merged.get(merged.size() - 1).end = Math.max(merged.get(merged.size() - 1).end, interval.end);
            }
        }
        
        List<Interval> result = new ArrayList<>();
        for (int i = 0; i < merged.size() - 1; i++) {
            result.add(new Interval(merged.get(i).end, merged.get(i + 1).start));
        }
        
        return result;
    }
}
