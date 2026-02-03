/**
 * Problem: Unique Length-3 Palindromic Subsequences
 * Difficulty: Medium
 * Tags: array, string, hash
 * 
 * Approach: For each character, find first and last occurrence, count unique middle chars
 * Time Complexity: O(n * 26) where n is length
 * Space Complexity: O(26)
 */

import java.util.*;

class Solution {
    public int countPalindromicSubsequence(String s) {
        Map<Character, Integer> first = new HashMap<>();
        Map<Character, Integer> last = new HashMap<>();
        
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (!first.containsKey(c)) {
                first.put(c, i);
            }
            last.put(c, i);
        }
        
        int result = 0;
        for (char c : first.keySet()) {
            if (first.get(c) < last.get(c)) {
                Set<Character> middle = new HashSet<>();
                for (int i = first.get(c) + 1; i < last.get(c); i++) {
                    middle.add(s.charAt(i));
                }
                result += middle.size();
            }
        }
        
        return result;
    }
}