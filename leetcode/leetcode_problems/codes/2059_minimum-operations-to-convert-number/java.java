/**
 * Problem: Minimum Operations to Convert Number
 * Difficulty: Medium
 * Tags: array, search, BFS
 * 
 * Approach: BFS to find shortest path from start to goal using operations
 * Time Complexity: O(n * range) where range is [0, 1000]
 * Space Complexity: O(range)
 */

import java.util.*;

class Solution {
    public int minimumOperations(int[] nums, int start, int goal) {
        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{start, 0});
        Set<Integer> visited = new HashSet<>();
        visited.add(start);
        
        while (!queue.isEmpty()) {
            int[] curr = queue.poll();
            int current = curr[0];
            int steps = curr[1];
            
            if (current == goal) {
                return steps;
            }
            
            for (int num : nums) {
                // Try all three operations
                int[] nextVals = {current + num, current - num, current ^ num};
                for (int nextVal : nextVals) {
                    if (nextVal == goal) {
                        return steps + 1;
                    }
                    
                    // Only consider values in valid range [0, 1000]
                    if (nextVal >= 0 && nextVal <= 1000 && !visited.contains(nextVal)) {
                        visited.add(nextVal);
                        queue.offer(new int[]{nextVal, steps + 1});
                    }
                }
            }
        }
        
        return -1;
    }
}