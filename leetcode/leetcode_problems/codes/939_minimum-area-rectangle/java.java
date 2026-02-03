/**
 * Problem: Minimum Area Rectangle
 * Difficulty: Medium
 * Tags: array, math, hash, sort
 * 
 * Approach: Group points by x-coordinate, for each pair of x-coordinates find common y-coordinates
 * Time Complexity: O(n^2) in worst case
 * Space Complexity: O(n) for storing points
 */

import java.util.*;

class Solution {
    public int minAreaRect(int[][] points) {
        Map<Integer, Set<Integer>> xToY = new HashMap<>();
        for (int[] point : points) {
            xToY.computeIfAbsent(point[0], k -> new HashSet<>()).add(point[1]);
        }
        
        List<Integer> xCoords = new ArrayList<>(xToY.keySet());
        Collections.sort(xCoords);
        
        int minArea = Integer.MAX_VALUE;
        for (int i = 0; i < xCoords.size(); i++) {
            for (int j = i + 1; j < xCoords.size(); j++) {
                int x1 = xCoords.get(i), x2 = xCoords.get(j);
                Set<Integer> commonY = new HashSet<>(xToY.get(x1));
                commonY.retainAll(xToY.get(x2));
                
                if (commonY.size() >= 2) {
                    List<Integer> sortedY = new ArrayList<>(commonY);
                    Collections.sort(sortedY);
                    for (int k = 0; k < sortedY.size() - 1; k++) {
                        int height = sortedY.get(k + 1) - sortedY.get(k);
                        int area = Math.abs(x2 - x1) * height;
                        minArea = Math.min(minArea, area);
                    }
                }
            }
        }
        
        return minArea == Integer.MAX_VALUE ? 0 : minArea;
    }
}