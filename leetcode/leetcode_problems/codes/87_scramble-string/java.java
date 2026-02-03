/**
 * Problem: Scramble String
 * Difficulty: Hard
 * Tags: string, tree, dp
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    private Map<String, Boolean> memo = new HashMap<>();
    
    public boolean isScramble(String s1, String s2) {
        if (s1.equals(s2)) {
            return true;
        }
        if (s1.length() != s2.length()) {
            return false;
        }
        
        String key = s1 + "#" + s2;
        if (memo.containsKey(key)) {
            return memo.get(key);
        }
        
        char[] arr1 = s1.toCharArray();
        char[] arr2 = s2.toCharArray();
        Arrays.sort(arr1);
        Arrays.sort(arr2);
        if (!Arrays.equals(arr1, arr2)) {
            memo.put(key, false);
            return false;
        }
        
        int n = s1.length();
        for (int i = 1; i < n; i++) {
            if ((isScramble(s1.substring(0, i), s2.substring(0, i)) && 
                 isScramble(s1.substring(i), s2.substring(i))) ||
                (isScramble(s1.substring(0, i), s2.substring(n - i)) && 
                 isScramble(s1.substring(i), s2.substring(0, n - i)))) {
                memo.put(key, true);
                return true;
            }
        }
        
        memo.put(key, false);
        return false;
    }
}