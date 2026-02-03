/**
 * Problem: Minimum Number of Work Sessions to Finish the Tasks
 * Difficulty: Medium
 * Tags: array, dp, bitmask
 * 
 * Approach: DP with bitmask - find minimum sessions to complete all tasks
 * Time Complexity: O(n * 2^n) where n is tasks
 * Space Complexity: O(2^n)
 */

import java.util.*;

class Solution {
    public int minSessions(int[] tasks, int sessionTime) {
        int n = tasks.length;
        int[] memo = new int[1 << n];
        Arrays.fill(memo, -1);
        return dp((1 << n) - 1, tasks, sessionTime, memo);
    }
    
    private int dp(int mask, int[] tasks, int sessionTime, int[] memo) {
        if (mask == 0) {
            return 0;
        }
        
        if (memo[mask] != -1) {
            return memo[mask];
        }
        
        int result = Integer.MAX_VALUE;
        
        // Try all subsets that fit in one session
        for (int submask = mask; submask > 0; submask = (submask - 1) & mask) {
            if ((submask & mask) != submask) {
                continue;
            }
            
            int total = 0;
            for (int i = 0; i < tasks.length; i++) {
                if ((submask >> i) & 1 == 1) {
                    total += tasks[i];
                }
            }
            
            if (total <= sessionTime) {
                result = Math.min(result, 1 + dp(mask ^ submask, tasks, sessionTime, memo));
            }
        }
        
        memo[mask] = result;
        return result;
    }
}
