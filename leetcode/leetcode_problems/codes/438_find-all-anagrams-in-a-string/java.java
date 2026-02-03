/**
 * Problem: Find All Anagrams in a String
 * Difficulty: Medium
 * Tags: array, string, tree, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

import java.util.*;

class Solution {
    public List<Integer> findAnagrams(String s, String p) {
        List<Integer> result = new ArrayList<>();
        if (s.length() < p.length()) {
            return result;
        }
        
        int[] pCount = new int[26];
        for (char c : p.toCharArray()) {
            pCount[c - 'a']++;
        }
        
        int[] windowCount = new int[26];
        for (int i = 0; i < p.length(); i++) {
            windowCount[s.charAt(i) - 'a']++;
        }
        
        if (Arrays.equals(pCount, windowCount)) {
            result.add(0);
        }
        
        for (int i = p.length(); i < s.length(); i++) {
            windowCount[s.charAt(i) - 'a']++;
            windowCount[s.charAt(i - p.length()) - 'a']--;
            
            if (Arrays.equals(pCount, windowCount)) {
                result.add(i - p.length() + 1);
            }
        }
        
        return result;
    }
}