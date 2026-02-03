/**
 * Problem: Frog Jump
 * Difficulty: Hard
 * Tags: array, dp, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    public boolean canCross(int[] stones) {
        Set<Integer> stoneSet = new HashSet<>();
        for (int stone : stones) {
            stoneSet.add(stone);
        }
        
        Map<String, Boolean> memo = new HashMap<>();
        return dfs(1, 1, stones[stones.length - 1], stoneSet, memo);
    }
    
    private boolean dfs(int position, int lastJump, int target, Set<Integer> stoneSet, Map<String, Boolean> memo) {
        if (position == target) {
            return true;
        }
        
        String key = position + "," + lastJump;
        if (memo.containsKey(key)) {
            return memo.get(key);
        }
        
        for (int jump = lastJump - 1; jump <= lastJump + 1; jump++) {
            if (jump > 0) {
                int nextPosition = position + jump;
                if (stoneSet.contains(nextPosition) && dfs(nextPosition, jump, target, stoneSet, memo)) {
                    memo.put(key, true);
                    return true;
                }
            }
        }
        
        memo.put(key, false);
        return false;
    }
}