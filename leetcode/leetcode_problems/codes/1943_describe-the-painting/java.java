/**
 * Problem: Describe the Painting
 * Difficulty: Medium
 * Tags: array, hash, sort, sweep line
 * 
 * Approach: Sweep line to track color changes at each position
 * Time Complexity: O(n log n) where n is segments
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public List<List<Long>> splitPainting(int[][] segments) {
        Map<Integer, Long> events = new TreeMap<>();
        
        for (int[] seg : segments) {
            events.put(seg[0], events.getOrDefault(seg[0], 0L) + seg[2]);
            events.put(seg[1], events.getOrDefault(seg[1], 0L) - seg[2]);
        }
        
        List<List<Long>> result = new ArrayList<>();
        long currentColor = 0;
        Integer prevPos = null;
        
        for (Map.Entry<Integer, Long> entry : events.entrySet()) {
            int pos = entry.getKey();
            if (prevPos != null && currentColor > 0) {
                result.add(Arrays.asList((long) prevPos, (long) pos, currentColor));
            }
            
            currentColor += entry.getValue();
            prevPos = pos;
        }
        
        return result;
    }
}