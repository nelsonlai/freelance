/**
 * Problem: Perfect Rectangle
 * Difficulty: Hard
 * Tags: array, math, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public boolean isRectangleCover(int[][] rectangles) {
        Map<String, Integer> corners = new HashMap<>();
        long area = 0;
        int minX = Integer.MAX_VALUE, minY = Integer.MAX_VALUE;
        int maxX = Integer.MIN_VALUE, maxY = Integer.MIN_VALUE;
        
        for (int[] rect : rectangles) {
            int x1 = rect[0], y1 = rect[1], x2 = rect[2], y2 = rect[3];
            minX = Math.min(minX, x1);
            minY = Math.min(minY, y1);
            maxX = Math.max(maxX, x2);
            maxY = Math.max(maxY, y2);
            
            area += (long)(x2 - x1) * (y2 - y1);
            
            String[] points = {x1 + "," + y1, x1 + "," + y2, x2 + "," + y1, x2 + "," + y2};
            for (String point : points) {
                corners.put(point, corners.getOrDefault(point, 0) + 1);
            }
        }
        
        long expectedArea = (long)(maxX - minX) * (maxY - minY);
        if (area != expectedArea) {
            return false;
        }
        
        Set<String> cornerPoints = new HashSet<>(Arrays.asList(
            minX + "," + minY, minX + "," + maxY, maxX + "," + minY, maxX + "," + maxY));
        
        for (String point : corners.keySet()) {
            int count = corners.get(point);
            if (cornerPoints.contains(point)) {
                if (count != 1) {
                    return false;
                }
            } else {
                if (count % 2 != 0) {
                    return false;
                }
            }
        }
        
        return true;
    }
}