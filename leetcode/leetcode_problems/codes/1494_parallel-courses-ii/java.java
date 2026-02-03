/**
 * Problem: Parallel Courses II
 * Difficulty: Hard
 * Tags: array, graph, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    public int minNumberOfSemesters(int n, int[][] relations, int k) {
        int[] prerequisites = new int[n];
        for (int[] relation : relations) {
            int u = relation[0] - 1;
            int v = relation[1] - 1;
            prerequisites[v] |= 1 << u;
        }
        
        int[] dp = new int[1 << n];
        Arrays.fill(dp, Integer.MAX_VALUE);
        dp[0] = 0;
        
        for (int mask = 0; mask < (1 << n); mask++) {
            if (dp[mask] == Integer.MAX_VALUE) {
                continue;
            }
            
            List<Integer> available = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                if ((mask >> i) & 1) == 0 && (prerequisites[i] & mask) == prerequisites[i]) {
                    available.add(i);
                }
            }
            
            generateSubsets(available, k, 0, new ArrayList<>(), mask, dp);
        }
        
        return dp[(1 << n) - 1];
    }
    
    private void generateSubsets(List<Integer> arr, int k, int start, List<Integer> current, int mask, int[] dp) {
        if (current.size() == k || start == arr.size()) {
            if (!current.isEmpty()) {
                int newMask = mask;
                for (int course : current) {
                    newMask |= 1 << course;
                }
                dp[newMask] = Math.min(dp[newMask], dp[mask] + 1);
            }
            return;
        }
        
        for (int i = start; i < arr.size(); i++) {
            List<Integer> next = new ArrayList<>(current);
            next.add(arr.get(i));
            generateSubsets(arr, k, i + 1, next, mask, dp);
        }
    }
}