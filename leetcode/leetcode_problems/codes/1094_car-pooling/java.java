/**
 * Problem: Car Pooling
 * Difficulty: Medium
 * Tags: array, sort, queue, heap
 * 
 * Approach: Track passenger changes at each location, check capacity
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n) for events
 */

import java.util.*;

class Solution {
    public boolean carPooling(int[][] trips, int capacity) {
        List<int[]> events = new ArrayList<>();
        for (int[] trip : trips) {
            events.add(new int[]{trip[1], trip[0]});
            events.add(new int[]{trip[2], -trip[0]});
        }
        
        events.sort((a, b) -> {
            if (a[0] != b[0]) return a[0] - b[0];
            return a[1] - b[1];
        });
        
        int current = 0;
        for (int[] event : events) {
            current += event[1];
            if (current > capacity) {
                return false;
            }
        }
        
        return true;
    }
}