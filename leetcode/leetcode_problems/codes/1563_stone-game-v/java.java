/**
 * Problem: Stone Game V
 * Difficulty: Hard
 * Tags: array, dp, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    private Map<String, Integer> memo = new HashMap<>();
    private int[] prefix;
    
    public int stoneGameV(int[] stoneValue) {
        int n = stoneValue.length;
        prefix = new int[n + 1];
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + stoneValue[i];
        }
        
        return dp(0, n - 1);
    }
    
    private int dp(int i, int j) {
        if (i >= j) {
            return 0;
        }
        
        String key = i + "," + j;
        if (memo.containsKey(key)) {
            return memo.get(key);
        }
        
        int result = 0;
        for (int k = i; k < j; k++) {
            int leftSum = prefix[k + 1] - prefix[i];
            int rightSum = prefix[j + 1] - prefix[k + 1];
            
            if (leftSum < rightSum) {
                result = Math.max(result, leftSum + dp(i, k));
            } else if (leftSum > rightSum) {
                result = Math.max(result, rightSum + dp(k + 1, j));
            } else {
                result = Math.max(result, leftSum + Math.max(dp(i, k), dp(k + 1, j)));
            }
        }
        
        memo.put(key, result);
        return result;
    }
}