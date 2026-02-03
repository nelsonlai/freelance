/**
 * Problem: Coin Path
 * Difficulty: Hard
 * Tags: array, graph, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    public List<Integer> cheapestJump(int[] coins, int maxJump) {
        int n = coins.length;
        if (coins[n-1] == -1) {
            return new ArrayList<>();
        }
        
        long[] dp = new long[n];
        int[] next = new int[n];
        Arrays.fill(dp, Long.MAX_VALUE);
        Arrays.fill(next, -1);
        dp[n-1] = coins[n-1];
        
        for (int i = n - 2; i >= 0; i--) {
            if (coins[i] == -1) {
                continue;
            }
            
            for (int j = i + 1; j < Math.min(i + maxJump + 1, n); j++) {
                if (dp[j] != Long.MAX_VALUE && dp[j] + coins[i] < dp[i]) {
                    dp[i] = dp[j] + coins[i];
                    next[i] = j;
                }
            }
        }
        
        if (dp[0] == Long.MAX_VALUE) {
            return new ArrayList<>();
        }
        
        List<Integer> result = new ArrayList<>();
        int i = 0;
        while (i != -1) {
            result.add(i + 1);
            i = next[i];
        }
        
        return result;
    }
}