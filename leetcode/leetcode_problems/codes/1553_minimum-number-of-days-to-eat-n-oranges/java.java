/**
 * Problem: Minimum Number of Days to Eat N Oranges
 * Difficulty: Hard
 * Tags: dp
 * 
 * Approach: Dynamic programming with memoization or tabulation
 * Time Complexity: O(n * m) where n and m are problem dimensions
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    private Map<Integer, Integer> memo = new HashMap<>();
    
    public int minDays(int n) {
        if (n <= 1) {
            return n;
        }
        
        if (memo.containsKey(n)) {
            return memo.get(n);
        }
        
        int result = n;
        result = Math.min(result, 1 + minDays(n - 1));
        
        if (n % 2 == 0) {
            result = Math.min(result, 1 + minDays(n / 2));
        }
        
        if (n % 3 == 0) {
            result = Math.min(result, 1 + minDays(n / 3));
        }
        
        memo.put(n, result);
        return result;
    }
}