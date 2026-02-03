/**
 * Problem: Longest Duplicate Substring
 * Difficulty: Hard
 * Tags: array, string, tree, hash, search
 * 
 * Approach: Binary search on length + rolling hash to check for duplicates
 * Time Complexity: O(n log n)
 * Space Complexity: O(n) for hash set
 */

import java.util.*;

class Solution {
    private static final long BASE = 26;
    private static final long MOD = 1000000007;
    
    public String longestDupSubstring(String s) {
        int n = s.length();
        int left = 1, right = n;
        String result = "";
        
        while (left < right) {
            int mid = (left + right) / 2;
            String dup = search(s, mid);
            if (dup != null) {
                result = dup;
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        return result;
    }
    
    private String search(String s, int length) {
        Set<Long> hashSet = new HashSet<>();
        long hashVal = 0;
        long power = 1;
        
        for (int i = 0; i < length; i++) {
            hashVal = (hashVal * BASE + (s.charAt(i) - 'a')) % MOD;
            if (i > 0) {
                power = (power * BASE) % MOD;
            }
        }
        hashSet.add(hashVal);
        
        for (int i = length; i < s.length(); i++) {
            hashVal = ((hashVal - (s.charAt(i - length) - 'a') * power) * BASE + 
                      (s.charAt(i) - 'a')) % MOD;
            if (hashVal < 0) hashVal += MOD;
            
            if (hashSet.contains(hashVal)) {
                return s.substring(i - length + 1, i + 1);
            }
            hashSet.add(hashVal);
        }
        
        return null;
    }
}