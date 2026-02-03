/**
 * Problem: Average Height of Buildings in Each Segment
 * Difficulty: Medium
 * Tags: array, greedy, sort, line sweep
 * 
 * Approach: Use line sweep to merge overlapping buildings, calculate average heights
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public int[][] averageHeightOfBuildings(int[][] buildings) {
        List<int[]> events = new ArrayList<>();
        
        for (int[] building : buildings) {
            int start = building[0];
            int end = building[1];
            int height = building[2];
            events.add(new int[]{start, height, 1});
            events.add(new int[]{end, height, -1});
        }
        
        events.sort((a, b) -> {
            if (a[0] != b[0]) {
                return Integer.compare(a[0], b[0]);
            }
            return Integer.compare(b[2], a[2]); // End before start
        });
        
        List<int[]> result = new ArrayList<>();
        long currentSum = 0;
        int currentCount = 0;
        Integer prevPos = null;
        
        for (int[] event : events) {
            int pos = event[0];
            int height = event[1];
            int delta = event[2];
            
            if (prevPos != null && prevPos < pos && currentCount > 0) {
                int avgHeight = (int) (currentSum / currentCount);
                if (!result.isEmpty() && result.get(result.size() - 1)[1] == prevPos && 
                    result.get(result.size() - 1)[2] == avgHeight) {
                    // Merge with previous segment
                    result.get(result.size() - 1)[1] = pos;
                } else {
                    result.add(new int[]{prevPos, pos, avgHeight});
                }
            }
            
            currentSum += height * delta;
            currentCount += delta;
            prevPos = pos;
        }
        
        return result.toArray(new int[result.size()][]);
    }
}