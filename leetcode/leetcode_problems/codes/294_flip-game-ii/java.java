/**
 * Problem: Flip Game II
 * Difficulty: Medium
 * Tags: string, dp, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    private Map<String, Boolean> memo = new HashMap<>();
    
    public boolean canWin(String currentState) {
        if (memo.containsKey(currentState)) {
            return memo.get(currentState);
        }
        
        for (int i = 0; i < currentState.length() - 1; i++) {
            if (currentState.charAt(i) == '+' && currentState.charAt(i + 1) == '+') {
                String newState = currentState.substring(0, i) + "--" + currentState.substring(i + 2);
                if (!canWin(newState)) {
                    memo.put(currentState, true);
                    return true;
                }
            }
        }
        
        memo.put(currentState, false);
        return false;
    }
}