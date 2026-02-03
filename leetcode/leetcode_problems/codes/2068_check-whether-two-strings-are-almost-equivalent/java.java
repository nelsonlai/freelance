/**
 * Problem: Check Whether Two Strings are Almost Equivalent
 * Difficulty: Easy
 * Tags: string, hash
 * 
 * Approach: Count character frequencies and check if difference <= 3 for all characters
 * Time Complexity: O(n + m) where n, m are string lengths
 * Space Complexity: O(26)
 */

import java.util.*;

class Solution {
    public boolean checkAlmostEquivalent(String word1, String word2) {
        Map<Character, Integer> count1 = new HashMap<>();
        Map<Character, Integer> count2 = new HashMap<>();
        
        for (char c : word1.toCharArray()) {
            count1.put(c, count1.getOrDefault(c, 0) + 1);
        }
        for (char c : word2.toCharArray()) {
            count2.put(c, count2.getOrDefault(c, 0) + 1);
        }
        
        Set<Character> allChars = new HashSet<>(count1.keySet());
        allChars.addAll(count2.keySet());
        
        for (char c : allChars) {
            int diff = Math.abs(count1.getOrDefault(c, 0) - count2.getOrDefault(c, 0));
            if (diff > 3) {
                return false;
            }
        }
        
        return true;
    }
}