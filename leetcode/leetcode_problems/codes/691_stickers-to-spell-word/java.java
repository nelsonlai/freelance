/**
 * Problem: Stickers to Spell Word
 * Difficulty: Hard
 * Tags: array, string, dp, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    public int minStickers(String[] stickers, String target) {
        int n = target.length();
        int[] dp = new int[1 << n];
        Arrays.fill(dp, Integer.MAX_VALUE);
        dp[0] = 0;
        
        for (int state = 0; state < (1 << n); state++) {
            if (dp[state] == Integer.MAX_VALUE) {
                continue;
            }
            
            for (String sticker : stickers) {
                int nextState = state;
                int[] count = new int[26];
                for (char c : sticker.toCharArray()) {
                    count[c - 'a']++;
                }
                
                for (int i = 0; i < n; i++) {
                    if (((state >> i) & 1) == 0 && count[target.charAt(i) - 'a'] > 0) {
                        nextState |= (1 << i);
                        count[target.charAt(i) - 'a']--;
                    }
                }
                
                dp[nextState] = Math.min(dp[nextState], dp[state] + 1);
            }
        }
        
        return dp[(1 << n) - 1] == Integer.MAX_VALUE ? -1 : dp[(1 << n) - 1];
    }
}