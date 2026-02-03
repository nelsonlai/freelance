/**
 * Problem: Minimum Cost to Connect Two Groups of Points
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    private Map<String, Integer> memo = new HashMap<>();
    private List<List<Integer>> cost;
    private int m, n;
    private int[] minCostGroup2;
    
    public int connectTwoGroups(List<List<Integer>> cost) {
        this.cost = cost;
        this.m = cost.size();
        this.n = cost.get(0).size();
        
        minCostGroup2 = new int[n];
        for (int j = 0; j < n; j++) {
            int min = Integer.MAX_VALUE;
            for (int i = 0; i < m; i++) {
                min = Math.min(min, cost.get(i).get(j));
            }
            minCostGroup2[j] = min;
        }
        
        return dp(0, 0);
    }
    
    private int dp(int i, int mask) {
        if (i == m) {
            int result = 0;
            for (int j = 0; j < n; j++) {
                if ((mask & (1 << j)) == 0) {
                    result += minCostGroup2[j];
                }
            }
            return result;
        }
        
        String key = i + "," + mask;
        if (memo.containsKey(key)) {
            return memo.get(key);
        }
        
        int result = Integer.MAX_VALUE;
        for (int j = 0; j < n; j++) {
            result = Math.min(result, cost.get(i).get(j) + dp(i + 1, mask | (1 << j)));
        }
        
        memo.put(key, result);
        return result;
    }
}