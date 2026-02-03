/**
 * Problem: The Earliest and Latest Rounds Where Players Compete
 * Difficulty: Hard
 * Tags: array, dp, recursion
 * 
 * Approach: Recursive DP to simulate tournament rounds
 * Time Complexity: O(n^2) where n is players
 * Space Complexity: O(n^2)
 */

import java.util.*;

class Solution {
    private Map<String, int[]> memo = new HashMap<>();
    
    public int[] earliestAndLatest(int n, int firstPlayer, int secondPlayer) {
        return dp(n, firstPlayer, secondPlayer);
    }
    
    private int[] dp(int players, int first, int second) {
        if (first + second == players + 1) {
            return new int[]{1, 1};
        }
        
        if (first > second) {
            int temp = first;
            first = second;
            second = temp;
        }
        
        String key = players + "," + first + "," + second;
        if (memo.containsKey(key)) {
            return memo.get(key);
        }
        
        int[] result;
        int half = (players + 1) / 2;
        
        if (first + second <= players + 1) {
            result = dp(half, first, second);
        } else {
            int offset = players - half;
            result = dp(half, first - offset, second - offset);
        }
        
        memo.put(key, result);
        return result;
    }
}