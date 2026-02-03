/**
 * Problem: Find K-Length Substrings With No Repeated Characters
 * Difficulty: Medium
 * Tags: array, string, tree, hash
 * 
 * Approach: Sliding window - maintain window of size k with no duplicates
 * Time Complexity: O(n) where n is string length
 * Space Complexity: O(k) for character set
 */

import java.util.*;

class Solution {
    public int numKLenSubstrNoRepeats(String s, int k) {
        if (s.length() < k) {
            return 0;
        }
        
        Map<Character, Integer> charCount = new HashMap<>();
        int result = 0;
        
        for (int i = 0; i < k; i++) {
            charCount.put(s.charAt(i), charCount.getOrDefault(s.charAt(i), 0) + 1);
        }
        
        if (charCount.size() == k) {
            result++;
        }
        
        for (int i = k; i < s.length(); i++) {
            charCount.put(s.charAt(i), charCount.getOrDefault(s.charAt(i), 0) + 1);
            charCount.put(s.charAt(i - k), charCount.get(s.charAt(i - k)) - 1);
            if (charCount.get(s.charAt(i - k)) == 0) {
                charCount.remove(s.charAt(i - k));
            }
            
            if (charCount.size() == k) {
                result++;
            }
        }
        
        return result;
    }
}