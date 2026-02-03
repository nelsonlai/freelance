/**
 * Problem: Valid Square
 * Difficulty: Medium
 * Tags: math
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public boolean validSquare(int[] p1, int[] p2, int[] p3, int[] p4) {
        int[][] points = {p1, p2, p3, p4};
        List<Integer> distances = new ArrayList<>();
        
        for (int i = 0; i < 4; i++) {
            for (int j = i + 1; j < 4; j++) {
                distances.add(dist(points[i], points[j]));
            }
        }
        
        Collections.sort(distances);
        
        return distances.get(0) > 0 &&
               distances.get(0).equals(distances.get(1)) &&
               distances.get(1).equals(distances.get(2)) &&
               distances.get(2).equals(distances.get(3)) &&
               distances.get(4).equals(distances.get(5));
    }
    
    private int dist(int[] p, int[] q) {
        return (p[0] - q[0]) * (p[0] - q[0]) + (p[1] - q[1]) * (p[1] - q[1]);
    }
}