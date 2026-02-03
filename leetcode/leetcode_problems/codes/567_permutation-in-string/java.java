/**
 * Problem: Permutation in String
 * Difficulty: Medium
 * Tags: array, string, tree, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

import java.util.*;

class Solution {
    public boolean checkInclusion(String s1, String s2) {
        if (s1.length() > s2.length()) {
            return false;
        }
        
        int[] s1Count = new int[26];
        int[] windowCount = new int[26];
        
        for (char c : s1.toCharArray()) {
            s1Count[c - 'a']++;
        }
        
        for (int i = 0; i < s2.length(); i++) {
            windowCount[s2.charAt(i) - 'a']++;
            
            if (i >= s1.length()) {
                windowCount[s2.charAt(i - s1.length()) - 'a']--;
            }
            
            if (Arrays.equals(s1Count, windowCount)) {
                return true;
            }
        }
        
        return false;
    }
}