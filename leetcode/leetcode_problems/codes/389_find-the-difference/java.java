/**
 * Problem: Find the Difference
 * Difficulty: Easy
 * Tags: string, hash, sort
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public char findTheDifference(String s, String t) {
        Map<Character, Integer> sCount = new HashMap<>();
        for (char c : s.toCharArray()) {
            sCount.put(c, sCount.getOrDefault(c, 0) + 1);
        }
        
        for (char c : t.toCharArray()) {
            int count = sCount.getOrDefault(c, 0);
            if (count == 0) {
                return c;
            }
            sCount.put(c, count - 1);
        }
        
        return ' ';
    }
}