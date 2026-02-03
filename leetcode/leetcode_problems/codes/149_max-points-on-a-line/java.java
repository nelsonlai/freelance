/**
 * Problem: Max Points on a Line
 * Difficulty: Hard
 * Tags: array, math, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int maxPoints(int[][] points) {
        if (points.length <= 2) {
            return points.length;
        }
        
        int maxPoints = 0;
        
        for (int i = 0; i < points.length; i++) {
            Map<String, Integer> slopeCount = new HashMap<>();
            int samePoint = 1;
            
            for (int j = i + 1; j < points.length; j++) {
                int x1 = points[i][0], y1 = points[i][1];
                int x2 = points[j][0], y2 = points[j][1];
                
                if (x1 == x2 && y1 == y2) {
                    samePoint++;
                } else {
                    int dx = x2 - x1;
                    int dy = y2 - y1;
                    int g = gcd(dx, dy);
                    String slope = (dx / g) + "/" + (dy / g);
                    slopeCount.put(slope, slopeCount.getOrDefault(slope, 0) + 1);
                }
            }
            
            int currentMax = samePoint;
            for (int count : slopeCount.values()) {
                currentMax = Math.max(currentMax, samePoint + count);
            }
            maxPoints = Math.max(maxPoints, currentMax);
        }
        
        return maxPoints;
    }
    
    private int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
}