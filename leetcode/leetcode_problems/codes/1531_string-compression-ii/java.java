/**
 * Problem: String Compression II
 * Difficulty: Hard
 * Tags: string, dp
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    private Map<String, Integer> memo = new HashMap<>();
    
    public int getLengthOfOptimalCompression(String s, int k) {
        return dp(0, k, '\0', 0, s);
    }
    
    private int dp(int i, int k, char prevChar, int prevCount, String s) {
        if (k < 0) {
            return Integer.MAX_VALUE;
        }
        if (i == s.length()) {
            return 0;
        }
        
        String key = i + "," + k + "," + prevChar + "," + prevCount;
        if (memo.containsKey(key)) {
            return memo.get(key);
        }
        
        int delete = dp(i + 1, k - 1, prevChar, prevCount, s);
        
        int keep;
        if (s.charAt(i) == prevChar) {
            keep = dp(i + 1, k, prevChar, prevCount + 1, s);
            if (prevCount == 1 || prevCount == 9 || prevCount == 99) {
                keep += 1;
            }
        } else {
            keep = 1 + dp(i + 1, k, s.charAt(i), 1, s);
        }
        
        int result = Math.min(delete, keep);
        memo.put(key, result);
        return result;
    }
}