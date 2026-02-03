/**
 * Problem: Digit Count in Range
 * Difficulty: Hard
 * Tags: dp, math
 * 
 * Approach: Count digits in [0, high] - count digits in [0, low-1]
 * Time Complexity: O(log n) where n is the number
 * Space Complexity: O(log n) for recursion
 */

import java.util.*;

class Solution {
    private Map<String, Integer> memo = new HashMap<>();
    private String digits;
    
    public int digitsCount(int d, int low, int high) {
        return countDigits(high, d) - countDigits(low - 1, d);
    }
    
    private int countDigits(int n, int d) {
        if (n < 0) return 0;
        digits = String.valueOf(n);
        return dp(0, true, false, 0, d);
    }
    
    private int dp(int pos, boolean tight, boolean started, int count, int d) {
        if (pos == digits.length()) {
            return started ? count : 0;
        }
        
        String key = pos + "," + tight + "," + started + "," + count;
        if (memo.containsKey(key)) {
            return memo.get(key);
        }
        
        int limit = tight ? (digits.charAt(pos) - '0') : 9;
        int result = 0;
        
        for (int digit = 0; digit <= limit; digit++) {
            boolean newTight = tight && (digit == limit);
            boolean newStarted = started || (digit > 0);
            int newCount = count + (digit == d && newStarted ? 1 : 0);
            result += dp(pos + 1, newTight, newStarted, newCount, d);
        }
        
        memo.put(key, result);
        return result;
    }
}