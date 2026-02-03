/**
 * Problem: Numbers With Repeated Digits
 * Difficulty: Hard
 * Tags: dp, math
 * 
 * Approach: Count numbers without repeated digits, subtract from total
 * Time Complexity: O(log n)
 * Space Complexity: O(log n) for recursion
 */

import java.util.*;

class Solution {
    private String digits;
    private Map<String, Integer> memo = new HashMap<>();
    
    public int numDupDigitsAtMostN(int n) {
        digits = String.valueOf(n + 1);
        return n - dp(0, true, 0, false);
    }
    
    private int dp(int pos, boolean tight, int mask, boolean started) {
        if (pos == digits.length()) {
            return started ? 1 : 0;
        }
        
        String key = pos + "," + tight + "," + mask + "," + started;
        if (memo.containsKey(key)) {
            return memo.get(key);
        }
        
        int limit = tight ? (digits.charAt(pos) - '0') : 9;
        int result = 0;
        
        for (int d = 0; d <= limit; d++) {
            boolean newTight = tight && (d == limit);
            boolean newStarted = started || (d > 0);
            
            if (!newStarted) {
                result += dp(pos + 1, newTight, mask, newStarted);
            } else if ((mask & (1 << d)) == 0) {
                result += dp(pos + 1, newTight, mask | (1 << d), newStarted);
            }
        }
        
        memo.put(key, result);
        return result;
    }
}