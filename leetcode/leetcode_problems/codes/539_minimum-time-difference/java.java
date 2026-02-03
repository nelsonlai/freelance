/**
 * Problem: Minimum Time Difference
 * Difficulty: Medium
 * Tags: array, string, math, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int findMinDifference(List<String> timePoints) {
        List<Integer> minutes = new ArrayList<>();
        for (String time : timePoints) {
            String[] parts = time.split(":");
            minutes.add(Integer.parseInt(parts[0]) * 60 + Integer.parseInt(parts[1]));
        }
        Collections.sort(minutes);
        
        int minDiff = Integer.MAX_VALUE;
        for (int i = 0; i < minutes.size(); i++) {
            int diff = minutes.get(i) - minutes.get((i - 1 + minutes.size()) % minutes.size());
            minDiff = Math.min(minDiff, Math.min(diff, 1440 - diff));
        }
        
        return minDiff;
    }
}