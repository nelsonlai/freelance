/**
 * Problem: Longest Substring with At Least K Repeating Characters
 * Difficulty: Medium
 * Tags: array, string, tree, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

import java.util.*;

class Solution {
    public int longestSubstring(String s, int k) {
        if (s.length() < k) {
            return 0;
        }
        
        Map<Character, Integer> count = new HashMap<>();
        for (char c : s.toCharArray()) {
            count.put(c, count.getOrDefault(c, 0) + 1);
        }
        
        for (char c : count.keySet()) {
            if (count.get(c) < k) {
                int maxLen = 0;
                for (String substring : s.split(String.valueOf(c))) {
                    maxLen = Math.max(maxLen, longestSubstring(substring, k));
                }
                return maxLen;
            }
        }
        
        return s.length();
    }
}