/**
 * Problem: Unique Substrings in Wraparound String
 * Difficulty: Medium
 * Tags: string, tree, dp
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    public int findSubstringInWraproundString(String s) {
        if (s == null || s.length() == 0) {
            return 0;
        }
        
        Map<Character, Integer> count = new HashMap<>();
        int length = 1;
        
        for (int i = 0; i < s.length(); i++) {
            if (i > 0 && (s.charAt(i) - s.charAt(i-1) == 1 || (s.charAt(i-1) == 'z' && s.charAt(i) == 'a'))) {
                length++;
            } else {
                length = 1;
            }
            
            char c = s.charAt(i);
            count.put(c, Math.max(count.getOrDefault(c, 0), length));
        }
        
        int result = 0;
        for (int val : count.values()) {
            result += val;
        }
        return result;
    }
}