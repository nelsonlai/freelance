/**
 * Problem: Data Stream as Disjoint Intervals
 * Difficulty: Hard
 * Tags: graph, hash, sort, search
 * 
 * Approach: Use hash map for O(1) lookups
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class SummaryRanges {
    private List<int[]> intervals;

    public SummaryRanges() {
        intervals = new ArrayList<>();
    }
    
    public void addNum(int value) {
        List<int[]> newIntervals = new ArrayList<>();
        int[] newInterval = {value, value};
        boolean inserted = false;
        
        for (int[] interval : intervals) {
            if (interval[1] < value - 1) {
                newIntervals.add(interval);
            } else if (interval[0] > value + 1) {
                if (!inserted) {
                    newIntervals.add(newInterval);
                    inserted = true;
                }
                newIntervals.add(interval);
            } else {
                newInterval[0] = Math.min(newInterval[0], interval[0]);
                newInterval[1] = Math.max(newInterval[1], interval[1]);
                inserted = true;
            }
        }
        
        if (!inserted) {
            newIntervals.add(newInterval);
        }
        
        intervals = newIntervals;
    }
    
    public int[][] getIntervals() {
        return intervals.toArray(new int[intervals.size()][]);
    }
}

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges obj = new SummaryRanges();
 * obj.addNum(value);
 * int[][] param_2 = obj.getIntervals();
 */