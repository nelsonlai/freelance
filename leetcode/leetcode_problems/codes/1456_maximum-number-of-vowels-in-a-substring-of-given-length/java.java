/**
 * Problem: Maximum Number of Vowels in a Substring of Given Length
 * Difficulty: Medium
 * Tags: array, string, tree
 * 
 * Approach: Sliding window - maintain count of vowels in window of size k
 * Time Complexity: O(n) where n is length of s
 * Space Complexity: O(1)
 */

import java.util.*;

class Solution {
    public int maxVowels(String s, int k) {
        Set<Character> vowels = new HashSet<>(Arrays.asList('a', 'e', 'i', 'o', 'u'));
        int maxCount = 0;
        int currentCount = 0;
        
        for (int i = 0; i < k; i++) {
            if (vowels.contains(s.charAt(i))) {
                currentCount++;
            }
        }
        maxCount = currentCount;
        
        for (int i = k; i < s.length(); i++) {
            if (vowels.contains(s.charAt(i - k))) {
                currentCount--;
            }
            if (vowels.contains(s.charAt(i))) {
                currentCount++;
            }
            maxCount = Math.max(maxCount, currentCount);
        }
        
        return maxCount;
    }
}