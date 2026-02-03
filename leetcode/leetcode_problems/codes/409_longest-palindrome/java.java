/**
 * Problem: Longest Palindrome
 * Difficulty: Easy
 * Tags: string, greedy, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int longestPalindrome(String s) {
        Map<Character, Integer> count = new HashMap<>();
        for (char c : s.toCharArray()) {
            count.put(c, count.getOrDefault(c, 0) + 1);
        }
        
        int length = 0;
        boolean hasOdd = false;
        
        for (int freq : count.values()) {
            length += (freq / 2) * 2;
            if (freq % 2 == 1) {
                hasOdd = true;
            }
        }
        
        return length + (hasOdd ? 1 : 0);
    }
}