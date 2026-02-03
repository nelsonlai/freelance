/**
 * Problem: Line Reflection
 * Difficulty: Medium
 * Tags: array, math, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public boolean isReflected(int[][] points) {
        if (points.length == 0) {
            return true;
        }
        
        Set<String> pointSet = new HashSet<>();
        int minX = Integer.MAX_VALUE;
        int maxX = Integer.MIN_VALUE;
        
        for (int[] point : points) {
            minX = Math.min(minX, point[0]);
            maxX = Math.max(maxX, point[0]);
            pointSet.add(point[0] + "," + point[1]);
        }
        
        double midX = (minX + maxX) / 2.0;
        
        for (int[] point : points) {
            double reflectedX = 2 * midX - point[0];
            String reflected = (int)reflectedX + "," + point[1];
            if (!pointSet.contains(reflected)) {
                return false;
            }
        }
        
        return true;
    }
}