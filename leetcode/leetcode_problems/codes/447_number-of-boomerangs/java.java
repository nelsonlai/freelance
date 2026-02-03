/**
 * Problem: Number of Boomerangs
 * Difficulty: Medium
 * Tags: array, math, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int numberOfBoomerangs(int[][] points) {
        int total = 0;
        for (int i = 0; i < points.length; i++) {
            Map<Integer, Integer> distCount = new HashMap<>();
            for (int j = 0; j < points.length; j++) {
                if (i != j) {
                    int dx = points[i][0] - points[j][0];
                    int dy = points[i][1] - points[j][1];
                    int dist = dx * dx + dy * dy;
                    distCount.put(dist, distCount.getOrDefault(dist, 0) + 1);
                }
            }
            for (int count : distCount.values()) {
                total += count * (count - 1);
            }
        }
        return total;
    }
}