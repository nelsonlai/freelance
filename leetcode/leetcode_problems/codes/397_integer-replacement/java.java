/**
 * Problem: Integer Replacement
 * Difficulty: Medium
 * Tags: dp, greedy
 * 
 * Approach: Dynamic programming with memoization or tabulation
 * Time Complexity: O(n * m) where n and m are problem dimensions
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    private Map<Long, Integer> memo = new HashMap<>();
    
    public int integerReplacement(int n) {
        return dfs((long)n);
    }
    
    private int dfs(long n) {
        if (n == 1) {
            return 0;
        }
        if (memo.containsKey(n)) {
            return memo.get(n);
        }
        
        int result;
        if (n % 2 == 0) {
            result = 1 + dfs(n / 2);
        } else {
            result = 1 + Math.min(dfs(n + 1), dfs(n - 1));
        }
        
        memo.put(n, result);
        return result;
    }
}