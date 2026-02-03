/**
 * Problem: Campus Bikes II
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: DP with bitmask - assign bikes to workers with minimum total distance
 * Time Complexity: O(m * 2^n) where m is workers, n is bikes
 * Space Complexity: O(2^n) for DP
 */

import java.util.*;

class Solution {
    private Map<String, Integer> memo = new HashMap<>();
    
    public int assignBikes(int[][] workers, int[][] bikes) {
        return dp(workers, bikes, 0, 0);
    }
    
    private int dp(int[][] workers, int[][] bikes, int workerIdx, int mask) {
        if (workerIdx == workers.length) {
            return 0;
        }
        
        String key = workerIdx + "," + mask;
        if (memo.containsKey(key)) {
            return memo.get(key);
        }
        
        int result = Integer.MAX_VALUE;
        for (int bikeIdx = 0; bikeIdx < bikes.length; bikeIdx++) {
            if ((mask & (1 << bikeIdx)) == 0) {
                int dist = manhattan(workers[workerIdx], bikes[bikeIdx]);
                result = Math.min(result, dist + dp(workers, bikes, workerIdx + 1, mask | (1 << bikeIdx)));
            }
        }
        
        memo.put(key, result);
        return result;
    }
    
    private int manhattan(int[] p1, int[] p2) {
        return Math.abs(p1[0] - p2[0]) + Math.abs(p1[1] - p2[1]);
    }
}