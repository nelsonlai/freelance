/**
 * Problem: Brick Wall
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int leastBricks(List<List<Integer>> wall) {
        Map<Integer, Integer> count = new HashMap<>();
        
        for (List<Integer> row : wall) {
            int prefix = 0;
            for (int i = 0; i < row.size() - 1; i++) {
                prefix += row.get(i);
                count.put(prefix, count.getOrDefault(prefix, 0) + 1);
            }
        }
        
        int maxCount = 0;
        for (int cnt : count.values()) {
            maxCount = Math.max(maxCount, cnt);
        }
        
        return wall.size() - maxCount;
    }
}