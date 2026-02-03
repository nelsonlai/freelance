/**
 * Problem: Can I Win
 * Difficulty: Medium
 * Tags: dp, math
 * 
 * Approach: Dynamic programming with memoization or tabulation
 * Time Complexity: O(n * m) where n and m are problem dimensions
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    public boolean canIWin(int maxChoosableInteger, int desiredTotal) {
        if (desiredTotal <= maxChoosableInteger) {
            return true;
        }
        if (maxChoosableInteger * (maxChoosableInteger + 1) / 2 < desiredTotal) {
            return false;
        }
        
        Map<Integer, Boolean> memo = new HashMap<>();
        return canWin(0, desiredTotal, maxChoosableInteger, memo);
    }
    
    private boolean canWin(int used, int remaining, int maxChoosable, Map<Integer, Boolean> memo) {
        if (memo.containsKey(used)) {
            return memo.get(used);
        }
        
        for (int i = 1; i <= maxChoosable; i++) {
            if ((used & (1 << i)) == 0) {
                if (i >= remaining || !canWin(used | (1 << i), remaining - i, maxChoosable, memo)) {
                    memo.put(used, true);
                    return true;
                }
            }
        }
        
        memo.put(used, false);
        return false;
    }
}